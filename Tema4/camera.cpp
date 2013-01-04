#include "camera.h"

Camera::Camera(int mode)
	: anglex(0), angley(0), angleTpsX(0.f), mode(mode)
{
}
Camera::~Camera()
{
}

void Camera::init()
{
	anglex = 0;
	angley = 0;
	angleTpsX = 0.f;
	position = Vector3D(0, 0, 0);
	forward = Vector3D(0, 0, -1);
	up = Vector3D(0, 1, 0);
	right = Vector3D(1, 0, 0);
}

void Camera::translate_Forward(float dist)
{
	// Translate forward like in FPS games
	Vector3D temp(forward);
	temp.y = 0;
	temp.Normalize();
	temp = temp * dist;
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
	// Translate up, with fixed X position
	Vector3D temp(up);
	temp.x = 0;
	temp.Normalize();
	temp = temp * dist;
	position.y += temp.y;
	position.z += temp.z;
}

// Move Up free roaming style
void Camera::translate_UpFree(float dist)
{
	position += up * dist;
}

void Camera::translate_Right(float dist)
{
	// Translate right like in FPS games
	Vector3D temp(right);
	temp.y = 0;
	temp.Normalize();
	temp = temp * dist;
	position.x += temp.x;
	position.z += temp.z;
}

void Camera::translate_RightYoZ(float dist)
{
	//Translate right, with fixed X position
	Vector3D temp(right);
	temp.x = 0;
	temp.Normalize();
	temp = temp * dist;
	position.y += temp.y;
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
	// Make sure that angle is reset to 0 when reached 360 degrees
	angley += angle;
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

	float angleToRotate;
	// Limit the up/down rotation
	if (newangle >= ANGLE_LIMIT)
	{
		angleToRotate = float(ANGLE_LIMIT - anglex);
		anglex = (float) ANGLE_LIMIT;
		up = (up * cos(angleToRotate) + forward * sin(angleToRotate)).Normalize();
		forward = up.CrossProduct(right).Normalize();
	}
	else if (newangle <= -ANGLE_LIMIT)
	{
		angleToRotate = float(-ANGLE_LIMIT - anglex);
		anglex = (float) -ANGLE_LIMIT;
		up = (up * cos(angleToRotate) + forward * sin(angleToRotate)).Normalize();
		forward = up.CrossProduct(right).Normalize();
	}
	else
	{
		angleToRotate = angle;
		anglex = newangle;
		up = (up * cos(angleToRotate) + forward * sin(angleToRotate)).Normalize();
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