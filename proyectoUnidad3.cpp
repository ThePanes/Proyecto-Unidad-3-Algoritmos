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
int main(int argc, char* argv[]) {
    const int amount = 1000;
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
    unordered_map<string, double> results;
    results["SelectionSort"] = getResultFromAlg(arr);
    vector<int> arr1,arr2;
    arr1.assign(arr.begin(), arr.end());
    arr2.assign(arr.begin(), arr.end());
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

