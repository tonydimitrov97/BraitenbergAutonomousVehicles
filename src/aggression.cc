/**
 * @file aggression.cc
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/aggression.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

/* Calculates the wheel velocity using the aggression behavior. Only called
when the robot is in its starving phase (<2 min since last food eaten) */
WheelVelocity Aggression::CalcWheelVelocity(double left_reading,
    double right_reading) {
  return WheelVelocity(right_reading * .4, left_reading * .4);
}

NAMESPACE_END(csci3081);
