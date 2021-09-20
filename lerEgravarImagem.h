#ifndef _LEREGRAVARIMAGEM__
#define _LEREGRAVARIMAGEM__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cabeçalho 1
typedef struct tagBITMAPFILEHEADER{  //ocupa 14 bytes e o 1° a aparecer no arquivo/ficheiro 
	char bfType[3]; //especifica o formato da imagem BMP
	unsigned int bfSize; //tamanho do arquivo em bytes
	unsigned short int bfReserved1;	
	unsigned short int bfReserved2;	
	unsigned int bfOffBits; //número de bytes deslocado para iniciar a leitura
}BITMAPFILEHEADER;

//Cabeçalho 2
typedef struct tagBITMPAINFOHEADER{ 
	unsigned int biSize; //tamanho do cabeçalho	
	unsigned int biWidth; //largura da imagem
	unsigned int biHeight; //altura da imagem
	unsigned short MbiPlanes; //quantidade de planos da imagem	
	unsigned short biBitCount;	//quantidade de bits por pixel
	unsigned int biCompression; //compressão, se existit
	unsigned int biSizeImage; //tamanho da imagem em bytes
	unsigned int biXPelsPerMeter; //número de pixels por metro horizontalmente
	unsigned int biYPelsPerMeter; //número de pixels por metro verticalmente
	unsigned int biClrUsed;	 //quantidade de cores utilizadas na imagem
	unsigned int biClrImportant;  //quantidade de cores importantes
}BITMAPINFOHEADER;

//define os pixels RGB da imagem
typedef struct{ 
	unsigned char rgbRed;      
	unsigned char rgbGreen;
	unsigned char rgbBlue;
} PIXEL;

typedef struct tagBITMAPINFO{  
	BITMAPINFOHEADER bmiHeader;
	PIXEL *bmiColors; 
}BITMAPINFO;

BITMAPFILEHEADER cab1;
BITMAPINFOHEADER cab2;

// Lê a imagem;
void ler_imagem(FILE *img, PIXEL ***Matriz, int *altura, int *largura, int *MAX, char *formato, BITMAPFILEHEADER *cab1, BITMAPINFOHEADER *cab2);

// Grava a imagem
void gravar_imagem(FILE *img, PIXEL **Matriz, char *formato, int largura, int altura, int MAX, BITMAPFILEHEADER cab1, BITMAPINFOHEADER cab2);


#endif //_LEREGRAVARIMAGEM__