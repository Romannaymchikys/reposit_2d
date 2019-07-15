#pragma once
#include "MyDefine.h"
#include <iostream>
#include <math.h>
#include "MyStructs.h"
class AuxiliaryFunctionalLine
{
public:
	static void changeShifts(Shifts& shifts_ONE, Shifts& shifts_TWO, const double PROPORT);
	// вычисление силы взаимодействие;
	static int auxCalcShift(int POSobj, int POSobjInteract);
	static Shifts calcShift(const CoordsOBJ coordOBJ,
		                    const CoordsOBJ coordOBJInteract);
	static int calcF(const Shifts shift);
	// функция вычесление пропорций
	static void calcProportion(Shifts& shift, const int F_FORES, const int F,
							   const int STRONG_ITERATION_F, const double COFF_INTERACT);
	// изменение координат
	static void calcShifts(Shifts& shift, const int F, const int F_MIN,
						   const int F_DIFFERENCE, const double COFF_INTERACT);
};

