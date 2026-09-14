#include <opencv2/opencv.hpp>

#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "FrameProcessor.hpp"
#include "ThreadSafeQueue.hpp"

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

    ThreadSafeQueue<cv::Mat> frameQueue(5);

    std::atomic<bool> stopRequested(false);

    std::thread readerThread([&]()
    {
        cv::Mat frame;

        while (!stopRequested)
        {
            if (!video.read(frame))
            {
                break;
            }

            if (!frameQueue.push(frame.clone()))
            {
                break;
            }
        }

        frameQueue.close();
    });

    cv::Mat frame;

    while (frameQueue.waitAndPop(frame))
    {
        auto start = std::chrono::steady_clock::now();

        cv::Mat processedFrame = processor.process(frame);

        auto end = std::chrono::steady_clock::now();

        double processingTime =
            std::chrono::duration<double, std::milli>(
                end - start
            ).count();

        double fps = 0.0;

        if (processingTime > 0.0)
        {
            fps = 1000.0 / processingTime;
        }

        std::string timeText =
            "Processing: " +
            std::to_string(processingTime).substr(0, 5) +
            " ms";

        std::string fpsText =
            "FPS: " +
            std::to_string(fps).substr(0, 5);

        cv::putText(
            processedFrame,
            timeText,
            cv::Point(20, 30),
            cv::FONT_HERSHEY_SIMPLEX,
            0.7,
            cv::Scalar(0, 255, 0),
            2
        );

        cv::putText(
            processedFrame,
            fpsText,
            cv::Point(20, 60),
            cv::FONT_HERSHEY_SIMPLEX,
            0.7,
            cv::Scalar(0, 255, 0),
            2
        );

        cv::imshow("Original", frame);
        cv::imshow("Contour Detection", processedFrame);

        char key = static_cast<char>(cv::waitKey(30));

        if (key == 'q')
        {
            stopRequested = true;
            frameQueue.close();
            break;
        }
    }

    stopRequested = true;
    frameQueue.close();

    if (readerThread.joinable())
    {
        readerThread.join();
    }

    video.release();
    cv::destroyAllWindows();

    return 0;
}
