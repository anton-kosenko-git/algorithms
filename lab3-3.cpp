/* ЛАБОРАТОРНА РОБОТА №3
Проектування алгоритмів
Студент Косенко А.П.
Завдання:
1. Розробити програму, що виконує наступні види сортування: 
- вибір; - пірамідальне; - за розрядами
2.	Згенерувати масив розмірності: 10000, 100000 елементів:
а. 1000 - відсортований за зростанням;
b. 10000 - з випадковими елементами (кількість генерувань = 1000);
c. 100000 - відсортований за спаданням.
3. Відсортувати одержані масиви за зростанням, отримавши такі змінні:
а. кількість порівнянь;
b. кількість обмінів.
*/

#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

int* initArray(int arr[], int size){
	srand(time(0)); 
    for(int i = 0; i < size; i++){
        arr[i] = rand() % 100;
	}
	return arr;
}

void printArr(int arr[], int size){
    for(int i = 0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

 
 void selectionSort(int arr[], int size, int* compare, int* change){
	 int temp = 0;
     int i, smallestIndex, current;
	 // Внешний цикл: перебираем каждый элемент массива (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него дойдем)
	for (i = 0; i < size - 1; i++)
	{
		// В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
		// Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
		smallestIndex = i;
         
		// Внутренний цикл: ищем наименьший элемент в неотсортированной части массива
		for (current = i + 1; current < size; current++)
		{
			// счетчик сравнений++
            compare++;
            // Если мы нашли элемент, который меньше текущего,
			if (arr[current] < arr[smallestIndex])
				// то запоминаем его
				smallestIndex = current;
		}
 
		// smallestIndex теперь наименьший элемент. 
                // Меняем местами наше текущее наименьшее число с тем, которое мы обнаружили
		    temp = arr[smallestIndex];
            arr[smallestIndex] = arr[i];
            arr[i] = temp;
            // счетчик обменов++
            change++;
	}
}

// Процедура для преобразования в двоичную кучу поддерева с корневым узлом i, что является
// индексом в arr[]. n - размер кучи

void heapify(int arr[], int n, int i, int* comp, int* sw)
{
    int largest = i;   
// Инициализируем наибольший элемент как корень
    int l = 2 * i + 1; // левый = 2 * i + 1
    int r = 2 * i + 2; // правый = 2*i + 2

 // Если левый дочерний элемент больше корня
    if (l < n && arr[l] > arr[largest]){
        largest = l;
        comp++;
    }

   // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && arr[r] > arr[largest]){
        largest = r;
        comp++;
    }

    // Если самый большой элемент не корень
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        sw++;

// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, n, largest, comp, sw);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(int arr[], int n, int* comp, int* sw)
{
    //*compare = 0;
    //*change = 0;
  // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comp, sw);

   // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--)
    {
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0, comp, sw);
    }
}

// Поиск максимального значения в массиве
int getMax(int arr[], int n, int* compare)
{
    int max = arr[0];
    for (int i = 1; i < n; i++){
        compare++;
        if (arr[i] > max){
            max = arr[i];
            compare++;
        }
    }
    return max;
}
 
// Функция сортировки подсчетом для arr[] согласно
// переменной представленной exp
void countSort(int arr[], int n, int exp, int* change)
{
    int output[n]; // создаем массив 
    int count[10] = { 0 };
    int i;
 
    // Сохраняем количество вхождений в count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    // Меняем count[i] таким образом чтобы count[i] теперь содержал фактическую 
    //  позицию числа в массиве output[]
    for (i = 1; i < 10; i++){
        count[i] += count[i - 1];
        change++;
    }
 
    // Строим массив output
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    // Копируем массив output в массив arr[], так чтобы arr[] теперь
    // содержал отсортированные значения согласно текущего числа 
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
// Функция поразрядной сортировки исходя из размера n
// Radix Sort
void radixSort(int arr[], int n, int* compare, int* change)
{
    compare = 0;
    change = 0;
    // Ищим максимальное число, чтобы узнать количество цифр
    int max = getMax(arr, n, compare);
 
    // Делаем сортировку подсчетом для каждой цифры так чтобы
    // вместо числа переданных цифр, передавалось число в определенной степени
    // где i текущий номер
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp, change);
}

int main()
{
    const int n1 = 100; // размер массива 1
    const int n2 = 100; // размер массива 2
    const int n3 = 100; // размер массива 3
   
    // создаем указатели для подсчета колличества сравнений и колличества обменов
    int* countCompares1;  
    int* countChanges1;
    int* countCompares2;  
    int* countChanges2;
    int* countCompares3;  
    int* countChanges3;
    
	int array[n1];
    
	//Заполняем массив-1 и выводим в консоль
	initArray(array, n1);
    cout << "******************SELECTION SORT******************" << endl;
    cout << "Initial array: " << endl;
	printArr(array, n1);
    	
	//Сортируем массив-1 по возрастанию выбором
	selectionSort(array, n1, countCompares1, countChanges1);
    cout << "Selection sorted array is: " << endl;
	printArr(array, n1);
    cout << endl;

    // выводим в консоль колличества сравнений и обменов
    cout << "Comparisons made: " << *countCompares1 << endl;
    cout << "Changes made: " << *countChanges1 << endl << endl;

    //delete[] array;

    //array = new int[n2];
    //Заполняем массив-2 и выводим в консоль
    initArray(array, n2);
    cout << "******************HEAP SORT******************" << endl;
    cout << "Initial array: " << endl;
	printArr(array, n2);
    
    //Сортируем массив-2 по возрастанию пирамидально
    heapSort(array, n2, countCompares2, countChanges2);
    cout << "Heap sorted array is: " << endl;
    printArr(array, n2);
    cout << endl;

    // выводим в консоль колличества сравнений и обменов
    //cout << "Comparisons made: " << *countCompares2 << endl;
    //cout << "Changes made: " << *countChanges2 << endl;

    //delete[] array;
    
    //array = new int[n3];
    //Заполняем массив-3 и выводим в консоль
    initArray(array, n3);
    cout << "******************RADIX SORT******************" << endl;
    cout << "Initial array-3: " << endl;
	printArr(array, n3);

    //Сортируем массив-3 по возрастанию по розрядам
    radixSort(array, n3, countCompares3, countChanges3);
    cout << "Radix sorted array is:" << endl;
    printArr(array, n3);
    cout << endl;

    // выводим в консоль колличества сравнений и обменов
    cout << "Comparisons made: " << *countCompares3 << endl;
    cout << "Changes made: " << *countChanges3 << endl;

    delete [] array;

    return 0;
}