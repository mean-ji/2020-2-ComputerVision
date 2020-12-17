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
    Mat imput = imread("namecard.JPG");
    Mat edge;
    
    Point p1, p2;
    vector<Vec4i> lines;
    Mat result,result1,img;
    
    resize(imput, imput, Size(400, 400), 0, 0, CV_INTER_LINEAR);
    result = imput.clone();
    result1 = imput.clone();
    img = imput.clone();
    
    cvtColor(imput, imput, CV_BGR2GRAY);
    blur(imput, imput, Size(3,3));
    Canny(imput, edge, 170, 280, 3);
    HoughLinesP(edge, lines, 1, CV_PI / 180, 100, 90, 80);
    
    Point2f input[4];
    Point2f output[4];
    
    for (int i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        line(result1, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, 8);
        if(i==2){
            input[1] = Point(l[0], l[1]);
            input[2] = Point(l[2], l[3]);
        }
        
        if(i==3){
            input[3] = Point(l[0], l[1]);
            input[0] = Point(l[2], l[3]);
        }
    }
    
    output[0] = Point2f(0, 0);
    output[1] = Point2f(result.cols, 0);
    output[2] = Point2f(result.cols, result.rows);
    output[3] = Point2f(0, result.rows);
    
    
    Mat homo_mat = getPerspectiveTransform(input, output);
    warpPerspective(img, result, homo_mat, Size(400, 400));
    imshow("output", result);

    waitKey();
    return 0;
}
