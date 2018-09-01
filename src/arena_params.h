/**
 * @file arena_params.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 *
 */

#ifndef SRC_ARENA_PARAMS_H_
#define SRC_ARENA_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/light.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
/**
* @brief Struct holding parameters for initializing the Arena.
*
* These parameters include the parameters for Arena's geometry as well as the
* parameters for initializing ALL entities within the Arena.
*/
struct arena_params {
  size_t n_lights{N_LIGHTS};
  size_t n_foods{N_FOODS};
  size_t n_robots{N_ROBOTS};
  uint x_dim{ARENA_X_DIM};
  uint y_dim{ARENA_Y_DIM};
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_PARAMS_H_
