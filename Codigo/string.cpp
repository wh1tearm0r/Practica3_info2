#include "string.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void codificacion1_string(string nombreArchivo, int n)
{
    ifstream entrada(nombreArchivo);
    if (!entrada.is_open()) {
        cout << "Error al abrir " << nombreArchivo << endl;
        return;
    }

    string contenido((istreambuf_iterator<char>(entrada)), istreambuf_iterator<char>());
    entrada.close();

    for (char &c : contenido) {
        c = c ^ n; // XOR con la clave
    }

    ofstream salida(nombreArchivo);
    salida << contenido;
    salida.close();
}

void decodificacion1_string(string nombreArchivo, int n)
{
    codificacion1_string(nombreArchivo, n);
}

void codificacion2_string(string nombreArchivo, int n)
{
    ifstream entrada(nombreArchivo);
    if (!entrada.is_open()) {
        cout << "Error al abrir " << nombreArchivo << endl;
        return;
    }

    string contenido((istreambuf_iterator<char>(entrada)), istreambuf_iterator<char>());
    entrada.close();

    for (char &c : contenido) {
        c = c + n;
    }

    ofstream salida(nombreArchivo);
    salida << contenido;
    salida.close();
}

void decodificacion2_string(string nombreArchivo, int n)
{
    ifstream entrada(nombreArchivo);
    if (!entrada.is_open()) {
        cout << "Error al abrir " << nombreArchivo << endl;
        return;
    }

    string contenido((istreambuf_iterator<char>(entrada)), istreambuf_iterator<char>());
    entrada.close();

    for (char &c : contenido) {
        c = c - n;
    }

    ofstream salida(nombreArchivo);
    salida << contenido;
    salida.close();
}

void registrarAdminStr()
{

}

void iniciarSesionAdminStr()
{

}
