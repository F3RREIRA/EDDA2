/*
  Programa: Cidade Solid�ria
  Data....: 31/05/2021
*/

/*Bibliotecas*/
#include <string.h>
#include <memory.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

     
/*Prot�tipos*/
int MenuDonativos (void);

/*Programa principal*/
int main(){ 

    /*Add acentos e �*/
	setlocale (LC_ALL, ""); 
	/*Tamanho da Janela*/
	//system("mode con:cols=75 lines=30");
	
	/*Declara��o de vari�veis*/
    int opcao; 
	/*Captura de op��o no MenuDonativos*/
    do{ 
        system ("cls"); 
        opcao = MenuDonativos(); 

            switch (opcao) { 
                case 1: /*MenuDonativos*/
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
					printf ("\n\t\tOP��O INV�LIDA!!!\n\n"); 
                    printf ("Tecle [Enter] para continuar..."); 
                    getchar();
                    system ("cls");
					system ("MenuDonativos.exe"); 
                } 
    }while(1); 

return 0; 
}

/*Fun��o MenuDonativos */
int MenuDonativos (void){ 

	/*cores
	0 - Preto
	1 - Azul	2 - Verde	3 - Verde-�gua	4 - Vermelho	5 - Roxo	6 - Amarelo
	7 - Branco	8 - Cinza	9 - Azul claro	A - Verde Claro	B - Verde-�gua claro
	C - Vermelho Claro	D - Lil�s	E - Amarelo Claro	F - Branco Brilhante*/
	
	/*cores do fundo e texto*/
    system("color 0E");
    
	/* Declara��o de vari�veis*/
    int opc;
	
	system("cls"); 
	printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLID�RIA\n"); 
    printf ("----------------------------------------------------------\n\n");
	printf ("	           << MENU DONATIVOS >>\n\n"); 
    printf ("      1 - Cadastro de novo donativo\n"); 
    printf ("      2 - Consulta donativos cadastrados\n"); 
    printf ("      0 - Voltar ao MENU PRINCIPAL\n\n"); 
    printf ("----------------------------------------------------------\n");
    printf ("Digite a op��o desejada e tecle [Enter]: ");
    scanf  ("%d", &opc); 
    printf ("----------------------------------------------------------\n");
    getchar(); 

return opc; 
}
