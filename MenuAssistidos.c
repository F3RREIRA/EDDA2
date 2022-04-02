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
int MenuAssistidos (void);
void ordenaIdadeDAT(void);
long int findSize(char file_name[]) ;
int quickSort(registro_ass *vetorRegistro, int start, int end); 
int partition(registro_ass *vetorRegistro, int start, int pivot) ;
void mostraIdade (registro_ass  *v, int tam);

/* Variáveis globais */
registro_ass 	informacao;
FILE      		*CSV;
FILE      		*DAT;
int       		i, cont=0;

/* Funções */
int partition(registro_ass *vetorRegistro, int start, int pivot) 
{
	registro_ass aux;
	int i; 
	int bigger = start;
	
	for (i = start; i < pivot; i++) {
		if ( atoll(vetorRegistro[i].datanasc) < atoll(vetorRegistro[pivot].datanasc) )  {
			aux = vetorRegistro[bigger];
			vetorRegistro[bigger] = vetorRegistro[i];
			vetorRegistro[i] = aux;
			bigger++;
		}
	}
	aux = vetorRegistro[bigger];
	vetorRegistro[bigger] = vetorRegistro[pivot];
	vetorRegistro[pivot] = aux;
	return bigger;
}
/* Função para ordenar o arquivo DAT */
int quickSort(registro_ass *vetorRegistro, int start, int end) 
{
	int pivot;
	if (start < end) {
		pivot = partition(vetorRegistro, start, end);
		quickSort(vetorRegistro, start, pivot-1);
		quickSort(vetorRegistro, pivot+1, end);
	}
}
/* Função para encontar tamanho do arquivo DAT */
long int findSize(char file_name[]) 
{ 
    long int res;
    /*Abre o arquivo para leitura*/
    FILE* fp = fopen(file_name, "r"); 
    /*Verifica se o arquivo existe*/
    if (fp == NULL) { 
        printf("Arquivo não encontrado!\n"); 
        return -1; 
    } 
    /*"Salta" para o fim do arquivo */
    fseek(fp, 0L, SEEK_END); 
    /*Calcula o tamanho do arquivo*/
    res = ftell(fp); 
    /*Fecha o arquivo*/
    fclose(fp); 
    return res; 
}
/* Função para ordenar arquivo DAT */
void ordenaIdadeDAT(void)
{
   FILE * ArqDAT;
   registro_ass  *vet;   
   int  ind=0;
   
   /* Alocar dinamicamente a memória para o vetor (vet) de registros (registro_ass)*/
   vet = (registro_ass  *) malloc (findSize("ASSISTIDOS.DAT"));
   if ( vet==NULL )
   {
   	  printf ("\nNão foi possível alocar %ld bytes em memória", findSize("ASSISTIDOS.DAT") );
   	  getch();
   	  system ("cls"); 
	  system ("MenuAssistidos.exe");
   }
   //debug
   //printf ("\n OSC.DAT tem %ld bytes", findSize("OSC.DAT") );    getch();

   /* Copiar o conteúdo do OSC.DAT para a memória alocada*/   
   /* abre o arquivo OSC.DAT para leitura (e depois transportá-lo para memória) */
   ArqDAT = fopen("ASSISTIDOS.DAT", "r");	
   if (  ArqDAT==NULL )
   {
      printf ("\nErro o ler 'ASSISTIDOS.DAT'!");
	  getch();
	  exit(0);		
   }
   while (!feof(ArqDAT)) /*Lê do arquivo para o vetor até o fim do arquivo*/
   {
   	 
   	 fread (&vet[ind], sizeof(registro_ass), 1, ArqDAT);
   	 if (!feof(ArqDAT))
   	    ind++;
   }
   fclose(ArqDAT);
   //debug
   printf ("\nLeu %i registros", ind ); getch();
   
   /*Ordena o vetor pela data de nascimento*/
   quickSort(vet, 0, ind-1) ;
   
   /* Mostra os idades ordenadas*/
   mostraIdade(vet, ind);
}
/*Função mostrar idades ordenadas*/
void mostraIdade (registro_ass  *v, int tam)
{
    int i;
	system ("cls"); printf ("\nIdades\n");
	for (i=0; i<tam; i++)
		printf ("[%3s]\n", v[i].datanasc);
	getch();
}
/* Função erro ao ler arquivo CSV */
void  errolerCSV (void)
{
	system ("cls");
	printf ("\n  ERRO AO LER ARQUIVO .CSV  ");
	getch();
	exit(0);
}
/* Função erro ao ler arquivo DAT */
void errogravarDAT (void)
{
	system ("cls");
	printf ("\n  ERRO AO GRAVAR NO ARQUIVO .DAT  ");
	getch();
	exit(0);
}

				/*----- CONVERSÃO DE CSV PARA DAT ------*/
