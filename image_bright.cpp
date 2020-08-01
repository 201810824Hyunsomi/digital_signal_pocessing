#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>// 위에 두 부분은 파일 입출력을 하기 위한 부분
#include <Windows.h>//구조체 정보를 가지고 있는 헤더 파일
void original(BYTE *img, BYTE *Out, int W, int H)
{
	int ImgSize = W * H;
	for (int i = 0; i < ImgSize; i++)
	{
		Out[i] = img[i];
	}

}
void change(BYTE *img, BYTE *Out, int W, int H)
{
	int ImgSize = W * H;
	for (int i = 0; i < ImgSize; i++)
	{
		Out[i] = 255 - img[i];
	}

}
void bright_change(BYTE *img, BYTE *Out, int W, int H)
{
	int ImgSize = W * H;
	for (int i = 0; i < ImgSize; i++)
	{
		Out[i] = 100 + img[i];
	}

}
void main()
{
	
	BITMAPFILEHEADER hf; // BMP 파일헤더 14Bytes
	BITMAPINFOHEADER hInfo; // BMP 인포헤더 40Bytes
	RGBQUAD hRGB[256]; // 팔레트 (256 * 4Bytes)
	FILE *fp;//데이터를 읽거나 내보낼 때 필요
	fp = fopen("lenna.bmp", "rb");// read binary mode 로 오픈함, fp에는 파일의 제일 첫번째 주소나 위치 가르킴
	if (fp == NULL) return;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);//fread 함수로 정보를 읽어 메모리 변수에 담는 과정
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;//영상의 화소 정보
	BYTE * Image = (BYTE *)malloc(ImgSize);//원래영상의 화소정보
	BYTE * Output = (BYTE *)malloc(ImgSize);//영상이 처리된 결과를 담는 배열 (둘의 크기는 동일 
	BYTE * Output2 = (BYTE *)malloc(ImgSize);
	BYTE * Output3 = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);
	/* 영상처리 */
	change(Image, Output, hInfo.biWidth, hInfo.biHeight);
	original(Image, Output2, hInfo.biWidth, hInfo.biHeight);
	bright_change(Image, Output3, hInfo.biWidth, hInfo.biHeight);
	fp = fopen("output.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), ImgSize, fp);
	fclose(fp);
	free(Image);
	free(Output);//메모리 누수 현상을 방지하기 위해서
	free(Output2);
	free(Output3);
}
