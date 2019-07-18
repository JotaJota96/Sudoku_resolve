#ifndef CUADRICULA_H
#define CUADRICULA_H
#include <iostream>

/*
 * La cuadricula se representa como un a matriz que almacena los valores de cada casilla
 * Los valores van del 1 al 9 y se utiliza el 0 para definir que la casilla esta vacia
 * una segunda matriz de booleanos define para cada coordenada si el valor correspondiente esa coordenada en la matriz de numeros, es un valor constante o variable
 *
 * Al recibirse coordenadas en las operaciones, se esperan valores de 1 a 9
 * */

#define DIMENSIONES 9 // dimensiones del tablero
#define DIMENSIONES_CUADRANTE 3

class Cuadricula{
private:
    int numeros[DIMENSIONES][DIMENSIONES];
    bool constantes[DIMENSIONES][DIMENSIONES];

    bool validarCoordenada(int x, int y);
public:
    Cuadricula();
    ~Cuadricula();

    void definirConstante(int x, int y, int val); // ubica el valor en la coordenada y lo define como constante
    bool esConstante(int x, int y); // dada una coordenada ({1a9},{1a9}) devuelve si ese numero es modificable o es constante

    void escribirNumero(int x, int y, int val); // escribe el valor en la coordenada, sobreescribiendo el anterior SII NO ES CONSTANTE
    void borrarNumero(int x, int y); // borra el numero en la coordenadaSII NO ES CONSTANTE

    int get(int x, int y); // devuelve el valor de la cuadricula en la coordenada solicitada
    bool estadoValido(); // devuelve true si el estado de la cuadricula cumple con las reglas del juego

};

#endif // CUADRICULA_H
