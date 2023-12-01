#include <iostream>
#include <limits.h>
using namespace std;

//Сравнения:
//В лучшем случае быстрая сортировка имеет сложность O(n log n) для сравнений, что обычно лучше, 
//чем поразрядная сортировка. Поразрядная сортировка имеет линейную сложность O(n* k) для сравнений,
//где k - число разрядов чисел.
//Перестановки :
//Быстрая сортировка, в худшем случае, может иметь до O(n ^ 2) перестановок, но обычно имеет O(n log n) перестановок.
//Поразрядная сортировка не выполняет прямых обменов элементов, как быстрая сортировка, поэтому количество перестановок
//зависит от особенностей реализации алгоритма и типа данных, но обычно оно меньше, чем у быстрой сортировки 
//в худшем случае.

void qsortRecursive(int mas[], int size) {
  // Указатели в начало и в конец массива
  int i = 0;
  int j = size - 1;

  // Центральный элемент массива
  int mid = mas[size / 2];

  // Делим массив
  do {
    // Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
    // В левой части массива пропускаем(оставляем на месте) элементы, которые
    // меньше центрального
    while (mas[i] < mid) {
      i++;
    }
    // В правой части пропускаем элементы, которые больше центрального
    while (mas[j] > mid) {
      j--;
    }

    // Меняем элементы местами
    if (i <= j) {
      int tmp = mas[i];
      mas[i] = mas[j];
      mas[j] = tmp;
      i++;
      j--;
    }
  } while (i <= j);

  // Рекурсивные вызовы, если осталось, что сортировать
  if (j > 0) {
    //"Левый кусок"
    qsortRecursive(mas, j + 1);
  }
  if (i < size) {
    //"Правый кусок"
    qsortRecursive(&mas[i], size - i);
  }
}
//определение разряда числа
int digit(int n, int k, int N, int M) { 
    return (n >> (N * k) & (M - 1)); 
}

// first_mas_ptr = l
// last_mas_ptr = r
void _radixsort(int *first_mas_ptr, int *last_mas_ptr, int N) {
  int k = (32 + N - 1) / N; //разряд числа, N - количество бит для разряда, определяем количество итераций(разрядов) для сортирвоки
  int M = 1 << N; //основание системы счисления
  int sz = last_mas_ptr - first_mas_ptr;
  int *b = new int[sz];
  int *c = new int[M]; //массив для подсчета элементов в корзинах
  for (int i = 0; i < k; i++) { //цикл для каждой итерации сортировок по разрядам
    for (int j = 0; j < M; j++) //обнуляем массив подсчета элементов в корзинах
      c[j] = 0;
    for (int *j = first_mas_ptr; j < last_mas_ptr; j++) //подсчитываем количество элементов, попадающих в корзину
      c[digit(*j, i, N, M)]++;
    for (int j = 1; j < M; j++)//вычисляем суммарное количество элементов, которые должны находиться в массиве
      c[j] += c[j - 1];
    for (int *j = last_mas_ptr - 1; j >= first_mas_ptr; j--) //распределяем элементы во временный массив в соответствии с их разрядами
      b[--c[digit(*j, i, N, M)]] = *j;
    //Копируем отсортированный временный массив обратно в исходный массив
    int cur = 0;
    for (int *j = first_mas_ptr; j < last_mas_ptr; j++)
      *j = b[cur++];
  }
  delete[] b;
  delete[] c;
}
void radixsort(int *first_mas_ptr, int *last_mas_ptr) {
  _radixsort(first_mas_ptr, last_mas_ptr, 8); //Вызываем вспомогательную функцию radixsort с N=8 (8 битами в разряде)
}

int main() {
  system("chcp 1251");
  int mas[] = {255, 3, 5, 2, 1, 7, 9, 8, 53, 48, 4, 321, 43, 99, -321};
  int size = sizeof(mas) / sizeof(mas[0]);
  int key;
  bool isRunning = true;

  cout << "Начальный массив\n";
  for (int i = 0; i < size; i++) {
    cout << mas[i] << " ";
  }
  cout << endl;

  do {
    do {
      std::cout << "Введите номер сортировки 1 - быстрая, 2- поразрядная, 3 - "
                   "выход из программы ";
      std::cin >> key;
    } while (key < 0 && key > 4);
    switch (key) {
    case 1:
      qsortRecursive(mas, size);
      for (int i = 0; i < size; i++) {
        cout << mas[i] << " ";
      }
      cout << endl;
      break;
    case 2:
      radixsort(mas, &mas[size]);
      for (int i = 0; i < size; i++) {
        cout << mas[i] << " ";
      }
      cout << endl;
      break;
    case 3:
      isRunning = false;
      break;
    }
  } while (isRunning);

  return 0;
}
