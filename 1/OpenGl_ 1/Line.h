#pragma once
#include "MyStructs.h"
#include "Point.h"
#include "FunctionalPoint.h"
#include "FunctionalLine.h"
#include "CreatLine.h"
class Line
{
public:
	Line(const StrongInteract& NEW_STRONG_INTERACT,
		 CoordsOBJ& coordObj,
		 const FigureColor& NEW_FIGURE_COLOR,
		 const AngleDeviat& ANGLE_DEVIAT,
		 const size_t LENGHT,
		 const size_t NEW_INITIAL_WEIGHT,
		 const size_t NUMBER_SPACE) :
			strongInteraction(NEW_STRONG_INTERACT),
				figureColor(NEW_FIGURE_COLOR)
		{
		// инициализация двух векторов
		vecPoints = CreatLine::creatVecPoints(coordObj, ANGLE_DEVIAT,
			strongInteraction.normal, LENGHT, NEW_INITIAL_WEIGHT, NUMBER_SPACE, 0, 0);
		vecStrongInteract = CreatLine::creatVecStrongInteract(vecPoints);
		};
		// массив точек
		std::vector<Point> vecPoints;
		// последовательность элементоми каторой евляются
		//  пара индексов елементов вектора линии 
		std::vector<Node> vecStrongInteract;
		// силы взаимодействия strongInteraction.F_min 
		// является плотностью вещества
		StrongInteract strongInteraction;
		FigureColor figureColor;
};

