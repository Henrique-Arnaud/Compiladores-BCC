#include "numero_verificador.h"

int is_number(char *texto, float *resultado, int *tamanho)
{
  int i = 0;
  float num = 0;
  float sinal = 1.0;
  float div = 10.0;
  int contagem_decimal = 0;
  if (texto[0] == '-')
  {
    sinal = -1.0;
    i = 1;
  }
  else if (texto[0] == '+')
  {
    i = 1;
  }
  for (; texto[i] != '\0'; i++)
  {
    if (texto[i] >= '0' && texto[i] <= '9')
    {
      if (contagem_decimal == 0)
      {
        num = num * 10.0 + (float)(texto[i] - '0');
      }
      else
      {
        num = num + ((float)(texto[i] - '0') / div);
        div *= 10.0;
      }
    }
    else if (texto[i] == '.')
    {
      contagem_decimal++;
    }
    else
    {
      return 0;
    }
  }
  if (contagem_decimal == 0)
  {
    *resultado = sinal * num;
  }
  else
  {
    *resultado = sinal * num;
  }
  *tamanho = i;
  return 1;
}
