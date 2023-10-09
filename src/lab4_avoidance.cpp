#include <ros/ros.h>
#include <sstream>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

	/* Below is the node for the robot to take in lidar output and avoid an obstacle by turning counterclockwise and keep moving */

sensor_msgs::LaserScan* lidar_out;
geometry_msgs::Twist desired_velocity;
geometry_msgs::Twist output_velocity;
double wall_dist;

void lidarCallback(const sensor_msgs::LaserScan::ConstPtr& msg2)
{
	ROS_INFO_ONCE("Wall distance is now: [%2.2f]", wall_dist);
    msg2->header.seq;

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
    {	 desired_velocity.linear.x = 0.0;
        desired_velocity.angular.z = 0.5;
        ROS_WARN("Detected obstacle, turning...");
    }
    else {
    	desired_velocity.linear.x = 0.5;
        desired_velocity.angular.z = 0.0;
        ROS_INFO("No obstacle detected");
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "obstacle_avoidance_node");
    ros::NodeHandle n;
    ros::Subscriber lidar_sub = n.subscribe<sensor_msgs::LaserScan>("laser_1", 10, lidarCallback);
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    ros::param::param("wall_dist", wall_dist, 0.5); /* Default to 0.5 */
    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        cmd_vel_pub.publish(desired_velocity);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

