#pragma once

// C++
#include <iostream>
#include <vector>
#include <string_view>
#include <array>
#include <memory>
#include <algorithm>
#include <cmath>

// OpenCV
#include <opencv2/opencv.hpp>

// Custom
#include "Types.h"
#include "Defines.h"

// Managers
#include "InputManager.h"

#define INPUT InputManager::Instance()