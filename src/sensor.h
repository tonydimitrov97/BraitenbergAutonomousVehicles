/**
 * @file sensor.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */
#ifndef SRC_SENSOR_H_
#define SRC_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/pose.h"
#include "src/wheel_velocity.h"
#include "src/behavior.h"
#include "src/rgb_color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Robot;

/**
 * @brief Parent class for both of the sensors a robot can have
 *
 * LightSensors are what detect the proximity of the robot to the light.
 * They make sure the robot follows its behavior
 *
 * The LightSensors get notified by light and create readings based upon their
 * proximity to the light.
 *
 * FoodSensors are what detect the proximity of the robot to the food.
 * They make sure the robot does not starve
 *
 * The FoodSensors get notified by food and create readings based upon their
 * proximity to the food.
 */
class Sensor {
 public:
 /**
  * @brief Default constructor
  */ 	
  Sensor() : robot_(NULL), pose_(Pose(0, 0)), reading_(0) {}
 /**
  * @brief Default destructor
  */  
  virtual ~Sensor() = default;

 /**
  * @brief Calculates the distance between two entities
  *
  * @param[in] sensor_pose - Position of the sensor
  * @param[in] entity_pose - Position of the entity
  * @param[out] returns the distance as a double
  */  
  double CalcDistance(Pose sensor_pose, Pose entity_pose);

 /**
  * @brief Gives a sensor reading based upon the position passed in
  *
  * @param entity_pose - the entity to base the reading off of
  */
  virtual void Notify(__unused Pose entity_pose) {}

 /**
  * @brief Resets the position and the sensor reading
  */  
  virtual void Reset() {}
	/**
	 * @brief Under certain circumstance, the compiler requires that the
	 * assignment operator is not defined. This `deletes` the default
	 * assignment operator.
	 */
  Sensor &operator=(__unused const Sensor &other) = default;

	/**
	 * @brief Under certain circumstance, the compiler requires that the copy
	 * constructor is not defined. This `deletes` the default copy constructor.
	 */
  explicit Sensor(__unused const Sensor &other) = default;

 /**
  * @brief Set the reading
  */  
  void set_reading(double reading) { reading_ = reading; }

 /**
  * @brief Return the reading
  */  
  double get_reading() { return reading_; }

 /**
  * @brief Set the sensor position
  */  
  void set_pose(Pose pose) { pose_ = pose; }

 /**
  * @brief Return the sensor position
  */  
  Pose get_pose() { return pose_; }

 /**
  * @brief Set the robot the sensor references
  */  
  void set_robot(Robot* robot) { robot_ = robot; }

 /**
  * @brief Return the robot reference
  */  
  Robot* get_robot() { return robot_; }

  void set_sensitivity(float sensitivity) { sensitivity_ = sensitivity; }

 protected:
  float sensitivity_{1200};
  Robot* robot_;
  Pose pose_;
  double reading_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_H_
