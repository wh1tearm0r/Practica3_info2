#include <iostream>
#include <fstream>
#include "arreglos.h"
#include "excepciones.h"

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

//Metodo 2 de codificacion (usuarios.bin)
/* Para codificar se convierte el archivo a binario (la entrada es el archivo .bin que es la salida de la funcion de registrarUsuarioArr)
 * el contenido del archivo se separa en bloques de n bits, cada bit dentro de un grupo se desplaza una posicion, de manera que el ultimo bit del
 * grupo codificado corresponda al ultimo bit del grupo sin codificar, el segundo bit codificado corresponde al primero sin codificar y asi sucesivamente.
 */

int codificacion2(const char* nombreArchivo){
    int n = 4;
    ifstream archivoEntrada(nombreArchivo, ios::binary);
    if(!archivoEntrada.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    archivoEntrada.seekg(0, ios::end);
    int longitud = archivoEntrada.tellg();
    archivoEntrada.seekg(0, ios::beg);

    char* contenido = new char[longitud];
    archivoEntrada.read(contenido, longitud);
    archivoEntrada.close();

    char* contenidoCodificado = new char[longitud];
    int indice = 0;
    while(indice < longitud){
        for(int i = 0; i < n; i++){
            if(indice + i < longitud){
                contenidoCodificado[indice + i] = contenido[indice + (i + 1) % n];
            }
        }
        indice += n;
    }

    ofstream archivoSalida(nombreArchivo, ios::binary);
    archivoSalida.write(contenidoCodificado, longitud);
    archivoSalida.close();

    delete[] contenido;
    delete[] contenidoCodificado;
    return 0;
}

//Decodificar
int decodificacion2(const char* nombreArchivo){
    int n = 4; // siendo n la cantidad de bits por bloque

    ifstream archivoEntrada(nombreArchivo, ios::binary);

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
    char* contenidoDecodificado = new char[longitud + 1];
    int indice = 0;
    while(indice < longitud){
        for(int i = 0; i < n; i++){
            if(indice + i < longitud){
                contenidoDecodificado[indice + (i + 1) % n] = contenido[indice + i];
            }
        }
        indice += n;
    }
    contenidoDecodificado[longitud] = '\0';

    //Guardar el contenido decodificado en el archivo de salida
    ofstream archivoSalida(nombreArchivo, ios::binary);
    archivoSalida.write(contenidoDecodificado, longitud);
    archivoSalida.close();

    delete[] contenido;
    delete[] contenidoDecodificado;

    return 0;
}

//Registrar administrador
void registrarAdminArr(){
    char usuario[10];
    char contrasena[5];

    //Condicional para saber si ya existe un archivo sudo.txt, en caso contrario, generar el archivo
    ifstream archivo("sudo.txt");
    if(!archivo.is_open()){
        cout << "Ingrese nombre de usuario: ";
        cin >> usuario;
        cout << "Ingrese contrasena: ";
        cin >> contrasena;
        ofstream archivo("sudo.txt", ios::app);
        archivo << usuario << " " << contrasena << endl;
        archivo.close();
        codificacion1("sudo.txt");
        cout << "Administrador registrado exitosamente" << endl;
    } else {
        cout << "El administrador ya esta registrado" << endl;
        archivo.close();
    }

}

void registrarUsuarioArr(){
    char usuario[11];
    char contrasena[5];
    long int saldo;

    cout << "Ingrese numero de cedula: ";
    cin >> usuario;

    //condicional para verificar si ya existe un archivo para ese usuario, en caso contrario, crear el archivo
    ifstream archivo(usuario, ios::binary);
    if(archivo.is_open()){
        archivo.close();
        errorAutenticacion("El usuario ya está registrado");

    }

    cout << "Ingrese contrasena: ";
    cin >> contrasena;
    cout << "Ingrese Saldo: ";
    cin >> saldo;

    ofstream archivoSalida(usuario, ios::binary);
    if(!archivoSalida.is_open()){
        errorArchivo(usuario);
    }

    archivoSalida.write(usuario, sizeof(usuario));
    archivoSalida.write(contrasena, sizeof(contrasena));
    archivoSalida.write((char*)&saldo, sizeof(saldo));
    archivoSalida.close();

    cout << "Usuario registrado exitosamente" << endl;
    codificacion2(usuario);
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
    if(!archivo.is_open()){
        errorArchivo("sudo.txt");
    }

    char usuarioArchivo[20];
    char contrasenaArchivo[20];
    bool encontrado = false;

    while(archivo >> usuarioArchivo >> contrasenaArchivo){
        if(compararCadenas(usuario, usuarioArchivo) && compararCadenas(contrasena, contrasenaArchivo)){
            encontrado = true;
            break;
        }
    }

    archivo.close();

    codificacion1("sudo.txt");

    if(!encontrado){
        errorAutenticacion(usuario);
    }

    int opcion;
    cout << "Inicio de sesion exitoso" << endl;
    cout << "Bienvenido, " << usuario << endl;
    cout << "Ingrese la operacion que desea realizar: " << endl;
    cout << "1) Registrar usuario" << endl;
    cout << "2) Salir" << endl;
    cin >> opcion;

    switch(opcion){
        case 1:
            registrarUsuarioArr();
            break;
        case 2:
            cout << "Saliendo..." << endl;
            break;
        default:
            errorEntrada("Opción no válida en menú de administrador");
    }
}

void iniciarSesionUsuarioArr(){
    char usuario[11];
    char contrasena[5];

    cout << "Ingrese numero de cedula: ";
    cin >> usuario;
    cout << "Ingrese contrasena: ";
    cin >> contrasena;

    decodificacion2(usuario);

    ifstream archivo(usuario, ios::binary);
    if(!archivo.is_open()){
        codificacion2(usuario);
        errorArchivo(usuario);
    }

    char usuarioArchivo[11];
    char contrasenaArchivo[5];
    long int saldo;

    archivo.read(usuarioArchivo, sizeof(usuarioArchivo));
    archivo.read(contrasenaArchivo, sizeof(contrasenaArchivo));
    archivo.read((char*)&saldo, sizeof(saldo));
    archivo.close();

    if(compararCadenas(usuario, usuarioArchivo) || compararCadenas(contrasena, contrasenaArchivo)){
        codificacion2(usuario);
        errorAutenticacion(usuario);
    }

    int opcion;
    cout << "Inicio de sesion exitoso" << endl;
    cout << "Bienvenido, " << usuario << endl;
    cout << "Su saldo es: " << saldo << endl;
    cout << "Ingrese la operacion que desea realizar: " << endl;
    cout << "1) Consultar saldo" << endl;
    cout << "2) Retirar" << endl;
    cout << "3) Salir" << endl;
    cin >> opcion;

    switch(opcion){
        case 1: {
            saldo -= 1000;
            cout << "Su saldo es: " << saldo << endl;
            cout << "Se ha hecho un cobro de 1000 por la consulta" << endl;

            ofstream archivo(usuario, ios::binary);
            if(!archivo.is_open()){
                codificacion2(usuario);
                errorArchivo(usuario);
            }

            archivo.write(usuarioArchivo, sizeof(usuarioArchivo));
            archivo.write(contrasenaArchivo, sizeof(contrasenaArchivo));
            archivo.write((char*)&saldo, sizeof(saldo));
            archivo.close();

            codificacion2(usuario);
            break;
        }

        case 2: {
            long int retiro;
            cout << "El costo de la transaccion es de $1000" << endl;
            cout << "Ingrese monto a retirar: ";
            cin >> retiro;

            if(retiro > saldo){
                codificacion2(usuario);
                errorEntrada("Saldo insuficiente para el retiro");
            }

            saldo -= retiro + 1000;
            cout << "Retiro exitoso. Su nuevo saldo es: " << saldo << endl;

            ofstream archivo(usuario, ios::binary);
            if (!archivo.is_open()) {
                codificacion2(usuario);
                errorArchivo(usuario);
            }

            archivo.write(usuarioArchivo, sizeof(usuarioArchivo));
            archivo.write(contrasenaArchivo, sizeof(contrasenaArchivo));
            archivo.write((char*)&saldo, sizeof(saldo));
            archivo.close();

            codificacion2(usuario);
            break;
        }

        case 3: {  // ← Agregar llave de apertura
            cout << "Saliendo..." << endl;
            codificacion2(usuario);
            break;
        }

        default: {
            codificacion2(usuario);
            errorEntrada("Opción no válida en menú de usuario");
        }
    }
}
