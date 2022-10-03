#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp >


using glm::vec3;

class Ray {
public:

	vec3 orig;
	vec3 dir;


	Ray() = default;

	Ray(vec3 orig, vec3 dir);


	vec3 at(float t);









};
