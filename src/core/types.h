#ifndef _TYPES_H_
#define _TYPES_H_
#include <glm/glm.hpp>

typedef glm::mat4 WorldMatrix;
typedef glm::mat4 ViewMatrix;
typedef glm::mat4 Projection;
typedef glm::mat4 AffineMatrix;

typedef glm::vec3 Front;
typedef glm::vec3 Up;
typedef glm::vec3 Position;
typedef glm::vec3 Scale;
typedef glm::vec3 Rotation;

typedef glm::vec2 Size2D;
typedef glm::vec2 Coordinate;

typedef float Speed;

#include <mutex>
#define MUTEX mutable std::mutex auto_mutex
#define LOCK_MUTEX const std::lock_guard<std::mutex> lock(auto_mutex)
#endif //_TYPES_H_
