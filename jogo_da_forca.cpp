/* Usando arrays, fa?a um jogo da forca para dois jogadores.

- O Jogador 1 deve informar uma palavra para ser adivinhada pelo Jogador 2 - limite a palavra a 20 caracteres.
- O Jogador 2 tem 5 vidas, cada erro ele perde uma vida.
- Cada acerto deve demonstrar a(ou as) posi??o(?es) que a letra informada ocupa na palavra.
- Ao acertar a palavra completa o jogo termina anunciando ao Jogador 2 que ele venceu.
- Caso todas as vidas do Jogador 2 acabem sem acerto da palavra o jogo termina anunciando que o Jogador 1 venceu. */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define LIMIT_WORD 21 // n?mero m?ximo de caracteres para a palavra a ser adivinhada
#define QUANT_LIFES 6 // quantidade de vidas
#define MAX_PLAYERS 50 // n?mero m?ximo de jogadores

void getPlayer(int *controler, int numPlayers);
int getWinner(int *score, int numPlayers, int *contWinners);
void sortSubject(char *subject);

int main()
{
	setlocale(LC_ALL, "Portuguese");

	// VARI?VEIS PRINCIPAIS
	char players[MAX_PLAYERS][50]; // armazena os nomes do jogadores
	int score[MAX_PLAYERS] = { }; // placar
	int lifes = QUANT_LIFES; // quantidade de vidas
	char wordToGuess[LIMIT_WORD]; // armazena a palavra que ser? adivinhada
	int wordLength; // guarda o tamanho da wordToGuess
	char subject[50];

	char letter; // armazena a letra informada
	char allLetters[27]; // armazena em um vetor todas as letras j? informadas, podendo receber at? todas as letras do alfabeto
	allLetters[0] = '*'; // s? para verificar se alguma letra j? foi informada;
	
	// VARI?VEIS AUXILIARES (CONTADORES E OUTRAS PARA VERIFICA??O)
	int numPlayers; // n?mero de jogadores na partida
	int playerScored; // saber quem pontuou
	int exit, control_player = -1; // controla a sa?da e a vez do jogador
	int validateWord; // valida a wordToGuess
	int validateLetter; // valida a letter
	int win = 0; // valor diferente de 0, significa que o Jogador 2 ganhou
	int winnerScore; // armazena a pontua??o do vencedor
	int contWinners; // armazena a quantidade de vencedores
	int contAllLetters = 0; // conta quantas letras j? foram informadas para ajudar no index do vetor allLetters[]
	char contLettersGuessed; // conta quantas letras j? foram adivinhadas
	char contSpecialChar = 0; // conta quantos espa?os ou h?fens t?m para saber apenas a quantidade de letras

	// FOR (variables)
	int heart; // percorre as vidas
	int let; // percorre as letras do vetor allLetters[]
	int eachLet; // percorre as letras da wordToGuess
	int player; // percorre vetores relativos a players
	
	// PEGANDO OS NOMES DOS JOGADORES
	printf("########## Jogo da Forca ##########\n\n");
	
	do
	{
		printf("Informe o n?mero de jogadores (m?x. 50): ");
		scanf("%d", &numPlayers);
		
		if (numPlayers < 1 || numPlayers > MAX_PLAYERS)
		{
			printf("\nValor inv?lido! Tente novamente.\n");
		}
	}
	while (numPlayers < 1 || numPlayers > MAX_PLAYERS);
	
	system("cls");
	
	printf("########## Jogo da Forca ##########\n\n");

	printf("OBSERVA??ES:\n\n");
	printf(">> O 'Jogador 1' ir? informar algo a ser adivinhado,\nenquanto o 'Jogador 2' ser? a pessoa tentando adivinhar;\n");
	printf(">> O 'Jogador 2' tem %d vidas para adivinhar;\n", QUANT_LIFES);
	printf(">> Jogar com a caixa alta do teclado ativada.\n\n");
	
	for (player = 0; player < numPlayers; player++)
	{
		printf("Nome do Jogador %d: ", player + 1);
		fflush(stdin);
		scanf("%50[^\n]", players[player]);
	}
	
	do
	{
		lifes = QUANT_LIFES;
		win = 0;
		contAllLetters = 0;
		contLettersGuessed = 0;
		contSpecialChar = 0;
		
		for (let = 0; let < 27; let++)
		{
			allLetters[let] = NULL;
		}
		allLetters[0] = '*';
		
		
		// PEDINDO AO JOGADOR 1 UMA PALAVRA
		getPlayer(&control_player, numPlayers);
		sortSubject(subject);
		
		do
		{
			system("cls");
	
			printf("OBSERVA??ES:\n\n");
			printf(">> Voc? pode digitar at? 20 caracteres no campo abaixo;\n");
			printf(">> Espa?os e h?fens tamb?m s?o permitidos;\n");
			printf(">> Evite colocar acentos.\n\n");
	
			printf("Ol?, %s! ? a sua vez.\n\nInforme algo para ser adivinhado relacionado ao tema '%s': ", players[control_player], subject);
			fflush(stdin);
			fgets(wordToGuess, LIMIT_WORD, stdin);
			
			wordLength = strlen(wordToGuess); // pega o tamanho da palavra informada
	
			wordToGuess[wordLength - 1] = '\0'; // tira o ENTER (\n) que veio com o fgets
	
			do
			{
				printf("\nConfirmar '%s'?\n", wordToGuess);
	
				printf("\nInforme (1) para SIM ou (2) para N?O: ");
				fflush(stdin);
				scanf("%d", &validateWord);
	
				if (validateWord != 1 && validateWord != 2)
				{
					printf("\nOp??o inv?lida! Tente novamente.\n");
				}
	
			} while (validateWord != 1 && validateWord != 2); // evita a inser??o de n?meros n?o correspondentes as op??es
			
		} while (validateWord == 2); // repete enquanto o Jogador 1 n?o confirmar a palavra
		
		wordLength = strlen(wordToGuess); // pega o tamanho da palavra informada, agora sem a caractere '\n'
		
		for (eachLet = 0; eachLet < wordLength; eachLet++) // percorre a wordToGuess
		{
			if (wordToGuess[eachLet] == ' ') // se tiver um espa?o na wordToGuess
			{
				printf("/ ");
	
				contSpecialChar++; // conta quantos espa?os t?m para saber apenas a quantidade de letras
			}
			else if (wordToGuess[eachLet] == '-') // se tiver um h?fen na wordToGuess
			{
				printf("- ");
	
				contSpecialChar++; // conta quantos h?fens t?m para saber apenas a quantidade de letras
			}
		}
	
		// IN?CIO DO JOGO - JOGADOR 2
		while (lifes > 0 && !win) // enquanto o Jogador 2 tiver vidas e n?o tiver ganhado o jogo ainda
		{
			system("cls");
			
			printf("OBS.: Quando houver '/' significa que h? um espa?o.\n\n");
			
			printf("########## Agora ? a vez dos demais jogadores ##########\n\n");
			
			// MOSTRANDO AS VIDAS DO JOGADOR 2
			printf("Vidas restantes ( ");
	
			for (heart = 0; heart < lifes; heart++)
			{
				printf("S2 ");
			}
	
			printf(")");
			
			// MOSTRA AS LETRAS J? INFORMADAS, SE HOUVER ALGUMA
			if (allLetters[0] != '*')
			{
				printf("\n\nLetras j? informadas >> ");
				
				for (let = 0; let < contAllLetters; let++)
				{
					if (let == contAllLetters - 1) // se for a ?ltima repeti??o
					{
						printf("%c", allLetters[let]);
					}
					else
					{
						printf("%c - ", allLetters[let]);
					}
				}
			}
			
			// MOSTRA O TEMA
			printf("Tema: %s", subject);
			
			// MOSTRA A PALAVRA QUE EST? SENDO ADIVINHADA
			printf("\n\nPalavra: ");
			
			contLettersGuessed = 0; // inicializa a quantidade de letras que j? foram adivinhadas com 0
			
			for (eachLet = 0; eachLet < wordLength; eachLet++) // percorre a wordToGuess
			{
				if (!contAllLetters) // se nenhuma letra foi informada ainda
				{
					if (wordToGuess[eachLet] == ' ') // se houver mais de uma palavra separadas por espa?o
					{
						printf("/ ");
	
						contLettersGuessed++; // vai contando quantas letras j? foram adivinhadas
					}
					else if (wordToGuess[eachLet] == '-') // se for uma palavra composta
					{
						printf("- ");
	
						contLettersGuessed++; // vai contando quantas letras j? foram adivinhadas
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
						if (allLetters[let] == wordToGuess[eachLet]) // se achar uma letra j? informada que corresponde a wordToGuess
						{
							printf("%c ", allLetters[let]);
							
							contLettersGuessed++; // vai contando quantas letras j? foram adivinhadas
							
							break;
						}
						else if (wordToGuess[eachLet] == ' ') // se houver mais de uma palavra separadas por espa?o
						{
							printf("/ ");
	
							contLettersGuessed++; // vai contando quantas letras j? foram adivinhadas
							
							break;
						}
						else if (wordToGuess[eachLet] == '-') // se for uma palavra composta
						{
							printf("- ");
	
							contLettersGuessed++; // vai contando quantas letras j? foram adivinhadas
							
							break;
						}
						else if (let == contAllLetters - 1) // sen?o, se for a ?ltima repeti??o e n?o tiver entrado nos IF anterior
						{
							printf("_ ");
						}
					}
				}
			}
			
			printf("(%d letras)", wordLength - contSpecialChar); // mostra a quantidade de letras na palavra
			
			if (contLettersGuessed == wordLength) // se o Jogador 2 j? adivinhou todas as letras da wordToGuess
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
					
					// verifica se o Jogador 2 j? informou essa letra
					for (let = 0; let < contAllLetters; let++)
					{
						if (letter == allLetters[let])
						{
							printf("\nCaractere inv?lido! Voc? j? informou este caractere. Tente novamente.");
							
							validateLetter = 0;
							
							break;
						}
					}
	
					if (letter == '\n' || letter == ' ' || letter == '-')
					{
						printf("\nCaractere inv?lido! ESPA?O, ENTER e H?FEN n?o s?o caracteres v?lidos. Tente novamente.");
					}
					
				} while (!validateLetter || letter == '\n' || letter == ' ' || letter == '-'); // repete enquanto a valida??o for 0, ou seja, a letra j? tiver sido informada antes, ou algum caractere inv?lido tenha sido informado
				
				// ADICIONAR AO VETOR NO QUAL CONSTA TODAS AS LETRAS INFORMADAS
				allLetters[contAllLetters] = letter;
				
				contAllLetters++; // acrescenta 1 ao index do vetor acima
				
				// VERIFICAR SE A LETRA EST? CONTIDA OU N?O NA PALAVRA
				for (eachLet = 0; eachLet < wordLength; eachLet++) // percorre a wordToGuess
				{
					if (letter == wordToGuess[eachLet])
					{
						printf("\nParab?ns! A letra '%c' faz parte da palavra.", letter);
						
						break;
					}
					else if (eachLet == wordLength - 1) // sen?o, se for a ?ltima repeti??o e n?o tiver entrado no IF anterior
					{
						printf("\nUps! A letra '%c' n?o faz parte da palavra.", letter);
						
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
			
			printf("\nAs vidas acabaram.\nParab?ns %s, voc? venceu a rodada!", players[control_player]);
			
			score[control_player]++;
		}
		else if (win == 100) // se o Jogador 2 ganhou
		{
			printf("\n\nParab?ns, voc? adivinhou e venceu a rodada!");
			
			printf("\n\nQuem adivinhou a palavra?\n");
			
			for (player = 0; player < numPlayers; player++)
			{
				printf("\n%d. %s", player + 1, players[player]);
			}
			
			do
			{
				printf("\n\nEscolha uma op??o: ");
				fflush(stdin);
				scanf("%d", &playerScored);
				
				if (playerScored < 1 || playerScored > numPlayers)
				{
					printf("\nOp??o inv?lida! Tente novamente.");
				}
			}
			while (playerScored < 1 || playerScored > numPlayers);
			
			for (player = 0; player < numPlayers; player++)
			{
				if (player == playerScored - 1)
				{
					score[player]++;
				}
			}
		}
		
		printf("\nPressione ENTER para continuar.");
		fflush(stdin);
		getchar();
		
		system("cls");
		
		printf("########## Jogo da Forca ##########\n\n");
		
		printf("PLACAR:\n\n");
		
		for (player = 0; player < numPlayers; player++)
		{
			printf("%s: %d\n", players[player], score[player]);
		}
		
		do
		{
			printf("\nContinuar a partida?\n\nInforme 1 para SIM ou 2 para N?O: ");
			fflush(stdin);
			scanf("%d", &exit);
			
			if (exit < 1 || exit > 2)
			{
				printf("\nOp??o inv?lida! Tente novamente.");
			}
		}
		while (exit < 1 || exit > 2);
	}
	while (exit != 2);
	
	winnerScore = getWinner(score, numPlayers, &contWinners);
	
	if (contWinners == 1)
	{
		for (player = 0; player < numPlayers; player++)
		{
			if (score[player] == winnerScore)
			{
				printf("\nParab?ns %s, voc? venceu o jogo!\n", players[player]);
				
				break;
			}
		}
	}
	else
	{
		printf("\nParab?ns:\n\n");
		
		for (player = 0; player < numPlayers; player++)
		{
			if (score[player] == winnerScore)
			{
				printf("\t%s\n", players[player]);
			}
		}
		
		printf("\nVoc?s empataram em %d ponto(s).\n", winnerScore);
	}
	
	printf("\nFim de Jogo! Pressione ENTER para encerrar o programa.");
	fflush(stdin);
	getchar();
	
	return 0;
}

void getPlayer(int *controler, int numPlayers)
{
	if (*controler == numPlayers - 1)
	{
		*controler = 0;
	}
	else
	{
		*controler = *controler + 1;
	}
	
	return;
}

int getWinner(int *score, int numPlayers, int *contWinners)
{
	int biggerScore;
	int player;
	
	for (player = 0; player < numPlayers; player++)
	{
		if (!player)
		{
			biggerScore = score[player];
		}
		else if (score[player] > biggerScore)
		{
			biggerScore = score[player];
		}
	}
	
	for (player = 0; player < numPlayers; player++)
	{
		if (score[player] == biggerScore)
		{	
			*contWinners = *contWinners + 1;
		}
	}
	
	return biggerScore;
}

void sortSubject(char *subject)
{
	char subjects[5][50] = {"teste1", "teste2", "teste3", "teste4", "teste5"};
	int num;
	
	srand(time(NULL));
	
	// Get random numbers from 0 to 4
	num = rand() % 5;
	
	strcpy(subject, subjects[num]);
	
	return;
}
