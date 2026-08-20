#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace classroom {

namespace fs = std::filesystem;

// these helpers make paths consistent whether an exercise runs from Terminal or an IDE.
[[nodiscard]] inline fs::path project_dir()
{
    return CLASS_PROJECT_DIR;
}

[[nodiscard]] inline fs::path assets_dir()
{
    return project_dir() / "assets";
}

[[nodiscard]] inline fs::path asset_path(const fs::path& relative_path)
{
    return assets_dir() / relative_path;
}

[[nodiscard]] inline fs::path output_dir()
{
    const fs::path directory{CLASS_OUTPUT_DIR};
    fs::create_directories(directory);
    return directory;
}

[[nodiscard]] inline fs::path output_path(const fs::path& relative_path)
{
    if (relative_path.is_absolute()) {
        throw std::invalid_argument("output_path expects a relative path");
    }

    const fs::path path = output_dir() / relative_path;
    if (path.has_parent_path()) {
        fs::create_directories(path.parent_path());
    }
    return path;
}

inline fs::path write_image(const fs::path& relative_path, const cv::Mat& image)
{
    const fs::path path = output_path(relative_path);
    if (!cv::imwrite(path.string(), image)) {
        throw std::runtime_error("Could not write image: " + path.string());
    }
    return path;
}

// CLASSROOM_NO_GUI=1 is useful in CI or an SSH session. Normally this behaves
// like imshow + waitKey and keeps the window open until a key is pressed.
inline void show_image(const std::string& title, const cv::Mat& image, int delay_ms = 0)
{
    if (std::getenv("CLASSROOM_NO_GUI") != nullptr) {
        return;
    }
    cv::imshow(title, image);
    cv::waitKey(delay_ms);
}

}  // namespace classroom
