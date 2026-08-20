#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>


using namespace cv;


int main(){
    Mat image = imread("images/cat.jpeg", IMREAD_ANYCOLOR);

    imshow("Output", image);

    return 0;
}