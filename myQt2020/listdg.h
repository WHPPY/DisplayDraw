#ifndef _LISTDG_H_
#define _LISTDG_H_

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX 100

//邻接表
class ListDG
{
private: //内部类
	class ENode
	{
	public:
		int ivex; //该边所指向的顶点位置
		ENode *nextEdge; //指向下一条弧的指针
	};

	//邻接表中表的顶点
	class VNode
	{
	public:
		string data; //顶点信息
		ENode *firstEdge; //指向第一跳依附该点的弧
	};

private:
	int mVexNum; //图的顶点的数目
	int mEdgeNum; //图的边的数目
	VNode mVexs[MAX];

public:
	//创建邻接表对应的图
	ListDG(string vexs[], int vlen, string edges[][2], int elen);
	~ListDG();

	//深度优先搜索遍历图
	void DFS(int idx);
	//广度优先搜索(类似于树的层次遍历)
	void BFS();
	//打印邻接图
	void print();

	std::vector<string> getDfsRet() const { return DfsRet; }

	int getPosition(string ch);

	bool hasEdge(int v,int w);

private:
	void DFS(int i, int *visited);
	void linkLast(ENode *list, ENode *node);

	std::vector<string> DfsRet;
};

#endif