/*
 * StepperMulti example
 * Control two steppers simultaneously with buttons
 * Steppers are driven by MX1508 drivers or similar
 * To use this with DRV8833 or similar add code for "Enable" pins
 *
 * (c)2024 by Aleksandr.ru
 * @url http://aleksandr.ru
*/

#define LEDPIN 13

#define BUTTON1_PIN 3
#define BUTTON2_PIN 4

#define MOTOR1_PIN1 6
#define MOTOR1_PIN2 7
#define MOTOR1_PIN3 8
#define MOTOR1_PIN4 9

#define MOTOR2_PIN1 A0
#define MOTOR2_PIN2 A1
#define MOTOR2_PIN3 A2
#define MOTOR2_PIN4 A3

#define STEPS 450 // Change this to the number of steps on your motor
#define SPEED 30  // Change this to desired speed of your motor

#include <StepperMulti.h>

StepperMulti myStepper1(STEPS, MOTOR1_PIN1, MOTOR1_PIN2, MOTOR1_PIN3, MOTOR1_PIN4);
StepperMulti myStepper2(STEPS, MOTOR2_PIN1, MOTOR2_PIN2, MOTOR2_PIN3, MOTOR2_PIN4);

int direction1 = -1;
int direction2 = -1;

void setup()
{
    Serial.begin(9600);

    myStepper1.setSpeed(SPEED);
    myStepper2.setSpeed(SPEED);

    // Buttons are connected to digital pins and ground
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);

    pinMode(LEDPIN, OUTPUT);
}

void loop()
{
    myStepper1.step();
    myStepper2.step();

    // No need to debounce button input
    // because when stepper in moving button takes no action
    if (!myStepper1.isMoving() && !digitalRead(BUTTON1_PIN)) {
        direction1 *= -1;
        myStepper1.start(direction1 * STEPS * 2);
        Serial.print("Stepper 1 start: ");
        Serial.println(direction1 > 0 ? "forwrd" : "backward");
    }
    else if (!myStepper1.isMoving()) {
        // For MX1508 or similar driver
        // stop() must be called when moving is complete
        // to release motor pins and prevent overheating
        myStepper1.stop();
    }

    // No need to debounce button input
    // because when stepper in moving button takes no action
    if (!myStepper2.isMoving() && !digitalRead(BUTTON2_PIN)) {
        direction2 *= -1;
        myStepper2.start(direction2 * STEPS * 2);
        Serial.print("Stepper 2 start: ");
        Serial.println(direction2 > 0 ? "forwrd" : "backward");
    }
    else if (!myStepper2.isMoving()) {
        // For MX1508 or similar driver
        // stop() must be called when moving is complete
        // to release motor pins and prevent overheating
        myStepper2.stop();
    }

    if (myStepper1.isMoving() || myStepper2.isMoving()) {
        digitalWrite(LEDPIN, HIGH);
    }
    else {
        digitalWrite(LEDPIN, LOW);
    }
}
