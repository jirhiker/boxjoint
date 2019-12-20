
#include <AccelStepper.h>

#define PUL 52
#define DIR 53
#define EN 50


//AccelStepper stepper=AccelStepper(1, PUL, DIR);

char user_input;
void setup() {
  //stepper.setEnablePin(EN);
  //stepper.setMaxSpeed(1000);
  //stepper.setSpeed(50);
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
      if (user_input =='f')
      {
        Serial.println("Doing F steps");
        do_steps(3*400, HIGH);
      }else if (user_input =='r')
      {
        Serial.println("Doing R steps");
        do_steps(3*400, LOW);
        
      }
      else if (user_input=='d')
      {
        digitalWrite(EN, LOW);
      }
      else if (user_input=='3')
      {
        Serial.println("Doing run");
        //stepper.runSpeed();
        delay(5000);
        //stepper.stop();
        Serial.println("Run finished");
      }
  }
}

double pulse_width=250;
void do_steps(int steps, bool dir){
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
