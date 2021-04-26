
#include <stdio.h>

int mult(int base, int exp)
{
	if(exp > 1)
	{
		base *= mult(base, exp - 1);
	}

	else if(exp == 0)
	{
		return 1;
	}

	return base;
}

int main()
{
	int base, expoente;

	printf("Digite a base e o expoente inteiros: ");
	scanf("%d", &base);
	scanf("%d", &expoente);

	printf("Resultado: %d", mult(base, expoente) );
}