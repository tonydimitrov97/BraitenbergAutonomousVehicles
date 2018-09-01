/**
 * @file sensor.cc
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/sensor.h"
#include <math.h>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

// Calcuate the distance using the pythagorean theroem
double Sensor::CalcDistance(Pose sensor_pose, Pose entity_pose) {
  return sqrt(pow((sensor_pose.x - entity_pose.x), 2) +
    pow((sensor_pose.y - entity_pose.y), 2));
}

NAMESPACE_END(csci3081);
