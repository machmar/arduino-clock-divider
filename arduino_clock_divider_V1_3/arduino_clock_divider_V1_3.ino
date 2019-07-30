#include <FastLED.h>

#define out1 12
#define out2 2
#define out3 3
#define out4 4
#define out5 5
#define out6 6
#define out7 7
#define out8 8
#define out9 13
#define out10 10
#define in 11
#define inDetect 14
#define lightS 15
#define primeS 16
#define edgeS 17
#define gatetriggerS 18
#define rst10S 19
int out1ClockVar = 0;
int out2ClockVar = 0;
int out3ClockVar = 0;
int out4ClockVar = 0;
int out5ClockVar = 0;
int out6ClockVar = 0;
int out7ClockVar = 0;
int out8ClockVar = 0;
int out9ClockVar = 0;
int out10ClockVar = 0;
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
long out1PMic = 0;
long out2PMic = 0;
long out3PMic = 0;
long out4PMic = 0;
long out5PMic = 0;
long out6PMic = 0;
long out7PMic = 0;
long out8PMic = 0;
long out9PMic = 0;
long out10PMic = 0;
int out1Division = 1;
int out2Division = 2;
int out3Division = 3;
int out4Division = 4;
int out5Division = 5;
int out6Division = 6;
int out7Division = 7;
int out8Division = 8;
int out9Division = 9;
int out10Division = 10;
int aniVar = 0;
int aniSelect = 0;
int inDetectVar = 1;
int inState = 0;
bool out9State = 0;
bool out9Prev = 1;
bool out10State = 0;
bool out10Prev = 1;
bool inPrev = 1;
int pwm = 10000;
#define pwmDefault 10000

long prevMill;
bool timvar;
int clockintiming;
int clockinspeed8bin;
int divisionpos;
int brivar;

#define dimming 0
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
  pinMode (lightS, INPUT_PULLUP);
  pinMode (primeS, INPUT_PULLUP);
  pinMode (edgeS, INPUT_PULLUP);
  pinMode (gatetriggerS, INPUT_PULLUP);
  pinMode (rst10S, INPUT_PULLUP);
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
      divisionpos++;
    } else timvar = 0;
    brightness;
  }

  if (digitalRead(inDetect) == 0) {
    inState = digitalRead(in);
    if (inState == inPrev) {
      if (digitalRead(edgeS) == 1 || (digitalRead(edgeS) == 0 && inState == 1)) {
        out1ClockVar++;
        out2ClockVar++;
        out3ClockVar++;
        out4ClockVar++;
        out5ClockVar++;
        out6ClockVar++;
        out7ClockVar++;
        out8ClockVar++;
        out9ClockVar++;
        out10ClockVar++;
      }
      inPrev = !inPrev;
      timvar = 1;
      divisionpos++;
    } else timvar = 0;
    if (divisionpos >= 256) divisionpos = 0;
    brivar = brightness - dimming;
  }

}

void timemeasuring() {
  unsigned long curMill = micros();
  if (timvar == 1) {
    clockintiming = curMill - prevMill;
    prevMill = curMill;
  }
  clockinspeed8bin = map(clockintiming, 50000, 1000000, 255, 10);
}

void write2pixels(int pix1hue, int pix2hue) {
  led[0] = CHSV(pix1hue, 255, 255);
  led[1] = CHSV(pix2hue, 255, 255);
  FastLED.setBrightness(brivar);
  FastLED.show();
}

