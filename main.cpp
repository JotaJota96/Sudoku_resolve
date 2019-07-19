#include <iostream>
#include <windows.h>
using namespace std;

#include "Cuadricula.h"

#define BORDE_VERTICAL				186
#define BORDE_HORIZONTAL			205
#define ESQUINA_SUPERIOR_IZQUIERDA	201
#define ESQUINA_SUPERIOR_DERECHA	187
#define ESQUINA_INFERIOR_IZQUIERDA	200
#define ESQUINA_INFERIOR_DERECHA	188
#define LINEA_VERTICAL				179
#define LINEA_HORIZONTAL			196
#define LINEA_INTERSECCION			197

#define COLOR_NORMAL 15
#define COLOR_TABLERO 11
#define COLOR_NUMERO 10
#define COLOR_CONSTANTE 1
#define COLOR_ERROR 4
//---------------------------------------------------------------------------------

bool resolver(Cuadricula*, int, int, int);
void llenarConstantes(Cuadricula*, int);
void dibujarLineasTablero();
void dibujarConstantesTablero(Cuadricula* c);
void dibujarNumeroTablero(int x, int y, int num, int tipoNumero);
void borrarNumeroTablero(int x, int y);
void GoToXY(int x, int y);
void cambiarColor(int val);

int main(){
    Cuadricula* c;

    while (true){
        c = new Cuadricula();
        llenarConstantes(c, 9);
        system("CLS");

        dibujarLineasTablero();
        dibujarConstantesTablero(c);

        bool resuelto = resolver(c, 9, 1,1);

        GoToXY(0,13);

        if (resuelto){
            cambiarColor(COLOR_NUMERO);
            cout << "El sudoku ha sido resuelto" << endl;
        }else{
            cambiarColor(COLOR_ERROR);
            cout << "El sudoku NO ha sido resuelto" << endl;
        }
        cambiarColor(COLOR_NORMAL);
        system("PAUSE");
        system("CLS");
    }
    return 0;
}

//---------------------------------------------------------------------------------
bool resolver(Cuadricula* c, int dimensiones, int columna, int fila){
    // resuelve el Sudoku recursivamente y devuelve true si logra resolverlo, de lo contrario false

    if (columna > dimensiones){
        columna = 1;
        fila++;
    }
    if (fila > dimensiones){
        return c->estadoValido();
    }

    // si la casilla actual es constante, simplemente avanza a la siguiente
    if (c->esConstante(columna, fila)){
        return resolver(c, dimensiones, columna+1, fila);
    }else{ // si no es una constante
        // intenta colocar cada uno de los posibles valores
        for (int i = 1; i <= dimensiones; i++){
            // escribe el numero candidato
            c->escribirNumero(columna, fila, i);
            // si el candidato deja la cuadricula en un estado valido, se avanza a la siguiente
            if (c->estadoValido()){
                dibujarNumeroTablero(columna, fila, i, COLOR_NUMERO);
                bool resuelto = resolver(c, dimensiones, columna+1, fila);
                if (resuelto){
                    return resuelto;
                }
            }
        }
        c->borrarNumero(columna,fila);
        borrarNumeroTablero(columna, fila);
        return false;
    }
}

