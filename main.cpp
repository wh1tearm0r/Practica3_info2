#include <iostream>
#include "string.h"
#include "arreglos.h"

using namespace std;

void version1(){
    int opcion;
    cout << "Ingrese opcion: " << endl;
    cout << "1) Iniciar sesion como administrador" << endl;
    cout << "2) Iniciar sesion como usuario" << endl;
    cout << "3) Registrar administrador" << endl;
    cin >> opcion;
    switch(opcion){
        case 1:
            iniciarSesionAdminArr();
            break;
        case 2:
            // iniciarSesionUsuario();
            break;
        case 3:
            registrarAdminArr();
            break;
        default:
            cout << "Opcion no valida" << endl;
    }
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
