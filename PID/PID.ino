const int Pin1 =  2;
const int Pin2 =  3;
float e_pres = 0, e_prev, Kp, Ki, Kd, teta_d, teta, t0, U, P, I, D;
int i,encoder = 0;

void setup() {
  Serial.begin(2000000);
  attachInterrupt(0, NumOfPulse_CHA, CHANGE);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.println("Enter teta_d, Kp, Ki, Kd");
  while (Serial.available() == 0);
  teta_d = Serial.parseInt();
  Kp = Serial.parseFloat();
  Ki = Serial.parseFloat();
  Kd = Serial.parseFloat() * 10000;
}

void NumOfPulse_CHA() {
    if(digitalRead(Pin1)) {
      if(digitalRead(Pin2)) {
          encoder++;
      }
      else {
         encoder--;
      }
    }
    else {
      if(digitalRead(Pin2)) {
          encoder--;
      }
      else {
         encoder++;
      }
    }
}

void loop() {
  if(Serial.available()) {
      teta_d = Serial.parseInt();
      t0 = millis();
  }
  teta = encoder*0.19125;
  e_prev = e_pres;
  e_pres = teta_d - teta;

  P = Kp * e_pres;
  I = Ki * e_pres;
  D = Kd * (e_pres - e_prev);
  U = P + I + D;
  if(U >= 0) {
    U = min(U, 255);
    analogWrite(5, U);
    analogWrite(6, 0);
  }
  else {
    U = abs(U);
    U = min(U, 255);
    analogWrite(6, U);
    analogWrite(5, 0);
  }
  //Serial.println(U);
  if((millis() - t0) < 1000) {
    Serial.print(millis());
    Serial.print('\t');
    Serial.println(teta);
  }
}
