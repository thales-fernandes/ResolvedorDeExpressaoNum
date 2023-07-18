#ifndef VALIDAIN
#define VALIDAIN
#include <iostream>
#include <string>
#include <algorithm>
#include "Pilha.h"
#include "Fila.h"

using namespace std;

bool ValidaIn(string expressao)
{
    /* Tira os espaços da expressão */
    expressao.erase(remove(expressao.begin(), expressao.end(), ' '), expressao.end());

    /* Checa se os caracteres são válidos */
    for (int i = 0; i < expressao.size(); i++)
    {
        if (!(expressao[i] >= '0' && expressao[i] <= '9') && expressao[i] != '.' && expressao[i] != '+' && expressao[i] != '-' 
        && expressao[i] != '*' && expressao[i] != '/' && expressao[i] != '(' && expressao[i] != ')')
        {
            return false;
        }
    }

    /* Checa se os números da expressão são inteiros ou float válidos 
    e se não há dois números em sequência */
    bool ant = false;
    for (int i = 0; i < expressao.size(); i++)
    {
        if ((expressao[i] >= '0' && expressao[i] <= '9') || expressao[i] == '.')
        {
            if (ant)
            {
                return false;
            }
            /* A partir de um número encontrado nós pegamos uma substring até que um espaço seja
            encontrado e então convertemos para float e checamos o seu tamanho. 
            Se o número for negativo será retornado falso */
            float convertido = stof(expressao.substr(i));
            int tamanho = to_string(convertido).size();
            if (tamanho == 0 || convertido < 0)
            {
                return false;
            }
            /* Um número foi encontrado e a variável bool recebe valor lógico igual a true */
            ant = true;
            i = i + (tamanho - 1);
        }
        else
        {
            ant = false;
        }
    }

    /* Verifica se não há dois operadores seguidos */
    bool operadorAnterior = false;
    for (int i = 0; i < expressao.size(); i++)
    {
        if (expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*' || expressao[i] == '/')
        {
            if (operadorAnterior)
            {
                return false;
            }
            operadorAnterior = true;
        }
        else
        {
            operadorAnterior = false;
        }
    }

    /* Empilha e desempilha os parênteses para verificar se todos que foram 
    abertos também foram fechados */
    PilhaArranjo<char> pilha;
    for (int i = 0; i < expressao.size(); i++)
    {
        if (expressao[i] == '(')
        {
            pilha.Empilha(expressao[i]);
        }
        else if (expressao[i] == ')')
        {
            if (pilha.GetTamanho() == 0)
            {
                return false;
            }
            else
            {
                pilha.Desempilha();
            }
        }
    }
    if (pilha.GetTamanho() > 0)
    {
        return false;
    }

    /* Checa se o número de operadores é igual ao número de operandos menos 1 */
    int nOperandos = 0;
    int nOperadores = 0;
    for (int i = 0; i < expressao.size(); i++)
    {
        /* Se encontrar um número, percorre a string até o número acabar e adiciona
        uma unidade na variável nOperandos */
        if ((expressao[i] >= '0' && expressao[i] <= '9') || expressao[i] == '.')
        {
            nOperandos++;
            while ((expressao[i] >= '0' && expressao[i] <= '9') || expressao[i] == '.')
            {
                i++;
            }
            i--;
        }
        else if (expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*' || expressao[i] == '/')
        {
            /* Se encontrar um operador adiciona uma unidade na variável nOperadores */
            nOperadores++;
        }
    }
    if (nOperandos - nOperadores != 1)
    {
        /* Se não houver exatamente um operando a mais que operadores retorn a falso */
        return false;
    }

    return true;
}

#endif