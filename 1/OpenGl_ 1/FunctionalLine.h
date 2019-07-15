#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "MyStructs.h"
#include "FunctionalPoint.h"
#include "AuxiliaryFunctionalLine.h"
#include "CreatLine.h"
#include "MyDefine.h"
#include "algorithm"
#include "Line.h"
class FunctionalLine
{
public:
	//ВЗАИМОДЕЙСТВИЕ
	//________________________________________________________________________________________________
	// сильное взаимодействие
	static size_t
		calcStrongInteraction_LEFT(Line& line, Point& pointOne,
			Point& pointTwo,
			int& size, int& i, const int INDEX,
			const int INDEX_SIZE);
	static Shifts
		calcStrongInteraction_RIGHT(Line& line, Point& pointOne,
			Point& pointTwo,
			int& size, int& i, const int INDEX,
			const int INDEX_SIZE);
	static void mainCalcStrongInteraction(std::vector<Line>& vecLine, Line& line,
		                                  const size_t NUMBER_SPACE,
		                                  const size_t NUMBER_AREA,
		                                  const size_t NUMBER_LINE);
	static void
		verificationExternalInteractions(std::vector<Line>& vecShapes,
			                             const size_t NUMBER_SPACE,
			                             const size_t NUMBER_AREA,
			                             const size_t NUMBER_LINE,
			                             const size_t NUMBER_POINT);
	//________________________________________________________________________________________________
	// слабое взаимодействие
	static void mainCalcWeakInteraction(std::vector<Line>& vecShapes, Line& line,
		                                const size_t NUMBER_SPACE,
		                                const size_t NUMBER_AREA,
		                                const size_t NUMBER_LINE);
	//________________________________________________________________________________________________
	// зануление "одиноких точек"
	static void  checkPointsForInteraction(Line& line);
	// проверка точек на взаимодействие
	static bool inspectorCoords(const Point& point, const Point& point_LEFT, const Point& point_REGHT,
		const size_t DEVIATION, const size_t F);
	static bool inspectorCoordsd(const Point& point, const Point& point_LEFT,
		const size_t DEVIATION);

	
};

