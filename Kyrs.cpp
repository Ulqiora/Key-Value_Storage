#include <iostream>

#define MAX_SIZE 100

int main() {
    int numeralOrder[MAX_SIZE] = {};
    int N;
    std::cout << "Enter order of square: ";
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cout << "array[" << i << "] = ";
        std::cin >> numeralOrder[i];
    }
    for (int i = 0; i < N; i++) {
        int lastElement = numeralOrder[N-1];
        for (int j = N - 1; j > 0; j--) numeralOrder[j] = numeralOrder[j - 1];
        numeralOrder[0] = lastElement;
        for (int j = 0; j < N; j++) std::cout << numeralOrder[j] << " ";
        std::cout << '\n';
    }
    return 0;
}