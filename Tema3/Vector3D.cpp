#include "Vector3D.h"

std::ostream& operator<< (std::ostream& os, const Vector3D &v2)
{
	os << "(" << v2.x << "," << v2.y << "," << v2.z <<")";
	return os;
}