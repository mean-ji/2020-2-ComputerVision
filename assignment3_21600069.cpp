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
    Mat lena = imread("lena.png");
    //Mat lena_filtered = lena.clone();
    
    Mat moon = imread("moon.jpg");
    //Mat moon_filtered = moon.clone();
    
    Mat saltnpepper = imread("saltnpepper.png");
    Mat saltnpepper_filtered = saltnpepper.clone();
    
    //lena.png
    imshow("lena", lena);
    
    Rect lena_rect(0,0,lena.cols/2,lena.rows);
    Mat lena_rect_roi = lena(lena_rect);
    blur(lena_rect_roi, lena_rect_roi, Size(7,7));
    imshow("lena_filtered", lena);
    
    //moon.jpg
    imshow("moon",moon);
    
    Rect moon_rect(moon.cols/2,0,moon.cols/2,moon.rows);
    Mat moon_rect_roi = moon(moon_rect);
    Mat tmp;
    Mat dst;
    Laplacian(moon_rect_roi, tmp, CV_16S);
    convertScaleAbs(tmp, tmp, 1.0, 0.0);
    moon_rect_roi = tmp + moon_rect_roi;
    imshow("moon_filtered", moon);
    

    
    //saltnpepper.png
    imshow("saltnpepper", saltnpepper);
    
    medianBlur(saltnpepper, saltnpepper_filtered, 9);
    imshow("saltnpepper_filtered", saltnpepper_filtered);

    
    waitKey(0);
    return 0;
}