void loop() {
  unsigned long CMic = micros();
  if (digitalRead(lightS) == 0) {
    write2pixels(divisionpos, clockinspeed8bin);
    timemeasuring();
  }
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
    if (analogRead(gatetriggerS) > 1000) {
      if (out1ClockVar >= out1Division) {
        out1Var = !out1Var;
        out1ClockVar = 0;
      }
      if (out2ClockVar >= out2Division) {
        out2Var = !out2Var;
        out2ClockVar = 0;
      }
      if (out3ClockVar >= out3Division) {
        out3Var = !out3Var;
        out3ClockVar = 0;
      }
      if (out4ClockVar >= out4Division) {
        out4Var = !out4Var;
        out4ClockVar = 0;
      }
      if (out5ClockVar >= out5Division) {
        out5Var = !out5Var;
        out5ClockVar = 0;
      }
      if (out6ClockVar >= out6Division) {
        out6Var = !out6Var;
        out6ClockVar = 0;
      }
      if (out7ClockVar >= out7Division) {
        out7Var = !out7Var;
        out7ClockVar = 0;
      }
      if (out8ClockVar >= out8Division) {
        out8Var = !out8Var;
        out8ClockVar = 0;
      }
      if (out9ClockVar >= out9Division) {
        out9Var = !out9Var;
        out9ClockVar = 0;
      }
      if (out10ClockVar >= out10Division) {
        out10Var = !out10Var;
        out10ClockVar = 0;
      }
    }
    if (analogRead(gatetriggerS) < 1000) {
      if (analogRead(gatetriggerS) < 20) pwm = pwmDefault;
      if (analogRead(gatetriggerS) > 20 && analogRead(gatetriggerS) < 1000) {
        timemeasuring();
        if (clockinspeed8bin > 100) pwm = map(gatetriggerS, 25, 995, 10000, 800000);
        if (clockinspeed8bin < 100) pwm = map(gatetriggerS, 25, 995, 100, 10000);
        
      }
      unsigned long CMic = micros();
      if (out1ClockVar >= out1Division) {
        out1Var = 1;
        out1PMic = CMic;
        out1ClockVar = 0;
      }
      if (out2ClockVar >= out2Division) {
        out2Var = 1;
        out2PMic = CMic;
        out2ClockVar = 0;
      }
      if (out3ClockVar >= out3Division) {
        out3Var = 1;
        out3PMic = CMic;
        out3ClockVar = 0;
      }
      if (out4ClockVar >= out4Division) {
        out4Var = 1;
        out4PMic = CMic;
        out4ClockVar = 0;
      }
      if (out5ClockVar >= out5Division) {
        out5Var = 1;
        out5PMic = CMic;
        out5ClockVar = 0;
      }
      if (out6ClockVar >= out6Division) {
        out6Var = 1;
        out6PMic = CMic;
        out6ClockVar = 0;
      }
      if (out7ClockVar >= out7Division) {
        out7Var = 1;
        out7PMic = CMic;
        out7ClockVar = 0;
      }
      if (out8ClockVar >= out8Division) {
        out8Var = 1;
        out8PMic = CMic;
        out8ClockVar = 0;
      }
      if (out9ClockVar >= out9Division) {
        out9Var = 1;
        out9PMic = CMic;
        out9ClockVar = 0;
      }
      if (out10ClockVar >= out10Division) {
        out10Var = 1;
        out10PMic = CMic;
        out10ClockVar = 0;
      }
      if (out1Var == 1 && CMic - out1PMic >= pwm) out1Var = 0;
      if (out2Var == 1 && CMic - out2PMic >= pwm) out2Var = 0;
      if (out3Var == 1 && CMic - out3PMic >= pwm) out3Var = 0;
      if (out4Var == 1 && CMic - out4PMic >= pwm) out4Var = 0;
      if (out5Var == 1 && CMic - out5PMic >= pwm) out5Var = 0;
      if (out6Var == 1 && CMic - out6PMic >= pwm) out6Var = 0;
      if (out7Var == 1 && CMic - out7PMic >= pwm) out7Var = 0;
      if (out8Var == 1 && CMic - out8PMic >= pwm) out8Var = 0;
      if (out9Var == 1 && CMic - out9PMic >= pwm) out9Var = 0;
      if (out10Var == 1 && CMic - out10PMic >= pwm) out10Var = 0;
    }
    if (digitalRead(primeS) == 1) {
      out1Division = 1;
      out2Division = 2;
      out3Division = 3;
      out4Division = 4;
      out5Division = 5;
      out6Division = 6;
      out7Division = 7;
      out8Division = 8;
      out9Division = 9;
      out10Division = 10;
    }
    if (digitalRead(primeS) == 0) {
      out1Division = 1;
      out2Division = 2;
      out3Division = 3;
      out4Division = 5;
      out5Division = 7;
      out6Division = 11;
      out7Division = 13;
      out8Division = 17;
      out9Division = 19;
      out10Division = 23;
    }
    if (digitalRead(rst10S) == 1) {
      pinMode (out10, OUTPUT);
      digitalWrite(out10, out10Var);
    }
    if (digitalRead(rst10S) == 0) {
      pinMode (out10, INPUT);
      if (digitalRead(out10) == 1) {
        out1ClockVar = 0;
        out2ClockVar = 0;
        out3ClockVar = 0;
        out4ClockVar = 0;
        out5ClockVar = 0;
        out6ClockVar = 0;
        out7ClockVar = 0;
        out8ClockVar = 0;
        out9ClockVar = 0;
        out10ClockVar = 0;
        out1Var = 0;
        out2Var = 0;
        out3Var = 0;
        out4Var = 0;
        out5Var = 0;
        out6Var = 0;
        out7Var = 0;
        out8Var = 0;
        out9Var = 0;
        out10Var = 0;
      }
    }
  }
  reading();
  Serial.print(digitalRead(lightS));
  Serial.print(" , ");
  Serial.print(digitalRead(primeS));
  Serial.print(" , ");
  Serial.print(analogRead(gatetriggerS));
  Serial.print(" , ");
  Serial.print(digitalRead(edgeS));
  Serial.print(" , ");
  Serial.println(clockintiming);
  digitalWrite(out1, out1Var);
  digitalWrite(out2, out2Var);
  digitalWrite(out3, out3Var);
  digitalWrite(out4, out4Var);
  digitalWrite(out5, out5Var);
  digitalWrite(out6, out6Var);
  digitalWrite(out7, out7Var);
  digitalWrite(out8, out8Var);
  digitalWrite(out9, out9Var);
}
