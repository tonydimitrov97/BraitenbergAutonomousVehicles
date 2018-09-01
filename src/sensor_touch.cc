/**
 * @file sensor_touch.cc
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

#include "src/sensor_touch.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorTouch::HandleCollision(
  __unused EntityType object_type,
  __unused ArenaEntity * object) {
  output_ = true;
}

NAMESPACE_END(csci3081);
