// Based on Copyrighted code from (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

#define STARTUP_PAUSE 1000
#define CAN_PAUSE 1000
#define ONBOARD_LED_BLINK_PAUSE_MS 100
#define ONBOARD_LED_PIN  2
#define CAN_TX_PIN 33
#define CAN_RX_PIN 32

void setup() {

  // Initialize the serial console and wait a second to start
  Serial.begin(115200);
  delay(STARTUP_PAUSE);

  // Tell the serial console who we are
  Serial.println("****************");
  Serial.println("*  CAN Sender  *");
  Serial.println("****************");

  // Initialize the onboard LED
  pinMode(ONBOARD_LED_PIN,OUTPUT);

  // Specify which hardware pins to use for RX and TX
  // (Default is 4 and 5)
  CAN.setPins(CAN_RX_PIN, CAN_TX_PIN);

  // Start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  } else {
    Serial.println("CAN Successfully Started.");
  }

}

void loop() {

  // Send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending CAN packet ... ");
  blink();  // Blink the onboard LED

  CAN.beginPacket(0x12);
  CAN.write('h');
  CAN.write('e');
  CAN.write('l');
  CAN.write('l');
  CAN.write('o');
  CAN.endPacket();

  Serial.println("Done.");

  delay(CAN_PAUSE);

  // Send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending extended CAN packet ... ");
  blink();  // Blink the onboard LED

  CAN.beginExtendedPacket(0xabcdef);
  CAN.write('w');
  CAN.write('o');
  CAN.write('r');
  CAN.write('l');
  CAN.write('d');
  CAN.endPacket();

  Serial.println("Done.");

  delay(CAN_PAUSE);
}

void blink() {
  // Blink the onboard LED to indicate we're sending CAN messages
  digitalWrite(ONBOARD_LED_PIN,HIGH);
  delay(ONBOARD_LED_BLINK_PAUSE_MS);
  digitalWrite(ONBOARD_LED_PIN,LOW);
}
