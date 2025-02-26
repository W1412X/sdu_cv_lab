#include<bits/stdc++.h> 
#include<opencv2/opencv.hpp>
using namespace std;
int main(int argc, char** argv){
    if(argc!=3){
        cout<<"Usage:./1_2 ori_path background_path"<<endl;
    }
    string ori_path=argv[1];
    string background_path=argv[2];
    cv::Mat img = cv::imread(ori_path, cv::IMREAD_UNCHANGED);
    if(img.empty()){
        cout<<ori_path+" is empty"<<endl;
        return 0;
    }
    vector<cv::Mat> channels;
    cv::split(img, channels);
    cv::Mat alpha_channel=channels[3];
    //show the transparent background
    cv::imshow("alpha_channel",alpha_channel);
    
    cv::waitKey(0);
    cv::Mat background=cv::imread(background_path,cv::IMREAD_UNCHANGED);
    if(background.empty()){
        cout<<background_path+" is empty"<<endl;
        return 0;
    }
    //ensure the background is the same size as the image
    cv::resize(background,background,img.size());
    cv::Mat alpha_mat;
    alpha_channel.convertTo(alpha_mat,CV_32F,1.0/255);

    //create the foreground img without the alpha channel
    cv::Mat foreground;
    cv::Mat rgb_part[3];
    cv::split(img,rgb_part);
    cv::merge(rgb_part,3,foreground);
    cv::Mat result = foreground.mul(alpha_mat) + background.mul(1 - alpha_mat);
    cv::imshow("Final Image", result);
    cv::waitKey(0);


}