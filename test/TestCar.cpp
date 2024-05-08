#include "Car.hpp"
#include <gtest/gtest.h>
#include <ros/package.h>
#include <rosneuro_filters/rosneuro_filters_utilities.hpp>

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

    TEST_F(CarTestSuite, Integration){
        std::string base_path = ros::package::getPath("rosneuro_filters_car");
        int frame_size = 32;

        ASSERT_TRUE(car_filter->configure());

        const std::string input_path = base_path + "/test/rawdata.csv";
        const std::string expected_path   = base_path + "/test/expected.csv";

        DynamicMatrix<double> input = readCSV<double>(input_path);
        DynamicMatrix<double> expected = readCSV<double>(expected_path);

        int nsamples  = input.rows();
        int nchannels = input.cols();

        DynamicMatrix<double> output = DynamicMatrix<double>::Zero(nsamples, nchannels);
        DynamicMatrix<double> frame = DynamicMatrix<double>::Zero(frame_size, nchannels);

        for(auto i = 0; i<nsamples; i = i+frame_size) {
            frame = input.middleRows(i, frame_size);
            output.middleRows(i, frame_size) = car_filter->apply(frame);
        }
        ASSERT_TRUE(output.isApprox(expected, 1e-6));
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_filter_car");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}