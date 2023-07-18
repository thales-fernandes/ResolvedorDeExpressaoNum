#ifndef CALCULO
#define CALCULO
#include <iostream>
#include <string>
#include "Pilha.h"
#include <sstream>
#include "Fila.h"

using namespace std;

struct DivisaoPorZero{
    int chavealeatoria;
};

/* Realiza o cálculo entre dois números de acordo com o operador*/
float operacao(float a, float b, char x)
{
    switch (x)
    {
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
        break;
    case '/':
        if(b == 0){
            DivisaoPorZero a_;
            throw a_;
        }
        return a / b;
        break;
    case '*':
        return a * b;
        break;
    }
    return 0.0;
}

/* Divide a expressão em tokens e realiza operações até encontrar o resultado final*/
float Calculo(FilaArranjo<char> &fila)
{
    string x = "";
    while(fila.GetTamanho() > 0)
        x = x + fila.Desenfileira();
    for(int i = 0; i < x.length(); i++){
        fila.Enfileira(x[i]);
    }
    float num;
    PilhaArranjo<float> pilha;
    float aux1, aux2;
    /* Divide a expressão em tokens */
    istringstream iss(x);
    string token;

    while (iss >> token)
    {
        /* Se o token for operador, Desempilha os dois números no topo da pilha e 
        realiza o cálculo entre esses dois números de acordo com o operador */
        if (token[0] == '+' || token[0] == '-' || token[0] == '/' || token[0] == '*')
        {
            aux1 = pilha.Desempilha();
            aux2 = pilha.Desempilha();
            num = operacao(aux2, aux1, token[0]);
            pilha.Empilha(num);
        }
        else
        {
            /* Nesse caso, o token é um número que será convertido para float e empilhado */
            num = stof(token);
            pilha.Empilha(num);
        }
    }
    aux1 = pilha.Desempilha();
    /* Retorna o valor final da expressão resolvida */
    return aux1;
}

#endif

