#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "editor.h"
#include "main.c"

#define MAX_LINHA 10010

typedef struct letra_struct *letra;

letra novaLetra(char c);

struct letra_struct{
	char v;
	letra next;
};

struct editorTCD{
	letra inicio, cursor, marcador, anterior;
};

editorTAD Editor (){
	editorTAD editor = (editorTAD) malloc(sizeof((editorTAD) NULL));
	editor->inicio = novaLetra((char) 0);
	editor->cursor = novaLetra('^');
	editor->inicio->next = editor->cursor;
	editor->marcador = (letra) -1;
	return editor;
}

letra novaLetra(char c){
	letra l = (letra) malloc (sizeof ( (letra) NULL));
	l->v = c;
	l->next = NULL;
	return l;
}

void CarregaTexto (editorTAD e, char *nome) {
	/*Caracteres de iteração*/
	char c, *k;
	letra l;
	FILE *arquivo = fopen (nome, "r");
	if (arquivo != NULL){
		c = getc(arquivo);printf("%x\n ", (unsigned int) c);
		while(c != EOF && c != 3 && c != 4){
			/*Grava o caractere lido*/
			l = novaLetra(c);
			l->next = (e->cursor)->next;
			(e->cursor)->next = l;
			//printf("%2x(%c) \n", (unsigned int) c, c);
			c = getc(arquivo);
		}
	} else printf("Arquivo vazio!\n");
	fclose(arquivo);
}

void ExibeEditor(editorTAD e){
	letra l;
	/*Exibe a parte antes do cursor*/
	for(l = e->inicio; l->next != NULL; l = l->next)
		printf("%c", l->v);
}

void InsereCaractere (editorTAD editor, char caractere) {
	
}

void RemoveCaractereAtual (editorTAD editor) {
	
}

void RemoveCaractereAnterior (editorTAD editor) {
	
}

void RetrocedeCursor (editorTAD editor) {
	
}

void AvancaCursor (editorTAD editor) {
	
}

void MarcaPosicao (editorTAD editor) {
	
}

void CopiaTexto (editorTAD editor) {
	
}

void InsereTexto (editorTAD editor) {
	
}

void SalvaTexto (editorTAD editor, char *nome) {
	
}
