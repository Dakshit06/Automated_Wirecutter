# Wiring Diagram & Circuit Connections
## ESP32 Cable Cutter - Web-Based System

---

## 🔌 Complete Wiring Guide

### Power Distribution

```
12V Power Supply
├── L298N Motor Driver (12V input)
│   └── 5V Output → ESP32 VIN (optional)
│
└── 5V Regulator (if not using L298N 5V out)
    ├── ESP32 (5V or 3.3V)
    └── Servo Motor (5-6V)

Ground Common (CRITICAL!)
├── ESP32 GND
├── L298N GND
├── Servo GND
└── 12V Power Supply GND
```

**⚠️ Important:** All components MUST share a common ground!

---

## 📋 Component-by-Component Connections

### 1. L298N Motor Driver to ESP32

#### L298N Connection Table
| L298N Terminal | Connect To | Wire Color Suggestion | Notes |
|----------------|------------|----------------------|-------|
| IN1 | ESP32 GPIO 14 | Yellow | Stepper coil 1A |
| IN2 | ESP32 GPIO 27 | Orange | Stepper coil 1B |
| IN3 | ESP32 GPIO 26 | Green | Stepper coil 2A |
| IN4 | ESP32 GPIO 25 | Blue | Stepper coil 2B |
| 12V | 12V Power Supply + | Red | Motor power input |
| GND | Common Ground | Black | Ground reference |
| 5V Out | ESP32 VIN (optional) | Red | Can power ESP32 |

#### Stepper Motor to L298N
| Stepper Wire | L298N Terminal | Coil | Notes |
|--------------|----------------|------|-------|
| Coil A Wire 1 | OUT1 | Coil A+ | Usually Red |
| Coil A Wire 2 | OUT2 | Coil A- | Usually Green |
| Coil B Wire 1 | OUT3 | Coil B+ | Usually Blue |
| Coil B Wire 2 | OUT4 | Coil B- | Usually Black |

**Troubleshooting Motor Behavior:**
- If motor doesn't move: Check power supply and connections
- If motor vibrates but doesn't rotate: Swap one coil pair
- If motor rotates opposite: Reverse both coils or change direction in code
- Test with multimeter: Coil pairs should have continuity (~1-5Ω)

---

### 2. MG996R Servo Motor

#### Servo Connection Table
| Servo Wire | Color | Connect To | Voltage |
|------------|-------|------------|---------|
| Signal | Orange/Yellow | ESP32 GPIO 18 | 3.3V/5V logic |
| VCC (Power) | Red | 5-6V Power Supply | 5-6V, 2A min |
| GND | Brown/Black | Common Ground | 0V |

**⚠️ Critical Servo Notes:**
- **DO NOT** power servo from ESP32 pins (draws too much current)
- Use dedicated 5V/6V power supply (2A minimum recommended)
- Add 470-1000µF capacitor across servo VCC/GND (close to servo)
- Use thick wires (20-22 AWG) for servo power lines
- Servo signal wire can connect directly to GPIO 18 (3.3V safe)

**Capacitor Placement:**
```
5V ──┬─── Servo VCC (Red)
     │
    === 1000µF Capacitor (+ side to 5V)
     │
GND ─┴─── Servo GND (Brown)
```

---

### 3. Complete System - Simplified (No LCD/Encoder/Buttons)

**This web-based version only needs:**
- ESP32
- L298N + Stepper Motor
- Servo Motor
- Power Supply (12V for motors, 5V for logic)

**No longer needed:**
- ❌ LCD Display
- ❌ Rotary Encoder  
- ❌ Physical Buttons

All control is via web interface!

---

## 🔧 Complete ESP32 Pinout Summary (Simplified)

### Digital Output Pins
| GPIO | Function | Component | Signal Type |
|------|----------|-----------|-------------|
| 14 | Stepper IN1 | L298N | Digital Out |
| 27 | Stepper IN2 | L298N | Digital Out |
| 26 | Stepper IN3 | L298N | Digital Out |
| 25 | Stepper IN4 | L298N | Digital Out |
| 18 | Servo Signal | MG996R | PWM (50Hz) |

### Power Pins
| Pin | Function | Voltage | Notes |
|-----|----------|---------|-------|
| VIN/5V | Power Input | 5V | From L298N 5V out or USB |
| 3.3V | Logic Power | 3.3V | Can power small sensors |
| GND | Ground | 0V | Must be common with all |

**Total Pin Usage: Only 5 GPIO pins!**

---

## ⚡ Power Supply Requirements

### Power Distribution Diagram

```
Main 12V Power Supply (2-3A recommended)
│
├─→ L298N Motor Driver (12V input)
│   ├─→ Stepper Motor (via OUT1-OUT4)
│   └─→ 5V Output (can power ESP32)
│
├─→ 5V Power Source (2A minimum)
│   ├─→ ESP32 (500mA max)
│   └─→ MG996R Servo Motor (up to 2A peak)
│
└─→ Common Ground (MUST be connected!)
```

### Component Power Consumption
| Component | Voltage | Typical Current | Peak Current | Notes |
|-----------|---------|----------------|--------------|-------|
| ESP32 | 5V | 150-250mA | 500mA | WiFi on |
| Stepper Motor | 12V | 400mA | 1.2A | Per coil |
| Servo Motor | 5-6V | 100mA idle | 2A peak | During cutting |

**Total Power Budget:**
- 12V @ 2-3A for stepper motor
- 5V @ 2.5-3A for ESP32 + servo
| NEMA 17 (running) | 12V | 1.2A | 14.4W |
| MG996R Servo | 5V | 2A (peak) | 10W |
| LCD Display | 5V | 50mA | 0.25W |
| **Total (max)** | - | - | **~27W** |

