#include "Car.hpp"
#include <gtest/gtest.h>

namespace rosneuro {

class CarTestSuite : public ::testing::Test {
    public:
        CarTestSuite() {};
        ~CarTestSuite() {};
        void SetUp() override {
            car_filter = new Car<double>();
        }
        void TearDown() override {
            delete car_filter;
        }
        Car <double>* car_filter;
};

TEST_F(CarTestSuite, TestCarName) {
    EXPECT_EQ(car_filter->name_, "car");
}

TEST_F(CarTestSuite, TestCarConfigure) {
    EXPECT_TRUE(car_filter->configure());
}

TEST_F(CarTestSuite, TestCarApply) {
    DynamicMatrix<double> input(3, 3);
    input << 1, 2, 3,
             4, 5, 6,
             7, 8, 9;

    DynamicMatrix<double> expected_output(3, 3);
    expected_output << -1, 0, 1,
                       -1, 0, 1,
                       -1, 0, 1;
    ASSERT_EQ(car_filter->apply(input), expected_output);
}

}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_filter_car");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}