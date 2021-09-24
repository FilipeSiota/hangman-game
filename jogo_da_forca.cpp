/* Usando arrays, faça um jogo da forca para dois jogadores.

- O Jogador 1 deve informar uma palavra para ser adivinhada pelo Jogador 2 - limite a palavra a 20 caracteres.
- O Jogador 2 tem 5 vidas, cada erro ele perde uma vida.
- Cada acerto deve demonstrar a(ou as) posição(ões) que a letra informada ocupa na palavra.
- Ao acertar a palavra completa o jogo termina anunciando ao Jogador 2 que ele venceu.
- Caso todas as vidas do Jogador 2 acabem sem acerto da palavra o jogo termina anunciando que o Jogador 1 venceu. */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

#define LIMIT_WORD 21 // número máximo de caracteres para a palavra a ser adivinhada
#define QUANT_LIFES 6 // quantidade de vidas

int main()
{
	setlocale(LC_ALL, "Portuguese");

	// VARIÁVEIS PRINCIPAIS
	char player1[50], player2[50]; // armazena os nomes do jogadores
	int lifes = QUANT_LIFES; // quantidade de vidas
	char wordToGuess[LIMIT_WORD]; // armazena a palavra que será adivinhada
	int wordLength; // guarda o tamanho da wordToGuess

	char letter; // armazena a letra informada
	char allLetters[27]; // armazena em um vetor todas as letras já informadas, podendo receber até todas as letras do alfabeto
	allLetters[0] = '*'; // só para verificar se alguma letra já foi informada;
	
	// VARIÁVEIS AUXILIARES (CONTADORES E OUTRAS PARA VERIFICAÇÃO)
	int validateWord; // valida a wordToGuess
	int validateLetter; // valida a letter
	int win = 0; // valor diferente de 0, significa que o Jogador 2 ganhou
	int contAllLetters = 0; // conta quantas letras já foram informadas para ajudar no index do vetor allLetters[]
	char contLettersGuessed; // conta quantas letras já foram adivinhadas
	char contSpecialChar = 0; // conta quantos espaços ou hífens têm para saber apenas a quantidade de letras

	// FOR (variables)
	int heart; // percorre as vidas
	int let; // percorre as letras do vetor allLetters[]
	int eachLet; // percorre as letras da wordToGuess
	
	// PEGANDO OS NOMES DOS JOGADORES
	printf("########## Jogo da Forca ##########\n\n");

	printf("OBSERVAÇÕES:\n\n");
	printf(">> O 'Jogador 1' irá informar algo a ser adivinhado,\nenquanto o 'Jogador 2' será a pessoa tentando adivinhar;\n");
	printf(">> O 'Jogador 2' tem %d vidas para adivinhar;\n", QUANT_LIFES);
	printf(">> Jogar com a caixa alta do teclado ativada.\n\n");

	printf("Nome do Jogador 1: ");
	fflush(stdin);
	scanf("%50[^\n]", player1);

	printf("Nome do Jogador 2: ");
	fflush(stdin);
	scanf("%50[^\n]", player2);

	// PEDINDO AO JOGADOR 1 UMA PALAVRA
	do
	{
		system("cls");

		printf("OBSERVAÇÕES:\n\n");
		printf(">> Você pode digitar até 20 caracteres no campo abaixo;\n");
		printf(">> Espaços e hífens também são permitidos;\n");
		printf(">> Evite colocar acentos.\n\n");

		printf("Olá, %s! É a sua vez.\n\nInforme algo para ser adivinhado: ", player1);
		fflush(stdin);
		fgets(wordToGuess, LIMIT_WORD, stdin);
		
		wordLength = strlen(wordToGuess); // pega o tamanho da palavra informada

		wordToGuess[wordLength - 1] = '\0'; // tira o ENTER (\n) que veio com o fgets

		do
		{
			printf("\nConfirmar '%s'?\n", wordToGuess);

			printf("\nInforme (1) para SIM ou (2) para NÃO: ");
			fflush(stdin);
			scanf("%d", &validateWord);

			if (validateWord != 1 && validateWord != 2)
			{
				printf("\nOpção inválida! Tente novamente.\n");
			}

		} while (validateWord != 1 && validateWord != 2); // evita a inserção de números não correspondentes as opções
		
	} while (validateWord == 2); // repete enquanto o Jogador 1 não confirmar a palavra
	
	wordLength = strlen(wordToGuess); // pega o tamanho da palavra informada, agora sem a caractere '\n'
	
	for (eachLet = 0; eachLet < wordLength; eachLet++) // percorre a wordToGuess
	{
		if (wordToGuess[eachLet] == ' ') // se tiver um espaço na wordToGuess
		{
			printf("/ ");

			contSpecialChar++; // conta quantos espaços têm para saber apenas a quantidade de letras
		}
		else if (wordToGuess[eachLet] == '-') // se tiver um hífen na wordToGuess
		{
			printf("- ");

			contSpecialChar++; // conta quantos hífens têm para saber apenas a quantidade de letras
		}
	}

	// INÍCIO DO JOGO - JOGADOR 2
	while (lifes > 0 && !win) // enquanto o Jogador 2 tiver vidas e não tiver ganhado o jogo ainda
	{
		system("cls");
		
		printf("OBS.: Quando houver '/' significa que há um espaço.\n\n");
		
		printf("########## Agora é sua vez %s ##########\n\n", player2);
		
		// MOSTRANDO AS VIDAS DO JOGADOR 2
		printf("Vidas restantes ( ");

		for (heart = 0; heart < lifes; heart++)
		{
			printf("S2 ");
		}

		printf(")");
		
		// MOSTRA AS LETRAS JÁ INFORMADAS, SE HOUVER ALGUMA
		if (allLetters[0] != '*')
		{
			printf("\n\nLetras já informadas >> ");
			
			for (let = 0; let < contAllLetters; let++)
			{
				if (let == contAllLetters - 1) // se for a última repetição
				{
					printf("%c", allLetters[let]);
				}
				else
				{
					printf("%c - ", allLetters[let]);
				}
			}
		}
		
		// MOSTRA A PALAVRA QUE ESTÁ SENDO ADIVINHADA
		printf("\n\nPalavra: ");
		
		contLettersGuessed = 0; // inicializa a quantidade de letras que já foram adivinhadas com 0
		
		for (eachLet = 0; eachLet < wordLength; eachLet++) // percorre a wordToGuess
		{
			if (!contAllLetters) // se nenhuma letra foi informada ainda
			{
				if (wordToGuess[eachLet] == ' ') // se houver mais de uma palavra separadas por espaço
				{
					printf("/ ");

					contLettersGuessed++; // vai contando quantas letras já foram adivinhadas
				}
				else if (wordToGuess[eachLet] == '-') // se for uma palavra composta
				{
					printf("- ");

					contLettersGuessed++; // vai contando quantas letras já foram adivinhadas
				}
				else
				{
					printf("_ ");
				}
			}
			else
			{
				for (let = 0; let < contAllLetters; let++) // percorre o allLetters
				{
					if (allLetters[let] == wordToGuess[eachLet]) // se achar uma letra já informada que corresponde a wordToGuess
					{
						printf("%c ", allLetters[let]);
						
						contLettersGuessed++; // vai contando quantas letras já foram adivinhadas
						
						break;
					}
					else if (wordToGuess[eachLet] == ' ') // se houver mais de uma palavra separadas por espaço
					{
						printf("/ ");

						contLettersGuessed++; // vai contando quantas letras já foram adivinhadas
						
						break;
					}
					else if (wordToGuess[eachLet] == '-') // se for uma palavra composta
					{
						printf("- ");

						contLettersGuessed++; // vai contando quantas letras já foram adivinhadas
						
						break;
					}
					else if (let == contAllLetters - 1) // senão, se for a última repetição e não tiver entrado nos IF anterior
					{
						printf("_ ");
					}
				}
			}
		}
		
		printf("(%d letras)", wordLength - contSpecialChar); // mostra a quantidade de letras na palavra
		
		if (contLettersGuessed == wordLength) // se o Jogador 2 já adivinhou todas as letras da wordToGuess
		{
			win = 100; // Jogador 2 ganhou
		}
		else
		{
			// PEDINDO UMA LETRA PARA O JOGADOR 2
			do
			{
				validateLetter = 1;
				
				printf("\n\nInforme uma letra: ");
				fflush(stdin);
				scanf("%c", &letter);
				
				// verifica se o Jogador 2 já informou essa letra
				for (let = 0; let < contAllLetters; let++)
				{
					if (letter == allLetters[let])
					{
						printf("\nCaractere inválido! Você já informou este caractere. Tente novamente.");
						
						validateLetter = 0;
						
						break;
					}
				}

				if (letter == '\n' || letter == ' ' || letter == '-')
				{
					printf("\nCaractere inválido! ESPAÇO, ENTER e HÍFEN não são caracteres válidos. Tente novamente.");
				}
				
			} while (!validateLetter || letter == '\n' || letter == ' ' || letter == '-'); // repete enquanto a validação for 0, ou seja, a letra já tiver sido informada antes, ou algum caractere inválido tenha sido informado
			
			// ADICIONAR AO VETOR NO QUAL CONSTA TODAS AS LETRAS INFORMADAS
			allLetters[contAllLetters] = letter;
			
			contAllLetters++; // acrescenta 1 ao index do vetor acima
			
			// VERIFICAR SE A LETRA ESTÁ CONTIDA OU NÃO NA PALAVRA
			for (eachLet = 0; eachLet < wordLength; eachLet++) // percorre a wordToGuess
			{
				if (letter == wordToGuess[eachLet])
				{
					printf("\nParabéns! A letra '%c' faz parte da palavra.", letter);
					
					break;
				}
				else if (eachLet == wordLength - 1) // senão, se for a última repetição e não tiver entrado no IF anterior
				{
					printf("\nUps! A letra '%c' não faz parte da palavra.", letter);
					
					lifes--; // como errou, perde uma vida
				}
			}
			
			printf("\n\nPressione ENTER para continuar.");
			fflush(stdin);
			getchar();
			
		}
		
	}
	
	if (!lifes) // se as vidas do Jogador 2 acabaram
	{
		system("cls");
		
		printf("########## GAME OVER ##########\n\n");
		
		printf("A palavra era: %s\n", wordToGuess);
		
		printf("\n%s, suas vidas acabaram.\nParabéns %s, você venceu o jogo!", player2, player1);
	}
	else if (win == 100) // se o Jogador 2 ganhou
	{
		printf("\n\nParabéns %s, você adivinhou e venceu o jogo!", player2);
	}
	
	printf("\n\nFim de Jogo! Pressione ENTER para encerrar o programa.");
	fflush(stdin);
	getchar();
	
	return 0;
}