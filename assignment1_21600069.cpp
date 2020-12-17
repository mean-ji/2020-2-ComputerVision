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
    Mat frame;
    VideoCapture cap;
    // check if file exists.if none program ends
    if (cap.open("background.mp4") == 0) {
        cout << "no such file!" << endl;
        waitKey(0);
    }
    
    double time = cap.get(CAP_PROP_POS_MSEC);
    int fps = cap.get(CAP_PROP_FPS);
    while (time<3000) {
        cap >> frame;
        if (frame.empty()) {
            cout << "end of video" << endl;
            break;
        }
        imshow("video", frame);
        int total_frames = cap.get(CAP_PROP_FRAME_COUNT);
        time = cap.get(CAP_PROP_POS_MSEC);
        double c_frame = cap.get(CAP_PROP_POS_FRAMES);
        
        waitKey(1000/fps);
        
        cout << "Frames: " << c_frame << "/" << total_frames << endl;
    }
}
