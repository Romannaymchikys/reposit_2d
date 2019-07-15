#pragma once
#include "MyStructs.h"
#include "Point.h"
#include "math.h"
class FunctionalPoint
{
public:
	static Shifts calcShiftForce(const AngleDeviat ANGLE_FROM_X, const int F);
	static Shifts shiftsSUM(Shifts shifts, const Shifts& SHIFTS_EXTERN_INTERACT);
	// ��������� ���������
	static void sumShiftObjectCoord(CoordsOBJ& �bjectCoordinats, const Shifts SHIFTS);
	static void calcForce(Point& point_LEFT, const size_t F, const AngleDeviat angle);
	static void mainCalcWeakForce(Point& point_LEFT, Point& point_REGHT);
};

