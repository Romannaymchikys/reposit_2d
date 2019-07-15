#include "stdafx.h"
#include "AuxiliaryFunctionalLine.h"

//  вычесляем сдвиги (катеты) для нахождение силы
int AuxiliaryFunctionalLine::
	auxCalcShift(int POSobj, int POSobjInteract)
{
	if (POSobj > POSobjInteract)
	{
		return abs(POSobj - POSobjInteract) * -1;
	}
	else
	{
		return abs(POSobj - POSobjInteract);
	}
}
// вычесляем сдвиг
Shifts AuxiliaryFunctionalLine::
	   calcShift(const CoordsOBJ coordOBJ,
				 const CoordsOBJ coordOBJInteract)
{
	Shifts shift(0, 0, 0);
	shift.shiftPlaneX = auxCalcShift(coordOBJ.POS_X, coordOBJInteract.POS_X);
	shift.shiftPlaneY = auxCalcShift(coordOBJ.POS_Y, coordOBJInteract.POS_Y);
	shift.shiftPlaneZ = auxCalcShift(coordOBJ.POS_Z, coordOBJInteract.POS_Z);
	return shift;
}
//_____________________________________________________________________________
// вычесляем силу
int AuxiliaryFunctionalLine::calcF(const Shifts shift)
{
	return (int)sqrt(shift.shiftPlaneX * shift.shiftPlaneX +
					 shift.shiftPlaneY * shift.shiftPlaneY);
}
// функция вычесление пропорций(в дальнейшем не нужна)
void AuxiliaryFunctionalLine::
     calcProportion(Shifts& shift, const int F_FORES, const int F,
					const int STRONG_ITERATION_F, const double COFF_INTERACT)
{
	double Proportion = abs(F_FORES) / ((abs(F) - abs(STRONG_ITERATION_F)));
	if (Proportion)
	{
		shift.shiftPlaneX = ((double)shift.shiftPlaneX / Proportion) / COFF_INTERACT;
		
		shift.shiftPlaneY = ((double)shift.shiftPlaneY / Proportion) / COFF_INTERACT;
		shift.shiftPlaneZ = ((double)shift.shiftPlaneZ / Proportion) / COFF_INTERACT;
	}
}
//____________________________________________________________________________
//изменение координат
void AuxiliaryFunctionalLine::
     calcShifts(Shifts& shift, const int F, const int F_MIN,
				const int F_DIFFERENCE, const double COFF_INTERACT)
{
	// если в данный момент растижение
	if (F_DIFFERENCE > 0)
	{
		calcProportion(shift, F, F, F_MIN, COFF_INTERACT);
	}
	// если в данный момент сжатие
	else if (F_DIFFERENCE < 0)
	{
		calcProportion(shift, F, F_MIN, F, -1 * COFF_INTERACT);
	}
}
void AuxiliaryFunctionalLine::
     changeShifts(Shifts& shifts_ONE, Shifts& shifts_TWO, const double PROPORT)
{
	shifts_ONE.shiftPlaneX = ((double)shifts_ONE.shiftPlaneX / PROPORT);
	shifts_ONE.shiftPlaneY = ((double)shifts_ONE.shiftPlaneY / PROPORT);
	shifts_ONE.shiftPlaneZ = ((double)shifts_ONE.shiftPlaneZ / PROPORT);
	shifts_TWO.shiftPlaneX = ((double)shifts_TWO.shiftPlaneX * PROPORT);
	shifts_TWO.shiftPlaneY = ((double)shifts_TWO.shiftPlaneY * PROPORT);
	shifts_TWO.shiftPlaneZ = ((double)shifts_TWO.shiftPlaneZ * PROPORT);
}