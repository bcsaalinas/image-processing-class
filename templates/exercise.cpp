#include <classroom/io.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>

int main()
{
    cv::Mat image(480, 640, CV_8UC3, cv::Scalar(32, 32, 32));

    // Your image-processing code goes here.

    const auto saved_path = classroom::write_image("result.png", image);
    std::cout << "Saved: " << saved_path << '\n';
    classroom::show_image("Result", image);
    return 0;
}
