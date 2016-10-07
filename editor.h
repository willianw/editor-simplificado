#ifndef _EDITOR_H
#define _EDITOR_H
/* Tipo Abstrato de Dados Editor */
typedef struct editorTCD *editorTAD;
/* Aloca memoria e retorna um editor vazio */
editorTAD Editor (void);
/* Carrega conteudo do editor de arquivo */
void CarregaTexto (editorTAD e, char *nome);
/* Move cursor para frente/tras uma posicao; nao tem efeito se posicao resultante for invalida */
void AvancaCursor (editorTAD e);
void RetrocedeCursor (editorTAD e);
/* Insere caractere na posicao do cursor */
void InsereCaractere (editorTAD e, char c);
/* Apaga caracartere na posição (anterior) do cursor */
void RemoveCaractereAtual (editorTAD e);
void RemoveCaractereAnterior (editorTAD e);
/* Marca/memoriza posição atual */
void MarcaPosicao (editorTAD e);
/* Copia texto entre posicao marcada e cursor (inclusive) */
void CopiaTexto (editorTAD e);
/* Insere texto em memoria auxiliar na posicao atual */
void InsereTexto (editorTAD e);
/* Exibe editor na tela */
void ExibeEditor (editorTAD e);
/* Salva conteudo do editor em arquivo */
void SalvaTexto (editorTAD e, char *nome);
#endif
