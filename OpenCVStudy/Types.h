#pragma once
#include <cstdint>
#include <opencv2/core.hpp>

// Scalar Objects
using usize = std::size_t;
using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
using float32 = float;
using float64 = double;

// OpenCV Types
using Point2i = cv::Point2i;
using Point2f = cv::Point2f;
using Point2d = cv::Point2d;
using Point3i = cv::Point3i;
using Point3f = cv::Point3f;
using Point3d = cv::Point3d;
using Size2i = cv::Size2i;
using Size2f = cv::Size2f;
using Size2d = cv::Size2d;
using Rect2i = cv::Rect2i;
using Rect2f = cv::Rect2f;
using Rect2d = cv::Rect2d;
using Vec2f = cv::Vec2f;
using Vec3f = cv::Vec3f;
using Vec4f = cv::Vec4f;
using Vec2d = cv::Vec2d;
using Vec3d = cv::Vec3d;
using Vec4d = cv::Vec4d;
using Vec3b = cv::Vec3b;
using Vec4b = cv::Vec4b;
using LogLevel = cv::utils::logging::LogLevel;