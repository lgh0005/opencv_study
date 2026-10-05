#pragma once

class CVProfiler
{
	DISABLE_COPY(CVProfiler)
	DISABLE_MOVE(CVProfiler)

private:
	CVProfiler();
	~CVProfiler();

#ifdef _DEBUG
	// Starts a fresh measurement, discarding the previous result.
	void Start();

	// Returns elapsed milliseconds. Repeated calls return the same result.
	double Stop();
	void Reset();

	// Returns the completed measurement (zero until Stop is called).
	double GetElapsedMilliseconds() const;

private:
	cv::TickMeter m_timer;
	bool m_running = false;

#else
	// Keep call sites valid in Release without timer state or OpenCV calls.
	void Start() {}
	double Stop() { return 0.0; }
	void Reset() {}
	double GetElapsedMilliseconds() const { return 0.0; }
#endif
};

