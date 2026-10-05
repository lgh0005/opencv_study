#include "pch.h"
#include "CVLogger.h"
#include "CVWindow.h"

CVWindow g_window("OpenCVStudy");

int main()
{
	// 디버거 도구 초기화
	CVLogger::SetLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);

	// 윈도우 시작
	g_window.Init();
	g_window.Run();
	
	return 0;
}
