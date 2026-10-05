#include "pch.h"
#include "CVLogger.h"

struct ContrastData
{
	Mat src;
};

Mat CalculateHist(const Mat& target)
{
	Mat hist;

	int channels[] = { 0 };
	int histSize[] = { 256 };

	float range[] = { 0, 256 };
	const float* ranges[] = { range };

	calcHist
	(
		&target,     // 입력 영상
		1,           // 입력 영상 개수
		channels,    // 사용할 채널
		Mat(),       // 마스크
		hist,        // 출력 히스토그램
		1,           // 히스토그램 차원 수
		histSize,    // Bin 개수
		ranges       // 픽셀 값 범위
	);

	return hist;
}

Mat CreateHistImage(const Mat& hist)
{
	// 히스토그램을 그릴 출력 이미지의 크기
	const int histWidth = 512;
	const int histHeight = 400;

	// 히스토그램 그래프를 그릴 흰색 배경 이미지 생성
	Mat histImage
	(
		histHeight,
		histWidth,
		CV_8UC3,
		Scalar(255, 255, 255)
	);

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

Mat AdjustContrast(const Mat& src, float alpha)
{
	Mat dst;

	/*
		명암비 조절식

		dst = src + (src - 128) * alpha

		이를 정리하면,

		dst = (1 + alpha) * src - 128 * alpha

		convertTo()를 이용하면 연산 결과에
		0 ~ 255 범위의 포화 연산도 적용된다.
	*/

	src.convertTo
	(
		dst,
		CV_8UC1,
		1.0 + alpha,
		-128.0 * alpha
	);

	return dst;
}

void UpdateContrast(int trackbarValue, void* userdata)
{
	ContrastData* data = static_cast<ContrastData*>(userdata);

	// Trackbar의 0 ~ 200 값을
	// alpha의 -1.0 ~ 1.0 범위로 변환
	const float alpha = (trackbarValue - 100) / 100.0f;

	// 명암비 조절
	Mat dst = AdjustContrast(data->src, alpha);

	// 변경된 영상의 히스토그램 계산
	Mat hist = CalculateHist(dst);

	// 히스토그램 시각화
	Mat histImage = CreateHistImage(hist);

	// 영상과 히스토그램 갱신
	imshow("Lena - Grayscale", dst);
	imshow("Lena - Histogram", histImage);
}

int main()
{
	// 이미지 불러오기
	Mat img = imread("Resources/lena_std.tif", IMREAD_COLOR);
	if (img.empty()) return -1;

	// Grayscale 변환
	Mat imgGray;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	// Callback에서 사용할 데이터
	ContrastData data;
	data.src = imgGray;

	// 출력 Window 생성
	namedWindow("Lena - Grayscale", WINDOW_AUTOSIZE);
	namedWindow("Lena - Histogram", WINDOW_AUTOSIZE);

	// 명암비 조절 Trackbar 생성
	createTrackbar
	(
		"Contrast",
		"Lena - Grayscale",
		nullptr,
		200,
		UpdateContrast,
		&data
	);

	// 중앙값 100
	// alpha = 0.0이므로 원본 영상
	setTrackbarPos("Contrast", "Lena - Grayscale", 100);

	// 최초 화면 출력
	UpdateContrast(100, &data);

	waitKey(0);

	return 0;
}