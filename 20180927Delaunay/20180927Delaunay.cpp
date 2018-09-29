//*****************************************************************************
//Title		:Delaunay
//Purpose	:Create mesh with Delaunay Triangulation Method
//Author	:Tanabe Yuta
//Date		:2018/09/27
//Copyright	:(C) 2018 Tanabe YutaS
//*****************************************************************************

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include "ElementClass.h"
#include "NodeClass.h"
#include "BoundaryClass.h"
#include "DelaunayClass.h"

using namespace std;

//*****************************************************************************
//要素の出力
//*****************************************************************************
void showelements(vector<ElementClass> _element, vector<NodeClass> _node) {
	FILE *fp;
	fp = _popen("gnuplot -persist", "w");							// パイプを開き、gnuplotの立ち上げ
	fprintf(fp, "set title 'Triangle Elements'\n");					//グラフタイトル
	fprintf(fp, "set multiplot\n");									// マルチプロットモード
	fprintf(fp, "set xrange [%lf:%lf]\n", -1.0, 6.0);	     		// 範囲の指定
	fprintf(fp, "set yrange [%lf:%lf]\n", -1.0, 2.0);
	fprintf(fp, "set xlabel \"x\"\n");							    // ラベル表示
	fprintf(fp, "set ylabel \"y\"\n");
	fprintf(fp, "set style arrow 1 nohead linecolor rgb 'black'\n");
	fprintf(fp, "set size ratio - 1\n");
	// 点のプロット
	for (int i = 0; i < _element.size(); i++) {
		fprintf(fp, "set arrow from %lf,%lf to %lf,%lf arrowstyle 1\n", _node[_element[i].node[0]].x, _node[_element[i].node[0]].y, _node[_element[i].node[1]].x, _node[_element[i].node[1]].y);
		fprintf(fp, "set arrow from %lf,%lf to %lf,%lf arrowstyle 1\n", _node[_element[i].node[1]].x, _node[_element[i].node[1]].y, _node[_element[i].node[2]].x, _node[_element[i].node[2]].y);
		fprintf(fp, "set arrow from %lf,%lf to %lf,%lf arrowstyle 1\n", _node[_element[i].node[2]].x, _node[_element[i].node[2]].y, _node[_element[i].node[0]].x, _node[_element[i].node[0]].y);
	}

	fprintf(fp, "plot '-' with points pointtype 1\n");
	fprintf(fp, "e\n");

	fprintf(fp, "set nomultiplot\n"); // マルチプロットモード終了
	fprintf(fp, "exit\n"); // gnuplotの終了
	fflush(fp);
}


//*****************************************************************************
//境界の取り込み
//*****************************************************************************
void getboundary(vector<BoundaryClass> &_boundary, string _fname, bool _type) {
	BoundaryClass tmpboundary;
	string tmp;

	ifstream fin(_fname);
	if (!fin) {
		cout << "File Open Error\n";
	}

	while (getline(fin, tmp)) {
		tmpboundary.nodelist.push_back(stoi(tmp));
	}
	fin.close();
	tmpboundary.type = _type;
	_boundary.push_back(tmpboundary);
}


//*****************************************************************************
//メイン処理
//*****************************************************************************
int main() {
	vector<NodeClass> node;							//節点
	vector<ElementClass> element;					//要素
	vector<BoundaryClass> boundary;					//境界
	DelaunayClass mesher;							//DelaunayTriangulationによるメッシャー

	//----------節点座標の取り込み----------
	string tmp;

	ifstream fin0("nodes.dat");
	if (!fin0) {
		cout << "File Open Error\n";
		return 1;
	}
	
	while (getline(fin0, tmp)) {
		istringstream ssi(tmp);
		string tmpx, tmpy;
		NodeClass tmpnode;

		ssi >> tmpx >> tmpy;
		tmpnode.x = stod(tmpx);
		tmpnode.y = stod(tmpy);
		node.push_back(tmpnode);
	}
	fin0.close();

	//----------外部境界の取り込み----------
	getboundary(boundary, "externalboundary.dat", true);

	//----------内部境界0の取り込み----------
	getboundary(boundary, "internalboundary0.dat", false);
	
	//----------内部境界1の取り込み----------
	getboundary(boundary, "internalboundary1.dat", false);

	//----------SuperTriangleの生成----------
	mesher.getsupertriangle(node, element);
	
	//----------外部境界の設置----------
	mesher.getelement(node, element, boundary[0]);

	//----------内部境界0の設置----------
	mesher.getelement(node, element, boundary[1]);

	//----------内部境界1の設置----------
	mesher.getelement(node, element, boundary[2]);

	//----------境界外要素の削除----------
	mesher.deleteelement(node, element, boundary[0]);
	mesher.deleteelement(node, element, boundary[1]);
	mesher.deleteelement(node, element, boundary[2]);

	//----------SuperTriangleの除去----------
	mesher.deletesupertriangle(node, element);

	//----------結果の表示----------
	showelements(element, node);
}