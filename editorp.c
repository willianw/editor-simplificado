#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "editor.h"

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
	FILE *arquivo = fopen (nome, "r");
	if (arquivo != NULL){
		c = getc(arquivo);
		while(c != EOF){
			if (e->cursor < e->proximo)
				/*Grava o caractere lido e avança o cursor*/
				*(e->cursor++) = c;
			else{
				printf("Editor cheio!\n"); break;}
			c = getc(arquivo);
		}
		/*Deslocamento dos caracteres para o fim do vetor*/
		for(k = e->inicio; k < e->cursor; k++){
			*(k + (e->fim - e->cursor) + 1) = *k;
		}
		/*Deslocamento do ponteiro 'proximo' para o primeiro caractere deslocado*/
		e->proximo = e->inicio + (e->fim - e->cursor);
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


int main (void)
{
  editorTAD editor;
  char nome[256];
  int c;

  printf ("Digite um nome de arquivo para carregar ou criar: ");
  fgets (nome, 256, stdin);      nome[strlen (nome) - 1] = '\0';
  editor = Editor ();
  CarregaTexto (editor, nome);

  printf (":");
  while ((c = getchar ())) 
    switch (c) {
    case 't': ExibeEditor (editor); printf ("\n"); break;
    case 'i': 
      while (1) {
		c = getchar ();
		if (c == EOF || c == 3 || c == 4) break;
		else if (c == '^') {
		  printf ("\n");
		  c = '\n';
		  break;
		} else InsereCaractere (editor, c);
      }
      break;
    case 'n': InsereCaractere (editor, '\n');   break;
    case 'r': RemoveCaractereAtual (editor);    break;
    case 'b': RemoveCaractereAnterior (editor); break;
    case 'e': RetrocedeCursor (editor);         break;
    case 'd': AvancaCursor (editor);            break;
    case 'm': MarcaPosicao (editor);            break;
    case 'c': CopiaTexto (editor);              break;
    case 'v': InsereTexto (editor);             break;
    case 's': SalvaTexto (editor, nome);        return 1;
    case EOF: case 3: case 4: return 1;
    case '\n': case '\r': printf (":"); break;
    }        
  return 0;
}
