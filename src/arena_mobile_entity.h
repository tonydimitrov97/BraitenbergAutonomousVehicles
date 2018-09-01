/**
 * @file arena_mobile_entity.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

#ifndef SRC_ARENA_MOBILE_ENTITY_H_
#define SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena_entity.h"
#include "src/common.h"
#include "src/sensor_touch.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A mobile entity in the Arena, capable of updating its own position
 * and/or velocity when asked by the simulation.
 *
 * All mobile entities must have a heading angle so that their orientation can
 * be properly drawn by the GraphicsArenaViewer.
 *
 * Since this is also a food class, many of its methods are intuitively
 * `virtual`.
 */
class ArenaMobileEntity : public ArenaEntity {
 public:
 /**
  * @brief ArenaMobileEntity's constructor.
  */
  ArenaMobileEntity()
    : ArenaEntity(),
      speed_(0),
      sensor_touch_(new SensorTouch) {
        set_mobility(true);
  }

 /**
  * @brief Under certain circumstance, the compiler requires that the
  * copy constructor is not defined. This `deletes` the default
  * copy constructor.
  */
  ArenaMobileEntity(const ArenaMobileEntity& other) = delete;

 /**
  * @brief Under certain circumstance, the compiler requires that the
  * assignment operator is not defined. This `deletes` the default
  * assignment operator.
  */
  ArenaMobileEntity& operator=(const ArenaMobileEntity& other) = delete;

 /**
  * @brief Returns the speed of the entity
  */
  virtual double get_speed() { return speed_; }

 /**
  * @brief Sets the speed of the entity
  */  
  virtual void set_speed(double sp) { speed_ = sp; }

  /**
   * @brief Get a pointer to the ArenaMobileEntity's touch sensor.
  */
  SensorTouch * get_touch_sensor() { return sensor_touch_; }

 private:
  double speed_;

 protected:
  // Using protected allows for direct access to sensor within entity.
  // It was awkward to have get_touch_sensor()->get_output() .
  SensorTouch * sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_MOBILE_ENTITY_H_
