
#include <stdio.h>

void dec2bin(int dec)
{
	if(dec/2 > 0)
	{
		dec2bin(dec/2);
	}
	printf("%d", dec % 2);
}

int main()
{
	int numeroDigitado;

	printf("Digite um numero inteiro: ");
	scanf("%d", &numeroDigitado);

	printf("Resultado: ");
	dec2bin(numeroDigitado);
}