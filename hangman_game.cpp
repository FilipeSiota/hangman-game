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
#include <time.h>

#define LIMIT_WORD 21 // número máximo de caracteres para a palavra a ser adivinhada
#define QUANT_LIVES 6 // quantidade de vidas
#define MAX_PLAYERS 50 // número máximo de jogadores

void getPlayer(int *controler, int numPlayers);
int getWinner(int *score, int numPlayers, int *contWinners);
void sortSubject(char *subject);

int main()
{
	setlocale(LC_ALL, "English");

	// VARIÁVEIS PRINCIPAIS
	char players[MAX_PLAYERS][50]; // armazena os nomes do jogadores
	int score[MAX_PLAYERS] = { }; // placar
	int lives = QUANT_LIVES; // quantidade de vidas
	char wordToGuess[LIMIT_WORD]; // armazena a palavra que será adivinhada
	int wordLength; // guarda o tamanho da wordToGuess
	char subject[50];

	char letter; // armazena a letra informada
	char allLetters[27]; // armazena em um vetor todas as letras já informadas, podendo receber até todas as letras do alfabeto
	allLetters[0] = '*'; // só para verificar se alguma letra já foi informada;
	
	// VARIÁVEIS AUXILIARES (CONTADORES E OUTRAS PARA VERIFICAÇÃO)
	int numPlayers; // número de jogadores na partida
	int playerScored; // saber quem pontuou
	int exit, control_player = -1; // controla a saída e a vez do jogador
	int validateWord; // valida a wordToGuess
	int validateLetter; // valida a letter
	int win = 0; // valor diferente de 0, significa que o Jogador 2 ganhou
	int winnerScore; // armazena a pontuação do vencedor
	int contWinners; // armazena a quantidade de vencedores
	int contAllLetters = 0; // conta quantas letras já foram informadas para ajudar no index do vetor allLetters[]
	char contLettersGuessed; // conta quantas letras já foram adivinhadas
	char contSpecialChar = 0; // conta quantos espaços ou hífens têm para saber apenas a quantidade de letras

	// FOR (variables)
	int heart; // percorre as vidas
	int let; // percorre as letras do vetor allLetters[]
	int eachLet; // percorre as letras da wordToGuess
	int player; // percorre vetores relativos a players
	
	// PEGANDO OS NOMES DOS JOGADORES
	printf("########## HANGMAN GAME ##########\n\n");
	
	do
	{
		printf("Insert the number of players (max. 50): ");
		scanf("%d", &numPlayers);
		
		if (numPlayers < 1 || numPlayers > MAX_PLAYERS)
		{
			printf("\nInvalid value! Try again.\n");
		}
	}
	while (numPlayers < 1 || numPlayers > MAX_PLAYERS);
	
	system("cls");
	
	printf("########## HANGMAN GAME ##########\n\n");

	printf("RULES:\n\n");
	printf(">> One of the players will insert something to be guessed (related to a sorted subject)\nwhile the other players will try to guess it;\n");
	printf(">> The players, who will be guessing, have %d lives;\n", QUANT_LIVES);
	printf(">> It's highly recommended to play with CAPS LOCK (ON).\n\n");
	
	for (player = 0; player < numPlayers; player++)
	{
		printf("Name of Player %d: ", player + 1);
		fflush(stdin);
		scanf("%50[^\n]", players[player]);
	}
	
	do
	{
		lives = QUANT_LIVES;
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
	
			printf("RULES:\n\n");
			printf(">> You can digit the maximum of %d characters in the scope below;\n", LIMIT_WORD - 1);
			printf(">> Hyphens and blank spaces are allowed;\n");
			printf(">> Avoid using stresses.\n\n");
	
			printf("Hey, %s! It's your turn.\n\nInsert something to be guessed related to the subject '%s': ", players[control_player], subject);
			fflush(stdin);
			fgets(wordToGuess, LIMIT_WORD, stdin);
			
			wordLength = strlen(wordToGuess); // pega o tamanho da palavra informada
	
			wordToGuess[wordLength - 1] = '\0'; // tira o ENTER (\n) que veio com o fgets
	
			do
			{
				printf("\nConfirm '%s'?\n", wordToGuess);
	
				printf("\nInsert (1) for YES or (2) for NO: ");
				fflush(stdin);
				scanf("%d", &validateWord);
	
				if (validateWord != 1 && validateWord != 2)
				{
					printf("\nInvalid option! Try again.\n");
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
		while (lives > 0 && !win) // enquanto o Jogador 2 tiver vidas e não tiver ganhado o jogo ainda
		{
			system("cls");
			
			printf("OBSERVATION: When you find a '/' (slash), it means there's a blank space.\n\n");
			
			printf("########## Now it's the other players' turn ##########\n\n");
			
			// MOSTRANDO AS VIDAS DO JOGADOR 2
			printf("Lifes left ( ");
	
			for (heart = 0; heart < lives; heart++)
			{
				printf("S2 ");
			}
	
			printf(")");
			
			// MOSTRA AS LETRAS JÁ INFORMADAS, SE HOUVER ALGUMA
			if (allLetters[0] != '*')
			{
				printf("\n\nInserted letters >> ");
				
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
			
			// MOSTRA O TEMA
			printf("\n\nSubject: %s", subject);
			
			// MOSTRA A PALAVRA QUE ESTÁ SENDO ADIVINHADA
			printf("\n\nWord: ");
			
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
			
			printf("(%d letters)", wordLength - contSpecialChar); // mostra a quantidade de letras na palavra
			
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
					
					printf("\n\nInsert a letter: ");
					fflush(stdin);
					scanf("%c", &letter);
					
					// verifica se o Jogador 2 já informou essa letra
					for (let = 0; let < contAllLetters; let++)
					{
						if (letter == allLetters[let])
						{
							printf("\nInvalid character! You've already inserted this character. Try again.");
							
							validateLetter = 0;
							
							break;
						}
					}
	
					if (letter == '\n' || letter == ' ' || letter == '-')
					{
						printf("\nInvalid character! SPACE, ENTER and HYPHEN aren't valid characters. Try again.");
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
						printf("\nCongrats! The letter '%c' belong to the word.", letter);
						
						break;
					}
					else if (eachLet == wordLength - 1) // senão, se for a última repetição e não tiver entrado no IF anterior
					{
						printf("\nUps! The letter '%c' doesn't belong to the word.", letter);
						
						lives--; // como errou, perde uma vida
					}
				}
				
				printf("\n\nPress ENTER to continue.");
				fflush(stdin);
				getchar();
				
			}
			
		}
		
		if (!lives) // se as vidas do Jogador 2 acabaram
		{
			system("cls");
			
			printf("########## GAME OVER ##########\n\n");
			
			printf("The word was: %s\n", wordToGuess);
			
			printf("\nThere are no more lives.\nCongrats %s, you won this round!\n", players[control_player]);
			
			score[control_player]++;
		}
		else if (win == 100) // se o Jogador 2 ganhou
		{
			printf("\n\nCongrats, you guessed it and won this round!");
			
			printf("\n\nWho guessed it?\n");
			
			for (player = 0; player < numPlayers; player++)
			{
				printf("\n%d. %s", player + 1, players[player]);
			}
			
			do
			{
				printf("\n\nChoose an option: ");
				fflush(stdin);
				scanf("%d", &playerScored);
				
				if (playerScored < 1 || playerScored > numPlayers)
				{
					printf("\nInvalid option! Try again.");
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
		
		printf("\nPress ENTER to continue.");
		fflush(stdin);
		getchar();
		
		system("cls");
		
		printf("########## HANGMAN GAME ##########\n\n");
		
		printf("SCORE:\n\n");
		
		for (player = 0; player < numPlayers; player++)
		{
			printf("%s: %d\n", players[player], score[player]);
		}
		
		do
		{
			printf("\nDo you want to continue playing the game?\n\nInsert (1) for YES or (2) for NO: ");
			fflush(stdin);
			scanf("%d", &exit);
			
			if (exit < 1 || exit > 2)
			{
				printf("\nInvalid option! Try again.");
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
				printf("\nCongrats %s, you won the game!\n", players[player]);
				
				break;
			}
		}
	}
	else
	{
		printf("\nCongrats:\n\n");
		
		for (player = 0; player < numPlayers; player++)
		{
			if (score[player] == winnerScore)
			{
				printf("\t%s\n", players[player]);
			}
		}
		
		printf("\nIt's a draw! Each one scored %d point(s).\n", winnerScore);
	}
	
	printf("\nGAME OVER! Press ENTER to finish the program.");
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
	char subjects[5][50] = {"SPORTS", "FOODS", "MOVIES/SERIES", "COUNTRIES/STATES/CITIES", "ANIMALS"};
	int num;
	
	srand(time(NULL));
	
	// Get random numbers from 0 to 4
	num = rand() % 5;
	
	strcpy(subject, subjects[num]);
	
	return;
}
