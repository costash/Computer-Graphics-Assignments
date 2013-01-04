//clasa camera
#pragma once
#include "HeadersAndDefines.h"
#include "Vector3D.h"

// Modes for camera
enum CameraModes
{
	MODE_FPS = 1,
	MODE_TPS = 2,
	MODE_TOP = 3
};

class Camera{
public:
	Camera(int mode);
	~Camera();

	// Translations
	void translate_Forward(float dist);		// Translation projected on XoZ
	void translate_ForwardFree(float dist);
	void translate_Up(float dist);			// Translation projected on YoZ
	void translate_UpFree(float dist);
	void translate_Right(float dist);
	void translate_RightYoZ(float dist);	// Translation projected on YoZ
	void translate_RightFree(float dist);	// Translation projected on XoZ

	// Rotations
	void rotateFPS_OY(float angle);			// Rotation made relative to (0, 1, 0) Up vector
	void rotateFPS_OX(float angle);			// Rotation capped at almost 90 degrees
	void rotateFPS_OZ(float angle);
	void rotateTPS_OY(float angle, float dist_to_interes);
	void rotateTPS_OX(float angle, float dist_to_interes);
	void rotateTPS_OZ(float angle, float dist_to_interes);

	void init();							// Inits the camera
	void render();							// Renders the camera

	float getAngleX();						// Angle for rotation around OX axis
	float getAngleY();						// Angle for rotation around OY axis

	//private:
public:
	Vector3D forward;
	Vector3D up;
	Vector3D right;
	Vector3D position;
	short int mode;							// Camera mode. Can be FPS, TPS or TOP
	float angleTpsX;
private:
	float anglex;
	float angley;
};