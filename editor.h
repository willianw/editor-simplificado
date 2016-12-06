#ifndef _EDITOR_H
#define _EDITOR_H

/* Tipo Abstrato de Dados Editor */
typedef struct editorTCD *editorTAD;

/* Tipo Abstrato de Dados Árvore de Busca Binária */
typedef struct arvoreTCD *arvoreTAD;

/* Aloca memoria e retorna um editor vazio */
editorTAD Editor (void);
/* Carrega conteudo do editor de arquivo */
void CarregaTexto (editorTAD e, char *nome);

/* Aloca memoria e retorna uma árvore de busca binária vazia */
arvoreTAD ArvoreBinaria (void);
/* Carrega dicionário (lista de palavras aceitas) em uma árvore de busca binária */
void CarregaDicionario (arvoreTAD a, char *nome);
/* Recorta texto entre posicao marcada e cursor (inclusive) */
void RecortaTexto (editorTAD e);
/* Busca próxima ocorrência de str no texto e atualize cursores. */
void Busca (editorTAD e, char *str);
/* Substitui próxima ocorrência de str1 por str2 e atualiza cursores. */
void Substitui (editorTAD e, char *str1, char *str2);
/* Verifica ortografia. Coloca a próxima palavra não aceita pelo dicionário (palavra é NULL se todas as palavras forem aceitas */
void Ortografia (editorTAD e, arvoreTAD a, char *palavra);

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

