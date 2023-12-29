#include <TinyWireM.h>
#include <Tiny4kOLED.h>

#define LEDPin 4
#define shock 1
#define screenPin 3

int val;
int steps = 0;
float dist = 0.76;
boolean shockstate;
boolean screenPinstate;

uint8_t width = 128;
uint8_t height = 32;

void setup() {
  pinMode(LEDPin,OUTPUT);
  pinMode(shock,INPUT_PULLUP);
  pinMode(screenPin,INPUT_PULLUP);
  oled.begin(128, 32, sizeof(tiny4koled_init_128x32br), tiny4koled_init_128x32br);
  oled.clear();
  oled.setFont(FONT8X16P);
  oled.on();
  oled.print("Ready");
  delay(200);
  oled.clear();
}

void loop () {
  shockstate = !digitalRead(shock);
  if (shockstate) {
    digitalWrite(LEDPin, HIGH);
    steps +=1;
    delay(10);
  } else {
    digitalWrite(LEDPin, LOW);
    screenPinstate = !digitalRead(screenPin);
    if (screenPinstate) {
      oled.clear();
      oled.setCursor(0, 0);
      oled.print(steps);
      oled.print(" steps");
      oled.setCursor(0, 2);
      oled.print(steps*2*dist);
      oled.print(" m");
      delay(500);
      oled.clear();
    }
  }
}
