#include <ros/ros.h>
#include <sstream>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

sensor_msgs::LaserScan* lidar_out;
geometry_msgs::Twist* desired_velocity;

// LIDAR callback function
void lidarCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    // Store the latest LIDAR data in the global variable
    lidar_out = msg;

    // Implement obstacle avoidance logic here based on LIDAR data and wall_dist
    // Example: Check LIDAR data to see if any obstacle is closer than wall_dist
    bool obstacle_detected = false;
    for (float range : msg->ranges)
    {
        if (range < wall_dist)
        {
            obstacle_detected = true;
            break; // Stop checking once an obstacle is detected
        }
    }

    // Adjust the desired velocity based on obstacle detection
    if (obstacle_detected)
    {
        // If an obstacle is detected, stop the robot
        desired_velocity.linear.x = 0.0;
        desired_velocity.angular.z = 0.0;
    }
    else
    {
        // If no obstacle is detected, continue moving forward
        desired_velocity.linear.x = 0.2; // Adjust the forward velocity as needed
        desired_velocity.angular.z = 0.0; // No angular velocity
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "obstacle_avoidance_node");
    ros::NodeHandle n;

    // Subscribe to the LIDAR topic
    ros::Subscriber lidar_sub = n.subscribe("lidar_topic", 1, lidarCallback);

    // Create a publisher to control the robot's velocity
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);

    // Set the wall_dist parameter (already set in roslaunch)
    double wall_dist;
    ros::param::param("wall_dist", wall_dist, 0.5);

    ros::Rate loop_rate(10);  // Adjust the rate as needed

    while (ros::ok())
    {
        // Publish the desired velocity to control the robot
        cmd_vel_pub.publish(desired_velocity);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

