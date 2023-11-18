/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_LENGTH 20

// Função para verificar se um número de cartão é válido usando o Algoritmo de Luhn
int luhnAlgorithmValidation(unsigned long long int cardNumber) {
    int sum = 0, isOdd = 1;

    while (cardNumber > 0) {
        int digit = cardNumber % 10;

        if (isOdd) {
            digit *= 2;

            if (digit > 9) {
                digit = digit % 10 + digit / 10;
            }
        }

        sum += digit;
        isOdd = !isOdd;
        cardNumber /= 10;
    }

    return (sum % 10 == 0) ? 1 : 0;
}

// Função para classificar o tipo de cartão
void classifyCard(unsigned long long int cardNumber) {
    int length = floor(log10(cardNumber)) + 1;
    int isValid = luhnAlgorithmValidation(cardNumber);

    if (isValid) {
        if (length == 15 && (cardNumber / 10000000000000 == 34 || cardNumber / 10000000000000 == 37)) {
            printf("AMEX\n");
        } else if (length == 16 && (cardNumber / 100000000000000 == 51 || cardNumber / 100000000000000 == 52 ||
                                   cardNumber / 100000000000000 == 53 || cardNumber / 100000000000000 == 54 ||
                                   cardNumber / 100000000000000 == 55)) {
            printf("MASTERCARD\n");
        } else if ((length == 13 || length == 16) && (cardNumber / 1000000000000 == 4 ||
                                                     cardNumber / 1000000000000000 == 4)) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }
}

int main() {
    char filePath[MAX_LENGTH];
    printf("Digite o caminho do arquivo: ");
    scanf("%s", filePath);

    FILE *file = fopen(filePath, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    unsigned long long int cardNumber;

    while (fscanf(file, "%llu", &cardNumber) == 1) {
        classifyCard(cardNumber);
    }

    fclose(file);

    return 0;
}

