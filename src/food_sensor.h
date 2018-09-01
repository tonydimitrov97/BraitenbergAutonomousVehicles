/**
 * @file food_sensor.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */
#ifndef SRC_FOOD_SENSOR_H_
#define SRC_FOOD_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/sensor.h"
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Robot;

/**
 * @brief Class representing a food sensor for the robot
 *
 * FoodSensors are what detect the proximity of the robot to the food.
 * They make sure the robot does not starve
 *
 * The FoodSensors get notified by food and create readings based upon their
 * proximity to the food.
 */
class FoodSensor : public Sensor {
 public:
 /**
  * @brief Constructor.
  *
  * @param[in] robot - reference to the robot of this sensor
  * @param[in] sensor_angle - the location of the sensor
  */  
  FoodSensor(Robot* robot, double sensor_angle);

 /**
  * @brief Default destructor.
  */
  ~FoodSensor() = default;

 /**
  * @brief Gives a sensor reading based upon the position passed in
  *
  * @param entity_pose - the entity to base the reading off of
  */
  void Notify(Pose entity_pose) override;

 /**
  * @brief Resets the position and the sensor reading
  */
  void Reset() override;

 private:
  double sensor_angle_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_SENSOR_H_
