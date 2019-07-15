#include "stdafx.h"
#include "FunctionalLine.h"
// не правильно указываются связи
size_t FunctionalLine::
       calcStrongInteraction_LEFT(Line& line, Point& pointOne,
	                              Point& pointTwo, int& size, 
		                          int& i, const int INDEX,
	                              const int INDEX_SIZE)
{
	Shifts shifts = AuxiliaryFunctionalLine::
		calcShift(pointOne.coordsObj, pointTwo.coordsObj);
	size_t F = AuxiliaryFunctionalLine::calcF(shifts);
	// проверка на разрыв
	if (F > line.strongInteraction.stretchingMAX)
	{
		line.vecStrongInteract.erase(line.vecStrongInteract.begin() + i);
		size += INDEX_SIZE;
	}
	else {
		if (F - line.strongInteraction.normal != 0)
		{
			AuxiliaryFunctionalLine::calcShifts(shifts, F,
				line.strongInteraction.normal, F - line.strongInteraction.normal,
				line.strongInteraction.COF_INTERACT);
		}
		pointOne.inertia = shifts;
			//FunctionalPoint::sumShiftObjectCoord(pointOne.coordsObj, shifts);
			//line.vecPoints[indexOne] = pointOne;
		i += INDEX;
	}
	return F;
}
Shifts FunctionalLine::
       calcStrongInteraction_RIGHT(Line& line, Point& pointOne,
	                               Point& pointTwo,int& size, int& i,
	                               const int INDEX, const int INDEX_SIZE)
{
	Shifts shifts(0, 0, 0);
	shifts = AuxiliaryFunctionalLine::
		calcShift(pointOne.coordsObj, pointTwo.coordsObj);
	size_t F = AuxiliaryFunctionalLine::calcF(shifts);
	// проверка на разрыв
	if (F > line.strongInteraction.stretchingMAX)
	{
		line.vecStrongInteract.erase(line.vecStrongInteract.begin() + i);
		size += INDEX_SIZE;
	}
	else {
		if (F - line.strongInteraction.normal != 0)
		{
			AuxiliaryFunctionalLine::calcShifts(shifts, F,
				line.strongInteraction.normal, F - line.strongInteraction.normal,
				line.strongInteraction.COF_INTERACT);	
		}
		//FunctionalPoint::sumShiftObjectCoord(pointOne.coordsObj, shifts);
		//line.vecPoints[indexOne] = pointOne;
		pointOne.inertia = shifts;
		i += INDEX;
	}
	return shifts;
}
// ____________________________________________________________________________
//проверка - есть ли у точки сильное взаимодействие
// т.е. связи в векторе vecPairInteract
struct Test {
	size_t index;
	Test(const size_t i) : index(i) {}
	bool operator() (const Node& node) {
		return index == node.indexOne || index == node.indexTwo;
	}
};
void  FunctionalLine::checkPointsForInteraction(Line& line)
{
	int size = line.vecPoints.size() - 1;
	std::pair<size_t, size_t> myPair;
	for (size_t i(0); i < size; ++i)
	{
		auto result = std::find_if(line.vecStrongInteract.begin(),
			line.vecStrongInteract.end(), Test(i));
		if (result == line.vecStrongInteract.end())
		{
			line.vecPoints[i].weight = 0;
		}
	}
}
//___________________________________________________________________________
void FunctionalLine::
     mainCalcStrongInteraction(std::vector<Line>& vecShapes, Line& line,
	                           const size_t NUMBER_SPACE,
	                           const size_t NUMBER_AREA,
	                           const size_t NUMBER_LINE)
{
	int size = line.vecStrongInteract.size();
	for (int i(size - 1); i >= 0;)
	{
		size_t indexOne = line.vecStrongInteract[i].indexOne;
		size_t indexTwo = line.vecStrongInteract[i].indexTwo;
		calcStrongInteraction_RIGHT(line, line.vecPoints[indexOne], line.vecPoints[indexTwo],
			size, i, -1, -1);
		if (line.vecPoints[indexOne].externalInteractInspector_RIGHT == true)
		{
			FunctionalPoint::shiftsSUM(line.vecPoints[indexOne].shiftsInertia,
				line.vecPoints[indexOne].inertia);

			line.vecPoints[indexOne].externalInteractInspector_RIGHT = false;
		}
		else {
			FunctionalPoint::sumShiftObjectCoord(line.vecPoints[indexOne].coordsObj,
				line.vecPoints[indexOne].inertia);
		}
	}
	for (int i(0); i < size;)
	{
		size_t indexOne = line.vecStrongInteract[i].indexOne;
		size_t indexTwo = line.vecStrongInteract[i].indexTwo;
	    calcStrongInteraction_LEFT(line, line.vecPoints[indexTwo], line.vecPoints[indexOne],
			size, i, 1, -1);
	
		if (line.vecPoints[indexTwo].externalInteractInspector_LEFT == true)
		{
			FunctionalPoint::shiftsSUM(line.vecPoints[indexTwo].shiftsInertia,
				line.vecPoints[indexTwo].inertia);
			line.vecPoints[indexTwo].externalInteractInspector_LEFT = false;
		}
		else
		{
			FunctionalPoint::sumShiftObjectCoord(line.vecPoints[indexTwo].coordsObj,
				line.vecPoints[indexTwo].inertia);
		}
	}
	// удаляемм отдельные точки
	checkPointsForInteraction(line);
}
bool FunctionalLine::
     inspectorCoordsd(const Point& point,
		              const Point& point_LEFT,
	                  const size_t DEVIATION)
{
	{
		int POS_X_LEFT, POS_Y_LEFT;

		if (point.coordsObj.POS_X > point_LEFT.coordsObj.POS_X)
		{
			POS_X_LEFT = abs(point.coordsObj.POS_X - point_LEFT.coordsObj.POS_X);
		}
		else
		{
			POS_X_LEFT = abs(point_LEFT.coordsObj.POS_X - point.coordsObj.POS_X);
		}
		if (point.coordsObj.POS_Y > point_LEFT.coordsObj.POS_Y)
		{
			POS_Y_LEFT = abs(point.coordsObj.POS_Y - point_LEFT.coordsObj.POS_Y);
		}
		else
		{
			POS_Y_LEFT = abs(point_LEFT.coordsObj.POS_Y - point.coordsObj.POS_Y);
		}
		return (POS_X_LEFT < DEVIATION && POS_Y_LEFT < DEVIATION);
	}
}
bool FunctionalLine::
     inspectorCoords(const Point& point, const Point& point_LEFT,
	                 const Point& point_REGHT, const size_t DEVIATION,
		             const size_t F)
{
	int POS_X_LEFT, POS_Y_RIGHT, POS_Y_LEFT, POS_X_RIGHT;
	
	if (point.coordsObj.POS_X > point_REGHT.coordsObj.POS_X)
	{
		POS_X_RIGHT = abs(point.coordsObj.POS_X - point_REGHT.coordsObj.POS_X);
	}
	else
	{
		POS_X_RIGHT = abs(point_REGHT.coordsObj.POS_X - point.coordsObj.POS_X);
	}
	if (point.coordsObj.POS_Y > point_REGHT.coordsObj.POS_Y)
	{
		POS_Y_RIGHT = abs(point.coordsObj.POS_Y - point_REGHT.coordsObj.POS_Y);
	}
	else
	{
		POS_Y_RIGHT = abs(point_REGHT.coordsObj.POS_Y - point.coordsObj.POS_Y);
	}

	if (point.coordsObj.POS_X > point_LEFT.coordsObj.POS_X)
	{
		POS_Y_LEFT = abs(point.coordsObj.POS_X - point_LEFT.coordsObj.POS_X);
	}
	else
	{
		POS_Y_LEFT = abs(point_LEFT.coordsObj.POS_X - point.coordsObj.POS_X);
	}
	if (point.coordsObj.POS_Y > point_LEFT.coordsObj.POS_Y)
	{
		POS_X_LEFT = abs(point.coordsObj.POS_Y - point_LEFT.coordsObj.POS_Y);
	}
	else
	{
		POS_X_LEFT = abs(point_LEFT.coordsObj.POS_Y - point.coordsObj.POS_Y);
	}
	
	return (POS_X_RIGHT < F  && POS_Y_RIGHT < F) ||
		(POS_X_LEFT < F && POS_Y_LEFT < F);
	
}
void FunctionalLine::
     verificationExternalInteractions(std::vector<Line>& vecShapes,
	                                  const size_t NUMBER_SPACE,
	                                  const size_t NUMBER_AREA,
	                                  const size_t NUMBER_LINE,
	                                  const size_t NUMBER_POINT)
{
	// выясняем растояние
	CoordsOBJ coordsObj_l(0, 0, 0);
	CoordsOBJ coordsObj_r(0, 0, 0);
	// пропорция для сравнивание 
	size_t deviation = 0;
	// индекс для первого элемента
	int index;
	if ( NUMBER_POINT == vecShapes[NUMBER_LINE].vecPoints.size() - 1)
	{
		coordsObj_l = vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT].coordsObj;
		coordsObj_r = vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT - 1].coordsObj;
		index = -1;
	}
	else
	{
		coordsObj_r = vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT].coordsObj;
		coordsObj_l = vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT + 1].coordsObj;
		index = +1;
	}
	Shifts shiftsObj(0, 0, 0);
	if (coordsObj_r.POS_X > coordsObj_l.POS_X)
	{
		shiftsObj.shiftPlaneX = abs(coordsObj_r.POS_X - coordsObj_l.POS_X);
	}
	else
	{
		shiftsObj.shiftPlaneX = abs(coordsObj_l.POS_X - coordsObj_r.POS_X);
	}

	if (coordsObj_r.POS_Y > coordsObj_l.POS_Y)
	{
		shiftsObj.shiftPlaneX = abs(coordsObj_r.POS_Y - coordsObj_l.POS_Y);
	}
	else
	{
		shiftsObj.shiftPlaneX = abs(coordsObj_l.POS_Y - coordsObj_r.POS_Y);
	}
	size_t F = AuxiliaryFunctionalLine::calcF(shiftsObj) ;
		const size_t SIZE = vecShapes.size();
		for (size_t i(NUMBER_LINE); i < SIZE; ++i)
		{
			 size_t SIZE_LINE = vecShapes[i].vecPoints.size();
			 size_t j(0);
			 if (i == NUMBER_LINE)
			 {
				 for (size_t j(NUMBER_POINT + 1); j < SIZE_LINE; ++j)
				 {
					 if (inspectorCoordsd(vecShapes[NUMBER_LINE].
						 vecPoints[NUMBER_POINT],
						 vecShapes[i].vecPoints[j], deviation))	
					 {
						 FunctionalPoint::mainCalcWeakForce(vecShapes[NUMBER_LINE].
							 vecPoints[NUMBER_POINT], vecShapes[i].vecPoints[j]);
						 vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT].externalInteractInspector_LEFT = true;
						 vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT].externalInteractInspector_RIGHT = true;
						 vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT].indExternInteract.NUMBER_LINE = i;
						 vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT].indExternInteract.NUMBER_POINT = j;
						 vecShapes[i].vecPoints[j].externalInteractInspector_LEFT = true;
						 vecShapes[i].vecPoints[j].externalInteractInspector_RIGHT = true;
						 vecShapes[i].vecPoints[j].indExternInteract.NUMBER_LINE = NUMBER_LINE;
						 vecShapes[i].vecPoints[j].indExternInteract.NUMBER_POINT = NUMBER_POINT;
					 }
				 }
			 }	
			 else {
				 F = NORMAL_F;
				 for (; j < SIZE_LINE; ++j)
				 {
					 if (inspectorCoordsd(vecShapes[NUMBER_LINE].
						 vecPoints[NUMBER_POINT],
						 vecShapes[i].vecPoints[j], F))
					 {
						 FunctionalPoint::mainCalcWeakForce(vecShapes[NUMBER_LINE].
							 vecPoints[NUMBER_POINT], vecShapes[i].vecPoints[j]);
						 vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT].externalInteractInspector_LEFT = true;
						 vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT].externalInteractInspector_RIGHT = true;
						 vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT].indExternInteract.NUMBER_LINE = i;
						 vecShapes[NUMBER_LINE].vecPoints[NUMBER_POINT].indExternInteract.NUMBER_POINT = j;
						 vecShapes[i].vecPoints[j].externalInteractInspector_LEFT = true;
						 vecShapes[i].vecPoints[j].externalInteractInspector_RIGHT = true;
						 vecShapes[i].vecPoints[j].indExternInteract.NUMBER_LINE = NUMBER_LINE;
						 vecShapes[i].vecPoints[j].indExternInteract.NUMBER_POINT = NUMBER_POINT;
					 }
				 }
				}	
		}
}
void FunctionalLine::
     mainCalcWeakInteraction(std::vector<Line>& vecLine, Line& line,
	                         const size_t NUMBER_SPACE,
	                         const size_t NUMBER_AREA,
	                         const size_t NUMBER_LINE)
{
	const int SIZE = line.vecPoints.size();
		for (size_t i(0); i < SIZE; ++i)
		{
			if (line.vecPoints[i].coordsObj.POS_Y > LAND_MARK)
			{
				if (line.vecPoints[i].externalInteractInspector_LEFT == false &&
					line.vecPoints[i].externalInteractInspector_RIGHT == false)
				{
					verificationExternalInteractions(vecLine, NUMBER_SPACE,
						                             NUMBER_AREA, NUMBER_LINE, i);
				}
				FunctionalPoint::sumShiftObjectCoord(line.vecPoints[i].coordsObj,
					line.vecPoints[i].shiftsInertia);
			}
		}
}
