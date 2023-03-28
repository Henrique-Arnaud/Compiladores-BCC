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
  Indeterminado
} Token;

typedef struct
{
  char token;
  char *valor;
} TokenList;

TokenList criarToken(char token, char *valor)
{
  TokenList lista;
  lista.token = token;
  lista.valor = malloc(strlen(valor) * sizeof(char));
  lista.valor = valor;

  return lista;
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

  buffer = (char *)malloc(sizeof(char) * (tamanhoArquivo + 1));

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

  int i, j, tamanho = 0;
  TokenList *lista;
  static char *enumTokenStrings[] = {"Mais", "Menos", "Multiplicacao", "Divisao", "Indeterminado"};

  for (i = 0; i < (int)strlen(textoArquivo); i++)
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

  for (i = 0, j = 0; i < (int)strlen(textoArquivo); i++)
  {
    switch (textoArquivo[i])
    {
    case '+':
      lista[j] = criarToken(textoArquivo[i], enumTokenStrings[Mais]);
      break;
    case '-':
      lista[j] = criarToken(textoArquivo[i], enumTokenStrings[Menos]);
      break;
    case '*':
      lista[j] = criarToken(textoArquivo[i], enumTokenStrings[Multiplicacao]);
      break;
    case '/':
      lista[j] = criarToken(textoArquivo[i], enumTokenStrings[Divisao]);
      break;
    default:
      if (!isspace(textoArquivo[i]))
      {
        lista[j] = criarToken(textoArquivo[i], enumTokenStrings[Indeterminado]);
      }
      break;
    }
    if (!isspace(textoArquivo[i]))
    {
      j++;
    }
  }
  printf("TOKENS: [");
  for (i = 0; i < tamanho; i++)
  {
    printf("\n\t%s(\n\t\t'%c',\n\t),", lista[i].valor, lista[i].token);
  }
  printf("\n]\n");

  free(textoArquivo);
  free(lista);
  return 0;
}
