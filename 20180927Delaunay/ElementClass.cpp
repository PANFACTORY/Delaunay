//*****************************************************************************
//Title		:Delaunay ElementClass
//Purpose	:Element for Delaunay Triangulation Method
//Author	:Tanabe Yuta
//Date		:2018/09/20
//Copyright	:(C) 2018 Tanabe Yuta
//*****************************************************************************
#include "pch.h"
#include "ElementClass.h"
#include <float.h>


ElementClass::ElementClass(){
	side[0] = false;				//�n�ߓ_�͑S�ċ��E�ł͂Ȃ����̂Ƃ���
	side[1] = false;
	side[2] = false;

	neighbor[0] = -1;				//�אڗv�f�ԍ��͎n�߂͖���
	neighbor[1] = -1;
	neighbor[2] = -1;
}


ElementClass::~ElementClass(){}


//*****************************************************************************
//���_����荞��
//*****************************************************************************
void ElementClass::setnode(int _node0, int _node1, int _node2) {
	node[0] = _node0;
	node[1] = _node1;
	node[2] = _node2;
}


//*****************************************************************************
//�אڗv�f�ԍ�����荞��
//*****************************************************************************
void ElementClass::setneighbor(int _neighbor0, int _neighbor1, int _neighbor2) {
	neighbor[0] = _neighbor0;
	neighbor[1] = _neighbor1;
	neighbor[2] = _neighbor2;
}


//*****************************************************************************
//�����̃I�u�W�F�N�g���R�s�[����
//*****************************************************************************
void ElementClass::copy(ElementClass _originalelement) {
	for (int i = 0; i < 3; i++) {
		node[i] = _originalelement.node[i];
		neighbor[i] = _originalelement.neighbor[i];
		side[i] = _originalelement.side[i];
	}
}


//*****************************************************************************
//�O�p�`�Ɛߓ_�̈ʒu�֌W�𔻒�
//	return -(i+1)	�Fi�Ԗڂ̕ӂ̊O��
//	return i+1		�Fi�Ԗڂ̕ӏ�
//	return 0		�F�O�p�`����
//*****************************************************************************

//**************************�v�C��*********************************************

int ElementClass::inouton(int _nodenum, vector<NodeClass> _node) {
	for (int i = 0; i < 3; i++) {
		double vecpro0 = _node[node[i % 3]].vecpro(_node[node[(i + 1) % 3]], _node[_nodenum]);
		double vecpro1 = _node[node[(i + 2) % 3]].vecpro(_node[node[i % 3]], _node[_nodenum]);
		
		if (fabs(vecpro0) <= DBL_EPSILON
			&& (_node[node[(i + 1) % 3]].x - _node[node[i % 3]].x)*(_node[_nodenum].x - _node[node[i % 3]].x) > 0.0
			&& fabs(_node[_nodenum].x - _node[node[i % 3]].x) < fabs(_node[node[(i + 1) % 3]].x - _node[node[i % 3]].x)) {	//�ӏ�ɂ������Ƃ�
			return (i + 2) % 3 + 1;
		}

		else if (vecpro0 < 0.0 && vecpro1 > 0.0) {			//�ӂ̊O���ɂ������Ƃ�
			return -((i + 2) % 3 + 1);
		}
	}
	return 0;												//�O�p�`�����ɂ������Ƃ�
}


//*****************************************************************************
//�w�肳�ꂽ�v�f�Ƃ̈ʒu�֌W��Ԃ�
//*****************************************************************************
int ElementClass::oppositenode(int _elementname) {
	for (int i = 0; i < 3; i++) {
		if (neighbor[i] == _elementname) {
			return i;
		}
	}
	return -1;
}