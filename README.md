# Paranoia: Hardware-Tokenized Text Encryption Keychain

A battery-free hardware key that lives on my keychain, built around an **RP2040-Zero** and a **JDY-23 BLE module**. Whenever I want to lock or unlock secret text, I just plug it straight into my phone or laptop over USB OTG. Everything happens offline right on the microcontroller—so my encryption keys never touch cloud apps, random servers, or third-party websites, and there is no battery inside waiting to die or puff up in my pocket.

---

## Why I Built This

* **Zero Battery Hassle:** There is no LiPo or coin cell inside that can swell, leak, or slowly drain while sitting on my keys. The board wakes up the instant it gets 5V VBUS power from a USB OTG cable or computer, runs off the RP2040-Zero's built-in 3.3V regulator, and shuts off completely the moment I unplug it.
* **Fast Local Text Scrambling:** Short notes, passwords, recovery phrases, or private messages get encrypted and decrypted directly on the chip in milliseconds. Even if a phone or PC has sketchy apps running, the actual key and math stay isolated on my hardware.
* **Full End-to-End Hardware Build:** I wanted to take a real hardware idea from scratch all the way to a finished board—choosing components, checking datasheets, drawing the schematic, routing a custom 2-layer PCB in EasyEDA Pro, keeping the 2.4 GHz Bluetooth antenna clear of copper, and writing the firmware myself.

<img width="383" height="258" alt="image" src="https://github.com/user-attachments/assets/57a5446a-d7d6-4c13-b40e-5fcea5b2d8bd" />
<img width="506" height="263" alt="image" src="https://github.com/user-attachments/assets/712a0126-5d4d-4082-ad95-2a34a402cea8" />

---

## How It Works (Data Flow)

1. **Plug In:** Connect the keychain to a phone (via USB OTG) or laptop over USB-C. 5V VBUS powers the RP2040-Zero, which supplies regulated 3.3V to the JDY-23 BLE module and logic circuits.
2. **Pick a Mode:** Use the two tactile buttons to switch between **Encrypt**, **Decrypt**, or **BLE Bridge** mode while checking the 3 status LEDs so I always know what state it's in.
3. **Send Text:** Type or paste plaintext (or ciphertext) over USB Serial—or wirelessly over Bluetooth Low Energy via the JDY-23.
4. **Get Output:** The RP2040 runs the cipher locally on its dual-core Cortex-M0+ CPU and spits back the scrambled or unscrambled text right away.

---

## Parts List & Architecture

| Part | Specs & What It Does |
| :--- | :--- |
| **MCU: RP2040-Zero** | Dual-core Arm Cortex-M0+ up to 133 MHz with 264 KB SRAM and 2 MB Flash. Acts as the main brain: handles USB OTG serial communication, executes the encryption/decryption math, reads button presses, drives the status LEDs, and regulates 5V VBUS down to 3.3V. |
| **BLE: JDY-23 Module** | Bluetooth 5.0 Low Energy transparent UART module (2.4 GHz, 3.3V logic). Connects to the RP2040-Zero's hardware UART (`TXD`/`RXD`) plus control/status pins (`PWRC`, `STAT`, `RST`) so I can wirelessly pass encrypted or decrypted payloads to a phone when needed. |
| **I/O: 3 × Status LEDs** | Discrete LEDs with current-limiting resistors for instant visual feedback without needing a screen—showing **Power Ready**, **Encrypt/Decrypt Active**, and **BLE Connected/Busy**. |
| **I/O: 2 × Tactile Buttons** | Physical buttons for switching modes, triggering encryption/decryption, or resetting/clearing buffers safely on the hardware itself. |
| **PCB: Custom 2-Layer Board** | Compact keychain-ready form factor (`50.8 mm x 33.15 mm`) with a mounting hole for a keyring, clean 3.3V logic routing, and a dedicated copper keep-out zone around the JDY-23 PCB antenna. |

<img width="714" height="393" alt="image" src="https://github.com/user-attachments/assets/00d94b0a-b9cb-4f7a-b79a-dae87c880db7" />

---

## PCB Design & Layout Notes

* **2.4 GHz Antenna Keep-Out:** Kept top and bottom copper pours, signal traces, and ground planes completely out from under and around the JDY-23's built-in PCB antenna so the RF signal doesn't get detuned, blocked, or lose range.
* **3.3V Logic & Signal Integrity:** Since both the RP2040-Zero and JDY-23 run at 3.3V logic levels, no level shifters were needed—keeping the board small and clean. I routed UART, button, and LED traces cleanly across two layers while keeping a solid ground reference underneath to cut down noise and EMI.
* **Zero-Error DRC:** Verified trace widths, clearances, drill sizes, and silkscreen labels using EasyEDA Pro's Design Rule Check (DRC) with zero errors or warnings before exporting Gerbers.

---

## Where I'm At (Project Roadmap)

* [x] **Schematic & Pin Mapping:** Selected all parts, verified 3.3V power budgets, and wired up the RP2040-Zero to the JDY-23 UART pins, 2 tactile buttons, and 3 status LEDs.
* [x] **2-Layer PCB Layout:** Finished routing the `50.8 mm x 33.15 mm` board in EasyEDA Pro, added the BLE antenna keep-out zone, and passed DRC with zero errors.
* [ ] **Fabrication & Soldering:** Ordering the custom PCBs and solder paste stencil, soldering the RP2040-Zero castellated pads, JDY-23 module, tactile switches, resistors, and LEDs, then doing basic power and continuity tests.
* [ ] **Firmware Development:** Writing the C/C++ (Pico SDK) or MicroPython firmware to handle USB OTG CDC serial I/O, hardware button debouncing, LED status blinking patterns, JDY-23 AT-command setup, and AES / custom text cipher routines.
