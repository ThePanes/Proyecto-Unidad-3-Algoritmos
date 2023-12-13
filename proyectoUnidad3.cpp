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

    for(int j = n/2; j > 0; j /= 2){
        for(int i = j; i < n; ++i){
            int temp = arr[i];
            int f;
            for(f = i; f >= j && arr[f - j] > temp; f-= j ){
                arr[f] = arr[f- j];
            }
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

    /*
    cout << "se imprimira el arreglo aleatorio antes de ser ordenado" <<endl;
    for(int i = 0; i < amount; ++i){
            cout << arr[i] << " ";
    }

    cout << endl;

    cout << "Se imprimira el segundo arreglo ordenado antes de ser ordenado" << endl;
    for(int i = 0; i < amount; ++i){
            cout << arrSorted[i] << " ";
    }

    cout << endl;

    cout << "Se imprimira el tercer arreglo alrevez antes de ser ordenado" << endl;
    for(int i = 0; i < amount; ++i){
            cout << arrReverse[i] << " ";
    }
    cout << endl;
        */
    unordered_map<string, double> results;
    results["SelectionSort"] = getResultFromAlg(arr);
    vector<int> arr1,arr2;
    arr1.assign(arr.begin(), arr.end());
    arr2.assign(arr.begin(), arr.end());

    /*
    cout << "Se imprimira el arreglo aleatorio ordenado" << endl;
    for(int i = 0; i < amount; ++i){
            cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Se imprimira el arreglo contado ordenado" << endl;
    for(int i = 0; i < amount; ++i){
            cout << arrSorted[i] << " ";
    }
    cout << endl;
    cout << "Se imprimira el arreglo alrevez ordenado" << endl;
    for(int i = 0; i < amount; ++i){
            cout << arrReverse[i] << " ";
    }
    cout << endl;

    */


    int id = 1;
    for (const auto& pair : results) {
        const string& key = pair.first;
        double value = pair.second;
        cout << id << ". " << key << ", " << fixed << value << setprecision(5)
        << endl;
        id++;
    }
    return 0;
}

