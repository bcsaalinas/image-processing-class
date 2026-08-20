#include <opencv2/opencv.hpp>

#include <filesystem>
#include <iostream>
#include <string>

void display_image(const std::string& window_name, const cv::Mat& image, int x_position)
{
    // window_normal allows the window to be resized instead of using the full image size
    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    cv::resizeWindow(window_name, 380, 300);
    cv::moveWindow(window_name, x_position, 80);
    cv::imshow(window_name, image);
}

int main()
{
    // the built-in file macro gives this source file's path at compile time
    const std::filesystem::path images_dir = std::filesystem::path(__FILE__).parent_path();

    // joining path pieces this way avoids fragile working-directory assumptions
    const std::filesystem::path cat_path = images_dir / "cat.jpeg";
    const std::filesystem::path dog_path = images_dir / "dog.png";
    const std::filesystem::path lizard_path = images_dir / "lizard.png";

    // imread decodes an image file and returns its pixels in a mat object
    const cv::Mat cat = cv::imread(cat_path.string(), cv::IMREAD_COLOR);
    const cv::Mat dog = cv::imread(dog_path.string(), cv::IMREAD_COLOR);
    const cv::Mat lizard = cv::imread(lizard_path.string(), cv::IMREAD_COLOR);

    // an empty mat means that imread could not find or decode the file
    if (cat.empty()) {
        std::cerr << "could not load: " << cat_path << '\n';
        return 1;
    }
    if (dog.empty()) {
        std::cerr << "could not load: " << dog_path << '\n';
        return 1;
    }
    if (lizard.empty()) {
        std::cerr << "could not load: " << lizard_path << '\n';
        return 1;
    }

    display_image("cat", cat, 20);
    display_image("dog", dog, 420);
    display_image("lizard", lizard, 820);

    std::cout << "press esc in any image window to exit\n";

    // waitkey also processes window events; 27 is the key code for esc
    while (cv::waitKey(0) != 27) {
    }

    cv::destroyAllWindows();    
    return 0;
}
