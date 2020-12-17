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
    VideoCapture capture("background.mp4");
    Mat avg, background, image, foregroundMask;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    int frame_avg = 10;
    int cnt = 2;
    
    double fps = capture.get(CV_CAP_PROP_FPS);
    capture >> background;
    cvtColor(background, background, CV_BGR2GRAY);
    avg = Mat(background.rows, background.cols, CV_8UC1, Scalar(0));
    add(background/frame_avg, avg, avg);
    
    while(fps < frame_avg) {
        add(background / cnt, avg*(cnt - 1) / cnt, avg);
        cnt++;
    }
    
    while(true) {
        if(capture.grab() == 0) break;
        capture.retrieve(image);
        cvtColor(image, image, CV_BGR2GRAY);
        
        absdiff(background, image, foregroundMask);
        threshold(foregroundMask, foregroundMask, 20, 255, CV_THRESH_BINARY);
        
        findContours(foregroundMask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        
        int rect = 0;
        vector<Rect> boundRect(contours.size());
               
        for (int i = 0; i < contours.size(); i++) {
            boundRect[i] = boundingRect(Mat(contours[i]));
            if (boundRect[i].area() > 400) {
                rectangle(image, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 255), 2, 8, 0);
                rect++;
            }
        }
        
        putText(image, format("# Rect: %d", rect), Point2f(15, 40), FONT_HERSHEY_COMPLEX_SMALL, 2, Scalar(255, 255, 255),3);
        
        imshow("background subtraction", image);
        waitKey(1000/fps);
    }
    
    return 0;
}

