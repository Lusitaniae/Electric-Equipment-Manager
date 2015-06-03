/* Trabalho Prático APROG-LEEC
   Jan-2014

O programa deverá ter o comportamento a seguir sugerido:
1.	x
	A posição deste equipamento na fila deve ser solicitada ao utilizador, no entanto, este deve ficar sempre posicionado 
	dentro do grupo com igual categoria. 
   
    IS DONE?f.	Verifica se o equipamento alguma vez foi utilizado pelo consumidor. No caso de ser a primeira vez pede os restantes 
	dados do equipamento. No caso de não ser a primeira vez acrescenta data e hora em que foi ligado.
2.	Desligar equipamento 
    x
	A posição onde se encontra o número do 
	equipamento não deve ficar desocupada, exceto se for o último da fila. Assim, todos os equipamentos que estão a seguir 
	ao equipamento que vai ser eliminado da fila (ou seja, desligado) têm de ser deslocados na fila (ver exemplo 2). 
    ±d.	Pergunta se quer eliminar o equipamento permanentemente. 
	
3.	
    b.	Exibe os dados bem como as datas e horas que cada equipamento dessa categoria esteve em funcionamento por ordem decrescente 
	de tempo total de uso. No caso do equipamento não se encontrar na fila deve também apresentar a mensagem "Equipamento desligado". 

*/

#include<stdio.h>
#include<stdlib.h> //to use exit(0)
#include<time.h>	
#include<string.h> 


#define MAX_EQ_DSP 100   //Limite máximo de equipamentos disponíveis para utilização
#define MAX_EQ_LIG  20   //Limite máximo de equipamentos ligados em simultâneo


typedef struct data {
	int dia; 
	char mes[20]; 
	int ano; 
	int hora; 
	int min; 
}Data; 

typedef struct equipamento { 
	int codDipositivo;
	char nomeEquipamento[40];
	int potencia;
	int categoria; 
	struct data ligado[100];
	struct data desligado[100];
}Equipamento;

iniciar_fila(int fila[])
{
      int i;
      for(i=1;i<=MAX_EQ_LIG;i++) fila[i]=0;
}

mostrar_fila(int fila[])
{
      int i;
      for(i=1;i<=MAX_EQ_LIG;i++) printf("%3d", fila[i]);
}

int valida_n(int fila[], int n) //se existe no vector 
{
    int i;
    for(i=1;i<=MAX_EQ_LIG;i++)
       if(fila[i]==n)	
          return 1;
		return 0;
}

int valida_ps(int f_equipamento_uso[], int ps) //se pos vazia
{
	if(f_equipamento_uso[ps] == 0)
		return 1;
	return 0;		  
}

psVazias(int f_equipamento_uso[], int ps)
{
	int i;
	for(i=0;i<ps;i++)
      	if(f_equipamento_uso[i] == 0){
      		printf("Nao pode inserir equipamento deixando posicoes anteriores em branco.");
      		getchar();
      		return 1;}
      	else	
    		return 0;
}
agrupado(int f_equipamento_uso[], int f_categoria[], int n, int pr, int ps)
{
	if(f_categoria[ps] == f_categoria[ps-1]){
		return 0;
	
		}
	return 1;
}

inserir(int f_equipamento_uso[], int f_categoria[], int n, int pr, int ps)
{
	// negar categorias su+periores depois das inferiores ( ordem crescente)      
	int i,j, temp_u,temp_pr,efi,zeros=0;
	for(i=MAX_EQ_LIG;i>ps;i--)
       {
            f_equipamento_uso[i]=f_equipamento_uso[i-1];
            f_categoria[i]      =f_categoria[i-1];
       }
       f_equipamento_uso[ps]=n;
       f_categoria[ps]=pr;
       
       /*
	if(f_equipamento_uso[ps]==0) 					//se ps vazia
		if(psVazias(f_equipamento_uso, ps)==0) 		//se nao deixa pos em branco
	            for(i=MAX_EQ_LIG;i>ps;i--){ //move elementos à dir da ps a ser inserido uma unidade
					f_equipamento_uso[i] = f_equipamento_uso[i-1];
                    f_categoria[i] = f_categoria[i-1];
               	 }
    	f_equipamento_uso[ps]=n;
        f_categoria[ps]=pr;*/

}
                         



