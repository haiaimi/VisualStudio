// FindWay.cpp : Defines the entry point for the console application.
//


#include "Graphics.h"
#include "conio.h"
#include "GetRoute.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void DrawWaybyStack();
void DrawWaybyRecur();
void DrawWaybyQueue();

int main()
{
	initgraph(800, 600);
	setbkcolor(LIGHTGRAY);
	cleardevice();

	
	
	//�����ͼ

	int length=0;     //��ͼ��
	int width=0;      //��ͼ��

	FILE *fp = fopen("Map.txt", "r");
	if (fp == NULL)
	{
		RECT r = { 200,20,50,100 };
		drawtext("��ͼ���ش���", &r, DT_CENTER);
		return -1;
	}

	fscanf(fp, "%d,", &length);
	fscanf(fp, "%d,", &width);

	if (length <= 0) length = 1;
	if (width <= 0) width = 1;

	//��̬������ά����
	int **a;
	a = new int*[width];
	for (int i = 0; i < width; i++) {
		a[i] = new int[length];
	}
	
	//��ȡ��ͼ
	
	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++) {
			fscanf(fp, "%d,", &a[i][j]);
		}

	
	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++) {
			if (a[i][j] == 0) {
				setfillcolor(BLACK);
				solidrectangle(j * 50, i * 50, 50 + j * 50, 50 + i * 50);
			}
			else{
				setfillcolor(RED);
				fillrectangle(j * 50, i * 50, 50 + j * 50, 50 + i * 50);
			}
		}
	

	setfillcolor(YELLOW);
	fillroundrect(560, 20, 650, 100, 30, 30);
	fillroundrect(560, 120, 650, 200, 30, 30);
	fillroundrect(560, 220, 650, 300, 30, 30);

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(16, 0, _T("����"));
	outtextxy(580, 50, _T("ջ����"));
	outtextxy(575, 150, _T("�ݹ鷽��"));
	outtextxy(580, 250, _T("�ӷ���"));
	
	while (true) {

		while (MouseHit()) {

			MOUSEMSG moumsg = GetMouseMsg();

			if (moumsg.uMsg == WM_LBUTTONDOWN)

				if (moumsg.x > 560 && moumsg.x < 650)

					if (moumsg.y > 20 && moumsg.y < 100)

						DrawWaybyStack();

					else if (moumsg.y > 120 && moumsg.y < 200)

						DrawWaybyRecur();

					else if (moumsg.y > 220 && moumsg.y < 300)

						DrawWaybyQueue();
					
		}
	
	}
	
	getchar();
	closegraph();
    return 0;
}

void DrawWaybyStack() {
	
	cleardevice();
	int length = 0;     //��ͼ��
	int width = 0;      //��ͼ��

	FILE *fp = fopen("Map.txt", "r");
	if (fp == NULL)
	{
		RECT r = { 200,20,50,100 };
		drawtext("��ͼ���ش���", &r, DT_CENTER);
	}

	fscanf(fp, "%d,", &length);
	fscanf(fp, "%d,", &width);

	if (length <= 0) length = 1;
	if (width <= 0) width = 1;

	//��̬������ά����
	int **a;
	a = new int*[width];
	for (int i = 0; i < width; i++) {
		a[i] = new int[length];
	}

	//��ȡ��ͼ

	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++) {
			fscanf(fp, "%d,", &a[i][j]);
		}


	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++) {
			if (a[i][j] == 0) {
				setfillcolor(BLACK);
				solidrectangle(j * 50, i * 50, 50 + j * 50, 50 + i * 50);
			}
			else {
				setfillcolor(RED);
				fillrectangle(j * 50, i * 50, 50 + j * 50, 50 + i * 50);
			}
		}


	setfillcolor(YELLOW);
	fillroundrect(560, 20, 650, 100, 30, 30);
	fillroundrect(560, 120, 650, 200, 30, 30);
	fillroundrect(560, 220, 650, 300, 30, 30);

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(16, 0, _T("����"));
	outtextxy(580, 50, _T("ջ����"));
	outtextxy(575, 150, _T("�ݹ鷽��"));
	outtextxy(580, 250, _T("�ӷ���"));

	int r[2] = { 9,9 };
	GetRoute getroute(a, width, length, r);
	getroute.FindRoutebyStack();        //ʹ��ջ����
	//��ȡջ������
	
	int* e[50] = { NULL };
	//*e = new int[2];
	getroute.Stack.getelement(e);
	int top = getroute.Stack.gettop();
	TCHAR s[100];
	_stprintf(s, _T("�����ڵ㣺%d"), top);
	outtextxy(670, 50, s);

	for (int i = 0; i < top; i++) {
		if (e[i] == NULL)break;
		int x = e[i][0];
		int y = e[i][1];
		setfillcolor(GREEN);
		fillrectangle(y * 50, x * 50, 50 + y * 50, 50 + x * 50);
		Sleep(500);
	}
	    fillrectangle(r[1] * 50, r[0] * 50, 50 + r[1] * 50, 50 + r[0] * 50);
	}

