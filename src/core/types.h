#ifndef _TYPES_H_
#define _TYPES_H_

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
