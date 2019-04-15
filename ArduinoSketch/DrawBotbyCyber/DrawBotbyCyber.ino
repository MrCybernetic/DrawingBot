#include <Servo.h>

// setup servo
int servoPin = A0;
int PEN_DOWN = 0; // angle of servo when pen is down
int PEN_UP = 80;   // angle of servo when pen is up
Servo penServo;

float wheel_dia=59.45;//51.84
float wheel_base=116.0; //      distance between the 2 wheels//103
int steps_rev=128; //           number of steps per revolution (16x gearbox)
int delay_time=5; //           time between steps in ms//5//8


// Stepper sequence org->pink->blue->yel
int L_stepper_pins[] = {6, 7, 8, 9};
int R_stepper_pins[] = {2, 3, 4, 5};

int fwd_mask[][4] =  {{0, 0, 0, 1},
                      {0, 0, 1, 1},
                      {0, 0, 1, 0},
                      {0, 1, 1, 0},
                      {0, 1, 0, 0},
                      {1, 1, 0, 0},
                      {1, 0, 0, 0},
                      {1, 0, 0, 1}};

int rev_mask[][4] =  {{1, 0, 0, 0},
                      {1, 1, 0, 0},
                      {0, 1, 0, 0},
                      {0, 1, 1, 0},
                      {0, 0, 1, 0},
                      {0, 0, 1, 1},
                      {0, 0, 0, 1},
                      {1, 0, 0, 1}};


void setup() {
  for(int pin=0; pin<4; pin++){
    pinMode(L_stepper_pins[pin], OUTPUT);
    digitalWrite(L_stepper_pins[pin], LOW);
    pinMode(R_stepper_pins[pin], OUTPUT);
    digitalWrite(R_stepper_pins[pin], LOW);
  }
  penServo.attach(servoPin);
  Serial.begin(9600);
  Serial.println("setup");
  penup();
  delay(1000);
}


void loop(){ 

right(90.07433);
forward(44.412434);
pendown();
moveWheelsRL(0.3416673*(10.902009+wheel_base/2.0),0.3416673*(10.902009-wheel_base/2.0));
moveWheelsRL(0.3416673*(10.902009+wheel_base/2.0),0.3416673*(10.902009-wheel_base/2.0));
moveWheelsRL(0.34166735*(10.90201+wheel_base/2.0),0.34166735*(10.90201-wheel_base/2.0));
moveWheelsRL(0.3416672*(10.902009+wheel_base/2.0),0.3416672*(10.902009-wheel_base/2.0));
moveWheelsRL(0.34166744*(10.902009+wheel_base/2.0),0.34166744*(10.902009-wheel_base/2.0));
moveWheelsRL(0.34166726*(10.902009+wheel_base/2.0),0.34166726*(10.902009-wheel_base/2.0));
moveWheelsRL(0.34166726*(10.90201+wheel_base/2.0),0.34166726*(10.90201-wheel_base/2.0));
moveWheelsRL(0.3416674*(10.902009+wheel_base/2.0),0.3416674*(10.902009-wheel_base/2.0));
moveWheelsRL(0.3416674*(10.902009+wheel_base/2.0),0.3416674*(10.902009-wheel_base/2.0));
moveWheelsRL(0.3416673*(10.902009+wheel_base/2.0),0.3416673*(10.902009-wheel_base/2.0));
moveWheelsRL(0.34166718*(10.90201+wheel_base/2.0),0.34166718*(10.90201-wheel_base/2.0));
moveWheelsRL(0.34166718*(10.902009+wheel_base/2.0),0.34166718*(10.902009-wheel_base/2.0));
moveWheelsRL(0.34166718*(10.902009+wheel_base/2.0),0.34166718*(10.902009-wheel_base/2.0));
moveWheelsRL(0.3416679*(10.902009+wheel_base/2.0),0.3416679*(10.902009-wheel_base/2.0));
moveWheelsRL(0.34166718*(10.90201+wheel_base/2.0),0.34166718*(10.90201-wheel_base/2.0));
moveWheelsRL(0.3416673*(10.902009+wheel_base/2.0),0.3416673*(10.902009-wheel_base/2.0));
penup();
left(168.75002);
forward(0.0);
left(90.0);
forward(5.8990326);
pendown();
moveWheelsRL(0.50047433*(5.002977-wheel_base/2.0),0.50047433*(5.002977+wheel_base/2.0));
moveWheelsRL(0.5004741*(5.002977-wheel_base/2.0),0.5004741*(5.002977+wheel_base/2.0));
moveWheelsRL(0.5004742*(5.002977-wheel_base/2.0),0.5004742*(5.002977+wheel_base/2.0));
moveWheelsRL(0.5004742*(5.002977-wheel_base/2.0),0.5004742*(5.002977+wheel_base/2.0));
moveWheelsRL(0.34166718*(5.002977-wheel_base/2.0),0.34166718*(5.002977+wheel_base/2.0));
moveWheelsRL(0.34166718*(5.002977-wheel_base/2.0),0.34166718*(5.002977+wheel_base/2.0));
moveWheelsRL(0.34166723*(5.002977-wheel_base/2.0),0.34166723*(5.002977+wheel_base/2.0));
moveWheelsRL(0.34166718*(5.002977-wheel_base/2.0),0.34166718*(5.002977+wheel_base/2.0));
moveWheelsRL(0.34166703*(5.002977-wheel_base/2.0),0.34166703*(5.002977+wheel_base/2.0));
moveWheelsRL(0.34166798*(5.002977-wheel_base/2.0),0.34166798*(5.002977+wheel_base/2.0));
moveWheelsRL(0.34166685*(5.002977-wheel_base/2.0),0.34166685*(5.002977+wheel_base/2.0));
moveWheelsRL(0.34166747*(5.002977-wheel_base/2.0),0.34166747*(5.002977+wheel_base/2.0));

penup();
  done();      // releases stepper motor
  while(1);    // wait for reset
}


