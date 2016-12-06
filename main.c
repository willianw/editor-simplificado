#include <stdio.h>
#include <string.h>
#include "editor.h"

int main (void)
{
  editorTAD editor;
  arvoreTAD dicionario;
  char nome[256], palavra[256], palavra2[256];
  int c, i;

  printf ("Digite um nome de arquivo para carregar ou criar: ");
  fgets (nome, 256, stdin);      nome[strlen (nome) - 1] = '\0';

  editor = Editor ();
  CarregaTexto (editor, nome);
  dicionario = ArvoreBinaria ();
  CarregaDicionario (dicionario, "dicio.txt");

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
    case 'R': RecortaTexto (editor);            break;
    case 'B': 
      i = 0;
      while (1) {
        c = getchar();
        if (c == EOF || c == 3 || c == 4 || c == '.' || i == 255) {
          palavra[i] = '\0'; break;
        } else palavra[i] = c;
        i++;
      }
      Busca (editor, palavra);              break;
    case 'S':
      i = 0;
      while (1) {
        c = getchar();
        if (c == EOF || c == 3 || c == 4 || c == ' ' || i == 255) {
          palavra[i] = '\0'; break;
        } else palavra[i] = c;
        i++;
      }
      i = 0;
      while (1) {
        c = getchar();
        if (c == EOF || c == 3 || c == 4 || c == '.' || i == 255) {
          palavra2[i] = '\0'; break;
        } else palavra2[i] = c;
        i++;
      }
      Substitui (editor, palavra, palavra2); break;
    case 'O': 
        Ortografia (editor, dicionario, palavra);       
        if (palavra != NULL && palavra[0] != '\0') {
            printf("Palavra incorreta: %s\n\n", palavra);
            ExibeEditor (editor);
        }
        break;
    case 's': SalvaTexto (editor, nome);        return 1;
    case EOF: case 3: case 4: return 1;
    case '\n': case '\r': printf (":"); break;
    }        
  return 0;
}
