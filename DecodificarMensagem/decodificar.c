
/*-------------------------------------------------------------------------------------
Programa 2 - Laboratório de Algoritmos e Estruturas de Dados 1 - LAEDS

Aluno: Ronaldo Mendonça Zica
Matrícula:20193018768
Data: 06/02/2021
Professora: Natalia Cosse Batista

-------------------------------------------------------------------------------------*/


//-------------------------------------------------------------------------------------
// Defines:

#define TAMANHO_MAX_NOME_ARQUIVO 100
#define TAMANHO_MAX_FRASE 1000

//-------------------------------------------------------------------------------------
// Includes:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------------------------------------------
// main:

int main()
{
	//---------------------------------------------------------------------------------
	// Declaração e inicialização de variáveis:

	FILE *arquivo;										// Para abrir o arquivo

	char nomeArquivo [TAMANHO_MAX_NOME_ARQUIVO];		// Para receber o nome do arquivo
	char fraseCodificada [TAMANHO_MAX_FRASE];			// Para receber a frase codificada
	char fraseDecodificada [TAMANHO_MAX_FRASE];		// Para receber a frase decodificada

	//char caracterLido = ' ';							// Para ler cada caracter da mensagem

	int posFraseCodificada = 0;							// Para indicar a posição da string
	int posFraseDecodificada;							// Para indicar a posição da string
	int tamanhoMensagem;								// Para receber o tamanho da mensagem
	int permutaBlocos;									// Para auxiliar no processo de permutar os blocos
	int permutaBlocosFinal;								// Para auxiliar no processo de permutar os blocos
	int refleteBlocos;									// Para auxiliar no processo de refletir os blocos		

	//---------------------------------------------------------------------------------
	// Leitura do arquivo + teste de abertura:

	printf("Digite o nome do arquivo: ");					// Início da mensagem padrão
	scanf("%s", nomeArquivo);

	arquivo = fopen(nomeArquivo, "rb");						// Abre o arquivo no modo leitura

	if(arquivo == 0)										// Teste para debug
	{
		printf("ERRO: O arquivo não pôde ser aberto.\n");
		return 0;
	}

	//---------------------------------------------------------------------------------
	// Impressão de um trecho da mensagem padrão:

	printf("\n--------------------\n");
	printf("Mensagem codificada:");
	printf("\n--------------------\n");

	//---------------------------------------------------------------------------------
	// Recebe a frase codificada do arquivo:

	fscanf(arquivo, "%s", fraseCodificada);

	/*

	while(caracterLido != EOF)									// Lê o arquivo até o fim
	{
		caracterLido = fgetc(arquivo);
		fraseCodificada[posFraseCodificada] = caracterLido;
		posFraseCodificada ++;
	}

	fraseCodificada[posFraseCodificada - 1] = '\0';				// Marca o fim da String

	*/

	//---------------------------------------------------------------------------------
	// Imprime a frase codificada + um trecho da mensagem padrão:

	printf("%s\n", fraseCodificada);

	printf("\n----------------------\n");
	printf("Mensagem decodificada:");
	printf("\n----------------------\n");

	//---------------------------------------------------------------------------------
	// Decifração da mensagem - Cria uma string auxiliar que armazenará a frase decodificada:

	tamanhoMensagem = sizeof(fraseCodificada);					// Calculando tamanho da mensagem + \0	

	for(posFraseCodificada = 0; posFraseCodificada < tamanhoMensagem; posFraseCodificada ++)
	{
		fraseDecodificada[posFraseCodificada] = fraseCodificada[posFraseCodificada];
	}

	//---------------------------------------------------------------------------------
	// Decifração da mensagem - Colocando os blocos na ordem correta:

	tamanhoMensagem = strlen(fraseDecodificada);				// Calculando tamanho da mensagem

	// Inverte os caracteres para arrumar os blocos

	permutaBlocos = 0;
	permutaBlocosFinal = tamanhoMensagem;

	for(posFraseDecodificada = 0; posFraseDecodificada < tamanhoMensagem; posFraseDecodificada += 8)
	{
		fraseDecodificada[permutaBlocos] = fraseCodificada[permutaBlocosFinal - 2];
		fraseDecodificada[permutaBlocos + 1] = fraseCodificada[permutaBlocosFinal - 1];

		fraseDecodificada[permutaBlocosFinal - 2] = fraseCodificada[permutaBlocos];
		fraseDecodificada[permutaBlocosFinal - 1] = fraseCodificada[permutaBlocos + 1];

		permutaBlocos += 4;
		permutaBlocosFinal -= 4;
	}

	//---------------------------------------------------------------------------------
	// Decifração da mensagem - Refletindo cada bloco:
	
	for(posFraseDecodificada = 0; posFraseDecodificada < tamanhoMensagem; posFraseDecodificada += 2)
	{															// Para cada bloco, inverte seus valores
		refleteBlocos = fraseDecodificada[posFraseDecodificada];
		fraseDecodificada[posFraseDecodificada] = fraseDecodificada[posFraseDecodificada + 1];
		fraseDecodificada[posFraseDecodificada + 1] = refleteBlocos;
	}

	//---------------------------------------------------------------------------------
	// Decifração da mensagem - Cifra de César:

	for(posFraseDecodificada = 0; posFraseDecodificada < tamanhoMensagem; posFraseDecodificada ++)
	{
		if(fraseDecodificada[posFraseDecodificada] != '#')
		{
			// Se é maiúsculo
			if( (fraseDecodificada[posFraseDecodificada] >= 'A') && (fraseDecodificada[posFraseDecodificada] <= 'Z') )
			{
				if(fraseDecodificada[posFraseDecodificada] > 'E')
				{
					fraseDecodificada[posFraseDecodificada] -= 5;
				}

				else
				{	// Realiza o deslocamento para o final do alfabeto
					fraseDecodificada[posFraseDecodificada] += ('Z' - 'A' - 4);
				}
			}

			// Se é minúsculo
			else
			{
				if(fraseDecodificada[posFraseDecodificada] > 'e')
				{
					fraseDecodificada[posFraseDecodificada] -= 5;
				}

				else
				{	// Realiza o deslocamento para o final do alfabeto
					fraseDecodificada[posFraseDecodificada] += ('z' - 'a' - 4);
				}
			}
		}

		else
		{
			fraseDecodificada[posFraseDecodificada] = ' ';
		}
	}
	
	//---------------------------------------------------------------------------------
	// Impressão final:

	printf("%s", fraseDecodificada);

	//putchar('\n');												// \n para facilitar leitura, comentar depois
}