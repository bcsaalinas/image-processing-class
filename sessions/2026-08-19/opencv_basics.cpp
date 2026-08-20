#include <classroom/io.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>

int main()
{
    std::cout << "OpenCV version: " << CV_VERSION << '\n';

    // OpenCV colors are BGR, so (30, 30, 30) is a dark neutral background.
    cv::Mat image(600, 800, CV_8UC3, cv::Scalar(30, 30, 30));

    cv::circle(image, cv::Point(400, 280), 120, cv::Scalar(0, 255, 255), cv::FILLED);
    cv::rectangle(
        image,
        cv::Point(100, 100),
        cv::Point(250, 220),
        cv::Scalar(255, 100, 50),
        cv::FILLED
    );
    cv::putText(
        image,
        "OpenCV works",
        cv::Point(270, 520),
        cv::FONT_HERSHEY_SIMPLEX,
        1.2,
        cv::Scalar(255, 255, 255),
        2
    );

    const auto saved_path = classroom::write_image("result.png", image);
    std::cout << "Saved: " << saved_path << '\n';

    classroom::show_image("OpenCV basics", image);
    return 0;
}
