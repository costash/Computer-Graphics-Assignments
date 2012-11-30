#include "camera.h"

Camera::Camera()
	: anglex(0), angley(0), mode(MODE_TPS)
{
}
Camera::~Camera()
{
}

void Camera::init()
{
	position = Vector3D(0, 0, 3);
	forward = Vector3D(0, 0, -1);
	up = Vector3D(0, 1, 0);
	right = Vector3D(1, 0, 0);
}

void Camera::translate_Forward(float dist)
{
	// Translate forward like in FPS games
	Vector3D temp(forward * dist);
	position.x += temp.x;
	position.z += temp.z;
}

// Move forward free roaming style
void Camera::translate_ForwardFree(float dist)
{
	position += forward * dist;
}

void Camera::translate_Up(float dist)
{
	position += up * dist;
}

void Camera::translate_Right(float dist)
{
	// Translate right like in FPS games
	Vector3D temp(right * dist);
	position.x += temp.x;
	position.z += temp.z;
}

// Move right free roaming style
void Camera::translate_RightFree(float dist)
{
	position += right * dist;
}



// Left/right rotation is always relative to the fixed up vector (0, 1, 0)
void Camera::rotateFPS_OY(float angle)
{
	angley += angle;
	//std::cerr << "angley: " << angley << "\n\n";
	if (angley > 2 * M_PI)
		angley -= (float)(2 * M_PI);
	else if (angley < -2 * M_PI)
		angley += (float)(2 * M_PI);

	// Create projection of fwd and right vectors on XoZ plan
	Vector3D fwdProjected(forward);
	fwdProjected.y = 0.f;
	float len = fwdProjected.Length();
	fwdProjected.Normalize();
	Vector3D rightProjected(fwdProjected.CrossProduct(Vector3D(0.f, 1.f, 0.f)).Normalize());

	float sinus = sin(angle);
	float cosinus = cos(angle);

	// newforward = fwdProjected * cos + rightProjected * sin
	Vector3D temp(fwdProjected * cosinus + rightProjected * sinus);
	temp = temp.Normalize() * len;
	temp.y = forward.y;
	forward = temp.Normalize();

	// newright = rightProjected * cos - fwdProjected * sin
	right = (rightProjected * cosinus - fwdProjected * sinus).Normalize();

	// newup = newright cross newforward
	up = right.CrossProduct(forward).Normalize();
}

void Camera::rotateFPS_OX(float angle)
{
	float newangle = anglex + angle;
	//std::cerr << "newangle: " << newangle << "anglex: " << anglex << "\n";
	// Limit the up/down rotation
	if (newangle >= ANGLE_LIMIT)
		anglex = (float) ANGLE_LIMIT;
	else if (newangle <= -ANGLE_LIMIT)
		anglex = (float) -ANGLE_LIMIT;
	else
	{
		anglex = newangle;
		up = (up * cos(angle) + forward * sin(angle)).Normalize();
		forward = up.CrossProduct(right).Normalize();
	}
}

void Camera::rotateFPS_OZ(float angle)
{
	right = right * cos(angle) + up * sin(angle);
	up = right.CrossProduct(forward);
}

void Camera::rotateTPS_OY(float angle, float dist_to_interes)
{
	translate_ForwardFree(dist_to_interes);
	rotateFPS_OY(angle);
	translate_ForwardFree(-dist_to_interes);

}
void Camera::rotateTPS_OX(float angle, float dist_to_interes)
{
	translate_ForwardFree(dist_to_interes);
	rotateFPS_OX(angle);
	translate_ForwardFree(-dist_to_interes);
}
void Camera::rotateTPS_OZ(float angle, float dist_to_interes)
{
	translate_ForwardFree(dist_to_interes);
	rotateFPS_OZ(angle);
	translate_ForwardFree(-dist_to_interes);
}


void Camera::render()
{
	// Make sure all vectors are normalized
	up.Normalize();
	forward.Normalize();
	right.Normalize();

	Vector3D center = position + forward;
	/*std::cerr << "Position: " << position << " forward: " << forward
	<< " \ncenter: " << center << " up: " << up << "\n\n";

	std::cerr << "Pos_len: " << position.Length() << " fwd_len: " << forward.Length()
	<< "\ncent_len: " << center.Length() << " up_len: " << up.Length() << "\n\n";*/
	gluLookAt(position.x, position.y, position.z, 
		center.x, center.y, center.z,
		up.x, up.y, up.z);
}

float Camera::getAngleX()
{
	return anglex;
}

float Camera::getAngleY()
{
	return angley;
}