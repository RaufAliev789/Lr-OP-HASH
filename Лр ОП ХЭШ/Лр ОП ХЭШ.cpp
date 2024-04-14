#include <iostream>
#include <string>
#include <algorithm>

int* HS_hash(const std::string* As, int size, int P, int M) {
    int* Hs = new int[size];
    for (int i = 0; i < size; i++) {
        int hash = 0;
        for (char c : As[i]) {
            hash = (hash * P + c) % M;
        }
        Hs[i] = hash;
    }
    std::sort(Hs, Hs + size);
    return Hs;
}

int binarySearch(const std::string* As, const int* Hs, int size, const std::string& Is, int P, int M) {
    int hash = 0;
    for (char c : Is) {
        hash = (hash * P + c) % M;
    }
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (Hs[mid] == hash) {
            if (As[mid] == Is) {
                return mid;
            }
            else {
                int index = mid;
                while (index > 0 && Hs[index - 1] == hash) {
                    if (As[index - 1] == Is) {
                        return index - 1;
                    }
                    index--;
                }
                index = mid;
                while (index < size - 1 && Hs[index + 1] == hash) {
                    if (As[index + 1] == Is) {
                        return index + 1;
                    }
                    index++;
                }
                return -1;
            }
        }
        else if (Hs[mid] < hash) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "ru");
    int size;
    std::cout << "Введите размер массива: ";
    std::cin >> size;

    std::string* As = new std::string[size];
    std::cout << "Введите элементы массива As:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cin >> As[i];
    }

    int P, M;
    std::cout << "Введите значения P и M: ";
    std::cin >> P >> M;

    int* Hs = HS_hash(As, size, P, M);

    std::string Is;
    std::cout << "Введите строку Is: ";
    std::cin >> Is;

    int index = binarySearch(As, Hs, size, Is, P, M);
    if (index != -1) {
        std::cout << "Ias: " << index << std::endl;
    }
    else {
        std::cout << "Строка не найдена" << std::endl;
    }

    delete[] As;
    delete[] Hs;

    return 0;
}
