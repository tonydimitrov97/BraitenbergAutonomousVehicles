/**
 * @file controller.cc
 *
 * @copyright 2018 Antonio Dimitrov, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>

#include "src/arena_params.h"
#include "src/common.h"
#include "src/controller.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

Controller::Controller() : last_dt(0) {
  // Initialize default properties for various arena entities
  arena_params aparams;
  aparams.n_lights = N_LIGHTS;
  aparams.n_foods = N_FOODS;
  aparams.x_dim = ARENA_X_DIM;
  aparams.y_dim = ARENA_Y_DIM;

  arena_ = new Arena(&aparams);

  // Start up the graphics (which creates the arena).
  // Run() will enter the nanogui::mainloop().
  viewer_ = new GraphicsArenaViewer(&aparams, arena_, this);
}

void Controller::Run() { viewer_->Run(); }

void Controller::AdvanceTime(double dt) {
  if ((last_dt + dt) <= .05) {
    last_dt += dt;
    return;
  }
  last_dt = 0;
  arena_->AdvanceTime(dt);
}

void Controller::AcceptCommunication(Communication com) {
  arena_->AcceptCommand(ConvertComm(com));
}

/** Converts communication from one source to appropriate communication to
 * the other source. For example, the viewer sends a kKeyUp communication,
 * and this translate to a kIncreaseSpeed communication to Arena.
 */
/**
  * @TODO: Complete the conversion code for all key presses.
  */
Communication Controller::ConvertComm(Communication com) {
  switch (com) {
    case (kPlay) : return kPlay;
    case (kPause) : return kPause;
    case (kNewGame) : return kReset;
    default: return kNone;
  }
}

void Controller::ChangeNumFearRobots(int n_robots) {
  if (n_robots > arena_->get_num_fear_robots())
    arena_->AddFearRobot(n_robots - arena_->get_num_fear_robots());
  else if (n_robots < arena_->get_num_fear_robots())
    arena_->RemoveFearRobot(arena_->get_num_fear_robots() - n_robots);
}

void Controller::ChangeNumExploreRobots(int n_robots) {
  if (n_robots > arena_->get_num_explore_robots())
    arena_->AddExploreRobot(n_robots - arena_->get_num_explore_robots());
  else if (n_robots < arena_->get_num_explore_robots())
    arena_->RemoveExploreRobot(arena_->get_num_explore_robots() - n_robots);
}

void Controller::ChangeNumLights(int n_lights) {
  if (n_lights > arena_->get_factory()->get_light_count())
    arena_->AddLight(n_lights - arena_->get_factory()->get_light_count());
  else if (n_lights < arena_->get_factory()->get_light_count())
    arena_->RemoveLight(arena_->get_factory()->get_light_count() - n_lights);
}

void Controller::ChangeNumFood(int n_food) {
  if (n_food > arena_->get_factory()->get_food_count())
    arena_->AddFood(n_food - arena_->get_factory()->get_food_count());
  else if (n_food < arena_->get_factory()->get_food_count())
    arena_->RemoveFood(arena_->get_factory()->get_food_count() - n_food);
}

void Controller::ChangeSensorSensitivity(int sensitivity) {
  for (unsigned int i = 0; i < arena_->get_mobile_entities().size(); i++)
    if (arena_->get_mobile_entities()[i]->get_type() == kRobot) {
      dynamic_cast<Robot *>(arena_->get_mobile_entities()[i])->
          get_light_sensor_left()->set_sensitivity(sensitivity);
      dynamic_cast<Robot *>(arena_->get_mobile_entities()[i])->
          get_light_sensor_right()->set_sensitivity(sensitivity);
      dynamic_cast<Robot *>(arena_->get_mobile_entities()[i])->
          get_food_sensor_left()->set_sensitivity(sensitivity);
      dynamic_cast<Robot *>(arena_->get_mobile_entities()[i])->
          get_food_sensor_right()->set_sensitivity(sensitivity);
    }
}

NAMESPACE_END(csci3081);
