
/*-------------------------------------------------------------------------------------
Programa 3 - Laboratório de Algoritmos e Estruturas de Dados 1 - LAEDS

Aluno: Ronaldo Mendonça Zica
Matrícula: 20193018768

Aluno:
Matrícula:

Data de início: 09/02/2021
Data de envio: 

Professora: Natalia Cosse Batista

-------------------------------------------------------------------------------------*/


//-------------------------------------------------------------------------------------
// Defines:

#define TAMANHO_MAX_NOME_ARQUIVO 100
#define TAMANHO_MAX_FRASE 1000
#define QUANTIDADE_MAX_ITENS 100

//-------------------------------------------------------------------------------------
// Includes:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------------------------------------------
// Criando o tipo de variável "mensagem":

typedef enum 
{
   otima, viavel, inviavel
} mensagem;

//-------------------------------------------------------------------------------------
// Função imprime mensagem:
// Parâmetro:	mensagem Mensagem - pode ser otima, viavel ou inviavel

void imprimeMensagem(mensagem Mensagem)
{
	if(Mensagem == otima)
	{
		printf("Solucao otima.");
	}

	else if(Mensagem == viavel)
	{
		printf("Solucao viavel mas nao otima.");
	}

	else
	{
		printf("Solucao inviavel.");
	}
}

//-------------------------------------------------------------------------------------
// main:

