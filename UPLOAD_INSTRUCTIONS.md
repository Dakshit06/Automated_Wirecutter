# Upload Instructions# Quick Upload Guide - ESP32 Cable Cutter

## ESP32 Cable Cutter Firmware

## 🚀 Your ESP32 is connected on **COM7**

---

---

## 📋 **Prerequisites**

## ✅ **EASIEST METHOD: Arduino IDE**

### Hardware

- ✅ ESP32 Development Board### Step 1: Open Arduino IDE

- ✅ USB Cable (data cable, not charge-only)- If not installed, download from: https://www.arduino.cc/en/software

- ✅ Working USB port on computer

### Step 2: Install ESP32 Board Support

### Software1. Open Arduino IDE

Choose one:2. Go to **File** → **Preferences**

- **Option A:** PlatformIO (recommended, easier)3. In "Additional Board Manager URLs", paste:

- **Option B:** Arduino IDE (traditional)   ```

   https://dl.espressif.com/dl/package_esp32_index.json

---   ```

4. Click **OK**

## 🚀 **Method 1: PlatformIO (Recommended)**5. Go to **Tools** → **Board** → **Boards Manager**

6. Search for "**ESP32**"

### Step 1: Install PlatformIO7. Click **Install** on "ESP32 by Espressif Systems"

8. Wait for installation to complete

**If using VS Code:**

1. Open VS Code### Step 3: Install Required Libraries

2. Go to Extensions (Ctrl+Shift+X)1. Go to **Tools** → **Manage Libraries**

3. Search "PlatformIO"2. Search and install these libraries:

4. Click Install on "PlatformIO IDE"   - **ESP32Servo** by Kevin Harrington

5. Reload VS Code   - **LiquidCrystal I2C** by Frank de Brabander



**If using CLI:**### Step 4: Open Your Code

```powershell1. Go to **File** → **Open**

pip install platformio2. Navigate to: `C:\Users\daksh\OneDrive\Desktop\Wirecutter\`

```3. Select **cable_cutter.ino**

4. Click **Open**

### Step 2: Open Project

### Step 5: Configure Arduino IDE

1. Open VS Code1. **Select Board:**

2. File → Open Folder   - Go to **Tools** → **Board** → **ESP32 Arduino**

3. Select: `C:\Users\daksh\OneDrive\Desktop\Wirecutter`   - Select **ESP32 Dev Module**

4. PlatformIO will detect project automatically

2. **Select Port:**

### Step 3: Connect ESP32   - Go to **Tools** → **Port**

   - Select **COM7 (Silicon Labs CP210x USB to UART Bridge)**

1. Connect ESP32 to USB port

2. Wait for drivers to install3. **Optional Settings (for faster upload):**

3. Check Device Manager for COM port (e.g., COM7)   - Tools → Upload Speed → **921600**

   - Tools → Flash Frequency → **80MHz**

### Step 4: Upload Firmware

### Step 6: Upload Code

**Using PlatformIO Toolbar:**1. Click the **Upload** button (→ arrow icon) in the toolbar

1. Look for PlatformIO icon in sidebar2. Wait for compilation (1-2 minutes first time)

2. Click "Upload" button (→)3. Watch for "Connecting..." message

3. Wait for compilation and upload4. If it says "Connecting..." for more than 10 seconds, press the **BOOT** button on your ESP32

5. Wait for upload to complete

**Using Terminal:**6. You should see "**Hard resetting via RTS pin...**" when done

```powershell

# Upload### Step 7: Monitor Output

pio run --target upload1. Click **Tools** → **Serial Monitor**

2. Set baud rate to **115200** (bottom right)

# Upload and monitor3. You should see: "Automated Cable Cutting System Initializing..."

pio run --target upload && pio device monitor

```---



**Expected Output:**## 🔧 **ALTERNATIVE: VS Code with Arduino Extension**

```

...If you prefer VS Code:

Linking .pio\build\esp32dev\firmware.elf

Building .pio\build\esp32dev\firmware.bin1. Install "Arduino" extension by Microsoft

Creating esp32 image...2. Press **Ctrl+Shift+P**

Successfully created esp32 image3. Type: "Arduino: Board Config"

Uploading .pio\build\esp32dev\firmware.bin4. Select: ESP32 Dev Module

esptool.py v3.35. Press **Ctrl+Shift+P** again

...6. Type: "Arduino: Upload"

Hard resetting via RTS pin...

========================= [SUCCESS] Took X.XX seconds =========================---

```

## 🐛 **Troubleshooting**

---

### Error: "Failed to connect"

