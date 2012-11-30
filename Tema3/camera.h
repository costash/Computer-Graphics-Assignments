//clasa camera
#pragma once
#include "HeadersAndDefines.h"
#include "Vector3D.h"


class Camera{
public:
	Camera();
	~Camera();

	void translate_Forward(float dist);
	void translate_ForwardFree(float dist);
	void translate_Up(float dist);
	void translate_Right(float dist);
	void translate_RightFree(float dist);

	void rotateFPS_OY(float angle);
	void rotateFPS_OX(float angle);
	void rotateFPS_OZ(float angle);
	void rotateTPS_OY(float angle, float dist_to_interes);
	void rotateTPS_OX(float angle, float dist_to_interes);
	void rotateTPS_OZ(float angle, float dist_to_interes);

	void init();
	void render();

	float getAngleX();
	float getAngleY();

	//private:
public:
	Vector3D forward;
	Vector3D up;
	Vector3D right;
	Vector3D position;
	short int mode;
private:
	float anglex;
	float angley;
};