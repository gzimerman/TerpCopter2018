#include <ros/ros.h>
#include <tera_detect/ObstacleDetection.h>
#include <sensor_msgs/Range.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>

sensor_msgs::Range lidar_msg;
geometry_msgs::PoseStamped pose_msg;
tera_detect::ObstacleDetection obstacle_status;

void tera_cb(const sensor_msgs::Range::ConstPtr &msg){
	lidar_msg = *msg;
}

void pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
	pose_msg = *msg;
}


int main(int argc, char** argv){

ros::init(argc,argv,"tera_detect");
ros::NodeHandle nh;

ros::Publisher obstacle_pub = nh.advertise<tera_detect::ObstacleDetection>
		("obsdetect", 10);

ros::Subscriber tera_sub = nh.subscribe<sensor_msgs::Range>
		("teraranger_one", 10, &tera_cb);

ros::Subscriber pose_sub = nh.subscribe<geometry_msgs::PoseStamped>
		("/mavros/local_position/pose", 10, &pose_cb);


ros::Rate rate(20.0);


while(ros::ok()){

	
	obstacle_status.range = lidar_msg.range;
	obstacle_status.distance_threshold = lidar_msg.max_range;

// To add: 
//	Convert quaternions from PoseStamped to euler angles.
//	Conditional to interpret angles/quaternions for bool types
//	within the ObstacleDetection message	
	
	//pose_msg.pose

	
//	obstacle_pub.publish(obstacle_status);

	ros::spinOnce();
        rate.sleep();
}



return 0;
}
