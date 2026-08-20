#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>

// usage: 01-show-images images/cat.jpeg images/dog.png images/lizard.png
int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <image> [image...]\n";
        return 1;
    }

    int x_position = 20;
    for (int i = 1; i < argc; ++i) {
        const std::string path = argv[i];

        // imread decodes an image file and returns its pixels in a mat object.
        // an empty mat means the file could not be found or decoded.
        const cv::Mat image = cv::imread(path, cv::IMREAD_COLOR);
        if (image.empty()) {
            std::cerr << "could not load: " << path << '\n';
            return 1;
        }

        // window_normal allows the window to be resized instead of using the full image size
        cv::namedWindow(path, cv::WINDOW_NORMAL);
        cv::resizeWindow(path, 380, 300);
        cv::moveWindow(path, x_position, 80);
        cv::imshow(path, image);
        x_position += 400;
    }

    std::cout << "press esc in any window to exit\n";

    // waitkey also processes window events; 27 is the key code for esc
    while (cv::waitKey(0) != 27) {
    }

    cv::destroyAllWindows();
    return 0;
}
