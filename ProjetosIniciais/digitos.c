
#include <stdio.h>

int Digitos(int N)
{
  int cont = 1;

  if(N >= 10)
  {
    cont += Digitos(N / 10);
  }

  return cont;
}

int main()
{
	int numeroDigitado;

	printf("Digite um numero inteiro: ");
	scanf("%d", &numeroDigitado);

	printf("Resultado: %d", Digitos(numeroDigitado));
}