#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

const int laserPin = 1;

void setup() {
  for (int i = 0; i < 7; ++i) {
	  pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
    

  AFMS.begin();
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(10);  // 10 rpm   

  Serial.begin(115200);
  Serial.println("Start");
}

int counter = 0;

void loop() {
  Serial.print("Step ");
  Serial.println(counter++);
  myMotor->step(10, FORWARD, MICROSTEP); 
  myMotor->step(10, BACKWARD, MICROSTEP);
  delay(1000);
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
}
