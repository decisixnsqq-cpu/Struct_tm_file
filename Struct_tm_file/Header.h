#pragma once
#include <iostream>
#include <ctime>

using namespace std;

struct DateArr
{
    tm** arr;
    int size;

    DateArr()
    {
        arr = nullptr;
        size = 0;
    }
};

// базовые функции
void InitDate(tm& date, int y, int m, int d);
void PrintDate(const tm& date);
void PrintDate(const DateArr& arrDate);

// работа с массивом
void InsertByIndex(DateArr& arrDate, tm* newDate, int index);
void AddLast(DateArr& arrDate, tm* newDate);
void DellByIndex(DateArr& arrDate, int index);
int FindFirst(const DateArr& arrDate, tm* date);

// сортировка
bool CompareDate(tm* date1, tm* date2);
void Sort(DateArr& arrDate);
void InsertSort(DateArr& arrDate);

// файлы
void SaveToFile(const char* filePath, const DateArr& arrDate);
void ReadFromFile(const char* filePath, DateArr& arrDate);

// очистка памяти
void FreeArr(DateArr& arrDate);
