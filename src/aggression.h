/**
 * @file aggression.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */
#ifndef SRC_AGGRESSION_H_
#define SRC_AGGRESSION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/braitenberg.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/**
 * @brief The class for the robot aggression behavior.
 *
 * This class inherits from Braitenberg and overrides its CalcWheelVelocity
 * method. This method makes the robot go quickly towards food
 */
class Aggression : public Braitenberg {
 public:
 /**
  * @brief Empty default constructor
  */
  Aggression() {}

 /**
  * @brief Default destructors
  */
  virtual ~Aggression() = default;

/**
  * @brief Determine the speed of both wheels based upon the robots proximity
  * to the food.
  *
  * @param[in] left_reading - reading for food sensor on the left
  * @param[in] right_reading  - reading for food sensor on the right
  * @param[out] The proper wheel velocities
  **/
  WheelVelocity CalcWheelVelocity(double left_reading,
   double right_reading) override;
};

NAMESPACE_END(csci3081);

#endif  // SRC_AGGRESSION_H_
