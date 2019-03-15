#pragma once

#include <opencv2/opencv.hpp>
extern "C"
{
	namespace SharedObject1
	{
		struct Color32
		{
			uchar r;
			uchar g;
			uchar b;
			uchar a;
		};
		int sendRawImageBytes(Color32* data, int width, int height);

		void getRawImageBytes(unsigned char* data, int width, int height);

		void setFrameToSend(cv::Mat frame);

		cv::Mat getCurrentFrame();

		void getSentFrame(unsigned char* data, int width, int height);
	}
}