void DrawWaybyRecur() {
	
	setbkcolor(LIGHTGRAY);
	cleardevice();
	//�����ͼ
	int length = 0;     //��ͼ��
	int width = 0;      //��ͼ��

	FILE *fp = fopen("Map.txt", "r");
	if (fp == NULL)
	{
		RECT r = { 200,20,50,100 };
		drawtext("��ͼ���ش���", &r, DT_CENTER);
	}

	fscanf(fp, "%d,", &length);
	fscanf(fp, "%d,", &width);

	if (length <= 0) length = 1;
	if (width <= 0) width = 1;

	//��̬������ά����
	int **a;
	a = new int*[width];
	for (int i = 0; i < width; i++) {
		a[i] = new int[length];
	}

	//��ȡ��ͼ

	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++) {
			fscanf(fp, "%d,", &a[i][j]);
		}


	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++) {
			if (a[i][j] == 0) {
				setfillcolor(BLACK);
				solidrectangle(j * 50, i * 50, 50 + j * 50, 50 + i * 50);
			}
			else {
				setfillcolor(RED);
				fillrectangle(j * 50, i * 50, 50 + j * 50, 50 + i * 50);
			}
		}


	setfillcolor(YELLOW);
	fillroundrect(560, 20, 650, 100, 30, 30);
	fillroundrect(560, 120, 650, 200, 30, 30);
	fillroundrect(560, 220, 650, 300, 30, 30);

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(16, 0, _T("����"));
	outtextxy(580, 50, _T("ջ����"));
	outtextxy(575, 150, _T("�ݹ鷽��"));
	outtextxy(580, 250, _T("�ӷ���"));

	int r[2] = { 9,9 };
	GetRoute getroute(a, 10, 10, r);
	int i = 0;
	getroute.FindRoutebyRecur(0,0,i);  //ʹ�õݹ鷽��

	int e[50][2] = { NULL };
	
	getroute.SaveRoute(e);
	
	int step = getroute.GetStepNum();
	TCHAR s[100];
	_stprintf(s, _T("�����ڵ㣺%d"), step);
	outtextxy(670, 50, s);

	for (int i = 0; i < step; i++) {
		if (e[i] == NULL)break;
		int x = e[i][0];
		int y = e[i][1];
		setfillcolor(GREEN);
		fillrectangle(y * 50, x * 50, 50 + y * 50, 50 + x * 50);
		Sleep(500);
	}

	
}

void DrawWaybyQueue() {

	cleardevice();

	//�����ͼ
	int length = 0;     //��ͼ��
	int width = 0;      //��ͼ��

	FILE *fp = fopen("Map.txt", "r");
	if (fp == NULL)
	{
		RECT r = { 200,20,50,100 };
		drawtext("��ͼ���ش���", &r, DT_CENTER);
	}

	fscanf(fp, "%d,", &length);
	fscanf(fp, "%d,", &width);

	if (length <= 0) length = 1;
	if (width <= 0) width = 1;

	//��̬������ά����
	int **a;
	a = new int*[width];
	for (int i = 0; i < width; i++) {
		a[i] = new int[length];
	}

	//��ȡ��ͼ

	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++) {
			fscanf(fp, "%d,", &a[i][j]);
		}


	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++) {
			if (a[i][j] == 0) {
				setfillcolor(BLACK);
				solidrectangle(j * 50, i * 50, 50 + j * 50, 50 + i * 50);
			}
			else {
				setfillcolor(RED);
				fillrectangle(j * 50, i * 50, 50 + j * 50, 50 + i * 50);
			}
		}


	setfillcolor(YELLOW);
	fillroundrect(560, 20, 650, 100, 30, 30);
	fillroundrect(560, 120, 650, 200, 30, 30);
	fillroundrect(560, 220, 650, 300, 30, 30);

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(16, 0, _T("����"));
	outtextxy(580, 50, _T("ջ����"));
	outtextxy(575, 150, _T("�ݹ鷽��"));
	outtextxy(580, 250, _T("�ӷ���"));

	int r[2] = { 9,9 };
	GetRoute getroute(a, 10, 10, r);

	getroute.FindRoutebyQueue();        //ʹ�öӷ���

	int e[50][2] = { NULL };

	getroute.SaveRoute(e);

	int step = getroute.GetStepNum()+1;
	TCHAR s[100];
	_stprintf(s, _T("����·�̣�%d"), step);
	outtextxy(670, 50, s);

	for (int i = 0; i < step-1; i++) {
		if (e[i] == NULL)break;
		int x = e[i][0];
		int y = e[i][1];
		setfillcolor(GREEN);
		fillrectangle(y * 50, x * 50, 50 + y * 50, 50 + x * 50);
		Sleep(500);
	}

	fillrectangle(r[1] * 50, r[0] * 50, 50 + r[1] * 50, 50 + r[0] * 50);
}