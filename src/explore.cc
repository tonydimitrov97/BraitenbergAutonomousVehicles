/**
 * @file explore.cc
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/explore.h"
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// Makes the robot go fast when not near a robot and run away when near one
WheelVelocity Explore::CalcWheelVelocity(double left_reading,
  double right_reading) {
  return WheelVelocity(MAX_READING - right_reading,
    MAX_READING - left_reading);
}

// Factors in both the lights and the food. The robot will both avoid lights
// like before but also go collect food
WheelVelocity Explore::CalcWheelVelocityWFood(double left_light_reading,
  double right_light_reading, double left_food_reading,
  double right_food_reading) {
  return WheelVelocity(((MAX_READING - right_light_reading) * .5) +
    (right_food_reading * .5), ((MAX_READING - left_light_reading) * .5) +
    (left_food_reading * .5));
}

NAMESPACE_END(csci3081);