inserirEqDISP(int n, int cat, Equipamento eq[]) //inserir na estrutura do Equipamento
{
    float potencia;
    char nome[40];
	eq[n].codDipositivo=n;
	eq[n].categoria=cat;
	//validate inputs
	printf("\nNome do Equipamento: ");		getchar();fgets(nome, 40, stdin);	strcpy(eq[n].nomeEquipamento, nome);
	printf("\nPotencia do Equipamento: ");	scanf("%f",&potencia);				eq[n].potencia=potencia;
	//getchar is used instead of fflush for OS portability. to prevent errors from \n
	
}
registarHora(int n, int  x, Equipamento eq[], Data data[])
{
	//char temp[30];		 
   const char * mes[] = { "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
 	struct tm *ptr;
        time_t lt;
        lt = time(NULL);
        ptr = localtime(&lt);
  	
	if(x==0){ //0:desligar		1:ligar
        eq[n].desligado[n].ano = (ptr->tm_year+1900);
 		eq[n].desligado[n].dia = (ptr->tm_mday); 	//printf("%i", (ptr->tm_mday));
 		eq[n].desligado[n].hora = (ptr->tm_hour); 	//printf("%i", (ptr->tm_hour));
 		eq[n].desligado[n].min = (ptr->tm_min); 	//printf("%i", (ptr->tm_min)); getchar();
		 
 		mktime(localtime(&ptr)); //define meses como strings 
 		strcpy(eq[n].ligado[n].mes, mes[ptr->tm_mon-1]); 
		  		 
    }else{
		eq[n].ligado[n].ano = (ptr->tm_year+1900);
 		eq[n].ligado[n].dia = (ptr->tm_mday); 	//printf("%i", (ptr->tm_mday));
 		eq[n].ligado[n].hora = (ptr->tm_hour); 	//printf("%i", (ptr->tm_hour));
 		eq[n].ligado[n].min = (ptr->tm_min); 	//printf("%i", (ptr->tm_min)); getchar();
		 
 		mktime(localtime(&ptr)); //define meses como strings 
 		strcpy(eq[n].ligado[n].mes, mes[ptr->tm_mon-1]);   
		}	
}	 	   
 		   
 		   
retirar(int n, int x[], int y[]) //retirar elemento n de x e y
{
 		 int i;
 		 for(i=0;i<20;i++)
				if(x[i] == n)
				{
	   					   x[i]=0; 	//eq_uso=0
	   					   y[i]=0;	//categ=0
	   					   return 1;  
	   			 }
		 return 0;	   
						   
}
removerDSP(int n, Equipamento eq[])
{
	strcpy(eq[n].nomeEquipamento, NULL);
	strcpy(eq[n].categoria, NULL);
	strcpy(eq[n].codDipositivo, NULL);
	strcpy(eq[n].potencia, NULL);
	strcpy(eq[n].nomeEquipamento, NULL);
	eq[n].ligado[n].ano =0;
 	eq[n].ligado[n].dia =0; 	//printf("%i", (ptr->tm_mday));
 	eq[n].ligado[n].hora = 0; 	//printf("%i", (ptr->tm_hour));
 	eq[n].ligado[n].min = 0; 	//printf("%i", (ptr->tm_min)); getchar();
	strcpy(eq[n].ligado[n].mes, NULL);   
}
unblanker(int n, int x[], int y[]) //remover espaços em branco ao remover elementos
{
	int j;
	for(j=0;j<=20;j++)
		if(x[j++] != 0 && x[j] == 0)
			{
			x[j] = x[j+1]; x[j+1] = 0;
			y[j] = y[j+1]; y[j+1] = 0;				
			}
}

ordenar(int n, int vec[])
{
	int troca, i, j;
	float aux;
	for(i=n-1; i>0; i--) {
    	troca = 0;
        	for (j=0 ; j<i; j++) {
            	//Alterar <> para crescente/decrescente
        		if (vec[j] < vec[j+1]) {
                	aux = vec[j];   vec[j] = vec[j+1];      vec[j+1] = aux;
                	troca = 1;
                    }
            }
            if (!troca) return;
    }
}						  
 
mostrar(int cat, Equipamento eq[],int f[])
{
    int i,equipCat=0;
	char status[11];

	for(i=0;i<MAX_EQ_DSP;i++)
		if(eq[i].categoria == cat)
  		    equipCat++;
  		    
	if(equipCat == 0)
	    printf("Equipamento inexistente para a categoria %i", cat);
	else{    
		int lista[equipCat];               
		
		for(i=0;i<MAX_EQ_DSP;i++)
			if(eq[i].categoria == cat)
				lista[i]=eq[i].codDipositivo;						   				   						   
		
		//ordenar(equipCat, lista);
		printf("	Equipamento Disponivel em %i:", cat);
		printf("\nNr Cod  Nome	Potencia	  Estado"	);
		for(i=1;i<=equipCat;i++){
			if(valida_n(f, eq[i].codDipositivo)) 
				strcpy(status,"LIGADO");	 
			else 
				strcpy(status,"DESLIGADO"); 
			
			
			printf("\n%i. (%i) %s	%i W		%s",i,eq[i].codDipositivo, eq[i].nomeEquipamento, eq[i].potencia,status );
			
		}
	}	
	getchar();		
		 
}

int somaConsumo(Equipamento eq[], int f_equipamento_uso[]) //more useless unworkable arsehit
{
	int i,j,soma=0,equipCat=0;
	char status[11];
	int lista[20];

	for(i=0;i<MAX_EQ_LIG;i++)
		if(f_equipamento_uso[i] != 0)
			for(j=0;j<MAX_EQ_DSP;j++)
  		    	lista[j]=eq[i].potencia;
  		    
	for(i=0;i<20;i++)
		soma+=lista[i];
	return(soma);
}
char potenciaSug(int consumo)
{
	char sug[19];
	if(consumo<1150)
		strcpy(sug, "minimo 1.15!");
	if(consumo >= 1150 && consumo <= 20700)
		strcpy(sug, "20.7");
	if(consumo > 20700 && consumo <=41400)
		strcpy(sug, "41.4");
	if(consumo>41400)
		strcpy(sug, "superior a 41.4");
		
}


main()
{
      char op;
      int f_categoria[MAX_EQ_LIG], f_equipamento_uso[MAX_EQ_LIG];
      int n, pr, ps, res_n, res_ps;
      int nr,sn;
      int tconsumo=0, spotencia=0;
      int f_equipamento_dsp[MAX_EQ_DSP];
      Equipamento equipamento[MAX_EQ_DSP];
      Data data[MAX_EQ_DSP];
      char categorias[][3]={"AA", "A+", "B"};

      system("title SiPEc - Simulador de Potencia Eletrica");

      iniciar_fila(f_categoria);
      iniciar_fila(f_equipamento_uso);
      //Equipamentos de amostra
      strcpy(equipamento[1].nomeEquipamento, "iPhone "); equipamento[1].categoria=1; equipamento[1].codDipositivo=33; equipamento[1].potencia=40;
      strcpy(equipamento[2].nomeEquipamento, "Mac Pro"); equipamento[2].categoria=1; equipamento[2].codDipositivo=40; equipamento[2].potencia=600;
      strcpy(equipamento[3].nomeEquipamento, "iMac 19"); equipamento[3].categoria=1; equipamento[3].codDipositivo=50; equipamento[3].potencia=360;
      strcpy(equipamento[4].nomeEquipamento, "OSX    "); equipamento[4].categoria=1; equipamento[4].codDipositivo=62; equipamento[4].potencia=85;
			

      do
      {
          res_n=res_ps=0;
          system("cls");
          printf("\n\n                                       Equipamento em Uso\n");
          printf("\n        Categoria");mostrar_fila(f_categoria); // mostrar AA, A+, BB em vez de 1 2 3 
          printf("\n                  ____________________________________________________________");
          printf("\n      Equipamento");mostrar_fila(f_equipamento_uso);
          printf("\n                  ____________________________________________________________");
          printf("\n          Posicao  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20");
          printf("\n\nTotal Consumo: %i W. \nPotencia Sugerida: %c kW.", tconsumo, spotencia/*somaConsumo(equipamento, f_equipamento_uso), potenciaSug(somaConsumo(equipamento, f_equipamento_uso))*/);
		  //
          printf("\n\n\n\nGestao de Equipamentos");
          printf("\n\n(1) Ligar Equipamento");
          printf("\n(2) Desligar Equipamento");
          printf("\n(3) Mostrar detalhe dos equipamentos de uma categoria (ligados, desligados)");
          printf("\n(0) Sair");
          printf("\nOpcao?");
	   	  
          scanf("%c",&op);
          switch(op)
          {
                case '1':
                     printf("\n>>> Ligar equipamento <<<");
                     do{
                         if(res_n==1) printf("\nJa existe.");
						 printf("\nNumero? ");scanf("%d",&n);
                         res_n=valida_n(f_equipamento_uso,n);
                     }while((n<1 || n>99) || res_n==1);
                     
                     printf("\nCategoria? ");scanf("%d",&pr);
                     while(pr<1 || pr>3){
					 	printf("Apenas pode escolher a categoria 1(AA), 2(A+) ou 3(B): ");
						scanf("%d",&pr);
						}		
                     
                     do{
                         printf("\nPosicao? ");scanf("%d",&ps);
                         res_ps=valida_ps(f_equipamento_uso,ps);
                         if(ps == 20 && f_equipamento_uso[20] != 0){
                         	registarHora(f_equipamento_uso[20], 0, equipamento, data); //is it working? not
                         	printf("Fila Cheia. O equipamento na posicao 20 vai ser desligado.");
                         	printf("%i", equipamento[1].desligado[1].dia); //equipamento de f_eq_uso, necessario descobrir id do struct equipamento
                         	getchar();
							}	
                     }while(ps<1 || ps>20); //alterado. Agora pode-se substituir valor actual em ps movendo tudo à dir e eliminando o último
                      inserir(f_equipamento_uso,f_categoria,n,pr,ps);
                      inserir(f_equipamento_dsp,f_categoria,n,pr,ps);
                      if(valida_n(f_equipamento_dsp,n))
					      {
						   	inserirEqDISP(n, pr, equipamento);
						   	registarHora(n, 1, equipamento, data);
							//inserir hora ligado   
							}
				      else{
				      	  registarHora(n, 1, equipamento, data);  
						  }	   
                     break;
                     
                case '2':
                     printf("\n>>> Desligar equipamento <<<");
                     do{
			 			   printf("\nNumero? ");scanf("%d",&nr);
					 }while(nr<1 || nr>99);
					 if(retirar(nr, f_equipamento_uso, f_categoria)){ 
						//se remover com sucesso
							registarHora(nr, 0, equipamento, data); 
							unblanker(nr, f_equipamento_uso, f_categoria);				
							//Imprimir Eq Disponiveis para verificar função abaixo
							printf("\nRemover dos Equipamentos Disponiveis? S/N");
							scanf("%c", &sn);
							getchar();
							if(sn == 'S' || sn == 's'){
					   		 		removerDSP(equipamento, nr); getchar(); //retirar(nr, f_equipamento_disp, f_categoria);
  		 					}else{}
  		 					
						}else{
							printf("Equipamento nao existe.");
							getchar();	   
							}					
							
                    break;
                case '3':
                     printf("\n>>> Mostrar detalhe dos equipamentos de uma categoria (ligados e desligados) <<<");
                     printf("\nCategoria? ");scanf("%d",&pr); //1AA 2A+ 3B
                     while(pr<1 || pr>3){
					 	printf("Apenas pode escolher a categoria 1(AA), 2(A+) ou 3(B): ");
						scanf("%d",&pr);
						}
                     mostrar( pr, equipamento, f_equipamento_uso);
                     break;
                case '0':
                     printf("\nTerminando....");
                     exit(0);  
					 break; //useless                
                default:
                     printf("\nERRO - Opcao invalida!");
                     getchar();
                     //break;
          }
      }while(op!='0');
      getchar();
}
