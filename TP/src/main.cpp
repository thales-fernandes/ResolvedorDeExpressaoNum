#include <iostream>
#include <string>
#include "ValidaIn.h"
#include "ValidaPos.h"
#include "PosParaIn.h"
#include "Calculo.h"
#include "InParaPos.h"
#include <iomanip>
#include "Fila.h"

/* Armazena a expressão na fila */
void Armazena(FilaArranjo<char> &fila, string s){
    for(int i = 0; i < s.length(); i++)
        fila.Enfileira(s[i]);
}

/* Realiza o resolvedor de expressões ao agrupar funções, ler a entrada
e imprimir a saída */
int main()
{
    /* string s e c usadas para captar os comandos "LER INFIXA" "LER POSFIXA"
    "INFIXA" "POSFIXA" e "RESOLVE". A string z é usada para captar a expressão
    de entrada */
    string s, z, c;
    z = "";
    FilaArranjo<char> exp;
    bool infixa = false;
    bool posfixa = false;
    while (cin >> s)
    {
        /* Lê a expressão de entrada */
        if (s == "LER")
        {
            cin >> c;
            if ((infixa) || (posfixa))
            {
                infixa = false;
                posfixa = false;
            }
            if(exp.GetTamanho() > 0)
                exp.Limpa();
            if (c == "INFIXA")
            {
                getline(cin, z);
                if (ValidaIn(z))
                {
                    infixa = true;
                    Armazena(exp, z);
                    cout << "EXPRESSAO OK: " << z << endl;
                }
                else
                {
                    cout << "ERRO: " << z << " NAO VALIDA" << endl;
                }
            }
            if (c == "POSFIXA")
            {
                getline(cin, z);
                if (ValidaPos(z))
                {
                    posfixa = true;
                    Armazena(exp, z);
                    cout << "EXPRESSAO OK: " << z << endl;
                }
                else
                {
                    cout << "ERRO: " << z << " NAO VALIDA" << endl;
                }
            }
        }
        /* Imprime a expressão armazenada na notação posfixa */
        if (s == "POSFIXA")
        {
            if (posfixa)
            {
                string aux = "";
                while(exp.GetTamanho() > 0)
                    aux = aux + exp.Desenfileira();
                cout << "POSFIXA: " << aux << endl;
                Armazena(exp, aux);
            }
            else
            {
                if (infixa)
                {
                    string aux = InParaPos(exp);
                    cout << "POSFIXA: " << aux << endl;
                }
                else
                {
                    cout << "ERRO: " << z << " NAO EXISTE" << endl;
                }
            }
        }
        /* Imprime a expressão armazenada na notação infixa */
        if (s == "INFIXA")
        {
            if (infixa)
            {
                string aux = "";
                while(exp.GetTamanho() > 0)
                    aux = aux + exp.Desenfileira();
                cout << "INFIXA: " << aux << endl;
                Armazena(exp, aux);
            }
            else
            {
                if (posfixa)
                {
                    cout << "INFIXA: " << PosParaIn(exp) << endl;
                }
                else
                {
                    cout << "ERRO: " << z << " NAO EXISTE" << endl;
                }
            }
        }
        /* Imprime o resultado da expressão armazenada */
        if (s == "RESOLVE")
        {
            if (posfixa)
            {
                float resultado = Calculo(exp);
                cout << fixed << setprecision(6);
                cout << "VAL: " << resultado << endl;
            }
            else if (infixa)
            {
                string aux;
                aux = InParaPos(exp);
                FilaArranjo<char> fila;
                Armazena(fila, aux);
                float resultado = Calculo(fila);
                cout << fixed << setprecision(6);
                cout << "VAL: " << resultado << endl;
                fila.Limpa();
            }
            else
            {
                cout << "ERRO: " << z << " NAO EXISTE" << endl;
            }
        }
    }

    return 0;
}