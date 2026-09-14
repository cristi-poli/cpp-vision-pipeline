#ifndef FRAME_PROCESSOR_HPP
#define FRAME_PROCESSOR_HPP

#include <opencv2/opencv.hpp>

class FrameProcessor
{
public:
    cv::Mat process(const cv::Mat& frame);

private:
    cv::Mat detectEdges(const cv::Mat& frame);
    void detectContours(cv::Mat& frame, const cv::Mat& edges);
};

#endif
