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
    Mat frame, left_roi, right_roi, edge_l, edge_r, result;
    float l_rho, l_theta, l_a, l_b, l_x0, l_y0, r_rho, r_theta, r_a, r_b, r_x0, r_y0;
    Point l_p1, l_p2, r_p1, r_p2;
    vector<Vec2f> l_lines, r_lines;
    
    VideoCapture cap;
    Rect rect_l(200, 400, 400, 200);
    Rect rect_r(600, 400, 400, 200);
    
    // check if file exists.if none program ends
    if (cap.open("Road.mp4") == 0) {
        cout << "no such file!" << endl;
        waitKey(0);
        
    }
    
    double time = cap.get(CAP_PROP_POS_MSEC);
    int fps = cap.get(CAP_PROP_FPS);
    
    while (time<20000) {
        cap >> frame;
        result = frame.clone();
        if (frame.empty()) {
            cout << "end of video" << endl;
            break;
        }
        
        left_roi = frame(rect_l);
        right_roi = frame(rect_r);
        
        cvtColor(left_roi, left_roi, CV_BGR2GRAY);
        cvtColor(right_roi, right_roi, CV_BGR2GRAY);
        
        Canny(left_roi, edge_l, 50, 250, 3);
        Canny(right_roi, edge_r, 50, 250, 3);
        
        HoughLines(edge_l, l_lines, 1, CV_PI / 180, 100);
        HoughLines(edge_r, r_lines, 1, CV_PI / 180, 100);
        
        //left line
        l_rho = 0;
        l_theta = 0;
        int l_count = 0;
        
        for (int i = 0; i < l_lines.size(); i++) {
            if(l_lines[i][1] * (180/CV_PI) > 30 && l_lines[i][1] * (180/CV_PI) < 60) {
                l_rho += l_lines[i][0];
                l_theta += l_lines[i][1];
                l_count++;
            }
        }
        
        l_rho = l_rho / l_count;
        l_theta = l_theta / l_count;
        
        if(l_theta * (180/CV_PI) > 30 && l_theta * (180/CV_PI) < 60){
            l_a = cos(l_theta);
            l_b = sin(l_theta);
            l_x0 = l_a * l_rho;
            l_y0 = l_b * l_rho;
            l_p1 = Point(200 + cvRound(l_x0 + 1000 * (-l_b)), 400 + cvRound(l_y0 + 1000 * l_a));
            l_p2 = Point(200 + cvRound(l_x0 - 1000 * (-l_b)), 400 + cvRound(l_y0 - 1000 * l_a));
            line(result, l_p1, l_p2, Scalar(0, 0, 255), 3, 8);
            
        }
        
        
        //right line
        r_rho = 0;
        r_theta = 0;
        int r_count = 0;
        
        for (int i = 0; i < r_lines.size(); i++) {
            if(r_lines[i][1] * (180/CV_PI) > 120 && r_lines[i][1] * (180/CV_PI) < 150) {
                r_rho = r_lines[i][0];
                r_theta = r_lines[i][1];
                r_count++;
            }
        }
        
        r_rho = r_rho / r_count;
        r_theta = r_theta / r_count;
        
        if(r_theta * (180/CV_PI) > 120 && r_theta * (180/CV_PI) < 150){
            r_a = cos(r_theta);
            r_b = sin(r_theta);
            r_x0 = r_a * r_rho;
            r_y0 = r_b * r_rho;
            r_p1 = Point(600 + cvRound(r_x0 + 1000 * (-r_b)), 400 + cvRound(r_y0 + 1000 * r_a));
            r_p2 = Point(600 + cvRound(r_x0 - 1000 * (-r_b)), 400 + cvRound(r_y0 - 1000 * r_a));
            line(result, r_p1, r_p2, Scalar(0, 0, 255), 3, 8);
        }
        
        
        time = cap.get(CAP_PROP_POS_MSEC);
        imshow("Frame", result);
        
        waitKey(1000/fps);
    }
    
    
    return 0;
}

