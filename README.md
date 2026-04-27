# Magic-Millipede | Developer README
### Millipedarium Tech Box | CUI Engineering & Computer Science<br/>
### Team Members:<br/>
- Tech Box & Electronics | Dev - Elijah Ludwig
- Tech Box Assembly & Mounting Design | Engineer - Tyler Cunningham
- Engineer - Ethan Stehr

## Project Overview
The Magic Millipedes exxhibit project is a for a public museum installation that houses live bioluminescent Motyxia millipedes. Visitors will then enter 1 of 4 small dark rooms in the middle of the exhibit called the Millipedarium, and will press a button to trigger a timed, 2 minute audio and UV light presentation which will reveal the millipedes natural fluorescence. 

This GitHub Repoistory contains all the software and hardware design for a each room's tech box. There are 4 identical production units deployed one per room, and each room operates independently from one another.

Some key features include:
- Button triggered 2 minute state machine
  - IDLE -> PHASE_1 -> PHASE_2 -> PHASE_3 -> IDLE)
- UV Light controlled a 4 channel power relay module as it's fail-safe being defaulted to OFF in case of power loss or issues on electrical circuits
- Synchronized audio playback across the three phases
- Exterior RGB indicator lights which communicates the availability of the room to other visitors
- A presentation counter that will persist across power cycles held on flash memory by LittleFS

# System Architecture

# Key Components
- Inland Esp32 Devboard (Any microcontroller will work - ideally Rasberry Pi Pico 2 (non-wifi ver.))
- Adafruit Audio FX 16MB Sound Board
- TPA3116D2 2x50W Amp
- AEDIKO 4-channel 12V Relay Module (12V Output Power to components, module triggered and powered by 5V)
- LM2596 Buck Converter (Step down 12V to 5V for logic components)
- Baomain 19mm RGB LED Indicator
- Baomain 19mm LED Momentary Button (White LED only)
- Waveform RealUV LED Strip (365nm)
  
# Getting Started
## Hardware Requirements
- ESP32 Dev Board (or Raspberry Pi Pico 2)
- All components Mentioned in [Key Components](#key-components)
- Perfboard assembly based on layout in photos in [Perfboard Layout](#perfboard-layout)
  - Ideal and recommended option is custom designed PCB Board for minimal soldering and hotswap access since this is going into a public muesum exhibit and this is a production environment and not testing

## Software Requirements
1. Install Arduino IDE
2. Add ESP32 Board Package (or Raspi Pico 2) | Located in settings (additional board manager urls)<br/>
   - `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Go to Tools, Board Manager, search "esp32", then install esp32 by Espressif Systems
3. Select Board: Tools, Board, ESP32 Arduino, ESP32 Dev MOdule
4. Open the software sketch `Millipede-esp32.ino` and upload it to the microcontroller through it's USB port

## Audio Files
The Sound Board stores the audio files (.ogg format for size) on the onboard flash, File name determines which GPIO pin trigger plays them. <br/>
<br/>T00.ogg - [Phase 1]
<br/>T01.ogg - [Phase 2]
<br/>T02.ogg - [Phase 3]

Upload the audio files to the sound board through its USB port.

## Presentation Counter
The software writes a cycle count using LittleFS on the ESP32's flash; to read the counter connect the ESP32 to a computer by USB and open Arduino Serial Monitor and the current presentation count should be printed in the console/Arduino serial monitor.

# Design Notes

# Perfboard Layout

<img width="1000" height="750" alt="180DCDD5-8C2A-46DF-9541-CCEC7A1FE8A4_1_201_a" src="https://github.com/user-attachments/assets/ea2e5852-03d0-4167-bff0-18450dce235c" /><br/>

<img width="500" height="1000" alt="3EE8E61E-1E24-4792-B0BE-7DFC6FBEFD1F_1_201_a" src="https://github.com/user-attachments/assets/29b1ef6f-2973-477c-9495-22ca29be2f30" />
