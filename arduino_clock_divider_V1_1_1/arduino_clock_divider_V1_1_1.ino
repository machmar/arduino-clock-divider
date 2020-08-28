#include <FastLED.h>

//I want to revrite the whole code  for the old 8hp version I have

const static uint8_t jacks[] = {12, 11, 2, 3, 4, 5, 6, 7, 8, 15, 10};
#define inDetect 14

uint32_t animationPMill;
uint8_t fallingAnimationString;
bool fallingAnimationState;
uint8_t pixelHue[2];
uint32_t ledPMill;
bool inDetectPrev;
bool inPrev;
uint8_t counter[10];

CRGB led[2];

void setup() {
  for (uint8_t i = 0; i < 11; i++) pinMode(jacks[i], OUTPUT);
  pinMode (inDetect, INPUT_PULLUP);
  FastLED.addLeds<NEOPIXEL, 9>(led, 2);

  //input-jack-init-BEGIN
  bool inDetectState = digitalRead(inDetect);
  inDetectPrev = inDetectState;
  for (uint8_t i = 0; i < 10; i++) digitalWrite(jacks[i + 1], 0);
  if (inDetectState) pinMode(jacks[0], OUTPUT);
  else pinMode(jacks[0], INPUT_PULLUP);
  //input-jack-init-END
  
  randomSeed(analogRead(21)); //get some random seed from a floating ADC pin
}

void advanceFallingAnimation() { //falling strings of on and off leds with random lenght
  for(uint8_t i = 10; i > 0; i--) { //copy the the led state into the one below it
    digitalWrite(jacks[i], digitalRead(jacks[i - 1]));
  }
  if (fallingAnimationString > 0) { //gets state of the top led
    digitalWrite(jacks[0], fallingAnimationState);
    fallingAnimationString--;
  }
  else {
    fallingAnimationString = random(1, 10); //gets a random value if the old one gets fully used
    fallingAnimationState = !fallingAnimationState; //toggles the state of the led for the new string
  }
  led[0] = CHSV(pixelHue[0]++, 255, 255); //this led just updates its hue every time this loops
  led[1] = CHSV(pixelHue[1] += 3, 255, 255); //this led does the smae as the other one just three times faster
}

void animation(uint8_t fps) {
  uint32_t CMill = millis();
  if (CMill - animationPMill >= 1000 / fps) {
    animationPMill = CMill;
    advanceFallingAnimation();
  }
}

void division() {
  bool inState = digitalRead(jacks[0]);
  if (inState != inPrev) { //INput jack state change detection
    inPrev = inState;
    for (uint8_t i = 0; i < 10; i++) { //increments the counters 
      counter[i]++;
    }
    digitalWrite(jacks[1], inState);
    for (uint8_t i = 1; i < 10; i++) { //check if the counter is high enough to change the ouptut state
      if (counter[i - 1] >= i + 1) {
        digitalWrite(jacks[i + 1], !digitalRead(jacks[i + 1]));
        counter[i - 1] = 0;
      }
    }
    led[0] = CHSV(pixelHue[0]++, 255, 255); //this led just updates its hue every time this loops
    led[1] = CHSV(pixelHue[1] -= 2, 255, 255); //this led does the smae as the other one just three times faster
  }
}

void refreshLeds(uint8_t brightness, uint8_t fps) {
  uint32_t CMill = millis();
  if (CMill - ledPMill >= 1000 / fps) {
    ledPMill = CMill;
    FastLED.setBrightness(brightness);
    FastLED.show();
  }
}

void loop() {
  bool inDetectState = digitalRead(inDetect);
  if (inDetectState != inDetectPrev) { //change INput directionwhen the jack plugs in or unplugs
    inDetectPrev = inDetectState;
    for (uint8_t i = 0; i < 10; i++) digitalWrite(jacks[i + 1], 0);
    if (inDetectState) pinMode(jacks[0], OUTPUT);
    else pinMode(jacks[0], INPUT_PULLUP);
  }
  if (inDetectState) animation(20); //selects between animations and dividing based on if the INput jack socket is occupied
  else division();
  refreshLeds(255, 20);
}
