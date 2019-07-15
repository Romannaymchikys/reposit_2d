#pragma once
#include "MyDefine.h"
#include <iostream>
#include <math.h>
#include "MyStructs.h"

class Point
{
public:
	Point(const CoordsOBJ& NEW_COORDS_OBJ,
		  const IndexSearchExternInteract& NEW_IND_EXTERN_INTERACT,
		  const Shifts& NEW_SHIFTS_INERTIA,
		  const Shifts& NEW_INERTIA,
		  const size_t newSizeStrongIteract, 
		  const size_t newWeight):
		coordsObj(NEW_COORDS_OBJ),
		indExternInteract(NEW_IND_EXTERN_INTERACT),
		shiftsInertia(NEW_SHIFTS_INERTIA),
		inertia(NEW_INERTIA),
		sizeStrongIteract(newSizeStrongIteract),
		weight(newWeight),
		externalInteractInspector_LEFT(false),
		externalInteractInspector_RIGHT(false){};

	CoordsOBJ coordsObj;
	//�����
	size_t weight;
	///������� ��������������
	// �������� ���� �� ��������������
	bool externalInteractInspector_LEFT;
	bool externalInteractInspector_RIGHT;
	// ������ ����������� ���������� ������
	size_t sizeStrongIteract;
	// ���������� ��� ������ ������� ��������������
	IndexSearchExternInteract indExternInteract;
	Shifts shiftsInertia;
	// ���� ����������� �� �����
	Shifts inertia;
};