#include <classroom/io.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>

int main()
{
    // CV_8UC1 means: 8-bit, unsigned, one channel (a grayscale image).
    // Scalar(0) initializes every pixel to black.
    cv::Mat image(500, 500, CV_8UC1, cv::Scalar(0));

    std::cout << "OpenCV: " << CV_VERSION << '\n';
    std::cout << "Rows (height): " << image.rows << '\n';
    std::cout << "Columns (width): " << image.cols << '\n';
    std::cout << "Channels: " << image.channels() << '\n';
    std::cout << "Bytes per pixel: " << image.elemSize() << '\n';

    // Mat::at uses (row, column), which is the same as (y, x).
    // Fill a 100 x 100 white square in the center of the black image.
    for (int row = 200; row < 300; ++row) {
        for (int column = 200; column < 300; ++column) {
            image.at<uchar>(row, column) = 255;
        }
    }

    const auto saved_path = classroom::write_image("white_square.png", image);
    std::cout << "Saved image: " << saved_path << '\n';

    classroom::show_image("01 - Mat basics", image);
    return 0;
}
