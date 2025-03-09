#include <opencv2/opencv.hpp>
#include "cmath"

cv::Mat image;

double sigmoid(int x, double mu, double sigma) {
    return 255.0 / (1 + exp(-(x - mu) / sigma));
}

void updateContrast(int, void*) {
    int mu = cv::getTrackbarPos("μ", "Image");
    int sigma = cv::getTrackbarPos("σ", "Image");
    
    cv::Mat adjustedImage = image.clone();
    
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            for (int k = 0; k < image.channels(); ++k) {
                adjustedImage.at<cv::Vec3b>(i, j)[k] = cv::saturate_cast<uchar>(sigmoid(image.at<cv::Vec3b>(i, j)[k], mu, sigma));
            }
        }
    }
    cv::imshow("Image", adjustedImage);
}

int main() {
    image = cv::imread("./img/a.png");
    if (image.empty()) {
        return -1;
    }

    cv::namedWindow("Image");
    int start1 = 128;
    int start2 = 20;
    int end1 = 255;
    int end2 = 100;
    cv::createTrackbar("μ", "Image", &start1, end1, updateContrast);
    cv::createTrackbar("σ", "Image", &start2, end2, updateContrast);

    updateContrast(0, 0);
    
    cv::waitKey(0);
    return 0;
}
