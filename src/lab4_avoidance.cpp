#include <ros/ros.h>
#include <sstream>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

sensor_msgs::LaserScan* lidar_out;
geometry_msgs::Twist desired_velocity;
geometry_msgs::Twist output_velocity;
double wall_dist;

void lidarCallback(const sensor_msgs::LaserScan::ConstPtr& msg2)
{
    ROS_INFO("Laser?: [%d]", msg2->header.seq);

    bool obstacle = false;
    for (float range : msg2->ranges)
    {
        if (range < wall_dist)
        {
            obstacle = true;
            break;
        }
    }
    if (obstacle)
    {	desired_velocity.linear.x = 0.0;
        desired_velocity.angular.z = 1.0;
    }
    else {
    	desired_velocity.linear.x = 0.5;
        desired_velocity.angular.z = 0.0;
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "obstacle_avoidance_node");
    ros::NodeHandle n;
    ros::Subscriber lidar_sub = n.subscribe<sensor_msgs::LaserScan>("laser_1", 10, lidarCallback);
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    ros::param::param("wall_dist", wall_dist, 0.1);
    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        cmd_vel_pub.publish(desired_velocity);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

