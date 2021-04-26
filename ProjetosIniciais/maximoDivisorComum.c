
#include <stdio.h>

int mdc(int a, int b)
{
	if(b > a)
	{
		int aux = a;
		a = b;
		b = aux;
		return mdc(a, b);
	}

	else
	{
		if(a % b != 0)
		{
			return mdc(b, a % b);
		}

		else
		{
			return b;
		}
	}
}

int main()
{
	int primeiroNum, segundoNum;

	printf("Digite dois numeros inteiros: ");
	scanf("%d", &primeiroNum);
	scanf("%d", &segundoNum);

	printf("Resultado: %d", mdc(primeiroNum, segundoNum) );
}