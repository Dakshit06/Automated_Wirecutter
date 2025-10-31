/*
  ESP32 Cable Cutter (Web UI) - No ArduinoJson required
  - AP: "CableFeeder" (open)
  - L298N 4-wire: IN1=14, IN2=27, IN3=26, IN4=25
  - Cutter Servo on GPIO 18 (MG996R)
  - Web UI: set Length (cm) and Quantity, Start, Stop, Emergency
  - Uses AccelStepper and ESP32Servo. Preferences used for steps/cm
  - JSON parsing & building done with simple string helpers (no ArduinoJson)
*/

#include <WiFi.h>
#include <WebServer.h>
#include <AccelStepper.h>
#include <ESP32Servo.h>
#include <Preferences.h>

// ---------- PIN MAP ----------
const int IN1 = 14;
const int IN2 = 27;
const int IN3 = 26;
const int IN4 = 25;
const int SERVO_PIN = 18;

// ---------- Motion / Servo params ----------
WebServer server(80);
AccelStepper stepper(AccelStepper::FULL4WIRE, IN1, IN2, IN3, IN4);
Servo cutterServo;
Preferences prefs;

const char* AP_NAME = "CableFeeder";

// Default calibration: replicate your original 200/3 steps-per-cm (~66.6667)
float STEPS_PER_CM = 200.0f / 3.0f; // editable in code or later via endpoint if needed

const float MAX_FEED_SPEED_STEPS_PER_SEC = 800.0f;
const float FEED_ACCEL_STEPS_PER_SEC2 = 400.0f;

// cutter angles (original used up to 130)
const int CUT_OPEN_ANGLE = 0;
const int CUT_CLOSE_ANGLE = 130;
const unsigned long CUT_HOLD_MS = 400;

// Job / state
volatile bool emergencyActive = false;
bool jobRunning = false;
bool pieceFeeding = false;
long stepsThisPiece = 0;
long pieceStartPosition = 0;
unsigned long pieceStartMs = 0;

int requestedCm = 0;
int requestedQty = 0;
int cyclesRemaining = 0;
int currentPiece = 0;

// Preferences key
const char* PREF_NAMESPACE = "cutter";
const char* PREF_KEY_STEPS_PER_CM = "steps_cm";

// ---------- HTML UI ----------
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!doctype html><html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>Cable Feeder</title>
<style>body{font-family:Arial,Helvetica,sans-serif;padding:14px} input{padding:6px;margin:6px 0;width:140px} button{padding:8px 10px;margin-right:6px} .stat{background:#f2f2f2;padding:10px;border-radius:6px;margin-top:10px;width:320px}</style>
</head><body>
<h2>ESP32 Cable Feeder</h2>
<label>Length (cm): <input id="len" type="number" min="1" max="2000" value="200"></label><br>
<label>Quantity: <input id="qty" type="number" min="1" max="500" value="1"></label><br>
<label>Speed %: <input id="speed" type="number" min="1" max="100" value="50"></label><br>
<button id="start">Start</button>
<button id="stop">Stop After Current</button>
<button id="em">Emergency Stop</button>
<div class="stat">
  <div>Job running: <span id="jr">No</span></div>
  <div>Current piece: <span id="cp">0</span></div>
  <div>Remaining: <span id="rem">0</span></div>
  <div>Steps to go: <span id="stg">0</span></div>
  <div>Piece progress: <span id="pct">0%</span></div>
  <div>Cal steps/cm: <span id="spcm">--</span></div>
</div>
<script>
async function sendAction(obj){
  try {
    const res = await fetch('/action', {method:'POST', headers:{'Content-Type':'application/json'}, body:JSON.stringify(obj)});
    const j = await res.json();
    return j;
  } catch(e){ alert('Error: '+e); }
}

document.getElementById('start').onclick = async ()=>{
  const len = parseInt(document.getElementById('len').value);
  const qty = parseInt(document.getElementById('qty').value);
  const speed = parseInt(document.getElementById('speed').value);
  await sendAction({cmd:'start', cm:len, qty:qty, speed_pct:speed});
};

document.getElementById('stop').onclick = async ()=> {
  await sendAction({cmd:'stop'});
};

document.getElementById('em').onclick = async ()=> {
  if(!confirm('Emergency stop NOW?')) return;
  await sendAction({cmd:'emergency'});
};

async function poll(){
  try {
    const r = await fetch('/status');
    const js = await r.json();
    document.getElementById('jr').textContent = js.jobRunning ? 'Yes' : 'No';
    document.getElementById('cp').textContent = js.currentPiece;
    document.getElementById('rem').textContent = js.remaining;
    document.getElementById('stg').textContent = js.stepsToGo;
    document.getElementById('pct').textContent = Math.round(js.pct) + '%';
    document.getElementById('spcm').textContent = js.stepsPerCm.toFixed(3);
  } catch(e) {
    // ignore errors
  }
  setTimeout(poll, 300);
}
poll();
</script></body></html>
)rawliteral";

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);
  delay(100);

  // load saved calibration if present
  prefs.begin(PREF_NAMESPACE, false);
  if (prefs.isKey(PREF_KEY_STEPS_PER_CM)) {
    STEPS_PER_CM = prefs.getFloat(PREF_KEY_STEPS_PER_CM, STEPS_PER_CM);
  }
  Serial.printf("Steps per cm = %.4f\n", STEPS_PER_CM);

  // stepper config
  stepper.setMaxSpeed(MAX_FEED_SPEED_STEPS_PER_SEC);
  stepper.setAcceleration(FEED_ACCEL_STEPS_PER_SEC2);
  stepper.disableOutputs(); // start off

  // servo attach & set to open
  cutterServo.attach(SERVO_PIN);
  cutterServo.write(CUT_OPEN_ANGLE);
  delay(200);

  // start open AP
  WiFi.softAP(AP_NAME);
  Serial.print("AP started: ");
  Serial.println(AP_NAME);
  Serial.print("AP IP: "); Serial.println(WiFi.softAPIP());

  // web routes
  server.on("/", HTTP_GET, [](){ server.send_P(200, "text/html", INDEX_HTML); });
  server.on("/status", HTTP_GET, handleStatus);
  server.on("/action", HTTP_POST, handleAction);
  server.begin();
  Serial.println("HTTP server started");
}

