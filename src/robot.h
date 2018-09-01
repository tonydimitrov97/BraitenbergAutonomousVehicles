/**
 * @file robot.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"
#include "src/entity_type.h"
#include "src/food.h"
#include "src/behavior.h"
#include "src/light_sensor.h"
#include "src/food_sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class Food;
class LightSensor;
class FoodSensor;
class MotionBehaviorDifferential;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a robot within the arena.
 *
 * Robots are composed of a motion handler, motion behavior, and touch sensor.
 * These classes interact to maintain the pose (position and heading) of the
 * robot. At each time step, the wheel velocities are used to calculate the
 * next pose of the robot. The handler manages the pose and user requests. The
 * behavior calculates the new pose foodd on wheel velocities.
 *
 * Robots can be controlled through keypress, which modify wheel velocities.
 *
 * The touch sensor is activated when the robot collides with an object.
 * The heading is modified after a collision to move the robot away from the
 * other object.
 */
class Robot : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor using initialization values from params.h.
   */
  explicit Robot(Behavior behavior);

  /**
   * @brief Default destructor
   */
  virtual ~Robot() = default;

  /**
   * @brief Default assignment operator overload.
   */
  Robot &operator=(const Robot& other) = default;

  /**
   * @brief Default copy constructor
   */
  Robot(const Robot& other) = default;

  /**
   * @brief Reset the Robot to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;

  /**
   * @brief Update the Robot's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief Handles the collision by setting the sensor to activated.
   */
  void HandleCollision(EntityType object_type, ArenaEntity * object = NULL);

  /**
   * @brief Get the name of the Robot for visualization and for debugging.
   */
  std::string get_name() const override { return "Robot"; }

  /**
  * @brief Return the motion_handler_ and its functions
  */
  MotionHandlerRobot get_motion_handler() {return motion_handler_;}

  /**
  * @brief Return the motion_behavior_ and its functions
  */
  MotionBehaviorDifferential get_motion_behavior() {return motion_behavior_;}

  /**
  * @brief Sets the robot's behavior
  */
  void set_behavior(Behavior behavior) {behavior_ = behavior;}

  /**
  * @brief Return the robot behavior, foodd upon the behavior the robot will
  * react to light in different ways.
  */
  Behavior get_behavior() {return behavior_;}

  /**
   * @brief Return the left light sensor
   */
  LightSensor* get_light_sensor_left() const { return light_sensor_left_; }

 /**
   * @brief Return the right light sensor
   */
  LightSensor* get_light_sensor_right() const { return light_sensor_right_; }

 /**
   * @brief Return the right food sensor
   */
  FoodSensor* get_food_sensor_left() const { return food_sensor_left_; }

 /**
   * @brief Return the right food sensor
   */
  FoodSensor* get_food_sensor_right() const { return food_sensor_right_; }

 /**
   * @brief Set the robot's hunger time
   */
  void set_hunger_time(float hunger_time);

 /**
   * @brief Return the hunger time
   */
  float get_hunger_time() { return hunger_time_; }

 /**
   * @brief Resets the arc time to the maximum
   */
  void reset_arc_time() { arc_time_ = ARC_TIME; }

  void set_has_hunger(bool has_hunger) { has_hunger_ = has_hunger; }

 private:
  // Manages pose and wheel velocities that change with time and collisions.
  MotionHandlerRobot motion_handler_;
  // Calculates changes in pose foodd on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
  // Each robot has two light sensors
  Behavior behavior_;
  // LightSensors for each side
  LightSensor* light_sensor_left_;
  LightSensor* light_sensor_right_;
  // LightSensors for each side
  FoodSensor* food_sensor_left_;
  FoodSensor* food_sensor_right_;
  // Sets the amount of time the light will arc for if it hits a light,
  // food, or wall.
  float arc_time_{0};
  // Hunger time
  float hunger_time_{HUNGER_TIME};
  // Meaning robot should be affected by hunger time
  bool has_hunger_{true};
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_H_
