/**
 * @file food_sensor.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/food_sensor.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

// explicit value constructor for the food sensor
FoodSensor::FoodSensor(Robot* robot, double sensor_angle) :
sensor_angle_(sensor_angle) {
  set_robot(robot);
  set_pose(Pose(
    robot->get_pose().x + robot_->get_radius() * cos(((robot->get_pose().theta
      + sensor_angle)/180)*PI),
    robot->get_pose().y + robot_->get_radius() * sin(((robot->get_pose().theta
      + sensor_angle)/180)*PI)));
  set_reading(0);
}

// Sets the reading in relation to the distance of the other entities
void FoodSensor::Notify(Pose entity_pose) {
  reading_ += sensitivity_/(pow(CalcDistance(pose_, entity_pose), 1.08));
}

// Reset function
void FoodSensor::Reset() {
  set_pose(Pose(
    robot_->get_pose().x + robot_->get_radius() * cos(((robot_->
      get_pose().theta + sensor_angle_)/180)*PI),
    robot_->get_pose().y + robot_->get_radius() * sin(((robot_->
      get_pose().theta + sensor_angle_)/180)*PI)));
  set_reading(0);
}

NAMESPACE_END(csci3081);
