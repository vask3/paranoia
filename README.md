# Paranoia: Hardware-Tokenized Text Encryption Keychain

Hello thatis my battery-free hardware key that lives on my keychain.I built it with **RP2040-Zero** and a **JDY-23 BLE module**. 

## How to use?

* **How?** If you want to lock or unlock secret text you just need to plug it straight into phone or laptop over USB OTG.
#Js Plug and play!

---

## Why I Built This

* **No expensive LiPo!!:** There is no LiPo or coin cell inside that can swell or drain while sitting on my keys. The board wakes up the instant it gets 5V VBUS power from a USB cable 
* **Fast Local Text Scrambling:** Short notes, passwords, recovery phrases, and private messages get encrypted and decrypted directly on the chip in milliseconds. 
* **Full End-to-End Hardware Build:** I wanted to take a real hardware idea from scratch all the way to a finished board. That meant choosing components, checking datasheets, drawing the schematic, and routing a custom 2-layer PCB in EasyEDA Pro. I also laid out the board to keep the 2.4 GHz Bluetooth antenna clear of copper and wrote the firmware myself.

<img width="383" height="258" alt="image" src="https://github.com/user-attachments/assets/57a5446a-d7d6-4c13-b40e-5fcea5b2d8bd" />
<img width="506" height="263" alt="image" src="https://github.com/user-attachments/assets/712a0126-5d4d-4082-ad95-2a34a402cea8" />

---

## How It Works (Data Flow)

1. **Plug In:** Connect the keychain to a phone (via USB OTG) or a laptop over USB-C. 5V VBUS powers the RP2040-Zero, which supplies regulated 3.3V to the JDY-23 BLE module and logic circuits.
2. **Pick a Mode:** Use the two tactile buttons (`SW1` and `SW2`) to switch between **Encrypt** and **Decrypt** modes (or enable the **BLE Bridge**).
3. **Send and Process Text:** Send your text to the board over Bluetooth. The RP2040 handles the encryption locally in firmware without saving keys.
4. **Copy and Unplug:** Grab the processed text on your screen and unplug the keychain. Cutting power wipes the RAM immediately.


<img width="714" height="393" alt="image" src="https://github.com/user-attachments/assets/00d94b0a-b9cb-4f7a-b79a-dae87c880db7" />

---

## Hardware Architecture & Pinout

The board uses a compact 2-layer layout designed in EasyEDA Pro. All components are soldered on a single side.

| Component | Name | Pin | What? |
| :--- | :--- | :--- | :--- |
| **JDY-23 BLE Module** | `U2` | `GP0` / `GP1` | UART communication (`BLE_RX` / `BLE_TX`) at 3.3V |
| **Green Status LED** | `LED1` + `R1` (470Ω) | `GP2` | Indicates ready state or successful decryption |
| **Yellow Status LED** | `LED2` + `R2` (470Ω) | `GP3` | Indicates Bluetooth activity or processing |
| **Red Status LED** | `LED3` + `R3` (470Ω) | `GP4` | Indicates encryption mode or error state |
| **Mode Button** | `SW1` | `GP5` | Active-low switch (`BTN_MODE`) to cycle operating modes |
| **Action Button** | `SW2` | `GP6` | Active-low switch (`BTN_ACTION`) to trigger or confirm tasks |

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