//---------------------------------------------------------------------------------
void llenarConstantes(Cuadricula* c, int dimensiones){
    string str = "";
    bool cargarLinea = true;

    cambiarColor(COLOR_NORMAL);
    cout << "Ingrese los numeros que hay en cada una de las 9 filas del tablero." << endl;
    cout << "Para cada fila ingrese un espacio si la casilla esta vacia, o el numero correspondiente." << endl;
    cambiarColor(COLOR_CONSTANTE);
    cout << "(ejemplo:) Ingrese la fila X: 123 5  8 " << endl;
    cambiarColor(COLOR_NORMAL);

    for (int i = 1; i <= dimensiones; i++){
        str = "";
        cargarLinea = true;

        cout << "Ingrese la fila " << i << ": ";
        getline(cin, str);

        if (str.length() != 9){
            cambiarColor(COLOR_ERROR);
            cout << "La linea ingresada es incorrecta. Se esperaban 9 caracteres." << endl;
            cambiarColor(COLOR_NORMAL);
            i--;
            cargarLinea = false;
        }else{
            for (int j = 0; j < dimensiones; j++){
                if (str[j] != ' ' && (str[j] < 48 || str[j] > 57)){
                    cambiarColor(COLOR_ERROR);
                    cout << "La linea ingresada es incorrecta. Solo se esperaban numeros o espacios." << endl;
                    cambiarColor(COLOR_NORMAL);
                    i--;
                    cargarLinea = false;
                    break;
                }
            }
        }
        if (cargarLinea){
            for (int j = 0; j < dimensiones; j++){
                if (str[j] != ' '){
                    c->definirConstante(j+1, i, str[j]-48);
                }
            }
        }
    }
}

//---------------------------------------------------------------------------------
void dibujarLineasTablero(){
    cambiarColor(COLOR_TABLERO);

    // dibuja las esquinas
    GoToXY(0,   0);  printf("%c", ESQUINA_SUPERIOR_IZQUIERDA);
    GoToXY(24,  0);  printf("%c", ESQUINA_SUPERIOR_DERECHA);
    GoToXY(0,  12);  printf("%c", ESQUINA_INFERIOR_IZQUIERDA);
    GoToXY(24, 12);  printf("%c", ESQUINA_INFERIOR_DERECHA);

    // dibuja lineas horizontales
    for (int i = 1; i < 24; i++){
        GoToXY(i,  0);  printf("%c", BORDE_HORIZONTAL);
        GoToXY(i,  4);  printf("%c", LINEA_HORIZONTAL);
        GoToXY(i,  8);  printf("%c", LINEA_HORIZONTAL);
        GoToXY(i, 12);  printf("%c", BORDE_HORIZONTAL);
    }
    // dibuja lineas verticales
    for (int i = 1; i < 12; i++){
        GoToXY(0,  i);  printf("%c", BORDE_VERTICAL);
        GoToXY(8,  i);  printf("%c", LINEA_VERTICAL);
        GoToXY(16, i);  printf("%c", LINEA_VERTICAL);
        GoToXY(24, i);  printf("%c", BORDE_VERTICAL);
    }
    // dibuja intersecciones de lineas internas
    GoToXY(8,  8);  printf("%c", LINEA_INTERSECCION);
    GoToXY(16, 8);  printf("%c", LINEA_INTERSECCION);
    GoToXY(8,  4);  printf("%c", LINEA_INTERSECCION);
    GoToXY(16, 4);  printf("%c", LINEA_INTERSECCION);

    GoToXY(0,13);
    cambiarColor(COLOR_NORMAL);
}
void dibujarConstantesTablero(Cuadricula* c){
    cambiarColor(COLOR_CONSTANTE);
    for (int y = 1; y <= 9; y++){
        for (int x = 1; x <= 9; x++){
            int val = c->get(x,y);
            if (val != 0){
                dibujarNumeroTablero(x, y, val, COLOR_CONSTANTE);
            }
        }
    }
    cambiarColor(COLOR_NORMAL);
}

//---------------------------------------------------------------------------------
void dibujarNumeroTablero(int x, int y, int num, int tipoNumero){
    cambiarColor(tipoNumero);
    GoToXY(x*2 + 2*((x-1)/3), y + (y-1)/3);  printf("%d", num);
    cambiarColor(COLOR_NORMAL);
}
void borrarNumeroTablero(int x, int y){
    GoToXY(x*2 + 2*((x-1)/3), y + (y-1)/3);  printf(" ");
}

//---------------------------------------------------------------------------------
void GoToXY(int x, int y){		// Coloca el cursor en la ordenada indicada
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = static_cast<short>(x);
    dwPos.Y = static_cast<short>(y);;
    SetConsoleCursorPosition(hCon, dwPos);
}
void cambiarColor(int val){
    // Necesita #include <windows.h>
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(val));
}

