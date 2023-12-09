#include <stdio.h>
#include <locale.h>
#include "read.c"

#define SALARIO 600.00

//Valores de peças extras
#define COTA_MEDIA  50
#define COTA_MAXIMA 80

//Valores a ser adicionados a cada cota atingida
#define ADICIONAL1 0.50
#define ADICIONAL2 0.75

float validaQuantidade (int quantidade)
{
	if (quantidade < COTA_MEDIA) 
		return 0;
	else if (quantidade >= COTA_MEDIA && quantidade <= COTA_MAXIMA) 
		return (quantidade - COTA_MEDIA) * ADICIONAL1;
	else 
		return ADICIONAL1 * (COTA_MAXIMA - COTA_MEDIA) + (quantidade - COTA_MAXIMA) * ADICIONAL2;
}

float calculaSalario (int *peca)
{
	return SALARIO + validaQuantidade (readInt ("Quantas peças foram criadas?", &*peca));
}

int modoSalario (int *contagemDePecas, int *contagemDeFuncionarios)
{
	int pecas;
	float salario = calculaSalario (&pecas);
	if (pecas == -255) return 1;
	*contagemDePecas += pecas;
	*contagemDeFuncionarios += 1;
	printf ("Salario: %.2f$\n\n", salario);
	return 0;
}

void mostraFinal(int x1, int x2)
{
	printf ("Peças %4d | %2d Funcionarios\n", x1, x2);
}

int main ()
{
	setlocale (LC_ALL, "Portuguese");

	typedef struct 
	{
		int pecasTotais = 0;
		int funcionarios = 0;
	}Lista;
	Lista registro;


	int opcao; //opção selecionada no menu.
	do
	{
		switch (readInt ("\nSelecione as opções com os seus números.\n\n Modo Salario ( 1 )\n  digite -255 para sair do modo\n\n Mostrar status ( 2 )\n\n Sair e mostrar status ( 0 )\n#", &opcao))
		{
			case 1:
				while (modoSalario (&registro.pecasTotais, &registro.funcionarios) == 0);
				break;
			case 2:
				mostraFinal(registro.pecasTotais, registro.funcionarios);
				break;
		}
	} while (opcao != 0);
	mostraFinal(registro.pecasTotais, registro.funcionarios);

	printf ("\n    __o  bici! \n  _/><_ \n (_)/(_) \n  ");
	return 0;
}