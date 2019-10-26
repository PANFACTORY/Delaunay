//*****************************************************************************
//Title		:Delaunay BoundaryClass
//Purpose	:Boundary for Delaunay Triangulation Method
//Author	:Tanabe Yuta
//Date		:2018/09/27�`
//Copyright	:(C) 2018 Tanabe Yuta
//*****************************************************************************

#include <vector>

using namespace std;

#pragma once
class BoundaryClass
{
public:
	BoundaryClass();
	~BoundaryClass();

	vector<int> nodelist;		//�ߓ_���X�g
	bool type;					//���E�̎�ށitrue:�O���@false:�����j

	int order(int _nodenum);	//�ߓ_�̋��E�ɂ�����ԍ���Ԃ�
};

