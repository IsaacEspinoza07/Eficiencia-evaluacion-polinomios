#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

#define MAX_GRADO 1000
#define PASO_GRADO 10

#define REPETICIONES 1000

int Aleatorio(int inicio, int fin);
long double EvaluarPolinomio(int *coeficientes,int tam,int x);
void CrearPolinomio(int *p, int tam);
long double EvaluarNoOptimo(int *pol,int tam, int x);


auto inicio = high_resolution_clock::now();
auto fin = high_resolution_clock::now();
long long duracion = duration_cast<nanoseconds>(fin - inicio).count();

void EscrituraArchivo(float Tabla[][1000][MAX_GRADO],int k, float promedio[][MAX_GRADO], const char NombreArchivo[]);
long double ExponenteExacto(int n, unsigned int exp);


float Tabla[2][REPETICIONES][MAX_GRADO];



int main()
{
    float Promedio[2][MAX_GRADO] = {0};
    srand(time(NULL));

    int *pol;
    int grado(0);
    int x;

    for(int i=10;i<=MAX_GRADO;i+=PASO_GRADO){
        cout << "Evaluando en polinomios de grado " << i << "...";
        //cout << endl << endl;
        for(int j=1;j<=REPETICIONES;++j){

            //generar numero aleatorio

            x = Aleatorio(2,5);


            //Crear el polinomio (arreglo de coeficientes)
            grado = i+1;
            pol = new int [grado];
            CrearPolinomio(pol, grado);


            //Medir tiempo algoritmo NO OPTIMO (evaluacion comun)
            inicio = high_resolution_clock::now();

            EvaluarNoOptimo(pol,grado,x);

            fin = high_resolution_clock::now();
            duracion = duration_cast<nanoseconds>(fin - inicio).count();

            Tabla[0][j-1][i/10-1] = duracion;
            Promedio[0][i/10-1] += duracion;



            //Medir tiempo algoritmo OPTIMO
            inicio = high_resolution_clock::now();

            EvaluarPolinomio(pol,grado,x);

            fin = high_resolution_clock::now();

            //Almacenamiento en tabla
            duracion = duration_cast<nanoseconds>(fin - inicio).count();

            Tabla[1][j-1][i/PASO_GRADO-1] = duracion;
            Promedio[1][i/PASO_GRADO-1] += duracion;

            delete []pol;


        }
        cout << "  Listo!\n\n";

    }

    EscrituraArchivo(Tabla,0,Promedio,"MetodoEvaluacionComun.csv");
    EscrituraArchivo(Tabla,1,Promedio,"MetodoEvaluacionHorner.csv");
    system("pause");
    return 0;
}


/////////////////////////////////////////////////////////////////////
//////////////////////////////FUNCIONES//////////////////////////////
/////////////////////////////////////////////////////////////////////

long double EvaluarNoOptimo(int *pol,int tam, int x){
    long double valor(0);
    long double coef(0);
    long double exp(0);

    for(int i=1;i<=tam;++i){
        coef = pol[i-1];
        exp = ExponenteExacto(x,tam-i);

        valor += coef*exp;
    }

    return valor;
}

/////////////////////////////////////////////////////////////////////

long double EvaluarPolinomio(int *coeficientes,int tam,int x)
{
    long double evaluacion = coeficientes[0];
    for(int i=1;i<tam;++i){
        evaluacion= evaluacion*x + coeficientes[i];
    }

    return evaluacion;
}

/////////////////////////////////////////////////////////////////////

void CrearPolinomio(int *p, int tam)
{
    p[0] = (rand()%2 ? 1 : -1) * Aleatorio(1, 10);

    // Resto de coeficientes
    for(int i=1; i<tam; ++i) {
        p[i] = Aleatorio(-10, 10);
    }
    return;
}

/////////////////////////////////////////////////////////////////////

int Aleatorio(int inicio, int fin)
{
    return inicio+rand()%(fin-inicio+1);
}

/////////////////////////////////////////////////////////////////////

void EscrituraArchivo(float Tabla[][1000][MAX_GRADO],int k, float promedio[][MAX_GRADO], const char NombreArchivo[]){

    //Escribir los valores dentro de un archivo independiente//
    ofstream myFile;
    myFile.open(NombreArchivo);

    myFile << "Grado del Polinomio: " << ',';
    for(int i=10;i<=MAX_GRADO;i+=PASO_GRADO){
        myFile << i << ',';
    }
    myFile << endl << endl;


    for(int i=0;i<1000;++i){

        for(int j=10;j<=MAX_GRADO;j+=10){
            myFile << ',' << Tabla[k][i][j/10-1];
        }
        myFile << endl;
    }


    /*Dice los promedios en la columna de cada quien.*/
    myFile << endl;
    myFile << endl <<"Promedios:";

    myFile << ',';
    for(int i=0;i<MAX_GRADO;i++){
        myFile << promedio[k][i]/1000 << ',';
    }

    myFile.close();


    //Reunir los promedios dentro de un solo archivo.
    ofstream ArchPromedios;
    ArchPromedios.open("Promedios.csv");

    string Nombres[] = {
        "Ev.Comun: ",
        "Ev.Horner: "
    };


    ArchPromedios << "Grado Polinomio:" << ',';
    for(int i=10;i<=MAX_GRADO;i+=PASO_GRADO){
        ArchPromedios << i << ',';
    }

    ArchPromedios << endl << endl;
    for(int i=0;i<2;i++){
        ArchPromedios << Nombres[i] << ',';
        for(int j=10;j<=MAX_GRADO;j+=PASO_GRADO){
            ArchPromedios << promedio[i][j/10-1]/1000 << ',';
        }
        ArchPromedios << endl;
    }

}

/////////////////////////////////////////////////////////////////////

long double ExponenteExacto(int n, unsigned int exp) {
    if(exp == 0) return 1.0L;
    long double resultado = 1.0L;
    for(unsigned i = 0; i < exp; ++i) {
        resultado *= n;
    }
    return resultado;
}
