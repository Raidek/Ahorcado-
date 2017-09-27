#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MaxL 50 //Lineas max de fichero.
#define MaxC 25 //Maximos caracteres por linea.
#define MaxI 51 //Total de letras del abecedario mas ',' para el array de actualiza lista

//################################################################################################################################################################################################
//###################################################################PROTOTIPOS DE FUNCIONES OBLIGATORIAS#########################################################################################
//################################################################################################################################################################################################


void cabecera();//imprime nombre y numero de matricula.

void borrarConsola();//Despeja la consola.

int longCad(char palabra[MaxC]);//Devuelve el nº de letras de la palabra a adivinar.

int cadenasIguales(char palabra[MaxC],char resolverPalabra[MaxC]);//Si el usuario decide resolver la palabra se compara la entrada con la palabra  a adivinar.

void iniciaCad(char cadGuion[MaxC],int tamPalabra);//Rellena una cadena con tantos '-' como nº de letras de la palabra adivinar.

int actualizaCad(char palabra[MaxC],char cadGuion[MaxC],char letra);//Si la letra esta en la palabra a adivinar, introduce en la cadena de guiones la letra en su
                                                                    //espacio correspondiente.He modificado la funcion a tipo int para que devuelva el nº de guiones
                                                                    //que se han sustituido ya que por ejemplo la letra 'r' sustituye dos guiones en la palabra 'perro',
                                                                    //entonces si se ha realizado un cambio la funcion devolvera un nº distinto de 0,por lo cual la
                                                                    //letra del usuario era correcta, y si devuelve cero significa que no se ha sustituido ningun guion
                                                                    //entonces la letra del usuario era erronea y por lo tanto avisar que introduzca otra.
                                                                    //(ESTO AHORRA HACER UNA FUNCION AUXILIAR).

int actualizaLista(char LetrasIndroducidas[MaxI],char letra);//Crea una lista con las letras que ha introducido el usuario y en caso de que introduzca una de la
                                                             //lista avisara de que esa letra ya ha sido introducida, y pedira que se introduzca otra.
                                                             //(ESTO AHORRA HACER UNA FUNCION AUXILIAR).

void imprimeFigura(int NumError);//Imprime la figura correspondiente al numero de errores.

//################################################################################################################################################################################################
//###################################################################PROTOTIPOS DE FUNCIONES AUXILIARES###########################################################################################
//################################################################################################################################################################################################

void palabraAislada(char fichero[MaxL][MaxC],char palabra[MaxC], int linea);//Copia la palabra propuesta de la matriz
                                                                            //fichero en la cadena palabra.

int imprimirMenu();//Donde se elige la tematica de la palabra

void aperturaFichero(char fichero[MaxL][MaxC],int opcion);//Saca las palabras del .txt y las copia en la matriz fichero.

int numAleatorio();//Devuelve un numero aleatorio para la eleccion de una palabra.

int informacion(int numError,char letrasIndroducidas[MaxI],char cadGuion[MaxC],int tematica);//Imprime la informacion que se menciona en el enunciado y tambien la tematica antes de cualquier
                                                                                             //lectura, y ademas devuelve '1' si el usuario quiere resolver o '0' si quiere seguir introduciendo
                                                                                             //letras.

void comprobador(char *letra,char resolverPalabra[MaxC],int elegir);//Compruba que tanto en la entrada de letras como en el array para resolver la palabra, esta conformada solo por
                                                                    //letras, en caso de que haya un caracter distinto de una letra avisara y se repetira la entrada de el dato.
                                                                    //Para elegir que se va a comprobar esta el valor int elegir, que sera '1' si va comprobar la letra metida por
                                                                    //el usuario o'0' si va comprobar el array de caracteres con el que el usuario quiere resolver la palabra.
                                                                    //Tras comprobar que son letras, automaticamente se lanzara la funcion 'Conversor'.

