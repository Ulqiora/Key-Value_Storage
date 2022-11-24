#include <iomanip>
#include <iostream>

#define MAX_SIZE 100

void latinSquareWithInt() {
    int numeralOrder[MAX_SIZE] = {};
    int N;
    std::cout << "Enter order of square: ";
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cout << "array[" << i << "] = ";
        std::cin >> numeralOrder[i];
    }
    for (int i = 0; i < N; i++) {
        int lastElement = numeralOrder[N - 1];
        for (int j = N - 1; j > 0; j--) numeralOrder[j] = numeralOrder[j - 1];
        numeralOrder[0] = lastElement;
        for (int j = 0; j < N; j++) std::cout << std::setw(3) << numeralOrder[j] << " ";
        std::cout << '\n';
    }
}
void latinSquareWithChar() {
    char numeralOrder[MAX_SIZE] = {};
    int N;
    std::cout << "Enter order of square: ";
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cout << "array[" << i << "] = ";
        std::cin >> numeralOrder[i];
    }
    for (int i = 0; i < N; i++) {
        int lastElement = numeralOrder[N - 1];
        for (int j = N - 1; j > 0; j--) numeralOrder[j] = numeralOrder[j - 1];
        numeralOrder[0] = lastElement;
        for (int j = 0; j < N; j++) std::cout << numeralOrder[j] << " ";
        std::cout << '\n';
    }
}

int main() {
    int chooseCase;
    std::cout << "Select the Latin square generation mode:\n1 - With char.\n2 - With int.\nChoose:";
    std::cin >> chooseCase;
    if (chooseCase == 1) {
        latinSquareWithChar();
    } else if (chooseCase == 2) {
        latinSquareWithInt();
    } else {
        std::cout << "Incorrect mode.\n";
    }
    return 0;
}