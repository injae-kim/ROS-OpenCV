#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "opencv");
    cv::VideoCapture cap(0);

    cv::Mat img;
    
    while(true)
    {
        cap.read(img)

        cv::imshow("img", img);
        cv::waitKey(1)
        
        ros::spinOnce();
    }

    return 0;
    
}