 
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

## Sourcing
* 1x [LM393](https://www.mouser.com/ProductDetail/Texas-Instruments/LM393BIPWR?qs=OlC7AqGiEDk6Hx8FCoL%252BIg%3D%3D)
  * [Datasheet](docs/external/lm393.pdf) 
  * package: TSSOP-8
  * footprint: same
  * price: $0.20 
* 1x [500k Potentiometer](https://www.mouser.com/ProductDetail/Bourns/3386P-DF6-504LF?qs=sGAEpiMZZMukHu%252BjC5l7YewRvTbBNT1xUr5dTHURUsc%3D)
  * [Datasheet](docs/external/pot-500k.pdf)
  * package: through hole
  * footprint: 2-pin header
* price: $2.48
* 2x [Diode 1N4148](https://www.mouser.com/ProductDetail/Panjit/1N4148W_R2_00001?qs=sPbYRqrBIVlsNrvmMQOkFA%3D%3D)
  * [Datasheet](docs/external/diode%20-%201N4148.pdf)
  * package: SOD-123-2
  * footprint:
  * price: $0
* 1x [1M Ohm Resistor](https://www.amazon.com/AEDIKO-Capacitor-Resistor-Assortment-Resistors/dp/B096Z6H7SV/ref=sr_1_4?sr=8-4)
  * [Datasheet](docs/external/lm393.pdf)   
  * package: 1206
  * footprint: same
  * price: $6
* 1x 10k Ohm Resistor
  * [Datasheet](docs/external/lm393.pdf)
  * package:
  * footprint:
  * price: $0
* 1x [?uF capacitor](https://www.amazon.com/1206-Capacitor-Kits-16values-Multilayer/dp/B0F5Q8V6BH/ref=sr_1_4?sr=8-4)
  * [Datasheet](docs/external/lm393.pdf)
  * package: 1206
  * footprint: same
  * price: $8

Dev parts
* 1x 1k Ohm Resistor
  * [Datasheet](docs/external/lm393.pdf)
  * package:
  * footprint:
  * price: $0
* 1x green LED
  * [Datasheet](docs/external/lm393.pdf)
  * package:
  * footprint:
  * price: $0