# 60% Modular Keyboard
 It is a 60% wireless keyboard(bluetooth) also works wired. It has magnetic modules. Currently I only added a Numpad but almost anything could be added in a chain as long as it works on i2c.
it has hotswapable switches, rgb lights for each key, OLED, rotoary encoder, dedicated fast charging module(1000mah) and a 2000mah single cell battery. Also it is kind of MCU agnostic, you can use any XIAO series MCU with it, for example rp2040 if you don't want bluetooth or nRF52840. 
![keyboard complete](Assets/keyboard%20assembled.jpeg)

# CAD Design
I used shapr3d to make the case, it is not done, I am still working on it, once I am happy with a case I will add it here, but the current case is as follows: 
![keyboard disassembled](Assets/keyboard%20disassembeled%20two.jpeg)
![keyboard dissassembled](Assets/keyboard%20disassmbled.jpeg)

# Wired connections
The charging module and battery are not connected to the PCB electrically, I will use wires for them. 
![wiring](Assets/wirting.jpeg)

# PCB design
I used KiCad to make the PCB. Here are the schematics:
![schematics](Assets/schematics.png)

Here is the PCB:
![PCB](Assets/latest%20PCB.png)

# Firmware
For Firmware I made two of them, one in QMK and one in ZMK. ZMK will work only when it is upgraded to zephyr 3.6 or use a custom driver for the I2C expander. QMK will work out of the box but it is not bluetooth, it is wired only. I will add the firmware here once I am done with it.

# BOM 

add BOM here