/* Função para converter CSV para DAT */
void  ConverteCSVDAT (void)
{
	char  aux [10];
	int   linha=1;
	int   qtdRegistros;
	char  ch;
	CSV = fopen ("ASSISTIDOS.CSV", "r");
	if (CSV==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO 'ASSISTIDOS.CSV'.  ");
		getch();
		exit(0);
	}

	DAT = fopen ("ASSISTIDOS.DAT", "w");
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO CRIAR ARQUIVO 'ASSISTIDOS.DAT'.  ");
		getch();
		exit(0);
	}


	qtdRegistros=0;
	while ( !feof(CSV) ) /* lê o CSV até o fim do arquivo*/
	{
		
		if(linha ==1)   /*pular primeira linha (tira cabeçalho)*/
		{
			do
			{
				ch = fgetc(CSV);
			}
			while(ch != '\n');
		}

		/* trata o nome */
        i=0;
        do
		{
		  informacao.nomecompleto[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.nomecompleto[i++] != ';' );
	    informacao.nomecompleto[--i] = '\0';
        //debug
        printf ("\nNome: %s", informacao.nomecompleto);
        
        /* trata a data de nascimento*/
        i=0;
		do
		{
		  informacao.datanasc[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.datanasc[i++] != ';' );
	    informacao.datanasc[--i] = '\0';
        //debug
        printf ("\nData de Nascimento: %s", informacao.datanasc); 

		/* trata o cpf */
		i=0;
      	do
		{
		  informacao.cpf[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.cpf[i++] != ';' );
	    informacao.cpf[--i] = '\0';
        //debug
        printf ("\nCPF: %s", informacao.cpf); 
        
        /* trata o município*/
	    i=0;		 
        do
		{
		  informacao.municipio[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.municipio[i++] != ';');
	    informacao.municipio[--i] = '\0';
        //debug
        printf ("\nMunicípio: %s", informacao.municipio);
        
        /* trata o endereço*/
        i=0; 
        do
		{
		  informacao.logradouro[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.logradouro[i++] != ';');
	    informacao.logradouro[--i] = '\0';
        //debug
        printf ("\nEndereço: %s", informacao.logradouro); 
        
        /* trata o número */
		i=0;
    	do
		{
		  informacao.nro	[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.nro	[i++] != ';');
	    informacao.nro	[--i] = '\0';
        //debug
        printf ("\nNúmero	: %s", informacao.nro	);
        
        /* trata o complemento */
		i=0;
    	do
		{
		  informacao.complemento	[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.complemento	[i++] != ';');
	    informacao.complemento	[--i] = '\0';
        //debug
        printf ("\nComplemento	: %s", informacao.complemento);
        
        /*trata o bairro*/
		i=0;
    	do
		{
		  informacao.bairro[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.bairro[i++] != ';');
	    informacao.bairro[--i] = '\0';
        //debug
        printf ("\nBairro: %s", informacao.bairro);

		/* trata o celular */
		i=0;
        do
		{
		  informacao.celular[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.celular[i++] != ';' );
	    informacao.celular[--i] = '\0';
        //debug
        printf ("\nCelular: %s", informacao.celular);  
        
        /* trata o pet */
		i=0;
        do
		{
		  informacao.possuipet[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.possuipet[i++] != '\n');
	    informacao.possuipet[--i] = '\0';
        //debug
        printf ("\nPossui PET: %s", informacao.possuipet);
        
		/* Contabiliza um registro convertido */
		qtdRegistros++; 

		/* Grava no DAT */
	    /*Grava registro montado no DAT*/
        if ( fwrite (&informacao, sizeof(registro_osc), 1, DAT) != 1 )
	   	   errogravarDAT();
	    linha++;
	    if (qtdRegistros == 880) break;
		
	
	}
	fclose (CSV);
	fclose (DAT);
	printf ("\n[%i] registro(s) convertido(s) com sucesso!!\n", qtdRegistros);
	printf ("\n  TESTE TESTE TESTE");
	getch();
	
	    	
}
/*Funcão para mostrar conteúdo do arquivo DAT*/
void MostraDAT (void)
{
    FILE * REL;
    REL = fopen ("RELASSIS.TXT", "w"); /*Cria arquivo de relatório TXT*/
    if (REL == NULL)
    {
		system ("cls");
		printf ("\n  ERRO AO CRIAR ARQUIVO RELASSIS.TXT");
		getch();
		system ("cls"); 
        system ("MenuAssistidos.exe");
	}
	DAT = fopen ("ASSISTIDOS.DAT", "r"); /*Ler conteúdo do arquivo DAT*/
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO 'ASSISTIDOS.DAT'  ");
		getch();
		system ("cls"); 
        system ("MenuAssistidos.exe");
	}
	/*Mostra conteúdo do arquivo DAT*/
	printf ("\n----- CONTEÚDO DE 'ASSISTIDOS.DAT' ------");
	printf ("\nNOME		DATA NASCIMENTO		CPF		MUNICÍPIO		ENDEREÇO			NÚMERO	COMPLEMENTO		BAIRRO		CELULAR		POSSUI PET");
	printf ("\n-------------------------------------");
	/*Escreve conteúdo do arquivo DAT no arquivo TXT*/
	fprintf (REL, "\n----- CONTEÚDO DE 'ASSISTIDOS.DAT' ------");
	//fprintf ("\nNOME		DATA NASCIMENTO		CPF		MUNICÍPIO		ENDEREÇO			NÚMERO	COMPLEMENTO		BAIRRO		CELULAR		POSSUI PET");
	fprintf (REL, "\n-------------------------------------");
	
	while ( !feof(DAT) ) /* lê o DAT até o fim do arquivo */
	{
		
		fread (&informacao, sizeof(informacao), 1, DAT);		
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO .DAT  ");
			getch();
			system ("cls"); 
            system ("MenuAssistidos.exe");
		}
		if (!feof(DAT)) 	/* Mostra registro lido */
		{
			printf  ("\n%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n\n", informacao.nomecompleto, informacao.datanasc,informacao.cpf,informacao.municipio,informacao.logradouro,informacao.nro,informacao.complemento,informacao.bairro,informacao.celular,informacao.possuipet);		
			fprintf (REL,"\n%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n\n", informacao.nomecompleto, informacao.datanasc,informacao.cpf,informacao.municipio,informacao.logradouro,informacao.nro,informacao.complemento,informacao.bairro,informacao.celular,informacao.possuipet);		
		}
		//getch();
	}
	fclose (DAT);
	fclose (REL);
	getch();
	system ("notepad RELASSIS.TXT ");
}

/*Programa principal*/
int main(){ 

    /*Add acentos e Ç*/
	setlocale (LC_ALL, ""); 
	/*Tamanho da Janela*/
	//system("mode con:cols=75 lines=30");
	
	/*Declaração de variáveis*/
    int opcao; 
	/*Captura de opção no MenuPrincipal*/
    do{ 
        system ("cls"); 
        opcao = MenuAssistidos(); 

            switch (opcao) { 
                case 1: /*MenuAssistidos*/
					system ("cls"); 
                    system ("roda.exe");
                break; 
                case 2: 
                    MostraDAT(); 
                break; 
                case 3: 
                    ConverteCSVDAT();
				break; 
				case 4: 
                    ordenaIdadeDAT(); 
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
					system ("MenuAssistidos.exe"); 
                } 
    }while(1); 

return 0; 
}

/*Função MenuAssistidos*/
int MenuAssistidos (void){ 

	/*cores
	0 - Preto
	1 - Azul	2 - Verde	3 - Verde-água	4 - Vermelho	5 - Roxo	6 - Amarelo
	7 - Branco	8 - Cinza	9 - Azul claro	A - Verde Claro	B - Verde-água claro
	C - Vermelho Claro	D - Lilás	E - Amarelo Claro	F - Branco Brilhante*/
	
	/*cores do fundo e texto*/
    system("color F4");
    
	/* Declaração de variáveis*/
    int opc;
	
    printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDÁRIA\n"); 
    printf ("----------------------------------------------------------\n\n");
	printf ("		   << MENU ASSISTIDOS >>\n\n"); 
    printf ("      1 - Cadastro de novo assistido\n"); 
    printf ("      2 - Consulta assistidos cadastrados\n"); 
	printf ("      3 - Converter CSV para DAT\n");
    printf ("      4 - Ordenar OSC.DAT\n"); 
    printf ("      0 - Voltar ao MENU PRINCIPAL\n\n");
    printf ("----------------------------------------------------------\n");
    printf ("Digite a opção desejada e tecle [Enter]: ");
    scanf ("%d", &opc); 
    printf ("----------------------------------------------------------\n");
    getchar(); 

return opc; 
}
