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
    Mat frame, middle_roi, edge_m, result;
    float m_rho, m_theta;
    Point m_p1, m_p2;
    vector<Vec2f> m_lines;
    
    VideoCapture cap;
    Rect rect_m(550, 440, 100, 200);
    
    // check if file exists.if none program ends
    if (cap.open("Road.mp4") == 0) {
        cout << "no such file!" << endl;
        waitKey(0);
        
    }
    
    int time = cap.get(CAP_PROP_POS_MSEC);
    int fps = cap.get(CAP_PROP_FPS);
    int prev = 10;
    
    while (time<35000) {
        //cout << time << endl;
        cap >> frame;
        result = frame.clone();
        if (frame.empty()) {
            cout << "end of video" << endl;
            break;
        }
        
        middle_roi = frame(rect_m);
        cvtColor(middle_roi, middle_roi, CV_BGR2GRAY);
        
        Canny(middle_roi, edge_m, 50, 200, 3);
        HoughLines(edge_m, m_lines, 1, CV_PI / 180, 100);
        
        //middle line
        m_rho = 0;
        m_theta = 0;
        int m_count = 0;
        int m_bool = 0;
        
        for (int i = 0; i < m_lines.size(); i++) {
            if(m_lines[i][1] * (180/CV_PI) > 0 && m_lines[i][1] * (180/CV_PI) < 30) {
                m_rho += m_lines[i][0];
                m_theta += m_lines[i][1];
                m_count++;
            }
        }
        
        m_rho = m_rho / m_count;
        m_theta = m_theta / m_count;
        
        if((m_theta * (180/CV_PI) > 0 && m_theta * (180/CV_PI) < 30)  ){
            m_bool = 1;
            prev = 10;
        }
        
        
        if(m_bool == 1 || prev < 10){
            putText(result, format("Warning!: Lane departure"), Point(400,100), FONT_HERSHEY_PLAIN, 3, Scalar(0, 0, 255),5);
            prev--;
            if(prev==0) prev = 10;
        }
        
        time = cap.get(CAP_PROP_POS_MSEC);
        imshow("Frame", result);
        
        waitKey(1000/(fps*20));
    }
    
    
    return 0;
}

