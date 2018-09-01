/**
 * @file motion_handler_robot.cc
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// Method for robot only reacting to either food or light
void MotionHandlerRobot::UpdateVelocity(double left_reading,
  double right_reading) {
  // Flip robot if it comes in contact with wall or robot
  if (entity_->get_touch_sensor()->get_output()) {
    entity_->RelativeChangeHeading(+180);
  }

  WheelVelocity vel = braitenberg_->
    CalcWheelVelocity(left_reading, right_reading);
  set_velocity(clamp_vel(vel.left), clamp_vel(vel.right));
}

// Method for reacting to both the light and the food
void MotionHandlerRobot::UpdateVelocity(double left_light_reading,
  double right_light_reading, double left_food_reading,
  double right_food_reading) {
  WheelVelocity vel = braitenberg_->CalcWheelVelocityWFood(left_light_reading,
    right_light_reading, left_food_reading, right_food_reading);
  set_velocity(clamp_vel(vel.left), clamp_vel(vel.right));
}

// Limit the speed of the robot
double MotionHandlerRobot::clamp_vel(double vel) {
  double clamped = 0.0;
  if (vel > 0)
    clamped = (vel > get_max_speed()) ?
              get_max_speed():
              vel;
  return clamped;
} /* clamp_vel() */

// Set the type of braitenberg vehicle based upon the behavior
void MotionHandlerRobot::set_behavior(Behavior behavior) {
  delete braitenberg_;
  if (behavior == kExplore)
    braitenberg_ = new Explore();
  else if (behavior == kFear)
    braitenberg_ = new Fear();
  else if (behavior == kAggression)
    braitenberg_ = new Aggression();
}

NAMESPACE_END(csci3081);
