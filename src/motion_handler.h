/**
 * @file motion_handler.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_H_
#define SRC_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/params.h"
#include "src/wheel_velocity.h"
#include "src/sensor_touch.h"
#include "src/arena_mobile_entity.h"
#include "src/behavior.h"
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief Food class for managing the pose and wheel velocity of the entity.
 *
 * The pose.heading will change when the entity collides.
 * The pose position will change at each timestep, which is determined by the
 * motion behavior, not the handler.
 * The pose.heading might change at each timestep (if wheel velocities are
 * not equivalent), again determined by the motion behavior.
 */
class MotionHandler {
 public:
  /**
   * @brief Constructor.
   */
  explicit MotionHandler(ArenaMobileEntity * ent)
    : velocity_(0, 0), entity_(ent) {}

  /**
   * @brief Default destructor.
   */
  virtual ~MotionHandler() {}

  /**
   * @brief Default copy constructor.
   */
  MotionHandler(const MotionHandler& other) = default;

  /**
   * @brief Default assignment operator overload.
   */
  MotionHandler& operator=(const MotionHandler& other) = default;

  /**
  * @brief Update velocity based on behavior
  */
  virtual void UpdateVelocity(__unused double left_reading,
    __unused double right_reading) {}

  /*
  * @brief Update the velocity based upon behavior and hunger level
  */
  virtual void UpdateVelocity(__unused double left_light_reading,
    __unused double right_light_reading, __unused double left_food_reading,
    __unused double right_food_reading) {}

  /**
   * @brief Getter for speed delta used when user requests speed increase.
   */
  double get_speed_delta() const { return speed_delta_; }

  /**
   * @brief Setter method for the speed delta. Set at initialization only.
   */
  void set_speed_delta(double sd) { speed_delta_ = sd; }

  /**
   * @brief Getter for angle delta used when user requests turning.
   */
  double get_angle_delta() const { return angle_delta_; }

  /**
   * @brief Setter method for the angle delta. Set at initialization only.
   */
  void set_angle_delta(double ad) { angle_delta_ = ad; }

  /**
   * @brief Getter method for the maximum speed of entity.
   */
  double get_max_speed() const { return max_speed_; }

  /**
   * @brief Setter method for the maximum speed. Set at initialization only.
   */
  void set_max_speed(double ms) { max_speed_ = ms; }

  /**
   * @brief Getter method for the maximum angle.
   */
  double get_max_angle() const { return max_angle_; }

  /**
   * @brief Setter method for the maximum angle. Set at initialization only.
   */
  void set_max_angle(double ma) { max_angle_ = ma; }

  /**
   * @brief Getter for WheelVelocity struct, which has a .left and .right value.
   */
  WheelVelocity get_velocity() const { return velocity_; }

  /**
   * @brief Setter for WheelVelocity struct with struct as input param.
   */
  void set_velocity(WheelVelocity vel) { velocity_ = vel; }

  /**
   * @brief Setter for WheelVelocity struct with input params of .left and
   * .right components.
   */
  void set_velocity(double vl, double vr) {
    velocity_.left = vl;
    velocity_.right = vr;
  }

  /**
   * @brief Return the entity.
   */
  ArenaMobileEntity * get_entity() { return entity_; }

 private:
  double max_speed_{10};
  double max_angle_{360};
  double speed_delta_{1};
  double angle_delta_{1};
  WheelVelocity velocity_;

 protected:
  ArenaMobileEntity * entity_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_H_
