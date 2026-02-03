#include "Header.h"
#include <iomanip>

void InitDate(tm& date, int y, int m, int d)
{
    date = {};
    date.tm_year = y - 1900;
    date.tm_mon = m - 1;
    date.tm_mday = d;
}

void PrintDate(const tm& date)
{
    cout << setw(4) << date.tm_year + 1900 << "/ "
         << setw(2) << date.tm_mon + 1 << "/ "
         << setw(2) << date.tm_mday << endl;
}

void PrintDate(const DateArr& arrDate)
{
    for (int i = 0; i < arrDate.size; i++)
    {
        PrintDate(*arrDate.arr[i]);
    }
}

void InsertByIndex(DateArr& arrDate, tm* newDate, int index)
{
    if (index < 0 || index > arrDate.size) return;

    tm** temp = new tm*[arrDate.size + 1];

    for (int i = 0; i < index; i++)
        temp[i] = arrDate.arr[i];

    temp[index] = newDate;

    for (int i = index; i < arrDate.size; i++)
        temp[i + 1] = arrDate.arr[i];

    delete[] arrDate.arr;
    arrDate.arr = temp;
    arrDate.size++;
}

void AddLast(DateArr& arrDate, tm* newDate)
{
    InsertByIndex(arrDate, newDate, arrDate.size);
}

void DellByIndex(DateArr& arrDate, int index)
{
    if (index < 0 || index >= arrDate.size) return;

    delete arrDate.arr[index];

    tm** temp = new tm*[arrDate.size - 1];

    for (int i = 0, j = 0; i < arrDate.size; i++)
    {
        if (i == index) continue;
        temp[j++] = arrDate.arr[i];
    }

    delete[] arrDate.arr;
    arrDate.arr = temp;
    arrDate.size--;
}

int FindFirst(const DateArr& arrDate, tm* date)
{
    for (int i = 0; i < arrDate.size; i++)
    {
        if (!CompareDate(arrDate.arr[i], date) &&
            !CompareDate(date, arrDate.arr[i]))
            return i;
    }
    return -1;
}

bool CompareDate(tm* date1, tm* date2)
{
    time_t t1 = mktime(date1);
    time_t t2 = mktime(date2);
    return t1 > t2;
}

void Sort(DateArr& arrDate)
{
    for (int n = 1; n < arrDate.size; n++)
    {
        for (int i = 0; i < arrDate.size - n; i++)
        {
            if (CompareDate(arrDate.arr[i], arrDate.arr[i + 1]))
                swap(arrDate.arr[i], arrDate.arr[i + 1]);
        }
    }
}

void InsertSort(DateArr& arrDate)
{
    for (int i = 1; i < arrDate.size; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (CompareDate(arrDate.arr[j - 1], arrDate.arr[j]))
                swap(arrDate.arr[j], arrDate.arr[j - 1]);
            else break;
        }
    }
}

void SaveToFile(const char* filePath, const DateArr& arrDate)
{
    FILE* f = nullptr;
    fopen_s(&f, filePath, "wb");
    if (!f) return;

    fwrite(&arrDate.size, sizeof(int), 1, f);

    for (int i = 0; i < arrDate.size; i++)
        fwrite(arrDate.arr[i], sizeof(tm), 1, f);

    fclose(f);
}

void ReadFromFile(const char* filePath, DateArr& arrDate)
{
    FILE* f = nullptr;
    fopen_s(&f, filePath, "rb");
    if (!f) return;

    FreeArr(arrDate);

    fread(&arrDate.size, sizeof(int), 1, f);
    arrDate.arr = new tm*[arrDate.size];

    for (int i = 0; i < arrDate.size; i++)
    {
        arrDate.arr[i] = new tm;
        fread(arrDate.arr[i], sizeof(tm), 1, f);
    }

    fclose(f);
}

void FreeArr(DateArr& arrDate)
{
    for (int i = 0; i < arrDate.size; i++)
        delete arrDate.arr[i];

    delete[] arrDate.arr;
    arrDate.arr = nullptr;
    arrDate.size = 0;
}
