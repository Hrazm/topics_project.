#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

class TopicsProjectNode {
public:
    TopicsProjectNode() {
        // Initialize ROS node handle
        nh = ros::NodeHandle();

        // Create publisher for /cmd_vel topic
        cmd_vel_publisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

        // Create subscriber for /scan topic
        laser_scan_subscriber = nh.subscribe("/scan", 10, &TopicsProjectNode::laserScanCallback, this);
    }

    void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg) {
        // Process laser scan data and decide robot behavior
        if (scan_msg->ranges[scan_msg->ranges.size() / 2] > 1.0) {
            // No obstacle in front, move forward
            moveForward();
        } else {
            // Obstacle in front, turn left
            turnLeft();
        }
    }

    void moveForward() {
        geometry_msgs::Twist cmd_vel_msg;
        cmd_vel_msg.linear.x = 0.5;  // Adjust linear velocity as needed
        cmd_vel_msg.angular.z = 0.0;
        cmd_vel_publisher.publish(cmd_vel_msg);
    }

    void turnLeft() {
        geometry_msgs::Twist cmd_vel_msg;
        cmd_vel_msg.linear.x = 0.0;
        cmd_vel_msg.angular.z = 0.5;  // Adjust angular velocity as needed
        cmd_vel_publisher.publish(cmd_vel_msg);
    }

private:
    ros::NodeHandle nh;
    ros::Publisher cmd_vel_publisher;
    ros::Subscriber laser_scan_subscriber;
};

int main(int argc, char** argv) {
    // Initialize the ROS node
    ros::init(argc, argv, "topics_project_node");

    // Create an instance of TopicsProjectNode
    TopicsProjectNode node;

    // Spin to allow the callback function to process incoming messages
    ros::spin();

    return 0;
}