## 🔨 **Method 2: Arduino IDE****Solution:** Press and hold the **BOOT** button on ESP32 when you see "Connecting..."



### Step 1: Install Arduino IDE### Error: "Port COM7 busy"

**Solution:** 

1. Download from: https://www.arduino.cc/en/software- Close any serial monitors

2. Install (accept defaults)- Unplug and replug the ESP32

3. Launch Arduino IDE- Try again



### Step 2: Add ESP32 Board Support### Error: "No board selected"

**Solution:** Make sure you selected ESP32 Dev Module under Tools → Board

1. File → Preferences

2. In "Additional Board Manager URLs", add:### Error: "Library not found"

   ```**Solution:** Install the libraries (ESP32Servo and LiquidCrystal_I2C)

   https://dl.espressif.com/dl/package_esp32_index.json

   ```---

3. Click OK

4. Tools → Board → Boards Manager## 📝 **Quick Test After Upload**

5. Search "ESP32"

6. Install "ESP32 by Espressif Systems"1. Open Serial Monitor (115200 baud)

7. Wait for installation (can take 5-10 minutes)2. You should see initialization messages

3. The LCD (if connected) will show "Cable Cutter"

### Step 3: Install Required Libraries4. Use the rotary encoder to set length

5. Press START button to begin operation

1. Tools → Manage Libraries (Ctrl+Shift+I)

2. Search and install each:---



   **Library 1: AccelStepper**## 🔌 **Hardware Connections Required**

   - Search: "AccelStepper"

   - Install: "AccelStepper by Mike McCauley"Before testing, ensure you have connected:

   

   **Library 2: ESP32Servo**### L298N Stepper Driver:

   - Search: "ESP32Servo"- IN1 → GPIO 14

   - Install: "ESP32Servo by Kevin Harrington"- IN2 → GPIO 27

- IN3 → GPIO 26

### Step 4: Open Code- IN4 → GPIO 25



**Important:** Arduino IDE works with `.ino` files, but we have `.cpp`### MG996R Servo:

- Signal (Orange) → GPIO 18

**Option A: Copy main.cpp content**- VCC (Red) → 5V external supply

1. Create new sketch: File → New- GND (Brown) → Common GND

2. Open: `Wirecutter\src\main.cpp`

3. Copy all contents### LCD Display (I2C):

4. Paste into new sketch- SDA → GPIO 21

5. Save as: `cable_cutter_web.ino`- SCL → GPIO 22

- VCC → 5V

**Option B: Use existing structure**- GND → GND

If you have `cable_cutter.ino` file:

1. File → Open### Buttons & Encoder:

2. Select: `Wirecutter\cable_cutter.ino`- START → GPIO 15 + GND

- STOP → GPIO 4 + GND

### Step 5: Configure Board- RESET → GPIO 2 + GND

- Encoder CLK → GPIO 32

1. **Select Board:**- Encoder DT → GPIO 33

   - Tools → Board → ESP32 Arduino- Encoder SW → GPIO 34

   - Select: **ESP32 Dev Module**

---

2. **Select Port:**

   - Tools → Port## ✨ **Status:**

   - Select your COM port (e.g., COM7)- ✅ Code tested and verified

- ✅ ESP32 detected on COM7

3. **Optional Settings:**- ✅ All files ready

   - Tools → Upload Speed → 921600- 📱 Ready to upload via Arduino IDE

   - Tools → CPU Frequency → 240MHz

   - Tools → Flash Frequency → 80MHz**Note:** The simulation we just ran confirmed the logic works perfectly. Now you just need to upload to hardware!

   - Tools → Flash Mode → QIO
   - Tools → Flash Size → 4MB
   - Tools → Partition Scheme → Default 4MB

### Step 6: Upload

1. Click **Upload** button (→) or press Ctrl+U
2. Wait for compilation (first time is slow)
3. Watch for upload progress
4. Wait for "Done uploading" message

**Expected Output in console:**
```
Sketch uses XXXXX bytes (XX%) of program storage space.
Global variables use XXXXX bytes (XX%) of dynamic memory.

esptool.py v3.3
...
Writing at 0x00010000... (100 %)
Wrote XXXXXX bytes (XXXXXX compressed) at 0x00010000...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
```

---

## 🔍 **Verify Upload Success**

### Check Serial Monitor

**PlatformIO:**
```powershell
pio device monitor
```

**Arduino IDE:**
1. Tools → Serial Monitor
2. Set baud rate: 115200
3. Set line ending: Newline

