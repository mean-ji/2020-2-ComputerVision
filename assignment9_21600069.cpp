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
    Mat finger,adaptive_1, adaptive, finger_binary, adaptive_binary, adaptive_1_binary;
    finger = imread("Finger.png", 0);
    adaptive_1 = imread("adaptive_1.jpg",0);
    adaptive = imread("adaptive.png",0);
    
    //finger
    adaptiveThreshold(finger, finger_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 75, 15);
    
    //adaptive_1
    adaptiveThreshold(adaptive_1, adaptive_1_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 85, 15);
    
    //adaptive
    adaptiveThreshold(adaptive, adaptive_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 10);
    
    imshow("finger_print", finger_binary);
    imshow("adaptive_1", adaptive_1_binary);
    imshow("adaptive", adaptive_binary);
    waitKey(0);
    return 0;
}

