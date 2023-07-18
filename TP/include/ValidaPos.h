#ifndef VALIDAPOS
#define VALIDAPOS
#include <iostream>
#include <string>
#include "Pilha.h"

using namespace std;

bool ValidaPos(string expr)
{
    /* Verifica se os caracteres são válidos */
    for (int i = 0; i < expr.size(); i++)
    {
        if (!(expr[i] >= '0' && expr[i] <= '9') && expr[i] != '.' && expr[i] != '+' && expr[i] != '-' && expr[i] != '*' && expr[i] != '/' && expr[i] != ' ')
        {
            return false;
        }
    }

   /* verifica que sempre há dois operandos antes de um operador na 
   expressão, de forma que se um operador for lido um operando é decrescido.
   Também verifica se os números float são válidos*/
    PilhaArranjo<float> pilha;
    for (int i = 0; i < expr.length(); i++)
    {
        if ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.')
        {
            float num = 0.0;
            float decimal = 1.0;
            while (i < expr.length() && ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.'))
            {
                if (expr[i] == '.')
                {
                    decimal = 0.1;
                }
                else
                {
                    num = num * 10 + (expr[i] - '0') * decimal;
                    decimal = decimal * 10.0;
                }
                i++;
            }
            i--;
            pilha.Empilha(num);
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
        {
            if (pilha.GetTamanho() < 2)
            {
                return false;
            }
            pilha.Desempilha();
        }
        else if (expr[i] != ' ')
        {
            return false;
        }
    }

    if (pilha.GetTamanho() == 1)
        return true;
    else
        return false;
}

#endif