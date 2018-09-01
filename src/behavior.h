/**
 * @file behavior.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

#ifndef SRC_BEHAVIOR_H_
#define SRC_BEHAVIOR_H_

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/* Enumerated type of all of the possible robot behaviors*/
enum Behavior {
  kLove,
  kAggression,
  kExplore,
  kFear,
  kNA
};

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_H_