void conversor(char *letra,char resolverPalabra[MaxC],int elegir);//Toda entrada de usuario de tipo char,pasa por esta funcion y en el caso de que haya introducido cualquier
                                                                  //caracter en mayuscula, se convertira en minuscula, mediante una comprobacion, si por ejemplo se introduce
                                                                  //'A', se hara esta operacion 'A'+32, que dara como resultado 'a'; esto es mejor ya que en vez de hacer un
                                                                  //switch de todo el abecedario, se hace una simple operacion para convertir mayusculas en minusculas.
                                                                  //Para elegir que se va a comprobar esta el valor int elegir, que sera '1' si va comprobar la letra metida
                                                                  //por el usuario o'0' si va comprobar el array de caracteres con el que el usuario quiere resolver la palabra.

//################################################################################################################################################################################################
//################################################################################# MAIN #########################################################################################################
//################################################################################################################################################################################################

int main()
{
 int i,numLetras,linea,opcionMP,pregunta,igual,numError,letrasCorrectas,opcionTrasAcabar;
 char fichero[MaxL][MaxC];//La matriz fichero es donde se guardaran todas las palabras del .txt
 char palabra[MaxC];//Palabra que se debe adivinar
 char cadGuion[MaxC];//cadena con tantos guiones como letras tiene la palabra a adivinar
 char letraUSR;//letras que va a introducir el usuario para adivinar la palabra
 char letrasIndroducidas[MaxI];//Son 10 letras solo pero usaremos ',' como separacion entre ellas por eso necesitamos mas de 10 espacios en la cadena
                               //y tambien inicializamos a NULL para indicar que todavia no se ha introducido ninguna letra.
 char resolverPalabra[MaxC];//Matriz donde se guardara la entrada del usuario si quiere resolver

 do//Por si al adivinar o fallar la palabra el usuario quiere finalizar
   {
     do
       {
         borrarConsola();
         cabecera();
         fflush( stdin );
         opcionMP=imprimirMenu();
         aperturaFichero(fichero,opcionMP);
         do
           {
             linea=numAleatorio();
             palabraAislada(fichero,palabra,linea);
             numLetras=longCad(palabra);
             iniciaCad(cadGuion,numLetras);
             letrasIndroducidas[0]='\0';//Por si hay mas de una iteraccion que se reinicie el valor NULL que es el centinela de impresion a la posicion cero
             i=0;
             numError=0;
             while(numLetras!=i && numError!=10)
               {
                 borrarConsola();
                 printf("\n");
                 pregunta=informacion(numError,letrasIndroducidas,cadGuion,opcionMP);
                 if(pregunta==1)//El usuario quiere seguir introduciendo letras
                   {
                     printf("\nIntroduzca letra: ");
                     scanf(" %c",&letraUSR);
                     comprobador(&letraUSR,resolverPalabra,1);
                     fflush( stdin );
                     conversor(&letraUSR,resolverPalabra,1);
                     while(!actualizaLista(letrasIndroducidas,letraUSR))
                       {
                         printf("\nEsa letra ya ha sido introducida introduzca otra: ");
                         scanf(" %c",&letraUSR);
                         fflush( stdin );
                       }
                     letrasCorrectas=actualizaCad(palabra,cadGuion,letraUSR);
                     if(letrasCorrectas!=0)
                       {
                         //La letra era correcta
                         printf("\n\tLETRA CORRECTA :D \n\n");
                         i=i+letrasCorrectas;
                       }
                     else
                       {
                         //La letra no era correcta
                         printf("\n\tLETRA INCORRECTA :(\n\n");
                         numError++;
                       }
                     system("pause");
                   }
                 else//El usuario ha decidido resolver
                   {
                     fflush( stdin );//He puesto fflush ya que se saltaba el gets
                     printf("\nLa palabra a adivinar es: ");
                     gets(resolverPalabra);
                     comprobador(&letraUSR,resolverPalabra,0);
                     conversor(&letraUSR,resolverPalabra,0);
                     igual=cadenasIguales(palabra,resolverPalabra);
                     if(igual)
                       {
                         i=numLetras;//Para salir del bucle
                       }
                     else
                       {
                         numError=10;//Para salir del bucle
                       }
                   }
               }
             borrarConsola();
             if(numLetras==i)
               {
                 printf("\n\n\n\t\t#####################################");
                 for(i=0;i<=numLetras;i++) printf("%c",'#');
                 printf("\n\t\tFELICIDADES HAS ADIVINADO LA PALABRA:%s\n",fichero[linea]);
                 printf("\t\t#####################################");
                 for(i=0;i<=numLetras;i++) printf("%c",'#');
                 printf("\n\n");
               }
             else if( numError==10)
               {
                 printf("\n\n\n\nPalabra incorrecta,la palabra es:%s\n\n",fichero[linea]);
               }
             printf("%cQuiere otra palabra de la misma tematica(1),cambiar de tematica(2) o finalizar(0)?: ",168);//168==¿, pero si pongo '¿' me imprime otro signo
             scanf("%d",&opcionTrasAcabar);
             while(opcionTrasAcabar>2 || opcionTrasAcabar<0)
               {
                 printf("\nEsa opcion no existe, porfavor introduzca 1 o 2 o 0 si quiere otra palabra de la misma tematica, cambiar de tematica\no finalizar, respectivamente: ");
                 fflush( stdin );
                 scanf("%d",&opcionTrasAcabar);
               }
           }while(opcionTrasAcabar==1);
       }while(opcionTrasAcabar==2);
   }while(opcionTrasAcabar!=0);
 exit(0);
}

