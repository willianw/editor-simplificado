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
