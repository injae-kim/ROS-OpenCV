#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <iostream>
#include <vector>
#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include <std_msgs/UInt8MultiArray.h>
#include <time.h>

clock_t start = clock();

int main(int argc, char** argv)
{
    ros::init(argc, argv, "opencv_pub");
    
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::UInt8MultiArray>("camera/image", 1000);

    cv::VideoCapture cap(0);
    cv::Mat frame;

    
    while(nh.ok())
    {
        cap >> frame;

        if(!frame.empty())
        {

            cv::imshow("frame", frame);
            // cv::imwrite("/home/helios789/catkin_ws/origin.jpg", frame);

            cv::resize(frame, frame, cv::Size(256, 256), 0, 0);

            // Encode - Decode image            
            std::vector<uchar> encode;
            std::vector<int> encode_param;
            encode_param.push_back(CV_IMWRITE_JPEG_QUALITY);
            encode_param.push_back(80);
            
            cv::imencode(".jpg", frame, encode, encode_param);

            cv::Mat decode = cv::imdecode(encode, 1);
            cv::imshow("decode", decode);

            // cv::imwrite("/home/helios789/catkin_ws/encode.jpg", decode);

            std_msgs::UInt8MultiArray msgArray;
            msgArray.data.clear();
            msgArray.data.resize(encode.size());
            std::copy(encode.begin(), encode.end(), msgArray.data.begin());

            pub.publish(msgArray);

            cv::waitKey(1);

            clock_t end = clock();
            ROS_INFO("%0.4f sec..", (double)(end-start) / 100000); 
            start = end;
            
        }

        ros::spinOnce();
    }

    return 0;
    
}