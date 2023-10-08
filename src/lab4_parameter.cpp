#include <ros/ros.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "lab4_parameter_node");
    ros::NodeHandle n;

	double wall_dist = 0.0;
	std::string param_name = "/robot0/wall_dist";
	ROS_INFO_ONCE("wall_dist began with: [%2.2f]", wall_dist);
	
	if (n.getParamCached(param_name, wall_dist)) 
	{
	ROS_INFO("wall_dist was updated to: [%2.2f]", wall_dist);
	}
	ROS_INFO_ONCE("wall_dist is now: [%2.2f]", wall_dist);

    return 0;
}
