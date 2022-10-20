#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<locale.h>
#define EspacoL -9
#define EspacoN -8



int main()
{
    setlocale(LC_ALL,"portuguese");

     system("color 3F");
     printf("\n\t\t\t\tProjeto Programação Linear - Simplex Padrão\n-----------------------------------------------------------------------------------------------------\n");
     printf("\nDesenvolvido por: Lucas Fernandes de Castro\nCurso: ADS 5 semestre");
     printf("\nProfessor: Andre de Lima");

      printf("\n\n\n\nAperte enter para continuar...");
      getchar();
      system("cls");





    system("color 5F");
    int tamVar,tamRest;

    printf("Quantas variaveis:");
    scanf("%d",&tamVar);

    fflush(stdin);

    printf("Quantas restrições:");
    scanf("%d",&tamRest);
    system("cls");

    float restricoes[tamRest][tamVar]; // lista de restrição
    float limitacao[tamRest]; //valores das limitações por linha
    float variaveis[tamVar]; // valor das variaveis
    char foMax[100];
    char concat[100]="",catInt[10]="", catFloat[10]="";
    int i = 0, j = 0 ;


    for(i=0; i<tamVar; i++)
    {
        fflush(stdin);
        printf("Informe o valor de X%d:",i+1);
        scanf("%f",&variaveis[i]);

        if(variaveis[i]<0)
        {

            while(variaveis[i]<0)
            {
                printf("Informe um valor positivo de X%d:",i+1);
                scanf("%f",&variaveis[i]);
            }
        }
        fflush(stdin);

        sprintf(catInt,"%d",i+1);
        sprintf(catFloat,"%.f",variaveis[i]);

        strcat(concat,catFloat);
        strcat(concat,"X");
        strcat(concat,catInt);

        if (i+1<tamVar) strcat(concat,"+");


    }
    strcpy(foMax,concat);
    printf("\nDefinido FoMax(Z)\n-------------------------------------------");
    printf("\nEnter para continuar..");
    getchar();
    system("cls");

    printf("\nInforme os valores das restrições Ex: X1=20 X2=20 X3=0 <= 120: \n\n");


    for(i=0; i<tamRest; i++)
    {
        printf("%d Restrição\n-------------------------------------",i+1);

        for(j=0; j<tamVar; j++)
        {

                printf("\nRestrição de X%d=",j+1);
                scanf("%f",&restricoes[i][j]);


            if(j==tamVar-1)
            {

                do
                {
                    printf("\n <=:");
                    fflush(stdin);
                    scanf("%f",&limitacao[i]);
                }
                while(limitacao[i]<=0);

            }

        }


    }

    bzero(concat,100);
    bzero(catInt,100);
    bzero(catFloat,100);


    char listViewRestricao[tamRest][100];


    //exibindo as restrição



    for(i=0; i<tamRest; i++)
    {

        for(j=0; j<tamVar; j++)
        {
            sprintf(catFloat,"%.f",restricoes[i][j]);
            sprintf(catInt,"%d",j+1);
            strcat(concat,catFloat);


            strcat(concat,"X");

            strcat(concat,catInt);


            if(j+1==tamVar)
            {
                strcat(concat,"<=");
                sprintf(catFloat,"%.f",limitacao[i]);
                strcat(concat,catFloat);


            }
            else
            {
                strcat(concat,"+");
            }
        }
        bzero(listViewRestricao[i],100);
        strcat(listViewRestricao[i],concat);
        bzero(concat,100);

    }
    fflush(stdin);
    fflush(stdout);

    system("cls");

    printf("\n\nFoMax(z)=%s",foMax);
    printf("\nSujeito a\n---------------------------------------");

    for(i=0; i<tamRest; i++)
    {

        printf("\n%s",listViewRestricao[i]);
    }
    printf("\n");
    for(i=0;i<tamVar;i++) printf("\nX%d>=0",i+1);





     printf("\n\nEnter para continuar..");
     getchar();

    system("cls");

    fflush(stdin);

    //negando as variaveis
    for(i=0; i<tamVar; i++)
    {
        variaveis[i]=(variaveis[i])*-1;
    }
    //criando linha de z
    int tamLinha = (tamRest+tamVar)+2;
    float linhaZ[tamLinha];
    linhaZ[0]=1;


    for(i=1; i<tamLinha; i++)
    {
        if(i<=tamVar)
        {
            linhaZ[i]= variaveis[i-1];
        }
        else if(i > tamVar)
        {
            linhaZ[i]=0;
        }
    }


    // matriz das restricao com folga
    float matRestComFolga[tamRest][tamLinha];

   int cont=1;

//mapeando matriz de restrição com folga
    for(i=0; i<tamRest; i++)
    {
        matRestComFolga[i][0]=0;

        for(j=1; j<tamLinha; j++)
        {
            if(j<=tamVar)
            {
                 matRestComFolga[i][j]=restricoes[i][j-1]; // dado restrição 10x1+20x2+x1=20 nesse momento -> 0 10 20 0 0 0 0
            }
            else if(j==tamLinha-1)
            {
               matRestComFolga[i][j]=limitacao[i];
            }
            else
            {
             matRestComFolga[i][j]=0;
            }

        }

         matRestComFolga[i][tamVar+cont]=1;

        cont++;

    }


     printf("\n\n");


     //criando a nova matriz
float matrizAtt[tamRest+1][tamLinha];
float menor = 99999999;
int columIn = -1;


  for(i=0; i<tamRest+1; i++)
    {


        for(j=0;j<tamLinha;j++)
        {
          if(i==0)
          {
              matrizAtt[i][j]=linhaZ[j];
              if(matrizAtt[i][j] < menor)
              {
                  menor =  matrizAtt[i][j];
                  columIn = j;

              }
          }else{
          matrizAtt[i][j]=matRestComFolga[i-1][j];
          }
        }

    }

int contFolga =1;
char z = 'Z';
char b = 'B';

      printf("\n\t\t\t\tALGORITMO 1\n----------------------------------------------------------------------------------------------------\n");
      //header
for(i=0;i<tamLinha;i++)
{
    if(i==0)
    {
        printf("%*c",EspacoL,z);
    }
    else if(i>0&&i<=tamVar)
    {
         printf("X%*d",EspacoL,i);
    }
    else if(i>tamVar && i<tamLinha-1)
    {
        printf("XF%*d",EspacoL,contFolga);
        contFolga++;
    }
    else if(i==tamLinha-1){
         printf("%*c",EspacoL,b);
    }

}
//exibindo
  for(i=0; i<tamRest+1; i++)
    {
       printf("\n");
        for(j=0;j<tamLinha;j++)
        {
          printf("%-10.1f",matrizAtt[i][j]);
        }

    }



int linhaOUT=-1;
menor=99999999;
float elementoPivo=0;


// pegando linha out e pivo
for(i=1;i<=tamRest;i++)
{   //coluna input                               //coeficiente
    float a = (matrizAtt[i][tamLinha-1] / matrizAtt[i][columIn]);
    if(a<=menor && a > 0)
    {
        menor = a;
        elementoPivo = matrizAtt[i][columIn];
        linhaOUT = i;


    }
}
//VB e VNB
float base;
int contbase=0;
int cont2=0;
int linha;
int tamCol= (tamRest+1);
char auxVar[100]="";
char varbasic[100]="";
char varNbasic[100]="";
contFolga=1;

while(1)
{
    for(int x=1; x<tamCol; x++)
    {
     if(matrizAtt[x][cont2]>1 || matrizAtt[x][cont2]<0)
     {
        contbase++;
     }
     else if(matrizAtt[x][cont2]==1)
     {
              contbase++;
              linha=x;
     }

    }
    if(contbase==1){

       if(cont2>0 && cont2<tamLinha-1)
       {
            base=matrizAtt[linha][tamLinha-1];
        if(cont2>tamVar)
        {
            sprintf(auxVar,"XF%d=%.1f\n",contFolga,base);
            contFolga++;
        }else sprintf(auxVar,"X%d=%.1f\n",cont2,base);




       strcat(varbasic,auxVar);
       }


       }else
       {
        if(cont2>0 && cont2<tamLinha-1)
       {
            if(cont2>tamVar)
        {
           sprintf(auxVar,"XF%d=0\n",contFolga,base);
           contFolga++;
        }else sprintf(auxVar,"X%d=0\n",cont2,base);

       strcat(varNbasic,auxVar);
       }
       }


    contbase=0;
    cont2++;

    if(cont2==tamLinha) break;
}

printf("\n\n\t\t\t\tSolução 1\n----------------------------------------------------------------------------------------------------\n");
printf("\n\nVALOR DE Z = 0  --> Solução não Ótima\n");
printf("\nElemento pivo[%.1f] na Coluna[%d]",elementoPivo,columIn+1);
printf("\n\nVB\n______________\n%s",varbasic);
printf("\n\n");
printf("VNB\n______________\n%s",varNbasic);





float vLinhaPivo[tamLinha];
float nLinhaPivo[tamLinha];
float auxLinhaPivo[tamLinha];
float novaLinha[tamLinha];

//mapeando a velha linha pivo
for(i=0;i<tamLinha;i++) vLinhaPivo[i] = matrizAtt[linhaOUT][i];

// mapeando a nova linha pivo
for(i=0;i<tamLinha;i++)
{
    nLinhaPivo[i]=(vLinhaPivo[i]/elementoPivo);
}

float novaMatriz[tamRest+1][tamLinha];


//criando a novaMatriz
for(i=0;i<tamRest+1;i++)
{

    for(j=0;j<tamLinha;j++)
        {

            if(i==linhaOUT)
            {
                novaMatriz[i][j]=nLinhaPivo[j];
            }else{

            novaLinha[j]= (matrizAtt[i][columIn]*(-1))*nLinhaPivo[j];
           novaLinha[j]= novaLinha[j]+matrizAtt[i][j];
           novaMatriz[i][j]=novaLinha[j];

            }

        }
}


int naoOtimo=0;
int contAlgorit =1;

while(1)
{

     contAlgorit++;
      printf("\n\n\n\n\n\t\t\t\tALGORITMO %d\n----------------------------------------------------------------------------------------------------\n",contAlgorit);
      contFolga=1;

 //header
for(i=0;i<tamLinha;i++)
{
    if(i==0)
    {
        printf("%*c",EspacoL,z);
    }
    else if(i>0&&i<=tamVar)
    {
         printf("X%*d",EspacoL,i);
    }
    else if(i>tamVar && i<tamLinha-1)
    {
        printf("XF%*d",EspacoL,contFolga);
        contFolga++;
    }
    else if(i==tamLinha-1){
         printf("%*c",EspacoL,b);
    }

}
//exibindo
  for(i=0; i<tamRest+1; i++)
    {
       printf("\n");
        for(j=0;j<tamLinha;j++)
        {
              if(i==0)
            {
                linhaZ[j]=novaMatriz[i][j];
            }


          printf("%-10.1f",novaMatriz[i][j]);
        }

    }



naoOtimo=0;

//se linha z existe negativo entao 1
for(i=0;i<tamLinha;i++)
{
     if(linhaZ[i]<0)
     {
         naoOtimo=1;
     }
}

//// bug no exercicio 8

bzero(auxVar,100);
bzero(varbasic,100);
bzero(varNbasic,100);
contFolga=1;

cont2=0;
while(1)
{
    for(int x=1; x<tamCol; x++)
    {
     if(novaMatriz[x][cont2]>1 || novaMatriz[x][cont2]<0)
     {
        contbase++;
     }
     else if(novaMatriz[x][cont2]==1)
     {
              contbase++;
              linha=x;
     }

    }
    if(contbase==1){

       if(cont2>0 && cont2<tamLinha-1)
       {
            base=novaMatriz[linha][tamLinha-1];
        if(cont2>tamVar)
        {
            sprintf(auxVar,"XF%d=%.1f\n",contFolga,base);
            contFolga++;
        }else sprintf(auxVar,"X%d=%.1f\n",cont2,base);




       strcat(varbasic,auxVar);
       }


       }else
       {
        if(cont2>0 && cont2<tamLinha-1)
       {
            if(cont2>tamVar)
        {
           sprintf(auxVar,"XF%d=0\n",contFolga,base);
           contFolga++;
        }else sprintf(auxVar,"X%d=0\n",cont2,base);

       strcat(varNbasic,auxVar);
       }
       }


    contbase=0;
    cont2++;

    if(cont2==tamLinha) break;
}


if(naoOtimo==1)
{
    printf("\n\n\t\t\t\tSolução %d\n----------------------------------------------------------------------------------------------------\n",contAlgorit);
    printf("\n\nVALOR DE Z = %.2f --> Solução Não Ótima",linhaZ[tamLinha-1]);

    for(i=0; i<tamRest+1; i++)
    {
        for(j=0;j<tamLinha;j++){matrizAtt[i][j]=novaMatriz[i][j];}
    }

}
else if(naoOtimo==0)
{
    printf("\n\n\t\t\t\tSolução %d\n----------------------------------------------------------------------------------------------------\n",contAlgorit);
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    printf("\n \t\t\tVALOR DE Z = %.2f --> Solução Ótima",linhaZ[tamLinha-1]);
    printf("\n\nVB\n______________\n%s",varbasic);
    printf("\n\n");
    printf("VNB\n______________\n%s",varNbasic);
    printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    printf("\nAperte enter para sair");
    getchar();
    exit(0);
    break;
}

// nova linha

linhaOUT=-1;
menor=99999999;
elementoPivo=0;

 for(i=0; i<tamLinha; i++)
    {
     if(matrizAtt[0][i]<menor)
     {
         menor = matrizAtt[0][i];
         columIn=i;
     }
    }

    menor=99999999;

for(i=1;i<=tamRest;i++)
{   //coluna input                               //coeficiente
    float a = (matrizAtt[i][tamLinha-1] / matrizAtt[i][columIn]);

    if(a<menor && a > 0)
    {
        menor = a;
        elementoPivo = matrizAtt[i][columIn];
        linhaOUT = i;


    }
}




printf("\n\nElemento pivo[%.1f] na Coluna[%d]",elementoPivo,columIn+1);

printf("\n\nVB\n______________\n%s",varbasic);
printf("\n\n");
printf("VNB\n______________\n%s",varNbasic);


for(i=0;i<tamLinha;i++) vLinhaPivo[i] = matrizAtt[linhaOUT][i];

for(i=0;i<tamLinha;i++)
{
    nLinhaPivo[i]=(vLinhaPivo[i]/elementoPivo);

}




for(i=0;i<tamRest+1;i++)
{

    for(j=0;j<tamLinha;j++)
        {

            if(i==linhaOUT)
            {
                novaMatriz[i][j]=nLinhaPivo[j];
            }else{

            novaLinha[j]= (matrizAtt[i][columIn]*(-1))*nLinhaPivo[j];
           novaLinha[j]= novaLinha[j]+matrizAtt[i][j];
           novaMatriz[i][j]=novaLinha[j];

            }

        }
}















}//fim while



    return 0;
}



void bzero(void *s, size_t n);
