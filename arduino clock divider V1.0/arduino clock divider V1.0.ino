int out1 = 11;
int out2 = 2;
int out3 = 3;
int out4 = 4;
int out5 = 5;
int out6 = 6;
int out7 = 7;
int out8 = 8;
int out9 = 9;
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
int in = 12;
int inState = 0;
bool inPrev = 1;
bool stepCheck = 0;


void setup() {

  pinMode (out1, OUTPUT);
  pinMode (out2, OUTPUT);
  pinMode (out3, OUTPUT);
  pinMode (out4, OUTPUT);
  pinMode (out5, OUTPUT);
  pinMode (out6, OUTPUT);
  pinMode (out7, OUTPUT);
  pinMode (out8, OUTPUT);
  pinMode (out9, OUTPUT);
  pinMode (out10, OUTPUT);
  pinMode (in, INPUT_PULLUP);

  //Serial.begin(2000000);

}

void reading() {
  inState = digitalRead(in);
  /*Serial.print(out1Var);
    Serial.print(out2Var);
    Serial.print(out3Var);
    Serial.print(out4Var);
    Serial.print(out5Var);
    Serial.print(out6Var);
    Serial.print(out7Var);
    Serial.print(out8Var);
    Serial.print(out9Var);
    Serial.println(out10Var);*/
  if (inState == 0 && inPrev == 0) {
    digitalWrite(out1, 0);
    out1Var++;
    out2Var++;
    out3Var++;
    out4Var++;
    out5Var++;
    out6Var++;
    out7Var++;
    out8Var++;
    out9Var++;
    out10Var++;
    inPrev = 1;
  }
  if (inState == 1 && inPrev == 1) {
    digitalWrite(out1, 1);
    out1Var++;
    out2Var++;
    out3Var++;
    out4Var++;
    out5Var++;
    out6Var++;
    out7Var++;
    out8Var++;
    out9Var++;
    out10Var++;
    inPrev = 0;
    stepCheck = 1;
  }
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

}

void loop() {
  reading();
  if (stepCheck == 0) {
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
  }
  /*if (out1Var <= 1/* && out10Var >=1) c
    else digitalWrite(out1, 0);*/
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
