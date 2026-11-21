# Paranoia

I wanted a tiny keychain thing I can plug into a phone or laptop over USB OTG to encrypt and decrypt text without keeping secret stuff on an always-online cloud app or draining a battery when it's just sitting on my keys.

## Why I'm making this
- **No battery to die or swell:** It only powers on when plugged in via USB OTG, so it stays dead simple and safe on a keychain.
- **Quick text encryption:** The whole point is scrambling/unscrambling short messages fast using an RP2040-Zero, a JDY-23 BLE module, 3 LEDs to show state/mode, and 2 buttons so I don't have to guess what it's doing.
- **Learning the full loop:** I designed the 2-layer PCB myself in EasyEDA Pro (including keeping the antenna area clear after some routing headaches and DRC checks), and next I'm writing the RP2040-Zero code and ordering the boards.
<img width="383" height="258" alt="image" src="https://github.com/user-attachments/assets/57a5446a-d7d6-4c13-b40e-5fcea5b2d8bd" />
<img width="506" height="263" alt="image" src="https://github.com/user-attachments/assets/712a0126-5d4d-4082-ad95-2a34a402cea8" />


## Parts & Board
- **MCU:** RP2040-Zero (USB OTG, powered only when plugged in)
- **BLE:** JDY-23 module over UART
- **I/O:** 3 LEDs + resistors, 2 tactile buttons
- **PCB:** Custom 2-layer board (`50.8 mm x 33.15 mm`) in EasyEDA Pro
<img width="714" height="393" alt="image" src="https://github.com/user-attachments/assets/00d94b0a-b9cb-4f7a-b79a-dae87c880db7" />

## Where things are at
- [x] Schematic & PCB routing (0 DRC errors)
- [ ] Order PCBs & solder parts
- [ ] Write firmware for encryption modes, buttons, LEDs, and BLE serial
