/*
 * StepperMulti example
 * Async stepper control using MX1508 driver or similar
 * To use this with DRV8833 or similar add code for "Enable" pins
 *
 * (c)2024 by Aleksandr.ru
 * @url http://aleksandr.ru
*/

#define LEDPIN 13
#define LEDDELAY 300

#define MOTORPIN1 6
#define MOTORPIN2 7
#define MOTORPIN3 8
#define MOTORPIN4 9

#define STEPS 450 // Change this to the number of steps on your motor
#define SPEED 30  // Change this to desired speed of your motor

#include <StepperMulti.h>

StepperMulti myStepper(STEPS, MOTORPIN1, MOTORPIN2, MOTORPIN3, MOTORPIN4);

int direction = 1;
bool ledon = false;

unsigned long previousMillis = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(LEDPIN, OUTPUT);

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
        // For MX1508 or similar driver
        // stop() must be called when moving is complete
        // to release motor pins and prevent overheating
        myStepper.stop();

        // Consider to add some time to cool down hardware
        // but don't use delay() because it's blocking:
        // delay(1000); // This will freeze flashing led

        direction *= -1;
        myStepper.start(direction * STEPS * 2);
        Serial.println("Stepper restart");
    }
}
