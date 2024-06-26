cmake_minimum_required(VERSION 2.8.3)
project(rosneuro_filters_car)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(ROSNEURO_DATA_MIN_VERSION "1.0.0")

##############################################################################
# Find dependencies
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
			 roscpp 
			 roslib
			 std_msgs
			 pluginlib
			 rosneuro_filters)

find_package(Eigen3 REQUIRED)
find_package(GTest REQUIRED)
find_package(PkgConfig)

SET(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(${catkin_INCLUDE_DIRS} 
                    ${EIGEN3_INCLUDE_DIRS}
					include
					include/${PROJECT_NAME}/)

##############################################################################
# Define package
##############################################################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES 
  ${PROJECT_NAME}
	
  CATKIN_DEPENDS
  	roscpp
	roslib
	std_msgs
	pluginlib
	rosneuro_filters
  DEPENDS
)


##############################################################################
# Build
##############################################################################

catkin_add_gtest(TestFilterCar test/TestCar.cpp)
target_link_libraries(TestFilterCar ${GTEST_BOTH_LIBRARIES} pthread gmock ${Eigen3_LIBRARIES})
target_link_libraries(TestFilterCar ${PROJECT_NAME} ${catkin_LIBRARIES})
include_directories(${GTEST_INCLUDE_DIRS} gmock pthread include include/${PROJECT_NAME}/)

add_definitions(${EIGEN3_DEFINITIONS})

## Plugin

# DC Spatial filter
add_library(${PROJECT_NAME} src/Car.cpp)
target_link_libraries(${PROJECT_NAME} ${Eigen3_LIBRARIES} 
									  ${catkin_LIBRARIES}
)

#################
## Executables ##
#################

add_executable(car_simloop_config example/car_simloop_config.cpp)
target_link_libraries(car_simloop_config ${PROJECT_NAME} ${catkin_LIBRARIES}) 


#################
##   Install   ##
#################
install(TARGETS ${PROJECT_NAME}

	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(FILES plugins_rosneuro_filters_car.xml
	DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
