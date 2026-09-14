# C++ Real-Time Computer Vision Pipeline

A computer vision project developed in C++ using OpenCV and CMake.

The application reads video frames and performs real-time image processing using grayscale conversion, Gaussian filtering and Canny edge detection.

## Features

- C++17
- OpenCV
- CMake build system
- Real-time video processing
- Gaussian Blur
- Canny Edge Detection
- Linux build support
- Automated build using GitHub Actions

## Processing Pipeline

Video Input  
↓  
Frame Capture  
↓  
Grayscale Conversion  
↓  
Gaussian Blur  
↓  
Canny Edge Detection  
↓  
Display Results

## Requirements

- C++17 compatible compiler
- CMake 3.16+
- OpenCV

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/vision_app path/to/video.mp4
```

Press `q` to exit the application.

## Future Improvements

- Object and contour detection
- Object-oriented architecture
- Multithreaded processing
- Thread-safe frame queue
- Performance and FPS monitoring
- Python performance analysis
- AI-based object detection
