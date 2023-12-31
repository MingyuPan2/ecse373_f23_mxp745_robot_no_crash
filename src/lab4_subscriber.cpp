#include <ros/ros.h>
#include <sstream>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include "robot_no_crash/topic_name.h"

	/* Below is the subscriber node, derived from Lab1. */

ros::Publisher* p_pub;

void desvelCallback(const geometry_msgs::Twist::ConstPtr& msg) /* Callback funciton */
{
    p_pub->publish(*msg);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "lab4_subscriber_node");
    ros::NodeHandle n;
    ros::Publisher publisher_handle = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    p_pub = &publisher_handle;
    ros::Subscriber des_vel_sub = n.subscribe<geometry_msgs::Twist>("des_vel", 10, desvelCallback);
    ros::spin();
    return 0;
}

