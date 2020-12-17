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
    vector<Rect> found;
    int i;
    char ch;
    // open the video file
    VideoCapture cap("Background.mp4");
    if (!cap.isOpened()) {
        cout << "can't open video file" << endl;
        return 0;
    }
    
    // detector (48x96 template)
    HOGDescriptor hog(
                      Size(48, 96),
                      Size(16, 16),
                      Size(8, 8),
                      Size(8, 8),
                      9);
    hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
    
    while (1) {

    cap >> frame;
    if (frame.empty()) break;

    hog.detectMultiScale(
                         frame,
                         found,
                         1.2,
                         Size(8, 8),
                         Size(32, 32),
                         1.19,
                         1.5);

        int rect = 0;
        for (i = 0; i < (int)found.size(); i++){
            cout << found[i] << endl;
            if(found[i].area()<19000 && found[i].area()>7000){
                rectangle(frame, found[i], Scalar(0, 255, 0), 2);
                rect++;
            }
            
        }
        
        
    putText(frame, format("# number of people: %d", rect), Point2f(10, 40), FONT_HERSHEY_COMPLEX_SMALL, 2, Scalar(255, 255, 255),3);
    imshow("Number of people", frame);
    ch = waitKey(10);
    if (ch == 27) break;
    }
    
    return 0;
}
