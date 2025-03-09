#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
using namespace std;

int main(int argc, char** argv){
    string ori_path = "./img/a.png";
    string background_path = "./img/test.jpeg";

    cv::Mat img = cv::imread(ori_path, cv::IMREAD_UNCHANGED);
    if(img.empty()){
        cout << ori_path + " is empty" << endl;
        return 0;
    }

    // Split the image into 4 channels (BGRA)
    vector<cv::Mat> channels;
    cv::split(img, channels);

    // Extract the alpha channel
    cv::Mat alpha_channel = channels[3];

    // Show the alpha channel (transparency mask)
    cv::imshow("Alpha Channel", alpha_channel);
    cv::waitKey(0);

    // Load the background image
    cv::Mat background = cv::imread(background_path, cv::IMREAD_UNCHANGED);
    if(background.empty()){
        cout << background_path + " is empty" << endl;
        return 0;
    }

    // Ensure the background is the same size as the image
    cv::resize(background, background, img.size());

    // Convert the alpha channel to float
    cv::Mat alpha_mat;
    alpha_channel.convertTo(alpha_mat, CV_32F, 1.0 / 255);

    // Prepare the foreground (without alpha channel)
    vector<cv::Mat> bgr_fore(3), bgr_back(3);
    cv::split(img, bgr_fore);  // Split foreground into BGR channels
    cv::split(background, bgr_back);  // Split background into BGR channels

    // Prepare result channels
    vector<cv::Mat> result(3,cv::Mat(img.rows,img.cols, CV_32F));
    auto start_time = chrono::high_resolution_clock::now();
    // Traverse each pixel by using pointers
    for(int i = 0; i < 3; i++) {
        // Create pointers to the image data
        cv::Mat fore_data = bgr_fore[i];
        cv::Mat back_data = bgr_back[i];
        cv::Mat alpha_data = alpha_mat;
        int num_pixels = img.rows * img.cols;

        for(int j = 0; j < img.rows; j++) {
            //get the row address
            uchar* data_fore=fore_data.ptr<uchar>(j);
            uchar* data_back=back_data.ptr<uchar>(j);
            float* data_alpha=alpha_data.ptr<float>(j);
            float* data_result=result[i].ptr<float>(j);
            for(int k = 0; k < img.cols; k++) {
                data_result[k]=data_fore[k] * data_alpha[k]+data_back[k]*(1.0f - data_alpha[k]);
            }
        }
        result[i].convertTo(result[i], bgr_fore[i].type());
    }
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end_time - start_time;
    cout << "Time : " << duration.count() << " seconds" << endl;

    // Merge the result channels to create the final image
    cv::Mat final;
    cv::merge(result, final);
    // Show the final image
    cv::imshow("Final Image", final);
    cv::waitKey(0);

    return 0;
}
