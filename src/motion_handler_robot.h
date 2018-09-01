/**
 * @file motion_handler_robot.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_ROBOT_H_
#define SRC_MOTION_HANDLER_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cassert>
#include <iostream>

#include "src/common.h"
#include "src/motion_handler.h"
#include "src/sensor_touch.h"
#include "src/communication.h"
#include "src/braitenberg.h"
#include "src/fear.h"
#include "src/aggression.h"
#include "src/explore.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/

/**
 * @brief Class managing a Robot's speed and heading angle foodd
 * on collisions and user inputs.
 *
 * Currently, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class MotionHandlerRobot : public MotionHandler {
 public:
  /**
   * @brief Explicit value constructor.
   */
  explicit MotionHandlerRobot(ArenaMobileEntity * ent, Behavior behavior)
      : MotionHandler(ent) {
        set_behavior(behavior);
      }

  /**
   * @brief Default copy constructor.
   */
  MotionHandlerRobot(const MotionHandlerRobot& other) = default;

  /**
   * @brief Default assignment operator overload.
   */
  MotionHandlerRobot& operator=(const MotionHandlerRobot& other) = default;

/**
  * @brief Set the speed of both wheels based upon the robots proximity
  * to the light.
  *
  * @param[in] left_reading - reading for the sensor on the left
  * @param[in] right_reading  - reading for the sensor on the right
  * @param[out] The proper wheel velocities
  **/
  void UpdateVelocity(double left_reading, double right_reading) override;

/**
  * @brief Set the speed of both wheels based upon the robots proximity
  * to the food and the light.
  *
  * @param[in] left_light_reading - reading for light sensor on the left
  * @param[in] right_light_reading  - reading for light sensor on the right
  * @param[in] left_food_reading - reading for food sensor on the left
  * @param[in] right_food_reading  - reading for food sensor on the right
  * @param[out] The proper wheel velocities
  **/
  void UpdateVelocity(double left_light_reading, double right_light_reading,
    double left_food_reading, double right_food_reading) override;

  /**
   * @brief Set the type of braitenberg vehicle based upon the behavior
   *
   * @param behavior - The way the robot will move based upon the entities
   */
  void set_behavior(Behavior behavior);

 private:
  double clamp_vel(double vel);
  Braitenberg* braitenberg_{nullptr};
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_ROBOT_H_
