#include "lerEgravarImagem.h"
#include "manipularMsgEimg.h"

int main(int argc, char **argv){
	char nomeArquivoTxt[40];
	FILE *arqTexto = fopen("mensagem.txt", "w"); //abertura de um arquivo txt para escrita
	PIXEL **matriz;//matriz de pixels
	int largura, altura, MAX, i, j; //largura, altura e máximo de cores
	char mensagem[8000]; //mensagem usada na encodificação e decodificação
	//mensagem = (char *) malloc(80*sizeof(char)); //alocação dinâmica para a mensagem

	if(mensagem == NULL){
		printf("NÃO FOI POSSÍVEL ALOCAR MEMÓRIA PARA O VETOR\n");
	}

	char nomeArquivo[25]; //nome do arquivo da imagem
	char formato[3]; //formato da imagem
	BITMAPFILEHEADER cab1; //variável do tipo cabeçalho 1
	BITMAPINFOHEADER cab2; //variável do tipo cabeçalho 2
	int tamMsg; //tamanho da mensagem

	printf("Nome do arquivo que deseja abrir:\n");
		scanf("%s", nomeArquivo);


	FILE *img = fopen(nomeArquivo, "rb"); //abre o arquivo para leitura em binário

	if(img == NULL){ //verifica se o arquivo existe
		fprintf(stderr, "ERRO, NÃO FOI POSSÍVEL ABRIR O ARQUIVO\n");
		ferror(img);
	}

	ler_imagem(img, &matriz, &altura, &largura, &MAX, formato, &cab1, &cab2); //função que lê a imagem
 		
 		fclose(img); //fecha o imagem



	img = fopen(nomeArquivo, "wb"); //reabre o arquivo para escrita em binário 

		
		printf("Insira uma mensagem:\n");
		fgetc(stdin); //limpando o buffer
		fgets(mensagem, 80, stdin);
	
		printf("Nome do arquivo de saida da mensagem:\n");
		scanf("%s", nomeArquivoTxt);

		tamMsg = strlen(mensagem)*8; //pega o tamanho da mensagem;
		char str[tamMsg*9];

		pegar_bits_msg(mensagem);

		printf("%s\n", mensagem);
		encodificar_msg(img, &matriz, largura, altura, tamMsg, mensagem, cab2, formato); //função que encodifica a mensagem
	
		gravar_imagem(img, matriz, formato, largura, altura, MAX, cab1, cab2); //função que grava os dados lidos na imagem

		decodificar_msg(img, matriz, largura, altura, nomeArquivoTxt, tamMsg, cab2, formato);

		fclose(img); //fecha a imagem novamente
		return 0;

}	