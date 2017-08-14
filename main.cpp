#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <string>
#include <strings.h>


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
//vector <string> temporal;
vector <Jugador> listaTemporal;
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
void RealizaRondas(vector<string>&,vector<Jugador>&);
int Puntaje();
int menu();
void imprimeLineas(string &,string &, int &);
void imprimeLineas(int &,string &,string &);
void OrdenaVector(vector<Jugador> &);
void leeArchivo(ifstream &,bool &);
void modificArchivo(vector<Jugador>&);
bool ComparaString(string c,vector<Jugador> &lt);
bool ComparaString(string c,vector<string> &lst);
int CopiaArchivo_Vector(vector <Jugador>&);

int main()
{

    try{
        int op =0;
        char opc;
     //   Jugador jug;
//        listaTemporal;
//        jugadores;


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
                                bool sigue =true;



                                string ced;
                                cout<<"Lista de Jugadores Registrados"<<endl;
                                leeArchivo(lee,estatus);
                                jugadores.reserve(8);
                                CopiaArchivo_Vector(listaTemporal);
                                char c;

                                while((existe==true)&&(sigue==true))
                                    //valida el numero de cedula que exista en el vector temporal
                                    //luego lo agrega a un vector de jugadores, esto va a facilitar la busqueda en el archivo
                                    //y poder generar los puntos de la ronda de cada uno
                                    {
                                        cout<<"Digite el numero de Cedula del Jugador"<<endl;
                                        cin>>ced;

                                            existe = ComparaString(ced,listaTemporal);

                                        if(existe){

                                                existe = ComparaString(ced,jugadores);

                                                if(!existe){
                                                      jugadores.push_back(ced);
                                                      jugadores.size();

                                                }


                                        }
                                        existe= true;

                                        if(jugadores.size()<8)
                                        {   sigue = true;

                                                cout<<"Desea agregar otro Jugador?: S/N"<<endl;
                                                cin>>c;
                                                 sigue = (toupper(c)!='N')?true:false;

                                        }
                                    }
                                    archivo.close();
                                    RealizaRondas(jugadores,listaTemporal);


                                    modificArchivo(listaTemporal);
                            }

                        break;

                        case 3:

                            {
                                estatus = false;
                                 CopiaArchivo_Vector(listaTemporal);
                                OrdenaVector(listaTemporal);
                                modificArchivo(listaTemporal);
                                cout<<"****RANKING****"<<endl;
                                leeArchivo(lee,estatus);
                                cout<<"\n"<<endl;

                            }

                        break;
                        case 4:
                            {
                                string mensaje;

                                mensaje = (remove(archive)?  "ERROR\n\n" :"Archivo Borrado Satisfactoriamente\n\n");

                                cout<< mensaje<<endl;

                            }

                        break;

                        case 0:
                            {

                            }

                            return 0;

                        break;
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

bool ComparaString(string c,vector<Jugador> &lt)
{
    bool resultado= false ;
    int d=0;


   for(unsigned int i=0; i< lt.size();i++)
    {
        d=c.compare(lt[i].cedula);

            if(d==0)
            {
                resultado = true;
                break;
            }

        }

    return resultado;

}
bool ComparaString(string c,vector<string> &lst)
{
    bool resultado= false ;
    int d=0;


   for(unsigned int i=0; i< lst.size();i++)
    {
        d=c.compare(lst[i]);

            if(d==0)
            {
                resultado = true;
                break;
            }

        }

    return resultado;

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
    int resultado=0;
    string nomb="";
    string ced="";
    int ptos =0;
    lee.open(archive);
        if(!archive)
        {
            cerr<<"Error al abrir el archivo LINEA 241"<<endl;
            exit(1);
        }

        while(lee>>ced>>nomb>>ptos)
        {   Jugador *j;
            j = new Jugador(ced,nomb,ptos);
            lt.push_back(*j);
            delete j;
            resultado++;

        }
        lee.close();
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
         cont =1;

         while(rd>>j->cedula>>j->nombre>>j->totalPuntos)

         {



               imprimeLineas(cont,j->cedula,j->nombre);
               cont++;
         }

    }else
        {

            hilera = "CEDULA\t\tNOMBRE\t\t\t\tPUNTAJE\n";

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

        cout<<cedula<<"\t\t"<<nombre<<"\t\t\t"<<ptos<<"\t\t\t"<<endl;
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

void RealizaRondas(vector<string>&lst,vector<Jugador>&lt)
/// se toma en cuenta el vector creado con las cedulas que ingreso el usuario, y en el vector temporal que se creo se
///se valida y se generan los turnos y rondas generando los puntajes.
{
    cont =1;
    int d =0;
    string l1="";
    string l2= "";
    const int base = 0;

    for( unsigned int i = 0;i< lst.size();i++)
    {
        for(unsigned int j=0;j< lt.size();j++)
        {
            l1 = lst[i];
            l2 = lt[j].cedula;
            d =l1.compare(l2);
            if(d==base)
            {
                 srand(time(NULL));

                while(cont!=6)
                {

                    lt[j].totalPuntos+= Puntaje();
                      cont++;
                }
            }
//            d= 0;
//            l1 = "";
//            l2 = "";

        }



    }
}

void modificArchivo(vector<Jugador>&lt)
//con los nuevos puntajes en el vector temporal, se piensa modificar los puntos
{
remove(archive);
    archivo.open(archive,ios::out|ios::app);


    if(archivo.is_open())
    {
       // archivo<<"CEDULA\t\tNOMBRE\t\t\t\tPUNTAJE\n"<<endl;
        for(unsigned int n=0; n<lt.size();n++)
        {
            archivo<< lt[n].cedula <<"\t\t\t"<< lt[n].nombre <<"\t\t\t"<< lt[n].totalPuntos <<endl;

        }

    }  else
        {
            cerr<<"Error no se pudo abrir el archivo Linea 431"<<endl;
        }


    archivo.close();
}



void OrdenaVector(vector<Jugador> &lt)
{
    string nomb ="";
    string ced="";
    int ptos=0;
     for( unsigned int l=0; l<lt.size()+1;l++)
        //este for ordena el vector de mayor a menor
    {


                if(lt[l+1].totalPuntos > lt[l].totalPuntos)
                {

                    ced = lt[l+1].cedula;
                    nomb = lt[l+1].nombre;
                    ptos = lt[l+1].totalPuntos;
                    Jugador *j = new Jugador(ced,nomb,ptos);



                    lt[l+1].cedula = lt[l].cedula;
                    lt[l+1].nombre = lt[l].nombre;
                    lt[l+1].totalPuntos = lt[l].totalPuntos;

                    lt[l].cedula = j->cedula;
                    lt[l].nombre = j->nombre;
                    lt[l].totalPuntos = j->totalPuntos;
                    delete j;
                }
                ced="";
                nomb="";
                ptos=0;

    }




}

int Puntaje(){
    int resultado=0;
    int num;
    const int PTOSDARDOS[6] = {1,2,3,4,5,10};
      //srand(time(0));
      //while(resultado==0){


        num = rand()%6;

        resultado=PTOSDARDOS[num];

    //  }
return resultado;

}
