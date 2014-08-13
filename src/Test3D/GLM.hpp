#ifndef GLM_H
#define GLM_H

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#define Mat4 glm::detail::tmat4x4<double,glm::highp>
#define Mat3 glm::detail::tmat3x3<double,glm::highp>
#define Vec3 glm::detail::tvec3<double,glm::highp>
#define Vec4 glm::detail::tvec4<double,glm::highp>

#endif
