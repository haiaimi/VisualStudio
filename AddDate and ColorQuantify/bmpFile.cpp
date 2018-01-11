#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

bool Write8BitImg2BmpFile(BYTE *pImg,int width,int height,BYTE *pPalette,const char * filename)
// 当宽度不是4的倍数时自动添加成4的倍数	
{  
	FILE * BinFile;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER BmpHeader;
	int i,extend;
	bool Suc=true;
	BYTE *pCur;

	// 打开文件
	if((BinFile=fopen(filename,"w+b"))==NULL) {  return false; }
	// 填充文件头
	FileHeader.bfType= ((WORD) ('M' << 8) | 'B');
	FileHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+256*4L;
	FileHeader.bfSize=FileHeader.bfOffBits+width*height ;
	FileHeader.bfReserved1=0;
	FileHeader.bfReserved2=0;
	if (fwrite((void *)&FileHeader,1,sizeof(FileHeader),BinFile)!=sizeof(FileHeader)) Suc=false;
	// 填充信息头
	BmpHeader.biSize = 40;
	BmpHeader.biWidth = width;
	BmpHeader.biHeight = height;
	BmpHeader.biPlanes = 1 ;
	BmpHeader.biBitCount = 8 ;
	BmpHeader.biCompression = 0 ;
	BmpHeader.biSizeImage = 0 ;
	BmpHeader.biXPelsPerMeter = 0;
	BmpHeader.biYPelsPerMeter = 0;
	BmpHeader.biClrUsed = 0;
	BmpHeader.biClrImportant = 0;
	if (fwrite((void *)&BmpHeader,1,sizeof(BmpHeader),BinFile)!=sizeof(BmpHeader)) Suc=false;
	// 写调色板数据
	for (i=0;i<256;i++) 
	{  
		if (fwrite((void *)(pPalette+i*4),1,4,BinFile)!=4) { Suc=false; break; }
	}
	// 写像素位图数据
	extend=(width+3)/4*4-width;//为了凑4的整数倍，每行需要填充的字节数
	if (extend==0)
	{   
		for(pCur=pImg+(height-1)*width;pCur>=pImg;pCur-=width)
		{   
			if (fwrite((void *)pCur,1,width,BinFile)!=(unsigned int)width) Suc=false; // 真实的数据
		}
	}
	else
	{   
		for(pCur=pImg+(height-1)*width;pCur>=pImg;pCur-=width)
		{   
			if (fwrite((void *)pCur,1,width,BinFile)!=(unsigned int)width) Suc=false; // 真实的数据
			for(i=0;i<extend;i++) // 填充凑数字节
				if (fwrite((void *)(pCur+width-1),1,1,BinFile)!=1) Suc=false;
		}
	}
	// 返回
	fclose(BinFile);
	return Suc;
}