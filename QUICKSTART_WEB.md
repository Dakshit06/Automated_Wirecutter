# 🚀 Quick Start Guide# 🚀 Quick Start - Web-Enabled Cable Cutter

## ESP32 Cable Cutter - Web Control Edition

## 📝 **BEFORE UPLOADING - IMPORTANT!**

---

### 1. Edit WiFi Credentials (Line 33-34)

## ⚡ **Super Quick Start (3 Steps)**Open `cable_cutter.ino` and change:



### 1️⃣ Upload Code```cpp

```powershellconst char* ssid = "YOUR_WIFI_SSID";        // ← Your WiFi name here

# In VS Code terminal or PowerShellconst char* password = "YOUR_WIFI_PASSWORD"; // ← Your WiFi password here

pio run --target upload```

```

**Example:**

### 2️⃣ Connect to WiFi```cpp

- Look for WiFi network: **`CableFeeder`**const char* ssid = "MyHome WiFi";

- Connect (no password)const char* password = "password123";

```

### 3️⃣ Open Web Interface

- Browser → **`http://192.168.4.1`**---

- Start cutting!

## 📤 **Upload to ESP32**

---

### Method 1: Arduino IDE (Easiest)

## 📋 **Complete Setup**1. Open Arduino IDE

2. File → Open → `cable_cutter.ino`

### Hardware Checklist3. Tools → Board → ESP32 Dev Module

- ✅ ESP32 connected to L298N (GPIO 14,27,26,25)4. Tools → Port → COM7

- ✅ Servo connected to GPIO 185. Click Upload ⬆️

- ✅ 12V power to L298N

- ✅ Common ground between all components### Method 2: VS Code Terminal

- ✅ USB cable for programming```powershell

C:/Users/daksh/AppData/Local/Microsoft/WindowsApps/python3.11.exe -m platformio run --target upload --upload-port COM7

### Software Requirements```

- ✅ PlatformIO installed (or Arduino IDE)

- ✅ Code uploaded to ESP32---

- ✅ Serial Monitor shows "AP started"

## 🌐 **Access Web Interface**

---

1. **After upload**, open Serial Monitor (115200 baud)

## 🔌 **Upload Methods**2. Wait for: `IP Address: 192.168.x.xxx`

3. **Open browser** on phone/computer

### Method 1: PlatformIO (Recommended)4. Go to: `http://192.168.x.xxx` (use YOUR IP)

```powershell5. **You'll see beautiful control panel!**

# Upload firmware

pio run --target upload---



# Monitor serial output## 🎮 **Control Options**

pio device monitor

```### Option 1: Web Browser 🌐

- Set length via web form

### Method 2: Arduino IDE- Click START/STOP buttons

1. Install ESP32 board support- Real-time progress monitoring

2. Install libraries:- Works on phone, tablet, PC

   - AccelStepper (by Mike McCauley)

   - ESP32Servo (by Kevin Harrington)### Option 2: Physical Buttons 🔘

3. Select: Tools → Board → ESP32 Dev Module- Rotary encoder: Set length

4. Select: Tools → Port → COM7 (your port)- START button: Begin operation

5. Click Upload- STOP button: Emergency stop

- RESET button: Reset system

---

### Option 3: API Calls 💻

## 🌐 **Access Web Interface**```

http://192.168.x.xxx/setLength?value=5000

### Connect to WiFi Access Pointhttp://192.168.x.xxx/start

http://192.168.x.xxx/stop

**On Phone/Tablet:**http://192.168.x.xxx/status

1. Settings → WiFi```

2. Select "CableFeeder"

3. Connect (ignore "no internet" warning)---



**On Computer:**## ✅ **Features**

1. WiFi icon → Select "CableFeeder"

2. Connect✨ **Web Interface**

- Beautiful responsive design

### Open Control Panel- Real-time status updates

- Progress bar visualization

**URL:** `http://192.168.4.1`- Mobile-friendly



**Works on:**🔧 **Control**

- ✅ Chrome- Set length: 2000-10000mm

- ✅ Firefox- START/STOP operations

- ✅ Safari- System reset

- ✅ Edge- Motor calibration

- ✅ Any mobile browser

📊 **Monitoring**

---- Live length tracking

- Progress percentage

## 🎮 **Using the Interface**- System state display

- Auto-refresh (1 sec)

### Set Parameters

```🔒 **Safety**

Length (cm):  [___200___]  ← Cable length (1-2000)- Physical emergency stop

Quantity:     [____10____]  ← Number of pieces (1-500)- Web emergency stop

Speed %:      [____50____]  ← Motor speed (1-100)- Length validation

```- State management



### Click Start---

- Motor begins feeding

- Watch real-time progress## 🐛 **Troubleshooting**

- Automatic cutting after each piece

### WiFi Not Connecting?

### Monitor Status- Check SSID and password (case-sensitive!)

