#include <LGAC.h>
#include <IRremote.h>

IRsend irsend;
LGAC lgac;

int ledPin = 3;

struct ac_mode {
  int mode;
  int fan;
  int temperature;
  int state;
};

ac_mode read_data(String data) {
  String buf[4];
  int from = 0;
  int n = 0;
  int index;
  ac_mode mode;

  while ((index = data.indexOf(',', from)) > -1) {
    buf[n] = data.substring(from, index);
    from = index + 1;
    n += 1;
  }
  buf[n] = data.substring(from);

  mode.mode = buf[0].toInt();
  mode.fan = buf[1].toInt();
  mode.temperature = buf[2].toInt();
  mode.state = buf[3].toInt();

  return mode;
}

void setup() {
  Serial.begin(9600);
  //LGAC LGAC(mode_heating,fan_4,30,state_off);
  // lgac.setMode(mode_cooling,fan_4,18, state_on);
}

void loop() {
  if (Serial.available()) {
    ac_mode mode = read_data(Serial.readStringUntil(';'));
    Serial.print("mode: ");
    Serial.print(mode.mode);
    Serial.print("\nfan: ");
    Serial.print(mode.fan);
    Serial.print("\ntemperature: ");
    Serial.print(mode.temperature);
    Serial.print("\nstate: ");
    Serial.print(mode.state);

    lgac.setMode(mode.mode, mode.fan, mode.temperature, mode.state);
    irsend.sendRaw(lgac.codes,LGAC_buffer_size,38);
  }
}
