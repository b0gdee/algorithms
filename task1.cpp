#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

// Сортировка пузырьком
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Быстрая сортировка
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Сортировка Шелла
void shellSort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Функция для генерации случайного массива
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Функция для измерения времени выполнения сортировки
long long measureTime(void (*sortFunction)(vector<int>&), vector<int>& arr) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

int main() {
    vector<int> sizes = {100, 1000, 10000, 100000}; // Размеры массивов для тестирования
    int numRuns = 10; // Количество запусков для усреднения

    for (int size : sizes) {
        long long bubbleTime = 0;
        long long quickTime = 0;
        long long shellTime = 0;

        for (int i = 0; i < numRuns; i++) {
            vector<int> arr = generateRandomArray(size);

            vector<int> arr1 = arr;
            bubbleTime += measureTime(bubbleSort, arr1);

            vector<int> arr2 = arr;
            quickTime += measureTime([](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, arr2);

            vector<int> arr3 = arr;
            shellTime += measureTime(shellSort, arr3);
        }

        cout << "Array size: " << size << endl;
        cout << "Bubble Sort Average Time: " << bubbleTime / numRuns << " microseconds" << endl;
        cout << "Quick Sort Average Time: " << quickTime / numRuns << " microseconds" << endl;
        cout << "Shell Sort Average Time: " << shellTime / numRuns << " microseconds" << endl;
        cout << "-------------------------" << endl;
    }

    return 0;
}