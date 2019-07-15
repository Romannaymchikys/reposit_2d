#pragma once
#include "MyDefine.h"
#include "MyStructs.h"
#include "FunctionalPoint.h"
#include "FunctionalLine.h"
#include "CreatLine.h"
#include "Line.h"
#include "Point.h"
#include <GL/glu.h> 
// ��������� ������
struct {
	const size_t height = 4;
	const size_t width = 5;
}aspectRatio;
struct MainFunctional
{
public:
	MainFunctional(std::vector<Line>& newVecLine) :
		vecLine(newVecLine){};
	void displayDrawing(Line line)
	{
		float POS_X_1, POS_Y_1;
		float POS_X_2, POS_Y_2;
		float F;
		if (!line.vecStrongInteract.empty() && !line.vecPoints.empty())
		{
			const size_t SIZE = line.vecStrongInteract.size() - 1;
			for (size_t i(0); i <= SIZE; ++i)
			{
				POS_X_1 = (float)(line.vecPoints[line.vecStrongInteract[i].indexOne]
					.coordsObj.POS_X) / PROPORTION;	
				POS_Y_1 = (float)(line.vecPoints[line.vecStrongInteract[i].indexOne]
					.coordsObj.POS_Y) / PROPORTION;
				POS_X_2 = (float)(line.vecPoints[line.vecStrongInteract[i].indexTwo]
					.coordsObj.POS_X) / PROPORTION;
				POS_Y_2 = (float)(line.vecPoints[line.vecStrongInteract[i].indexTwo]
					.coordsObj.POS_Y) / PROPORTION;
				glVertex2f(POS_X_1 / WIDHT * HIEGHT, POS_Y_1);
				glVertex2f(POS_X_2 / WIDHT * HIEGHT, POS_Y_2);
			}
		}
	}
	void functionalDisplay()
	{
		
	
		const size_t SIZE = vecLine.size();
	
		
			for (int i(0); i < SIZE; ++i)
			{
				FunctionalLine::mainCalcStrongInteraction(vecLine, vecLine[i], 0, 0, i);
				
				
			}
			for (int i(0); i < SIZE; ++i)
			{
				
				FunctionalLine::mainCalcWeakInteraction(vecLine, vecLine[i], 0, 0, i);

			}
	
	/*for (int i(SIZE - 1); i >= 0; --i)
		{
			FunctionalLine::mainCalcStrongInteractionRIGHT(vecShapes, vecShapes[i], 0, 0, i);
		}*/
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (size_t i(0); i < SIZE; ++i)
		{
			//������ ����� (������� �����������)
			glColor3f(vecLine[i].figureColor.color_1, // ���� ����� �����, � ������ ����� - �������  
				      vecLine[i].figureColor.color_2,
				      vecLine[i].figureColor.color_3);
			glBegin(GL_LINES); // �������� �������� � ���������, ��� ��� �����
			displayDrawing(vecLine[i]);
		}
		glEnd();
		glFlush();
	}
	
	std::vector<Line> vecLine;
};

void calcWeakInteraction( Line& line, const Force& FORCE)
{
	size_t SIZE = line.vecPoints.size();
	for (size_t i(0); i < SIZE; ++i)
	{
		const int F = FORCE.F - line.vecPoints[i].weight;
		if (F > 0)
		{
			line.vecPoints[i].shiftsInertia = FunctionalPoint::calcShiftForce(FORCE.angle, F);
		}
		line.vecPoints[i].inertia = FunctionalPoint::calcShiftForce(FORCE.angle, FORCE.F);
	}

	
}

