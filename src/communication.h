/**
 * @file communication.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

#ifndef SRC_COMMUNICATION_H_
#define SRC_COMMUNICATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

enum Communication {
  // communications from GUI to controller
  kPlay,
  kPause,
  kNewGame,

  // communications from controller to Arena
  kReset,

  kNone   // in case it is needed
};

NAMESPACE_END(csci3081);

#endif  // SRC_COMMUNICATION_H_
