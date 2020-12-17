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
    CascadeClassifier face_classifier;
    Mat frame, grayframe, backgound;
    Mat result, bgModel, fgModel, foreground;
    vector<Rect> faces;
    int i;
    
    Mat m_backproj, hsv;
    Mat m_model3d;
    Rect m_rc;
    float hrange[] = { 0,180 };
    float vrange[] = { 0,255 };
    float srange[] = { 0,255 };
    const float* ranges[] = { hrange, srange, vrange }; // hue, saturation, brightness
    int channels[] = { 0, 1, 2 };
    int hist_sizes[] = { 16, 16, 16 };
    
    //open the webcam
    VideoCapture cap(0);
    backgound = imread("background.png");
    
    //check successed
    if(!cap.isOpened()) {
        cout << "Could not open camera" << endl;
        return -1;
    }
    //face detection configuration
    face_classifier.load("haarcascade_frontalface_alt.xml");
    
    while(true) {
        //get a new frame from webcam
        cap >> frame;
        
        //convert captured frame to gray scale
        cvtColor(frame, grayframe, COLOR_BGR2GRAY);
        face_classifier.detectMultiScale(
                                grayframe,
                                faces,
                                1.3,
                                3,
                                0,
                                Size(30,30)
        );
        
        //draw the results
            Point lb(faces[0].x + faces[0].width, faces[0].y + faces[0].height);
            Point tr(faces[0].x, faces[0].y);
            //rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
            Rect rectangle(lb, tr);
            
            //histogram backprojection
            //calcBackProject(&frame, 1, channels, m_model3d, m_backproj, ranges);
            //tracking
            //meanShift(m_backproj, rectangle, TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
            //rectangle(frame, m_rc, Scalar(0, 0, 255), 3);
 
            grabCut(frame, result, rectangle, bgModel, fgModel, 10, GC_INIT_WITH_RECT);
            compare(result, GC_PR_FGD, result, CMP_EQ);
            foreground = Mat(frame.size(), CV_8UC3, Scalar(255,255,255));
            frame.copyTo(foreground, result);
            
            for(int i = 0; i < foreground.rows; i++) {
                for(int j = 0; j < foreground.cols; j++) {
                    if(foreground.at<Vec3b>(i,j)[0]==255 && foreground.at<Vec3b>(i,j)[1]==255 &&
                       foreground.at<Vec3b>(i,j)[2]==255) {
                        foreground.at<Vec3b>(i,j)[0] = backgound.at<Vec3b>(i,j)[0];
                        foreground.at<Vec3b>(i,j)[1] = backgound.at<Vec3b>(i,j)[1];
                        foreground.at<Vec3b>(i,j)[2] = backgound.at<Vec3b>(i,j)[2];
                    }
                }
            }
        
        //print the output
        imshow("Project3", foreground);
        if(waitKey(33) == 27) break;
    }
    
    return 0;
}
