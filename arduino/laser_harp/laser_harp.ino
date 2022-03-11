#include <Wire.h>
#include <Adafruit_MotorShield.h>

const int motorPort = 2;
const int motorSpeed = 55;
const int motorSwing = 20;
const int laserPin = 7;
const int beamCount = 4;
const long baudRate = 115200;
const int lightSensorPin = A0;
const int interBeamDelay = 100;

int loopCounter = 0;

const bool motorEnabled = true;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Connect a stepper motor with 200 steps per revolution (1.8 degree) to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, motorPort);

void setup() {
	// First set the first 8 pins as outputs and drive them low
	for (int i = 0; i < 7; ++i) {
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}

	AFMS.begin();
	myMotor->setSpeed(motorSpeed);

	Serial.begin(baudRate);
	Serial.println("Start");
}

void loop() {
	Serial.print("Step ");
	Serial.println(loopCounter++);
	
	for (int i = 0; i < beamCount; ++i) {
		if (motorEnabled) {
			myMotor->step(motorSwing/beamCount, FORWARD, DOUBLE);
		}
		digitalWrite(laserPin, HIGH);
		int lightIntensity = analogRead(A0);
		Serial.println(lightIntensity);
		delay(interBeamDelay);
		digitalWrite(laserPin, LOW);
	}
	for (int i = 0; i < beamCount; ++i) {
		if (motorEnabled) {
			myMotor->step(motorSwing/beamCount, BACKWARD, DOUBLE);
		}
		digitalWrite(laserPin, HIGH);
		delay(interBeamDelay);
		digitalWrite(laserPin, LOW);
	}
	delay(1000);
}
