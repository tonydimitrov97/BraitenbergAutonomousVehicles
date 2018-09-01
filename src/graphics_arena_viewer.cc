/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <iostream>

#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/rgb_color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
    const struct arena_params *const params,
    Arena * arena, Controller * controller) :
    GraphicsApp(
        params->x_dim + GUI_MENU_WIDTH + GUI_MENU_GAP * 2,
        params->y_dim,
        "Robot Simulation"),
    controller_(controller),
    arena_(arena) {
  auto *gui = new nanogui::FormHelper(screen());
  nanogui::ref<nanogui::Window> window =
      gui->addWindow(
          Eigen::Vector2i(10 + GUI_MENU_GAP, 10),
          "Menu");
  window->setLayout(new nanogui::GroupLayout());
  gui->addGroup("Simulation Control");
  playing_button_ =
    gui->addButton(
      "Play",
      std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));
  playing_button_->setFixedWidth(100);

  new_game_button_ =
    gui->addButton(
      "New Game",
      std::bind(&GraphicsArenaViewer::OnNewGameBtnPressed, this));
  new_game_button_->setFixedWidth(100);
  
  gui->addGroup("Arena Configuration");

  // Creating a panel impacts the layout. Widgets, sliders, buttons can be
  // assigned to either the window or the panel.
  nanogui::Widget *panel = new nanogui::Widget(window);

  // *************** SLIDER 1 ************************//
  new nanogui::Label(panel, "Number of Fear Robots", "sans-bold");
  nanogui::Slider *slider = new nanogui::Slider(panel);
  // The starting value (range is from 0 to 1)
  // Note that below the displayed value is 10* slider value.
  slider->setValue(1.f);
  slider->setFixedWidth(100);
  
  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox = new nanogui::TextBox(panel);
  textBox->setFixedSize(nanogui::Vector2i(60, 25));
  textBox->setFontSize(20);
  textBox->setValue("5");

  // This is the lambda function called while the user is moving the slider
  slider->setCallback(
    [textBox](float value) {
      textBox->setValue(std::to_string(int(value*5)));
    }
  );
  // This is the lambda function called once the user is no longer manipulating the slider.
  // Note robot_count_ is set, which is a graphics_arena_ variable in this version, although
  // you should communicate that value to the controller so that it can configure the Arena.
  slider->setFinalCallback(
    [&](float value) {
      robot_count_ = int(value*5);
      controller_->ChangeNumFearRobots(robot_count_);
    }
  );

  // *************** SLIDER 2 ************************//
  new nanogui::Label(panel, "Number of Explore Robots", "sans-bold");
  nanogui::Slider *slider2 = new nanogui::Slider(panel);
  slider2->setValue(1.f);
  slider2->setFixedWidth(100);
  //textBox->setUnits("%");

  nanogui::TextBox *textBox2 = new nanogui::TextBox(panel);
  textBox2->setFixedSize(nanogui::Vector2i(60, 25));
  textBox2->setFontSize(20);
  textBox2->setValue("5");
  //textBox2->setAlignment(nanogui::TextBox::Alignment::Right);

  slider2->setCallback(
    [textBox2](float value) {
      textBox2->setValue(std::to_string(int(value*5)));
    }
  );

  slider2->setFinalCallback(
    [&](float value) {
      robot_count_ = int(value*5);
      controller_->ChangeNumExploreRobots(robot_count_);
    }
  );

  // *************** SLIDER 3 ************************//
  new nanogui::Label(panel, "Number of Lights", "sans-bold");
  nanogui::Slider *slider3 = new nanogui::Slider(panel);
  slider3->setValue(1.f);
  slider3->setFixedWidth(100);
  //textBox->setUnits("%");

  nanogui::TextBox *textBox3 = new nanogui::TextBox(panel);
  textBox3->setFixedSize(nanogui::Vector2i(60, 25));
  textBox3->setFontSize(20);
  textBox3->setValue("4");
  //textBox2->setAlignment(nanogui::TextBox::Alignment::Right);

  slider3->setCallback(
    [textBox3](float value) {
      textBox3->setValue(std::to_string(int(value*4)));
    }
  );

  slider3->setFinalCallback(
    [&](float value) {
      light_count_ = int(value*4);
      controller_->ChangeNumLights(light_count_);
    }
  );

  // *************** SLIDER 4 ************************//
  new nanogui::Label(panel, "Number of Food", "sans-bold");
  nanogui::Slider *slider4 = new nanogui::Slider(panel);
  slider4->setValue(1.f);
  slider4->setFixedWidth(100);
  //textBox->setUnits("%");

  nanogui::TextBox *textBox4 = new nanogui::TextBox(panel);
  textBox4->setFixedSize(nanogui::Vector2i(60, 25));
  textBox4->setFontSize(20);
  textBox4->setValue("4");
  //textBox2->setAlignment(nanogui::TextBox::Alignment::Right);

  slider4->setCallback(
    [textBox4](float value) {
      textBox4->setValue(std::to_string(int(value*4)));
    }
  );

  slider4->setFinalCallback(
    [&](float value) {
      food_count_ = int(value*4);
      controller_->ChangeNumFood(food_count_);
    }
  );

  // *************** SLIDER 5 ************************//
  new nanogui::Label(panel, "Sensitivity of Sensors", "sans-bold");
  nanogui::Slider *slider5 = new nanogui::Slider(panel);
  slider5->setValue(1.f);
  slider5->setFixedWidth(100);
  //textBox->setUnits("%");

  nanogui::TextBox *textBox5 = new nanogui::TextBox(panel);
  textBox5->setFixedSize(nanogui::Vector2i(60, 25));
  textBox5->setFontSize(20);
  textBox5->setValue("1200");
  //textBox2->setAlignment(nanogui::TextBox::Alignment::Right);

  slider5->setCallback(
    [textBox5](float value) {
      textBox5->setValue(std::to_string(int(value*1200)));
    }
  );

  slider5->setFinalCallback(
    [&](float value) {
      sensitivity_ = int(value*1200);
      controller_->ChangeSensorSensitivity(sensitivity_);
    }
  );

  // Lays out all the components with "15" units of inbetween spacing
  panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 15));

  // ^^^^^^^^^^^^^^^^^^^^^^    ADDED TO HERE (modification of nanogui example1.cc)  ^^^^^^^^^^^^^^^^^^^^^^^^

  screen()->performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (arena_->get_game_status() != WON && arena_->get_game_status() != LOST)
      if (!arena_->get_paused())
        controller_->AdvanceTime(dt);
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnPlayingBtnPressed() {
  // Not implemented. Sample code provided to show how to implement.
  if (!arena_->get_paused()) {
    playing_button_->setCaption("Play");
    controller_->AcceptCommunication(kPause);
  } else {
    playing_button_->setCaption("Pause");
    controller_->AcceptCommunication(kPlay);
  }
}

