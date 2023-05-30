#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "numero_verificador.c"

typedef enum
{
  Mais,
  Menos,
  Multiplicacao,
  Divisao,
  Exponenciacao,
  Numero,
  Indeterminado
} Token;

// static char *enumTokenStrings[] = {"Mais", "Menos", "Multiplicacao", "Divisao", "Exponenciacao", "Número", "Indeterminado"};

struct No
{
  void *valor;
  char *tipo;
  Token token;
  struct No *proximo;
};

void inserir_lista(struct No **cabeca, void *valor, Token token, size_t tamanho)
{
  struct No *novo_no = (struct No *)malloc(sizeof(struct No));
  novo_no->token = token;
  novo_no->proximo = *cabeca;

  if (valor == NULL)
  {
    novo_no->valor = NULL;
  }
  else if (token == Numero)
  {
    novo_no->valor = malloc(sizeof(float));
    memcpy(novo_no->valor, valor, sizeof(float));

    char *tipo = "float";

    novo_no->tipo = malloc(sizeof(tipo));
    memcpy(novo_no->tipo, tipo, 5);
  }
  else
  {
    novo_no->valor = (char *)malloc(tamanho + 1);
    memcpy(novo_no->valor, valor, tamanho);
    ((char *)novo_no->valor)[tamanho] = '\0';

    char *tipo = "string";

    novo_no->tipo = malloc(sizeof(tipo) + 1);
    memcpy(novo_no->tipo, tipo, 6);
  }

  *cabeca = novo_no;
}

void expressao(struct No *cabeca, float *resultado)
{
  struct No *atual = cabeca;
  while (atual != NULL)
  {
    *resultado = 0;
    if (atual->token == Numero)
      printf("-----(%.2f)\n", *(float *)atual->valor);
    atual = atual->proximo;
  }
}

void exibir_lista(struct No *cabeca)
{
  float resultado;
  expressao(cabeca, &resultado);

  //printf("TOKENS: [");
  //printf("\n\t%s(\n\t\t%.2f - %s,\n\t),", enumTokenStrings[atual->token], *(float *)atual->valor, atual->tipo);
  //printf("\n\t%s(\n\t\t'%s' - %s,\n\t),", enumTokenStrings[atual->token], (char *)atual->valor, atual->tipo);
  //printf("\n]\n");
}

void limpar_lista(struct No *inicio)
{
  struct No *atual = inicio;
  while (atual != NULL)
  {
    struct No *prox = atual->proximo;
    free(atual->valor);
    free(atual->tipo);
    free(atual);
    atual = prox;
  }
}

int identifica_numero(char *texto, float *numero, int *tamanho)
{
  if (is_number(texto, numero, tamanho))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void identificador(char *texto, struct No **cabeca)
{
  if (*texto == '\0')
  {
    return;
  }
  int espacoCaracter = 1;
  int tamanhoNumero = 0;
  float numero = 0;

  printf("(%s)\n", texto);
  if (identifica_numero(texto, &numero, &tamanhoNumero))
  {
    inserir_lista(cabeca, (void *)&numero, Numero, tamanhoNumero);
    identificador(texto + tamanhoNumero, cabeca);
    return;
  }
  switch (*texto)
  {
  case '+':
    inserir_lista(cabeca, texto, Mais, sizeof(*texto));
    break;
  case '-':
    inserir_lista(cabeca, texto, Menos, sizeof(*texto));
    break;
  case '*':
    if (*(texto + 1) == '*')
    {
      inserir_lista(cabeca, texto, Exponenciacao, sizeof(*texto) + 1);
      espacoCaracter = 2;
    }
    else
    {
      inserir_lista(cabeca, texto, Multiplicacao, sizeof(*texto));
    }
    break;
  case '/':
    inserir_lista(cabeca, texto, Divisao, sizeof(*texto));
    break;
  }
  identificador(texto + espacoCaracter, cabeca);
}

char *lerArquivo(char *nomeArquivo)
{

  FILE *arquivo;
  int tamanhoArquivo, tamanhoTexto;
  char *buffer = NULL;
  arquivo = fopen(nomeArquivo, "r");

  if (arquivo == NULL)
  {
    printf("Arquivo inválido");
    return 0;
  }

  fseek(arquivo, 0, SEEK_END);
  tamanhoArquivo = ftell(arquivo);
  rewind(arquivo);

  buffer = (char *)malloc(sizeof(char) * (tamanhoArquivo + 1) + 1);

  tamanhoTexto = fread(buffer, sizeof(char), tamanhoArquivo, arquivo);

  buffer[tamanhoArquivo] = '\0';

  if (tamanhoArquivo != tamanhoTexto)
  {
    free(buffer);
    buffer = NULL;
  }

  fclose(arquivo);

  return buffer;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Nenhum arquivo foi passado como parâmetro");
    return 1;
  }

  char *textoArquivo = NULL;
  textoArquivo = lerArquivo(argv[1]);

  struct No *cabeca = NULL;

  identificador(textoArquivo, &cabeca);
  exibir_lista(cabeca);

  limpar_lista(cabeca);
  free(textoArquivo);
  return 0;
}
