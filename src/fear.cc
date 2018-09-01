/**
 * @file fear.cc
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/fear.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// Makes the robot go slow when not near a robot and run away when near one
WheelVelocity Fear::CalcWheelVelocity(double left_reading,
  double right_reading) {
  return WheelVelocity(left_reading, right_reading);
}

// Factors in both the lights and the food. The robot will both avoid lights
// like before but also go collect food
WheelVelocity Fear::CalcWheelVelocityWFood(double left_light_reading,
  double right_light_reading, double left_food_reading,
  double right_food_reading) {
  return WheelVelocity((left_light_reading * .5) + (right_food_reading * .5),
         (right_light_reading * .5) + (left_food_reading * .5));
}

NAMESPACE_END(csci3081);
