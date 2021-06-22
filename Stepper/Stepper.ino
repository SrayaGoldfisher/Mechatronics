//Digital control of stepper motor
//Familiarity with different ways of operating a stepper motor
//Control of motion parameters of stepper motor
//UART Communication


short FullSteps[4] = {B00000001,
                      B00000010,
                      B00000100,
                      B00001000};

short HalfSteps[8] = {B00000001,
                B00000011,
                B00000010,
                B00000110,
                B00000100,
                B00001100,
                B00001000,
                B00001001};

short Wave[4] = {B00000011,
                B00000110,
                B00001100,
                B00001001};
               
int steps,mode;
float vel;
int i = 0,dir, j;
unsigned long dt,t0 = 0;

void setup() {
  DDRB = B11111111;
  Serial.begin(115200);
  Serial.print("Enter number of steps, dir, mode [0-full,1-half,2-wave], vel");
  while (Serial.available() == 0);
  steps = Serial.parseInt();
  dir = Serial.parseInt();
  mode = Serial.parseInt();
  vel = Serial.parseFloat();
  dt =(unsigned long) vel;
}

void loop() {
  if(mode == 0) {
    move(FullSteps, 4);
  }
  if(mode == 1) {
    move(HalfSteps, 8);
  }
  if(mode == 2) {
    move(Wave, 4);
  }
}

void move(short StepsType[], int len){
  // Serial.println(i);
  if(i < steps) {
    if((millis() - t0) > dt) {
      if(dir == 1) {
        PORTB = StepsType[i%len];
      }
      else {
        PORTB = StepsType[(len - 1) - i%len];
      }
     i++;
     t0 = millis();     
  }
 }
}


/*
  // Serial.println(i);
  if(i < steps) {
    if ((millis() - t0) > dt) {
      if(dir == 1) {
        PORTB = FullSteps[i%4];
      }
      else {
        PORTB = FullSteps[3 - i%4];
      }
     i++;
     t0 = millis();     
    }
  }
*/

