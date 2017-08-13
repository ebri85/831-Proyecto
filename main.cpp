#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <string>

#include <time.h>

using namespace std;



//Estructuras de Datos



struct Jugador
{
    string cedula;
    string nombre;
    int totalPuntos;

    Jugador(){};

    Jugador(string cedula, string nombre, int totalPuntos)
    {
        this->cedula=cedula;
        this->nombre= nombre;
        this->totalPuntos = totalPuntos;
    }


};

//struct Perdedor{
//    int ronda;
//    int codJugador;
//    string nombre;
//    int puntos;
//
//};

struct Ronda
{
    string codJugador;
      int puntos;
};

struct Tragos
{

    int cod;
    string nombre;
    int costo;

};

//Variables Globales

const int tamRonda = 10;
bool estatus;
const char *archive = "Tabla_Resultados.txt";
fstream archivo;
ofstream escribe;
ifstream lee;
string hilera ="";
vector <string> jugadores;
vector <string> temporal;
vector<Jugador> listaTemporal;
int cont =0;






    //Tabla de tragos
   Tragos tabla[6]={{1,"Martin en las Rocas",3500},
                    {2,"Maria Sangrienta",2500},
                    {3,"Miguelino",2000},
                    {4,"Polaco Blanco",1500},
                    {5, "Jugo de Ganzo",800},
                    {10,"Caldo de Sapo",500}
                    };

//Funciones Prototipo

void RegistraJugador(string &ced, string &nomb);
int generaArchivo();
void RealizaRondas(vector<string> &,vector<Jugador> &);
int Puntaje();
int menu();
void imprimeLineas(string &,string &, int &);
void imprimeLineas(int &,string &,string &);
void OrdenaVector(vector<Jugador> &);
void leeArchivo(ifstream &,bool &);
void modificArchivo(vector<Jugador>&);

int CopiaArchivo_Vector(vector <Jugador> &lt);

