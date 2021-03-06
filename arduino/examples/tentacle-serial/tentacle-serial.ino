#include <SPI.h>

#include "tentacle-build.h"
//Checkout http://tentacle.readme.io for setup and usage instructions
#define conn Serial

TentacleArduino tentacle;
Pseudopod pseudopod(conn, conn, tentacle);

void setup() {
  Serial.begin(57600);
}

void loop() {
  readData();

  if(!pseudopod.isConfigured()) {
    delay(100);
    pseudopod.requestConfiguration();
  }

  if(pseudopod.shouldBroadcastPins() ) {
    delay(pseudopod.getBroadcastInterval());
    pseudopod.sendConfiguredPins();
  }
}

void readData() {
  while (conn.available()) {
    if(pseudopod.readMessage() == TentacleMessageTopic_action) {
      pseudopod.sendPins();
    }
  }

}
