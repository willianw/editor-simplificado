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
	letra inicio, cursor, marcador, anterior, fim, copia_comeco, copia_fim;
	letra marcador_n, marcador_a;
};

editorTAD Editor (){
	editorTAD editor = (editorTAD) malloc(sizeof((editorTAD) NULL));
	editor->inicio = novaLetra(0);
	editor->cursor = novaLetra('^');
	editor->fim = novaLetra(0);
	editor->inicio->next = editor->cursor;
	editor->anterior = editor->inicio;
	editor->marcador = (letra) -1;
	editor->cursor->next = editor->fim;
	return editor;
}

letra novaLetra(char c){
	letra l = (letra) malloc (sizeof ( (letra) NULL));
	l->v = c;
	l->next = NULL;
	return l;
}

letra lookPrevious(editorTAD editor, letra l){
	letra k = editor->inicio;
	while (k->next != l && k->next != NULL)
		k = k->next;
	if (k->next == NULL)
		return NULL;
	else
		return k;
}

void CarregaTexto (editorTAD e, char *nome) {
	/*Caracteres de iteração*/
	char c, *k;
	letra l;
	FILE *arquivo = fopen (nome, "r");
	if (arquivo != NULL){
		c = getc(arquivo);
		while(c != EOF && c != 3 && c != 4){
			//printf("%x (%c)\n", (unsigned int) c, c);
			/*Grava o caractere lido*/
			l = novaLetra(c);
			l->next = (e->cursor);
			(e->anterior)->next = l;
			e->anterior = l;
			//printf("%2x(%c) \n", (unsigned int) c, c);
			c = getc(arquivo);
		}
	} else printf("Arquivo vazio!\n");
	fclose(arquivo);
}

void ExibeEditor(editorTAD e){
	letra l;
	/*Exibe a parte antes do cursor*/
	for(l = e->inicio->next; l->next != NULL; l = l->next)
		printf("%c", l->v);
	//if (l = e->cursor)
		//printf("%c", l->v);
}

void InsereCaractere (editorTAD editor, char caractere) {
	letra l = novaLetra(caractere);
	l->next = editor->cursor;
	editor->anterior->next = l;
	editor->anterior = l;
}

void RemoveCaractereAtual (editorTAD editor) {
	letra atual = editor->cursor->next;;
	if (atual != editor->fim){
		editor->cursor->next = atual->next;
		free(atual);
	}
}

void RemoveCaractereAnterior (editorTAD editor) {
	letra k = lookPrevious(editor, editor->anterior);
	if (editor->anterior != editor->inicio){
		k->next = editor->cursor;
		free(editor->anterior);
		editor->anterior = k;
	}
}

void RetrocedeCursor (editorTAD editor) {
	letra Anterior = lookPrevious(editor, editor->anterior);
	if (editor->anterior != editor->inicio){
		editor->anterior->next = editor->cursor->next;
		editor->cursor->next = editor->anterior;
		Anterior->next = editor->cursor;
		editor->anterior = Anterior;
	}
}

void AvancaCursor (editorTAD editor) {
	letra Proximo = editor->cursor->next->next;
	if (editor->cursor->next != editor->fim){
		editor->anterior->next = editor->cursor->next;
		editor->anterior = editor->anterior->next;
		editor->cursor->next->next = editor->cursor;
		editor->cursor->next = Proximo;
	}
}

void MarcaPosicao (editorTAD editor) {
	editor->marcador = editor->cursor;
	editor->marcador_a = editor->anterior;
	editor->marcador_n = editor->cursor->next;
}

void CopiaTexto (editorTAD editor) {
	letra i = editor->marcador_n;
	letra l, primeiro, segundo;
	while(i != editor->cursor && i != editor->fim)
		i = i->next;
	if  (i == editor->cursor){	/*marcador antes de cursor*/
		primeiro = editor->marcador_n;
		segundo = editor->cursor;
	} else{						/*cursor antes de marcador*/
		primeiro = editor->cursor->next;
		segundo = editor->marcador_n;
	}
	l = novaLetra(primeiro->v);
	editor->copia_comeco = l;
	editor->copia_fim = editor->copia_comeco;
	for (i = primeiro->next; i != segundo; i = i->next){
		l = novaLetra(i->v);
		editor->copia_fim->next = l;
		editor->copia_fim = l;
	}
	for(i = editor->copia_comeco; i != editor->copia_fim; i = i->next)
		printf("%c", i->v);
	printf("\n");
}

void InsereTexto (editorTAD editor) {
	editor->anterior->next = editor->copia_comeco;
	editor->copia_fim->next = editor->cursor;
	editor->anterior = editor->copia_fim;
}

void SalvaTexto (editorTAD editor, char *nome) {
	
}
