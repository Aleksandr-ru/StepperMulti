StepperMulti - protothread stepper library for Arduino
======================================================

This library is a fork of [Stepper Library for Arduino](https://github.com/arduino-libraries/Stepper)
and aimed to make several step motors run asynchronously in protothreading.

For base principles please refer to the
[original library's documentation](https://docs.arduino.cc/libraries/stepper/).

For common usage examples check the `examples` folder.

The library is licensed under LGPL version 2.1.

## New functions


### `start(int steps_to_move)`

Start to move the motor to a specific number of steps, at a speed determined by the most recent call to `setSpeed()`.
This function is non-blocking.

#### Parameters

* `steps_to_move`: the number of steps to turn the motor. Positive integer to turn one direction, negative integer to turn the other.

#### Returns

None.


### `stop(bool free_motor = true)`

Stop moving the motor. By default it releases motor pins to prevent hardware overheating.

#### Parameters

* `free_motor`: if set to `false` motor pins are not released and motor is keep holding current position (breaking).

#### Returns

None.


### `step()`

Rotate the motor according to current speed. This function must be called in every main loop.
There should be no any blocking functions (like `delay`) at least when the motor is moving.

#### Parameters

None.

#### Returns

None.


### `isMoving()`

Get current state of the motor: moving or not.
It returns `true` until number of steps set in `start()` is not reached or `stop()` is called.

#### Parameters

None.

#### Returns

Boolean weather the motor is now moving or not.


---

(c)2022 by [Aleksandr.ru](http://aleksandr.ru)