**Expected Output:**
```
Steps per cm = 66.6667
AP started: CableFeeder
AP IP: 192.168.4.1
HTTP server started
```

✅ **If you see this, upload was successful!**

---

## 🐛 **Troubleshooting**

### "Port Busy" Error

**Solution:**
1. Close Serial Monitor
2. Close other programs using serial port
3. Unplug and replug USB cable
4. Try upload again

### "Failed to Connect" Error

**Solution 1: Hold BOOT button**
1. Unplug ESP32
2. Hold BOOT button on ESP32
3. Plug in USB while holding
4. Start upload
5. Release BOOT when "Connecting..." appears

**Solution 2: Check drivers**
1. Open Device Manager
2. Look for "Silicon Labs" or "CH340" under Ports
3. If missing, install drivers:
   - CP210x: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
   - CH340: http://www.wch.cn/downloads/CH341SER_ZIP.html

**Solution 3: Try different USB port**
- Use USB 2.0 port (not USB 3.0)
- Try rear panel ports (not front)
- Avoid USB hubs

### "Cannot Open Serial Port" Error

**Solution:**
```powershell
# Check which ports are available
pio device list

# Or in PowerShell
Get-WmiObject Win32_PnPEntity | Where-Object {$_.Name -match "COM\d+"} | Select Name, DeviceID
```

### Compilation Errors

**Missing AccelStepper library:**
```
Error: AccelStepper.h: No such file or directory
```
**Fix:** Install AccelStepper library

**Missing ESP32Servo library:**
```
Error: ESP32Servo.h: No such file or directory
```
**Fix:** Install ESP32Servo library

**WiFi.h not found:**
```
Error: WiFi.h: No such file or directory
```
**Fix:** Ensure ESP32 board support is installed

---

## ⚙️ **platformio.ini Configuration**

Your `platformio.ini` should contain:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

upload_speed = 921600
monitor_speed = 115200

lib_deps = 
    waspinator/AccelStepper@^1.64
    madhephaestus/ESP32Servo@^0.13.0
```

---

## 📝 **Post-Upload Steps**

### 1. Test WiFi Access Point

1. Disconnect USB (or leave connected for power)
2. Wait 5 seconds
3. Check WiFi networks on phone/laptop
4. Look for "CableFeeder"

### 2. Test Web Interface

1. Connect to "CableFeeder" WiFi
2. Open browser
3. Go to: http://192.168.4.1
4. Verify page loads

### 3. Test Motor Control

1. Set Length: 10 cm
2. Set Quantity: 1
3. Set Speed: 30%
4. Click Start
5. Verify motor moves

---

## 🔄 **Updating Firmware**

To update code:

1. Edit `src/main.cpp`
2. Save changes
3. Reconnect USB if disconnected
4. Upload again using same method
5. Serial Monitor will show restart

**Calibration persists:** Your STEPS_PER_CM calibration is saved in ESP32's Preferences and will survive firmware updates!

---

## 💾 **Backup Your Calibration**

Before uploading new firmware, note your calibration:

**Check Serial Monitor:**
```
Steps per cm = 66.6667  ← Write this down!
```

Or check web status page:
```
Cal steps/cm: 66.667
```

---

## 🎯 **Quick Reference**

### PlatformIO Commands
```powershell
# Build only
pio run

# Upload firmware
pio run --target upload

# Monitor serial
pio device monitor

# Upload and monitor
pio run --target upload && pio device monitor

# Clean build
pio run --target clean

# List connected devices
pio device list
```

### Arduino IDE Shortcuts
- **Verify:** Ctrl+R
- **Upload:** Ctrl+U
- **Serial Monitor:** Ctrl+Shift+M
- **New:** Ctrl+N
- **Open:** Ctrl+O
- **Save:** Ctrl+S

---

## 🆘 **Still Having Issues?**

1. **Check USB cable:** Use a data cable (not charge-only)
2. **Try different port:** USB 2.0 preferred
3. **Update drivers:** CP210x or CH340
4. **Check board selection:** ESP32 Dev Module
5. **Verify baud rate:** 115200 for Serial Monitor
6. **Power cycle:** Unplug ESP32, wait 5 sec, replug
7. **Check Serial Monitor:** Look for error messages

---

## 📚 **Related Documentation**

- **README.md** - Complete project overview
- **QUICKSTART_WEB.md** - Fast setup guide
- **WEB_CONTROL_GUIDE.md** - Web interface usage
- **WIRING_DIAGRAM.md** - Hardware connections

---

**✅ Upload Complete! Now connect to WiFi and start cutting! ✅**

*For support, check Serial Monitor output at 115200 baud*
