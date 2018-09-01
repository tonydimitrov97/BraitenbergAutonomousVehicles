/**
 * @file robot.cc
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot(Behavior behavior) :
    motion_handler_(this, behavior),
    motion_behavior_(this),
    behavior_(behavior),
    light_sensor_left_(new LightSensor(this, -SENSOR_ANGLE)),
    light_sensor_right_(new LightSensor(this, SENSOR_ANGLE)),
    food_sensor_left_(new FoodSensor(this, -SENSOR_ANGLE)),
    food_sensor_right_(new FoodSensor(this, SENSOR_ANGLE)) {
  set_type(kRobot);
  set_color(ROBOT_COLOR);
  set_pose(ROBOT_INIT_POS);
  set_radius(ROBOT_MAX_RADIUS);
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  // If it is within the collision time then move in an arc
  if (arc_time_ > 0) {
    RelativeChangeHeading(+5);
    motion_handler_.UpdateVelocity(7, 7);
    arc_time_ -= dt;
  } else {
    // Robot not hungry at all
    if (hunger_time_ > HUNGER_TIME * .8) {
      motion_handler_.UpdateVelocity(light_sensor_left_->get_reading(),
        light_sensor_right_->get_reading());
    // Robot hungry but not starving
    } else if (hunger_time_ > HUNGER_TIME * .2) {
      motion_handler_.UpdateVelocity(light_sensor_left_->get_reading(),
        light_sensor_right_->get_reading(),
       food_sensor_left_->get_reading(), food_sensor_right_->get_reading());
    // Robot starving
    } else {
      motion_handler_.set_behavior(kAggression);
      motion_handler_.UpdateVelocity(food_sensor_left_->get_reading(),
        food_sensor_right_->get_reading());
    }
  }

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Decrement the hunger time
  if (has_hunger_)
    hunger_time_ -= dt;

  // Reset Sensors for next cycle
  sensor_touch_->Reset();
  light_sensor_left_->Reset();
  light_sensor_right_->Reset();
  food_sensor_left_->Reset();
  food_sensor_right_->Reset();
} /* TimestepUpdate() */

// Resets all of robots attributes
void Robot::Reset() {
  set_pose(SetPoseRandomly());
  set_color(ROBOT_COLOR);
  motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  motion_handler_.set_velocity(0, 0);
  motion_handler_.set_behavior(behavior_);
  arc_time_ = 0;
  hunger_time_ = HUNGER_TIME;
  sensor_touch_->Reset();
  light_sensor_left_->Reset();
  light_sensor_right_->Reset();
  food_sensor_left_->Reset();
  food_sensor_right_->Reset();
} /* Reset() */

// Decides robot's motion when it registers a collision
void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  arc_time_ = ARC_TIME;
  sensor_touch_->HandleCollision(object_type, object);
}

// Sets the hunger time to max and sets it to its default behavior
void Robot::set_hunger_time(float hunger_time) {
  motion_handler_.set_behavior(behavior_);
  hunger_time_ = hunger_time;
}

NAMESPACE_END(csci3081);
