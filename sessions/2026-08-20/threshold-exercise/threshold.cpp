#include <classroom/io.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <filesystem>

using namespace std;
using namespace cv;

int main()
{
    namespace fs = std::filesystem;

    //built in macro to get the path of the source file at compile time
    fs::path image_path = fs::path(__FILE__).parent_path() / "test.png";
    cout << "CWD: " << fs::current_path() << '\n';
    cout << "Reading: " << image_path << '\n';

    // read as grayscale for uchar thresholding
    Mat image = imread(image_path.string(), IMREAD_GRAYSCALE);

    if (image.empty()) {
        cerr << "Could not load image: " << image_path << endl;
        return 1;
    }

    int threshold_value = 128;
    Mat threshold_image(image.rows, image.cols, CV_8UC1);

    for (int j = 0; j < image.rows; ++j) {
        for (int i = 0; i < image.cols; ++i) {
            threshold_image.at<uchar>(j, i) =
                (image.at<uchar>(j, i) > threshold_value) ? 255 : 0;
        }
    }

    imshow("Input Image", image);
    imshow("Threshold Image", threshold_image);
    waitKey(0);

    const auto saved_path = classroom::write_image("result.png", threshold_image);
    cout << "Saved: " << saved_path << '\n';
    classroom::show_image("Result", threshold_image);
    return 0;
}