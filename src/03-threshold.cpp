#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <filesystem>
#include <iostream>


using namespace cv;

int main(){
    Mat image = imread("images/test.png", IMREAD_GRAYSCALE);

    if (image.empty()){
         std::cerr << "Could not load image: " << std::endl;
        return 1;
    }

    Mat threshold = Mat(image.rows, image.rows,CV_8UC1 );


    int threshold_value = 128;
    
    for ( int i = 0; i < image.rows; i++)
    {   
        for (int j = 0; j < image.cols; j++)
        {

            threshold.at<uchar>(i,j) = image.at<uchar>(i,j) > threshold_value ? 255 : 0;

        }
        
    }


    imshow("Input", image);
    imshow("Output", threshold);
    waitKey(0);
    
    return 0;
    


}