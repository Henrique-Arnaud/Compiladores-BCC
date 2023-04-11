#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
  Mais,
  Menos,
  Multiplicacao,
  Divisao,
  Exponenciacao,
  Indeterminado
} Token;

static char *enumTokenStrings[] = {"Mais", "Menos", "Multiplicacao", "Divisao", "Exponenciacao", "Indeterminado"};
static char *enumToken[] = {"+", "-", "*", "/", "**", ""};

typedef struct
{
  char *token;
  char *valor;
} TokenList;

TokenList criarToken(Token token)
{
  TokenList lista;
  lista.token = malloc(strlen(enumToken[token]) * sizeof(char));
  lista.token = enumToken[token];

  lista.valor = malloc(strlen(enumTokenStrings[token]) * sizeof(char));
  lista.valor = enumTokenStrings[token];

  return lista;
}

void identificador(char *texto, TokenList *lista, int *index)
{
  if (*texto == '\0')
  {
    return;
  }
  int espacoCaracter = 1;
  switch (*texto)
  {
  case '+':
    lista[*index] = criarToken(Mais);
    break;
  case '-':
    lista[*index] = criarToken(Menos);
    break;
  case '*':
    if (*(texto + 1) == '*')
    {
      lista[*index] = criarToken(Exponenciacao);
      espacoCaracter = 2;
    }
    else
    {
      lista[*index] = criarToken(Multiplicacao);
    }
    break;
  case '/':
    lista[*index] = criarToken(Divisao);
    break;
  default:
    if (!isspace(*texto))
    {
      lista[*index] = criarToken(Indeterminado);
    }
    break;
  }
  if (!isspace(*texto))
  {
    (*index)++;
  }
  identificador(texto + espacoCaracter, lista, index);
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
  int index = 0;
  int tamanho = 0;
  TokenList *lista;

  for (int i = 0; i < (int)strlen(textoArquivo); i++)
  {
    if (!isspace(textoArquivo[i]))
    {
      tamanho++;
    }
  }

  if (tamanho == 0)
  {
    printf("Nenhum token foi inserido");
    return 0;
  }

  lista = malloc(tamanho * sizeof *lista);

  identificador(textoArquivo, lista, &index);

  printf("TOKENS: [");
  for (int i = 0; i < tamanho && lista[i].valor != NULL; i++)
  {
    printf("\n\t%s(\n\t\t'%s',\n\t),", lista[i].valor, lista[i].token);
  }
  printf("\n]\n");

  free(lista);
  free(textoArquivo);
  return 0;
}
