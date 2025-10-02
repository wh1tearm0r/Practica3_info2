#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <string>
using namespace std;

void errorArchivo(const string& nombreArchivo);
void errorAutenticacion(const string& usuario);
void errorEntrada(const string& detalle);
void errorCodificacion(const string& detalle);

#endif
