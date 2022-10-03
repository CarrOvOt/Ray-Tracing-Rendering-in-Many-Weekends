#include "ray.h"

Ray::Ray(vec3 origin, vec3 direction):orig(origin),dir(direction) {
}

vec3 Ray::at(float t){

	return orig + dir * t;
}
