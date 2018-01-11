
#include "GetRoute.h"

//��ȡ·����Ĺ��캯��
GetRoute::GetRoute(int **a,int w,int l,int r[]) {
	
	width = w;
	length = l;

	map = new int*[width];
	for (int i = 0; i < width; i++) {
		map[i] = new int[length];
	}

	map[0][0] = 1;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++)
			map[i][j] = a[i][j];
	}
	
	Export = r;
	int *b = new int[2];
	b[0] = 0;
	b[1] = 0;
	Stack.push(b);

}

//ջ����Ѱ·
void GetRoute::FindRoutebyStack() {

	int *b = new int[2];
	int i, j;

	while (1)
	{
		b = Stack.get();      //�õ���ǰջ��Ԫ��
		i = b[0];
		j = b[1];
		int n, m;
		int pushcount = 0;  //�ڸõ���ջ����
		n = i; m = j - 1;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[n][m] == 0) {
				int *a = new int[2];
				a[0] = n;
				a[1] = m;
				Stack.push(a);
				pushcount++;
				map[n][m] = 2;
			}
			else {
				n = i - 1; m = j;
			}
		}
		if (IsExport())break;

		n = i - 1; m = j;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[n][m] == 0) {
				int *a = new int[2];
				a[0] = n;
				a[1] = m;
				Stack.push(a);
				pushcount++;
				map[n][m] = 2;
			}
		}
		if (IsExport())break;

		n = i; m = j + 1;
		if (m > -1 && m < width && n > -1 && n < length)
			if (map[n][m] == 0) {
				int *a = new int[2];
				a[0] = n;
				a[1] = m;
				Stack.push(a);
				pushcount++;
				map[n][m] = 2;
			}
			if (IsExport())break;

			n = i + 1; m = j;
			if (m > -1 && m < width && n > -1 && n < length) {
				if (map[n][m] == 0) {
					int *a = new int[2];
					a[0] = n;
					a[1] = m;
					Stack.push(a);
					pushcount++;
					map[n][m] = 2;
				}
			}
			if (IsExport())break;

			if (pushcount == 0)   //����õ�û����ջ�ͳ�ջ,������һ��
				Stack.pop();

		}
	}

//�ݹ鷽��Ѱ·
void GetRoute::FindRoutebyRecur(int x, int y, int &count) {

	map[x][y] = 2;
	temp[count][0] = x;
	temp[count][1] = y;

	if (x == Export[0] && y == Export[1]) {
		for (int i = 0; i <= count; i++) {
			route[i][0] = temp[i][0];
			route[i][1] = temp[i][1];
			
		}
		StepNum = count;
		}
		count++;

	if (!IsNoWay(x, y)) {
		
		int n, m;

		n = x; m = y - 1;
		if (m > -1 && m < width && n > -1 && n < length) {

			if (map[n][m] == 0)
				FindRoutebyRecur(x, y - 1, count);
		}
		
		n = x - 1; m = y;
		if (m > -1 && m < width && n > -1 && n < length) {

			if (map[x - 1][y] == 0)
				FindRoutebyRecur(x - 1, y, count);
		}

		n = x; m = y + 1;
		if (m > -1 && m < width && n > -1 && n < length) {

			if (map[n][m] == 0)
				FindRoutebyRecur(x, y + 1, count);
		}

		n = x + 1; m = y;
		if (m > -1 && m < width && n > -1 && n < length) {

			if (map[n][m] == 0)
				FindRoutebyRecur(x + 1, y, count);
		}

		 temp[count][0] = 0;
		 temp[count][0] = 0;
		 count--;

	}
	else {
		temp[count][0] = 0;
		temp[count][0] = 0;
		count--;
	}

}

