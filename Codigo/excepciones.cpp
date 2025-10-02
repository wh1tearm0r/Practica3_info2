#include "excepciones.h"
#include <iostream>
using namespace std;

void errorArchivo(const string& nombreArchivo) {
    string mensaje = "No se pudo abrir o acceder al archivo: " + nombreArchivo;
    throw mensaje.c_str();
}

void errorAutenticacion(const string& usuario) {
    string mensaje = "Fallo de autenticación para el usuario: " + usuario;
    throw mensaje.c_str();
}

void errorEntrada(const string& detalle) {
    string mensaje = "Entrada inválida: " + detalle;
    throw mensaje.c_str();
}

void errorCodificacion(const string& detalle) {
    string mensaje = "Error en proceso de codificación/decodificación: " + detalle;
    throw mensaje.c_str();
}