//################################################################################################################################################################################################
//################################################################################ FUNCIONES OBLIGATORIAS ########################################################################################
//################################################################################################################################################################################################

void cabecera()//##################################################################################### CABECERA ##########
{
 printf("NOMBRE:GONZALO GONZALEZ BULLIDO\nMATRICULA: BN0027\n\n");
}

void borrarConsola()//################################################################################ BORRAR CONSOLA ####
{
  system("cls");
  //Esta funcion la he sacado del la libreria stdio.h, puesto que limpia la consola
  //sin tener que poner saltos de linea sea cual sea el tamaño en el que se abra la
  //consola ya que en cada ordenador el tamaño de la consola varia por lo tanto no
  //se podria poner un numero fijo de saltos de linea.
}

int longCad(char palabra[MaxC])//#################################################################### LONG CAD ###########
{
 int cont=0;
 while(palabra[cont]!='\0')//En vez de poner '\0' tambien se podria poner NULL
  {
   cont++;
  }
 return cont;
}

int cadenasIguales(char palabra[MaxC],char resolverPalabra[MaxC])//################################# CADENAS IGUALES #####
{
 int acertada=0,i=0;
 while(palabra[i]!='\0' && resolverPalabra[i]!='\0' && palabra[i]==resolverPalabra[i])
  {
   i++;
  }
 if(palabra[i]==resolverPalabra[i]) acertada=1;
 return acertada;
}

void iniciaCad(char cadGuion[MaxC],int tamPalabra)//################################################ INICIA CAD ##########
{
 char gui='-';
 int i;
 for(i=0;i<tamPalabra;i++) cadGuion[i]=gui;
 cadGuion[i]='\0';//Pongo caracter nulo para poder imprimir luego solo los guiones
}

int actualizaCad(char palabra[MaxC],char cadGuion[MaxC],char letra)//############################### ACTUALIZA CAD #######
{
 int pos,resul=0;
 for(pos=0;palabra[pos]!='\0';pos++)//Hacemos ciclo for porque la letra puede estar dos veces en una misma palabra.EJM: 'r' en perro
 {
    if(palabra[pos]==letra)
  {
    cadGuion[pos]=letra;
    resul++;//La letra del usuario era correcta
  }
 }
 return resul;
}

int actualizaLista(char letrasIndroducidas[MaxI],char letra)//##################################### ACTUALIZA LISTA ######
{
 int i=0;
 while(letrasIndroducidas[i]!=letra && letrasIndroducidas[i]!='\0')
  {
    i++;
  }
  if(letrasIndroducidas[i]=='\0')//La letra no se habria introducido se procede a incluirla en la lista
  {
   if(i==0)//Para la primera letra
    {
     letrasIndroducidas[i]=letra;
     letrasIndroducidas[i+1]='\0';
     return 1;
    }
   else//Demas letras
   {
    letrasIndroducidas[i]=',';
    letrasIndroducidas[i+1]=letra;
    letrasIndroducidas[i+2]='\0';//Ponemos '\0' para saber en una proxima llamada que hemoos llegado al final y tambien para imprimir hasta donde queremos
    return 1;
   }
  }
  return 0;//Ya se habia introducido esta letra
}

