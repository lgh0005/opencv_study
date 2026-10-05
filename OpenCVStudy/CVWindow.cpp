#include "pch.h"
#include "CVWindow.h"
#include "InputManager.h"

CVWindow::CVWindow
(
    const cv::String& title,
    int32 width,
    int32 height
) : m_title(title),
    m_width(width),
    m_height(height) { }

CVWindow::~CVWindow() = default;

void CVWindow::Init()
{
    // 윈도우 초기화
    cv::namedWindow(m_title, cv::WINDOW_NORMAL);
    cv::resizeWindow(m_title, m_width, m_height);
    m_shouldClose = false;

    // 매니저 초기화
    INPUT.Init(m_title);
}

void CVWindow::Run()
{
    while (!m_shouldClose)
    {
        INPUT.Update();

        if (IsCloseRequested())
        {
            m_shouldClose = true;
        }
    }
}

void CVWindow::Close()
{
    // 윈도우 종료
    m_shouldClose = true;
    cv::destroyWindow(m_title);

    // 매니저 정리
    INPUT.Reset();
}

void CVWindow::Resize(int32 width, int32 height)
{
    m_width = width;
    m_height = height;
    cv::resizeWindow(m_title, m_width, m_height);
}

bool CVWindow::IsCloseRequested() const
{
    return cv::getWindowProperty(m_title, cv::WND_PROP_VISIBLE) < 1.0;
}