int main()
{
	//---------------------------------------------------------------------------------
	// Declaração de variáveis:

	FILE *arquivo;										// Para abrir o arquivo

	char nomeArquivo[TAMANHO_MAX_NOME_ARQUIVO];			// Para receber o nome do arquivo
	char fraseLida[TAMANHO_MAX_FRASE];					// Para ler informações contidas no arquivo
	
	int W;												// Capacidade da mochila
	int N;												// Número de itens
	int contadorItens;									// Para iterar e ler os itens e seus pesos
	int contadorSolucao;								// Para iterar e encontrar a melhor solução
	int contadorSolucaoAux;								// Para iterar e encontrar a melhor solução
	int maiorValor;										// Para receber o valor da solução ótima
	int pesoMaiorValor;									// Para receber o peso do valor da solução ótima
	int maiorValorGlobal;								// Recebe o maior valor possível
	int pesoVerificado;									// Peso a ser verificado de acordo com a solução dada
	int valorVerificado;								// Valor a ser verificado de acordo com a solução dada

	int pesoItens[QUANTIDADE_MAX_ITENS];				// Irá conter o peso de cada um dos itens
	int valorItens[QUANTIDADE_MAX_ITENS];				// Irá conter o preço de cada um dos itens
	int solucaoVerificada[QUANTIDADE_MAX_ITENS];		// Irá conter a solução verificada

	mensagem Mensagem;									// Para imprimir a mensagem de saída

	//---------------------------------------------------------------------------------
	// Leitura do arquivo + teste de abertura:

	printf("Digite o nome do arquivo: ");					// Início da mensagem padrão
	scanf("%s", nomeArquivo);

	arquivo = fopen(nomeArquivo, "rb");						// Abre o arquivo no modo leitura

	if(arquivo == 0)										// Teste para debug
	{
		printf("ERRO: O arquivo não pôde ser aberto.\n");	// Nome incorreto do arquivo

		Mensagem = inviavel;								// Imprime a mensagem de solução inviável
		imprimeMensagem(Mensagem);

		return 0;											// Finaliza o programa
	}

	//---------------------------------------------------------------------------------
	// Início do recebimento de dados do arquivo - W:

	fscanf(arquivo, "%s", fraseLida);						// Recebe W - capacidade da mochila

	if( (fraseLida[0] == EOF) || (fraseLida[0] <= 0) )		// Se o caracter W recebido for inválido
	{
		Mensagem = inviavel;								// Imprime a mensagem de solução inviável
		imprimeMensagem(Mensagem);

		return 0;											// Finaliza o programa
	}

	W = atoi(fraseLida);

	//---------------------------------------------------------------------------------
	// Início do recebimento de dados do arquivo - N:

	fscanf(arquivo, "%s", fraseLida);						// Recebe N - número de itens

	if( (fraseLida[0] == EOF) || (fraseLida[0] <= 0) )		// Se o caracter N recebido for inválido
	{
		Mensagem = inviavel;								// Imprime a mensagem de solução inviável
		imprimeMensagem(Mensagem);

		return 0;											// Finaliza o programa
	}

	N = atoi(fraseLida);

	//---------------------------------------------------------------------------------
	// Recebimento de dados do arquivo - Itens:

	for(contadorItens = 0; contadorItens < N; contadorItens ++)
	{
		fscanf(arquivo, "%s", fraseLida);						// Recebe N - número de itens

		if(fraseLida[0] == EOF)									// Se o caracter recebido for inválido
		{
			Mensagem = inviavel;								// Imprime a mensagem de solução inviável
			imprimeMensagem(Mensagem);

			return 0;											// Finaliza o programa
		}

		pesoItens[contadorItens] = atoi(fraseLida);				// Armazena o peso do item (contadorItens)

		// ****************************************************************************		

		fscanf(arquivo, "%s", fraseLida);						// Recebe N - número de itens

		if(fraseLida[0] == EOF)									// Se o caracter recebido for inválido
		{
			Mensagem = inviavel;								// Imprime a mensagem de solução inviável
			imprimeMensagem(Mensagem);

			return 0;											// Finaliza o programa
		}

		valorItens[contadorItens] = atoi(fraseLida);			// Armazena o valor do item (contadorItens)
	}
	
	//---------------------------------------------------------------------------------
	// Recebimento de dados do arquivo - Solução a ser verificada:

	for(contadorItens = 0; contadorItens < N; contadorItens ++)
	{
		fscanf(arquivo, "%s", fraseLida);						// Recebe N - número de itens

		if(fraseLida[0] == EOF)									// Se o caracter recebido for inválido
		{
			Mensagem = inviavel;								// Imprime a mensagem de solução inviável
			imprimeMensagem(Mensagem);

			return 0;											// Finaliza o programa
		}

		solucaoVerificada[contadorItens] = atoi(fraseLida);		// Armazena o peso do item (contadorItens)
	}

	//---------------------------------------------------------------------------------
	// Inicialização das variáveis para a solução ótima:

	//maiorValor = 0;												// Inicializa com maior valor nulo
	//pesoMaiorValor = 0;											// Inicializa com peso do maior valor nulo
	maiorValorGlobal = 0;										// Inicializa com peso do maior valor nulo

	//---------------------------------------------------------------------------------
	// Processamento dos dados - análise da solução obtida:

	for(contadorItens = 0; contadorItens < N; contadorItens ++)
	{															// Percorrer todos os itens -> 0,1,2,3,4,...
		for(contadorSolucao = contadorItens + 1; contadorSolucao < N; contadorSolucao ++)
		{														// Percorrer após o primeiro -> 0,1,2 [...] 0,2,3, [...]

			maiorValor = valorItens[contadorItens];				// Inicializa com maior incial
			pesoMaiorValor = pesoItens[contadorItens];			// Inicializa com peso inicial

			for(contadorSolucaoAux = contadorSolucao; contadorSolucaoAux < N; contadorSolucaoAux ++)
			{													// Se é possível usar esse item sem exceder o peso, use
				if(pesoMaiorValor + pesoItens[contadorSolucaoAux] <= W)
				{												// Adiciona o peso, valor desse item
					//printf("%d <- %d\n", maiorValor, valorItens[contadorSolucaoAux]);

					maiorValor += valorItens[contadorSolucaoAux];
					pesoMaiorValor += pesoItens[contadorSolucaoAux];
				}
			}

			if(maiorValor > maiorValorGlobal)
			{
				maiorValorGlobal = maiorValor;					// Redefine a solução ótima. foi encontrada uma melhor
			}

			//putchar('\n');
			//printf("Maior valor até então: %d\n", maiorValorGlobal);	// Teste para debug
		}
	}

	//---------------------------------------------------------------------------------
	// Processamento dos dados - comparação da solução ótima com a solução dada:

	pesoVerificado = valorVerificado = 0;						// Inicializa as variáveis utilizadas nesse trecho de código

	for(contadorItens = 0; contadorItens < N; contadorItens ++)	// Percorre a solução dada
	{
		if(solucaoVerificada[contadorItens])					// Se é 1, adiciona o peso e o valor na comparação
		{
			pesoVerificado += pesoItens[contadorItens];
			valorVerificado += valorItens[contadorItens];
		}
	}

	//---------------------------------------------------------------------------------
	// Processamento dos dados - tomada de decisão com base nos cálculos sobre a solução informada:

	if(pesoVerificado > W)									// Excesso de peso
	{
		Mensagem = inviavel;								// Imprime a mensagem de solução inviável
		imprimeMensagem(Mensagem);
	}

	else if(valorVerificado > maiorValorGlobal)
	{
		Mensagem = otima;									// Imprime a mensagem de solução ótima
		imprimeMensagem(Mensagem);
	}

	else if( valorVerificado <= maiorValorGlobal)
	{
		Mensagem = viavel;									// Imprime a mensagem de solução viável
		imprimeMensagem(Mensagem);
	}

	//---------------------------------------------------------------------------------
	// Impressões para debug:
	/*

	for(contadorItens = 0; contadorItens < N; contadorItens ++)	// Imprime o peso e o valor de cada item
	{
		printf("%d, %d\n", pesoItens[contadorItens], valorItens[contadorItens]);
	}

	putchar('\n');												// \n para facilitar leitura

	for(contadorItens = 0; contadorItens < N; contadorItens ++)	// Imprime a solução verificada
	{
		printf("%d\n", solucaoVerificada[contadorItens]);
	}

	*/

	//putchar('\n');													// \n para facilitar leitura

	//printf("Valor verificado: %d\n", valorVerificado);
	//printf("Maior valor: %d\n", maiorValorGlobal);

	//putchar('\n');												// \n para facilitar leitura

	//*/
}