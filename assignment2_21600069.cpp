//
//  main.cpp
//  opencv_project
//
//  Created by 김민지 on 02/09/2020.
//  Copyright © 2020 김민지. All rights reserved.
//

#include "cv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main() {
    Mat image = imread("lena.png",0);
    Mat negative_img = image.clone();
    
    Mat image_1 = image.clone();
    Mat log_img = Mat::zeros(image_1.size(), image_1.type());
    
    Mat image_2 = image.clone();
    
    //nagative_img
    for(int i = 0; i < image.cols; i++){
        for(int j = 0; j < image.rows; j++){
            image.at<uchar>(j, i) = 255 - image.at<uchar>(j, i);
        }
    }
    
    imshow("negative_img", image);

    
    //log_img
    add(image_1, Scalar(1), image_1);
    image_1.convertTo(image_1, CV_32F);
    log(image_1, log_img);

    normalize(log_img, log_img, 0, 255, NORM_MINMAX);
    convertScaleAbs(log_img, log_img, 1.5);
    
    imshow("log_img", log_img);
    
    //answer
//    double c = 1.5f
//    image.convertTo(image, CV_32F);
//    image = abs(image) +1;
//    log(image, image);
//    image = c+ image;
//    normalize(image, image, 0, 255, NORM_MINMAX);
//    convertScaleAbs(log_img, image);
    
    //gamma_img
    Mat table(1, 256, CV_8U);
    uchar* p = table.ptr();
    Mat gamma_img = image_2.clone();

    for( int i = 0; i < 256; ++i) p[i] = saturate_cast<uchar>(pow(i / 255.0, 0.5) * 255.0);
    LUT(image_2, table, gamma_img);

    imshow("gamma_img", gamma_img);
    
    //answer
//    Mat[]terator_<uchar> it, end;
//    float gamma = 0.5f;
//    unsigned char pix[256];
//
//    for( int i = 0; i < 256; ++i) pix[i] = (pow(float)(i / 255.0, 0.5) * 255.0f);
//    gamma_img = image.clone();
//
//    for(it = gamma_img.begin<uchar>(), end = gamma_img.end<uchar>(); it != end; it++){
//        *it = pix[(*it)];
//    }
    
    
    waitKey(0);
    return 0;
}