**Recommended Power Supply**: 12V 3A (36W) for safety margin

---

## 🛠️ Assembly Instructions

### Step-by-Step Wiring

1. **Prepare Workspace**
   - Clear, well-lit area
   - Organize components
   - Label all wires

2. **Power Distribution First**
   ```
   - Connect 12V supply to power distribution board
   - Install 5V buck converter (12V → 5V)
   - Create common ground bus
   - Test voltages before connecting components
   ```

3. **Connect ESP32**
   ```
   - Mount ESP32 on breadboard/PCB
   - Connect 5V and GND
   - Verify power LED illuminates
   ```

4. **Wire L298N Driver**
   ```
   - Connect IN1-IN4 to ESP32 GPIOs (14, 27, 26, 25)
   - Connect 12V power to L298N
   - Connect GND to common ground
   - Ensure enable jumpers are in place
   ```

5. **Connect NEMA 17**
   ```
   - Identify coil pairs (measure resistance)
   - Connect to L298N OUT1-OUT4
   - Secure motor to mounting bracket
   - Attach feed wheel to motor shaft
   ```

6. **Wire Servo Motor**
   ```
   - Connect signal wire to GPIO 18
   - Connect power to separate 5V supply (2A minimum)
   - Connect GND to common ground
   - Mount servo to cutting mechanism frame
   ```

7. **Install LCD Display**
   ```
   - Connect VCC to 5V
   - Connect GND to ground
   - Connect SDA to GPIO 21
   - Connect SCL to GPIO 22
   - Mount display in visible location
   ```

8. **Add Rotary Encoder**
   ```
   - Connect CLK to GPIO 32
   - Connect DT to GPIO 33
   - Connect SW to GPIO 34
   - Connect + to 3.3V
   - Connect GND to ground
   ```

9. **Install Control Buttons**
   ```
   - START button: GPIO 15 to GND
   - STOP button: GPIO 4 to GND
   - RESET button: GPIO 2 to GND
   - Mount on control panel
   ```

10. **Final Checks**
    ```
    - Verify all connections with multimeter
    - Check for short circuits
    - Ensure proper polarity
    - Test continuity on all grounds
    - Double-check power supply voltages
    ```

---

## 🔍 Troubleshooting Connections

### Visual Inspection Checklist
- [ ] All wires securely connected
- [ ] No exposed wire causing shorts
- [ ] Power supply polarity correct
- [ ] Ground connections solid
- [ ] GPIO pins match code configuration
- [ ] Servo has separate power supply
- [ ] Motor coils connected properly

### Testing Individual Components

**Test ESP32**:
```cpp
void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Test OK");
}
```

**Test L298N & Stepper**:
```cpp
// Run calibrateSystem() function in main code
// Should complete one rotation
```

**Test Servo**:
```cpp
cutterServo.attach(18);
cutterServo.write(90);  // Should move to 90°
```

**Test LCD**:
```cpp
lcd.init();
lcd.backlight();
lcd.print("Test OK");
```

**Test Encoder**:
- Rotate encoder, watch serial monitor for value changes

**Test Buttons**:
- Press each button, verify serial output or LED response

---

## 📐 Mechanical Assembly Notes

### Feed Mechanism
```
[NEMA 17 Motor]
        |
   [Drive Wheel] ← 50mm diameter, rubber coated
        |
   [Cable Path] ← 10mm cable
        |
[Pressure Wheel] ← Spring loaded
```

### Cutting Assembly
```
[Servo Motor]
      |
 [Linkage Arm]
      |
 [Blade Holder]
      |
  [Cutting Blade] ← Hardened steel
```

---

## 🎨 Wiring Best Practices

1. **Color Coding**:
   - Red: Positive power
   - Black: Ground
   - Yellow/White: Signal lines
   - Green/Blue: I2C/Communication

2. **Wire Gauge**:
   - Power (12V): 18-20 AWG
   - Motor connections: 20-22 AWG
   - Signal wires: 22-26 AWG

3. **Wire Management**:
   - Use cable ties
   - Separate power and signal wires
   - Label all connections
   - Allow strain relief

4. **Soldering**:
   - Use heat shrink tubing
   - Secure all solder joints
   - Test continuity after soldering

5. **Connectors**:
   - Use JST connectors for removable connections
   - Screw terminals for power
   - Dupont connectors for prototyping

---

## 🚨 Safety Warnings

⚠️ **ELECTRICAL SAFETY**
- Disconnect power before wiring
- Check polarity before powering on
- Use fuses on power supply
- Keep liquids away from electronics

⚠️ **MECHANICAL SAFETY**
- Cutting blade is sharp - handle carefully
- Add emergency stop button
- Use safety guards around cutting area
- Test at low speed first

⚠️ **COMPONENT PROTECTION**
- Don't exceed voltage ratings
- Ensure proper current capacity
- Add flyback diodes for motors
- Use capacitors for power filtering

---

## 📊 Circuit Diagram Legend

```
Symbol Meanings:
─────  Wire connection
┴      Ground
─┤├─   Capacitor
─/\/\─ Resistor
─>─    Diode
[M]    Motor
[S]    Switch/Button
MCU    Microcontroller
```

---

## 🔗 Additional Resources

- **ESP32 Pinout**: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
- **L298N Guide**: https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/
- **Servo Control**: https://www.arduino.cc/reference/en/libraries/servo/
- **I2C LCD**: https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/

---

**Document Version**: 1.0  
**Last Updated**: October 21, 2025  
**Status**: Ready for assembly and testing
