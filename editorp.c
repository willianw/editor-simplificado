#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "editor.h"
#include "main.c"

#define MAX_LINHA 10010
struct editorTCD{
	/*Vetor sobre o qual o texto será manipulado, vetor auxiliar (cópia)*/
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


/*Implementação: há duas pilhas: a primeira, cuja base está no início do vetor e o topo cresce no sentido positivo (pos[base] < pos[topo]), que contém os caracteres antes do cursor.
A segunda, de base no fim do vetor e cujo topo cresce no sentido negativo (pos[topo] < pos[base]).
Em vez de usar o formato vec[topo], usei diretamente um ponteiro (char *) para essas localizações.*/
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
	int t;
	FILE *arquivo;
	if (arquivo != NULL){
		arquivo = fopen (nome, "r");
		fseek(arquivo, 0, SEEK_END);
		t = ftell(arquivo);
		fseek(arquivo, 0, SEEK_SET);
		/* Os caracteres serão lidos de forma que o último deles esteja na última posição do vetor, pois esses caracteres estarão na pilha depois do cursor (vide linha 26).*/
		e->proximo = e->linha + MAX_LINHA - 1 - t;
		fread(e->proximo, t, 1, arquivo);
		
	} else { /*Caso de arquivo nulo/vazio*/
		arquivo = fopen (nome, "w");
		}
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
		/*Aqui deve-se atentar para o fato de que o cursor pode estar antes ou depois do marcador. Cada caso desses deve ser tratado separadamente*/
		if (editor->marcador > editor->proximo) {
			for(k = editor->marcador; k >= editor->proximo; k--)
				*(editor->copia++) = *k;
		}
		else if (editor->marcador < editor->proximo) {
			for(k = editor->proximo; k >= editor->marcador; k--)
				*(editor->copia++) = *k;
		}
	}
}

void InsereTexto (editorTAD editor) {
	if (editor->copia > editor->aux)
		while (editor->copia > editor->aux)
			InsereCaractere (editor, *(--editor->copia));
	editor->marcador = (char *) -1;
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

arvoreTAD ArvoreBinaria (void){
	return NULL;
}
void CarregaDicionario (arvoreTAD a, char *nome){}
void RecortaTexto (editorTAD editor) {
	char *k; int i, ds;
	if (editor->marcador != (char *) -1) {
		editor->copia = editor->aux;
		/*Aqui deve-se atentar para o fato de que o cursor pode estar antes ou depois do marcador. Cada caso desses deve ser tratado separadamente*/
		if (editor->marcador > editor->proximo) {
			ds = (editor->marcador - editor->proximo) + 1;
			for(k = editor->marcador; k >= editor->proximo; k--)
				*(editor->copia++) = *k;
			for(i = 0; i < ds; i++)
				RemoveCaractereAtual(editor);
		}
		else if (editor->marcador < editor->proximo) {
			ds = (editor->marcador - editor->proximo);
			for(k = editor->proximo; k >= editor->marcador; k--)
				*(editor->copia++) = *k;
			for(i = 0; i < ds; i++)
				RemoveCaractereAnterior(editor);
			RemoveCaractereAtual(editor);
		}
	}
}void Busca (editorTAD e, char *str){}
void Substitui (editorTAD e, char *str1, char *str2){}
void Ortografia (editorTAD e, arvoreTAD a, char *palavra){}



