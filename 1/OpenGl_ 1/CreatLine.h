#pragma once
#include <vector>
#include "MyStructs.h"
#include "FunctionalPoint.h"
#include "Point.h"
#include "AuxiliaryFunctionalLine.h"
class CreatLine
{
public:
	static void calcWeakInteraction(Shifts& foresShifts,
		                            const AngleDeviat ANGLE_DEVIAT, const size_t F);
	static void initWeightAndPointVecPoints(std::vector<Point>& vecPoints,
		                                   const AngleDeviat ANGLE_DEVIAT,
		                                   const size_t FORCE, 
		                                  size_t initialWeight);
	static Point creatPoint(const CoordsOBJ& COORDS_OBJ, const size_t INITIAL_WEIGHT,
		                                               const size_t NUMBER_SPACE,
		                                               const size_t NUMBER_AREA,
		                                               const size_t NUMBER_LINE,
	                                                   const size_t NUMBER_POINT,
		                                               const size_t LENGHT);
	static std::vector<Point> creatVecPoints( CoordsOBJ& coordObj, 
		                                      const AngleDeviat ANGLE_DEVIAT,
		                                      const size_t NORMAL_DISTANCE,
		                                      const size_t LENGHT,
		                                      const size_t INITIAL_WEIGHT,
		                                      const size_t NUMBER_SPACE,
		                                      const size_t NUMBER_AREA,
		                                      const size_t NUMBER_LINE);
	static std::vector<Node> creatVecStrongInteract(const std::vector<Point> vecPoints);
};

