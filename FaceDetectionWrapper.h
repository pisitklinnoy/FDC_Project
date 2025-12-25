#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <vector>
#include <string>

class FaceDetectionWrapper
{
private:
    std::vector<cv::Rect> detectedFaces;
    cv::Mat currentImage;

public:
    bool LoadImageFile(const std::string& path)
    {
        currentImage = cv::imread(path);
        return !currentImage.empty();
    }

    int DetectFaces(const std::string& cascadePath)
    {
        if (currentImage.empty()) return 0;

        cv::CascadeClassifier faceCascade;
        if (!faceCascade.load(cascadePath))
        {
            return -1;
        }

        cv::Mat grayImage;
        cv::cvtColor(currentImage, grayImage, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(grayImage, grayImage);

        detectedFaces.clear();
        faceCascade.detectMultiScale(grayImage, detectedFaces, 1.1, 3, 0, cv::Size(30, 30));

        return (int)detectedFaces.size();
    }

    int GetFaceCount() const
    {
        return (int)detectedFaces.size();
    }

    bool GetFaceRect(int index, int& x, int& y, int& width, int& height)
    {
        if (index < 0 || index >= (int)detectedFaces.size())
            return false;

        cv::Rect face = detectedFaces[index];
        x = face.x;
        y = face.y;
        width = face.width;
        height = face.height;
        return true;
    }

    bool SaveFaceImage(int index, const std::string& outputPath)
    {
        if (currentImage.empty() || index < 0 || index >= (int)detectedFaces.size())
            return false;

        cv::Mat faceImage = currentImage(detectedFaces[index]);
        return cv::imwrite(outputPath, faceImage);
    }

    bool GetImageWithRectangle(int index, std::vector<uchar>& buffer)
    {
        if (currentImage.empty() || index < 0 || index >= (int)detectedFaces.size())
            return false;

        cv::Mat displayImage = currentImage.clone();
        cv::rectangle(displayImage, detectedFaces[index], cv::Scalar(0, 255, 0), 2);

        return cv::imencode(".bmp", displayImage, buffer);
    }

    double ComputeDistance(const std::string& face1Path, const std::string& face2Path)
    {
        cv::Mat img1 = cv::imread(face1Path);
        cv::Mat img2 = cv::imread(face2Path);

        if (img1.empty() || img2.empty())
            return -1.0;

        cv::Mat f1, f2;
        cv::resize(img1, f1, cv::Size(100, 100));
        cv::resize(img2, f2, cv::Size(100, 100));

        cv::cvtColor(f1, f1, cv::COLOR_BGR2GRAY);
        cv::cvtColor(f2, f2, cv::COLOR_BGR2GRAY);

        f1.convertTo(f1, CV_32F);
        f2.convertTo(f2, CV_32F);

        return cv::norm(f1, f2, cv::NORM_L2);
    }

    bool SaveCurrentFace(int index, const std::string& outputPath)
    {
        if (currentImage.empty() || index < 0 || index >= (int)detectedFaces.size())
            return false;

        cv::Mat faceImage = currentImage(detectedFaces[index]);
        return cv::imwrite(outputPath, faceImage);
    }
};
