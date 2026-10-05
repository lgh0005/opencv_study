#pragma once

class CVWindow
{
	DISABLE_COPY(CVWindow)

public:
	CVWindow
	(
		const cv::String& title,
		int32 width = 800,
		int32 height = 600
	);
	~CVWindow();

public:
	void Init();
	void Run();
	void Close();
	void Resize(int32 width, int32 height);

private:
	bool IsCloseRequested() const;

private:
	cv::String m_title;
	int32 m_width	     { 800 };
	int32 m_height       { 600 };
	bool m_shouldClose   { false };
};