// ----- HELPER FUNCTIONS -----------
int step(float distance){
  int steps = round(distance * steps_rev / (wheel_dia * PI));
  return steps;  
}

void left_rotationNTimes(int rotationNumber){
  int steps = rotationNumber * steps_rev;
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}

void right_rotationNTimes(int rotationNumber){
  int steps = rotationNumber * steps_rev;
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}

void forward(float distance){
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
          digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
          digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
}

void backward(float distance){
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
}


void right(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * PI * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
  delay(10);
}


void left(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * PI * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
  delay(10);
}

void moveWheelsRL(float Rdist, float Ldist) {
  bool RDirection = Rdist>=0;
  bool LDirection = Ldist>=0;
  int stepsR = step(abs(Rdist));
  int stepsL = step(abs(Ldist));
  Serial.println("Rdist "+String(Rdist));
  Serial.println("Ldist "+String(Ldist));
  Serial.println("stepsR "+String(stepsR));
  Serial.println("stepsL "+String(stepsL));
  int stepsMax = max(stepsR,stepsL);
  int stepsMin = min(stepsR,stepsL);
  int ratio = round(float(stepsMax)/float(stepsMin));
  Serial.println("L dir "+String(LDirection));
  Serial.println("R dir "+String(RDirection));
  for(int step=0; step<stepsMax; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        if (stepsMax==stepsR) {
          if (RDirection) {
            digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
          } else {
            digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
          }
          if (step%ratio==0 && step<stepsMin) {
            if (LDirection) {
              digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
            } else {
              digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
            }
          }
        }
        if (stepsMax==stepsL) {
          if (LDirection) {
            digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
          } else {
            digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
          }
          if (step%ratio==0 && step<stepsMin) {
            if (RDirection) {
              digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
            } else {
              digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
            }
          }
        }
      }
      delay(delay_time);
    } 
  }   
  delay(10);
}


void done(){ // unlock stepper to save battery
  for(int mask=0; mask<8; mask++){
    for(int pin=0; pin<4; pin++){
      digitalWrite(R_stepper_pins[pin], LOW);
      digitalWrite(L_stepper_pins[pin], LOW);
    }
    delay(delay_time);
  }
}


void penup(){
  delay(250);
  Serial.println("PEN_UP()");
  penServo.write(PEN_UP);
  delay(250);
}


void pendown(){
  delay(250);  
  Serial.println("PEN_DOWN()");
  penServo.write(PEN_DOWN);
  delay(250);
}
