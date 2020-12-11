#include "listdg.h"

/*
* �����ڽӱ��Ӧ��ͼ(�����ṩ�����ݣ�
*/
ListDG::ListDG(string vexs[], int vlen, string edges[][2], int elen)
{
	string c1, c2;
	int i, p1, p2;
	ENode *node1, *node2;

	//��ʼ��"������"��"����"
	mVexNum = vlen;
	mEdgeNum = elen;
	//��ʼ��"�ڽӱ�"�Ķ���
	for (i = 0; i < mVexNum; i++)
	{
		mVexs[i].data = vexs[i];
		mVexs[i].firstEdge = NULL;
	}

	//��ʼ��"�ڽӱ�"�ı�
	for (i = 0; i < mEdgeNum; i++)
	{
		//��ȡ�ߵ���ʼ����ͽ�������
		c1 = edges[i][0];
		c2 = edges[i][1];

		p1 = getPosition(c1);
		p2 = getPosition(c2);
		//��ʼ��node1
		node1 = new ENode();
		node1->ivex = p2;
		//��node1���ӵ�"p1���������ĩβ"
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node1;
		else
			linkLast(mVexs[p1].firstEdge, node1);
	}
}

/*
* ��������
*/
ListDG::~ListDG()
{
}

/*
* ��node�ڵ����ӵ�list���
*/
void ListDG::linkLast(ENode *list, ENode *node)
{
	ENode *p = list;

	while (p->nextEdge)
		p = p->nextEdge;
	p->nextEdge = node;
}

/*
* ����ch��λ��
*/
int ListDG::getPosition(string ch)
{
	int i;
	for (i = 0; i < mVexNum; i++){
		if (mVexs[i].data == ch)
			return i;
	}
	return -1;
}

/*
* ��ӡ�ڽӱ�ͼ
*/
void ListDG::print()
{
	int i, j;
	ENode *node;

	cout << "List Graph:" << endl;
	for (i = 0; i < mVexNum; i++)
	{
		cout << i << "(" << mVexs[i].data << "):";
		node = mVexs[i].firstEdge;
		while (node != NULL)
		{
			cout << node->ivex << "(" << mVexs[node->ivex].data << ")";
			node = node->nextEdge;
		}
		cout << endl;
	}
}

void ListDG::DFS(int i, int *visited)
{
	ENode *node;

	visited[i] = 1;
	cout << mVexs[i].data << " ";
	DfsRet.push_back(mVexs[i].data);
	node = mVexs[i].firstEdge;
	while (node != NULL)
	{
		if (!visited[node->ivex])
			DFS(node->ivex, visited);
		node = node->nextEdge;
	}
}

void ListDG::DFS(int idx)
{
	int i;
	int visited[MAX]; //������ʱ��

	//��ʼ�����ж��㶼û�б�����
	for (i = 0; i < mVexNum; i++)
		visited[i] = 0;

	cout << "DFS:";

	for (i = idx; i < mVexNum; i++)
	{
		if (!visited[i] && mVexs[i].firstEdge != NULL){
			if (hasEdge(i, i + 1)){
				visited[i + 1] = false;
			}
			else{
				visited[i + 1] = true;
			}
			DFS(i, visited);
		}
		else{
			break;
		}

	}
	cout << endl;

}

bool ListDG::hasEdge(int v, int w)
{
	ENode *temp_node = mVexs[v].firstEdge;
	while (temp_node != NULL)
	{
		cout << temp_node->ivex << "(" << mVexs[temp_node->ivex].data << ")";
		if (mVexs[temp_node->ivex].data == mVexs[w].data)
		{
			return true;
		}
		temp_node = temp_node->nextEdge;
	}
	return false;
}

void ListDG::BFS()
{
	int head = 0;
	int rear = 0;
	int queue[MAX];
	int visited[MAX];
	int i, j, k;
	ENode *node;

	for (i = 0; i < mVexNum; i++)
	{
		visited[i] = 0;
	}

	cout << "BFS:";
	for (i = 0; i < mVexNum; i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			cout << mVexs[i].data << " ";
			queue[rear++] = i;
		}

		while (head != rear)
		{
			j = queue[head++];
			node = mVexs[j].firstEdge;
			while (node != NULL)
			{
				k = node->ivex;
				if (!visited[k])
				{
					visited[k] = 1;
					cout << mVexs[k].data << " ";
					queue[rear++] = k;
				}
				node = node->nextEdge;
			}
		}
		cout << endl;
	}

}