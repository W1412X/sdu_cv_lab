#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace std;
void showImg(string&path){
    cv::Mat img = cv::imread(path);
    if(img.empty()){
        cout<<"img is empty"<<endl;
        return;
    }
    cv::imshow(path,img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
int main(int argc,char*argv[]){
    if(argc!=2){
        cout<<"usage:./main path"<<endl;
    }else{
        string path=argv[1];
        showImg(path);
    }
}