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
- UV Light controlled a 4 module power relay as it's fail-safe being defaulted to OFF in case of power loss or issues on electrical circuits
- Synchronized audio playback across the three phases
- Exterior RGB indicator lights which communicates the availability of the room to other visitors
- A presentation counter that will persist across power cycles held on flash memory by LittleFS

# System Architecture

# Key Components

# Getting Started

# Design Notes


Perfboard Layout
-

<img width="1000" height="750" alt="180DCDD5-8C2A-46DF-9541-CCEC7A1FE8A4_1_201_a" src="https://github.com/user-attachments/assets/ea2e5852-03d0-4167-bff0-18450dce235c" /><br/>

<img width="500" height="1000" alt="3EE8E61E-1E24-4792-B0BE-7DFC6FBEFD1F_1_201_a" src="https://github.com/user-attachments/assets/29b1ef6f-2973-477c-9495-22ca29be2f30" />
