#include <FastLED.h> //https://github.com/FastLED/FastLED

int out1 = 11;
int out2 = 2;
int out3 = 3;
int out4 = 4;
int out5 = 5;
int out6 = 6;
int out7 = 7;
int out8 = 8;
int out9 = 21;
int out10 = 10;
int out1Var = 0;
int out2Var = 0;
int out3Var = 0;
int out4Var = 0;
int out5Var = 0;
int out6Var = 0;
int out7Var = 0;
int out8Var = 0;
int out9Var = 0;
int out10Var = 0;
int aniVar = 0;
int aniSelect = 0;
int in = 12;
int inDetect = 14;
int inDetectVar = 1;
int inState = 0;
bool out9State = 0;
bool out9Prev = 1;
bool out10State = 0;
bool out10Prev = 1;
bool inPrev = 1;

long prevMill;
bool timvar;
int clockintiming;
int clockinspeed;
int divisionpos;
int brivar;

#define dimming 200
#define brightness 255

#define numled 2
CRGB led[numled];

void setup() {
  pinMode (out1, OUTPUT);
  pinMode (out2, OUTPUT);
  pinMode (out3, OUTPUT);
  pinMode (out4, OUTPUT);
  pinMode (out5, OUTPUT);
  pinMode (out6, OUTPUT);
  pinMode (out7, OUTPUT);
  pinMode (out8, OUTPUT);
  pinMode (in, INPUT_PULLUP);
  pinMode (inDetect, INPUT_PULLUP);
  FastLED.addLeds<NEOPIXEL, 9>(led, numled);
  Serial.begin(2000000);
}

void reading() {
  if (digitalRead(inDetect) == 1) {
    out9State = digitalRead(out9);
    if (out9State == 0 && out9Prev == 0) {
      out9Prev = 1;
    }
    if (out9State == 1 && out9Prev == 1) {
      aniSelect++;
      out9Prev = 0;
    }
    out10State = digitalRead(out10);
    if (out10State == 0 && out10Prev == 0) {
      out10Prev = 1;
    }
    if (out10State == 1 && out10Prev == 1) {
      aniVar++;
      out10Prev = 0;
      timvar = 1;
    } else timvar = 0;
    brivar = brightness;
  }

  if (digitalRead(inDetect) == 0) {
    digitalWrite(out1, inState);
    inState = digitalRead(in);
    if (inState == inPrev) {
      digitalWrite(out1, 0);
      //out1Var++;
      out2Var++;
      out3Var++;
      out4Var++;
      out5Var++;
      out6Var++;
      out7Var++;
      out8Var++;
      out9Var++;
      out10Var++;
      inPrev = !inPrev;
      timvar = 1;
      divisionpos++;
    } else timvar = 0;

    if (out1Var == 2) out1Var = 0;
    if (out2Var == 4) out2Var = 0;
    if (out3Var == 6) out3Var = 0;
    if (out4Var == 8) out4Var = 0;
    if (out5Var == 10) out5Var = 0;
    if (out6Var == 12) out6Var = 0;
    if (out7Var == 14) out7Var = 0;
    if (out8Var == 16) out8Var = 0;
    if (out9Var == 18) out9Var = 0;
    if (out10Var == 20) out10Var = 0;
    if (divisionpos >= 256) divisionpos = 0;
    brivar = brightness - dimming;
  }

}

void timemeasuring() {
  unsigned long curMill = millis();
  if(timvar == 1) {
    clockintiming = curMill - prevMill;
    prevMill = curMill;
  }
  clockinspeed = map(clockintiming, 50, 1000, 255, 10);
}

void write2pixels(int pix1hue, int pix2hue) {
  led[0] = CHSV(pix1hue, 255, 255);
  led[1] = CHSV(pix2hue, 255, 255);
  FastLED.setBrightness(brivar);
  FastLED.show();
}

