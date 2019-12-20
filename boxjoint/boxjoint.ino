
#include "BasicStepperDriver.h"

#define PUL 52
#define DIR 53
#define EN 50
#define LLIMIT 49
#define HLIMIT 48
#define FREE_F 47
#define FREE_R 46
#define MOTOR_STEPS 400
#define RPM 120
#define MICROSTEPS 1
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000


BasicStepperDriver stepper(MOTOR_STEPS, DIR, PUL);

char user_input;

void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(EN, OUTPUT);

  pinMode(LLIMIT, INPUT);
  pinMode(HLIMIT, INPUT);
  pinMode(FREE_F, INPUT);
  pinMode(FREE_R, INPUT);

  stepper.begin(RPM, MICROSTEPS);
  stepper.setEnableActiveState(HIGH);
  stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

  Serial.begin(115200);
}

void loop() {

  while(Serial.available()){
      user_input = Serial.read();
      if (user_input =='f')
      {
        Serial.println("Doing F steps");
        init_steps(1200, HIGH);
      }else if (user_input =='r')
      {
        Serial.println("Doing R steps");
        init_steps(1200, LOW);
      }
      else if (user_input=='d')
      {
        digitalWrite(EN, LOW);
      }
      else if (user_input=='m')
      {
        motor_steps();
      }
  }

  if check_limits(){
    set_free();
    do_step();
  }


}

double pulse_width=250;
int gsteps = 0;

void set_free(){
    if digitalRead(FREE_F){
        init_step(10, HIGH);
    } digitalRead(FREE_R) {
        init_step(10, LOW);
    }
}

bool check_limits(){
    return HIGH;
//     return digitalRead(LLIMIT) || digitalRead(HLIMIT);
}

void do_step(){
    if (gsteps>0){
        do_single_step();
        gsteps--;
    }
}

void init_step(int steps, bool dir){
    gsteps = steps;
    digitalWrite(EN, HIGH);
    delayMicroseconds(5);
    digitalWrite(DIR, dir);
    delayMicroseconds(5);
}

void do_single_step(){
    digitalWrite(PUL, HIGH);
    delayMicroseconds(pulse_width);
    digitalWrite(PUL, LOW);
    delayMicroseconds(pulse_width);
}


void motor_steps(){
    stepper.enable();
    stepper.rotate(720);
    stepper.disable();
}


// void do_steps(int steps, bool dir){
//   digitalWrite(EN, HIGH);
//   digitalWrite(DIR, dir);
//   delayMicroseconds(5);
//
//   for(int i=0; i<steps; i++)
//   {
//     digitalWrite(PUL, HIGH);
//     delayMicroseconds(pulse_width);
//     digitalWrite(PUL, LOW);
//     delayMicroseconds(pulse_width);
//   }
// }
