#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

#include "FrameProcessor.hpp"

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

    FrameProcessor processor;

    cv::Mat frame;

    while (true)
    {
        video >> frame;

        if (frame.empty())
        {
            break;
        }

        cv::Mat edges = processor.process(frame);

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
