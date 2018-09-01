/**
 * @file light.cc
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/light.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Light::Light() : motion_behavior_(this) {
  set_color(LIGHT_COLOR);
  set_pose(LIGHT_POSITION);
  set_radius(LIGHT_RADIUS);
  set_type(kLight);
  set_speed(LIGHT_SPEED);
}

void Light::Reset() {
  set_pose(SetPoseRandomly());
  set_radius(SetLightSizeRandomly());
  velocity_.left = LIGHT_SPEED;
  velocity_.right = LIGHT_SPEED;
  arc_time_ = 0;
}

WheelVelocity Light::HandleArc(unsigned int dt) {
  // Set the robot to arc when it collides
  if (arc_time_ > 0) {
    RelativeChangeHeading(+5);
    velocity_.left = LIGHT_SPEED + 2;
    velocity_.right = LIGHT_SPEED + 2;
    arc_time_ -= dt;
  } else {
    velocity_.left = LIGHT_SPEED;
    velocity_.right = LIGHT_SPEED;
  }

  return velocity_;
}

void Light::TimestepUpdate(__unused unsigned int dt) {
  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, HandleArc(dt));

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
} /* TimestepUpdate() */

void Light::HandleCollision(EntityType object_type, ArenaEntity * object) {
  RelativeChangeHeading(+180);
  arc_time_ = ARC_TIME;
  sensor_touch_->HandleCollision(object_type, object);
}

NAMESPACE_END(csci3081);
