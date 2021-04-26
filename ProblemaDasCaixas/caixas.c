
/*-------------------------------------------------------------------------------------
Programa 1 - Laboratório de AEDS
Aluno: Ronaldo Mendonça Zica
-------------------------------------------------------------------------------------*/

#define TAMANHO_MAX_NOME_ARQUIVO 100
#define TAMANHO_MAX_NUMERO 30
#define NUMERO_MAX_CHAR_FILEIRAS 3
#define NUMERO_MAX_FILEIRAS 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	// Declaração de variáveis

	FILE *arquivo;
	char nomeArquivo [TAMANHO_MAX_NOME_ARQUIVO], numeroFileirasAux [NUMERO_MAX_CHAR_FILEIRAS], valorCaixaAux [TAMANHO_MAX_NUMERO];
	char charAux = '-';
	int numeroFileiras, posicaoAux = 0, contadorFileiras, contadorCaixas, maiorValor = 0, posicaoValorCaixas = 0, somaTotalAtual;
	int fileiraAtual, caixaAtual, melhorCaixa = 0, melhorFileira = 0;

	//-------------------------------------------------------------------------------------
	// Abertura do arquivo + teste da abertura

	printf("Digite o nome do arquivo de entrada: ");
	scanf("%s", nomeArquivo);

	arquivo = fopen(nomeArquivo, "rb");

	if(arquivo == 0)										// teste para debug
	{
		//printf("ERRO: O arquivo não pôde ser aberto.\n");
		return 0;
	}

	//-------------------------------------------------------------------------------------
	// Processamento de dados do arquivo: Primeiro número - quantidade de fileiras
	// Deve ser diferente de EOF, maior que 0 e menor que 21

	while(charAux != '\n')
	{
		charAux = fgetc(arquivo);
		numeroFileirasAux [posicaoAux] = charAux;
		posicaoAux ++;

		if(charAux == EOF)
		{
			//printf("ERRO: O arquivo aberto não possui nada escrito nele.\n");
			return 0;
		}
	}

	numeroFileiras = atoi(numeroFileirasAux);

	if( (numeroFileiras <= 0) || (numeroFileiras > 20) )
	{
		//printf("ERRO: O número de fileiras informado no arquivo (%d) é inválido.\n", numeroFileiras);
		return 0;
	}

	//-------------------------------------------------------------------------------------
	// Armazenamento dos dados do arquivo em um vetor para fácil manipulação

	int valorCaixas[numeroFileiras][NUMERO_MAX_FILEIRAS];

	for(contadorFileiras = 1; contadorFileiras <= numeroFileiras; contadorFileiras ++)	// percorre todas as fileiras
	{
		posicaoValorCaixas = 0;

		for(contadorCaixas = 1; contadorCaixas <= contadorFileiras; contadorCaixas ++)
		{
			posicaoAux = 0;
			charAux = fgetc(arquivo);

			while( (charAux != '\n') && (charAux != ' ') && (charAux != EOF) )
			{
				valorCaixaAux [posicaoAux] = charAux;
				posicaoAux ++;
				charAux = fgetc(arquivo);
			}

			valorCaixas[contadorFileiras - 1][posicaoValorCaixas]	= atoi(valorCaixaAux);
			posicaoValorCaixas ++;

			for(posicaoAux = 0; posicaoAux < TAMANHO_MAX_NUMERO; posicaoAux ++)
			{
				valorCaixaAux[posicaoAux] = ' ';
			}	
		}
	}

	//-------------------------------------------------------------------------------------
	// Imprime para Debug o vetor com o valor de cada uma das caixas
	
	/*
	for(int cont1 = 1; cont1 <= numeroFileiras; cont1 ++)
	{
		printf("Fileira %d:\n", cont1);

		for(int cont2 = 1; cont2 <= cont1; cont2 ++)
		{
			printf("%d ", valorCaixas[cont1 - 1][cont2 - 1]);
		}

		printf("\n");
	}
	*/

	//-------------------------------------------------------------------------------------
	// Processamento de dados do vetor: encontra o valor para cada caixa

	posicaoValorCaixas = 0;

	for(contadorFileiras = 1; contadorFileiras <= numeroFileiras; contadorFileiras ++)	// percorre todas as fileiras
	{
		for(contadorCaixas = 1; contadorCaixas <= contadorFileiras; contadorCaixas ++)
		{
			somaTotalAtual = valorCaixas[contadorFileiras - 1][contadorCaixas - 1];
			//printf("valor inicial da soma: %d\n", somaTotalAtual);

			for(fileiraAtual = contadorFileiras - 1; fileiraAtual >= 0; fileiraAtual --)
			{
				for(caixaAtual = 0; caixaAtual < fileiraAtual; caixaAtual ++)
				{
					//printf("%d += %d\n", somaTotalAtual, valorCaixas[fileiraAtual - 1][caixaAtual]);
					somaTotalAtual += valorCaixas[fileiraAtual - 1][caixaAtual];
				}
			}

			if(somaTotalAtual > maiorValor)
			{
				melhorCaixa = contadorCaixas - 1;
				melhorFileira = contadorFileiras - 1;
				maiorValor = somaTotalAtual;
			}

			posicaoValorCaixas ++;

			//printf("Soma total atual: %d.\n", somaTotalAtual);
			//printf("Melhor caixa até então: %d, fileira %d.\n", melhorCaixa + 1, melhorFileira + 1);
		}
	}

	//-------------------------------------------------------------------------------------
	// Imprime a mensagem de saída

	printf("Resposta: fileira %d, caixa %d.", melhorFileira + 1, melhorCaixa + 1);

	//-------------------------------------------------------------------------------------
	// Fechamento do arquivo

	fclose(arquivo);
}