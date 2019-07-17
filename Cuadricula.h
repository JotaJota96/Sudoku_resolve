#ifndef CUADRICULA_H
#define CUADRICULA_H

/*
 * La cuadricula se representa como un a matriz que almacena los valores de cada casilla
 * Los valores van del 1 al 9 y se utiliza el 0 para definir que la casilla esta vacia
 * una segunda matriz de booleanos define para cada coordenada si el valor correspondiente esa coordenada en la matriz de numeros, es un valor constante o variable
 * */

class Cuadricula{
private:
    int numeros[9][9];
    bool constantes[9][9];
public:
    Cuadricula();
    ~Cuadricula();

    bool definirConstante(int x, int y, int val); // ubica el valor en la coordenada y lo define como constante
    bool escribirNumero(int x, int y, int val); // escribe el valor en la coordenada, sobreescribiendo el anterior SII NO ES CONSTANTE
    bool borrarNumero(int x, int y); // borra el numero en la coordenadaSII NO ES CONSTANTE
    bool esConstante(int x, int y); // dada una coordenada ({1a9},{1a9}) devuelve si ese numero es modificable o es constante
    bool estadoValido(); // devuelve true si el estado de la cuadricula cumple con las reglas del juego

};

#endif // CUADRICULA_H
