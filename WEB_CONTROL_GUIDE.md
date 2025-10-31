# Web Control Guide
## ESP32 Cable Cutter - WiFi Access Point Interface

---

## 🌐 **Web-Based Control System**

This cable cutter uses a **WiFi Access Point** for control - no router needed!

**Key Features:**
- ✅ No WiFi network required - ESP32 creates its own
- ✅ Control from phone, tablet, or laptop
- ✅ Real-time progress monitoring
- ✅ Batch cutting with quantity support
- ✅ Adjustable speed control
- ✅ Emergency stop with confirmation

---

## 🚀 **Quick Start Guide**

### Step 1: Power On ESP32

1. Connect 12V power supply to L298N
2. ESP32 will automatically start
3. Wait ~5 seconds for WiFi AP to initialize

### Step 2: Connect to WiFi Access Point

**On your phone/tablet/laptop:**

1. Open WiFi settings
2. Look for network: **`CableFeeder`**
3. Connect to it (no password required)
4. Wait for connection confirmation

**WiFi Details:**
- **SSID:** `CableFeeder`
- **Password:** None (open network)
- **IP Address:** `192.168.4.1`

### Step 3: Open Web Interface

1. Open any web browser
2. Navigate to: **`http://192.168.4.1`**
3. Web interface will load instantly

**Bookmark it for quick access!**

---

## 🎮 **Using the Web Interface**

### Web Page Layout

```
┌─────────────────────────────────────┐
│     ESP32 Cable Feeder              │
├─────────────────────────────────────┤
│ Length (cm): [____200____]          │
│ Quantity:    [_____1_____]          │
│ Speed %:     [____50_____]          │
│                                     │
│ [Start] [Stop After Current] [🚨EM] │
├─────────────────────────────────────┤
│ Status Box:                         │
│ Job running: No                     │
│ Current piece: 0                    │
│ Remaining: 0                        │
│ Steps to go: 0                      │
│ Piece progress: 0%                  │
│ Cal steps/cm: 66.667                │
└─────────────────────────────────────┘
```

### Input Parameters

#### 1. **Length (cm)**
- Range: 1 - 2000 cm (20 meters)
- Default: 200 cm (2 meters)
- Enter desired cable length

#### 2. **Quantity**
- Range: 1 - 500 pieces
- Default: 1 piece
- Number of identical pieces to cut

#### 3. **Speed %**
- Range: 1 - 100%
- Default: 50%
- Motor speed (50% recommended for testing)

### Control Buttons

#### **Start Button**
- Begins cutting operation immediately
- Validates input parameters first
- Starts feeding first piece

#### **Stop After Current Button**
- Graceful stop: completes current piece
- Remaining pieces are cancelled
- Motor stops after cut completes

#### **Emergency Stop Button** 🚨
- **Requires confirmation!**
- Immediate halt (stops mid-operation)
- Motors disabled instantly
- Must restart ESP32 to resume

---

## 📊 **Real-Time Status Display**

The status box updates every 300ms (3 times per second):

### Status Fields

| Field | Description | Example |
|-------|-------------|---------|
| **Job running** | Yes/No | Yes |
| **Current piece** | Piece being cut | 3 |
| **Remaining** | Pieces left to cut | 7 |
| **Steps to go** | Steps left for current piece | 1234 |
| **Piece progress** | Completion percentage | 45% |
| **Cal steps/cm** | Calibration value | 66.667 |

---

## 💡 **Usage Examples**

### Example 1: Single Piece
1. Set Length: `100` cm
2. Set Quantity: `1`
3. Set Speed: `50`%
4. Click **Start**
5. Wait for cutting to complete
6. Remove cable piece

### Example 2: Batch of 10 Pieces
1. Set Length: `200` cm
2. Set Quantity: `10`
3. Set Speed: `60`%
4. Click **Start**
5. Monitor progress (shows 1/10, 2/10, etc.)
6. System automatically cuts all 10 pieces
7. Collect all pieces when done

### Example 3: Testing/Calibration
1. Set Length: `10` cm
2. Set Quantity: `1`
3. Set Speed: `30`% (slow for accuracy)
4. Click **Start**
5. Measure actual cut length
6. Adjust calibration if needed

---

## 🔧 **Troubleshooting**

### Cannot See "CableFeeder" WiFi Network

**Possible Causes:**
- ESP32 not powered properly
- Code not uploaded correctly
- WiFi interference

**Solutions:**
1. Check Serial Monitor (115200 baud)
   - Look for "AP started: CableFeeder"
   - Check IP address (should be 192.168.4.1)
2. Restart ESP32
3. Move closer to ESP32 (within 10 meters)
4. Check other devices can see the network

### Web Page Won't Load

**Solutions:**
1. Verify you're connected to "CableFeeder" WiFi
2. Try `http://192.168.4.1` (not https)
3. Clear browser cache
4. Try different browser (Chrome, Firefox, Safari)
5. Check Serial Monitor for errors

