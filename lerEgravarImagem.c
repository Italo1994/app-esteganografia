#include "lerEgravarImagem.h"

void ler_imagem(FILE *img, PIXEL ***Matriz, int *altura, int *largura, int *MAX, char *formato, BITMAPFILEHEADER *cab1, BITMAPINFOHEADER *cab2) {
	int i, j;
	//int MAX;


	fscanf(img, "%c%c", &formato[0], &formato[1]); //Lê o formato da imagem
	formato[2] = '\0'; //Insere no último índice o caractere especial delimitador do final da string 

	if(strcmp(formato, "P6") != 0 && strcmp(formato, "BM") != 0){//verifica se o formato é válido(PPM ou BMP)
		fprintf(stderr, "O FORMATO DA IMAGEM NÃO É VÁLIDO\n");
		ferror(img);
	}

	if(strcmp(formato, "P6") == 0){ //testa se o formato é PPM binário
		fscanf(img, "%d %d %d", largura, altura, MAX); //Lê o cabeçalho da imagem
		fgetc(img);
		*Matriz = (PIXEL **) malloc( (*largura) * sizeof(PIXEL *)); //Aloca dinamicamente a largura da imagem
		for(i=0; i<*largura; i++){ //Percorre as colunas 
			(*Matriz)[i] = (PIXEL *) malloc( (*altura) * sizeof(PIXEL) ); //Aloca dinamicamente a altura da imagem
			for(j=0; j<*altura; j++){ //Percorre as linhas
				fscanf(img, "%c%c%c", &(*Matriz)[i][j].rgbRed, &(*Matriz)[i][j].rgbGreen, &(*Matriz)[i][j].rgbBlue); //Lê as cores por pixel
			}
		}
	}

	if(strcmp(formato, "BM") == 0){ //Verifica se o formato é BMP
		rewind(img); //Aponta para o início do arquivo

	  /*Lê todos os atributos do cabeçalho 1*/
		fread(&cab1->bfType, sizeof(cab1->bfType)-1, 1,img);
	    fread(&cab1->bfSize, sizeof(cab1->bfSize), 1,img);
	    fread(&cab1->bfReserved1, sizeof(cab1->bfReserved1), 1,img);
	    fread(&cab1->bfReserved2, sizeof(cab1->bfReserved2), 1,img);
	    fread(&cab1->bfOffBits, sizeof(cab1->bfOffBits), 1,img);
	  /*Lê todos os atributos do cabeçalho 2*/
	    fread(&cab2->biSize, sizeof(cab2->biSize), 1,img);
	    fread(&cab2->biWidth, sizeof(cab2->biWidth), 1,img);
	    fread(&cab2->biHeight, sizeof(cab2->biHeight), 1,img);
	    fread(&cab2->MbiPlanes, sizeof(cab2->MbiPlanes), 1,img);
	    fread(&cab2->biBitCount, sizeof(cab2->biBitCount), 1,img);
	    fread(&cab2->biCompression, sizeof(cab2->biCompression), 1,img);
	    fread(&cab2->biSizeImage, sizeof(cab2->biSizeImage), 1,img);
	    fread(&cab2->biXPelsPerMeter, sizeof(cab2->biXPelsPerMeter), 1,img);
	    fread(&cab2->biYPelsPerMeter, sizeof(cab2->biYPelsPerMeter), 1,img);
	    fread(&cab2->biClrUsed, sizeof(cab2->biClrUsed), 1,img);
	    fread(&cab2->biClrImportant, sizeof(cab2->biClrImportant), 1,img);
		int trash;

		*Matriz = (PIXEL **) malloc( cab2->biHeight * sizeof(PIXEL *) ); //Aloca dinamicamente a altura da imagem
		for(i=0; i<cab2->biHeight; i++){ //Percorre as linhas
			(*Matriz)[i] = (PIXEL *) malloc( cab2->biWidth * sizeof(PIXEL) ); //Aloca dinamicamente as colunas
			for(j=0; j<cab2->biWidth; j++){ //Percorre as colunas
				fscanf(img, "%c%c%c",  &(*Matriz)[i][j].rgbRed, &(*Matriz)[i][j].rgbGreen, &(*Matriz)[i][j].rgbBlue); //Lê as cores por pixel
			}
		}
	}
}

void gravar_imagem(FILE *img, PIXEL **Matriz, char *formato, int largura, int altura, int MAX, BITMAPFILEHEADER cab1, BITMAPINFOHEADER cab2) {
	int i, j;

	if(strcmp(formato, "P6") != 0 && strcmp(formato, "BM") != 0){ //Verifica se o formato é válido
		fprintf(stderr, "O FORMATO DA IMAGEM NÃO É VÁLIDO\n");
		ferror(img);
	}

	if(strcmp(formato, "P6") == 0){ //Verifica se o formato é PPM binário
		fprintf(img, "%s\n%d %d\n%d\n", formato, largura, altura, MAX); //imprime o cabeçalho no arquivo "img"

		for(i=0; i<largura; i++){ //Percorre as colunas
			for(j=0; j<altura; j++){ //Percorre as linha
				fprintf(img, "%c%c%c", Matriz[i][j].rgbRed, Matriz[i][j].rgbGreen, Matriz[i][j].rgbBlue); //Imprime as cores/pixel no arquivo "img"
			}
		}
	}

	if(strcmp(formato, "BM") == 0){ //Verifica se o formato é BMP
		rewind(img); //Aponta para o início do arquivo

		 /*Lê todos os atributos do cabeçalho 1*/
		fwrite(&cab1.bfType, sizeof(cab1.bfType)-1, 1,img);
	    fwrite(&cab1.bfSize, sizeof(cab1.bfSize), 1,img);
	    fwrite(&cab1.bfReserved1, sizeof(cab1.bfReserved1), 1,img);
	    fwrite(&cab1.bfReserved2, sizeof(cab1.bfReserved2), 1,img);
	    fwrite(&cab1.bfOffBits, sizeof(cab1.bfOffBits), 1,img);
	  /*Lê todos os atributos do cabeçalho 2*/
	    fwrite(&cab2.biSize, sizeof(cab2.biSize), 1,img);
	    fwrite(&cab2.biWidth, sizeof(cab2.biWidth), 1,img);
	    fwrite(&cab2.biHeight, sizeof(cab2.biHeight), 1,img);
	    fwrite(&cab2.MbiPlanes, sizeof(cab2.MbiPlanes), 1,img);
	    fwrite(&cab2.biBitCount, sizeof(cab2.biBitCount), 1,img);
	    fwrite(&cab2.biCompression, sizeof(cab2.biCompression), 1,img);
	    fwrite(&cab2.biSizeImage, sizeof(cab2.biSizeImage), 1,img);
	    fwrite(&cab2.biXPelsPerMeter, sizeof(cab2.biXPelsPerMeter), 1,img);
	    fwrite(&cab2.biYPelsPerMeter, sizeof(cab2.biYPelsPerMeter), 1,img);
	    fwrite(&cab2.biClrUsed, sizeof(cab2.biClrUsed), 1,img);
	    fwrite(&cab2.biClrImportant, sizeof(cab2.biClrImportant), 1,img);
		int trash;

		for(i=0; i<cab2.biHeight; i++){ //Percorre as linhas
			for(j=0; j<cab2.biWidth; j++){ //Percorre as colunas
				fprintf(img, "%c%c%c",  Matriz[i][j].rgbRed, Matriz[i][j].rgbGreen, Matriz[i][j].rgbBlue); //Imprime as cores/pixel no arquivo "img"
			}
		}
	}
}

