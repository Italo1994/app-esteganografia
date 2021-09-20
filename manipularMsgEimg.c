#include "manipularMsgEimg.h"

void pegar_bits_msg(char *mensagem) {
	int i, j;
	int k = 0;
	char cpy[2];
	int tamanhoMsg = strlen(mensagem);
	char str[tamanhoMsg][8];
	
	for(i=0; i<tamanhoMsg; i++){
		str[i][0] = '\0';
		for(j=0; j<8; j++){
			sprintf(cpy,"%d", (mensagem)[i]%2);
			strcat(str[i], cpy);
			(mensagem)[i]/=2;
		}
		str[i][j] = '\0';
		//printf("%s ", str[i]);
	}
	printf("\n");

	for(i=0; i<tamanhoMsg; i++){
		for(j=0; j<8; j++){
			(mensagem)[k] = str[i][j];
			k++;
		}
	}
	printf("\n");
}

void encodificar_msg(FILE *img, PIXEL ***Matriz, int largura, int altura, int tam_msg, char *str, BITMAPINFOHEADER cab2, char *formato) {
	int l=0, i, j;
	printf("%s\n", str);
		fscanf(img, "%s", formato);

	if(strcmp(formato, "P6") == 0) {
		for(i=0; i<largura; i++) {
			for(j=0; j<altura && l < tam_msg; j++) {

				if( str[l] == '0' ) {
					(*Matriz)[i][j].rgbRed = (*Matriz)[i][j].rgbRed>>1;
					(*Matriz)[i][j].rgbRed = (*Matriz)[i][j].rgbRed<<1;
				}
				else {
					(*Matriz)[i][j].rgbRed = (*Matriz)[i][j].rgbRed | 1;
				}
				l++;
				if( str[l] == '0' ) {
					(*Matriz)[i][j].rgbGreen = (*Matriz)[i][j].rgbGreen>>1;
					(*Matriz)[i][j].rgbGreen = (*Matriz)[i][j].rgbGreen<<1;
				}
				else {
					(*Matriz)[i][j].rgbGreen = (*Matriz)[i][j].rgbGreen | 1;
				}
				l++;
				if( str[l] == '0' ) {
					(*Matriz)[i][j].rgbBlue = (*Matriz)[i][j].rgbBlue>>1;
					(*Matriz)[i][j].rgbBlue = (*Matriz)[i][j].rgbBlue<<1;
				}
				else {
					(*Matriz)[i][j].rgbBlue = (*Matriz)[i][j].rgbBlue | 1;
				}
				l++;
			}	
		}
	}

	if(strcmp(formato, "BM") == 0) {
		for(i=0; i<cab2.biHeight; i++) {
			for(j=0; j<cab2.biWidth && l < tam_msg; j++) {

				if( str[l] == '0' ) {
					(*Matriz)[i][j].rgbRed = (*Matriz)[i][j].rgbRed>>1;
					(*Matriz)[i][j].rgbRed = (*Matriz)[i][j].rgbRed<<1;
				}
				else {
					(*Matriz)[i][j].rgbRed = (*Matriz)[i][j].rgbRed | 1;
				}
				l++;
				if( str[l] == '0' ) {
					(*Matriz)[i][j].rgbGreen = (*Matriz)[i][j].rgbGreen>>1;
					(*Matriz)[i][j].rgbGreen = (*Matriz)[i][j].rgbGreen<<1;
				}
				else {
					(*Matriz)[i][j].rgbGreen = (*Matriz)[i][j].rgbGreen | 1;
				}
				l++;
				if( str[l] == '0' ) {
					(*Matriz)[i][j].rgbBlue = (*Matriz)[i][j].rgbBlue>>1;
					(*Matriz)[i][j].rgbBlue = (*Matriz)[i][j].rgbBlue<<1;
				}
				else {
					(*Matriz)[i][j].rgbBlue = (*Matriz)[i][j].rgbBlue | 1;
				}
				l++;
			}	
		}
	}


}

void decodificar_msg(FILE *img, PIXEL **Matriz, int largura, int altura, char *nomeArq, int tam_msg, BITMAPINFOHEADER cab2, char *formato) {
	int l=0, i, j, pot = 0;
	char c;
	char *vet;
	vet = malloc(tam_msg*3*sizeof(char));
	fscanf(img, "%s", formato);

	FILE *arq_texto = fopen(nomeArq, "w");

	if(strcmp(formato, "P6") == 0){
		for(i=0; i<largura; i++) {
			for(j=0; j<altura; j++) {
				if(Matriz[i][j].rgbRed%2 == 1 && l<tam_msg){
					vet[l] =  '1';	
					l++;
				}
				else if(Matriz[i][j].rgbRed%2 == 0 && l<tam_msg){
					vet[l] = '0';
					l++;
				}
				if(Matriz[i][j].rgbGreen%2 == 1 && l<tam_msg){
					vet[l] =  '1';	
					l++;
				}
				else if(Matriz[i][j].rgbGreen%2 == 0 && l<tam_msg){
					vet[l] = '0';
					l++;
				}
				if(Matriz[i][j].rgbBlue%2 == 1 && l<tam_msg){
					vet[l] =  '1';	
					l++;
				}
				else if(Matriz[i][j].rgbBlue%2 == 0 && l<tam_msg){
					vet[l] = '0';
					l++;
				}
			}		
		}

	}	

	if(strcmp(formato, "BM") == 0){
		for(i=0; i<cab2.biHeight; i++) {
			for(j=0; j<cab2.biWidth; j++) {
				if(Matriz[i][j].rgbRed%2 == 1 && l<tam_msg){
					vet[l] =  '1';	
					l++;
				}
				else if(Matriz[i][j].rgbRed%2 == 0 && l<tam_msg){
					vet[l] = '0';
					l++;
				}
				if(Matriz[i][j].rgbGreen%2 == 1 && l<tam_msg){
					vet[l] =  '1';	
					l++;
				}
				else if(Matriz[i][j].rgbGreen%2 == 0 && l<tam_msg){
					vet[l] = '0';
					l++;
				}
				if(Matriz[i][j].rgbBlue%2 == 1 && l<tam_msg){
					vet[l] =  '1';	
					l++;
				}
				else if(Matriz[i][j].rgbBlue%2 == 0 && l<tam_msg){
					vet[l] = '0';
					l++;
				}
			}		
		}
		
	}	

		/*for(i=0;i<l;i++){ 
			printf("%c",vet[i]);
		}*/

		printf("\n");
		for(j=0 ; j < tam_msg/8; j++, pot+=8){
			for(i=7;i >= 0;i--){
				if(vet[i+pot] == '1'){
					c=c<<1;
					c=c|1;
				}
				else if(vet[i+pot] == '0'){
					c=c<<1;
				}
			}
			fprintf(arq_texto, "%c", c);
			c=0;
		}
		fclose(arq_texto);
}




