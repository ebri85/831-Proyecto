#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>

#include <time.h>

using namespace std;

//Estructuras de Datos



struct Jugador{
    char *cedula;
    char *nombre;
    int   totalPuntos;
};

//struct Perdedor{
//    int ronda;
//    int codJugador;
//    string nombre;
//    int puntos;
//
//};

struct Ronda{
    char *codJugador;
      int puntos;
};

struct Tragos{

    int cod;
    char *nombre;
    int costo;

};

//Variables Globales

const int tamRonda = 10;
int fila= 0;




    //Tabla de tragos
   Tragos tabla[6]={{1,"Martin en las Rocas",3500},
                    {2,"Maria Sangrienta",2500},
                    {3,"Miguelino",2000},
                    {4,"Polaco Blanco",1500},
                    {5, "Jugo de Ganzo",800},
                    {10,"Caldo de Sapo",500}
                    };






//Funciones Prototipo

//Jugador [][] IniciaJuego();
void RegistraJugador(Jugador &j);
void RegistraPartida(Ronda [][tamRonda],int,int,Jugador []);
void IdentificaPerdedor(Ronda [][tamRonda], Perdedor [],Jugador [], int,int);
void ImprimePerdedores(Perdedor [],Jugador [], Tragos []);
int Puntaje();
int menu();


int main()
{

    try{
        int op =0;
        char opc;
        int fila;
        Jugador jugadores[fila];
        Ronda ronda[fila][tamRonda];
        Perdedor perdedor[tamRonda];


            do{
                cout<< menu()<<endl;
                    cin>>op;

                switch(op){

                        case 1:
                        {
                         cout<<"Indique la cantidad de Jugadores que van a Participar"<<endl;
                                        cin>>fila;
                            if(fila<2){

                                cout<<"Debe de ingresar otro Jugador"<<endl;

                                }if(fila>8){
                                    cout<<"No pueden jugar mas de 8 Jugadores"<<endl;
                                }else {


                                    RegistraJugador(jugadores,fila);

                                }

                        }break;


                        case 2:
                        {   ///For que genera las partidas
                                   for(int i = 0;i<fila;i++){
                                        for(int j= 0; j<tamRonda;j++){

                                            RegistraPartida(ronda,i,j,jugadores);
                                        }
                                   }

                             ///FIN For que genera las partidas



                        }break;

                        case 3:

                        ///For que Identifica Perdedor en cada partida y lo agrega a un Arreglo de Perdedores


                        {   for(int i = 0;i<fila;i++){
                                        for(int j= 0; j<tamRonda;j++){

                                            IdentificaPerdedor(ronda,perdedor,jugadores,i,j);

                                        }
                                   }
                         ///FIN For que Identifica Perdedor en cada partida


                            ImprimePerdedores(perdedor,jugadores,tabla);

                        }break;

                        case 0:

                            return 0;


                        default:
                            break;


                    }

                    cout<<"Desea realizar otra Accion \t S/N"<<endl;
                        cin>>opc;

                }while(toupper(opc)!='N');

        }catch(...){

            cout<<"Por favor revisar error"<<endl;
        }

    }





int menu(){ //Metodo encargado de Mostrar el de Menu en Consola

    int resultado=0;

    string menu = "Juego BAR LA Sanguijuela Testaruda\n\n";

    menu+= "1 - Registro de Participantes \n";
    menu+= "2 - Inicio Partidas \n";
    menu+= "3 - Muestra Resultados \n";
    menu+= "0 - SALIR \n\n";


    cout<<menu<<endl;

return resultado;
//Fin de Metodo Menu
}


///Registra el jugador, con el nombre, asigna codigo, y estado, se guarda
///se guarda en arreglo de structs Jugadores
void RegistraJugador(Jugador &j, fstream &archivo){
    try{
            ofstream archivo("RegistroJugadores",ios::out);

            if(!archivo)
            {
                cerr<<"No se pudo generar el archivo."<<endl;
                exit(1);
            }

            archivo<<"Cedula\t\t"<<"Nombre\t\t"<<"Puntaje"<<endl;



                }

        }   catch(...){

        cout<<"Ocurrio un problema"<< endl;
    }


}


///Metodo registra partida, se guarda en un arreglo de partidas, con los puntos obtenidos
void RegistraPartida(Ronda arreglo[][tamRonda],int numFila,int rondaNumero,Jugador jug[]){
   try{

        int sum;
        Ronda *ptrRonda;


        ptrRonda = &arreglo[numFila][rondaNumero];

        ptrRonda->codJugador = jug[numFila].codJugador ;
             srand(time(0));
            sum= Puntaje() ;

            ptrRonda->puntos = sum + Puntaje();



    }   catch(...){

        cout<<"Ocurrio un problema"<< endl;
    }
}
///Recorre la partida y guarda el perdedor en un arreglo, registra el trago que compro
void IdentificaPerdedor(Ronda arreglo[][tamRonda], Perdedor perd[],Jugador jug[],int f,int c){

    Perdedor *ptrPerdedor;

    ptrPerdedor = &perd[0];
    int ronda =1;

    for (int i = 0; i<f;i++){
        for(int j = 0;j<c;j++){
         srand(time(0));

            if(arreglo[i][j].puntos<arreglo[i+1][j+1].puntos){

                ptrPerdedor->ronda = ronda++;

                ptrPerdedor->codJugador = jug[i].codJugador;

                ptrPerdedor->nombre = jug[i].nombre;

                ptrPerdedor->puntos = Puntaje();

            } else{

                    ptrPerdedor->ronda = ronda++;

                    ptrPerdedor->codJugador = jug[i+1].codJugador;

                    ptrPerdedor->nombre = jug[i+1].nombre;

                    ptrPerdedor->puntos = Puntaje();



            }
            ptrPerdedor++;


        }

    }



}

///Imprime la lista de Perdedores por del Arreglo de Perderdores por en cada Ronda

void ImprimePerdedores(Perdedor perd[],Jugador jug[], Tragos tbl[]){

    Perdedor *ptrPerdedor;
    int cont = 0;
    int pos;
    ptrPerdedor = &perd[0];

    for(int i = 0;i<tamRonda;i++) {

           pos = ptrPerdedor->puntos;

            cout<<"Nombre del perdedor de la Ronda"<<" "<<cont+1<<" "<< jug[cont].nombre<<" "<<"Compro Trago"<< tbl[pos].nombre<<endl;




        ptrPerdedor++;
        cont++;
    }
}


int Puntaje(){
    int resultado=0;
    int num;
    const int PTOSDARDOS[6] = {1,2,3,4,5,10};

      while(resultado==0){

        srand(time(0));
        num = rand()%6;
        resultado=PTOSDARDOS[num];

      }
return resultado;

}