void GraphicsArenaViewer::OnNewGameBtnPressed() {
  controller_->AcceptCommunication(kNewGame);
  arena_->set_paused(true);
  playing_button_->setCaption("Play");
  arena_->set_game_status(PLAYING);
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx,
                                     const Robot *const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading of this robot
  nvgSave(ctx);
  nvgTranslate(ctx,
               static_cast<float>(robot->get_pose().x),
               static_cast<float>(robot->get_pose().y));
  nvgRotate(ctx,
            static_cast<float>(robot->get_pose().theta * M_PI / 180.0));

  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, static_cast<float>(robot->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(robot->get_color().r, robot->get_color().g,
                       robot->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, static_cast<float>(M_PI / 2.0));
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgRestore(ctx);
  nvgRestore(ctx);

  // robot's left sensor
  nvgSave(ctx);
  nvgBeginPath(ctx);
  nvgTranslate(ctx,
            static_cast<float>(robot->get_light_sensor_left()->get_pose().x),
            static_cast<float>(robot->get_light_sensor_left()->get_pose().y));
  nvgCircle(ctx, 0.0, 0.0, 2.);
  nvgFillColor(ctx,
               nvgRGBA(255, 255, 255, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(255, 255, 50, 255));
  nvgStroke(ctx);
  nvgRestore(ctx);

  // robot's right sensor
  nvgSave(ctx);
  nvgBeginPath(ctx);
  nvgTranslate(ctx,
            static_cast<float>(robot->get_light_sensor_right()->get_pose().x),
            static_cast<float>(robot->get_light_sensor_right()->get_pose().y));
  nvgCircle(ctx, 0.0, 0.0, 2.);
  nvgFillColor(ctx,
               nvgRGBA(255, 255, 255, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(255, 255, 50, 255));
  nvgStroke(ctx);
  nvgRestore(ctx);
}
void GraphicsArenaViewer::DrawArena(NVGcontext *ctx) {
  nvgBeginPath(ctx);
  // Creates new rectangle shaped sub-path.
  nvgRect(ctx, 0, 0, arena_->get_x_dim(), arena_->get_y_dim());
  nvgStrokeColor(ctx, nvgRGBA(255, 255, 255, 255));
  nvgStroke(ctx);
}

void GraphicsArenaViewer::DrawEntity(NVGcontext *ctx,
                                       const ArenaEntity *const entity) {
  // light's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx,
            static_cast<float>(entity->get_pose().x),
            static_cast<float>(entity->get_pose().y),
            static_cast<float>(entity->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(entity->get_color().r, entity->get_color().g,
                       entity->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // light id text label
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));

  if (entity->get_type() != kRobot)
    nvgText(ctx,
          static_cast<float>(entity->get_pose().x),
          static_cast<float>(entity->get_pose().y),
          entity->get_name().c_str(), nullptr);
}

void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
  DrawArena(ctx);
  std::vector<ArenaEntity *> entities = arena_->get_entities();
  for (auto &entity : entities) {
    DrawEntity(ctx, entity);
  } /* for(i..) */
  for (unsigned int i = 0; i < arena_->get_mobile_entities().size(); i++)
    if (arena_->get_mobile_entities()[i]->get_type() == kRobot)
      DrawRobot(ctx, dynamic_cast<Robot *>(arena_->get_mobile_entities()[i]));

  nvgFontSize(ctx, 72.0f);
  if (arena_->get_game_status() == LOST) {
      nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
      nvgText(ctx,
          static_cast<float>(X_DIM/2),
          static_cast<float>(Y_DIM/2),
          "You Lost", nullptr);
  } else if (arena_->get_game_status() == WON) {
      nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
      nvgText(ctx,
          static_cast<float>(X_DIM/2),
          static_cast<float>(Y_DIM/2),
          "YOU WIN!!!", nullptr);
  }
}

NAMESPACE_END(csci3081);
