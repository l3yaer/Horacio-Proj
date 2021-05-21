#ifndef _TYPES_H_
#define _TYPES_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define _OS_WIN
#ifdef _WIN64
#define _OS_WIN64
#else
#define _OS_WIN32
#endif

#elif __APPLE__
#include <TargetConditionals.h>
#define _OS_DARWIN
#if TARGET_IPHONE_SIMULATOR
#define _OS_IOS_SIM
#elif TARGET_OS_IPHONE
#define _OS_IOS
#elif TARGET_OS_MAC
#define _OS_MACOS
#else
#   error "Unknown Apple platform"
#endif

#elif __linux__
#define _OS_LINUX
#elif __unix__ // all unices not caught above
#define _OS_UNIX
#elif defined(_POSIX_VERSION)
#define _OS_POSIX
#else
#   error "Unknown compiler"
#endif

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <utility>

typedef glm::mat4 WorldMatrix;
typedef glm::mat4 ViewMatrix;
typedef glm::mat4 Projection;
typedef glm::mat4 AffineMatrix;

typedef glm::vec3 Front;
typedef glm::vec3 Up;
typedef glm::vec3 Position;
typedef glm::vec3 Scale;
typedef glm::vec3 Rotation;
typedef glm::vec3 Color;

typedef glm::vec2 Size2D;
typedef glm::vec2 Coordinate;

typedef float Speed;

typedef std::pair<Coordinate, Coordinate> Bounds;

#define VEC_TO_STRING(x) glm::to_string((x))

#include <mutex>
#define MUTEX mutable std::mutex auto_mutex
#define LOCK_MUTEX const std::lock_guard<std::mutex> lock(auto_mutex)
#endif //_TYPES_H_
