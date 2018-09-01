// Google Test Framework
#include <gtest/gtest.h>
#include <cmath>

// Project code from the ../src directory
#include "../src/motion_handler.h"
#include "../src/motion_handler_robot.h"
#include "../src/robot.h"

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
#ifdef MOTIONHANDLER_TESTS

/************************************************************************
* SETUP
*************************************************************************/
class MotionHandlerTest : public ::testing::Test {
 public:
   MotionHandlerTest() {}
 protected:
  /* declare members */
  csci3081::Robot* rFear = new csci3081::Robot(csci3081::kFear);
  csci3081::Robot* rExplore = new csci3081::Robot(csci3081::kExplore);
  csci3081::Robot* rAggression = new csci3081::Robot(csci3081::kAggression);
 };

/*************************************************************/
/** TESTS for Methods of MotionHandler ***********************/
/*************************************************************/

// Testing UpdateVelocity with Fear
TEST_F(MotionHandlerTest, RobotFearNoHungerNegativeReading) {
  rFear->get_motion_handler().UpdateVelocity(-1, -1);
  EXPECT_EQ(rFear->get_motion_handler().get_velocity().left, 0)
    << "\nFAIL RobotFearNoHungerNegativeReading: Left\n";
  EXPECT_EQ(rFear->get_motion_handler().get_velocity().right, 0)
    << "\nFAIL RobotFearNoHungerNegativeReading: Right\n";
}

TEST_F(MotionHandlerTest, RobotFearNoHungerNormalReading) {

}

TEST_F(MotionHandlerTest, RobotFearNoHungerMaxReading) {

}

TEST_F(MotionHandlerTest, RobotFearWithHungerNegativeReading) {

}

TEST_F(MotionHandlerTest, RobotFearWithHungerNormalReading) {

}

TEST_F(MotionHandlerTest, RobotFearWithHungerMaxReading) {

}

TEST_F(MotionHandlerTest, RobotExploreNoHungerNegativeReading) {
  rExplore->get_motion_handler().UpdateVelocity(-1, -1);
  EXPECT_EQ(rExplore->get_motion_handler().get_velocity().left, 10)
    << "\nFAIL RobotExploreNoHungerNegativeReading: Left\n";
  EXPECT_EQ(rExplore->get_motion_handler().get_velocity().right, 10)
    << "\nFAIL RobotExploreNoHungerNegativeReading: Right\n";
}

TEST_F(MotionHandlerTest, RobotExploreNoHungerNormalReading) {

}

TEST_F(MotionHandlerTest, RobotExploreNoHungerMaxReading) {

}

TEST_F(MotionHandlerTest, RobotExploreWithHungerNegativeReading) {

}

TEST_F(MotionHandlerTest, RobotExploreWithHungerNormalReading) {

}

TEST_F(MotionHandlerTest, RobotExploreWithHungerMaxReading) {

}

TEST_F(MotionHandlerTest, RobotAggressionNegativeReading) {

}

TEST_F(MotionHandlerTest, RobotAggressionNoHungerNormalReading) {

}

TEST_F(MotionHandlerTest, RobotAggressionNoHungerMaxReading) {

}

#endif
