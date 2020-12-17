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

Mat drawHistogram(Mat src) {
    Mat hist_1, hist_2, histImage;
    
    int i, hist_w, hist_h, bin_w, histSize_1, histSize_2;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    
    hist_w = 512;
    hist_h = 512;
    histSize_1 = 16;
    histSize_2 = 8;
    bin_w = cvRound((double)hist_w/histSize_1);
    
    
    histImage = Mat(hist_h,hist_w,CV_8UC3,Scalar(255,255,255));
    calcHist(&src, 1, 0, Mat(), hist_1, 1, &histSize_1, &histRange);
    normalize(hist_1,hist_1,0,histImage.rows,NORM_MINMAX,-1,Mat());
    
    for(i = 0; i < histSize_1; i++) {
        rectangle(histImage, Point(bin_w*i,hist_h), Point(bin_w*i+hist_w/histSize_1, hist_h - cvRound(hist_1.at<float>(i))), Scalar(0,0,0),-1); //draw histogram
    }
    
    calcHist(&src, 1, 0, Mat(), hist_2, 1, &histSize_2, &histRange);
    
    for(i = 0; i < histSize_2; i++) {
        hist_2.at<float>(i) = hist_2.at<float>(i)/(src.rows*src.cols); //normalized histogram
        putText(src, format("bin %d, %f",i+1,hist_2.at<float>(i)), Point(20,40+20*i), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
    }
    
    return histImage;
}


int main() {
    Mat moon;
    Mat moon_equalized;
    Mat hist_graph;
    Mat hist_equalized_graph;
    
    moon = imread("moon.png",0);
    equalizeHist(moon, moon_equalized);
    
    hist_graph = drawHistogram(moon);
    hist_equalized_graph = drawHistogram(moon_equalized);
    
    imshow("before", moon);
    imshow("after", moon_equalized);
    
    imshow("h1", hist_graph);
    imshow("h2", hist_equalized_graph);
    
    waitKey(0);
    return 0;
}