int main()
{

    try{
        int op =0;
        char opc;



        generaArchivo();



            do{
                cout<< menu()<<endl;
                    cin>>op;

                switch(op){

                        case 1:
                            {
                                char continua;


                                    do
                                    {
                                        string cedula= "";
                                        cout<<"Digite el Numero de Cedula del Usuario"<<endl;
                                            cin>>cedula;
                                        string nombre="";
                                        cout<<"Digite el Nombre del Jugador"<<endl;
                                            cin>>nombre;

                                        RegistraJugador(cedula,nombre);
                                            cout<<"Desea agregar otro usuario : S/N?"<<endl;
                                                cin>>continua;

                                    }while(toupper(continua)=='S');

                            }

                        break;


                        case 2:
                            {
                                estatus = true;
                                bool existe = true;
                                bool sigue= true;


                                string ced;
                                cout<<"Lista de Jugadores Registrados"<<endl;
                                leeArchivo(lee,estatus);
                                jugadores.reserve(8);
                                CopiaArchivo_Vector(listaTemporal);

                            }

                        break;

                        case 3:

                            {
                                estatus = false;
                                cout<<"****RANKING****"<<endl;
                                leeArchivo(lee,estatus);
                                cout<<"\n"<<endl;


                            }



                        break;
                        case 4:
                            {
                                string mensaje;

                                mensaje = (remove("Tabla_Resultados.txt")?  "ERROR\n\n" :"Archivo Borrado Satisfactoriamente\n\n");

                                cout<< mensaje<<endl;

                            }

                        break;

                        case 5:
                            {

                                for(unsigned int i=0; i < listaTemporal.size();i++)
                                {

                                    cout<< listaTemporal[i].cedula<<" \t\t\t "<< listaTemporal[i].nombre <<"\t\t\t" <<listaTemporal[i].totalPuntos<<endl;
                                }

                            }

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





int menu()
//Metodo encargado de Mostrar el de Menu en Consola
{

    int resultado=0;

    string menu = "Juego BAR LA Sanguijuela Testaruda\n\n";

    menu+=  "1 - Registro de Participantes \n";
    menu+=  "2 - Realizar las Rondas \n";
    menu+=  "3 - Ver Ranking\n";
    menu+=  "4 - Borrar Archivo\n";
    menu+=  "0 - SALIR \n\n";


    cout<<menu<<endl;

return resultado;
//Fin de Metodo Menu
}
int CopiaArchivo_Vector(vector <Jugador> &lt)
///copia el archivo a un vector temporal para luego generar las rondas y modificar el archivo.
{
    lt.clear();
    int resultado=1;
    string nomb,ced;
    int ptos;
    lee.open(archive);
        if(!archive)
        {
            cerr<<"Error al abrir el archivo LINEA 241"<<endl;
            exit(1);
        }

        while(lee>> ced >> nomb >> ptos)
        {   Jugador *j;
            j = new Jugador(ced,nomb,ptos);
            lt.push_back(*j);
            delete j;
            resultado++;

        }



    return resultado;

}
int generaArchivo()
///revisa si el archivo existe abriendolo, si existe lo cierra, si no existe crea el mismo y lo cierra
{


       if (lee.is_open())//revisa si esta creado el archivo, retorna 1 si el archivo existe
       {
           lee.close();
           return 1;
       }
        else
            {
                //crea el archivo retorna 0

                  archivo.open(archive);
                  archivo.close();
                return 0;

            }
}

void leeArchivo(ifstream &rd,bool &t)
//va a leer el archivo e imprimir el contenido del archivo,
//dependiendo el valor de true o false que se le pase imprime los puntos, la idea es que si entra en true es
//para imprimir la lista de jugadores para poder seleccionarlos para
//la partida
{
    string hilera;

    Jugador *j = new Jugador();

    rd.open(archive);
    if(!rd)
    {
        cerr<<"Error para abrir el Archivo LINEA 312";

        exit(1);
    }

    if(t==true)
    {
         hilera = "INDICE\t\tCEDULA\t\t\t\tNOMBRE\n";


         cout<<hilera<<endl;


         while(rd>>j->cedula>>j->nombre>>j->totalPuntos)
         {


             temporal.push_back(j->cedula);
             cont++;

               imprimeLineas(cont,j->cedula,j->nombre);
         }

    }else
        {

            hilera = "CEDULA\t\t\t\ttNOMBRE\t\t\t\t\t\tPUNTAJE\n";

            cout<<hilera<<endl;

             while(rd>>j->cedula>>j->nombre>>j->totalPuntos)
             {
                 imprimeLineas(j->cedula,j->nombre,j->totalPuntos);
             }

        }


        delete j;
        rd.close();


}

void imprimeLineas(string &cedula,string &nombre, int &ptos)
    //imprime lineas dle archivo
    {

        cout<<cedula<<"\t\t\t"<<nombre<<"\t\t\t"<<ptos<<endl;
    }

void imprimeLineas(int &indice,string &cedula,string &nombre)
    //imprime lineas dle archivo
    {
        cout<<indice<<"\t\t"<<cedula<<"\t\t\t"<<nombre<<"\t\t\t"<<endl;
    }


void RegistraJugador(string &ced, string &nomb)
///Registra el jugador, con el nombre, asigna cedula, y puntaje en 0, se guarda en un archivo de texto
{
    try{

        ofstream escribe(archive,ios::app);
        int ptos=0;

            if(escribe.is_open())
            {
               Jugador *j = new Jugador(ced,nomb,ptos);

                escribe<< j->cedula <<"\t\t\t"<< j->nombre <<"\t\t\t"<< j->totalPuntos <<endl;

                delete j;

             escribe.close();
            }
            else
            {
                cout<<"Error no se pudo abrir el archivo LINEA 390"<<endl;
            }
        }   catch(...){

        cout<<"Ocurrio un problema"<< endl;
    }

}

void RealizaRondas(vector<string> &lst,vector<Jugador> &lt)
{



}

void modificArchivo(vector<Jugador>&lt)
{
      escribe.open(archive,ios::app);

    if(escribe.is_open())
    {
        for(unsigned int n=0; n<lt.size();n++)
        {
            escribe<< lt[n].cedula <<"\t\t\t"<< lt[n].nombre <<"\t\t\t"<< lt[n].totalPuntos <<endl;

        }

    }  else
        {
            cerr<<"Error no se pudo abrir el archivo Linea 473"<<endl;
        }


    archivo.close();
}



void OrdenaVector(vector<Jugador> &lt)
{
    string nomb;
    string ced;
    int ptos;
     for(unsigned int l=0; l<lt.size();l++)
        //este for ordena el vector de mayor a menor
    {
         Jugador *j;

                if(lt[l+1].totalPuntos > lt[l].totalPuntos)
                {

                    ced = lt[l+1].cedula;
                    nomb = lt[l+1].nombre;
                    ptos = lt[l+1].totalPuntos;
                        j = new Jugador(ced,nomb,ptos);



                    lt[l+1].cedula = lt[l].cedula;
                    lt[l+1].nombre = lt[l].nombre;
                    lt[l+1].totalPuntos = lt[l].totalPuntos;


                    lt[l]= *j;

                }
        delete j;
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