// ---------- Loop ----------
void loop() {
  server.handleClient();

  // emergency halts everything immediately
  if (emergencyActive) {
    // make sure outputs disabled
    stepper.disableOutputs();
    cutterServo.write(CUT_OPEN_ANGLE); // ensure cutter open
    // do nothing until user clears power/reset or sends another command
    return;
  }

  // If feeding, run stepper
  if (pieceFeeding && !emergencyActive) {
    stepper.run();

    // check if reached
    if (stepper.distanceToGo() == 0) {
      // compute actual moved (for info)
      long actualMoved = stepper.currentPosition() - pieceStartPosition;
      Serial.printf("Piece %d finished (actual steps %ld)\n", currentPiece, actualMoved);

      // perform cut
      performCut();

      pieceFeeding = false;

      // next piece or finish
      cyclesRemaining--;
      if (cyclesRemaining > 0) {
        currentPiece++;
        delay(120);
        beginPiece();
      } else {
        // finished job
        jobRunning = false;
        Serial.println("Job complete");
        stepper.disableOutputs();
      }
    }
  }
}

// ---------- Functions ----------

void beginPiece() {
  if (emergencyActive) return;
  stepsThisPiece = (long)round(requestedCm * STEPS_PER_CM);
  pieceStartPosition = stepper.currentPosition();
  stepper.move(stepsThisPiece);
  stepper.enableOutputs();
  pieceStartMs = millis();
  pieceFeeding = true;
  Serial.printf("Begin piece %d/%d : %d cm -> %ld steps\n", currentPiece, requestedQty, requestedCm, stepsThisPiece);
}

void performCut() {
  Serial.println("Cut: ramping servo to close...");
  // smooth ramp open->close->open
  int from = CUT_OPEN_ANGLE;
  int to = CUT_CLOSE_ANGLE;
  if (from < to) {
    for (int p = from; p <= to; p += 5) { cutterServo.write(p); delay(15); }
  } else {
    for (int p = from; p >= to; p -= 5) { cutterServo.write(p); delay(15); }
  }
  delay(CUT_HOLD_MS);
  // return
  if (from < to) {
    for (int p = to; p >= from; p -= 5) { cutterServo.write(p); delay(12); }
  } else {
    for (int p = to; p <= from; p += 5) { cutterServo.write(p); delay(12); }
  }
  Serial.println("Cut done, servo returned to open.");
}

