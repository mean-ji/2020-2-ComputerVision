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
    Mat avg, background, image, foregroundMask, erosion, dilation;
    Mat element_dilate = getStructuringElement(MORPH_ELLIPSE, Size(6,6));
    Mat element_erode = getStructuringElement(MORPH_ELLIPSE, Size(6,6));
    
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    double fps = capture.get(CV_CAP_PROP_FPS);
    capture >> background;
    cvtColor(background, background, CV_BGR2GRAY);
    
    
    while(true) {
        if(capture.grab() == 0) break;
        capture.retrieve(image);
        cvtColor(image, image, CV_BGR2GRAY);
        
        absdiff(background, image, foregroundMask);
        threshold(foregroundMask, foregroundMask, 20, 255, CV_THRESH_BINARY);
        
        dilate(foregroundMask, erosion,element_dilate);
        erode(erosion, erosion, element_erode);
        dilate(erosion, erosion,getStructuringElement(MORPH_ELLIPSE, Size(3,3)));
        
       
        findContours(erosion, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        
        int rect = 0;
        vector<Rect> boundRect(contours.size());
               
        for (int i = 0; i < contours.size(); i++) {
            boundRect[i] = boundingRect(Mat(contours[i]));
            if (boundRect[i].area() > 1200) {
                rectangle(image, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 255), 2, 8, 0);
                rect++;
            }
        }
        
        putText(image, format("# number of people: %d", rect), Point2f(10, 40), FONT_HERSHEY_COMPLEX_SMALL, 2, Scalar(255, 255, 255),3);
        
        imshow("background subtraction", image);
        waitKey(1000/fps);
    }
    
    return 0;
}

