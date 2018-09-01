/**
 * @file arena.cc
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena.h"
#include "src/arena_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params *const params)
    : x_dim_(params->x_dim),
      y_dim_(params->y_dim),
      factory_(new EntityFactory),
      entities_(),
      mobile_entities_(),
      light_entities_(),
      food_entities_(),
      game_status_(PLAYING) {
  AddRobot(params->n_robots);
  for (auto ent : entities_) {
    // Placing all sensors in correct area in the beginning
    dynamic_cast<Robot *>(ent)->get_light_sensor_left()->Reset();
    dynamic_cast<Robot *>(ent)->get_light_sensor_right()->Reset();
  } /* for(ent..) */
  AddFood(params->n_foods);
  AddLight(params->n_lights);
}

Arena::~Arena() {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::AddRobot(int quantity) {
  Robot* robotPtr = NULL;
  for (int i = 0; i < quantity; i++) {
    // Making half of the robots with fear behavior and half with explore
    if (i < quantity/2) {
      robotPtr = dynamic_cast<Robot *> (factory_->CreateEntity(kRobot, kFear));
      num_fear_robots_++;
    } else {
      robotPtr = dynamic_cast<Robot *> (factory_->CreateEntity(kRobot, kExplore));
      num_explore_robots_++;
    }
    entities_.push_back(robotPtr);
    mobile_entities_.push_back(robotPtr);
  }  // end for
}

void Arena::AddFearRobot(int quantity) {
  Robot* robotPtr = NULL;
  for (int i = 0; i < quantity; i++) {
    robotPtr = dynamic_cast<Robot *>(factory_->CreateEntity(kRobot, kFear)); 
    entities_.push_back(robotPtr);
    mobile_entities_.push_back(robotPtr);
    num_fear_robots_++;
    num_robots_++;
  }  // end for
}

void Arena::AddExploreRobot(int quantity) {
  Robot* robotPtr = NULL;
  for (int i = 0; i < quantity; i++) {
    robotPtr = dynamic_cast<Robot *>(factory_->CreateEntity(kRobot, kExplore)); 
    entities_.push_back(robotPtr);
    mobile_entities_.push_back(robotPtr);
    num_explore_robots_++;
    num_robots_++;
  }  // end for
}

void Arena::RemoveFearRobot(int quantity) {
  ArenaMobileEntity* temp;

  for (int j = 0; j < quantity; j++) {
    for (unsigned int i = 0; i < mobile_entities_.size(); i++)
      if (mobile_entities_[i]->get_type() == kRobot)
        if (dynamic_cast<Robot *> (mobile_entities_[i])->get_behavior() == kFear) {
          temp = mobile_entities_[i];
          mobile_entities_.erase(mobile_entities_.begin() + i);
          break;
        }

    for (unsigned int i = 0; i < entities_.size(); i++)
      if (entities_[i] == temp) {
        entities_.erase(entities_.begin() + i);
        break;
      }

    num_robots_--;
    num_fear_robots_--;
    delete temp;
  }
}

void Arena::RemoveExploreRobot(int quantity) {
  ArenaMobileEntity* temp;

  for (int j = 0; j < quantity; j++) {
    for (unsigned int i = 0; i < mobile_entities_.size(); i++)
      if (mobile_entities_[i]->get_type() == kRobot)
        if (dynamic_cast<Robot *> (mobile_entities_[i])->get_behavior() == kExplore) {
          temp = mobile_entities_[i];
          mobile_entities_.erase(mobile_entities_.begin() + i);
          break;
        }

    for (unsigned int i = 0; i < entities_.size(); i++)
      if (entities_[i] == temp) {
        entities_.erase(entities_.begin() + i);
        break;
      }

    num_robots_--;
    num_explore_robots_--;
    delete temp;
  }
}

void Arena::AddLight(int quantity) {
  Light* lightPtr = NULL;
  // Start loop N_ROBOTS to properly loop through ids
  for (int i = 0; i < quantity; i++) {
    lightPtr = dynamic_cast<Light *>
          (factory_->CreateEntity(kLight, kNA));
    entities_.push_back(lightPtr);
    mobile_entities_.push_back(lightPtr);
    light_entities_.push_back(lightPtr);
  }
}

void Arena::RemoveLight(int quantity) {
  ArenaMobileEntity* temp;
  
  for (int j = 0; j < quantity; j++) {
    for (unsigned int i = 0; i < mobile_entities_.size(); i++)
      if (mobile_entities_[i]->get_type() == kLight){
          temp = mobile_entities_[i];
          mobile_entities_.erase(mobile_entities_.begin() + i);
          break;
      }
    
    for (unsigned int i = 0; i < entities_.size(); i++)
      if (entities_[i] == temp) {
        entities_.erase(entities_.begin() + i);
        break;
      }

    for (unsigned int i = 0; i < light_entities_.size(); i++)
      if (light_entities_[i] == temp) {
        light_entities_.erase(light_entities_.begin() + i);
        break;
      }

    factory_->set_light_count(factory_->get_light_count() - 1);
    delete temp;
  }
}

void Arena::AddFood(int quantity) {
  // Reactivate the hunger if it was not set before
  if (factory_->get_food_count() == 0)
    for (unsigned int i = 0; i < mobile_entities_.size(); i++)
      if (mobile_entities_[i]->get_type() == kRobot)
        dynamic_cast<Robot *>(mobile_entities_[i])->set_has_hunger(true);
      
  Food* foodPtr = NULL;
  for (int i = 0; i < quantity; i++) {
    foodPtr = dynamic_cast<Food *>(factory_->CreateEntity(kFood, kNA));
    entities_.push_back(foodPtr);
    food_entities_.push_back(foodPtr);
  }
}

void Arena::RemoveFood(int quantity) {
  ArenaEntity* temp;
  for (int j = 0; j < quantity; j++) {
    for (unsigned int i = 0; i < entities_.size(); i++)
      if (entities_[i]->get_type() == kFood){
          temp = entities_[i];
          entities_.erase(entities_.begin() + i);
          break;
      }

    for (unsigned int i = 0; i < food_entities_.size(); i++)
      if (food_entities_[i] == temp) {
        food_entities_.erase(food_entities_.begin() + i);
        break;
      }

    factory_->set_food_count(factory_->get_food_count() - 1);
    delete temp;
  }

  // Remove hunger if there is no food
  if (factory_->get_food_count() == 0)
    for (unsigned int i = 0; i < mobile_entities_.size(); i++)
      if (mobile_entities_[i]->get_type() == kRobot) {
        dynamic_cast<Robot *>(mobile_entities_[i])->set_has_hunger(false);
        dynamic_cast<Robot *>(mobile_entities_[i])->set_hunger_time(HUNGER_TIME);
      }
}

void Arena::Reset() {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

// The primary driver of simulation movement. Called from the Controller
// but originated from the graphics viewer.
void Arena::AdvanceTime(double dt) {
  if (!(dt > 0)) {
    return;
  }
  for (size_t i = 0; i < 1; ++i) {
    UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep() {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   * Check hunger levels and notify the sensors, check for collisions
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  }

  CheckIfStarved();
  UpdateLightSensor();
  UpdateFoodSensor();
  HandleAllCollisions();
  
}  // UpdateEntitiesTimestep()

void Arena::CheckIfStarved() {
  // If robots starves end the game
  for (unsigned int i = 0; i < mobile_entities_.size(); i++)
    if (mobile_entities_[i]->get_type() == kRobot)
      if (dynamic_cast<Robot *>(mobile_entities_[i])->get_hunger_time() <= 0)
        set_game_status(LOST);
}

void Arena::UpdateLightSensor() {
  /* Notify all of the robots of all of the Lights */
  for (unsigned int i = 0; i < light_entities_.size(); i++) {
    for (unsigned int j = 0; j < mobile_entities_.size(); j++) {
      if (mobile_entities_[j]->get_type() == kRobot) {
        dynamic_cast<Robot *>(mobile_entities_[j])->get_light_sensor_left()->
          Notify(light_entities_[i]->get_pose());
        dynamic_cast<Robot *>(mobile_entities_[j])->get_light_sensor_right()->
          Notify(light_entities_[i]->get_pose());
      }
    }
  }
}

void Arena::UpdateFoodSensor() {
  /* Notify all of the robots of all of the Food */
  for (unsigned int i = 0; i < food_entities_.size(); i++) {
    for (unsigned int j = 0; j < mobile_entities_.size(); j++) {
      if (mobile_entities_[j]->get_type() == kRobot) {
        dynamic_cast<Robot *>(mobile_entities_[j])->get_food_sensor_left()
          ->Notify(food_entities_[i]->get_pose());
        dynamic_cast<Robot *>(mobile_entities_[j])->get_food_sensor_right()
          ->Notify(food_entities_[i]->get_pose());
      }
    }
  }
}

void Arena::HandleAllCollisions() {
  /* Determine if any mobile entity is colliding with wall.
   * Adjust the position accordingly so it doesn't overlap.
   */
  for (auto &ent1 : mobile_entities_) {
    HandleWallCollisions(ent1);
   /* Robots collide with other robots 
    * Lights collide with other lights
    * If a robot touches food it no longer is hungry
    */
    for (auto &ent2 : entities_) {
      if (ent2 == ent1) { continue; }
      HandleEntityCollisions(ent1, ent2);
    }
  }
}

void Arena::HandleWallCollisions(ArenaMobileEntity* ent1) {
  /* Determine if any mobile entity is colliding with wall.
   * Adjust the position accordingly so it doesn't overlap.
   */
  EntityType wall = GetCollisionWall(ent1);
  if (kUndefined != wall) {
    AdjustWallOverlap(ent1, wall);
    if (ent1->get_type() == kRobot)
      dynamic_cast<Robot *>(ent1)->HandleCollision(wall);
    else if (ent1->get_type() == kLight)
      dynamic_cast<Light *>(ent1)->HandleCollision(wall);
  }
}

void Arena::HandleEntityCollisions(ArenaMobileEntity* ent1, ArenaEntity* ent2) {
 /* Robots collide with other robots 
  * Lights collide with other lights
  * If a robot touches food it no longer is hungry
  */
  if (IsColliding(ent1, ent2)) {
    if (ent1->get_type() == kRobot && ent2->get_type() == kRobot) {
      AdjustEntityOverlap(ent1, ent2);
      dynamic_cast<Robot *> (ent1)->reset_arc_time();
      dynamic_cast<Robot *> (ent2)->reset_arc_time();
      dynamic_cast<Robot *> (ent1)->HandleCollision(ent2->get_type(), ent2);
    } else if (ent1->get_type() == kLight && ent2->get_type() == kLight) {
      AdjustEntityOverlap(ent1, ent2);
      dynamic_cast<Light *> (ent1)->reset_arc_time();
      dynamic_cast<Light *> (ent2)->reset_arc_time();
      dynamic_cast<Light *> (ent1)->HandleCollision(ent2->get_type(), ent2);
    } else if (ent1->get_type() == kRobot && ent2->get_type() == kFood) {
      dynamic_cast<Robot *> (ent1)->set_hunger_time(HUNGER_TIME);
    } else if (ent1->get_type() == kFood && ent2->get_type() == kRobot) {
      dynamic_cast<Robot *> (ent2)->set_hunger_time(HUNGER_TIME);
    }
  }
}

// Determine if the entity is colliding with a wall.
// Always returns an entity type. If not collision, returns kUndefined.
EntityType Arena::GetCollisionWall(ArenaMobileEntity *const ent) {
  if (ent->get_pose().x + ent->get_radius() >= x_dim_) {
    return kRightWall;  // at x = x_dim_
  } else if (ent->get_pose().x - ent->get_radius() <= 0) {
    return kLeftWall;  // at x = 0
  } else if (ent->get_pose().y + ent->get_radius() >= y_dim_) {
    return kBottomWall;  // at y = y_dim
  } else if (ent->get_pose().y - ent->get_radius() <= 0) {
    return kTopWall;  // at y = 0
  } else {
    return kUndefined;
  }
} /* GetCollisionWall() */

/* The entity type indicates which wall the entity is colliding with.
* This determines which way to move the entity to set it slightly off the wall. */
void Arena::AdjustWallOverlap(ArenaMobileEntity *const ent, EntityType object) {
  Pose entity_pos = ent->get_pose();
  switch (object) {
    case (kRightWall):  // at x = x_dim_
    ent->set_position(x_dim_-(ent->get_radius()+5), entity_pos.y);
    break;
    case (kLeftWall):  // at x = 0
    ent->set_position(ent->get_radius()+5, entity_pos.y);
    break;
    case (kTopWall):  // at y = 0
    ent->set_position(entity_pos.x, ent->get_radius()+5);
    break;
    case (kBottomWall):  // at y = y_dim_
    ent->set_position(entity_pos.x, y_dim_-(ent->get_radius()+5));
    break;
    default:
    {}
  }
}

/* Calculates the distance between the center points to determine overlap */
bool Arena::IsColliding(
  ArenaMobileEntity * const mobile_e,
  ArenaEntity * const other_e) {
    double delta_x = other_e->get_pose().x - mobile_e->get_pose().x;
    double delta_y = other_e->get_pose().y - mobile_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    return
    (distance_between <= (mobile_e->get_radius() + other_e->get_radius()));
}

/* This is called when it is known that the two entities overlap.
* We determine by how much they overlap then move the mobile entity to
* the edge of the other
*/
/* @TODO: Add functionality to Pose to determine the distance distance_between two instances (e.g. overload operator -)
*/
/* @BUG: The robot will pass through the home food on occasion. The problem
 * is likely due to the adjustment being in the wrong direction. This could
 * be because the cos/sin generate the wrong sign of the distance_to_move
 * when the collision is in a specific quadrant relative to the center of the
 * colliding entities..
 */
void Arena::AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
  ArenaEntity *const other_e) {
    double delta_x = mobile_e->get_pose().x - other_e->get_pose().x;
    double delta_y = mobile_e->get_pose().y - other_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    double distance_to_move =
      mobile_e->get_radius() + other_e->get_radius() - distance_between + 3;
    double angle = atan2(delta_y, delta_x);
    mobile_e->set_position(
      mobile_e->get_pose().x+cos(angle)*distance_to_move,
      mobile_e->get_pose().y+sin(angle)*distance_to_move);
}

// Accept communication from the controller. Dispatching as appropriate.
/** Accepting commands for playing and pausing the game as well as setting a 
  * new game.
  */
void Arena::AcceptCommand(Communication com) {
  switch (com) {
    case(kPlay): paused_ = !paused_;
      break;
    case(kPause): paused_ = !paused_;
      break;
    case(kReset): Reset();
      break;
    case(kNone):
    default: break;
  }
} /* AcceptCommand */

NAMESPACE_END(csci3081);
