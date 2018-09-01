/**
 * @file light.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/pose.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a mobile light within the Arena.
 *
 * The lights have a wheel velocity which controls their movement. With that
 * they also have TimestepUpdate which controls the visual movement. 
 * HandleCollision controls what the light does when it collides with an 
 * entity.
 */
class Light : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   */
  Light();

  /**
   * @brief Get the name of the Light for visualization purposes, and to
   * aid in debugging.
   */
  std::string get_name() const override {
    return "Light";
  }

  /**
   * @brief Reset the Robot to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;

  /**
   * @brief Update the light's position after the specified
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
  * @brief Resets the arc time to the maximum
  */
  void reset_arc_time() { arc_time_ = ARC_TIME; }

 private:
  /**
   * @brief Set the arc of the light when it collides with wall, food, 
   * or light
   */
  WheelVelocity HandleArc(unsigned int dt);

 /**
  * @brief Sets light size randomly.
  */
  int SetLightSizeRandomly() { return (random() %
    (LIGHT_MAX_RADIUS - LIGHT_MIN_RADIUS + 1) + LIGHT_MIN_RADIUS); }

  // Calculates changes in pose foodd on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
  // Makes the wheel velocity the default speed at the beginning.
  WheelVelocity velocity_{LIGHT_SPEED, LIGHT_SPEED};
  // Sets the amount of time the light will arc for if it hits an light,
  // or wall.
  float arc_time_{0};
};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_H_