void loop() {
  timemeasuring();
  write2pixels(divisionpos, clockinspeed);
  inDetectVar = digitalRead(inDetect);
  if (inDetectVar == 1) {
    pinMode (out9, INPUT);
    pinMode (out10, INPUT_PULLUP);
    if (aniSelect == 0) {
      if (aniVar == 0) digitalWrite (out1, 1);
      if (aniVar == 1) digitalWrite (out2, 1);
      if (aniVar == 2) digitalWrite (out3, 1);
      if (aniVar == 3) digitalWrite (out4, 1);
      if (aniVar == 4) digitalWrite (out5, 1);
      if (aniVar == 5) digitalWrite (out6, 1);
      if (aniVar == 6) digitalWrite (out7, 1);
      if (aniVar == 7) digitalWrite (out8, 1);
      if (aniVar == 8) digitalWrite (out1, 0);
      if (aniVar == 9) digitalWrite (out2, 0);
      if (aniVar == 10) digitalWrite (out3, 0);
      if (aniVar == 11) digitalWrite (out4, 0);
      if (aniVar == 12) digitalWrite (out5, 0);
      if (aniVar == 13) digitalWrite (out6, 0);
      if (aniVar == 14) digitalWrite (out7, 0);
      if (aniVar == 15) digitalWrite (out8, 0);
      if (aniVar >= 16) aniVar = 0;
    }
    if (aniSelect == 1) {
      if (aniVar == 0) {
        digitalWrite (out1, 1);
      }
      if (aniVar == 1) {
        digitalWrite (out2, 1);
      }
      if (aniVar == 2) {
        digitalWrite (out3, 1);
      }
      if (aniVar == 3) {
        digitalWrite (out4, 1);
      }
      if (aniVar == 4) {
        digitalWrite (out5, 1);
      }
      if (aniVar == 5) {
        digitalWrite (out6, 1);
      }
      if (aniVar == 6) {
        digitalWrite (out7, 1);
      }
      if (aniVar == 7) {
        digitalWrite (out1, 0);
        digitalWrite (out8, 1);
      }
      if (aniVar == 8) {
        digitalWrite (out2, 0);
      }
      if (aniVar == 9) {
        digitalWrite (out3, 0);
      }
      if (aniVar == 10) {
        digitalWrite (out4, 0);
      }
      if (aniVar == 11) {
        digitalWrite (out5, 0);
      }
      if (aniVar == 12) {
        digitalWrite (out6, 0);
      }
      if (aniVar == 13) {
        digitalWrite (out7, 0);
      }
      if (aniVar == 14) {
        digitalWrite (out8, 0);
      }
      if (aniVar >= 15) aniVar = 0;
    }
    if (aniSelect == 2) {
      if (aniVar == 0) {
        digitalWrite (out1, 1);
      }
      if (aniVar == 1) {
        digitalWrite (out2, 1);
      }
      if (aniVar == 2) {
        digitalWrite (out3, 1);
      }
      if (aniVar == 3) {
        digitalWrite (out4, 1);
      }
      if (aniVar == 4) {
        digitalWrite (out5, 1);
      }
      if (aniVar == 5) {
        digitalWrite (out6, 1);
      }
      if (aniVar == 6) {
        digitalWrite (out1, 0);
        digitalWrite (out7, 1);
      }
      if (aniVar == 7) {
        digitalWrite (out2, 0);
        digitalWrite (out8, 1);
      }
      if (aniVar == 8) {
        digitalWrite (out1, 0);
      }
      if (aniVar == 9) {
        digitalWrite (out2, 0);
      }
      if (aniVar == 8) {
        digitalWrite (out3, 0);
      }
      if (aniVar == 9) {
        digitalWrite (out4, 0);
      }
      if (aniVar == 10) {
        digitalWrite (out5, 0);
      }
      if (aniVar == 11) {
        digitalWrite (out6, 0);
      }
      if (aniVar == 12) {
        digitalWrite (out7, 0);
      }
      if (aniVar == 13) {
        digitalWrite (out8, 0);
      }
      if (aniVar >= 14) aniVar = 0;
    }
    if (aniSelect == 3) {
      if (aniVar == 0) {
        digitalWrite (out1, 1);
      }
      if (aniVar == 1) {
        digitalWrite (out2, 1);
      }
      if (aniVar == 2) {
        digitalWrite (out3, 1);
      }
      if (aniVar == 3) {
        digitalWrite (out4, 1);
      }
      if (aniVar == 4) {
        digitalWrite (out5, 1);
      }
      if (aniVar == 5) {
        digitalWrite (out1, 0);
        digitalWrite (out6, 1);
      }
      if (aniVar == 6) {
        digitalWrite (out2, 0);
        digitalWrite (out7, 1);
      }
      if (aniVar == 7) {
        digitalWrite (out3, 0);
        digitalWrite (out8, 1);
      }
      if (aniVar == 8) {
        digitalWrite (out4, 0);
      }
      if (aniVar == 9) {
        digitalWrite (out5, 0);
      }
      if (aniVar == 10) {
        digitalWrite (out6, 0);
      }
      if (aniVar == 11) {
        digitalWrite (out7, 0);
      }
      if (aniVar == 12) {
        digitalWrite (out8, 0);
      }
      if (aniVar >= 13) aniVar = 0;
    }
    if (aniSelect == 4) {
      if (aniVar == 0) {
        digitalWrite (out1, 1);
      }
      if (aniVar == 1) {
        digitalWrite (out2, 1);
      }
      if (aniVar == 2) {
        digitalWrite (out3, 1);
      }
      if (aniVar == 3) {
        digitalWrite (out4, 1);
      }
      if (aniVar == 4) {
        digitalWrite (out1, 0);
        digitalWrite (out5, 1);
      }
      if (aniVar == 5) {
        digitalWrite (out2, 0);
        digitalWrite (out6, 1);
      }
      if (aniVar == 6) {
        digitalWrite (out3, 0);
        digitalWrite (out7, 1);
      }
      if (aniVar == 7) {
        digitalWrite (out4, 0);
        digitalWrite (out8, 1);
      }
      if (aniVar == 8) {
        digitalWrite (out5, 0);
      }
      if (aniVar == 9) {
        digitalWrite (out6, 0);
      }
      if (aniVar == 10) {
        digitalWrite (out7, 0);
      }
      if (aniVar == 11) {
        digitalWrite (out8, 0);
      }
      if (aniVar >= 12) aniVar = 0;
    }
    if (aniSelect == 5) {
      if (aniVar == 0) {
        digitalWrite (out1, 1);
      }
      if (aniVar == 1) {
        digitalWrite (out2, 1);
      }
      if (aniVar == 2) {
        digitalWrite (out3, 1);
      }
      if (aniVar == 3) {
        digitalWrite (out1, 0);
        digitalWrite (out4, 1);
      }
      if (aniVar == 4) {
        digitalWrite (out2, 0);
        digitalWrite (out5, 1);
      }
      if (aniVar == 5) {
        digitalWrite (out3, 0);
        digitalWrite (out6, 1);
      }
      if (aniVar == 6) {
        digitalWrite (out4, 0);
        digitalWrite (out7, 1);
      }
      if (aniVar == 7) {
        digitalWrite (out5, 0);
        digitalWrite (out8, 1);
      }
      if (aniVar == 9) {
        digitalWrite (out6, 0);
      }
      if (aniVar == 10) {
        digitalWrite (out7, 0);
      }
      if (aniVar == 11) {
        digitalWrite (out8, 0);
      }
      if (aniVar >= 12) aniVar = 0;
    }
    if (aniSelect == 6) {
      if (aniVar == 0) {
        digitalWrite (out1, 1);
      }
      if (aniVar == 1) {
        digitalWrite (out2, 1);
      }
      if (aniVar == 2) {
        digitalWrite (out1, 0);
        digitalWrite (out3, 1);
      }
      if (aniVar == 3) {
        digitalWrite (out2, 0);
        digitalWrite (out4, 1);
      }
      if (aniVar == 4) {
        digitalWrite (out3, 0);
        digitalWrite (out5, 1);
      }
      if (aniVar == 5) {
        digitalWrite (out4, 0);
        digitalWrite (out6, 1);
      }
      if (aniVar == 6) {
        digitalWrite (out5, 0);
        digitalWrite (out7, 1);
      }
      if (aniVar == 7) {
        digitalWrite (out6, 0);
        digitalWrite (out8, 1);
      }
      if (aniVar == 8) {
        digitalWrite (out7, 0);
      }
      if (aniVar == 9) {
        digitalWrite (out8, 0);
      }
      if (aniVar >= 10) aniVar = 0;
    }
    if (aniSelect == 7) {
      if (aniVar == 0) {
        digitalWrite (out1, 1);
      }
      if (aniVar == 1) {
        digitalWrite (out1, 0);
        digitalWrite (out2, 1);
      }
      if (aniVar == 2) {
        digitalWrite (out2, 0);
        digitalWrite (out3, 1);
      }
      if (aniVar == 3) {
        digitalWrite (out3, 0);
        digitalWrite (out4, 1);
      }
      if (aniVar == 4) {
        digitalWrite (out4, 0);
        digitalWrite (out5, 1);
      }
      if (aniVar == 5) {
        digitalWrite (out5, 0);
        digitalWrite (out6, 1);
      }
      if (aniVar == 6) {
        digitalWrite (out6, 0);
        digitalWrite (out7, 1);
      }
      if (aniVar == 7) {
        digitalWrite (out7, 0);
        digitalWrite (out8, 1);
      }
      if (aniVar == 8) {
        digitalWrite (out8, 0);
      }
      if (aniVar >= 9) aniVar = 0;
    }
    if (aniSelect == 8) {
      if (aniVar == 0) {
        digitalWrite (out1, 1);
        digitalWrite (out2, 0);
        digitalWrite (out3, 0);
        digitalWrite (out4, 0);
        digitalWrite (out5, 1);
        digitalWrite (out6, 0);
        digitalWrite (out7, 0);
        digitalWrite (out8, 0);
      }
      if (aniVar == 1) {
        digitalWrite (out1, 0);
        digitalWrite (out2, 1);
        digitalWrite (out3, 0);
        digitalWrite (out4, 0);
        digitalWrite (out5, 0);
        digitalWrite (out6, 1);
        digitalWrite (out7, 0);
        digitalWrite (out8, 0);
      }
      if (aniVar == 2) {
        digitalWrite (out1, 0);
        digitalWrite (out2, 0);
        digitalWrite (out3, 1);
        digitalWrite (out4, 0);
        digitalWrite (out5, 0);
        digitalWrite (out6, 0);
        digitalWrite (out7, 1);
        digitalWrite (out8, 0);
      }
      if (aniVar == 3) {
        digitalWrite (out1, 0);
        digitalWrite (out2, 0);
        digitalWrite (out3, 0);
        digitalWrite (out4, 1);
        digitalWrite (out5, 0);
        digitalWrite (out6, 0);
        digitalWrite (out7, 0);
        digitalWrite (out8, 1);
      }
      if (aniVar >= 4) aniVar = 0;
    }
    /* if (aniSelect == 9) {
         if (aniVar == 0) {
           digitalWrite (out1, 1);
           digitalWrite (out2, 0);
           digitalWrite (out3, 0);
           digitalWrite (out4, 1);
           digitalWrite (out5, 0);
           digitalWrite (out6, 0);
           digitalWrite (out7, 1);
           digitalWrite (out8, 0);
         }
         if (aniVar == 1) {
           digitalWrite (out1, 0);
           digitalWrite (out2, 1);
           digitalWrite (out3, 0);
           digitalWrite (out4, 0);
           digitalWrite (out5, 1);
           digitalWrite (out6, 0);
           digitalWrite (out7, 0);
           digitalWrite (out8, 1);
         }
         if (aniVar == 2) {
           digitalWrite (out1, 1);
           digitalWrite (out2, 0);
           digitalWrite (out3, 1);
           digitalWrite (out4, 0);
           digitalWrite (out5, 0);
           digitalWrite (out6, 1);
           digitalWrite (out7, 0);
           digitalWrite (out8, 0);
         }
         if (aniVar == 3) {
           digitalWrite (out1, 0);
           digitalWrite (out2, 1);
           digitalWrite (out3, 0);
           digitalWrite (out4, 1);
           digitalWrite (out5, 0);
           digitalWrite (out6, 0);
           digitalWrite (out7, 1);
           digitalWrite (out8, 0);
         }
         if (aniVar == 4) {
           digitalWrite (out1, 0);
           digitalWrite (out2, 0);
           digitalWrite (out3, 1);
           digitalWrite (out4, 0);
           digitalWrite (out5, 1);
           digitalWrite (out6, 0);
           digitalWrite (out7, 0);
           digitalWrite (out8, 1);
         }
         if (aniVar == 5) {
           digitalWrite (out1, 1);
           digitalWrite (out2, 0);
           digitalWrite (out3, 0);
           digitalWrite (out4, 1);
           digitalWrite (out5, 0);
           digitalWrite (out6, 1);
           digitalWrite (out7, 0);
           digitalWrite (out8, 0);
         }
         if (aniVar == 6) {
           digitalWrite (out1, 0);
           digitalWrite (out2, 1);
           digitalWrite (out3, 0);
           digitalWrite (out4, 0);
           digitalWrite (out5, 1);
           digitalWrite (out6, 0);
           digitalWrite (out7, 1);
           digitalWrite (out8, 0);
         }
         if (aniVar == 7) {
           digitalWrite (out1, 0);
           digitalWrite (out2, 0);
           digitalWrite (out3, 1);
           digitalWrite (out4, 0);
           digitalWrite (out5, 0);
           digitalWrite (out6, 1);
           digitalWrite (out7, 0);
           digitalWrite (out8, 1);
         }
         if (aniVar == 8) {
           digitalWrite (out1, 1);
           digitalWrite (out2, 0);
           digitalWrite (out3, 0);
           digitalWrite (out4, 1);
           digitalWrite (out5, 0);
           digitalWrite (out6, 0);
           digitalWrite (out7, 1);
           digitalWrite (out8, 0);
         }
         if (aniVar >= 9) aniVar = 0;
      }*/
    if (aniSelect == 9) {
      if (aniVar == 0) {
        digitalWrite (out1, 1);
        digitalWrite (out2, 0);
        digitalWrite (out3, 1);
        digitalWrite (out4, 0);
        digitalWrite (out5, 1);
        digitalWrite (out6, 0);
        digitalWrite (out7, 1);
        digitalWrite (out8, 0);
      }
      if (aniVar == 1) {
        digitalWrite (out1, 0);
        digitalWrite (out2, 1);
        digitalWrite (out3, 0);
        digitalWrite (out4, 1);
        digitalWrite (out5, 0);
        digitalWrite (out6, 1);
        digitalWrite (out7, 0);
        digitalWrite (out8, 1);
      }
      if (aniVar >= 2) aniVar = 0;
    }
    if (aniSelect == 10) aniSelect = 0;
  }


  if (inDetectVar == 0) {
    pinMode (out9, OUTPUT);
    pinMode (out10, OUTPUT);
    if (out2Var <= 2 && out2Var >= 1) digitalWrite(out2, 1);
    else digitalWrite(out2, 0);
    if (out3Var <= 4 && out3Var >= 2) digitalWrite(out3, 1);
    else digitalWrite(out3, 0);
    if (out4Var <= 6 && out4Var >= 3) digitalWrite(out4, 1);
    else digitalWrite(out4, 0);
    if (out5Var <= 8 && out5Var >= 4) digitalWrite(out5, 1);
    else digitalWrite(out5, 0);
    if (out6Var <= 10 && out6Var >= 5) digitalWrite(out6, 1);
    else digitalWrite(out6, 0);
    if (out7Var <= 12 && out7Var >= 6) digitalWrite(out7, 1);
    else digitalWrite(out7, 0);
    if (out8Var <= 14 && out8Var >= 7) digitalWrite(out8, 1);
    else digitalWrite(out8, 0);
    if (out9Var <= 16 && out9Var >= 8) digitalWrite(out9, 1);
    else digitalWrite(out9, 0);
    if (out10Var <= 18 && out10Var >= 9) digitalWrite(out10, 1);
    else digitalWrite(out10, 0);
  }
  reading();
  Serial.print(clockinspeed);
  Serial.print(" , ");
  Serial.print(clockintiming);
  Serial.print(" , ");
  Serial.println(divisionpos);
}
