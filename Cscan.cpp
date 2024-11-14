
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>  // Para usar atoi
#include <cmath> 



using namespace std;

int numeroDePistas;
int numeroDeCabeza;
int sentido;
int tiempo;
vector<int> procesos;



// Función C-SCAN
int Cscan(int pistas, int headA, vector<int>& procesos, int sentido) {
    int suma = 0;

    sort(procesos.begin(), procesos.end());
    
    procesos.insert(procesos.begin(), 0); 
    if (pistas!= 0){
        procesos.push_back(pistas); 
    }
    
    vector<int> izquierda, derecha;
    for (int i = 0; i < procesos.size(); i++) {
        if (procesos[i] < headA) {
            izquierda.push_back(procesos[i]);
        } else {
            derecha.push_back(procesos[i]);
        }
    }

    cout << "Procesando solicitud en: " << headA << endl;
    if (sentido == 1){
        for (int i = 0; i < derecha.size(); i++) {
        suma += abs(headA - derecha[i]);
        headA = derecha[i];
        cout << "Procesando solicitud en: " << headA << endl;
        }

        suma += abs(headA - pistas); 
        headA = pistas; 
        cout << "Regresando al inicio del disco" << endl;
        
        // Procesamos las solicitudes de la parte izquierda en orden ascendente
        for (int i = 0; i < izquierda.size(); i++) {
            suma += abs(headA - izquierda[i]);
            headA = izquierda[i];
            cout << "Procesando solicitud en: " << headA << endl;
        }
    }else{

        for (int i = izquierda.size()-1 ; i >=0 ;i--) {
            suma += abs(headA - izquierda[i]);
            headA = izquierda[i];
            cout << "Procesando solicitud en: " << headA << endl;
        }
        suma += abs(headA - pistas); 
        headA = pistas; 
        cout << "Regresando al limite del disco" << endl;
        for (int i = derecha.size()-1; i >=0; i--) {
            suma += abs(headA - derecha[i]);
            headA = derecha[i];
            cout << "Procesando solicitud en: " << headA << endl;
        }
        
    }
    return suma;
}




bool esNumero(const string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;  // No es un número
        }
    }
    return true;  // Es un número
}

void lecturaArchivo() {
    ifstream archivo("entrada.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;

    // Leer el número de pistas
    getline(archivo, linea);
    if (!esNumero(linea)) {
        cerr << "Error: El número de pistas no es válido." << endl;
        return;
    }
    numeroDePistas = atoi(linea.c_str());  // Convertir cadena a número

    // Leer el número de cabeza del brazo
    getline(archivo, linea);
    if (!esNumero(linea)) {
        cerr << "Error: El número de cabeza no es válido." << endl;
        return;
    }
    numeroDeCabeza = atoi(linea.c_str());  // Convertir cadena a número

    // Leer el sentido
    getline(archivo, linea);
    if (!esNumero(linea)) {
        cerr << "Error: El sentido no es válido." << endl;
        return;
    }
    sentido = atoi(linea.c_str());  // Convertir cadena a número

    getline(archivo, linea);
    if (!esNumero(linea)) {
        cerr << "Error: El sentido no es válido." << endl;
        return;
    }
    tiempo = atoi(linea.c_str());  // Convertir cadena a número


    // Leer los procesos
    getline(archivo, linea);
    stringstream ss(linea);
    int proceso;
    while (ss >> proceso) {
        procesos.push_back(proceso);  // Almacenar los procesos en el vector
    }

    archivo.close();
}

int main() {
    lecturaArchivo();

    // Verificación de los datos leídos
    cout << "Número de pistas: " << numeroDePistas << endl;
    cout << "Número de cabeza: " << numeroDeCabeza << endl;
    cout << "Sentido: " << sentido << endl;
    cout << "Tiempo por pasos: " << tiempo << endl;
    cout << "Procesos: ";

    for (size_t i = 0; i < procesos.size(); i++) {
        cout << procesos[i] << " ";  // Imprimir los procesos
    }
    cout << endl;
    cout << endl;
    // Llamada a la función Cscan con las variables ya definidas
    int resultado = Cscan(numeroDePistas, numeroDeCabeza, procesos, sentido); 
    int tt = tiempo*resultado;

    cout << "\nTotal de longitud recorrida: " << resultado << endl;
    cout << "\nTotal de tiempo gastado (longitud*tiempo): " << tt << endl;

    return 0;
}