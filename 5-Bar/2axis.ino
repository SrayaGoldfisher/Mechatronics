//Activation of a 5-Bar robotic system with 2 degrees of freedom
//The system is driven by connection of 2 PID systems controlled by microcontroller


const int CHA1 =  2;
const int CHB1 =  7;
const int CHA2 =  3;
const int CHB2 =  8;
float e_pres = 0, e_prev, Kp, Ki, Kd, teta_d, teta, t0, U, P, I, D;
int i, encoderL, encoderR, PulseRight, PulseLeft, MovementRight, MovementLeft;
float l0, l1, l2, l3, l4, l5, l6, theta1, theta6, dt = 0.1, x = 0, y = 0 ,tet;
float angels[4] = {0};
const float Pi = 3.14159;
//setup:
//left motor - motor 5,6 encoder 2, 7. 2 interrupte. pin 5 to pin 1 in driver
//right motor - motor 9,10 encoder 3, 8. 3 interrupte. pin 9 to pin 3 in driver
void setup() {
  Serial.begin(2000000);
  attachInterrupt(0, NumOfPulseL, CHANGE);
  attachInterrupt(1, NumOfPulseR, CHANGE);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
//  Serial.println("Kp, Ki, Kd");
//  while (Serial.available() == 0);
//  Kp = Serial.parseFloat();
//  Ki = Serial.parseFloat();
//  Kd = Serial.parseFloat() * 10000;
  Kp=20; Ki=20; Kd=0;
//  Serial.println("x, y");
  encoderL = encoderR = 0;
}

void NumOfPulseL() {
    if(digitalRead(CHA1)) {
      if(digitalRead(CHB1)) {
          encoderL++;
      }
      else {
         encoderL--;
      }
    }
    else {
      if(digitalRead(CHB1)) {
          encoderL--;
      }
      else {
         encoderL++;
      }
    }
}

void NumOfPulseR() {
    if(digitalRead(CHA2)) {
      if(digitalRead(CHB2)) {
          encoderR++;
      }
      else {
         encoderR--;
      }
    }
    else {
      if(digitalRead(CHB2)) {
          encoderR--;
      }
      else {
         encoderR++;
      }
    }
}

float r2d(float rad){
  return rad*180/Pi;
}

void PID(float teta_d, int Pulse, int output1, int output2) {
  t0 = millis();
  teta = Pulse*0.19125;
  e_prev = e_pres;
  e_pres = teta_d - teta;

  P = Kp * e_pres;
  I = Ki * e_pres;
  D = Kd * (e_pres - e_prev);
  U = P + I + D;
  if(U >= 0) {
    U = min(U, 255);
    analogWrite(output1, U);
    analogWrite(output2, 0);
  }
  else {
    U = abs(U);
    U = min(U, 255);
    analogWrite(output2, U);
    analogWrite(output1, 0);
  }
}

bool inverse_kinematics(float x, float y, float &ang1_1, float &ang2_1, float &ang1_2, float &ang2_2) {
  l0 = 160;
  l1 = sqrt(x * x + y * y);
  l2 = 60;
  l5 = 60;
  l3 = 140;
  l4 = 140;
  theta1 = atan2(y, x);
  ang1_1 = theta1 + acos((l3*l3 - l1 * l1 - l2 * l2) / (-2 * l1*l2));
  ang1_2 = theta1 - acos((l3*l3 - l1 * l1 - l2 * l2) / (-2 * l1*l2));
  l6 = sqrt((l0 - x)*(l0 - x) + (y)*(y));
  theta6 = atan2((-l1 * sin(theta1)), (l0 - l1 * cos(theta1)));
  ang2_1 = theta6 + acos((l4*l4 - l6 * l6 - l5 * l5) / (2 * l6*l5));
  ang2_2 = theta6 - acos((l4*l4 - l6 * l6 - l5 * l5) / (2 * l6*l5));

  if (l1 < (l2 + l3) && l6 < (l4 + l5) && l1 > abs(l2 - l3) && l6 > abs(l4 - l5)){
    return false;
  }
  else {
    return true;
  }
}

void loop() {
  if(Serial.available()) {
    x = Serial.parseFloat();
    y = Serial.parseFloat();
    while(Serial.available())Serial.read();
      Serial.print(angels[0]);
      Serial.print("\n");
      Serial.print(angels[1]);
      Serial.print("\n");
  }

  if(x != 0 && y != 0) {
    if(!inverse_kinematics(x, y, angels[0], angels[1], angels[2], angels[3])){   
      PID(r2d(angels[0]), encoderL, 5, 6);
      PID(r2d(angels[1]), encoderR, 9, 10);
    }
  }
  else{
     PID(0, encoderL, 5, 6);
     PID(0, encoderR, 9, 10);
  }
//  Serial.print(encoderL * 0.19125);
//  Serial.print("\n");
//  Serial.print(r2d(angels[0]));
//  Serial.print("\n");
}