// ----------------- Simple JSON helpers (no ArduinoJson) -----------------
// Extract a string value: looks for "key":"value"
String extractJsonString(const String &body, const String &key) {
  String needle = String("\"") + key + String("\"");
  int i = body.indexOf(needle);
  if (i < 0) return String();
  int colon = body.indexOf(':', i + needle.length());
  if (colon < 0) return String();
  int quote1 = body.indexOf('\"', colon);
  if (quote1 < 0) return String();
  int quote2 = body.indexOf('\"', quote1 + 1);
  if (quote2 < 0) return String();
  return body.substring(quote1 + 1, quote2);
}

// Extract an integer value: looks for "key":<number>
long extractJsonInt(const String &body, const String &key, long fallback=0) {
  String needle = String("\"") + key + String("\"");
  int i = body.indexOf(needle);
  if (i < 0) return fallback;
  int colon = body.indexOf(':', i + needle.length());
  if (colon < 0) return fallback;
  int j = colon + 1;
  // skip spaces
  while (j < body.length() && isSpace(body[j])) j++;
  // capture sign or digits
  int start = j;
  if (j < body.length() && (body[j] == '-' || body[j] == '+')) j++;
  while (j < body.length() && isDigit(body[j])) j++;
  if (j == start) return fallback;
  String num = body.substring(start, j);
  return num.toInt();
}

// Build a small JSON string from key-values (numbers/booleans)
String buildStatusJson(bool jobRun, int curPiece, int remaining, long stepsToGo, double pct, float stepsPerCm) {
  String s = "{";
  s += "\"jobRunning\":";
  s += (jobRun ? "true" : "false");
  s += ",\"currentPiece\":";
  s += String(curPiece);
  s += ",\"remaining\":";
  s += String(remaining);
  s += ",\"stepsToGo\":";
  s += String(stepsToGo);
  s += ",\"pct\":";
  s += String(pct,2);
  s += ",\"stepsPerCm\":";
  s += String(stepsPerCm,4);
  s += "}";
  return s;
}

// ---------- Web handlers (now use string helpers) ----------
void handleStatus() {
  long stepsToGo = pieceFeeding ? stepper.distanceToGo() : 0;
  double pct = 0.0;
  if (pieceFeeding && stepsThisPiece > 0) {
    long done = stepsThisPiece - stepsToGo;
    if (done < 0) done = 0;
    pct = ((double)done * 100.0) / (double)stepsThisPiece;
    if (pct < 0) pct = 0;
    if (pct > 100) pct = 100;
  }
  String out = buildStatusJson(jobRunning, currentPiece, cyclesRemaining, stepsToGo, pct, STEPS_PER_CM);
  server.send(200, "application/json", out);
}

void handleAction() {
  String body = server.arg("plain");
  body.trim();

  String cmd = extractJsonString(body, "cmd");
  if (cmd.length() == 0) {
    // maybe cmd provided as raw token (fallback)
    int pos = body.indexOf("cmd");
    if (pos < 0) {
      server.send(400, "application/json", "{\"ok\":false,\"error\":\"no cmd\"}");
      return;
    }
  }

  if (cmd == "start") {
    int cm = (int)extractJsonInt(body, "cm", 100);
    int qty = (int)extractJsonInt(body, "qty", 1);
    int speed_pct = (int)extractJsonInt(body, "speed_pct", 50);
    if (cm < 1) cm = 1;
    if (qty < 1) qty = 1;

    // prepare job
    requestedCm = cm;
    requestedQty = qty;
    cyclesRemaining = qty;
    currentPiece = 1;
    jobRunning = true;
    emergencyActive = false;

    // map speed
    float speed = ((float)constrain(speed_pct, 1, 100) / 100.0f) * MAX_FEED_SPEED_STEPS_PER_SEC;
    stepper.setMaxSpeed(speed);

    beginPiece();

    String resp = "{\"ok\":true,\"status\":\"started\",\"cm\":" + String(cm) + ",\"qty\":" + String(qty) + "}";
    server.send(200, "application/json", resp);
    return;
  } else if (cmd == "stop") {
    cyclesRemaining = 0;
    server.send(200, "application/json", "{\"ok\":true,\"status\":\"stop_requested\"}");
    return;
  } else if (cmd == "emergency") {
    emergencyActive = true;
    jobRunning = false;
    pieceFeeding = false;
    stepper.stop();
    stepper.disableOutputs();
    cutterServo.write(CUT_OPEN_ANGLE);
    server.send(200, "application/json", "{\"ok\":true,\"status\":\"emergency_on\"}");
    return;
  } else {
    server.send(400, "application/json", "{\"ok\":false,\"error\":\"unknown_cmd\"}");
    return;
  }
}
