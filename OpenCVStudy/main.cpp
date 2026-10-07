#include "pch.h"
#include "CVLogger.h"

Mat CalculateHist(const Mat& target)
{
	Mat hist;

	int channels[] = { 0 };
	int histSize[] = { 256 };

	float range[] = { 0, 256 };
	const float* ranges[] = { range };

	calcHist
	(
		&target,
		1,
		channels,
		Mat(),
		hist,
		1,
		histSize,
		ranges
	);

	return hist;
}

Mat CreateHistImage(const Mat& hist)
{
	// 히스토그램을 그릴 출력 이미지의 크기
	const int histWidth = 512;
	const int histHeight = 400;

	// 히스토그램 그래프를 그릴 흰색 배경 이미지 생성
	Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(255, 255, 255));

	// 실제 히스토그램 값은 픽셀 개수이므로
	// 그래프 높이에 맞게 정규화
	Mat normalizedHist;
	normalize(hist, normalizedHist, 0, histHeight, NORM_MINMAX);

	// 히스토그램의 Bin 개수
	const int histSize = normalizedHist.rows;

	// 각 Bin이 차지할 가로 길이
	const int binWidth = cvRound(static_cast<double>(histWidth) / histSize);

	// 각 Bin의 높이를 이용하여 선 그래프 형태로 히스토그램 생성
	for (int i = 1; i < histSize; ++i)
	{
		Point prev(binWidth * (i - 1), histHeight - cvRound(normalizedHist.at<float>(i - 1)));
		Point current(binWidth * i, histHeight - cvRound(normalizedHist.at<float>(i)));

		line(histImage, prev, current, Scalar(0, 0, 0), 2);
	}

	return histImage;
}

Mat EqualizeImage(const Mat& src)
{
	Mat dst;

	// 히스토그램 평활화
	equalizeHist(src, dst);

	return dst;
}

void ShowScaled(const string& windowName, const Mat& image, double scale)
{
	// 실제 영상은 변경하지 않고 출력용 영상만 축소
	Mat displayImage;
	resize(image, displayImage, Size(), scale, scale, INTER_AREA);

	imshow(windowName, displayImage);
}

int main()
{
	// 디버거 도구 초기화
	CVLogger::SetLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);

	// 이미지 불러오기
	Mat img = imread("Resources/lena_std.tif", IMREAD_COLOR);
	if (img.empty()) return -1;

	// Grayscale 변환
	Mat src;
	cvtColor(img, src, COLOR_BGR2GRAY);

	// 원본 영상의 히스토그램 계산
	Mat srcHist = CalculateHist(src);

	// 원본 영상의 히스토그램 시각화
	Mat srcHistImage = CreateHistImage(srcHist);

	// 히스토그램 평활화
	Mat dst = EqualizeImage(src);

	// 평활화된 영상의 히스토그램 계산
	Mat dstHist = CalculateHist(dst);

	// 평활화된 영상의 히스토그램 시각화
	Mat dstHistImage = CreateHistImage(dstHist);

	// 출력 크기 비율
	const double displayScale = 0.7;

	// 출력
	ShowScaled("Source - Grayscale", src, displayScale);
	ShowScaled("Source - Histogram", srcHistImage, displayScale);
	ShowScaled("Equalized - Grayscale", dst, displayScale);
	ShowScaled("Equalized - Histogram", dstHistImage, displayScale);

	waitKey(0);

	return 0;
}