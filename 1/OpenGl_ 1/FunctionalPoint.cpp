#include "stdafx.h"
#include "FunctionalPoint.h"


// ��������� ����� � ������ ��������� ��������� ����
Shifts FunctionalPoint::
       calcShiftForce(const AngleDeviat ANGLE_FROM_X, const int F)
{
	/* �������� �����(�� ������� � � ����� ������� ������ ����
	������� ����� � ������������ ��������� (X ��� Y ��� Z))
	������ ���� ������� ������������� ����
	������������� �������� �������
	��� ��� X �� 270 �� 90 ����� �������������(������)
	��� ��� Y �� 0 �� 180 ����� �������������(�����)
	����� �� ���� ������(������������� ��� �������������,
	�� ����� ������������ ���)
	��������� ��� � ������������ ������ � ����� �������� ��������
	��������� ���� ���� ��� ���� �� ������ ��������������
	�������������.
	������� �bjectCoordinats.second � coordXandY.second -
	�������� ������� ����������� ������������ ��� Y
	������� �bjectCoordinats.first � coordXandY.first -
	�������� ������� ����������� ������������ ��� X
	� ������ ������ F - ����� ������� ������ ����������
	��������� ��������� ������������ ������ ����� ����������
	��� ������ ������ � ��������
	SIN - (���������)��������� ����� ����������� ��� Y ������ ����������
	COS - (���������)��������� ����� ����������� ��� X ������ ����������*/
	Shifts shift(0, 0, 0);
	double SIN, COS;
	if (ANGLE_FROM_X.angleByY == 0 || ANGLE_FROM_X.angleByY == 90 ||
		ANGLE_FROM_X.angleByY == 180 || ANGLE_FROM_X.angleByY == 270)
	{
		switch (ANGLE_FROM_X.angleByY)
		{
		case (270): SIN = -1, COS = 0; break;
		case (180): SIN = 0, COS = -1; break;
		case (90):  SIN = 1, COS = 0;  break;
		case (0):   SIN = 0, COS = 1;  break;
		}
	}
	else
	{
		SIN = sin(ANGLE_FROM_X.angleByY * PI / 180);
		COS = cos(ANGLE_FROM_X.angleByY * PI / 180);
	}
	shift.shiftPlaneY = SIN * F;
	shift.shiftPlaneX = COS * F;
	return shift;
	/* ��� ���������� ������ �� ��� X � ���� �����
	����� �� z = ������ x, � x ����������� ��� ������ z
	��������� ������������ ������������
	����� z = x = ����������
	�������� �� ��� x(��������������� ��� ����� x)
	�������� ������� ������� � ����������� �������� ���� Z
	������ ������� ��������������� � ������ �������
	������ ����� ����� newX ��� ����� ����� Z(����������)
	�������� �� ( ���� Z * PI/ 180)
	����� X
	newShiftPlaneXandYandZ.second.second =
	cos(forse.routePlaneXandY * PI / 180) * forse.F;
	newShiftPlaneXandYandZ.second.first =
	cos(forse.routePlaneZ * PI / 180) * newShiftPlaneXandYandZ.second.second;
	����� Z
	����� ����������� ��� Z
	newShiftPlaneXandYandZ.first =
	sin(forse.routePlaneZ * PI / 180) * newShiftPlaneXandYandZ.second.second;
	*/
}
Shifts FunctionalPoint::
        shiftsSUM(Shifts shifts,
			      const Shifts& SHIFTS_EXTERN_INTERACT)
{
	shifts.shiftPlaneX += SHIFTS_EXTERN_INTERACT.shiftPlaneX;
	shifts.shiftPlaneY += SHIFTS_EXTERN_INTERACT.shiftPlaneY;
	shifts.shiftPlaneZ += SHIFTS_EXTERN_INTERACT.shiftPlaneZ;
	return shifts;
}
// ��������� ���������
void FunctionalPoint::
     sumShiftObjectCoord(CoordsOBJ& �bjectCoordinats, 
		                 const Shifts SHIFTS )
{
	
	�bjectCoordinats.POS_X += SHIFTS.shiftPlaneX;
	�bjectCoordinats.POS_Y += SHIFTS.shiftPlaneY;
	�bjectCoordinats.POS_Z += SHIFTS.shiftPlaneZ;
}
void FunctionalPoint::calcForce(Point& point,
	                            const size_t F, const AngleDeviat ANGLE)
{
	const int F_PUSHING = F - point.weight;
	if (F_PUSHING > 0)
	{
		point.shiftsInertia = FunctionalPoint::calcShiftForce(ANGLE, F_PUSHING);
	}
}
void FunctionalPoint::mainCalcWeakForce(Point& point_LEFT,
	                                    Point& point_REGHT)
{
	double proportia;

	if (point_LEFT.weight > point_REGHT.weight)
	{
		proportia = (double)point_LEFT.weight / (double)point_REGHT.weight;

	}
	else if (point_REGHT.weight > point_LEFT.weight)
	{
		proportia = (double)point_REGHT.weight / (double)point_LEFT.weight;

	}
	else {
		proportia = 1;
	}
	if ((point_LEFT.shiftsInertia.shiftPlaneX >= 0 && point_REGHT.shiftsInertia.shiftPlaneX >= 0) ||
		(point_LEFT.shiftsInertia.shiftPlaneX <= 0 && point_REGHT.shiftsInertia.shiftPlaneX <= 0))
	{
		if ((abs(point_LEFT.shiftsInertia.shiftPlaneX) <= abs(point_REGHT.shiftsInertia.shiftPlaneX)) &&
			point_LEFT.weight >= point_REGHT.weight)
		{
			int shift_LEFT_X = point_LEFT.shiftsInertia.shiftPlaneX;		
			point_LEFT.shiftsInertia.shiftPlaneX = (point_REGHT.shiftsInertia.shiftPlaneX -
				point_LEFT.shiftsInertia.shiftPlaneX) / proportia + point_LEFT.shiftsInertia.shiftPlaneX;
			point_REGHT.shiftsInertia.shiftPlaneX = shift_LEFT_X;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneX) >= abs(point_REGHT.shiftsInertia.shiftPlaneX)) &&
			point_LEFT.weight >= point_REGHT.weight)
		{
			int shift_LEFT_X = point_LEFT.shiftsInertia.shiftPlaneX;		
			point_LEFT.shiftsInertia.shiftPlaneX = point_LEFT.shiftsInertia.shiftPlaneX -
				(point_LEFT.shiftsInertia.shiftPlaneX - point_REGHT.shiftsInertia.shiftPlaneX) /
				proportia;
			point_REGHT.shiftsInertia.shiftPlaneX = shift_LEFT_X;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneX) <= abs(point_REGHT.shiftsInertia.shiftPlaneX)) &&
			point_LEFT.weight <= point_REGHT.weight)
		{
			int shift_REGHT_X = point_REGHT.shiftsInertia.shiftPlaneX;
			point_REGHT.shiftsInertia.shiftPlaneX = (point_LEFT.shiftsInertia.shiftPlaneX -
				point_REGHT.shiftsInertia.shiftPlaneX) / proportia + point_REGHT.shiftsInertia.shiftPlaneX;
			point_LEFT.shiftsInertia.shiftPlaneX = shift_REGHT_X;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneX) >= abs(point_REGHT.shiftsInertia.shiftPlaneX)) &&
			point_LEFT.weight <= point_REGHT.weight)
		{
			int shift_REGHT_X = point_REGHT.shiftsInertia.shiftPlaneX;
			point_REGHT.shiftsInertia.shiftPlaneX = point_REGHT.shiftsInertia.shiftPlaneX -
				(point_REGHT.shiftsInertia.shiftPlaneX - point_LEFT.shiftsInertia.shiftPlaneX) /
				proportia;
			point_LEFT.shiftsInertia.shiftPlaneX = shift_REGHT_X;
		}
	}
	else if ((point_LEFT.shiftsInertia.shiftPlaneX > 0 && point_REGHT.shiftsInertia.shiftPlaneX < 0) ||
		     (point_LEFT.shiftsInertia.shiftPlaneX < 0 && point_REGHT.shiftsInertia.shiftPlaneX > 0))
	{
		if ((abs(point_LEFT.shiftsInertia.shiftPlaneX) <= abs(point_REGHT.shiftsInertia.shiftPlaneX)) &&
			point_LEFT.weight >= point_REGHT.weight)
		{
			int shift_LEFT_X = point_LEFT.shiftsInertia.shiftPlaneX;
			point_LEFT.shiftsInertia.shiftPlaneX = point_LEFT.shiftsInertia.shiftPlaneX +
				point_REGHT.shiftsInertia.shiftPlaneX / proportia;
			point_REGHT.shiftsInertia.shiftPlaneX = point_REGHT.shiftsInertia.shiftPlaneX + 
				shift_LEFT_X * proportia;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneX) >= abs(point_REGHT.shiftsInertia.shiftPlaneX)) &&
			point_LEFT.weight >= point_REGHT.weight)
		{
			int shift_LEFT_X = point_LEFT.shiftsInertia.shiftPlaneX;
			point_LEFT.shiftsInertia.shiftPlaneX = point_LEFT.shiftsInertia.shiftPlaneX +
				point_REGHT.shiftsInertia.shiftPlaneX / proportia;
			point_REGHT.shiftsInertia.shiftPlaneX = shift_LEFT_X;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneX) <= abs(point_REGHT.shiftsInertia.shiftPlaneX)) &&
			point_LEFT.weight <= point_REGHT.weight)
		{
			int shift_REGHT_X = point_REGHT.shiftsInertia.shiftPlaneX;
			point_REGHT.shiftsInertia.shiftPlaneX = point_REGHT.shiftsInertia.shiftPlaneX +
				point_LEFT.shiftsInertia.shiftPlaneX / proportia;
			point_LEFT.shiftsInertia.shiftPlaneX = point_LEFT.shiftsInertia.shiftPlaneX +
				shift_REGHT_X * proportia;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneX) >= abs(point_REGHT.shiftsInertia.shiftPlaneX)) &&
			point_LEFT.weight <= point_REGHT.weight)
		{
			int shift_REGHT_X = point_REGHT.shiftsInertia.shiftPlaneX;
			point_REGHT.shiftsInertia.shiftPlaneX = point_REGHT.shiftsInertia.shiftPlaneX +
				point_LEFT.shiftsInertia.shiftPlaneX / proportia;
			point_LEFT.shiftsInertia.shiftPlaneX = shift_REGHT_X;
		}
	}
	if ((point_LEFT.shiftsInertia.shiftPlaneY >= 0 && point_REGHT.shiftsInertia.shiftPlaneY >= 0) ||
		(point_LEFT.shiftsInertia.shiftPlaneY <= 0 && point_REGHT.shiftsInertia.shiftPlaneY <= 0))
	{
		if ((abs(point_LEFT.shiftsInertia.shiftPlaneY) <= abs(point_REGHT.shiftsInertia.shiftPlaneY)) &&
			point_LEFT.weight >= point_REGHT.weight)
		{
			int shift_LEFT_Y = point_LEFT.shiftsInertia.shiftPlaneY;
			point_LEFT.shiftsInertia.shiftPlaneY = (point_REGHT.shiftsInertia.shiftPlaneY -
				point_LEFT.shiftsInertia.shiftPlaneY) / proportia + point_LEFT.shiftsInertia.shiftPlaneY;
			point_REGHT.shiftsInertia.shiftPlaneY = shift_LEFT_Y;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneY) >= abs(point_REGHT.shiftsInertia.shiftPlaneY)) &&
			point_LEFT.weight >= point_REGHT.weight)
		{
			int shift_LEFT_Y = point_LEFT.shiftsInertia.shiftPlaneY;
			point_LEFT.shiftsInertia.shiftPlaneY = point_LEFT.shiftsInertia.shiftPlaneY -
				(point_LEFT.shiftsInertia.shiftPlaneY - point_REGHT.shiftsInertia.shiftPlaneY) /
				proportia;
			point_REGHT.shiftsInertia.shiftPlaneY = shift_LEFT_Y;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneY) <= abs(point_REGHT.shiftsInertia.shiftPlaneY)) &&
			point_LEFT.weight <= point_REGHT.weight)
		{
			int shift_REGHT_Y = point_REGHT.shiftsInertia.shiftPlaneY;
			point_REGHT.shiftsInertia.shiftPlaneY = (point_LEFT.shiftsInertia.shiftPlaneY -
				point_REGHT.shiftsInertia.shiftPlaneY) / proportia + point_REGHT.shiftsInertia.shiftPlaneY;
			point_LEFT.shiftsInertia.shiftPlaneY = shift_REGHT_Y;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneY) >= abs(point_REGHT.shiftsInertia.shiftPlaneY)) &&
			point_LEFT.weight <= point_REGHT.weight)
		{
			int shift_REGHT_Y = point_REGHT.shiftsInertia.shiftPlaneY;
			point_REGHT.shiftsInertia.shiftPlaneY = point_REGHT.shiftsInertia.shiftPlaneY -
				(point_REGHT.shiftsInertia.shiftPlaneY - point_LEFT.shiftsInertia.shiftPlaneY) /
				proportia;
			point_LEFT.shiftsInertia.shiftPlaneY = shift_REGHT_Y;
		}
	}
	else if ((point_LEFT.shiftsInertia.shiftPlaneY > 0 && point_REGHT.shiftsInertia.shiftPlaneY < 0) ||
		(point_LEFT.shiftsInertia.shiftPlaneY < 0 && point_REGHT.shiftsInertia.shiftPlaneY > 0))
	{
		if ((abs(point_LEFT.shiftsInertia.shiftPlaneY) <= abs(point_REGHT.shiftsInertia.shiftPlaneY)) &&
			point_LEFT.weight >= point_REGHT.weight)
		{
			int shift_LEFT_Y = point_LEFT.shiftsInertia.shiftPlaneY;
			point_LEFT.shiftsInertia.shiftPlaneY = point_LEFT.shiftsInertia.shiftPlaneY +
				point_REGHT.shiftsInertia.shiftPlaneY / proportia;
			point_REGHT.shiftsInertia.shiftPlaneY = point_REGHT.shiftsInertia.shiftPlaneY +
				shift_LEFT_Y * proportia;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneY) >= abs(point_REGHT.shiftsInertia.shiftPlaneY)) &&
			point_LEFT.weight >= point_REGHT.weight)
		{
			int shift_LEFT_Y = point_LEFT.shiftsInertia.shiftPlaneY;
			point_LEFT.shiftsInertia.shiftPlaneY = point_LEFT.shiftsInertia.shiftPlaneY +
				point_REGHT.shiftsInertia.shiftPlaneY / proportia;
			point_REGHT.shiftsInertia.shiftPlaneY = shift_LEFT_Y;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneY) <= abs(point_REGHT.shiftsInertia.shiftPlaneY)) &&
			point_LEFT.weight <= point_REGHT.weight)
		{
			int shift_REGHT_Y = point_REGHT.shiftsInertia.shiftPlaneY;
			point_REGHT.shiftsInertia.shiftPlaneY = point_REGHT.shiftsInertia.shiftPlaneY +
				point_LEFT.shiftsInertia.shiftPlaneY / proportia;
			point_LEFT.shiftsInertia.shiftPlaneY = point_LEFT.shiftsInertia.shiftPlaneY +
				shift_REGHT_Y * proportia;
		}
		else if ((abs(point_LEFT.shiftsInertia.shiftPlaneY) >= abs(point_REGHT.shiftsInertia.shiftPlaneY)) &&
			point_LEFT.weight <= point_REGHT.weight)
		{
			int shift_REGHT_Y = point_REGHT.shiftsInertia.shiftPlaneY;
			point_REGHT.shiftsInertia.shiftPlaneY = point_REGHT.shiftsInertia.shiftPlaneY +
				point_LEFT.shiftsInertia.shiftPlaneY / proportia;
			point_LEFT.shiftsInertia.shiftPlaneY = shift_REGHT_Y;
		}
	}
}