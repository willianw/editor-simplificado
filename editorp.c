#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "editor.h"

#define MAX_LINHA 10010
struct editorTCD{
	char linha[MAX_LINHA];
	char *inicio, *fim, *cursor, *proximo;
	char cs; 
};

editorTAD Editor (){
	editorTAD editor = (editorTAD) malloc(sizeof((editorTAD) NULL));
	editor -> inicio = editor -> linha;
	editor -> fim = ( editor -> linha ) + MAX_LINHA - 1;
	editor -> cursor = editor -> inicio;
	editor -> proximo = editor -> fim;
	editor -> cs = '^';
	return editor;
}

void CarregaTexto (editorTAD e, char *nome) {
	char c, *k;
	FILE *arquivo = fopen (nome, "r");
	if (arquivo != NULL){
		char c = getc(arquivo);
		while(c != EOF){
			printf("%c", c);
			if (e->cursor < e->proximo)
				*(e->cursor++) = c;
			else{
				printf("Editor cheio!\n"); break;
			}
			c = getc(arquivo);
		}
		printf("\n");
		for(k = e->cursor; k >= e->inicio; k--){
			printf("%c", *k);
			*(e->fim - (k - e->cursor)) = *k;
		}
		printf("\n");
	} else printf("Arquivo vazio!\n");
	fclose(arquivo);
}

void ExibeEditor(editorTAD e){
	char *c;
	for(c = e->inicio; c < e-> cursor; c++)
		printf("%c", *c);
	printf("%c", (e->cs));
	for(c = e->proximo; c < e-> fim; c++)
		printf("%c", *c);
}

void InsereCaractere (editorTAD editor, char caractere) {}
void RemoveCaractereAtual (editorTAD editor) {}
void RemoveCaractereAnterior (editorTAD editor) {}
void RetrocedeCursor (editorTAD editor) {}
void AvancaCursor (editorTAD editor) {}
void MarcaPosicao (editorTAD editor) {}
void CopiaTexto (editorTAD editor) {}
void InsereTexto (editorTAD editor) {}
void SalvaTexto (editorTAD editor, char *nome) {}

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
