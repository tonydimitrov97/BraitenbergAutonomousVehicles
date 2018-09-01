// Google Test Framework
#include <gtest/gtest.h>
#include <cmath>

// Project code from the ../src directory
#include "../src/light_sensor.h"
#include "../src/light.h"
#include "../src/robot.h"
#include "../src/pose.h"
#include "../src/behavior.h"

#define HIGH_READING 30
#define LOW_READING 1

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
#ifdef LIGHTSENSOR_TESTS

/************************************************************************
* SETUP
*************************************************************************/
class LightSensorTest : public ::testing::Test {
 public:
   LightSensorTest() {}
 protected:
   virtual void SetUp() {
     // ResetTest
     ls.set_sensor_angle(40);
     ls.set_robot(rPtr);

     // NotifyOneLightMinDistance
     ls1.set_pose(csci3081::Pose(500,500));
     l1.set_pose(csci3081::Pose(500,500));

     // NotifyOneLightLargeDistance
     ls2.set_pose(csci3081::Pose(0,0));
     l2.set_pose(csci3081::Pose(1000,1000));

     // NotifyTwoLightsLowDistance
     ls3.set_pose(csci3081::Pose(500,500));
     l3.set_pose(csci3081::Pose(550,550));
     l4.set_pose(csci3081::Pose(525,525));

     // NotifyTwoLightsLargeDistance
     ls4.set_pose(csci3081::Pose(0,0));
     l5.set_pose(csci3081::Pose(950,950));
     l6.set_pose(csci3081::Pose(1000,1000));

     // LightSensorTest, NotifyTwoLightsOneCloseOneFar
     ls5.set_pose(csci3081::Pose(0,0));
     l7.set_pose(csci3081::Pose(0,0));
     l8.set_pose(csci3081::Pose(1000,1000));

     // NotifyOneLightMediumDistance
     ls6.set_pose(csci3081::Pose(0,0));
     l9.set_pose(csci3081::Pose(100,100));

     // NotifyTwoLightsMediumDistance
     ls7.set_pose(csci3081::Pose(0,0));
     l10.set_pose(csci3081::Pose(100,100));
     l11.set_pose(csci3081::Pose(150,150));

     // NotifyTwoLightsOneMediumOneLowDistance
     ls8.set_pose(csci3081::Pose(0,0));
     l12.set_pose(csci3081::Pose(0,0));
     l13.set_pose(csci3081::Pose(150,150));

     // NotifyTwoLightsOneMediumOneFarDistance
     ls9.set_pose(csci3081::Pose(0,0));
     l14.set_pose(csci3081::Pose(100,100));
     l15.set_pose(csci3081::Pose(1000,1000));

     // NotifyTwoLightSensorsEqualDistanceFromLight
     ls10.set_pose(csci3081::Pose(100,100));
     ls11.set_pose(csci3081::Pose(300,300));
     l16.set_pose(csci3081::Pose(200,200));

     // NotifyTwoLightSensorsOneCloserThanOtherToLight
     ls12.set_pose(csci3081::Pose(100,100));
     ls13.set_pose(csci3081::Pose(250,250));
     l17.set_pose(csci3081::Pose(200,200));
   }

  /* declare members */
  csci3081::Robot* rPtr = new csci3081::Robot(csci3081::kFear);
  csci3081::LightSensor ls, ls1, ls2, ls3, ls4, ls5, ls6, ls7, ls8, ls9, ls10,
    ls11, ls12, ls13;
  csci3081::Light l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14,
    l15, l16, l17;
 };

/*************************************************************/
/** TESTS for Methods of LightSensor *************************/
/*************************************************************/

TEST_F(LightSensorTest, ResetTest) {
  ls.get_robot()->set_pose(csci3081::Pose(500, 500));
  ls.Reset();
  EXPECT_EQ(ls1.get_reading(), 0)
    << "\nFAIL ResetTestReading\n";
  EXPECT_EQ(ls.get_pose().x, 500 + ls.get_robot()->get_radius() * cos(((ls.get_robot()->get_pose().theta + 40)/180)*PI))
    << "\nFAIL ResetLightSensorPositionX\n";
  EXPECT_EQ(ls.get_pose().y, 500 + ls.get_robot()->get_radius() * sin(((ls.get_robot()->get_pose().theta + 40)/180)*PI))
    << "\nFAIL ResetLightSensorPositionY\n";
}

// Notify test with one Light really close to the sensor
TEST_F(LightSensorTest, NotifyOneLightMinDistance) {
  ls1.Notify(l1.get_pose());
  EXPECT_GT(ls1.get_reading(), HIGH_READING)
    << "\nFAIL NotifyOneLightMinDistance\n";
}

// Notify test with one Light really far away from the sensor
TEST_F(LightSensorTest, NotifyOneLightLargeDistance) {
  ls2.Notify(l2.get_pose());
  EXPECT_LT(ls2.get_reading(), LOW_READING)
    << "\nFAIL NotifyOneLightLargeDistance\n";
}

// Notify test with two lights really close to the sensor
TEST_F(LightSensorTest, NotifyTwoLightsLowDistance) {
  ls3.Notify(l3.get_pose());
  ls3.Notify(l4.get_pose());
  EXPECT_GT(ls3.get_reading(), HIGH_READING)
    << "\nFAIL NotifyTwoLightsLowDistance\n";
}

