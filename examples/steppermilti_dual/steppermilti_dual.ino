/*
 * StepperMulti example
 * Drive two steppers simultaneously
 *
 * (c)2024 by Aleksandr.ru
 * @url http://aleksandr.ru
*/

#define MOTORPIN11 6
#define MOTORPIN12 7
#define MOTORPIN13 8
#define MOTORPIN14 9

#define MOTORPIN21 A0
#define MOTORPIN22 A1
#define MOTORPIN23 A2
#define MOTORPIN24 A3

#define STEPS 450
#define SPEED 30

#include <StepperMulti.h>

StepperMulti myStepper1(STEPS, MOTORPIN11, MOTORPIN12, MOTORPIN13, MOTORPIN14);
StepperMulti myStepper2(STEPS, MOTORPIN21, MOTORPIN22, MOTORPIN23, MOTORPIN24);

int direction1 = 1;
int direction2 = -1;

void setup()
{
    Serial.begin(9600);

    myStepper1.setSpeed(SPEED);
    myStepper2.setSpeed(SPEED);
}

void loop()
{
    myStepper1.step();
    myStepper2.step();

    if (!myStepper1.isMoving()) {
        direction1 *= -1;
        myStepper1.start(direction1 * STEPS);
        Serial.println("Stepper 1 start");
    }
    else if (!myStepper2.isMoving()) {
        direction2 *= -1;
        myStepper2.start(direction2 * STEPS);
        Serial.println("Stepper 2 start");
    }
}
