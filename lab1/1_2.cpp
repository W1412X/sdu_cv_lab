#include<bits/stdc++.h> 
#include<opencv2/opencv.hpp>
using namespace std;
int main(int argc, char** argv){
    if(argc!=3){
        cout<<"Usage:./1_2 ori_path background_path"<<endl;
        return 0; 
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
    vector<cv::Mat>bgr_fore(3);
    vector<cv::Mat>bgr_back(3);
    //here split the img to rgb 
    cv::split(img,bgr_fore);
    cv::split(background,bgr_back);
    vector<cv::Mat>result(3);
    auto start_time = chrono::high_resolution_clock::now();
    for(int i=0;i<3;i++){
        cv::Mat fore = bgr_fore[i].clone();
        cv::Mat back = bgr_back[i].clone();
        cv::Mat alpha = alpha_mat.clone();
        fore.convertTo(fore, CV_32F);
        back.convertTo(back, CV_32F);
        alpha.convertTo(alpha, CV_32F);
        cv::Mat mul_fore = fore.mul(alpha);
        cv::Mat mul_back = back.mul(cv::Scalar(1.0) - alpha); 
        cv::Mat result_part;
        mul_fore.convertTo(mul_fore, CV_32F);
        mul_back.convertTo(mul_back, CV_32F);
        result_part = mul_fore + mul_back;
        result_part.convertTo(result[i], bgr_fore[i].type());
    }
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end_time - start_time;
    cout << "Time : " << duration.count() << " seconds" << endl;
    cv::Mat final;
    cv::merge(result,final);
    cv::imshow("Final Image", final);
    cv::waitKey(0);


}