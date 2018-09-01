/**
 * @file arena.h
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

#ifndef SRC_ARENA_H_
#define SRC_ARENA_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>

#include "src/common.h"
#include "src/food.h"
#include "src/entity_factory.h"
#include "src/robot.h"
#include "src/communication.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
struct arena_params;

/**
 * @brief The main class for the simulation of a 2D world with many entities
 * running around.
 *
 * While GraphicsArenaViewer handles the graphics, Arena handles all the
 * data and all the entities (it is the model of MVC). It manages the
 * interaction among the entities in the Arena.
 *
 */

class Arena {
 public:
  /**
   * @brief Arena's constructor.
   *
   * @param params A arena_params passed down from main.cc for the
   * initialization of Arena and the entities therein.
   *
   * Initialize all private variables and entities.
   */
  explicit Arena(const struct arena_params *const params);

  /**
   * @brief Arena's destructor. `delete` all entities created.
   */
  ~Arena();

  /**
   * @brief Advance the simulation by the specified # of steps.
   *
   * @param[in] dt The # of steps to increment by. This is
   * practically unused because the arena state is advanced
   * incrementally at a fixed rate.
   *
   * If `dt == 0`, `return` immediately. Otherwise calls
   * Arena::UpdateEntitiesTimestep() once.
   */
  void AdvanceTime(double dt);

  /**
   * @brief Adds a "quantity" number of robots to the arena
   */
  void AddRobot(int quantity);

  /**
   * @brief Adds a "quantity" number of fear robots to the arena
   */
  void AddFearRobot(int quantity);

  /**
   * @brief Adds a "quantity" number of explore robots to the arena
   */
  void AddExploreRobot(int quantity);

  /**
   * @brief Removes a "quantity" number of robots from the arena
   */
  void RemoveFearRobot(int quantity);

  /**
   * @brief Removes a "quantity" number of robots from the arena
   */
  void RemoveExploreRobot(int quantity);

  /**
   * @brief Removes a "quantity" number of lights from the arena
   */
  void RemoveLight(int quantity);

  /**
   * @brief Removes a "quantity" number of lights from the arena
   */
  void RemoveFood(int quantity);

  /**
   * @brief Adds a "quantity" number of lights to the arena
   */
  void AddLight(int quantity);

  /**
   * @brief Adds a "quantity" number of food to the arena
   */
  void AddFood(int quantity);

  /**
   * @brief Accepts a screen command and performs a task accordingly
   */
  void AcceptCommand(Communication com);

  /**
   * @brief Reset all entities in Arena.
   */
  void Reset();

  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  Arena &operator=(const Arena &other) = delete;

  /**
   * @brief Under certain circumstance, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  Arena(const Arena &other) = delete;

  /**
   * @brief Determine if two entities have collided in the Arena. Collision is
   * defined as the distance between two entities being less than the sum of
   * their radii.
   *
   * @param mobile_e This entity is definitely moving.
   * @param other_e This entity might be mobile or immobile.
   * @param[out] True if entities overlapping.
   *
   **/
  bool IsColliding(
    ArenaMobileEntity * const mobile_e, ArenaEntity * const other_e);

  /**
  * @brief Move the mobile entity to the edge of the other without overlap.
  * Without this, entities tend to get stuck inside one another.
  **/
  void AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
    ArenaEntity *const other_e);

  /**
   * @brief Determine if a particular entity has gone out of the boundaries of
   * the simulation (i.e. has collided with any one of the walls).
   *
   * @param ent The entity to check.
   * @param [out] An entity type signifying wall (e.g. kRightWall). kUndefined
   * if no collision.
   *
   * The checked entity's position will be updated to a "back-off position" so
   * that it won't get stuck into a wall. The calculation of the "back-off
   * position" is technically not accurate, but good enough for our purpose.
   */
  EntityType GetCollisionWall(ArenaMobileEntity * const ent);

  /**
  * @brief Move the entity to the edge of the wall without overlap.
  * Without this, entities tend to get stuck in walls.
  **/
  void AdjustWallOverlap(ArenaMobileEntity * const ent, EntityType wall);


  /**
   * @brief Update all entities for a single timestep.
   *
   * First calls each entity's TimestepUpdate method to update their speed,
   * heading angle, and position. Then check for collisions between entities
   * or between an entity and a wall.
   */
  void UpdateEntitiesTimestep();

  /**
   * @brief Returns all of the entities
   */
  std::vector<class ArenaEntity *> get_entities() const { return entities_; }

  /**
   * @brief Returns all of the mobile entities 
   */
  std::vector<class ArenaMobileEntity *> get_mobile_entities() const
  { return mobile_entities_; }

  /**
   * @brief Returns the x dimension of the graphics window
   */
  double get_x_dim() { return x_dim_; }
  /**
   * @brief Returns the y dimension of the graphics window
   */
  double get_y_dim() { return y_dim_; }

  /**
   * @brief Returns the game status
   */
  int get_game_status() const { return game_status_; }

  /**
   * @brief Sets the game status to playing or paused
   */
  void set_game_status(int status) { game_status_ = status; }

  /**
   * @brief Sets whether the game is paused or not
   */
  void set_paused(bool paused) { paused_ = paused; }

  /**
   * @brief Returns if the game is paused or not
   */
  bool get_paused(void) { return paused_; }

  EntityFactory* get_factory() { return factory_; }

  int get_num_fear_robots() {return num_fear_robots_; }

  int get_num_explore_robots() {return num_explore_robots_; }

  int get_num_robots() {return num_robots_; }

 private:
  /**
   * @brief Check to see if any of the robots are starving, if they are set
   * the status to lost
   */
  void CheckIfStarved();

  /**
   * @brief Loops through all of the light sensors and notifies them of all of
   * the lights.
   */
  void UpdateLightSensor();

  /**
   * @brief Loops through all of the food sensors and notifies them of all of
   * the food.
   */
  void UpdateFoodSensor();

  /**
   * @brief Handles all of the collisions of the entities, whether it be with
   * the wall or other entities.
   */
  void HandleAllCollisions();

  /**
   * @brief Handles wall collisions of entity1
   * param ent1 The entity which collides
   */
  void HandleWallCollisions(ArenaMobileEntity* ent1);

  /**
   * @brief Handles collisions of entity1 into entity2
   * param ent1 The entity which collides
   * param ent2 What it collides with
   */
  void HandleEntityCollisions(ArenaMobileEntity* ent1, ArenaEntity* ent2);

  // Dimensions of graphics window inside which entities must operate
  double x_dim_;
  double y_dim_;

  // Used to create all entities within the arena
  EntityFactory *factory_;

  // All entities mobile and immobile.
  std::vector<class ArenaEntity *> entities_;

  // A subset of the entities -- only those that can move (only Robot for now).
  std::vector<class ArenaMobileEntity *> mobile_entities_;

  // A subset of Lights
  std::vector<class Light *> light_entities_;

  // A subset of Food
  std::vector<class Food *> food_entities_;

  // win/lose/playing state
  int game_status_;

  // Checks if the game is paused or not
  bool paused_{true};

  int num_robots_{N_ROBOTS};

  int num_fear_robots_{0};

  int num_explore_robots_{0};
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_H_