// Notify test with two lights really far away from sensor
TEST_F(LightSensorTest, NotifyTwoLightsLargeDistance) {
  ls4.Notify(l5.get_pose());
  ls4.Notify(l6.get_pose());
  EXPECT_LT(ls4.get_reading(), LOW_READING)
    << "\nFAIL NotifyTwoLightsLargeDistance\n";
}

// Notify test with two lights one really close and one really far from sensor
TEST_F(LightSensorTest, NotifyTwoLightsOneCloseOneFar) {
  ls5.Notify(l7.get_pose());
  ls5.Notify(l8.get_pose());
  EXPECT_GT(ls5.get_reading(), HIGH_READING)
    << "\nFAIL NotifyTwoLightsOneCloseOneFar\n";
}

// Notify test with one light at a medium distance from the sensor
TEST_F(LightSensorTest, NotifyOneLightMediumDistance) {
  ls6.Notify(l9.get_pose());
  EXPECT_GT(ls6.get_reading(), LOW_READING)
    << "\nFAIL NotifyOneLightMediumDistance: Reading Too Low\n";
  EXPECT_LT(ls6.get_reading(), HIGH_READING)
      << "\nFAIL NotifyOneLightMediumDistance: Reading Too High\n";
}

// Notify test with two lights at a medium distance from the sensor
TEST_F(LightSensorTest, NotifyTwoLightsMediumDistance) {
  ls7.Notify(l10.get_pose());
  ls7.Notify(l11.get_pose());
  EXPECT_GT(ls7.get_reading(), LOW_READING)
    << "\nFAIL NotifyTwoLightsMediumDistance: Reading Too Low\n";
  EXPECT_LT(ls7.get_reading(), HIGH_READING)
      << "\nFAIL NotifyTwoLightsMediumDistance: Reading Too High\n";
}

// Notify test with two lights one really close to the sensor and one a medium distance
TEST_F(LightSensorTest, NotifyTwoLightsOneMediumOneLowDistance) {
  ls8.Notify(l12.get_pose());
  ls8.Notify(l13.get_pose());
  EXPECT_GT(ls8.get_reading(), HIGH_READING)
    << "\nFAIL NotifyTwoLightsOneMediumOneLowDistance\n";
}

// Notify test with two lights one at a medium distance from the sensor and one far
TEST_F(LightSensorTest, NotifyTwoLightsOneMediumOneFarDistance) {
  ls9.Notify(l14.get_pose());
  ls9.Notify(l15.get_pose());
  EXPECT_GT(ls9.get_reading(), LOW_READING)
    << "\nFAIL NotifyTwoLightsOneMediumOneFarDistance: Reading Too Low\n";
  EXPECT_LT(ls9.get_reading(), HIGH_READING)
      << "\nFAIL NotifyTwoLightsOneMediumOneFarDistance: Reading Too High\n";
}

// Testing to see if both sensors give the same light reading if they are equidistant from light
TEST_F(LightSensorTest, NotifyTwoLightSensorsEqualDistanceFromLight) {
  ls10.Notify(l16.get_pose());
  ls11.Notify(l16.get_pose());
  EXPECT_EQ(ls10.get_reading(), ls11.get_reading())
    << "\nFAIL NotifyTwoLightSensorsEqualDistanceFromLight\n";
}

// Testing if one sensor gives a higher sensor reading if it is closer to light
TEST_F(LightSensorTest, NotifyTwoLightSensorsOneCloserThanOtherToLight) {
  ls12.Notify(l17.get_pose());
  ls13.Notify(l17.get_pose());
  EXPECT_GT(ls13.get_reading(), ls12.get_reading())
    << "\nFAIL NotifyTwoLightSensorsOneCloserThanOtherToLight\n";
}

// Testing explicit value constructor
TEST_F(LightSensorTest, ExplicitValueConstructor) {
  csci3081::Robot* r1 = new csci3081::Robot(csci3081::kFear);
  r1->set_pose(csci3081::Pose(100,100));
  csci3081::LightSensor* ls8 = new csci3081::LightSensor(r1, 40);
  EXPECT_EQ(ls8->get_reading(), 0) << "\nFAIL ExplicitValueConstructor: reading\n";
  EXPECT_EQ(ls8->get_pose().x, 100 + ls8->get_robot()->get_radius() * cos(((ls8->get_robot()->get_pose().theta + 40)/180)*PI)) << "\nFAIL ExplicitValueConstructor: Pose x\n";
  EXPECT_EQ(ls8->get_pose().y, 100 + ls8->get_robot()->get_radius() * sin(((ls8->get_robot()->get_pose().theta + 40)/180)*PI)) << "\nFAIL ExplicitValueConstructor: Pose y\n";
  EXPECT_EQ(ls8->get_robot(), r1) << "\nFAIL ExplicitValueConstructor: Robot\n";
  EXPECT_EQ(ls8->get_sensor_angle(), 40) << "\nFAIL ExplicitValueConstructor: sensor angle\n";
}

// Testing CalcDistance
TEST_F(LightSensorTest, CalcDistance) {
  double distTest = ls13.CalcDistance(csci3081::Pose(0,0), csci3081::Pose(3,4));
  EXPECT_EQ(distTest, 5) << "\nFAIL CalcDistance\n";
}

#endif
