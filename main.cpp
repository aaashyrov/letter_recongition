#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Mat> getLettersFromImage(const cv::Mat &image) {
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::Mat thresh;
  cv::threshold(gray, thresh, 0, 255, cv::THRESH_BINARY);
  cv::Mat image_erode;
  cv::Mat white = cv::Mat(3, 3, gray.type(), cv::Scalar(255, 255, 255));
  cv::erode(thresh, image_erode, white);

  std::vector<cv::Vec4i> hierarchy;
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(image_erode, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point(0, 0));

  cv::Mat output;
  image.copyTo(output);

  for (size_t i = 0; i < contours.size(); i++) {
    auto v = cv::boundingRect(contours.at(i));
      if(v.width*v.height>200) {
        cv::rectangle(output, cv::Rect(v.x, v.y, v.width, v.height), cv::Scalar(70, 0, 0), 1);
      }
  }

  cv::imshow("input", image);
  cv::imshow("Enlarged", image_erode);
  cv::imshow("output", output);
  cv::waitKey(0);

  return output;
}

int main() {

  getLettersFromImage(cv::imread("/home/alisher/Desktop/raspoznovania_obrazov/lab1/yellow_objects/models/u.png"));

  return 0;
}
