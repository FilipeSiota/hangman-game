/* Jogo da forca */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

const int LIFES = 5;

int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	char palavra[21], letra, letTrue[25], letAll[25];
	int vidas = LIFES, confirmar = 0, tamPalavra, quantTrue = 0, quantAll = 0, c, i, win = 0, quantAcertado = 0;
	
	// pegando a palavra do Jogador 1
	do
	{
		system("cls");
		
		puts("##### Jogador 1 #####");
	
		printf("\nInforme uma palavra (máx. 20 caracteres): ");
		scanf("%21[^\n]", palavra);
		fflush(stdin);
		
		do
		{
			printf("\nConfirmar palavra '%s'?\n", palavra);
			printf("0) Não\n1) Sim\n\n>> ");
			scanf("%d", &confirmar);
			fflush(stdin);
			
			if (confirmar && confirmar != 1)
			{
				printf("\nOpção inválida!\n");
			}
			
		} while (confirmar && confirmar != 1);
		
		
	} while (!confirmar);
	
	tamPalavra = strlen(palavra);
	
	while (vidas && !win)
	{	
		system("cls");
		
		printf("Vidas: ");
	
		for (i = 0; i < vidas; i++)
		{
			printf("S2 ");
		}
		
		printf("\n\nLetras já informadas: ");
		
		for (i = 0; i < quantAll; i++)
		{
			if (i == quantAll - 1)
			{
				printf("%c", letAll[i]);
			}
			else
			{
				printf("%c - ", letAll[i]);
			}
		}
		
		printf("\n\nPalavra: ");
		
		quantAcertado = 0;
		
		if (quantTrue)
		{
			for (i = 0; i < tamPalavra; i++)
			{
				for (c = 0; c < quantTrue; c++)
				{
					if (palavra[i] == letTrue[c])
					{	
						break;
					}
				}
				
				if (palavra[i] == letTrue[c])
				{
					printf("%c ", letTrue[c]);
					
					quantAcertado++;
				}
				else
				{
					printf("_ ");
				}
			}
		}
		else
		{
			for (i = 0; i < tamPalavra; i++)
			{
				printf("_ ");
			}
		}
		
		if (quantAcertado == tamPalavra)
		{
			win = 1;
			
			printf("\n\nJogador 2 ganhou o jogo!\n\n");
		}
		else
		{
			do
			{
				printf("\n\nInforme uma letra: ");
				scanf("%c", &letra);
				fflush(stdin);
				
				for (i = 0; i < quantAll; i++)
				{
					if (letAll[i] == letra)
					{
						printf("\nVocê já informou esta letra!\n");
						
						i = 100;
						
						break;
					}
				}
			} while (i == 100);
			
			for (i = 0; i < tamPalavra; i++)
			{
				if (palavra[i] == letra)
				{
					i = 100;
					
					break;
				}
			}
			
			if (i == 100)
			{
				printf("\nVocê acertou a letra!\n");
				
				letTrue[quantTrue] = letra;
				
				quantTrue++;
			}
			else
			{
				printf("\nVocê errou a letra!\n");
				
				vidas--;
			}
			
			letAll[quantAll] = letra;
			quantAll++;
			
			if (vidas)
			{
				printf("\nPressione enter para adivinhar novamente.");
				getche();
			}
			else
			{
				printf("\nUps! Suas vidas acabaram.\n");
			}
			
		}
	}
	
	if (!vidas)
	{
		printf("\nJogador 1 ganhou o jogo!\n\n");
	}
	
	system("pause");
	return 0;
}