```- Ensure 2.4GHz WiFi (ESP32 doesn't support 5GHz)

Job running:   Yes- Move ESP32 closer to router

Current piece: 3

Remaining:     7### Can't Access Web Page?

Steps to go:   1234- Use IP address from Serial Monitor

Piece progress: 45%- Include `http://` (not https)

Cal steps/cm:  66.667- Ensure same WiFi network

```- Try `ping 192.168.x.xxx`



---### Upload Failing?

- Press BOOT button when "Connecting..."

## 🔧 **First Time Setup**- Check COM port (COM7)

- Close other serial monitors

### Test Run- Unplug/replug ESP32

1. Set length: **10 cm**

2. Set quantity: **1**---

3. Set speed: **30%** (slow for testing)

4. Click **Start**## 📱 **Add to Phone Home Screen**

5. Watch operation

6. Verify cut length**iPhone:**

1. Open web interface in Safari

### Calibration2. Tap Share → Add to Home Screen

If cut length is incorrect:3. Works like an app!



1. Measure actual length**Android:**

2. Calculate new calibration:1. Open in Chrome

   ```2. Menu → Add to Home screen

   new_steps_per_cm = 66.67 × (requested / actual)3. Access from app drawer!

   ```

3. Update in code:---

   ```cpp

   float STEPS_PER_CM = <your_value>;## 🎯 **Quick Test**

   ```

4. Re-upload firmware1. Upload code with WiFi credentials

2. Open Serial Monitor → note IP address

**Example:**3. Open browser → `http://YOUR_IP`

- Requested: 10 cm4. Set length to 2000mm

- Actual: 9.5 cm5. Click START

- New value: 66.67 × (10 / 9.5) = **70.18**6. Watch progress in real-time!

7. Click STOP anytime

---8. Click RESET for next cut



## 🐛 **Troubleshooting**---



### Can't See WiFi Network## 📞 **Need Help?**

```

✅ Check Serial Monitor for "AP started"Check these files:

✅ ESP32 powered correctly?- `WEB_CONTROL_GUIDE.md` - Full web interface documentation

✅ Wait 5-10 seconds after power on- `README.md` - Complete system documentation

✅ Try restarting ESP32- `WIRING_DIAGRAM.md` - Hardware connections

```- `UPLOAD_INSTRUCTIONS.md` - Upload help



### Web Page Won't Load---

```

✅ Connected to "CableFeeder"?**Your cable cutter is now WiFi-enabled! Control it from anywhere on your network! 🎉**

✅ Using http:// (not https://)?
✅ Correct IP: 192.168.4.1?
✅ Try clearing browser cache
```

### Motor Not Moving
```
✅ Check Serial Monitor for errors
✅ 12V power connected to L298N?
✅ Motor connections correct?
✅ Try lower speed (30%)
```

### Wrong Length
```
✅ Recalibrate STEPS_PER_CM
✅ Check for cable slippage
✅ Test with slower speed
✅ Verify stepper motor wiring
```

---

## 📱 **Mobile Quick Reference**

### iOS
1. Settings → Wi-Fi → "CableFeeder"
2. Safari → `192.168.4.1`
3. Add to Home Screen (optional)

### Android
1. Settings → Wi-Fi → "CableFeeder"
2. Chrome → `192.168.4.1`
3. Menu → Add to Home screen (optional)

---

## ⚙️ **Serial Monitor Commands**

**Baud Rate:** 115200

**Expected Output:**
```
Steps per cm = 66.6667
AP started: CableFeeder
AP IP: 192.168.4.1
HTTP server started

[When job starts]
Begin piece 1/10 : 200 cm -> 13333 steps
Piece 1 finished (actual steps 13333)
Cut: ramping servo to close...
Cut done, servo returned to open.
Job complete
```

---

## 🎯 **Quick Tips**

1. **Bookmark** http://192.168.4.1 on your device
2. **Test first** with small length (10 cm)
3. **Start slow** (30-50% speed)
4. **Stay connected** to WiFi during operation
5. **Use Emergency Stop** only if necessary
6. **Monitor Serial** for detailed logs

---

## 📊 **Default Values**

| Parameter | Default Value |
|-----------|--------------|
| WiFi SSID | CableFeeder |
| WiFi Password | None (open) |
| IP Address | 192.168.4.1 |
| Web Port | 80 |
| Calibration | 66.67 steps/cm |
| Max Speed | 800 steps/sec |
| Servo Open | 0° |
| Servo Close | 130° |

---

## 🚨 **Safety**

- ⚠️ Keep hands away from cutting area
- ⚠️ Use emergency stop if anything goes wrong
- ⚠️ Monitor first few pieces closely
- ⚠️ Don't power off mid-operation
- ⚠️ Disconnect power before maintenance

---

## 📚 **Next Steps**

- Read **WEB_CONTROL_GUIDE.md** for detailed usage
- Check **WIRING_DIAGRAM.md** for connections
- Review **README.md** for complete documentation
- Calibrate system for your specific setup
- Test with different speeds and lengths

---

**🎉 You're Ready to Cut! 🎉**

*Quick Reference Card - Keep this handy!*
