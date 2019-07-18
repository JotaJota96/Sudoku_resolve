#include "Cuadricula.h"

Cuadricula::Cuadricula(){
    // inicializa los valores de las matrices
    for (int y = 0; y < DIMENSIONES; y++){
        for (int x = 0; x < DIMENSIONES; x++){
            numeros[y][x] = 0;
            constantes[y][x] = false;
        }
    }
}
Cuadricula::~Cuadricula(){

}


void Cuadricula::definirConstante(int x, int y, int val){
    // ubica el valor en la coordenada y lo define como constante
    if (validarCoordenada(x,y)){
        return;
    }
    escribirNumero(x, y, val);
    constantes[y-1][x-1] = true;
}


bool Cuadricula::esConstante(int x, int y){
    // dada una coordenada ({1a9},{1a9}) devuelve si ese numero es modificable o es constante
    return constantes[y-1][x-1];
}


void Cuadricula::escribirNumero(int x, int y, int val){
    // escribe el valor en la coordenada, sobreescribiendo el anterior SII NO ES CONSTANTE
    if (validarCoordenada(x,y)){
        return;
    }
    if(esConstante(x,y) == false){
        numeros[y-1][x-1] = val;
    }
}


void Cuadricula::borrarNumero(int x, int y){
    // borra el numero en la coordenadaSII NO ES CONSTANTE
    if (validarCoordenada(x,y)){
        return;
    }
    if(esConstante(x,y) == false){
        numeros[y-1][x-1] = 0;
    }
}


int Cuadricula::get(int x, int y){
    // devuelve el valor de la cuadricula en la coordenada solicitada
    if (validarCoordenada(x,y)){
        return 0;
    }
    return numeros[y-1][x-1];
}


bool Cuadricula::estadoValido(){
    // devuelve true si el estado de la cuadricula cumple con las reglas del juego

    int val = 0;

    // se define el array para llevar la cuenta de cuales numeros ya se han encontrado durante la verificacion
    bool numerosEncontrados[DIMENSIONES];

    // verificacion de filas
    for (int y = 0; y < DIMENSIONES; y++){
        // inicializa el registro de numeros encontrados
        for (int v = 0; v < DIMENSIONES; v++) numerosEncontrados[v] = false;

        for (int x = 0; x < DIMENSIONES; x++){
            val = numeros[y][x];

            // si la casilla esta vacia, salta a la siguiente
            if (val == 0){
                continue;
            }

            if (numerosEncontrados[val -1]){
                return false;
            }
            numerosEncontrados[val -1] = true;
        }
    }

    // verificacion de columnas
    for (int x = 0; x < DIMENSIONES; x++){
        // inicializa el registro de numeros encontrados
        for (int v = 0; v < DIMENSIONES; v++) numerosEncontrados[v] = false;

        for (int y = 0; y < DIMENSIONES; y++){
            val = numeros[y][x];

            // si la casilla esta vacia, salta a la siguiente
            if (val == 0){
                continue;
            }

            if (numerosEncontrados[val -1]){
                return false;
            }
            numerosEncontrados[val -1] = true;
        }
    }


    // los primeros dos for recorren los cuadrantes de tal manera que numeros(j,i) siempre es la esquina superior izquierda del cuadrante a verificar
    for (int i = 0; i < DIMENSIONES; i += DIMENSIONES_CUADRANTE){
        for (int j = 0; j < DIMENSIONES; j += DIMENSIONES_CUADRANTE){
            // verificacion del cuadrante (j,i)

            // inicializa el registro de numeros encontrados
            for (int v = 0; v < DIMENSIONES; v++) numerosEncontrados[v] = false;

            for (int y = i; y < i+DIMENSIONES_CUADRANTE; y++){
                for (int x = i; x < j+DIMENSIONES_CUADRANTE; x++){
                    val = numeros[y][x];

                    // si la casilla esta vacia, salta a la siguiente
                    if (val == 0){
                        continue;
                    }

                    if (numerosEncontrados[val -1]){
                        return false;
                    }
                    numerosEncontrados[val -1] = true;
                }
            }
        }
    }
    return true;
}


bool Cuadricula::validarCoordenada(int x, int y){
    return (x < 1 || x > DIMENSIONES || y < 1 || y > DIMENSIONES);
}
