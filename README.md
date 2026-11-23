# Paranoia: Hardware-Tokenized Text Encryption Keychain

A battery-free hardware key that lives on my keychain, built around an **RP2040-Zero** and a **JDY-23 BLE module**. Whenever I want to lock or unlock secret text, I just plug it straight into my phone or laptop over USB OTG. Everything happens offline right on the microcontroller, so my encryption keys never touch the cloud or external servers. There is also no battery inside waiting to die or puff up in my pocket.

---

## Why I Built This

* **Zero Battery Hassle:** There is no LiPo or coin cell inside that can swell or drain while sitting on my keys. The board wakes up the instant it gets 5V VBUS power from a USB OTG cable or computer and runs off the RP2040-Zero's built-in 3.3V regulator. The moment I unplug it, power cuts off completely.
* **Fast Local Text Scrambling:** Short notes, passwords, recovery phrases, and private messages get encrypted and decrypted directly on the chip in milliseconds. Even if a phone or PC has sketchy apps running, the actual key and math stay isolated on my hardware.
* **Full End-to-End Hardware Build:** I wanted to take a real hardware idea from scratch all the way to a finished board. That meant choosing components, checking datasheets, drawing the schematic, and routing a custom 2-layer PCB in EasyEDA Pro. I also laid out the board to keep the 2.4 GHz Bluetooth antenna clear of copper and wrote the firmware myself.

<img width="383" height="258" alt="image" src="https://github.com/user-attachments/assets/57a5446a-d7d6-4c13-b40e-5fcea5b2d8bd" />
<img width="506" height="263" alt="image" src="https://github.com/user-attachments/assets/712a0126-5d4d-4082-ad95-2a34a402cea8" />

---

## How It Works (Data Flow)

1. **Plug In:** Connect the keychain to a phone (via USB OTG) or a laptop over USB-C. 5V VBUS powers the RP2040-Zero, which supplies regulated 3.3V to the JDY-23 BLE module and logic circuits.
2. **Pick a Mode:** Use the two tactile buttons (`SW1` and `SW2`) to switch between **Encrypt** and **Decrypt** modes (or enable the **BLE Bridge**) while checking the status LEDs to see which state is active.
3. **Send and Process Text:** Send your text to the board over USB Serial or Bluetooth. The RP2040-Zero handles the encryption math locally in firmware without saving keys on your phone or computer.
4. **Copy and Unplug:** Grab the processed text on your screen and unplug the keychain. Cutting power wipes the RAM immediately.

---

## Hardware Architecture & Pinout

The board uses a compact 2-layer layout designed in EasyEDA Pro. All components sit on a single side to keep the keychain slim and easy to solder.

| Component | Designator | RP2040 Pin | Function |
| :--- | :--- | :--- | :--- |
| **JDY-23 BLE Module** | `U2` | `GP0` / `GP1` | UART communication (`BLE_RX` / `BLE_TX`) at 3.3V |
| **Green Status LED** | `LED1` + `R1` (470Ω) | `GP2` | Indicates ready state or successful decryption |
| **Yellow Status LED** | `LED2` + `R2` (470Ω) | `GP3` | Indicates Bluetooth activity or processing |
| **Red Status LED** | `LED3` + `R3` (470Ω) | `GP4` | Indicates encryption mode or error state |
| **Mode Button** | `SW1` | `GP5` | Active-low switch (`BTN_MODE`) to cycle operating modes |
| **Action Button** | `SW2` | `GP6` | Active-low switch (`BTN_ACTION`) to trigger or confirm tasks |

### Design Choices
* **Current-Limiting Resistors:** Each 0603 LED (`LED1` to `LED3`) is paired with a `470Ω` resistor (`R1` to `R3`) to keep current draw low while remaining clearly visible in daylight.
* **Internal Pull-Ups:** Both tactile switches (`KH-6X6X5H-GTM`) connect directly to ground, relying on the RP2040's internal pull-up resistors to save board space.
* **Power Regulation:** The JDY-23 runs directly off the RP2040-Zero's `3V3` pin, eliminating the need for an external LDO voltage regulator.

---

## Bill of Materials (BOM)

* **1x** Waveshare RP2040-Zero (`U1`)
* **1x** JDY-23 Bluetooth 5.0 BLE Module (`U2`)
* **2x** 6x6x5mm SMD Tactile Push Buttons (`SW1`, `SW2`)
* **1x** 0603 Green SMD LED (`LED1`)
* **1x** 0603 Yellow SMD LED (`LED2`)
* **1x** 0603 Red SMD LED (`LED3`)
* **3x** 0603 470Ω Resistors (`R1`, `R2`, `R3`)

---

## Getting Started

1. **Flash the Firmware:** Hold the `BOOT` button on the RP2040-Zero while plugging it into your computer, then drag and drop the compiled `.uf2` firmware file onto the `RPI-RP2` drive.
2. **Connect a Terminal or App:** Open any serial terminal on your PC (or a BLE serial app on your phone) at `115200` baud.
3. **Encrypt or Decrypt:** Press `SW1` to select your mode, send your text string, and press `SW2` if hardware confirmation is enabled.
