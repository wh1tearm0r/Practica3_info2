#include <iostream>
#include "string.h"
#include "arreglos.h"

using namespace std;

void version1(){

}

void version2(){

}

int main()
{
    int version;
    cout << "Ingrese version del programa: " << endl;
    cout << "1) Version 1 (arreglos)" << endl;
    cout << "2) Version 2 (string)" << endl;
    cin >> version;

    switch(version){
        case 1:
            version1();
            break;
        case 2:
            version2();
            break;
        default:
            cout << "Version no valida" << endl;
    }

    return 0;
}
