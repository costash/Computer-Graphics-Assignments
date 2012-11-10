#pragma once
#include "Transform3d.h"
#include "Support3d.h"

void Transform3d::translate(Point3d *pct, float tx, float ty, float tz){
	pct->x += tx;
	pct->y += ty;
	pct->z += tz;
}

void Transform3d::rotateX(Point3d *pct, float angleInRadians){
	float y_aux = pct->y;
	pct->y = pct->y * cos(angleInRadians) - pct->z * sin(angleInRadians);
	pct->z = y_aux * sin(angleInRadians) + pct->z * cos(angleInRadians);
}
void Transform3d::rotateY(Point3d *pct, float angleInRadians){
	float x_aux = pct->x;
	pct->x = pct->x * cos(angleInRadians) + pct->z * sin(angleInRadians);
	pct->z = -x_aux * sin(angleInRadians) + pct->z * cos(angleInRadians);
}
void Transform3d::rotateZ(Point3d *pct, float angleInRadians){
	float x_aux = pct->x;
	pct->x = pct->x * cos(angleInRadians) - pct->y * sin(angleInRadians);
	pct->y = x_aux * sin(angleInRadians) + pct->y * cos(angleInRadians);
}

void Transform3d::rotateXRelativeToAnotherPoint(Point3d *pct, Point3d *ref, float angleInRadians){
	translate(pct, -ref->x, -ref->y, -ref->z);
	rotateX(pct, angleInRadians);
	translate(pct, ref->x, ref->y, ref->z);
}
void Transform3d::rotateYRelativeToAnotherPoint(Point3d *pct, Point3d *ref, float angleInRadians){
	translate(pct, -ref->x, -ref->y, -ref->z);
	rotateY(pct, angleInRadians);
	translate(pct, ref->x, ref->y, ref->z);
}
void Transform3d::rotateZRelativeToAnotherPoint(Point3d *pct, Point3d *ref, float angleInRadians){
	translate(pct, -ref->x, -ref->y, -ref->z);
	rotateZ(pct, angleInRadians);
	translate(pct, ref->x, ref->y, ref->z);
}
void Transform3d::scale(Point3d *pct, float sx, float sy, float sz){
	pct->x *= sx;
	pct->y *= sy;
	pct->z *= sz;
}
void Transform3d::scaleRelativeToAnotherPoint(Point3d *pct, Point3d *ref, float sx, float sy, float sz){
	translate(pct, -ref->x, -ref->y, -ref->z);
	scale(pct, sx, sy, sz);
	translate(pct, ref->x, ref->y, ref->z);
}