#ifndef POSPARAIN
#define POSPARAIN
#include <iostream>
#include <sstream>
#include "Pilha.h"
using namespace std;

/* Converte a expressão posfixa em infixa */
string PosParaIn(FilaArranjo<char> &expressao)
{
	string exp = "";
	while(expressao.GetTamanho() > 0)
		exp = exp + expressao.Desenfileira();
	for(int i = 0; i < exp.length(); i++)
		expressao.Enfileira(exp[i]);
	PilhaArranjo<string> pilha;
    /* Divide a expressão em tokens */
	istringstream iss(exp);
    string token;
    
    while (iss >> token){
        /* Se o token for um número ele é colocado entre parênteses e empilhado */
		if (token[0] >= '0' && token[0] <= '9')
		{
		string aux = "( " + token + " )";
		pilha.Empilha(aux);
		}
		else
		{
			/* Se o token for um operador, dois números são desempilhados e uma string 
			resultante é formada com os dois números e o operador entre parênteses 
			e essa string é empilhada */
			string op1 = pilha.Desempilha();
			string op2 = pilha.Desempilha();
			string res = "( " + op2 + " " + token + " " + op1 + " )";
            pilha.Empilha(res);
		}
	}
	/* Retorna a string final com a expressão infixa */
	return pilha.Desempilha();
}

#endif
