#include "ros/ros.h"
#include "cartographer_ros_msgs/LandmarkList.h"
#include "cartographer_ros_msgs/LandmarkEntry.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/String.h"
#include "std_msgs/Header.h"


static ros::Publisher* landmarkPtr;
std::string id;

void code_message_callback(const std_msgs::StringConstPtr& msg)
{
     id=msg->data;
}

void object_position_callback(const geometry_msgs::PoseStampedConstPtr& msg)
{

	int ret = system("clear");

	double pos_x = msg->pose.position.x;
	double pos_y = msg->pose.position.y;
	double pos_z = msg->pose.position.z;

	double ori_x = msg->pose.orientation.x;
	double ori_y = msg->pose.orientation.y;
	double ori_z = msg->pose.orientation.z;
	double ori_w = msg->pose.orientation.w;

	cartographer_ros_msgs::LandmarkList  landmark;

    landmark.header.stamp = ros::Time::now();
    landmark.header.frame_id = "base_footprint";    // 根据lua配置坐标系
    landmark.landmarks.resize(1);

	landmark.landmarks[0].id = id;
	landmark.landmarks[0].tracking_from_landmark_transform.position.x = pos_x;
	landmark.landmarks[0].tracking_from_landmark_transform.position.y = pos_y;
	landmark.landmarks[0].tracking_from_landmark_transform.position.z = pos_z;
	landmark.landmarks[0].tracking_from_landmark_transform.orientation.w = ori_w;
	landmark.landmarks[0].tracking_from_landmark_transform.orientation.x = ori_x;
	landmark.landmarks[0].tracking_from_landmark_transform.orientation.y = ori_y;
	landmark.landmarks[0].tracking_from_landmark_transform.orientation.z = ori_z;
	landmark.landmarks[0].translation_weight = 9999.9;   // double  很大的数
	landmark.landmarks[0].rotation_weight = 9999.9;

	landmarkPtr->publish(landmark);
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "publandmark_node");
    ros::NodeHandle nh;

    ros::Publisher landmark_pub = nh.advertise<cartographer_ros_msgs::LandmarkList>("landmark", 10);
    ros::Subscriber code_message_sub = nh.subscribe<std_msgs::String>("/visp_auto_tracker/code_message", 20, code_message_callback);
    ros::Subscriber object_position_sub = nh.subscribe<geometry_msgs::PoseStamped>("/visp_auto_tracker/object_position", 20, object_position_callback);

    landmarkPtr = &landmark_pub;
    ros::spin();
    return 0;
}