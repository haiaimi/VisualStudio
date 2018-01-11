
#include "SeqStack.h"
#include "LinkedQueue.h"
#include "stdafx.h"
#include "stdlib.h"

class GetRoute 
{
private:
	 
	int **map;                //地图数组
	int width;                //地图宽
	int length;               //地图长
	int *Export;              //出口位置
	int temp[40][2] = {0};  
	int StepNum=0;            //路程
	struct Position           //点结构
	{         
		int x;
		int y;
		int tag;              //该点所在线路的标签

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
	SeqStack<int*> Stack;      //栈
	LinkedQueue<Position> Queue;  //队列
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

