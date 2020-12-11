#ifndef _LISTDG_H_
#define _LISTDG_H_

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX 100

//�ڽӱ�
class ListDG
{
private: //�ڲ���
	class ENode
	{
	public:
		int ivex; //�ñ���ָ��Ķ���λ��
		ENode *nextEdge; //ָ����һ������ָ��
	};

	//�ڽӱ��б�Ķ���
	class VNode
	{
	public:
		string data; //������Ϣ
		ENode *firstEdge; //ָ���һ�������õ�Ļ�
	};

private:
	int mVexNum; //ͼ�Ķ������Ŀ
	int mEdgeNum; //ͼ�ıߵ���Ŀ
	VNode mVexs[MAX];

public:
	//�����ڽӱ��Ӧ��ͼ
	ListDG(string vexs[], int vlen, string edges[][2], int elen);
	~ListDG();

	//���������������ͼ
	void DFS(int idx);
	//�����������(���������Ĳ�α���)
	void BFS();
	//��ӡ�ڽ�ͼ
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