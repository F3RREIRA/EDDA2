/*
  Programa: Cidade Solidária
  Data....: 31/05/2021
*/

/*Bibliotecas*/
#include <string.h>
#include <memory.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

     
/*Protótipos*/
int MenuAtendimento (void);

/*Programa principal*/
int main(){ 

    /*Add acentos e Ç*/
	setlocale (LC_ALL, ""); 
	/*Tamanho da Janela*/
	//system("mode con:cols=75 lines=30");
	
	/*Declaração de variáveis*/
    int opcao; 
	/*Captura de opção no MenuAtendimento*/
    do{ 
        system ("cls"); 
        opcao = MenuAtendimento(); 

            switch (opcao) { 
                case 1: /*MenuAtendimento*/
					system ("cls"); 
                    system ("roda.exe");
                break; 
                case 2: 
                    //MostraDAT(); 
                break; 
                case 3: 
                    //ConverteCSVDAT();
				break; 
				case 4: 
                    //OrdenaCNPJDAT(); 
                break;  
           		case 0: /*MenuPrincipal*/
				    //system ("cls"); 
                    system ("MenuPrincipal.exe");
                    exit(0);
                default: 
                
                    /*cores do fundo e texto*/
					system("color C0");
					/*system("cls");*/ 
					printf ("\n\t\tOPÇÃO INVÁLIDA!!!\n\n"); 
                    printf ("Tecle [Enter] para continuar..."); 
                    getchar();
                    system ("cls");
					system ("MenuAtendimento.exe"); 
                } 
    }while(1); 

return 0; 
}

/*Função MenuAtendimento */
int MenuAtendimento (void){ 

	/*cores
	0 - Preto
	1 - Azul	2 - Verde	3 - Verde-água	4 - Vermelho	5 - Roxo	6 - Amarelo
	7 - Branco	8 - Cinza	9 - Azul claro	A - Verde Claro	B - Verde-água claro
	C - Vermelho Claro	D - Lilás	E - Amarelo Claro	F - Branco Brilhante*/
	
	/*cores do fundo e texto*/
    system("color F2");
    
	/* Declaração de variáveis*/
    int opc;

	system("cls"); 
	printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDÁRIA\n"); 
    printf ("----------------------------------------------------------\n\n");
	printf ("		     << ATENDIMENTO >>\n\n"); 
    printf ("   Nome: xxxxxxxxxx	             Ordem: [0000/0000]\n\n"); 
    printf ("   CPF:  00000000000000\n\n\n"); 
 	printf ("      1 - Cesta entregue\n");
    printf ("      2 - Cesta não entregue\n");
    printf ("      0 - Voltar ao MENU PRINCIPAL\n\n");
    printf ("----------------------------------------------------------\n");
    printf ("Digite a opção desejada e tecle [Enter]: ");
    scanf  ("%d", &opc); 
    printf ("----------------------------------------------------------\n");
    getchar(); 

return opc; 
}
