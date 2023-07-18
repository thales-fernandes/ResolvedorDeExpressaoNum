#ifndef INPARAPOS
#define INPARAPOS
#include <iostream>
#include <cstring>
#include "Pilha.h"
#include "Fila.h"

using namespace std;

/* Determina a precedência dos operadores*/
int prioridade(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

/* Converte a expressão infixa para posfixa */
string InParaPos(FilaArranjo<char> &s)
{
    string exp = "";
    while(s.GetTamanho() > 0)
        exp = exp + s.Desenfileira();
    for(int j = 0; j < exp.length(); j++)
        s.Enfileira(exp[j]);
    PilhaArranjo<char> pilha;
    string convertida = "";

    for (int i = 0; i < exp.length(); i++)
    {
        if (exp[i] == ' ')
            continue;

        /* Adiciona os operandos na string final */
        if ((exp[i] >= '0' && exp[i] <= '9') || exp[i] == '.')
        {
            while ((exp[i] >= '0' && exp[i] <= '9') || exp[i] == '.')
            {
                convertida += exp[i];
                i++;
            }
            convertida += " ";
            i--;
        }

        /* Coloca os parênteses de abertura na pilha */
        else if (exp[i] == '(')
        {
            pilha.Empilha(exp[i]);
        }

        /* Tira elementos da pilha e coloca na string final se for parênteses
         de fechamento */
        else if (exp[i] == ')')
        {
            while ((pilha.GetTamanho() > 0) && pilha.topov() != '(')
            {
                convertida += pilha.Desempilha();
                convertida += " ";
            }
            pilha.Desempilha();
        }

        /* Caso seja um operador, tira elementos da pilha de acordo com a precedência dos operadores
        e coloca na string de saída*/
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
        {
            while ((pilha.GetTamanho() > 0) && prioridade(exp[i]) <= prioridade(pilha.topov()))
            {
                convertida += pilha.Desempilha();
                convertida += " ";
            }
            pilha.Empilha(exp[i]);
        }
    }

    /* Coloca os elementos na pilha na string de saída */
    while (pilha.GetTamanho() > 0)
    {
        convertida += pilha.Desempilha();
        convertida += " ";
    }
    /* Retorna a string final com a expressão convertida */
    return convertida;
}

#endif
