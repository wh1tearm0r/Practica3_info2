#include <iostream>
#include <fstream>
#include "arreglos.h"

using namespace std;

// Funciones para la version con arreglos

//Metodo uno de codificacion (archivo sudo.txt)
/* Se leen los caracteres del archivo de texto en ASCII, separandolo en bloques de n bits, en el primer bloque se cambian unos por
 * ceros y en viceversa, para los siguientes grupos se cuentan los numeros de 1s y 0s en el bloque anterior, si hay igual cantidad de
 * 1s y 0s se invierte cada bit del grupo, si hay mas 0s se invierte cada dos bits y si hay mas 1s se invierte cada tres bits.
 * La funcion va a recibir el archivo sudo.txt escrito en registrarAdminArr y se le hara sobreescritura en el proceso anotado */

int codificacion1(const char* nombreArchivo){
    int n = 4; // siendo n la cantidad de bits por bloque
    ifstream archivoEntrada(nombreArchivo);

    if(!archivoEntrada.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    //Leer el archivo de entrada y guardar el contenido en un arreglo char

    archivoEntrada.seekg(0, ios::end);
    int longitud = archivoEntrada.tellg();
    archivoEntrada.seekg(0, ios::beg);

    char* contenido = new char[longitud + 1];
    archivoEntrada.read(contenido, longitud);
    contenido[longitud] = '\0';
    archivoEntrada.close();

    //Codificar el contenido
    char* contenidoCodificado = new char[longitud * 8 + 1];
    //Separar en bloques de n bits y codificar
    int indice = 0;
    for(int i = 0; i < longitud; i++){
        char caracter = contenido[i];
        for(int j = 7; j >= 0; j--){
            int bit = (caracter >> j) & 1;
            //Codificacion del primer bloque
            if(indice < n){
                bit = 1 - bit; //Invertir bit
            } else {
                //Codificacion de los siguientes bloques
                int unos = 0;
                int ceros = 0;
                for(int k = indice - n; k < indice; k++){
                    if(contenidoCodificado[k] == '1'){
                        unos++;
                    } else {
                        ceros++;
                    }
                }
                if(unos == ceros){
                    bit = 1 - bit; //Invertir bit
                } else if(ceros > unos){
                    if((indice % 2) == 0){
                        bit = 1 - bit; //Invertir cada dos bits
                    }
                } else {
                    if((indice % 3) == 0){
                        bit = 1 - bit; //Invertir cada tres bits
                    }
                }
            }
            contenidoCodificado[indice] = bit + '0'; //Convertir a char
            indice++;
        }
    }

    contenidoCodificado[indice] = '\0';

    //Guardar el contenido codificado en el archivo de salida
    ofstream archivoSalida(nombreArchivo);
    archivoSalida.write(contenidoCodificado, indice);
    archivoSalida.close();

    delete[] contenido;
    delete[] contenidoCodificado;

    return 0;
}

//Decodificar el archivo sudo.txt para iniciar sesion
int decodificacion1(const char* nombreArchivo){
    int n = 4; // siendo n la cantidad de bits por bloque
    ifstream archivoEntrada(nombreArchivo);

    if(!archivoEntrada.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    //Leer el archivo de entrada y guardar el contenido en un arreglo char

    archivoEntrada.seekg(0, ios::end);
    int longitud = archivoEntrada.tellg();
    archivoEntrada.seekg(0, ios::beg);

    char* contenido = new char[longitud + 1];
    archivoEntrada.read(contenido, longitud);
    contenido[longitud] = '\0';
    archivoEntrada.close();

    //Decodificar el contenido
    int longitudDecodificado = longitud / 8;
    char* contenidoDecodificado = new char[longitudDecodificado + 1];

    int indiceDecodificado = 0;
    for(int i = 0; i < longitud; i += 8){
        char byteDecodificado = 0;

        for(int j = 0; j < 8; j++){
            int indice = i + j;
            if(indice >= longitud) break;

            // Leer el bit codificado (como caracter '0' o '1')
            int bitCodificado = contenido[indice] - '0';

            // Aplicar decodificación (inversa de la codificación)
            int bitOriginal = bitCodificado;

            if(indice < n){
                // Primer bloque: se invirtió, así que volvemos a invertir
                bitOriginal = 1 - bitCodificado;
            } else {
                // Bloques siguientes: contar en el CONTENIDO CODIFICADO
                int unos = 0;
                int ceros = 0;
                for(int k = indice - n; k < indice; k++){
                    if(contenido[k] == '1'){
                        unos++;
                    } else {
                        ceros++;
                    }
                }

                if(unos == ceros){
                    bitOriginal = 1 - bitCodificado;
                } else if(ceros > unos){
                    if((indice % 2) == 0){
                        bitOriginal = 1 - bitCodificado;
                    }
                } else {
                    if((indice % 3) == 0){
                        bitOriginal = 1 - bitCodificado;
                    }
                }
            }

            // Reconstruir el byte
            byteDecodificado |= (bitOriginal << (7 - j));
        }

        contenidoDecodificado[indiceDecodificado] = byteDecodificado;
        indiceDecodificado++;
    }

    //Guardar el contenido decodificado en el archivo de salida
    ofstream archivoSalida(nombreArchivo);
    archivoSalida.write(contenidoDecodificado, indiceDecodificado);
    archivoSalida.close();

    delete[] contenido;
    delete[] contenidoDecodificado;

    return 0;
}

bool compararCadenas(const char* a, const char* b){
    for(int i = 0; a[i] != '\0' || b[i] != '\0'; i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}

//Registrar administrador
void registrarAdminArr(){
    char usuario[20];
    char contrasena[20];
    cout << "Ingrese nombre de usuario: ";
    cin >> usuario;
    cout << "Ingrese contrasena: ";
    cin >> contrasena;

    //guardar en archivo sudo.txt
    ofstream archivo("sudo.txt", ios::app);
    archivo << usuario << " " << contrasena << endl;
    archivo.close();
    cout << "Administrador registrado exitosamente" << endl;

    codificacion1("sudo.txt");
}

//Iniciar Sesion como Administrador
void iniciarSesionAdminArr(){
    char usuario[20];
    char contrasena[20];
    cout << "Ingrese nombre de usuario: ";
    cin >> usuario;
    cout << "Ingrese contrasena: ";
    cin >> contrasena;

    decodificacion1("sudo.txt");

    //leer archivo sudo.txt y verificar si el usuario y contrasena son correctos
    ifstream archivo("sudo.txt");
    char usuarioArchivo[20];
    char contrasenaArchivo[20];
    bool encontrado = false;
    while(archivo >> usuarioArchivo >> contrasenaArchivo){
        if(compararCadenas(usuario, usuarioArchivo) &&
            compararCadenas(contrasena, contrasenaArchivo)){
            encontrado = true;
            break;
        }
    }

    archivo.close();

    codificacion1("sudo.txt");

    if(encontrado){
        cout << "Inicio de sesion exitoso" << endl;
        //Aqui va el menu de administrador
    } else {
        cout << "Usuario o contrasena incorrectos" << endl;
    }
}
