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
		// ������������� ���� ��������
		vecPoints = CreatLine::creatVecPoints(coordObj, ANGLE_DEVIAT,
			strongInteraction.normal, LENGHT, NEW_INITIAL_WEIGHT, NUMBER_SPACE, 0, 0);
		vecStrongInteract = CreatLine::creatVecStrongInteract(vecPoints);
		};
		// ������ �����
		std::vector<Point> vecPoints;
		// ������������������ ���������� ������� ��������
		//  ���� �������� ��������� ������� ����� 
		std::vector<Node> vecStrongInteract;
		// ���� �������������� strongInteraction.F_min 
		// �������� ���������� ��������
		StrongInteract strongInteraction;
		FigureColor figureColor;
};

