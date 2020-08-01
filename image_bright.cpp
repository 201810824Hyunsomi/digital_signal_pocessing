#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>// ���� �� �κ��� ���� ������� �ϱ� ���� �κ�
#include <Windows.h>//����ü ������ ������ �ִ� ��� ����
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
	
	BITMAPFILEHEADER hf; // BMP ������� 14Bytes
	BITMAPINFOHEADER hInfo; // BMP ������� 40Bytes
	RGBQUAD hRGB[256]; // �ȷ�Ʈ (256 * 4Bytes)
	FILE *fp;//�����͸� �аų� ������ �� �ʿ�
	fp = fopen("lenna.bmp", "rb");// read binary mode �� ������, fp���� ������ ���� ù��° �ּҳ� ��ġ ����Ŵ
	if (fp == NULL) return;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);//fread �Լ��� ������ �о� �޸� ������ ��� ����
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;//������ ȭ�� ����
	BYTE * Image = (BYTE *)malloc(ImgSize);//���������� ȭ������
	BYTE * Output = (BYTE *)malloc(ImgSize);//������ ó���� ����� ��� �迭 (���� ũ��� ���� 
	BYTE * Output2 = (BYTE *)malloc(ImgSize);
	BYTE * Output3 = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);
	/* ����ó�� */
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
	free(Output);//�޸� ���� ������ �����ϱ� ���ؼ�
	free(Output2);
	free(Output3);
}
