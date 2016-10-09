#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "editor.h"

#define MAX_LINHA 10010

letra novaLetra(char c){
	letra l = (letra) malloc (sizeof ( (letra) NULL));
	l->v = c;
	l->next = NULL;
	return l;
}

struct editorTCD{
	letra inicio, cursor, marcador, anterior;
};

struct letra_struct{
	char v;
	struct letra_struct *next;
};

typedef struct *letra_struct letra;

editorTAD Editor (){
	editorTAD editor = (editorTAD) malloc(sizeof((editorTAD) NULL));
	editor->inicio = novaLetra(NULL);
	editor->cursor = novaLetra('^');
	editor->inicio->next = editor->cursor;
	editor->marcador = (letra) -1;
	return editor;
}

void CarregaTexto (editorTAD e, char *nome) {
	/*Caracteres de iteração*/
	char c, *k;
	FILE *arquivo = fopen (nome, "r");
	if (arquivo != NULL){
		c = getc(arquivo);printf("%x\n ", (unsigned int) c);
		while(c != EOF && c != 3 && c != 4){
			/*Grava o caractere lido*/
			InsereFim(e, c);printf("%2x(%c) \n", (unsigned int) c, c);
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


int main (void)
{
  editorTAD editor;
  char nome[256];
  int c;

  printf ("Digite um nome de arquivo para carregar ou criar: ");
  fgets (nome, 256, stdin);      nome[strlen (nome) - 1] = '\0';
  printf("a instanciar editor\n");
  editor = Editor ();
  printf("instanciou editor\n");
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

void InsereFim(editorTAD editor, char c){
	letra l = novaLetra(c);
	l->next = editor->cursor->next;
	editor->cursor->next = l;
}
