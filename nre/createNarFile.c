#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PROXIMA_POSICAO_SEM_HEADER (int)buffer2[i + 1] + 3

void WriteBinFile(void)
{
  FILE *ptr;
  unsigned char a[259] = {42, 0, 0, 32, 41, 96, 48, 47, 16, 42, 32, 40, 48, 42, 16, 40, 32, 43, 48, 38, 16, 43, 32, 40, 160, 37, 144, 27, 128, 7, 48, 41, 16, 40, 32, 43, 48, 39, 16, 43, 240, 1, 255, 32, 5, 0, 0};

  ptr = fopen("test.nar", "wb");
  fwrite(a, sizeof(unsigned char), 259, ptr);
  fclose(ptr);
}

int main(int argc, char *argv[])
{
  WriteBinFile();
  return 0;
}