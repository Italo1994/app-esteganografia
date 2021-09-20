#ifndef __MANIPULARMSGEIMG
#define __MANIPULARMSGEIMG__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerEgravarImagem.h"

//pega bit a bit da mensagem
void pegar_bits_msg(char *mensagem);

void encodificar_msg(FILE *img, PIXEL ***Matriz, int largura, int altura, int tam_msg, char *str,BITMAPINFOHEADER cab2, char *formato);

void decodificar_msg(FILE *img, PIXEL **Matriz, int largura, int altura,char *nomeArq, int tam_msg, BITMAPINFOHEADER cab2, char *formato);


#endif //__MANIPULARMSGEIMG__