
	maiorValor = valorItens[contadorItens];				// Inicializa com maior incial
	pesoMaiorValor = pesoItens[contadorItens];			// Inicializa com peso inicial

	for(contadorSolucaoAux = contadorSolucao; contadorSolucaoAux < N; contadorSolucaoAux ++)
	{
		for(contadorItensAux = contadorSolucao; contadorItensAux < N; contadorItensAux ++)
		{													// Se é possível usar esse item sem exceder o peso, use
			maiorValor += valorItens[contadorItensAux];
			pesoMaiorValor += pesoItens[contadorItensAux];
		}
															// Se é possível usar esse item sem exceder o peso, use
		if( (maiorValor > maiorValorGlobal) && (pesoMaiorValor < W) )
		{
			maiorValorGlobal = maiorValor;					// Redefine a solução ótima. foi encontrada uma melhor
		}
	}

	//putchar('\n');
	//printf("Maior valor até então: %d\n", maiorValorGlobal);	// Teste para debug


	//00000000000000000000000000000000000

	for(contadorVerificaSolucao = contadorSolucaoAux; contadorVerificaSolucao < N; contadorVerificaSolucao ++)
	{
		if(pesoMaiorValor + pesoItens[contadorVerificaSolucao] < W) && (pesoMaiorValor + pesoItens[contadorSolucaoAux] + pesoItens[contadorVerificaSolucao] > W)
		{
			
		}
	}