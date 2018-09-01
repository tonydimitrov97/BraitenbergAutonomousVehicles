/**
 * @file light_sensor.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */
#ifndef SRC_LIGHT_SENSOR_H_
#define SRC_LIGHT_SENSOR_H_

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
 * @brief Class representing a light sensor for the robot
 *
 * LightSensors are what detect the proximity of the robot to the light.
 * They make sure the robot follows its behavior
 *
 * The LightSensors get notified by light and create readings based upon their
 * proximity to the light.
 */
class LightSensor : public Sensor {
 public:
 /**
  * @brief Constructor.
  *
  * @param[in] robot - reference to the robot of this sensor
  * @param[in] sensor_angle - the location of the sensor
  */
  LightSensor(Robot* robot, double sensor_angle);

 /**
  * @brief Default destructor.
  */
  ~LightSensor() = default;
/**
  * @brief Default constructor.
  */
  LightSensor() = default;

  void set_sensor_angle(double sensor_angle) { sensor_angle_ = sensor_angle; }

  double get_sensor_angle() { return sensor_angle_; }

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

#endif  // SRC_LIGHT_SENSOR_H_
