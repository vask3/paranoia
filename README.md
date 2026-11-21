# Paranoia: Hardware-Tokenized Text Encryption Keychain

A custom-designed, battery-free hardware key built around the **RP2040-Zero** and **JDY-23 BLE module**. Designed to plug directly into a phone or laptop via USB OTG to encrypt and decrypt sensitive text securely offline without exposing keys to cloud apps or risking battery degradation on a keychain.

---

## Why This Project Exists

* **Zero Battery Hassle:** No lithium-ion cells to swell, leak, or slowly discharge over time. The device powers on instantaneously only when plugged into a USB OTG port or host device, keeping it ultra-compact, maintenance-free, and safe for everyday keychain carry.
* **Instantaneous Local Text Scrambling:** Designed for speed. Short notes, passwords, or messages are processed on the fly using a dedicated microcontroller, removing reliance on online services or vulnerable third-party storage.
* **Complete Hardware Loop Execution:** A personal engineering challenge covering the entire design lifecycle—from initial architecture and schematic capture to routing a 2-layer PCB in EasyEDA Pro, managing high-frequency RF clearance, and writing bare-metal firmware.

<img width="383" height="258" alt="image" src="https://github.com/user-attachments/assets/57a5446a-d7d6-4c13-b40e-5fcea5b2d8bd" />
<img width="506" height="263" alt="image" src="https://github.com/user-attachments/assets/712a0126-5d4d-4082-ad95-2a34a402cea8" />

---

## Architecture & Bill of Materials

| Component | Function & Role |
| :--- | :--- |
| **MCU: RP2040-Zero** | Core processing, USB OTG interface, crypto execution, and hardware control. Powered strictly via VBUS. |
| **BLE: JDY-23 Module** | Low-energy wireless serial communication (UART) for passing encrypted/decrypted payloads to companion devices if needed. |
| **I/O: 3 × Status LEDs** | Visual feedback indicating operational state (e.g., Power, Encryption Active, BLE Connected/Ready). |
| **I/O: 2 × Tactile Buttons** | Mode switching, encryption/decryption execution triggers, and state management. |
| **PCB: Custom 2-Layer Board** | Compact form factor (`50.8 mm x 33.15 mm`) optimized for keychain attachment with careful RF ground plane management around the BLE antenna. |

<img width="714" height="393" alt="image" src="https://github.com/user-attachments/assets/00d94b0a-b9cb-4f7a-b79a-dae87c880db7" />

---

## PCB Design & Layout Considerations

* **Antenna Clearance:** Kept copper pours, traces, and ground planes completely clear underneath and around the JDY-23 antenna zone to prevent RF signal attenuation and maintain stable BLE connectivity.
* **Trace Optimization:** Routed signal traces cleanly across two layers while preserving a solid underlying ground reference plane to minimize electromagnetic interference (EMI) and ensure signal integrity across the UART lines.
* **Design Rule Checking (DRC):** Fully verified with zero errors in EasyEDA Pro prior to manufacturing preparation.

---

## Current Project Status

* [x] **Schematic Capture & Component Selection:** Finalized pin mapping for the RP2040-Zero and JDY-23 UART interface.
* [x] **PCB Layout & Routing:** Completed 2-layer layout (`50.8 mm x 33.15 mm`) with DRC clearance checks passed.
* [ ] **Board Fabrication & Assembly:** Ordering custom PCBs, stencil, and soldering components (RP2040-Zero, JDY-23, tactile buttons, current-limiting resistors, and LEDs).
* [ ] **Firmware Development:** Writing the C/C++ or MicroPython firmware to handle USB OTG input/output, button debouncing, LED state mapping, and AES/custom text cipher logic over serial/BLE streams.
