#include <iostream>
using namespace std;

#include "Cuadricula.h"

void mostrarTablero(Cuadricula*);


int main(){
    Cuadricula* c = new Cuadricula();
    c->definirConstante(1,1,1);
    c->definirConstante(7,8,1);
    c->definirConstante(8,8,1);

    mostrarTablero(c);

    cout << "Estado valido: " << c->estadoValido() << endl;

    return 0;
}


void mostrarTablero(Cuadricula* c){
    printf("+---------------------------+\n");
    for (int y = 1; y <= 9; y++){
        printf("|");
        for (int x = 1; x <= 9; x++){
            int val = c->get(x,y);
            if (val == 0){
                printf("   ");
            }else{
                printf(" %d ", val);
            }
        }
        printf("|\n");
    }
    printf("+---------------------------+\n");
}

