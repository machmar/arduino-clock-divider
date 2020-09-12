#include <FastLED.h>

//I want to rewrite the whole code for this new 4hp version too
//!WARNING! The expander should be working but Im not sure as my expander broke. !EDIT! The expander works fine.

const static uint8_t outJack[] = {12, 2, 3, 4, 5, 6, 7, 8, 13, 10};
#define inJack 11
#define inDetect 14
#define lightS 15
#define primeS 16
#define edgeS 17
#define gateTriggerS 18
#define reset10S 19

#define triggerLenght 10

//#define SerialDebug //uncomment this #define to enable Serial DEBUG.
//The Baud rate is 1000000 - it will work with both 8 and 16 MHz based arduinos.

bool lightPrev;
bool primePrev;
bool edgePrev;
bool reset10Prev;
uint8_t pixelHue[2];
uint32_t ledPMill;
bool inDetectPrev;
bool inPrev;
uint8_t counter[11];
bool gate2TriggerClockFlag;
uint32_t gate2TriggerPMill;
bool outputState[11];
bool gate2TriggerTimerRunning;
uint32_t logicLedPMill;

CRGB led[2];

void setup() {
  for (uint8_t i = 0; i < 10; i++) pinMode(outJack[i], OUTPUT);
  for (uint8_t i = 0; i < 10; i++) digitalWrite(outJack[i], 0);
  pinMode(inDetect, INPUT_PULLUP);
  pinMode (lightS, INPUT_PULLUP);
  pinMode (primeS, INPUT_PULLUP);
  pinMode (edgeS, INPUT_PULLUP);
  pinMode (gateTriggerS, INPUT_PULLUP);
  pinMode (reset10S, INPUT_PULLUP);

  FastLED.addLeds<NEOPIXEL, 9>(led, 2);

  //input-jack-init-BEGIN
  bool inDetectState = digitalRead(inDetect);
  inDetectPrev = inDetectState;
  if (inDetectState) pinMode(outJack[0], INPUT);
  else pinMode(outJack[0], INPUT_PULLUP);
  //input-jack-init-END

  led[0] = 0xff0000;
  led[1] = 0x5500ff;
  FastLED.show();

  #ifdef SerialDebug
  Serial.begin(1000000);
  Serial.println("Rudimentary DEBUG connection established. Starting DEBUG.");
  Serial.println("!WARNING! The module will run significantly slower with this DEBUG running.");
  Serial.println();
  #endif
}

void refreshLeds(uint8_t brightness, uint8_t fps) {
  uint32_t CMill = millis();
  if (CMill - ledPMill >= 1000 / fps) {
    ledPMill = CMill;
    FastLED.setBrightness(brightness);
    FastLED.show();
    #ifdef SerialDebug
    Serial.println("LEDs refreshed");
    #endif
  }
}

void divisionCore(uint8_t divisions[], bool edge, bool disable10) {
  bool inState = digitalRead(inJack);
  if (inState != inPrev) { //INput jack state change detection
    inPrev = inState;
    #ifdef SerialDebug
    Serial.print("Clock impulse detected. The current state is: ");
    Serial.println(inState);
    #endif
    if (edge || !edge && inState) {
      for (uint8_t i = 0; i < 10; i++) { //increments the counters
        counter[i]++;
      }
      gate2TriggerClockFlag = 1;
    }

    for (uint8_t i = 0; i < 10 - disable10; i++) { //check if the counter is high enough to change the ouptut state
      if (divisions[i] == 1) {
        outputState[i] = inState;
        counter[i] = 0;
      }
      else if (counter[i] >= divisions[i]) {
        outputState[i] = !outputState[i];
        counter[i] = 0;
      }
    }
    if (disable10) digitalWrite(outJack[9], 0);
    led[0] = CHSV(pixelHue[0]++, 255, 255); //this led just updates its hue every time this loops
    led[1] = CHSV(pixelHue[1] -= 2, 255, 255); //this led does the same as the other one just three times faster
  }
}

