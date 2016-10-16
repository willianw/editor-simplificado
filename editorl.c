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
	/*Limites da lista ligada. Ambos são apenas 'headers': não contém texto*/
	letra inicio, fim;
	/*Letra com o caractere '^'. Fica inserido entre os caracteres do texto*/
	letra cursor;
	/*Aponta para o próximo caractere do cursor (cursor->next) quando 'm' é pressionado*/
	letra marcador;
	/*Aponta para a letra imediatamente antes do cursor*/
	letra anterior;
	/*Apontam para os limites do texto (inclusive) das letras a serem copiadas
	OBS.: por algum motivo desconhecido, inicio->next aponta para copia->comeco.
	Isso atrapalha a operação de cópia.
	Não consegui identificar porque isso ocorre*/
	copia_comeco, copia_fim;
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
	editor->copia_comeco = editor->copia_fim = NULL;
	return editor;
}

/*Criação de um novo objeto do tipo 'letra'*/
letra novaLetra(char c){
	letra l = (letra) malloc (sizeof ( (letra) NULL));
	l->v = c;
	l->next = NULL;
	return l;
}

/*Detecta a letra anterior ao argumento. Caso a letra não tenha antecessor, retorna NULL*/
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
	/*Letra iterativa*/
	letra l;
	FILE *arquivo = fopen (nome, "r");
	if (arquivo != NULL){ /*Arquivo não-vazio*/
		c = getc(arquivo);
		while(c != EOF && c != 3 && c != 4){
			/*Adiciona o caractere à lista ligada*/
			l = novaLetra(c);
			l->next = (e->cursor);
			(e->anterior)->next = l;
			e->anterior = l;
			c = getc(arquivo);
		}
	} else { /*Arquivo vazio*/
		arquivo = fopen (nome, "w");
	}
	fclose(arquivo);
}

void ExibeEditor(editorTAD e){
	letra l;
	for(l = e->inicio->next; l->next != NULL; l = l->next)
		printf("%c", l->v);
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
	printf("%ld %ld \n", (long)editor->inicio->next, (long)editor->copia_comeco);
	if (editor->anterior != editor->inicio){
		editor->anterior->next = editor->cursor->next;
		editor->cursor->next = editor->anterior;
		Anterior->next = editor->cursor;
		editor->anterior = Anterior;
	}
	printf("%ld %ld \n", (long)editor->inicio->next, (long)editor->copia_comeco);
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
	printf("%ld %ld \n", (long)editor->inicio->next, (long)editor->copia_comeco);
	if (editor->marcador == (letra) -1)
		editor->marcador = editor->cursor->next;
	printf("%ld %ld \n", (long)editor->inicio->next, (long)editor->copia_comeco);
}

void CopiaTexto (editorTAD editor) {
	letra i, l, primeiro_i, segundo_e;
	for(i = editor->inicio; ; i = i->next)
		if (i == NULL || i == editor->marcador || i == editor->cursor)
			break;
	/*printf("%ld %ld \n", (long)editor->inicio->next, (long)editor->copia_comeco);*/
	/*A partir desse bloco, o editor->inicio->next é alterado*/
	if (i == editor->cursor){	/*Cursor antes de marcador*/
		editor->copia_comeco = editor->cursor->next;
		editor->copia_fim = editor->marcador;
	} else{						/*Marcador antes de cursor*/
		editor->copia_comeco = editor->marcador;
		editor->copia_fim = editor->cursor;
	}
}

void InsereTexto (editorTAD editor) {
	letra i;
	for (i = editor->copia_comeco; i != editor->copia_fim; i = i->next)
		InsereCaractere(editor, i->v);
}

void SalvaTexto (editorTAD editor, char *nome) {
	letra i;
	FILE *arquivo = fopen (nome, "w");
	for (i = editor->inicio; i != editor->fim; i = i->next)
		if (i != editor->cursor)
			putc(i->v, arquivo);
	fclose(arquivo);	
}
