#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "editor.h"
#include "main.c"

#define MAX_LINHA 10010
struct editorTCD{
	/*Vetor sobre o qual o texto será manipulado*/
	char linha[MAX_LINHA], aux[MAX_LINHA];
	/*Apontam para o caractere inicial e final*/
	char *inicio, *fim;
	/*Aponta para uma posição depois do último caractere antes do cursor*/
	char *cursor;
	/*Aponta para o primeiro caractere depois do cursor*/
	char *proximo;
	/*Caractere que corresponte ao cursor: '^'*/
	char cs; 
	
	char *marcador;
	/*Marca uma posição após o último caractere copiado*/
	char *copia;
};

editorTAD Editor (){
	editorTAD editor = (editorTAD) malloc(sizeof((editorTAD) NULL));
	editor -> inicio = editor -> linha;
	editor -> fim = ( editor -> linha ) + MAX_LINHA - 1;
	/*Inicializado no começo do texto*/
	editor -> cursor = editor -> inicio;
	/*Inicializado no fim do vetor*/
	editor -> proximo = editor -> fim;
	editor -> cs = '^';
	editor -> marcador = (char *) -1;
	editor -> copia = editor -> aux;
	return editor;
}

void CarregaTexto (editorTAD e, char *nome) {
	/*Caracteres de iteração*/
	char c, *k;
	printf("vai carregar\n");
	FILE *arquivo = fopen (nome, "r");
	printf("carregou\n");
	if (arquivo != NULL){
		printf("Não nulo\n");
		c = getc(arquivo);printf("%x\n ", (unsigned int) c);
		printf("first char\n");
		while(c != EOF && c != 3 && c != 4){
			printf("access [%ld] ", e->cursor-e->inicio);
			printf("[%ld] ", e->fim-e->cursor);
			
			if (e->cursor < e->proximo){
				/*Grava o caractere lido e avança o cursor*/
				*(e->cursor++) = c;printf("%2x(%c) \n", (unsigned int) c, c);
				printf("[%ld] ", e->proximo-e->inicio);
			}
			else{
				printf("Editor cheio!\n"); break;}
			c = getc(arquivo);
			printf("[%ld] ", e->proximo-e->cursor);
		}
		/*Deslocamento dos caracteres para o fim do vetor*/
		for(k = e->cursor - 1; k >= e->inicio; k--){
			*(k + (e->fim - e->cursor) + 1) = *k;
		}
		/*Deslocamento do ponteiro 'proximo' para o primeiro caractere deslocado*/
		e->proximo = e->inicio + (e->fim - e->cursor) + 1;
		/*Cursor volta ao inicio*/
		e->cursor = e->inicio;
	} else printf("Arquivo vazio!\n");
	fclose(arquivo);
}

void ExibeEditor(editorTAD e){
	char *c;
	/*Exibe a parte antes do cursor*/
	for(c = e->inicio; c < e-> cursor; c++)
		printf("%c", *c);
	/*Exibe o cursor*/
	printf("%c", (e->cs));
	/*Exibe a parte depois do cursor*/
	for(c = e->proximo; c <= e-> fim; c++)
		printf("%c", *c);
	printf("\nInício: %c\nCursor-1: %c\nPróximo: %c\nFinal: %c\n", *e->inicio, *(e->cursor-1), *e->proximo, *e->fim);
}

void InsereCaractere (editorTAD editor, char caractere) {
	if (editor->cursor < editor->proximo)
		*(editor->cursor++) = caractere;
}

void RemoveCaractereAtual (editorTAD editor) {
	if (editor->proximo < editor->fim)
		editor->proximo++;
}

void RemoveCaractereAnterior (editorTAD editor) {
	if (editor->cursor > editor->inicio)
		editor->cursor--;
}

void RetrocedeCursor (editorTAD editor) {
	if (editor->cursor > editor->inicio)
		*(--editor->proximo) = *(--editor->cursor);
}

void AvancaCursor (editorTAD editor) {
	if (editor->proximo < editor->fim)
		*(editor->cursor++) = *(editor->proximo++);
}

void MarcaPosicao (editorTAD editor) {
	editor->marcador = editor->proximo;
}

void CopiaTexto (editorTAD editor) {
	char *k;
	if (editor->marcador != (char *) -1) {
		editor->copia = editor->aux;
		if (editor->marcador > editor->proximo) {
			for(k = editor->marcador; k >= editor->proximo; k--)
				*(editor->copia++) = *k;
		}
		else if (editor->marcador < editor->proximo) {
			for(k = editor->proximo; k >= editor->marcador; k--)
				*(editor->copia++) = *k;
		}
		editor->marcador = (char *) -1;
	}
}

void InsereTexto (editorTAD editor) {
	if (editor->copia > editor->aux)
		while (editor->copia > editor->aux)
			InsereCaractere (editor, *(--editor->copia));
}

void SalvaTexto (editorTAD editor, char *nome) {
	char *k;
	FILE *arquivo = fopen (nome, "w");
	for (k = editor->inicio; k < editor->cursor; k++)
		putc(*k, arquivo);
	for (k = editor->proximo; k < editor->fim; k++)
		putc(*k, arquivo);
	fclose(arquivo);
}



