#include <Homie.h>

const int RELAY_PIN = 5;

HomieNode audoSwitcherNode("audioSwitcher", "switch");

bool switchInputHandler(const HomieRange& range, const String& value) {
  if (value != "true" && value != "false") return false;

  bool on = (value == "true");
  digitalWrite(RELAY_PIN, on ? HIGH : LOW);
  audoSwitcherNode.setProperty("on").send(value);
  Homie.getLogger() << "Relay is " << (on ? "on" : "off") << endl;

  return true;
}

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  Homie_setFirmware("audio-switcher", "1.0.0");

  audoSwitcherNode.advertise("on").settable(switchInputHandler);

  Homie.setup();
}

void loop() {
  Homie.loop();
}