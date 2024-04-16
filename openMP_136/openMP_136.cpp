// openMP_136.cpp 

// author: Денисова Екатерина

//136н. Даны натуральное число n, действительные числа a1,..., an. Вычислить:
// sum((sqrt(abs(a[i])) - a[i])^2)
#include <iostream>
#include <omp.h> // openMP
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

// функция заполнения массива случайными числами
// из диапазона от min до max
void fill_random(float* arr, int size, float min, float max) {
    
    for (int i = 0; i < size; i++) {
        arr[i] = min + static_cast<double>(rand()) / (RAND_MAX / (max - min));
    }
}


int main()
{

    setlocale(LC_ALL, "Russian");

    // Инициализация генератора случайных чисел
    srand(time(nullptr));

    int n = 100'000'000; // Количество элементов
    float* a = new float[n];

    fill_random(a, n, 0.0, 0.3);

    double sum1 = 0.0;
    double sum = 0.0;

    // начало измерения времени
    auto startTime1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        sum1 += pow(sqrt(abs(a[i])) - a[i], 2);
    }
    // конец измерения времени
    auto endTime1 = chrono::high_resolution_clock::now();
    
    // рассчитываем время выполнения перемножения
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(endTime1 - startTime1).count();
    std::cout << "Результат вычислений: " << sum1 << std::endl;
    cout << "Время выполнения: " << duration1 << endl << endl;



    // начало измерения времени
    auto startTime = chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < n; i++) {
            sum += pow(sqrt(abs(a[i])) - a[i], 2);
        }

        #pragma omp single
        std::cout << "Число потоков: " << omp_get_num_threads() << std::endl;
    }
    // конец измерения времени
    auto endTime = chrono::high_resolution_clock::now();

    // рассчитываем время выполнения перемножения
    auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

    //std::cout << "Число потоков: " << omp_get_num_threads() << std::endl;

    /*for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }*/
    std::cout << "Результат вычислений с использованием библиотеки OpenMP: " << sum << std::endl;
    cout << "Время выполнения: " << duration << endl;
    
    
    
}

 