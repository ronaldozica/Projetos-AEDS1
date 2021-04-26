
/*-------------------------------------------------------------------------------------
Programa 6 - Laboratório de Algoritmos e Estruturas de Dados 1 - LAEDS
Programa 6 - Busca por padrão em sequência

Aluno: Ronaldo Mendonça Zica
Matrícula: 20193018768

Aluno: Nasser Rafael França Kilesse

Data de início: 22/03/2021
Data limite de envio: 19/03/2021

Professora: Natalia Cosse Batista

-------------------------------------------------------------------------------------*/


//-------------------------------------------------------------------------------------
// Defines:

#define TAMANHO_MAX_NOME_ARQUIVO 100
#define TAMANHO_MAX_FRASE 100
#define NUMERO_MAX_ELEMENTOS 1000
#define QUANTIDADE_LINHAS_MATRIZ 2
#define QUANTIDADE_DIGITOS_PADRAO 11

//-------------------------------------------------------------------------------------
// Includes:

#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// Criando o tipo de variável "boolean":

typedef enum 
{
   verdadeiro, falso
} boolean;

//-------------------------------------------------------------------------------------
// Criando o tipo de variável "mensagem":

typedef enum 
{
   encontrado, naoEncontrado
} Mensagem;

//-------------------------------------------------------------------------------------
// Função imprime mensagem:
// Parâmetro:	mensagem Mensagem - pode ser otima, viavel ou inviavel

void imprimeMensagem(Mensagem mensagem)
{
	printf("Resultado: ");

	if(mensagem == encontrado)
	{
		printf("Padrao de faixa de pedestres encontrado.");
	}

	else
	{
		printf("Padrao de faixa de pedestres nao encontrado.");
	}
}

//-------------------------------------------------------------------------------------
// Principal - main:

