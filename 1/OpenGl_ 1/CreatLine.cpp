#include "stdafx.h"
#include "CreatLine.h"
void CreatLine::
calcWeakInteraction(Shifts& foresShifts,
	                const AngleDeviat ANGLE_DEVIAT,
	                const size_t F)
{
	if (F > 0) {
		foresShifts = FunctionalPoint::calcShiftForce(ANGLE_DEVIAT, F);
	}
}
void CreatLine::
     initWeightAndPointVecPoints(std::vector<Point>& vecPoints, 
		                         const AngleDeviat ANGLE_DEVIAT,
	                             const size_t FORCE,
	                             size_t initialWeight)
{
	size_t SIZE = vecPoints.size();
	for (size_t i(0); i < SIZE; ++i)
	{
		const int F = FORCE - vecPoints[i].weight;
		if (F > 0)
		{
			vecPoints[i].shiftsInertia = FunctionalPoint::calcShiftForce(ANGLE_DEVIAT, F);
		}
		vecPoints[i].inertia = FunctionalPoint::calcShiftForce(ANGLE_DEVIAT, FORCE);
	}
}
Point CreatLine::creatPoint(const CoordsOBJ& COORDS_OBJ, 
	                        const size_t INITIAL_WEIGHT,
	                        const size_t NUMBER_SPACE,
	                        const size_t NUMBER_AREA,
	                        const size_t NUMBER_LINE,
	                        const size_t NUMBER_POINT,
	                        const size_t LENGHT)
{
	IndexSearchExternInteract indexSearchExternInteract(NUMBER_SPACE, NUMBER_AREA,
		                                                 NUMBER_LINE, NUMBER_POINT);
	size_t F_Null = 0;
	AngleDeviat angleNull(0, 0);
	Shifts shiftsNull(0, 0, 0);
	size_t sizeStrongIteract;
	// 0 - нет связей
	// 1 - слево связь
	// 2 - справо связь
	// 3 - и слево и справо связь
	if (NUMBER_POINT == 0);
	{
		sizeStrongIteract = 2;
	}
	if (NUMBER_POINT > 0 && NUMBER_POINT < LENGHT - 1)
	{
		sizeStrongIteract = 3;
	}
	if ( NUMBER_POINT == LENGHT - 1)
	{
		sizeStrongIteract = 1;
	}
	Point point(COORDS_OBJ, indexSearchExternInteract, shiftsNull,
		        shiftsNull, sizeStrongIteract, INITIAL_WEIGHT);
	return point;
}
std::vector<Point> CreatLine::
                     creatVecPoints(CoordsOBJ& coordObj,
						            const AngleDeviat ANGLE_DEVIAT,
						            const size_t NORMAL_DISTANCE,
						            const size_t LENGHT,
						            const size_t INITIAL_WEIGHT,
						            const size_t NUMBER_SPACE,
						            const size_t NUMBER_AREA,
						            const size_t NUMBER_LINE)
{
	// создание вектора точект
	std::vector<Point> vecPoints;
	for (size_t i(0); i < LENGHT; ++i)
	{
		vecPoints.push_back(creatPoint(coordObj, INITIAL_WEIGHT, NUMBER_SPACE,
			                                    NUMBER_AREA, NUMBER_LINE, i, LENGHT));
		FunctionalPoint::sumShiftObjectCoord(coordObj,
		FunctionalPoint::calcShiftForce(ANGLE_DEVIAT, NORMAL_DISTANCE));
		
	}
	return vecPoints;
}
// создание последовательности сил взаимодействие
std::vector<Node> CreatLine::
                  creatVecStrongInteract(const std::vector<Point> vecPoints)
{
	Node node;
	std::vector<Node> newVecStrongInteract;
	const size_t SIZE = vecPoints.size() - 2;
	for (size_t i(0); i < SIZE; ++i )
	{
		node.indexOne = i;
		node.indexTwo = i + 1;
		newVecStrongInteract.push_back(node);
	}
	return newVecStrongInteract;
}

