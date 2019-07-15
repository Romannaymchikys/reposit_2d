#include "stdafx.h"
#include "FunctionalPoint.h"


// вычесляет сдвиг в каждой плоскости отдельной силы
Shifts FunctionalPoint::
       calcShiftForce(const AngleDeviat ANGLE_FROM_X, const int F)
{
	/* вычеляем сдвиг(на сколько и в какую сторану данная сила
	сдвинит обект в определенной плоскости (X или Y или Z))
	данные углы создают отрицательный либо
	положительный деапозон сдвигов
	для оси X от 270 до 90 сдвиг положительный(вправо)
	для оси Y от 0 до 180 сдвиг положительный(вверх)
	затем от вида сдвига(положительный или отрицательный,
	на кокой координатной оси)
	добовляем его в определенный вектор с точно такимиже сдвигоми
	расмотрим нашу силу как одну из сторон прямоугольного
	трехугольника.
	сторона оbjectCoordinats.second и coordXandY.second -
	являются катетам паралельным координатной оси Y
	сторона оbjectCoordinats.first и coordXandY.first -
	являются катетам паралельным координатной оси X
	в данном случае F - можно назвать длинну гипотенузы
	вычисляем пропорцию относительно длинны нашей гипатенузы
	при помощи синуса и косинуса
	SIN - (пропорция)восколько катет поролельный оси Y меньше гипотенузы
	COS - (пропорция)восколько катет поролельный оси X меньше гипотенузы*/
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
	/* для вычисление сдвига по оси X в трех мерии
	сдвиг по z = сдвигу x, а x вычесляется при помощи z
	расмотрим прямоугольны трехугольник
	сдвиг z = x = гипотенузе
	проекция на ось x(непосредственно сам сдвиг x)
	является катетом который с гипотенузой образует угол Z
	тоесть выходят непосредственно с самого объекта
	тоесть чтобы найти newX нам нужно сдвиг Z(гипотенузу)
	умнохить на ( угол Z * PI/ 180)
	сдвиг X
	newShiftPlaneXandYandZ.second.second =
	cos(forse.routePlaneXandY * PI / 180) * forse.F;
	newShiftPlaneXandYandZ.second.first =
	cos(forse.routePlaneZ * PI / 180) * newShiftPlaneXandYandZ.second.second;
	сдвиг Z
	катет поролельный оси Z
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
// ИЗМЕНЕНИЕ КООРДИНАТ
void FunctionalPoint::
     sumShiftObjectCoord(CoordsOBJ& оbjectCoordinats, 
		                 const Shifts SHIFTS )
{
	
	оbjectCoordinats.POS_X += SHIFTS.shiftPlaneX;
	оbjectCoordinats.POS_Y += SHIFTS.shiftPlaneY;
	оbjectCoordinats.POS_Z += SHIFTS.shiftPlaneZ;
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