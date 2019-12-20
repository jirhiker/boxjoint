#define PUL 52
#define DIR 53
#define EN 50

char user_input;
void setup() {
  // put your setup code here, to run once:
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(EN, OUTPUT);
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()){
      user_input = Serial.read();
      if (user_input =='1')
      {
        Serial.println("Doing F steps");
        stepper(3*400, HIGH);
      }else if (user_input =='2')
      {
        Serial.println("Doing R steps");
        stepper(3*400, LOW);
      }
  }
}

double pulse_width=200;
void stepper(int steps, bool dir){
  digitalWrite(EN, HIGH);
  digitalWrite(DIR, dir);
  delayMicroseconds(5);

  
  for(int i=0; i<steps; i++)
  {
    digitalWrite(PUL, HIGH);
    delayMicroseconds(pulse_width);
    digitalWrite(PUL, LOW);
    delayMicroseconds(pulse_width);
  }

  //digitalWrite(EN, LOW);
}
