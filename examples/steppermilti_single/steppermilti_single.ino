/*
 * StepperMulti example
 * Async stepper control
 *
 * (c)2024 by Aleksandr.ru
 * @url http://aleksandr.ru
*/

#define LEDPIN 13
#define LEDDELAY 500

#define MOTORPIN1 6
#define MOTORPIN2 7
#define MOTORPIN3 8
#define MOTORPIN4 9

#define STEPS 450
#define SPEED 30

#include <StepperMulti.h>

StepperMulti myStepper(STEPS, MOTORPIN1, MOTORPIN2, MOTORPIN3, MOTORPIN4);

int direction1 = 1;
bool ledon = false;

unsigned long previousMillis = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(LEDPIN, OUTPUT);
    digitalWrite(LEDPIN, LOW);

    myStepper.setSpeed(SPEED);
}

void loop()
{
    unsigned long currentMillis = millis();

    if (millis() - previousMillis >= LEDDELAY) {
        previousMillis = currentMillis;
        ledon = !ledon;
        digitalWrite(LEDPIN, ledon ? HIGH : LOW);
    }

    myStepper.step();

    if (!myStepper.isMoving()) {
        direction *= -1;
        myStepper.start(direction * STEPS);
        Serial.println("Stepper restart");
    }
}
