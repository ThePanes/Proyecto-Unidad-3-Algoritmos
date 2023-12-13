#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <random>
#include <iostream>
#include <chrono>
using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

using namespace std;

void printTiempoTomado(const string& nombreAlgoritmo, double time_taken){
    cout << "Tiempo del Algoritmo " << nombreAlgoritmo << " : " << fixed << time_taken << "segundos" << endl;
}


void SelectionSort(vector<int>& arr) {

    int n = arr.size();
    for (int i = 0; i < n ; ++i) {
        for (int j = i; j < n ; ++j) {
            if (arr[j] < arr[i]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void quickSort(vector<int>& arr, int low, int high){

    if(low < high){
        int pivot = arr[high];
        int i = low - 1;

        for(int j = low; j <= high - 1; j++){
            if(arr[j] < pivot){
                i++;
                swap(arr[i],arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pivotActual = i + 1;
        quickSort(arr,low,pivotActual - 1);
        quickSort(arr,pivotActual + 1,high);
    }
}

void bubbleSort(vector<int>& arr){
    int n = arr.size();

    for(int i = 0; i < n - 1; ++i){
        for(int j = 0; j < n - i - 1;++j){
            if(arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void shellSort(vector<int>& arr){
    int n = arr.size();

    for(int z = n /2; z > 0; z/=2){
        for(int i = z; i < n; ++i){
            int temp = arr[i];
            int j = i;
            while(j >= z && arr[j - z] > temp){
                arr[j] = arr[j - z];
                j -= z;
            }
            arr[j] = temp;
        }
    }
}

void heapSortInternalFuncion(vector<int>& arr, int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }

    if(right < n && arr[right] > arr[largest]){
        largest = right;
    }

    if(largest != i){
        swap(arr[i], arr[largest]);
        heapSortInternalFuncion(arr, n , largest);
    }
}

void heapSort(vector<int>& arr){
    int n = arr.size();

    for(int i = n/2 - 1; i >= 0; --i){
        heapSortInternalFuncion(arr,n,i);
    }
    for(int i = n - 1; i > 0; --i){
        swap(arr[0], arr[i]);
        heapSortInternalFuncion(arr,i,0);
    }
}

void insertionSort(vector<int>& arr){
    int n = arr.size();
    for(int i = 1; i < n; ++i){
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void mergeSortInternalFuncion(vector<int>& arr, int low, int mid, int high){

    int n1 = mid - low + 1;
    int n2 = high - mid;
    vector<int> left;
    vector<int> right;

    for(int i = 0; i < n1; ++i){
        left.push_back(arr[low + i]);
    }
    for(int j = 0; j < n2; ++j){
        right.push_back(arr[mid + 1 + j]);
    }
    int i = 0;
    int j = 0;
    int k = low;
    while(i < n1 && j < n2){
        if(left[i]  <= right[j]){
            arr[k] = left[i];
            ++i;
        }else{
            arr[k] = right[j];
            ++j;
        }
        ++k;
    }
    while(i < n1){
        arr[k] = left[i];
        ++i;
        ++k;
    }
    while(j < n2){
        arr[k] = right[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& arr, int low, int high){
    if(low < high){
        int mid = low + (high - low) / 2;
        mergeSort(arr,low,mid);
        mergeSort(arr,mid + 1, high);
        mergeSortInternalFuncion(arr,low,mid,high);
    }
}

double getResultFromAlg(vector<int>& arr, const string& nombreAlgoritmo) {
    auto start = chrono::high_resolution_clock::now();
    vector<int> arrCopia = arr;
    if(nombreAlgoritmo == "SelectionSort"){
        SelectionSort(arrCopia);
    }else if(nombreAlgoritmo == "quickSort"){
        quickSort(arrCopia, 0 , arrCopia.size() - 1);
    }else if(nombreAlgoritmo == "bubbleSort"){
        bubbleSort(arrCopia);
    }else if(nombreAlgoritmo == "shellSort"){
        shellSort(arrCopia);
    }else if(nombreAlgoritmo == "heapSort"){
        heapSort(arrCopia);
    }else if(nombreAlgoritmo == "insertionSort"){
        insertionSort(arrCopia);
    }else if(nombreAlgoritmo == "mergeSort"){
        mergeSort(arrCopia, 0 , arrCopia.size() - 1);
    }
    auto end = high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    printTiempoTomado(nombreAlgoritmo,duration.count());
    return duration.count();
}

void realizarCarrera(vector<int>& arr, const string& nombreCarrera){

    vector<int> arrCopia = arr;
    double better_time = numeric_limits<double>::infinity();
    string mejorAlgoritmo = " ";
    vector <string> algotirmos = {"SelectionSort","quickSort","bubbleSort","shellSort","heapSort","insertionSort","mergeSort"};

    for(const string& nombreAlgoritmo : algotirmos){
        double tiempoAlgoritmo = getResultFromAlg(arrCopia,nombreAlgoritmo);
        if(tiempoAlgoritmo < better_time){
            better_time = tiempoAlgoritmo;
            mejorAlgoritmo = nombreAlgoritmo;
        }
    }

    cout << "El mejor tiempo fue para: " << mejorAlgoritmo << " con un tiemo de: " << better_time << endl;

}

void empezarCarrera(const vector<int>& arr, const string& nombreCarrera){
    cout << "Carrera: " << nombreCarrera << endl;

    vector<int> arrCopia = arr;
    cout << "Se usaran los algoritmos de Ordenamiento para ver cual demora menos en ordenar este arreglo." << endl;

    realizarCarrera(arrCopia, "Copia de" + nombreCarrera);

    cout << endl;
}

int main() {

    srand(static_cast<unsigned int>(time(nullptr)));
    vector<int>arrPlayers, arrSortedPlayers,arrReversePlayers;
    int random_value;

    const int amountPlayers = 100000;
    //cout << "Generando set de datos jugadores en un rango de 100.000 a 110.000: " << endl;
    for (int i = 0; i < amountPlayers ; ++i) {
        arrSortedPlayers.push_back(i+1);
        arrReversePlayers.push_back(amountPlayers-i);
        if ( i == 0 ) {
            random_value = 1 + rand() % (amountPlayers);
            arrPlayers.push_back(random_value);
        }
        else {
            random_value = 1 + rand() % (amountPlayers);
            arrPlayers.push_back(random_value);
        }
    }

    vector<int>arrObjects, arrSortedObjects,arrReverseObjects;
    int random_value_objects;

    const int amountObjects = 15000;
    //cout << "Generando set de datos trazabilidad objetos entre 1.000 y 1.500 con 15 categorias: " << endl;
    for (int i = 0; i < amountObjects ; ++i) {
        arrSortedObjects.push_back(i+1);
        arrReverseObjects.push_back(amountObjects-i);
        if ( i == 0 ) {
            random_value_objects = 1 + rand() % (amountObjects);
            arrObjects.push_back(random_value_objects);
        }
        else {
            random_value_objects = 1 + rand() % (amountObjects);
            arrObjects.push_back(random_value_objects);
        }
    }

    vector<int>arrEvents, arrSortedEvents,arrReverseEvents;
    int random_value_events;

    const int amountEvents = 80000;
    //cout << "Generando set de datos Eventos de cada escenario entre 60.000 a 80.000 combinaciones: " << endl;
    for (int i = 0; i < amountEvents ; ++i) {
        arrSortedEvents.push_back(i+1);
        arrReverseEvents.push_back(amountEvents-i);
        if ( i == 0 ) {
            random_value_events = 1 + rand() % (amountEvents);
            arrEvents.push_back(random_value_events);
        }
        else {
            random_value_events = 1 + rand() % (amountEvents);
            arrEvents.push_back(random_value_events);
        }
    }


    cout << "Se termino de generar los datos" << endl;

    int opcion;

    do{
        cout << "Bienvenido al menu principal, a continuacion seleccione una opcion:" << endl;
        cout << "1. Carrera Cola de Espera Jugadores." << endl;
        cout << "2. Carrera Trazabilidad de Objetos." << endl;
        cout << "3. Carrera Eventos de Cada Escenario." << endl;
        cout << "4. Salir." << endl;
        cin >> opcion;

        switch(opcion){
            case 1:
                empezarCarrera(arrSortedPlayers, "Cola de Espera Jugadores, arreglo en orden");
                empezarCarrera(arrPlayers,"Cola de Espera Jugadores, arreglo random");
                empezarCarrera(arrReversePlayers, "Cola de Espera Jugadores, arreglo en reversa");

                break;
            case 2:
                empezarCarrera(arrSortedObjects, "Cola Trazabilidad de Objetos, arreglo en orden");
                empezarCarrera(arrObjects, "Cola Trazabilidad de Objetos, arreglo random");
                empezarCarrera(arrReverseObjects, "Cola Trazabilidad de Objetos, arreglo en reversa");
                break;
            case 3:
                empezarCarrera(arrSortedEvents, "Cola Eventos de Cada Escenario, arreglo en orden");
                empezarCarrera(arrEvents, "Cola Eventos de Cada Escenario, arreglo random");
                empezarCarrera(arrReverseEvents, "Cola Eventos de Cada Escenario, arreglo en reversa");
                break;
            default:
                cout << "Opcion invalida, reintente." << endl;
                break;
        }

    }while(opcion != 4);



    return 0;
}

