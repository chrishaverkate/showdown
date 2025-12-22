 
# Parts
## OpAmp
* [LM2904 OpAmp](docs/external/op-amp%20-%20lm2904b.pdf)
* [LM393 comparator](docs/external/lm393.pdf)

## Piezo Element
Several options to explore:
* [Piezo Vibration Sensor - Large with Mass](https://www.sparkfun.com/piezo-vibration-sensor-large-with-mass.html)
* [Piezo Vibration Sensor - Large](https://www.sparkfun.com/piezo-vibration-sensor-large.html)
* [Piezo Vibration Sensor - Small Vertical](https://www.sparkfun.com/piezo-vibration-sensor-small-vertical.html)
* [Piezo Vibration Sensor - Small Horizontal](https://www.sparkfun.com/piezo-vibration-sensor-small-horizontal.html)
* [Mini Speaker 12mm 2.048kHz](https://www.sparkfun.com/mini-speaker-pc-mount-12mm-2-048khz.html)
* [Piezo Element](https://www.sparkfun.com/piezo-element.html#content-documentation)


# Design

## Digitally Controlled Shot Sensing
All GPIO pins on the Pico can output PWM.
If you run PWM at a high frequency and pass it through a low-pass RC filter, you get a stable analog voltage.

Typical RC filter example:
* R = 10kΩ
* C = 1µF

Gives ~16 Hz cutoff → smooth stable DC output

```python
from machine import Pin, PWM
import time

pwm = PWM(Pin(15))   # any PWM-capable pin
pwm.freq(50000)      # high frequency to help filtering

def set_voltage(v):
    # v is desired voltage 0.0–3.3
    duty = int(v / 3.3 * 65535)
    pwm.duty_u16(duty)

while True:
    set_voltage(1.65)  # output ~1.65V
    time.sleep(1)

```

## LM393 Comparator Description
### Core idea
Use a comparator (e.g. LM393) and make its reference voltage adjustable with a potentiometer.

### Circuit sketch
* Piezo + front end (same as before):
  * Piezo → node SENSE
  * Other piezo lead → GND
  * 1 MΩ from SENSE to GND
  * Clamp diodes:
    * 1N4148 from SENSE to 5 V (anode at SENSE, cathode at 5 V)
    * 1N4148 from GND to SENSE (anode at GND, cathode at SENSE)
  * Optional: 10–100 nF from SENSE to GND (smooth the spikes)

Comparator:
* LM393 power: VCC = 5 V, GND = GND
  * + input → SENSE (the piezo signal)
  * – input → VREF (threshold from pot)
  *Output → 10 kΩ pull-up to 5 V → Arduino digital pin
* Sensitivity pot (the knob):
  * Use a 10 kΩ or 50 kΩ pot
  * One end of pot → 5 V
  * Other end of pot → GND
  * Wiper (middle pin) → VREF (the comparator – input)

Now, turning the pot moves VREF between 0 and 5 V:
* Lower VREF → smaller piezo spike needed → more sensitive
* Higher VREF → stronger vibration needed → less sensitive

If you want to “invert” that feel (turn clockwise for more sensitive), just swap which end of the pot goes to 5 V and GND.

## LM2904 OpAmp Description
## Key Points About the LM2904
- Runs happily from a **single 5 V supply**.
- Inputs work from **GND up to about VCC – 1.5 V**
  - (With 5 V supply → usable input range up to ~3.5 V.)
- Output is **not rail-to-rail**; with 5 V the HIGH level will be **~3–4 V**,  
  which is still a valid HIGH for an Arduino digital input.

We use **one half** of the LM2904 as a simple comparator:

- **Non-inverting (+) input** = piezo signal
- **Inverting (–) input** = adjustable threshold (from potentiometer)

## Schematic (Text Description)

### Supply
- **LM2904 VCC → +5 V (Arduino 5 V)**
- **LM2904 GND → GND**

## Piezo Front End
- Piezo lead 1 → `SENSE`
- Piezo lead 2 → GND

**Conditioning components:**
- **1 MΩ resistor** from `SENSE` → GND (bias/discharge)
- **Clamp diodes:**
  - 1× 1N4148 from `SENSE` → 5 V (anode at SENSE, cathode at 5 V)
  - 1× 1N4148 from GND → `SENSE` (anode at GND, cathode at SENSE)
- **Optional:** 10–100 nF capacitor from `SENSE` → GND (smoothing)

## Comparator (LM2904)
- **LM2904 + input → `SENSE`**
- **LM2904 – input → `VREF`** (threshold from potentiometer)

## Potentiometer for Adjustable Sensitivity
Use a **10 kΩ or 50 kΩ potentiometer**:

- One outer pin → 5 V
- Other outer pin → GND
- Middle wiper → `VREF` → LM2904 (– input)

**Effect:**
- Lower VREF → more sensitive (smaller vibration triggers)
- Higher VREF → less sensitive (requires stronger hit)

## Output to Arduino
- **LM2904 output → (optional 1 kΩ resistor) → Arduino digital input**

Configure the Arduino pin as a standard digital input or interrupt source.

## Logic Sense
With the normal wiring (`+` = SENSE, `–` = VREF):

- **If `SENSE` > `VREF` → Output HIGH**
- **If `SENSE` < `VREF` → Output LOW**

To invert the logic (LOW on vibration spike), simply swap which LM2904 input receives `SENSE` and `VREF`.