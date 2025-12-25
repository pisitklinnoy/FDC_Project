#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <string>

class FaceDetector
{
public:
    static std::vector<cv::Rect> DetectFaces(const cv::Mat& image, const std::string& cascadePath)
    {
        std::vector<cv::Rect> faces;
        
        cv::CascadeClassifier faceCascade;
        if (!faceCascade.load(cascadePath))
        {
            return faces;
        }

        cv::Mat grayImage;
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(grayImage, grayImage);

        faceCascade.detectMultiScale(grayImage, faces, 1.1, 3, 0, cv::Size(30, 30));
        
        return faces;
    }

    static double ComputeSimilarity(const cv::Mat& face1, const cv::Mat& face2)
    {
        cv::Mat f1, f2;
        cv::resize(face1, f1, cv::Size(100, 100));
        cv::resize(face2, f2, cv::Size(100, 100));

        cv::cvtColor(f1, f1, cv::COLOR_BGR2GRAY);
        cv::cvtColor(f2, f2, cv::COLOR_BGR2GRAY);

        f1.convertTo(f1, CV_32F);
        f2.convertTo(f2, CV_32F);

        double distance = cv::norm(f1, f2, cv::NORM_L2);
        return distance;
    }
};
