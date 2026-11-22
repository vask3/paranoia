// test firmware for my paranoia keychain thing
// checks leds, buttons, ble uart and basic xor scramble

#include <Arduino.h>

// change these if your schematic uses different GP pins
#define LED_GREEN  2
#define LED_YELLOW 3
#define LED_RED    4

#define BTN_MODE   6
#define BTN_ACTION 7

// Serial1 on RP2040-Zero is GP0 (TX) and GP1 (RX) by default
#define BLE_SERIAL Serial1

int mode = 0; // 0 = green (light), 1 = yellow (medium), 2 = red (paranoid)
byte keys[3] = {0x13, 0x5A, 0xA7};

String xorText(String txt, byte k) {
  String out = "";
  for (int i = 0; i < txt.length(); i++) {
    char c = txt[i] ^ k;
    // keep it printable hex so ble/serial doesnt freak out
    char buf[3];
    sprintf(buf, "%02X", (byte)c);
    out += buf;
  }
  return out;
}

void updateLeds() {
  digitalWrite(LED_GREEN,  mode == 0 ? HIGH : LOW);
  digitalWrite(LED_YELLOW, mode == 1 ? HIGH : LOW);
  digitalWrite(LED_RED,    mode == 2 ? HIGH : LOW);
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_ACTION, INPUT_PULLUP);

  Serial.begin(115200);
  BLE_SERIAL.begin(9600); // JDY-23 default baud rate

  // quick led check on boot so i know nothing is bridged or dead
  digitalWrite(LED_GREEN, HIGH);  delay(150); digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, HIGH); delay(150); digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, HIGH);    delay(150); digitalWrite(LED_RED, LOW);

  updateLeds();
  Serial.println("paranoia test firmware ready");
  BLE_SERIAL.println("paranoia ble ready");
}

void loop() {
  // switch mode with button 1
  if (digitalRead(BTN_MODE) == LOW) {
    delay(40); // lazy debounce
    if (digitalRead(BTN_MODE) == LOW) {
      mode = (mode + 1) % 3;
      updateLeds();
      Serial.print("mode: ");
      Serial.println(mode);
      while (digitalRead(BTN_MODE) == LOW);
    }
  }

  // send a test encrypted string with button 2
  if (digitalRead(BTN_ACTION) == LOW) {
    delay(40);
    if (digitalRead(BTN_ACTION) == LOW) {
      String testMsg = "hello world";
      String enc = xorText(testMsg, keys[mode]);
      Serial.println("test enc: " + enc);
      BLE_SERIAL.println("test enc: " + enc);

      // blink current led once to show it sent
      updateLeds();
      delay(80);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, LOW);
      delay(80);
      updateLeds();

      while (digitalRead(BTN_ACTION) == LOW);
    }
  }

  // anything typed in USB serial gets scrambled and sent over BLE + printed back
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();
    if (msg.length() > 0) {
      String enc = xorText(msg, keys[mode]);
      Serial.println("enc: " + enc);
      BLE_SERIAL.println("enc: " + enc);
    }
  }

  // anything coming from phone over JDY-23 BLE gets scrambled and echoed back
  if (BLE_SERIAL.available()) {
    String msg = BLE_SERIAL.readStringUntil('\n');
    msg.trim();
    if (msg.length() > 0) {
      String enc = xorText(msg, keys[mode]);
      BLE_SERIAL.println("enc: " + enc);
      Serial.println("ble -> " + enc);
    }
  }
}