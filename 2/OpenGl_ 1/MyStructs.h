#pragma once
#include <vector>
struct CoordsOBJ
{
	CoordsOBJ(const int newPOS_X, const int newPOS_Y, const int newPOS_Z) :
		POS_X(newPOS_X), POS_Y(newPOS_Y), POS_Z(newPOS_Z){};
	int POS_X;
	int POS_Y;
	int POS_Z;
} ;
// сдвиг обекта отдельной силы во всех плоскостях 
struct Shifts
{
	Shifts(const int newShiftPlaneX,
		const int newShiftPlaneY,
		const int newShiftPlaneZ) :
		shiftPlaneX(newShiftPlaneX),
		shiftPlaneY(newShiftPlaneY),
		shiftPlaneZ(newShiftPlaneZ) {};
	int shiftPlaneX;
	int shiftPlaneY;
	int shiftPlaneZ;
};
//углы отклонение от координатной линии X
struct AngleDeviat
{
	AngleDeviat(const int newAngleByY,
		const int newAngleByZ) :
		angleByY(newAngleByY),
		angleByZ(newAngleByZ){};
	int angleByY;
	int angleByZ;
};
//сильное взаимодействие
/* определяет силу связывание мотериала
F_min и F_max диапозон при котором материал
может сжиматься и растягиваться
чем менше разница между F_min и F_max
тем жёще материал
*/
struct StrongInteract
{
	StrongInteract(const size_t newNormal, const size_t newStretchingMAX,
		 const double newCOF_INTERACT) :
		normal(newNormal), stretchingMAX(newStretchingMAX),
		COF_INTERACT(newCOF_INTERACT){};
   // точка гормоничного расположения
	size_t normal;
	// до какого предела растягивается взаимодействие между двумя точками
	size_t stretchingMAX;
	// коффициент расцяжения
	double COF_INTERACT;
	
};

// узел сил взаимодействие
struct Node
{
	size_t indexOne;
	size_t indexTwo;
};
// индексация для поиска внешних взаимодействий
struct IndexSearchExternInteract
{
	IndexSearchExternInteract(const size_t NEW_NUMBER_SPACE, const size_t NEW_NUMBER_AREA,
		                      const size_t NEW_NUMBER_LINE, const size_t NEW_NUMBER_POINT) :
		NUMBER_SPACE(NEW_NUMBER_SPACE), NUMBER_AREA(NEW_NUMBER_AREA),
		NUMBER_LINE(NEW_NUMBER_LINE), NUMBER_POINT(NEW_NUMBER_POINT) {};
	size_t NUMBER_SPACE;
	size_t NUMBER_AREA;
	size_t NUMBER_LINE;
	size_t NUMBER_POINT;
	
};
struct Force
{
	Force(const Shifts& newShifts, const AngleDeviat& newAngle, const size_t newF) :
		shifts(newShifts), angle(newAngle), F(newF) {};
	Shifts shifts;
	AngleDeviat angle;
	size_t F;
};
struct FigureColor
{
	FigureColor(const float newColor_1, const float newColor_2, const float newColor_3) :
		color_1(newColor_1), color_2(newColor_2), color_3(newColor_3) {};
	float color_1;
	float color_2;
	float color_3;
};
// пропорции икрана
/*// добовляем силы действующие на объект
// название силы, сила(растаяние на которая она дей ствует),
// угол  (напровление силы от объекта объекта,считается относительно плоскости X)
// константность силы true если сила не изменяется
///создание скорости
mBalans.creationForce(1.2, 65, false);*/

