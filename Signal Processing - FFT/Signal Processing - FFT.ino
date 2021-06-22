int n, N, k, f;
int x[100];
unsigned long dt, t0 = 0; 
double Re=0, Im=0, Xk;
int flag;
void setup() {
  Serial.begin(115200);
  Serial.println("Enter number of N, f(Hz)");
  while (Serial.available() == 0);
  N = Serial.parseInt();
  f = Serial.parseInt();
  dt = 1000./f;
  n = 0;
}


void loop() {
    if(n <= N){
      if((millis() - t0) >= dt){
        x[n] = analogRead(A0);
        t0 = millis();
        n++;
      }
    }
    
    if(n == N){
      for(k = 0; k < N; k++){
        for(n = 0; n < N; n++){
          Re = Re + x[n]*cos(-2*PI*k*n/N);
          Im = Im+ x[n]*sin(-2*PI*k*n/N);
        }
        Xk = sqrt(pow(Re,2) + pow(Im,2));
        Serial.println(Xk);
        Re = 0;
        Im = 0;
      }
    }
}
