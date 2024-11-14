#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std; 


vector <int> lTracks;
int numTracks;
int numHead;
int numPrevious;
int numTime;

void info(vector <int> tracks,vector <int> path, int time, int moves){
	time = time * moves;
	cout << "\n\n\tLa informacion respuesto a las solicitudes del disco ";
	cout << "\n ################ \n";
	cout << "Son las siguientes:" << endl;
	cout << "La cantidad de movimientos fueron: " << moves << endl;
	cout << "El tiempo para realizar todas las solicitudes fue de: " << time << "u" << endl;
	cout << "El camino para cumplir con las solicitudes fue: " << endl;
	cout << "* ";
	for(int i = 0; i < path.size() - 1; i++){
		cout << path[i] << " -> ";
	}
	cout << path.back() << endl;
}

void scan(vector <int> tracks, int time, int top, int head, int previous){
	vector <int> path;
	int direction;
	int next;
	int minDiference;
	int diference;
	int actual;
	int moves;
	int indx;
	int max = *max_element(tracks.begin(), tracks.end());
	path.push_back(head);
	if(top == 0){
		top = max;
	}
	if(previous >= head){
		direction = -1;
	}
	else{
		direction = 1;
	}
	while (tracks.size() != 0){
		next = 0;
		actual = head;
		minDiference = max;
		while(next < tracks.size()){
			if(tracks[next] < actual and direction == -1){
				diference = actual - tracks[next];
				if(diference < minDiference){
					minDiference = diference;
					head = tracks[next];
					indx = next;
				}
			}
			else if(tracks[next] > actual and direction == 1){
				diference = tracks[next] - actual;
				if(diference < minDiference){
					minDiference = diference;
					head = tracks[next];
					indx = next;
				}
			}
			++next;
		}
		if (actual == head and direction == -1){
			minDiference = head - 0;
			head = 0;
			direction = 1;

		}
		else if(actual == head and direction == 1){
			minDiference = top - head;
			head = top;
			direction = -1;
		}
		else{
			tracks.erase (tracks.begin()+indx);
			
		}
		cout << "Se paso de la pista " << actual << " a la " << head << " y los movimientos fueron: " << minDiference << endl;
		cout << "El acumulador de movimientos va en: " << moves << endl;
		cout << "diference es: " << diference << endl;
		moves = moves + minDiference;
		path.push_back(head);
	}
	info(tracks,path, time, moves);

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
    ifstream archivo("entradaSCAN.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
 
    // Leer el total de pistas
    getline(archivo, linea);
    if (!esNumero(linea)) {
        cerr << "Error: El número de pistas no es válido." << endl;
        return;
    }
    numTracks = atoi(linea.c_str());  // Convertir cadena a número

    // Leer el número de cabeza del brazo
    getline(archivo, linea);
    if (!esNumero(linea)) {
        cerr << "Error: El número de cabeza no es válido." << endl;
        return;
    }
    numHead = atoi(linea.c_str());  // Convertir cadena a número

    // Leer la pista previa al brazo
    getline(archivo, linea);
    if (!esNumero(linea)) {
        cerr << "Error: El numero de disoc no es válido." << endl;
        return;
    }
    numPrevious = atoi(linea.c_str());  // Convertir cadena a número
    
    getline(archivo, linea);
    if (!esNumero(linea)) {
        cerr << "Error: El tiempo no es válido." << endl;
        return;
    }
    numTime = atoi(linea.c_str());  // Convertir cadena a número

    // Leer los procesos
    getline(archivo, linea);
    stringstream ss(linea);
    int proceso;
    while (ss >> proceso) {
        lTracks.push_back(proceso);  // Almacenar los procesos en el vector
    }

    archivo.close();
}

int main() {
    lecturaArchivo();
    cout << "\t ->Estos fueron los datos leidos<-" << endl;
    cout << "- El numero total de discos son: " << numTracks << endl;
    cout << "- El numero de la cabeza del brazo del disco es: " << numHead << endl;
    cout << "- El numero de la pista previa a la cabeza es: " << numPrevious << endl;
    cout << "- El tiempo que toma para cada solicitud es: " << numTime << "u"<< endl;
    cout << "Las solicitudes son : ";
    for(int i = 0; i < lTracks.size(); ++i){
    	cout << lTracks[i] << " ";
	}
	cout << "\n\n\n";
	cout << "De acuerdo al algoritmo de SCAN, la salida de acuerdo a los datos es: " << endl;
	cout << "\n\n";
		
	scan(lTracks, numTime, numTracks, numHead, numPrevious);
}