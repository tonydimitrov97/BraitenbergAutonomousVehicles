/**
 * @file fear.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */
#ifndef SRC_FEAR_H_
#define SRC_FEAR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/braitenberg.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/**
 * @brief The class for the robot fear behavior.
 *
 * This class inherits from Braitenberg and overrides its CalcWheelVelocity
 * and CalcWheelVelocityWFood methods. The robot will move slowly and avoid
 * light when it is near
 */
class Fear : public Braitenberg {
 public:
 /**
  * @brief Empty default constructor
  */  	
  Fear() {}

 /**
  * @brief Default destructors
  */
  virtual ~Fear() = default;

/**
  * @brief Determine the speed of both wheels based upon the robots proximity
  * to the light.
  *
  * @param[in] left_reading - reading for light sensor on the left
  * @param[in] right_reading  - reading for light sensor on the right
  * @param[out] The proper wheel velocities
  **/
  WheelVelocity CalcWheelVelocity(double left_reading, double right_reading)
    override;

/**
  * @brief Determine the speed of both wheels based upon the robots proximity
  * to the food and the light.
  *
  * @param[in] left_light_reading - reading for light sensor on the left
  * @param[in] right_light_reading  - reading for light sensor on the right
  * @param[in] left_food_reading - reading for food sensor on the left
  * @param[in] right_food_reading  - reading for food sensor on the right
  * @param[out] The proper wheel velocities
  **/
  WheelVelocity CalcWheelVelocityWFood(double left_light_reading,
    double right_light_reading, double left_food_reading,
    double right_food_reading) override;
};

NAMESPACE_END(csci3081);

#endif  // SRC_FEAR_H_