### Status Not Updating

**Solutions:**
1. Refresh web page (F5)
2. Check WiFi connection strength
3. Don't use multiple devices simultaneously
4. Check Serial Monitor for errors

### Motor Not Moving After Start

**Solutions:**
1. Check Serial Monitor for error messages
2. Verify L298N power supply (12V)
3. Check motor connections
4. Try lower speed (30-40%)
5. Test with short length first (10 cm)

### Cutting Wrong Length

**Solutions:**
1. Recalibrate STEPS_PER_CM
2. Check for cable slippage
3. Test at slower speed
4. Measure and adjust formula:
   ```
   new_steps_per_cm = current × (requested / actual)
   ```

---

## 🔐 **Security Notes**

### Current Setup: Open Network
- **No password** for easy access
- Anyone within WiFi range can connect
- Suitable for:
  - Personal workshop
  - Controlled environment
  - Testing/development

### Adding Password Protection (Optional)

If you want to secure your network, modify the code:

**In main.cpp, change line:**
```cpp
WiFi.softAP(AP_NAME);
```

**To:**
```cpp
WiFi.softAP(AP_NAME, "your_password_here");
```

**Example:**
```cpp
WiFi.softAP(AP_NAME, "CableCutter123");
```

Then re-upload the code.

---

## 📱 **Mobile Device Tips**

### iOS (iPhone/iPad)
1. Settings → Wi-Fi
2. Select "CableFeeder"
3. Dismiss "No Internet Connection" warning (this is normal)
4. Open Safari → http://192.168.4.1
5. Add to Home Screen for app-like experience

### Android
1. Settings → Wi-Fi
2. Select "CableFeeder"
3. Tap "Connect anyway" if warned about no internet
4. Open Chrome → http://192.168.4.1
5. Menu → Add to Home screen

### Windows Laptop
1. Click WiFi icon in taskbar
2. Connect to "CableFeeder"
3. Click "Connect anyway" if prompted
4. Open browser → http://192.168.4.1

### Mac
1. Click WiFi icon in menu bar
2. Select "CableFeeder"
3. Open Safari → http://192.168.4.1

---

## 🎯 **Best Practices**

### Before Starting Job
1. ✅ Verify cable is loaded properly
2. ✅ Check blade is in open position
3. ✅ Test with single piece first
4. ✅ Start with 50% speed
5. ✅ Monitor first few pieces

### During Operation
1. ✅ Watch status display for progress
2. ✅ Keep device connected to WiFi
3. ✅ Don't close browser tab
4. ✅ Use "Stop After Current" for graceful stop
5. ✅ Only use Emergency Stop if necessary

### After Operation
1. ✅ Let servo return to open position
2. ✅ Collect all cut pieces
3. ✅ Clear any cable remnants
4. ✅ Power off if done for the day

---

## 🌟 **Advanced Features**

### Monitoring from Serial Port

For detailed logs, connect via USB and open Serial Monitor:

**Baud Rate:** 115200

**Sample Output:**
```
Steps per cm = 66.6667
AP started: CableFeeder
AP IP: 192.168.4.1
HTTP server started
Begin piece 1/10 : 200 cm -> 13333 steps
Piece 1 finished (actual steps 13333)
Cut: ramping servo to close...
Cut done, servo returned to open.
Begin piece 2/10 : 200 cm -> 13333 steps
...
Job complete
```

### API Access (For Developers)

You can control the system programmatically:

**Get Status:**
```bash
curl http://192.168.4.1/status
```

**Start Job:**
```bash
curl -X POST http://192.168.4.1/action \
  -H "Content-Type: application/json" \
  -d '{"cmd":"start","cm":200,"qty":10,"speed_pct":50}'
```

**Stop:**
```bash
curl -X POST http://192.168.4.1/action \
  -H "Content-Type: application/json" \
  -d '{"cmd":"stop"}'
```

---

## 📖 **Related Documentation**

- **README.md** - Complete project overview
- **WIRING_DIAGRAM.md** - Hardware connections
- **UPLOAD_INSTRUCTIONS.md** - Firmware upload guide
- **QUICKSTART_WEB.md** - Quick reference card

---

## 💡 **Tips & Tricks**

1. **Save Settings:** Browser remembers your last inputs
2. **Bookmark Page:** Quick access from any device
3. **Test Mode:** Use 10cm length, 1 piece, 30% speed
4. **Monitor Progress:** Keep browser visible during operation
5. **WiFi Range:** Stay within 10-30 meters of ESP32
6. **Multiple Devices:** Only use one at a time
7. **Power Cycle:** Restart ESP32 if WiFi acts strange
8. **Calibration:** Write down calibration value after adjusting

---

**📱 Happy Cutting via WiFi! 📱**

*Last Updated: 2025*
