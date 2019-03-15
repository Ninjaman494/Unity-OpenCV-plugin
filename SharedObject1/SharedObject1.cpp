#include "SharedObject1.h"
#include <opencv2/opencv.hpp>

extern "C"
{
	/*float SharedObject1::Foopluginmethod()
	{
		cv::Mat img(10, 10, CV_8UC1); // use some OpenCV objects
		return img.rows * 1.0f;     // should return 10.0f
	}*/

	cv::Mat _currentFrame;
	cv::Mat _frameToSend;

	// Recieves an array of image bytes and converts into an Opencv Mat
	int SharedObject1::sendRawImageBytes(Color32* data, int width, int height)
	{
		_currentFrame = cv::Mat(height, width, CV_8UC4, data);
		return _currentFrame.rows;
	}

	// Convert the currentFrame Mat into an array for bytes and store in the
	// given data array
	void SharedObject1::getRawImageBytes(unsigned char* data, int width, int height)
	{
		if (_currentFrame.empty()) {
			return;
		}

		//Resize Mat to match the array passed to it from C#
		cv::Mat resizedMat(height, width, _currentFrame.type());
		cv::resize(_currentFrame, resizedMat, resizedMat.size(), cv::INTER_CUBIC);

		//Convert from BGR to ARGB 
		//cv::Mat argb_img;
		//cv::cvtColor(resizedMat, argb_img, CV_BGR2RGBA);
		//std::vector<cv::Mat> bgra;
		//cv::split(argb_img, bgra);
		//std::swap(bgra[0], bgra[3]);
		//std::swap(bgra[1], bgra[2]);
		std::memcpy(data, resizedMat.data, resizedMat.total() * resizedMat.elemSize());
	}

	void SharedObject1::setFrameToSend(cv::Mat frame) {
		_frameToSend = frame;
	}

	void SharedObject1::getSentFrame(unsigned char* data, int width, int height) {
		if (_frameToSend.empty()) {
			return;
		}

		// Resize Mat to match the array passed to it from C#
		cv::Mat resizedMat(height, width, _frameToSend.type());
		cv::resize(_frameToSend, resizedMat, resizedMat.size(), cv::INTER_CUBIC);
		// Copy over
		std::memcpy(data, resizedMat.data, resizedMat.total() * resizedMat.elemSize());
	}

	cv::Mat SharedObject1::getCurrentFrame() {
		return _currentFrame;
	}
}