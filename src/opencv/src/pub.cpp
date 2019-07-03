#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <iostream>
#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include <time.h>

clock_t start = clock();

int main(int argc, char** argv)
{
    ros::init(argc, argv, "opencv_pub");
    
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("camera/image", 1);
    sensor_msgs::ImagePtr msg;

    cv::VideoCapture cap(0);
    cv::Mat frame;

    
    while(nh.ok())
    {
        cap >> frame;

        if(!frame.empty())
        {

            cv::imshow("frame", frame);

            msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
            pub.publish(msg);

            cv::waitKey(1000);

            clock_t end = clock();
            ROS_INFO("%0.4f sec..", (double)(end-start) / 100000); 
            start = end;
            
        }

        ros::spinOnce();
    }

    return 0;
    
}