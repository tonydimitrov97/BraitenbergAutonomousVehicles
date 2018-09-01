/**
 * @file entity_factory.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

#ifndef SRC_ENTITY_FACTORY_H_
#define SRC_ENTITY_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/food.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/light.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/rgb_color.h"
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A factory for the instantiation of all types of arena entities.
 *
 * The factory keeps track of the number of entities of each type and overall.
 * It assigns ID's to the entity when it creates it.
 * The factory randomly places entities, and in doing so, attempts to not
 * have them overlap.
 */
class EntityFactory {
 public:
  /**
   * @brief EntityFactory constructor.
   */
  EntityFactory();

  /**
   * @brief Default destructor.
   */
  virtual ~EntityFactory() = default;

  /**
  * @brief CreateEntity is primary purpose of this class.
  *
  * @param[in] etype The type to make.
  * @param[in] behavior, in case it is a robot
  * @param[out] new dynamically created entity.
  *
  * Currently, the Arena gets the entity and places it in the appropriate data
  * structure. It might be useful to instead have the factory place on the
  * appropriate data structure so that the call to Arena is the same regardless
  * of the entity type.
  */
  ArenaEntity* CreateEntity(EntityType etype, Behavior behavior);

  int get_entity_count() { return entity_count_; }

  void set_entity_count(int entity_count) { entity_count_ = entity_count; }

  int get_robot_count() { return robot_count_; }

  void set_robot_count(int robot_count) { robot_count_ = robot_count; }

  int get_light_count() { return light_count_; }

  void set_light_count(int light_count) { light_count_ = light_count; }

  int get_food_count() { return food_count_; }

  void set_food_count(int food_count) { food_count_ = food_count; }


 private:
   /**
   * @brief CreateRobot called from within CreateEntity.
   * 
   * @param[in] behavior, sets what type of robot it is
   */
  Robot* CreateRobot(Behavior behavior);

  /**
  * @brief CreateLight called from within CreateEntity.
  */
  Light* CreateLight();

  /**
  * @brief CreateFood called from within CreateEntity.
  */
  Food* CreateFood();

  /**
  * @brief An attempt to not overlap any of the newly constructed entities.
  */
  Pose SetPoseRandomly();

  /**
  * @brief Sets light size randomly.
  */
  int SetLightSizeRandomly();

  /**
  * @brief Sets robot size randomly.
  */
  int SetRobotSizeRandomly();

  /* Factory tracks the number of created entities. There is no accounting for
   * the destruction of entities */
  int entity_count_{0};
  int robot_count_{0};
  int light_count_{0};
  int food_count_{0};
};

NAMESPACE_END(csci3081);

#endif  // SRC_ENTITY_FACTORY_H_
