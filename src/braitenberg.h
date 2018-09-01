/**
 * @file braitenberg.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */
#ifndef SRC_BRAITENBERG_H_
#define SRC_BRAITENBERG_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/wheel_velocity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/**
 * @brief This parent class for all of the possible robot behaviors
 *
 * The three possible subclasses as of right now are Fear, Aggression, Explore
 * These classes override the CalcWheelVelocity and CalcWheelVelocityWFood 
 * methods. Based upon the circumstances this controls the robot's behavior 
 * towards food and light.
 */
class Braitenberg {
 public:
 /**
  * @brief Empty default constructor
  */	
  Braitenberg() {}

 /**
  * @brief Empty destructor
  */
  virtual ~Braitenberg() {}

 /**
  * @brief When overwritten this only takes into account either food or light
  * and returns an appropriate wheel velocity based upon proximity
  */
  virtual WheelVelocity CalcWheelVelocity(__unused double left_reading,
    __unused double right_reading) { return WheelVelocity(0, 0); }

 /**
  * @brief Takes into account both the food and the light, returns appropriate
  * wheel velocity.
  */
  virtual WheelVelocity CalcWheelVelocityWFood(
    __unused double left_light_reading, __unused double right_light_reading,
    __unused double left_food_reading, __unused double right_food_reading)
  { return WheelVelocity(0, 0); }
};

NAMESPACE_END(csci3081);

#endif  // SRC_BRAITENBERG_H_
