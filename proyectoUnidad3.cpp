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

double getResultFromAlg(vector<int>& arr) {
    time_t start, end;
    double time_taken;
    time(&start);
    ios_base::sync_with_stdio(false);
                        //cambiar esta funcion hace el tiempo del algoritmo usado.
    SelectionSort(arr);
    //quickSort(arr,0,arr.size()- 1);

    time(&end);
    time_taken = double(end - start);
    return time_taken;
}

void realizarCarrera(vector<int>& arr, const string& nombreAlgoritmo){

    auto start = chrono::high_resolution_clock::now();

    if(nombreAlgoritmo == "SelectionSort"){
        SelectionSort(arr);
    }else if(nombreAlgoritmo == "quickSort"){
        quickSort(arr, 0 , arr.size() - 1);
    }else if(nombreAlgoritmo == "bubbleSort"){
        bubbleSort(arr);
    }else if(nombreAlgoritmo == "shellSort"){
        shellSort(arr);
    }else if(nombreAlgoritmo == "heapSort"){
        heapSort(arr);
    }else if(nombreAlgoritmo == "insertionSort"){
        insertionSort(arr);
    }else if(nombreAlgoritmo == "mergeSort"){
        mergeSort(arr, 0 , arr.size() - 1);
    }

    auto end = high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    printTiempoTomado(nombreAlgoritmo,duration.count());
}

void empezarCarrera(const vector<int>& arr, const string& nombreCarrera){
    cout << "Carrera: " << nombreCarrera << endl;

    vector<int> arrCopiaSelectionSort = arr;
    vector<int> arrCopiaquickSort = arr;
    vector<int> arrCopiabubbleSort = arr;
    vector<int> arrCopiashellSort = arr;
    vector<int> arrCopiaheapSort = arr;
    vector<int> arrCopiainsertionSort = arr;
    vector<int> arrCopiamergeSort= arr;

            //utilizado para comprobar el orden.
    /*
    cout << "Se imprimiran los arreglos antes de ser ordenados y el algoritmo que los va a ordenar:" << endl;
    cout << "Arreglo ordenado por los algoritmos:" << endl;
    for(int i = 0; i < arr.size(); ++i){
        cout << arr[i] << " ";
    }
    cout << endl;
    */

    cout << "Se usaran los algoritmos de Ordenamiento para ver cual demora menos en ordenar este arreglo." << endl;

    realizarCarrera(arrCopiaSelectionSort,"SelectionSort" );
    realizarCarrera(arrCopiaquickSort, "quickSort");
    realizarCarrera(arrCopiabubbleSort, "bubbleSort");
    realizarCarrera(arrCopiashellSort, "shellSort");
    realizarCarrera(arrCopiaheapSort, "heapSort");
    realizarCarrera(arrCopiainsertionSort, "insertionSort");
    realizarCarrera(arrCopiamergeSort, "mergeSort");

    cout << endl;
            // esto se utilizo para comprobar el orden.
    /*
    cout << "Arreglo ordenado por selectionSort:" << endl;
    for(int i = 0; i < arr.size(); ++i){
        cout << arrCopiaSelectionSort[i] << " ";
    }
    cout << endl;
    cout << "Arreglo ordenado por quickSort:" << endl;
    for(int i = 0; i < arr.size(); ++i){
        cout << arrCopiaquickSort[i] << " ";
    }
    cout << endl;
    cout << "Arreglo ordenado por bubbleSort:" << endl;
    for(int i = 0; i < arr.size(); ++i){
        cout << arrCopiabubbleSort[i] << " ";
    }
    cout << endl;
    cout << "Arreglo ordenado por shellSort:" << endl;
    for(int i = 0; i < arr.size(); ++i){
        cout << arrCopiashellSort[i] << " ";
    }
    cout << endl;
    cout << "Arreglo ordenado por heapSort:" << endl;
    for(int i = 0; i < arr.size(); ++i){
        cout << arrCopiaheapSort[i] << " ";
    }
    cout << endl;
    cout << "Arreglo ordenado por insertionSort:" << endl;
    for(int i = 0; i < arr.size(); ++i){
        cout << arrCopiainsertionSort[i] << " ";
    }
    cout << endl;
    cout << "Arreglo ordenado por mergeSort:" << endl;
    for(int i = 0; i < arr.size(); ++i){
        cout << arrCopiamergeSort[i] << " ";
    }
    cout << endl;
    */
}

int main() {
    const int amount = 10000;
    vector<int>arr, arrSorted,arrReverse;
    int random_value;

    cout << "Generando set de datos: " << endl;
    for (int i = 0; i < amount ; ++i) {
        arrSorted.push_back(i+1);
        arrReverse.push_back(amount-i);
        if ( i == 0 ) {
            random_value = 1 + rand() % (amount);
            arr.push_back(random_value);
        }
        else {
            random_value = 1 + rand() % (amount);
            arr.push_back(random_value);
        }
    }

    cout << "Se termino de generar los datos" << endl;

    int opcion;

    do{
        cout << "Bienvenido al menu principal, a continuacion seleccione una opcion:" << endl;
        cout << "1. Carrera Cola de Espera." << endl;
        cout << "2. Carrera Trazabilidad de Objetos." << endl;
        cout << "3. Carrera Eventos Cada Escenario." << endl;
        cout << "4. Salir." << endl;
        cin >> opcion;

        switch(opcion){
            case 1:
                empezarCarrera(arrSorted, "Cola de espera, arreglo en orden");
                empezarCarrera(arr,"Cola de espera, arreglo random");
                empezarCarrera(arrReverse, "Cola de espera, arreglo en reversa");

                break;
        }

    }while(opcion != 4);



    return 0;
}

