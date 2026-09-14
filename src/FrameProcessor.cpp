#include "FrameProcessor.hpp"

#include <vector>

cv::Mat FrameProcessor::process(const cv::Mat& frame)
{
    cv::Mat output = frame.clone();

    cv::Mat edges = detectEdges(frame);

    detectContours(output, edges);

    return output;
}

cv::Mat FrameProcessor::detectEdges(const cv::Mat& frame)
{
    cv::Mat gray;
    cv::Mat blurred;
    cv::Mat edges;

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

    return edges;
}

void FrameProcessor::detectContours(
    cv::Mat& frame,
    const cv::Mat& edges
)
{
    std::vector<std::vector<cv::Point>> contours;

    cv::findContours(
        edges,
        contours,
        cv::RETR_EXTERNAL,
        cv::CHAIN_APPROX_SIMPLE
    );

    for (const auto& contour : contours)
    {
        double area = cv::contourArea(contour);

        if (area > 500)
        {
            cv::Rect boundingBox = cv::boundingRect(contour);

            cv::rectangle(
                frame,
                boundingBox,
                cv::Scalar(0, 255, 0),
                2
            );
        }
    }
}
