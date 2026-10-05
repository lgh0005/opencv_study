#include "pch.h"
#include "InputManager.h"

InputManager::InputManager() = default;
InputManager::~InputManager() = default;

void InputManager::Init(const cv::String& windowName)
{
	cv::setMouseCallback(windowName, &InputManager::MouseCallback, this);
	Reset();
}

void InputManager::Update()
{
	for (auto& button : m_buttons)
	{
		button.pressed = false;
		button.released = false;
	}
	m_wheelDelta = 0;
	m_horizontalWheelDelta = 0;
	m_keyCode = cv::waitKeyEx(1);
}

void InputManager::Reset()
{
	m_buttons = {};
	m_mousePosition = {};
	m_keyCode = -1;
	m_mouseFlags = 0;
	m_wheelDelta = 0;
	m_horizontalWheelDelta = 0;
}

bool InputManager::IsMouseDown(MouseButton button) const
{
	return m_buttons.at(static_cast<std::size_t>(button)).down;
}

bool InputManager::IsMousePressed(MouseButton button) const
{
	return m_buttons.at(static_cast<std::size_t>(button)).pressed;
}

bool InputManager::IsMouseReleased(MouseButton button) const
{
	return m_buttons.at(static_cast<std::size_t>(button)).released;
}

void InputManager::MouseCallback(int event, int x, int y, int flags, void* userData)
{
	if (userData)
		static_cast<InputManager*>(userData)->OnMouse(event, x, y, flags);
}

void InputManager::OnMouse(int event, int x, int y, int flags)
{
	// 마우스 처리
	m_mousePosition = cv::Point(x, y);
	m_mouseFlags = flags;
	const int masks[] = { cv::EVENT_FLAG_LBUTTON, cv::EVENT_FLAG_RBUTTON, cv::EVENT_FLAG_MBUTTON };
	const int downEvents[] = { cv::EVENT_LBUTTONDOWN, cv::EVENT_RBUTTONDOWN, cv::EVENT_MBUTTONDOWN };
	const int upEvents[] = { cv::EVENT_LBUTTONUP, cv::EVENT_RBUTTONUP, cv::EVENT_MBUTTONUP };
	const int doubleEvents[] = { cv::EVENT_LBUTTONDBLCLK, cv::EVENT_RBUTTONDBLCLK, cv::EVENT_MBUTTONDBLCLK };
	
	// 키보드 처리
	for (usize i = 0; i < m_buttons.size(); ++i)
	{
		auto& button = m_buttons[i];
		bool down = (flags & masks[i]) != 0;
		if (event == downEvents[i] || event == doubleEvents[i]) down = true;
		if (event == upEvents[i]) down = false;
		button.pressed |= down && !button.down;
		button.released |= !down && button.down;
		button.down = down;
	}

	// 마우스 휠 이벤트 처리
	if (event == cv::EVENT_MOUSEWHEEL) m_wheelDelta += cv::getMouseWheelDelta(flags);
	else if (event == cv::EVENT_MOUSEHWHEEL) m_horizontalWheelDelta += cv::getMouseWheelDelta(flags);
}

