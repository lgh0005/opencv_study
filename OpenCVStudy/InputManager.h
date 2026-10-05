#pragma once

enum class MouseButton 
{ 
	Left, 
	Right, 
	Middle 
};

struct ButtonState
{
	bool down = false;
	bool pressed = false;
	bool released = false;
};

class InputManager
{
	DECLARE_SINGLE(InputManager)

private:
	InputManager();
	~InputManager();

public:

	// One window, on its UI thread. Call after namedWindow.
	void Init(const cv::String& windowName);

	// Call once per frame before queries; also pumps HighGUI events.
	void Update();
	void Reset();

public:
	// Key events/repeats only: HighGUI does not report keyboard releases.
	// -1 means no event. Special-key codes are backend dependent.
	int32 GetKeyCode() const { return m_keyCode; }
	bool IsKeyPressed(int32 key) const { return key >= 0 && m_keyCode == key; }

public:
	cv::Point GetMousePosition() const { return m_mousePosition; }
	bool IsMouseDown(MouseButton button) const;
	bool IsMousePressed(MouseButton button) const;
	bool IsMouseReleased(MouseButton button) const;
	int32 GetWheelDelta() const { return m_wheelDelta; }
	int32 GetHorizontalWheelDelta() const { return m_horizontalWheelDelta; }

	// Flags from the last mouse event, includingd Ctrl/Shift/Alt.
	int32 GetMouseFlags() const { return m_mouseFlags; }

private:
	static void MouseCallback(int32 event, int32 x, int32 y, int32 flags, void* userData);
	void OnMouse(int32 event, int32 x, int32 y, int32 flags);

	std::array<ButtonState, 3> m_buttons {};
	cv::Point m_mousePosition {};
	int32 m_keyCode = -1;
	int32 m_mouseFlags = 0;
	int32 m_wheelDelta = 0;
	int32 m_horizontalWheelDelta = 0;
};

