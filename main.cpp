#include <opencv2/opencv.hpp>
#include <time.h>
#include "zklz_bsd.h"

static BSDProcesser bsd_processer;

int main() {
	

	VideoCapture cap;
	//cap.open("1.mp4"); // 读取视频文件
	cap.open("2020_01_05_235506_01_b.MOV"); // 读取视频文件
	Mat frame,image;
	cap >> image;
	resize(image, frame, Size(1280, 720));
	//resize(image, frame, Size(), 0.5, 0.5);

	VideoWriter outputvideo;
	outputvideo.open("testvideo.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, frame.size(), 1);

	int startframe = 0;
	int endframe = 300;
	cap.set(CAP_PROP_POS_FRAMES, startframe);  // 设置当前帧
	while (1) {
		for (int i = 0;i < 2;i++) {
			cap >> image;
		}
		
		if (image.empty()) break;
		int fnum = (int)(cap.get(CAP_PROP_POS_FRAMES));   // 记录当前帧数

		resize(image, frame, Size(1280, 720));
		//resize(image, frame, Size(), 0.5, 0.5);

		bsd_processer.Run(frame, BSD_MODE_DAY);

		namedWindow("test", CV_WINDOW_NORMAL);
		imshow("test", frame);

		outputvideo << frame;



		if (waitKey(1) >= 0) break;
		//if (fnum == endframe) {
		//	break;
		//}
	}
	
	cap.release();
	outputvideo.release();

	return 0;
}