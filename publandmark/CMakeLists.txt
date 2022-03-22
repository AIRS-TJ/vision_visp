cmake_minimum_required(VERSION 2.8.3)
project(publandmark)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    geometry_msgs
    cartographer_ros_msgs
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

catkin_package(
  CATKIN_DEPENDS
    roscpp
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

add_executable(publandmark_node src/publandmark.cpp)
target_link_libraries(publandmark_node  ${catkin_LIBRARIES})

install(TARGETS publandmark_node RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION} )