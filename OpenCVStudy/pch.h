#pragma once

// C++
#include <iostream>
#include <vector>
#include <string_view>
#include <array>
#include <memory>
#include <algorithm>
#include <cmath>
#include <filesystem>
using namespace std;

// OpenCV
#include <opencv2/opencv.hpp>
using namespace cv;

// Custom
#include "Types.h"
#include "Defines.h"

// Managers
#include "InputManager.h"

#define INPUT InputManager::Instance()