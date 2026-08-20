#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace {

constexpr int kSize = 300;      // every pattern is a square image of this side
constexpr int kStripe = 20;     // thickness of the line patterns, in pixels
constexpr uchar kBlack = 0;
constexpr uchar kWhite = 255;

// CV_8UC1 means: 8-bit, unsigned, one channel (a grayscale image).
cv::Mat make_canvas(uchar value = kBlack)
{
    return cv::Mat(kSize, kSize, CV_8UC1, cv::Scalar(value));
}

cv::Mat vertical_lines()
{
    cv::Mat image = make_canvas();
    // mat::at uses (row, column), which is the same as (y, x)
    for (int row = 0; row < image.rows; ++row) {
        for (int column = 0; column < image.cols; ++column) {
            image.at<uchar>(row, column) = (column / kStripe) % 2 == 0 ? kBlack : kWhite;
        }
    }
    return image;
}

cv::Mat horizontal_lines()
{
    cv::Mat image = make_canvas();
    for (int row = 0; row < image.rows; ++row) {
        for (int column = 0; column < image.cols; ++column) {
            image.at<uchar>(row, column) = (row / kStripe) % 2 == 0 ? kBlack : kWhite;
        }
    }
    return image;
}

cv::Mat horizontal_gradient()
{
    cv::Mat image = make_canvas();
    for (int row = 0; row < image.rows; ++row) {
        for (int column = 0; column < image.cols; ++column) {
            // map the column into 0..255: black on the left, white on the right
            image.at<uchar>(row, column) =
                static_cast<uchar>(column * 255 / (image.cols - 1));
        }
    }
    return image;
}

cv::Mat vertical_gradient()
{
    cv::Mat image = make_canvas();
    for (int row = 0; row < image.rows; ++row) {
        for (int column = 0; column < image.cols; ++column) {
            image.at<uchar>(row, column) = static_cast<uchar>(row * 255 / (image.rows - 1));
        }
    }
    return image;
}

cv::Mat diagonal_gradient()
{
    cv::Mat image = make_canvas();
    const int max_sum = (image.rows - 1) + (image.cols - 1);
    for (int row = 0; row < image.rows; ++row) {
        for (int column = 0; column < image.cols; ++column) {
            // the brightness grows with the distance to the top-left corner
            image.at<uchar>(row, column) = static_cast<uchar>((row + column) * 255 / max_sum);
        }
    }
    return image;
}

// a chess board of squares_per_side x squares_per_side cells
cv::Mat chess_board(int squares_per_side)
{
    cv::Mat image = make_canvas();
    const int cell = kSize / squares_per_side;
    for (int row = 0; row < image.rows; ++row) {
        for (int column = 0; column < image.cols; ++column) {
            const bool white_cell = ((row / cell) + (column / cell)) % 2 == 0;
            image.at<uchar>(row, column) = white_cell ? kWhite : kBlack;
        }
    }
    return image;
}

// white background, black square in the middle, white square inside that one
cv::Mat nested_squares()
{
    cv::Mat image = make_canvas(kWhite);
    const int outer_margin = kSize / 6;    // where the black square starts
    const int inner_margin = kSize / 3;    // where the white square starts
    for (int row = 0; row < image.rows; ++row) {
        for (int column = 0; column < image.cols; ++column) {
            const bool in_black = row >= outer_margin && row < kSize - outer_margin &&
                                  column >= outer_margin && column < kSize - outer_margin;
            const bool in_white = row >= inner_margin && row < kSize - inner_margin &&
                                  column >= inner_margin && column < kSize - inner_margin;
            if (in_white) {
                image.at<uchar>(row, column) = kWhite;
            } else if (in_black) {
                image.at<uchar>(row, column) = kBlack;
            }
        }
    }
    return image;
}

}  // namespace

int main()
{
    const std::vector<std::pair<std::string, cv::Mat>> patterns{
        {"vertical lines", vertical_lines()},
        {"horizontal lines", horizontal_lines()},
        {"horizontal gradient", horizontal_gradient()},
        {"vertical gradient", vertical_gradient()},
        {"diagonal gradient", diagonal_gradient()},
        {"chess 2x2", chess_board(2)},
        {"chess 5x5", chess_board(5)},
        {"nested squares", nested_squares()},
    };

    // lay the windows out in two rows of four
    int index = 0;
    for (const auto& [name, image] : patterns) {
        cv::namedWindow(name, cv::WINDOW_NORMAL);
        cv::resizeWindow(name, 260, 260);
        cv::moveWindow(name, 20 + (index % 4) * 290, 60 + (index / 4) * 330);
        cv::imshow(name, image);
        ++index;
    }

    std::cout << "press esc in any window to exit\n";

    // waitkey also processes window events; 27 is the key code for esc
    while (cv::waitKey(0) != 27) {
    }

    cv::destroyAllWindows();
    return 0;
}