void imprimeFigura(int numError)//################################################################# IMPRIMIR FIGURA ######
{
  switch( numError )
  {
  case 0: printf("\t.......\n");
          printf("\t. .\n");
          printf("\t. .\n");
          printf("\t. .\n");
          printf("\t. .\n");
          printf("\t. .\n");
          printf("\t. .\n");
          printf("\t.......\n");
          break;

  case 1: printf("\n");
          printf("\n");
          printf("\n");
          printf("\n");
          printf("\n");
          printf("\t------\n");
          break;

  case 2:printf("\n");
         printf("\t| \n");
         printf("\t| \n");
         printf("\t| \n");
         printf("\t| \n");
         printf("\t------\n");
         break;

  case 3:printf("\t_____\n");
         printf("\t|/ \n");
         printf("\t| \n");
         printf("\t| \n");
         printf("\t| \n");
         printf("\t------\n");
         break;

  case 4:printf("\t_____\n");
         printf("\t|/ O \n");
         printf("\t| \n");
         printf("\t| \n");
         printf("\t| \n");
         printf("\t------\n");
         break;

  case 5:printf("\t_____\n");
         printf("\t|/ O \n");
         printf("\t|  | \n");
         printf("\t|  | \n");
         printf("\t| \n");
         printf("\t------\n");
         break;

  case 6:printf("\t_____\n");
         printf("\t|/ O \n");
         printf("\t| /| \n");
         printf("\t|  | \n");
         printf("\t| \n");
         printf("\t------\n");
         break;

  case 7:printf("\t_____\n");
         printf("\t|/ O \n");
         printf("\t| /|\\\n");
         printf("\t|  | \n");
         printf("\t| \n");
         printf("\t------\n");
         break;

  case 8:printf("\t_____\n");
         printf("\t|/ O \n");
         printf("\t| /|\\\n");
         printf("\t|  | \n");
         printf("\t| / \n");
         printf("\t------\n");
         break;

  case 9:printf("\t_____\n");
         printf("\t|/ O \n");
         printf("\t| /|\\\n");
         printf("\t|  | \n");
         printf("\t| / \\\n");
         printf("\t------\n");
         break;

  default: break;
  }
}

//################################################################################################################################################################################################
//################################################################################ FUNCIONES AUXILIARES ##########################################################################################
//################################################################################################################################################################################################


void palabraAislada(char fichero[MaxL][MaxC],char palabra[MaxC],int fila)//###################### PALABRA AISLADA ################
{
 int i=0;
 while(fichero[fila][i]!='\0')
    {
        palabra[i]=fichero[fila][i];
        i++;
    }
 palabra[i]='\0';//Pongo caracter nulo para tener un valor centinela al luego comparar
}

int imprimirMenu()//############################################################################# IMPRIMIR MENU ##################
{
 int opcion;

 printf("\tMENU PRINCIPAL\n\n");
 printf("\t(1) Animales\n\n");
 printf("\t(2) Profesiones\n\n");
 printf("\t(3) Nombres\n\n");
 printf("\t(4) Paises\n\n");
 printf("\t(0) Salir\n\n");//Por si el usuario queria finalizar pero se equivoca y elige volver al menu principal
 printf("\nElija una tematica o salga poniendo el numero correspondiente: ");
 scanf("%d",&opcion);
 while(opcion>4 || opcion<0)
  {
   printf("\nHa introducido una opcion que no esta en el menu, porfavor introduzca una viable: ");
   fflush( stdin );
   scanf("%d",&opcion);
  }
return opcion;
}