MainFunctional creatAndInitLines()
{
	// ������ ������� ���
	//___________________________________________________________________
	size_t F_Gravit = 3400;
	AngleDeviat angleGravit(270, 0);
	Shifts shiftsGravit(0, 0, 0);
	shiftsGravit = FunctionalPoint::calcShiftForce(angleGravit, F_Gravit);
	Force forceGravit(shiftsGravit, angleGravit, F_Gravit);
	//___________________________________________________________________
	//___________________________________________________________________
	size_t F_Speed_1 = 300;
	AngleDeviat angleSpeed_1(20, 0);
	Shifts shiftsSpeed_1(0, 0, 0);
	shiftsSpeed_1 = FunctionalPoint::calcShiftForce(angleSpeed_1, F_Speed_1);
	Force forceSpeed_1(shiftsSpeed_1, angleSpeed_1, F_Speed_1);
	//___________________________________________________________________
	//___________________________________________________________________
	size_t F_Speed_2 =800;
	AngleDeviat angleSpeed_2(10, 0);
	Shifts shiftsSpeed_2(0, 0, 0);
	shiftsSpeed_2 = FunctionalPoint::calcShiftForce(angleSpeed_2, F_Speed_2);
	Force forceSpeed_2(shiftsSpeed_2, angleSpeed_2, F_Speed_2);
	//___________________________________________________________________
	//___________________________________________________________________
	size_t F_Speed_3 = 260;
	AngleDeviat angleSpeed_3(200, 0);
	Shifts shiftsSpeed_3(0, 0, 0);
	shiftsSpeed_3 = FunctionalPoint::calcShiftForce(angleSpeed_3, F_Speed_3);
	Force forceSpeed_3(shiftsSpeed_3, angleSpeed_3, F_Speed_3);
	//___________________________________________________________________
	//___________________________________________________________________
	size_t F_Null = 0;
	AngleDeviat angleNull(0, 0);
	Shifts shiftsNull(0, 0, 0);
	shiftsNull = FunctionalPoint::calcShiftForce(angleNull, F_Null);
	Force forceNull(shiftsNull, angleNull, F_Null);
	//___________________________________________________________________

	std::vector<Line> vecShapes;
	// ���������� ��������� ����� �����
	CoordsOBJ coordOBJ_1(-50000, 0, 0);
	// ���� ��������� ������� ����� ������������ ������������ ����� X
	AngleDeviat angleDeviat_1(20, 0);
	// ������ �������� �������������� ��� �����
	StrongInteract strongInteract_1(500,  // ����� ������������ ������������
		10000, // ������������ ���������
		1.7);// ���������� ���������        
			 // ������� �����
	FigureColor figureColor_1(1.0, 0.0, 0.0);
	Line Line_1(strongInteract_1,// ������� ��������������
		coordOBJ_1, // ��������� ����������
		figureColor_1, // ���� ������
		angleDeviat_1, // ��������� ���� ������������ �����
		100, // ���������� ��������������
		100,// ����� ������ �����
		1); // � ����� ������ ����������� �����
			// ��������� ���� 
	calcWeakInteraction(Line_1, forceSpeed_1);
	vecShapes.push_back(Line_1);
	//______________________________________________________________________________
	CoordsOBJ coordOBJ_3(-50000, -10000, 0);
	// ���� ��������� ������� ����� ������������ ������������ ����� X
	AngleDeviat angleDeviat_3(0, 0);
	// ������ �������� �������������� ��� �����
	StrongInteract strongInteract_3(500,  // ����� ������������ ������������
		10000, // ������������ ���������
		1.7);// ���������� ���������   
			 // ������� �����
	FigureColor figureColor_3(0.0, 0.0, 1.0);
	Line Line_3(strongInteract_3,// ������� ��������������
		coordOBJ_3, // ��������� ����������
		figureColor_3, // // ���� ������
		angleDeviat_3, // ��������� ���� ������������ �����
		101, // ���������� ��������������
		100,// ����� ������ �����
		1); // � ����� ������ ����������� �����
	calcWeakInteraction(Line_3, forceSpeed_2);
	//calcWeakInteraction(Line_3, forceNull);
	vecShapes.push_back(Line_3);
	//______________________________________________________________________________
	CoordsOBJ coordOBJ_2(8000, -46000, 0);
	// ���� ��������� ������� ����� ������������ ������������ ����� X
	AngleDeviat angleDeviat_2(90, 0);
	// ������ �������� �������������� ��� �����
	StrongInteract strongInteract_2(500,  // ����� ������������ ������������
		10000, // ������������ ���������
		2.4);// ���������� ���������   
			 // ������� �����
	FigureColor figureColor_2(0.0, 1.0, 0.0);
	Line Line_2(strongInteract_2,// ������� ��������������
		coordOBJ_2, // ��������� ����������
		figureColor_2, // // ���� ������
		angleDeviat_2, // ��������� ���� ������������ �����
		201, // ���������� ��������������
		600,// ����� ������ �����
		0); // � ����� ������ ����������� �����
	//calcWeakInteraction(Line_2, forceSpeed_2);
	calcWeakInteraction(Line_2, forceNull);
	vecShapes.push_back(Line_2);
	
	//______________________________________________________________________________
	CoordsOBJ coordOBJ_4(30000, 40000, 0);
	// ���� ��������� ������� ����� ������������ ������������ ����� X
	AngleDeviat angleDeviat_4(0, 0);
	// ������ �������� �������������� ��� �����
	StrongInteract strongInteract_4(500,  // ����� ������������ ������������
		10000, // ������������ ���������
		1.7);// ���������� ���������   
			 // ������� �����
	FigureColor figureColor_4(0.0, 1.0, 1.0);
	Line Line_4(strongInteract_4,// ������� ��������������
		coordOBJ_4, // ��������� ����������
		figureColor_4, // // ���� ������
		angleDeviat_4, // ��������� ���� ������������ �����
		100, // ���������� ��������������
		100,// ����� ������ �����
		4); // � ����� ������ ����������� �����
	calcWeakInteraction(Line_4, forceSpeed_3);
	//calcWeakInteraction(Line_2, forceNull);
	vecShapes.push_back(Line_4);
	MainFunctional mainFunc(vecShapes);
	return mainFunc;
}