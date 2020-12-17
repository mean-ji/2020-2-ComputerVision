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
    Mat frame, left_roi, right_roi;
    VideoCapture cap;
    Rect rect_l(200, 400, 400, 200);
    Rect rect_r(600, 400, 400, 200);
    
    // check if file exists.if none program ends
    if (cap.open("Road.mp4") == 0) {
        cout << "no such file!" << endl;
        waitKey(0);
        
    }
    
    int fps = cap.get(CAP_PROP_FPS);
    while (1) {
        cap >> frame;
        
        if (frame.empty()) {
            cout << "end of video" << endl;
            break;
        }
        
        left_roi = frame(rect_l);
        right_roi = frame(rect_r);
        
        cvtColor(left_roi, left_roi, CV_BGR2GRAY);
        cvtColor(right_roi, right_roi, CV_BGR2GRAY);
        
        blur(left_roi, left_roi, Size(5,5));
        blur(right_roi, right_roi, Size(5,5));
        
        Canny(left_roi, left_roi, 10, 60, 3);
        Canny(right_roi, right_roi, 10, 60, 3);
        
        namedWindow("Left canny");
        moveWindow("Left canny", 200, 0);
        namedWindow("Right canny");
        moveWindow("Right canny", 600, 0);
        
        imshow("Left canny", left_roi);
        imshow("Right canny", right_roi);
        
        waitKey(1000/fps);
    }
    
    
    return 0;
}

