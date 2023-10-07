#include <ros/ros.h>
#include <sstream>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include "robot_no_crash/topic_name.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "lab4_publisher_node");
    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    ros::Rate loop_rate(1);
    
    int count = 0;
    while (ros::ok())
    {
        geometry_msgs::Twist twist_msg;
        
        /* (.data) not working
        std::stringstream ss;
	ss << "Linear V (x, y, z)= (" << twist_msg.linear.x << ", " << twist_msg.linear.y << ", " << twist_msg.linear.z << ")"
   	<< " Angular V (x, y, z)= (" << twist_msg.angular.x << ", " << twist_msg.angular.y << ", " << twist_msg.angular.z << ")";
	twist_msg.data = ss.str();

    	  ROS_INFO("Publish twist_msg - Linear V (x, y, z)= (%f, %f, %f), Angular V (x, y, z)= (%f, %f, %f)",
          twist_msg.linear.x, twist_msg.linear.y, twist_msg.linear.z,
          twist_msg.angular.x, twist_msg.angular.y, twist_msg.angular.z);
        */
        
        cmd_vel_pub.publish(twist_msg);
        
        ros::spinOnce();
        
        loop_rate.sleep();
   	++count;
    }
    return 0;
}