void aperturaFichero(char fichero[MaxL][MaxC],int opcion)//###################################### APERTURA DE FICHERO ############
{
int i=0;
FILE *F;
switch( opcion )
 {
  case 1: F = fopen ("Animales.txt","r");
          break;

  case 2: F = fopen ("Profesiones.txt","r");
          break;

  case 3: F = fopen ("Nombres.txt","r");
          break;

  case 4: F = fopen ("Paises.txt","r");
          break;

  case 0: exit(0);//Comando para terminar la ejecucion entera del programa
          break;
 }
if (F==NULL)
 {
    printf("\n\t\tERROR:el fichero no se ha abierto correctamente\n");
    exit(0);
 }
else
 {
  //el fichero se ha abierto correctamente
  fscanf(F,"%s",fichero[i]);
  while(!feof(F))
   {
     i++;
     fscanf(F,"%s",fichero[i]);
   }
  fclose(F);
 }
}

int numAleatorio()//############################################################################# NUMERO ALEATORIO ###############
{
srand(time(NULL));
return rand()%50;
}

int informacion(int numError,char letrasIndroducidas[MaxI],char cadGuion[MaxC],int tematica)//################ INFORMACION ####################
{
 int j=0,opcion;
 printf("TEMATICA:");//Imprime la tematica de la palabra a adivinar
 if(tematica==1) printf("ANIMALES\n");
 else if(tematica==2) printf("PROFESIONES\n");
 else if(tematica==3) printf("NOMBRES\n");
 else printf("PAISES\n");
 printf("Errores= %d de 10\n",numError);//Iprime numero de errores
 printf("Ustes ya ha introducido estas letras: ");//Imprime las letras ya introducidas
 puts(letrasIndroducidas);
 printf("\n");
 j=0;
 imprimeFigura(numError);//Imprime la figura del ahorcado correspondiente alnumero de error
 printf("\n");
 printf("Su progreso:");
 puts(cadGuion);
 printf("\n");
 printf("\n");//Aqui se pregunta si el usuario quiere resolver o introducir letras
 printf("%cQuiere introducir letras (1) o resolver(0)?: ",168);//168==¿, pero si pongo '¿' me imprime otro signo
 scanf("%d",&opcion);
 while(opcion<0 || opcion>1)
  {
   printf("\nEsa opcion no existe, porfavor introduzca 1 o 0 si quiere seguir introduciendo letras o resolver, respectivamente: ");
   fflush( stdin );
   scanf("%d",&opcion);
  }
return opcion;
}

void comprobador(char *letra,char resolverPalabra[MaxC],int elegir)//############################ COMPROBADOR ####################
{
 int j=0;
 if(elegir)
  {
   while((*letra<'A' || *letra>'Z')&& (*letra<'a'|| *letra>'z'))//Comprueba si lo que se ha introducido es una letra
    {
     printf("\nNo ha introducido una letra, porfavor introduzca una letra: ");
     scanf(" %c",letra);
     fflush( stdin );
    }
  }
 else
  {
   while(resolverPalabra[j]!='\0')//Recorre el array en busca de caracteres distintos a letras
    {
     if ((resolverPalabra[j]<'A' || resolverPalabra[j]>'Z')&& (resolverPalabra[j]<'a'|| resolverPalabra[j]>'z'))
      {
       j=0;
       printf("\nHa introducido algun caracter distinto de una letra, escriba la resolucion solo con letras: ");
       gets(resolverPalabra);
       fflush( stdin );
      }
     else j++;
    }
  }
}

void conversor(char *letra,char resolverPalabra[MaxC],int elegir)//############################## CONVERSOR ######################
{
 int j=0;
 if(elegir)
  {
   if(*letra>='A' && *letra<='Z')//Comprueba si la letra es una mayuscula y la tranformar a minuscula
    {
      *letra=*letra+32;//Ejemplo si *letra='A' entonces al hacer *letra+32, *letra='a';
    }
  }
 else
  {
   while(resolverPalabra[j]!='\0')//Recorre el array en busca de mayusculas y las tranforma en minisculas
    {                             //mediante el mismo metodo que las letras
     if (resolverPalabra[j]>='A' && resolverPalabra[j]<='Z')
      {
       resolverPalabra[j]=resolverPalabra[j]+32;
       j++;
      }
     else j++;
    }
  }
}
