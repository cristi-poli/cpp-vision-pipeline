#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: ./vision_app <video_path>\n";
        return 1;
    }

    std::string videoPath = argv[1];

    cv::VideoCapture video(videoPath);

    if (!video.isOpened())
    {
        std::cerr << "Error: Could not open video.\n";
        return 1;
    }

    cv::Mat frame;
    cv::Mat gray;
    cv::Mat blurred;
    cv::Mat edges;

    while (true)
    {
        video >> frame;

        if (frame.empty())
        {
            break;
        }

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        cv::GaussianBlur(
            gray,
            blurred,
            cv::Size(5, 5),
            0
        );

        cv::Canny(
            blurred,
            edges,
            50,
            150
        );

        cv::imshow("Original", frame);
        cv::imshow("Edge Detection", edges);

        char key = static_cast<char>(cv::waitKey(30));

        if (key == 'q')
        {
            break;
        }
    }

    video.release();
    cv::destroyAllWindows();

    return 0;
}