int main()
{
	//---------------------------------------------------------------------------------
	// Declaração de variáveis e inicialização de variáveis:

	FILE *arquivo;										// Para abrir o arquivo

	char nomeArquivo[TAMANHO_MAX_NOME_ARQUIVO];			// Para receber o nome do arquivo
	char fraseLida[TAMANHO_MAX_FRASE];					// Para ler informações contidas no arquivo

	int N;												// N do enunciado: Número total de elementos
	int contadorElementos;								// Para iterar e percorrer o vetor de elementos
	int contadorElementosAuxiliar;						// Para iterar e percorrer o vetor de elementos sem repetições e organizá-lo em ordem crescente
	int contadorElementosSemRepeticoes;					// Para iterar e percorrer o vetor de elementos sem repetições
	int posicaoElementosSemRepeticoes = 0;				// Para marcar a posição atual do vetor sem repetições
	int contadorColunaMatriz;							// Para iterar e percorrer as colunas da matriz
	int quantidadeElementosDiferentes;					// Para salvar a quantidade de elementos diferentes
	int variavelAuxiliaTroca;							// Para ajudar a organizar o vetor em ordem crescente
	int quantidadeColunas;								// Essa variável será o K, que é inicializado com 1 e será incrementado ao longo do código

	int elementosLidos[NUMERO_MAX_ELEMENTOS];			// Armazena os elementos na ordem lida
	int elementosSemRepeticoes[NUMERO_MAX_ELEMENTOS];	// Armazena os elementos sem repetições na ordem lida na ordem lida

	int **matriz;

	boolean numeroJaApareceu;							// Para ajudar a criar o vetor sem repetições

	//---------------------------------------------------------------------------------
	// Leitura do arquivo + teste de abertura:

	printf("Digite o nome do arquivo: ");					// Início da mensagem padrão
	scanf("%s", nomeArquivo);

	arquivo = fopen(nomeArquivo, "rb");						// Abre o arquivo no modo leitura

	if(arquivo == 0)										// Teste para debug
	{
		printf("ERRO: O arquivo não pôde ser aberto.\n");	// Nome incorreto do arquivo
		return 0;											// Finaliza o programa
	}

	//---------------------------------------------------------------------------------
	// Início da leitura de dados do arquivo - Obtém o valor de N e verifica se esse valor é válido:

	fscanf(arquivo, "%s", fraseLida);						// Recebe N: Número total de elementos

	if(fraseLida[0] == EOF)									// Se o caracter W recebido for inválido
	{
		printf("ERRO: O valor de N informado é inválido ou inexistente.\n");
		return 0;											// Finaliza o programa
	}

	N = atoi(fraseLida);									// Transforma a String lida em Inteiro

	if( N <= 0)												// N deve ser obrigatoriamente maior que 0
	{
		printf("ERRO: O valor de N não pode ser menor ou igual a 0.\n");
		return 0;	
	}

	//---------------------------------------------------------------------------------
	// Leitura de dados do arquivo - Lê todos os elementos e os coloca em um vetor na ordem em que aparecem:

	for(contadorElementos = 0; contadorElementos < N; contadorElementos ++)
	{
		fscanf(arquivo, "%s", fraseLida);						// Lê o elemento atual

		if(fraseLida[0] == EOF)									// Se o caracter recebido for inválido
		{
			printf("ERRO: O número de elementos informado em N não condiz com a quantidade de elementos presente.\n");
			return 0;											// Finaliza o programa
		}

		elementosLidos[contadorElementos] = atoi(fraseLida);	// Armazena o item atual (da posição contadorElementos)
	}

	//---------------------------------------------------------------------------------
	// Processamento dos dados do arquivo: Cria um vetor com os números lidos sem repetições

	for(contadorElementos = 0; contadorElementos < N; contadorElementos ++)
	{
		numeroJaApareceu = falso;

		for(contadorElementosSemRepeticoes = 0; contadorElementosSemRepeticoes < contadorElementos; contadorElementosSemRepeticoes ++)
		{									// Conta de 0 até o elemento atual
			if(elementosLidos[contadorElementos] == elementosLidos[contadorElementosSemRepeticoes])
			{								// Se o elemento atual repetiu em algum momento até então
				numeroJaApareceu = verdadeiro;
			}
		}

		if(numeroJaApareceu == falso)
		{									// Esse número não apareceu, então o armazena no vetor e desloca o contador para a próxima posição
			elementosSemRepeticoes[posicaoElementosSemRepeticoes] = elementosLidos[contadorElementos];
			posicaoElementosSemRepeticoes ++;
		}
	}

	//---------------------------------------------------------------------------------
	// Processamento dos dados do arquivo: Organiza o vetor dos números sem repetição em ordem crescente

	for(contadorElementos = 0; contadorElementos < posicaoElementosSemRepeticoes; contadorElementos ++)
	{														// Percorre o vetor
		for(contadorElementosAuxiliar = contadorElementos + 1; contadorElementosAuxiliar < posicaoElementosSemRepeticoes; contadorElementosAuxiliar ++)
		{													// Percorre o vetor pegando o conteúdo do próximo endereço para comparação
			if(elementosSemRepeticoes[contadorElementos] > elementosSemRepeticoes[contadorElementosAuxiliar])
			{												// Se tem dois números fora de ordem, troca eles de lugar e reinicia a comparação
				variavelAuxiliaTroca = elementosSemRepeticoes[contadorElementos];
				elementosSemRepeticoes[contadorElementos] = elementosSemRepeticoes[contadorElementosAuxiliar];
				elementosSemRepeticoes[contadorElementosAuxiliar] = variavelAuxiliaTroca;
				contadorElementos = -1;						// -1 porque quando sair do for vai somar 1 e ficar em 0 novamente
				break;	// Esse algoritmo para organizar o vetor em ordem crescente provavelmente não é o mais eficiente mas foi suficiente para esse exercício
			}
		}
	}

	//---------------------------------------------------------------------------------
	// Cria a matriz dinamicamente:

	matriz = malloc(QUANTIDADE_LINHAS_MATRIZ * sizeof (int*));
												// Aloca um vetor de 2 ponteiros para as linhas
	matriz[0] = malloc(1 * sizeof (int));		// Aloca na primeira linha um vetor de 1 inteiro
	matriz[1] = malloc(1 * sizeof (int));		// Aloca na segunda linha um vetor de 1 inteiro
	// A razão de ter alocado somente 1 inteiro é que conforme o valor de K for mudando ao longo do código serão alocadas mais posições	

	//---------------------------------------------------------------------------------
	// Inicializa e reinicializa algumas variáveis para auxiliar no preenchimento da matriz:

	contadorColunaMatriz = 0;					// Coluna atual da matriz, será o K - 1
	quantidadeElementosDiferentes = posicaoElementosSemRepeticoes + 1;	// Salva a quantidade de elementos diferentes
	quantidadeColunas = 1;						// K começa com 1
	posicaoElementosSemRepeticoes = 0;			// Reinicializa o contador para o vetor de elementos sem repetições

	//---------------------------------------------------------------------------------
	// Preenche a matriz e aloca mais posições conforme a necessidade:

	// Inicialmente, preenche a primeira coluna da matriz
	// Será preenchido a primeira coluna da matriz separada porque no for seguinte será realizada sempre a comparação da coluna atual com a anterior
	// Logo, será necessário uma coluna inicial prrenchida para que seja possível realizar essa comparação

	for(posicaoElementosSemRepeticoes = 0; posicaoElementosSemRepeticoes < quantidadeElementosDiferentes; posicaoElementosSemRepeticoes ++)
	{									// Percorre o vetor de elementos repetidos organizado em ordem crescente
		if(elementosSemRepeticoes[posicaoElementosSemRepeticoes] == elementosLidos[0])
		{								// A posição desse vetor que possui o número desejado é igual ao valor atribuído a esse elemento na primeira linha da matriz
			matriz[0][contadorColunaMatriz] = posicaoElementosSemRepeticoes + 1;
			break;						// A razão de somar 1 nessa variável é porque as posições do vetor começam em 0, logo, a posição real sempre estará deslocada em -1
		}
	}

	matriz[1][contadorColunaMatriz] = 1;		// Para a segunda linha da matriz, será realizado um contador que começa em 1 e incrementa a cada repetição consecutiva do número

	for(contadorElementos = 1; contadorElementos < N; contadorElementos ++)
	{											// Percorre todos os elementos do vetor lido, verificando quantas repetições consecutivas existem
		if(elementosLidos[contadorElementos] != elementosLidos[contadorElementos - 1])
		{										// Se o número atual é diferente do número anterior, então é necessário realizar algumas mudanças
			contadorColunaMatriz ++;			// Primeiro, incrementa o contador que irá indicar a coluna atual da matriz
			quantidadeColunas ++;				// Depois, incrementa o K

			matriz[0] = realloc(matriz[0], quantidadeColunas * sizeof (int));
			matriz[1] = realloc(matriz[1], quantidadeColunas * sizeof (int));
			// Agora, cada uma das linhas da matriz são realocadas para que seja possível caber K elementos

			for(posicaoElementosSemRepeticoes = 0; posicaoElementosSemRepeticoes < quantidadeElementosDiferentes; posicaoElementosSemRepeticoes ++)
			{									// Mesma lógica executada para o caso inicial
				if(elementosSemRepeticoes[posicaoElementosSemRepeticoes] == elementosLidos[contadorElementos])
				{								// Encontra a posição do vetor sem repetições com o elemento lido e coloca essa posição na primeira linha da matriz
					matriz[0][contadorColunaMatriz] = posicaoElementosSemRepeticoes + 1;
					break;
				}
			}

			matriz[1][contadorColunaMatriz] = 1;	// Reinicia a contagem de elementos consecutivos para a segunda linha
		}

		else
		{
			matriz[1][contadorColunaMatriz] ++;	// Como os dois números comparados são iguais, aumenta a contagem de núemros consecutivos
		}
	}

	//---------------------------------------------------------------------------------
	// Analisa se possui o padrão do enunciado:

	//int padraoAnalisado[11] =  {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};	// Mensagem padrão passada no enunciado
	//int posicaoAtualComparada = 0;					// Posição comparada do padrão do enunciado
	//int posicaoInicialComparada = 0;				// Posição inicial de comparação
	//Mensagem mensagem = naoEncontrado;				// Cria uma variável do tipo mensagem para que possa ser chamada a função imprimeMensagem

	for(contadorElementos = 0; contadorElementos < N; contadorElementos ++)
	{												// Itera todos os elementos do vetor
		printf("%d ", matriz[0][contadorElementos]);
	}

	putchar('\n');

	//---------------------------------------------------------------------------------
	// Imprime mensagem:

	//imprimeMensagem(mensagem);						// O valor da variável "mensagem" pode ser: encontrada ou naoEncontrada

	//---------------------------------------------------------------------------------
	// Impressões finais do código:
	/*

	printf("Matriz:\n");						// Mensagem estática

	for(contadorElementos = 0; contadorElementos < quantidadeColunas; contadorElementos ++)
	{											// Imprime primeiro a primeira linha
		printf("%d ", matriz[0][contadorElementos]);
	}
	putchar('\n');
	for(contadorElementos = 0; contadorElementos < quantidadeColunas; contadorElementos ++)
	{											// Depois a segunda
		printf("%d ", matriz[1][contadorElementos]);	
	}
	putchar('\n');

	*/

	//---------------------------------------------------------------------------------
	// Impressões para debug:

	//printf("O valor de N é: %d\n", N);

	/*
	for(contadorElementos = 0; contadorElementos < N; contadorElementos ++)
	{
		printf("%d ", elementosLidos[contadorElementos]);
	}
	putchar('\n');
	for(contadorElementosSemRepeticoes = 0; contadorElementosSemRepeticoes < posicaoElementosSemRepeticoes; contadorElementosSemRepeticoes ++)
	{
		printf("%d ", elementosSemRepeticoes[contadorElementosSemRepeticoes]);
	}
	putchar('\n');
	*/

	//---------------------------------------------------------------------------------
	// Libera a memória da matriz:

	free(matriz[0]); 			// Primeiro libera cada uma das linhas individualmente
	free(matriz[1]);
	free(matriz);				// Depois libera o vetor de ponteiros para cada uma das linhas
}