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
    VideoCapture capture("Faces.mp4");
    CascadeClassifier face_classifier;
    Mat frame, grayframe;
    vector<Rect> faces;
    int temp;
   
    face_classifier.load("haarcascade_frontalface_alt.xml");
    
    int fps = capture.get(CAP_PROP_FPS);
    
    while(1) {
        capture >> frame;
        int u_input = waitKey(1000/fps);
      
        if(u_input == 102) {
            while(1) {
                if((u_input = waitKey(1000/fps)) != 102 && u_input!=-1) break;
                cvtColor(frame, grayframe, COLOR_BGR2GRAY);
                face_classifier.detectMultiScale(
                    grayframe,
                    faces,
                    1.1, // increase search scale by 10% each pass
                    3, // merge groups of three detections
                    0, // not used for a new cascade
                    Size(30, 30) //min size
                );
                
                temp = faces[0].area();
                int count=0;

                for (int i = 0; i < faces.size(); i++) {
                    if (faces[i].area() < temp) {
                        count = i;
                    }
                }
                
                Point lb(faces[count].x + faces[count].width, faces[count].y + faces[count].height);
                Point tr(faces[count].x, faces[count].y);
                rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
                imshow("Faces", frame);
                capture >> frame;
                //u_input = waitKey(1000/fps);
            }
        }
        if(u_input == 109) {
            while(1) {
                if((u_input = waitKey(1000/fps)) != 109 && u_input!=-1) break;
                cvtColor(frame, grayframe, COLOR_BGR2GRAY);
                face_classifier.detectMultiScale(
                    grayframe,
                    faces,
                    1.1, // increase search scale by 10% each pass
                    3, // merge groups of three detections
                    0, // not used for a new cascade
                    Size(30, 30) //min size
                );
                
                Point lb(faces[faces.size()/2].x + faces[faces.size()/2].width, faces[faces.size()/2].y + faces[faces.size()/2].height);
                Point tr(faces[faces.size()/2].x, faces[faces.size()/2].y);
                rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
                imshow("Faces", frame);
                capture >> frame;
                //u_input = waitKey(1000/fps);
            }
        }
        if(u_input == 110) {
            while(1) {
                if((u_input = waitKey(1000/fps)) != 110 && u_input!=-1) break;
                cvtColor(frame, grayframe, COLOR_BGR2GRAY);
                face_classifier.detectMultiScale(
                    grayframe,
                    faces,
                    1.1, // increase search scale by 10% each pass
                    3, // merge groups of three detections
                    0, // not used for a new cascade
                    Size(30, 30) //min size
                );
                
                temp = faces[0].area();
                int count=0;

                for (int i = 0; i < faces.size(); i++) {
                    if (faces[i].area() > temp) {
                        count = i;
                    }
                }
                
                Point lb(faces[count].x + faces[count].width, faces[count].y + faces[count].height);
                Point tr(faces[count].x, faces[count].y);
                rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
                imshow("Faces", frame);
                capture >> frame;
                
            }
        }
        if(u_input == 27) {
            break;
        }
        
        imshow("Faces", frame);
        //u_input = waitKey(1000/fps);
    }
    return 0;
}
