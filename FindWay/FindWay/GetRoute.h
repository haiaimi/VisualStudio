
#include "SeqStack.h"
#include "LinkedQueue.h"
#include "stdafx.h"
#include "stdlib.h"

class GetRoute 
{
private:
	 
	int **map;                //��ͼ����
	int width;                //��ͼ��
	int length;               //��ͼ��
	int *Export;              //����λ��
	int temp[40][2] = {0};  
	int StepNum=0;            //·��
	struct Position           //��ṹ
	{         
		int x;
		int y;
		int tag;              //�õ�������·�ı�ǩ

		Position()
		{
			x = 0;
			y = 0;
			tag = 0;
		}

		Position(int m, int n, int t)
		{
			x = m;
			y = n;
			tag = t;
		}
		Position & operator = (Position &str) {
			this->x = str.x;
			this->y = str.y;
			this->tag = str.tag;
			return *this;
		}
	};
	
public:

	int route[40][2] = {0};
	SeqStack<int*> Stack;      //ջ
	LinkedQueue<Position> Queue;  //����
	GetRoute(int **a,int w,int l,int r[]);

	void FindRoutebyStack();
	void FindRoutebyRecur(int x, int y, int &count);
	void FindRoutebyQueue();

	bool IsExport();
	bool IsNoWay(int x, int y);

	void SaveRoute(int a[][2]);
	int GetStepNum();
	void RandSearch(int x, int y,int tag);
	
	
};