void gate2Trigger(uint16_t trigLenght) {
  uint32_t CMill = millis();

  if (gate2TriggerClockFlag) {
    for (uint8_t i = 0; i < 10; i++) {
      digitalWrite(outJack[i], outputState[i]);
      if (outputState[i]) {
        outputState[i] = 0;
        counter[i] = 0;
      }
    }
    gate2TriggerPMill = CMill;
    gate2TriggerClockFlag = 0;
    gate2TriggerTimerRunning = 1;
    #ifdef SerialDebug
    Serial.println("Outs set to theier state.");
    #endif
  }

  if (CMill - gate2TriggerPMill >= trigLenght && gate2TriggerTimerRunning) {
    for (uint8_t i = 0; i < 10; i++) digitalWrite(outJack[i], 0);
    gate2TriggerTimerRunning = 0;
    #ifdef SerialDebug
    Serial.println("Outs set to logical 0.");
    #endif
  }
}

void gate2Jack() {
  for (uint8_t i = 0; i < 10; i++) digitalWrite(outJack[i], outputState[i]);
}

void dividing() {
  bool lightState = digitalRead(lightS);
  bool primeState = digitalRead(primeS);
  bool edgeState = digitalRead(edgeS);
  uint16_t gateTriggerState = analogRead(gateTriggerS);
  bool reset10State = digitalRead(reset10S);

  if (!lightState) refreshLeds(255, 15);

  uint8_t standardDividing[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  uint8_t primeDividing[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23};
  if (primeState) divisionCore(standardDividing, edgeState, !reset10State);
  else divisionCore(primeDividing, edgeState, !reset10State);

  if (gateTriggerState > 980) gate2Jack();
  else if (gateTriggerState > 20) gate2Trigger(map(gateTriggerState, 25, 975, 200, 0));
  else gate2Trigger(triggerLenght);

  if (reset10State != reset10Prev) {
    reset10Prev = reset10State;
    pinMode(outJack[9], reset10State);
  }
  if (!reset10State) {
    digitalWrite(outJack[9], 0);
    if (digitalRead(outJack[9])) {
    for (uint8_t i = 0; i < 9; i++) {
        outputState[i] = 0;
        counter[i] = 0;
      }
    }
  }
}

void logic() {
  bool AState = digitalRead(outJack[0]);
  bool BState = digitalRead(outJack[1]);
  bool CState = digitalRead(outJack[8]);
  bool DState = digitalRead(outJack[9]);

  digitalWrite(outJack[2], AState & BState);
  digitalWrite(outJack[3], AState | BState);
  digitalWrite(outJack[4], AState ^ BState);
  digitalWrite(outJack[5], CState & DState);
  digitalWrite(outJack[6], CState | DState);
  digitalWrite(outJack[7], CState ^ DState);

  if (millis() - logicLedPMill >= 50) {
    logicLedPMill = millis();
    led[0] = CHSV(pixelHue[0]++, 255, 255); //this led just updates its hue every time this loops
    led[1] = CHSV(pixelHue[1] -= 2, 255, 255); //this led does the same as the other one just three times faster
  }

  if (!digitalRead(lightS)) refreshLeds(255, 20);
}

void loop() {
  bool inDetectState = digitalRead(inDetect);
  if (inDetectState != inDetectPrev) { //change INput direction when the jack plugs in or unplugs
    inDetectPrev = inDetectState;
    for (uint8_t i = 0; i < 10; i++) digitalWrite(outJack[i], 0);
    if (!inDetectState) {
      pinMode(inJack, INPUT_PULLUP);
      pinMode(outJack[0], OUTPUT);
      pinMode(outJack[1], OUTPUT);
      pinMode(outJack[8], OUTPUT);
      pinMode(outJack[9], digitalRead(reset10S));
      #ifdef SerialDebug
      Serial.println("IN jack plugged in");
      #endif
    }
    else {
      pinMode(inJack, INPUT);
      pinMode(outJack[0], INPUT);
      pinMode(outJack[1], INPUT);
      pinMode(outJack[8], INPUT);
      pinMode(outJack[9], INPUT);
      #ifdef SerialDebug
      Serial.println("IN jack unplugged");
      #endif
    }
  }
  if (inDetectState) logic();
  else dividing();
}