//���з���Ѱ·
void GetRoute::FindRoutebyQueue() {

	Position line[60][60];              //�����е�·�ߣ����֧��60��·������
	int a[2] = { 0,0 };        
	Position begin(0, 0, 0);            //Ĭ�����
	Queue.enqueue(begin);
	map[0][0] = 2;
	int l = 0;                          //·�ߺ�
	int step = 0;                       //·��
	bool FindExport = false;            //�Ƿ��ҵ�����


	while (!FindExport) {
		int m = 0;                      //һ��������ڽ�·
		Position temp[8];
		while (!Queue.empty()) {        //�ж϶����Ƿ�Ϊ��

			temp[m] = Queue.dequeue();
			m++;
		}
		
		for (int i = 0; i < m; i++) {

			if (temp[i].x == Export[0] && temp[i].y == Export[1]) {
				int r = temp[i].tag;
				for (int k = 0; k < step; k++) {
					route[k][0] = line[r][k].x;
					route[k][1] = line[r][k].y;
				}
				FindExport = true;
				StepNum = step;
			}

			if (!IsNoWay(temp[i].x, temp[i].y)) {
				
					for (int j = 0; j < step; j++) {

						line[l][j] = line[temp[i].tag][j];
					}
					line[l][step] = temp[i];
					temp[i].tag = l;
			}
			        l++;

		    
		}
		        step++;

		for (int i = 0; i < m; i++) {
			int x = temp[i].x;
			int y = temp[i].y;

			if (!IsNoWay(x, y)) {
				//���Ҹõ���Χ�ĵ㣬���������
				int tag = temp[i].tag;
				RandSearch(x, y, tag);
			}
		}

	}
}

//�ж��Ƿ�Ϊ���ڣ�����ջ��
bool GetRoute::IsExport() {

	int *b = Stack.get();
	if (b[0] == Export[0] && b[1] == Export[1])
		return true;

	return false;
}

//�ж��Ƿ�����·�����ڵݹ�Ͷ��У�
bool GetRoute::IsNoWay(int x,int y) {
	
	if (x > 0 && x < width-1 && y > 0 && y < length-1) { 
		if (map[x][y - 1] && map[x - 1][y] && map[x][y + 1] && map[x + 1][y] ) {
			return true;
		}
   }
	if (x == 0 && y > 0 && y < length-1) {
		if (map[x][y - 1] && map[x][y + 1] && map[x + 1][y] ) {
			return true;
		}
	}
	if (x == width-1 && y > 0 && y < length-1) {
		if (map[x][y - 1] && map[x - 1][y] && map[x][y + 1] ) {
			return true;
		}
	}
	if (x > 0 && x < width-1 && y == 0) {
		if (map[x - 1][y] && map[x][y + 1] && map[x + 1][y] ) {
			return true;
		}
	}
	if (x > 0 && x < width-1 && y == length-1) {
		if (map[x][y - 1] && map[x - 1][y] && map[x + 1][y]) {
			return true;
		}
	}
	if (x == 0 && y == 0) {
		if (map[x][y + 1] && map[x + 1][y]) {
			return true;
		}
	}
	if (x == 0 && y == length-1) {
		if (map[x][y - 1] && map[x + 1][y]) {
			return true;
		}
	}
	if (x == width-1 && y == 0) {
		if (map[x - 1][y] && map[x][y + 1]) {
			return true;
		}
	}
	if (x == width-1 && y == length-1) {
		if (map[x][y - 1] && map[x - 1][y]) {
			return true;
		}
	}
	return false;
}

void GetRoute::SaveRoute(int a[][2]) {

	for (int i = 0; i <= StepNum; i++) {
		a[i][0] = route[i][0];
		a[i][1] = route[i][1];
	}
}

//���ز���
int GetRoute::GetStepNum() {

	return StepNum+1;
}

//���ѡ����˳��
void GetRoute::RandSearch(int x, int y, int tag) {

	int r = rand() % 4;
	
	if (r == 0) {
		int m = x; int n = y - 1;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		m = x - 1;  n = y;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		m = x;  n = y + 1;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		m = x + 1;  n = y;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}
	}

	if (r == 1) {
		
		int m = x - 1;  int n = y;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		m = x;  n = y + 1;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		m = x + 1;  n = y;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

	    m = x;  n = y - 1;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}
	}

	if (r == 2) {

		int m = x;  int n = y + 1;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		m = x + 1;  n = y;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		 m = x;  n = y - 1;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		m = x - 1;  n = y;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}
	}
	
	if (r == 3) {

		int m = x + 1;  int n = y;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		 m = x; n = y - 1;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		m = x - 1;  n = y;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}

		m = x;  n = y + 1;
		if (m > -1 && m < width && n > -1 && n < length) {
			if (map[m][n] == 0) {
				Queue.enqueue(Position(m, n, tag));
				map[m][n] = 2;
			}
		}
	}
}