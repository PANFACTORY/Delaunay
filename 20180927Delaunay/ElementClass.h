//*****************************************************************************
//Title		:Delaunay ElementClass
//Purpose	:Element for Delaunay Triangulation Method
//Author	:Tanabe Yuta
//Date		:2018/09/20
//Copyright	:(C) 2018 Tanabe Yuta
//*****************************************************************************
#pragma once
#include <vector>
#include "NodeClass.h"

using namespace std;

class ElementClass{
public:
	ElementClass();
	~ElementClass();

	int node[3];											//���_�̐ߓ_�ԍ�
	int neighbor[3];										//�אڗv�f�ԍ�
	bool side[3];											//true:�ӂ����E		false:�ӂ��񋫊E

	void setnode(int _node0, int _node1, int _node2);		//���_�̎�荞��
	void setneighbor(int _neighbor0, int _neighbor1, int _neighbor2);		//�אڗv�f�ԍ��̎�荞��
	void copy(ElementClass _originalelement);				//�I�u�W�F�N�g���R�s�[����

	int inouton(int _nodenum, vector<NodeClass> _node);		//�v�f�Ɠ_�̈ʒu�֌W��Ԃ�
	int oppositenode(int _elementname);						//�w�肳�ꂽ�v�f�Ƃ̈ʒu�֌W��Ԃ�
};
