#ifndef FILA
#define FILA
#include <iostream>

using namespace std;

template <typename Tipo>
class Fila
{
public:
    Fila() { tamanho = 0; };
    int GetTamanho() { return tamanho; };
    bool Vazia() { return tamanho == 0; };
    virtual void Enfileira(Tipo item) = 0;
    virtual Tipo Desenfileira() = 0;
    virtual void Limpa() = 0;

protected:
    int tamanho;
};

template <typename Tipo>
class FilaArranjo : public Fila<Tipo>
{
public:
    FilaArranjo() : Fila<Tipo>()
    {
        frente = 0;
        tras = 0;
    };
    void Enfileira(Tipo item)
    {
        if (this->tamanho == MAXTAM)
            throw "Fila Cheia!";
        itens[tras] = item;
        // fila circular
        tras = (tras + 1) % MAXTAM;
        this->tamanho++;
    };
    Tipo Desenfileira()
    {
        Tipo aux;
        if (this->tamanho == 0)
            throw "Fila está vazia!";
        aux = itens[frente];
        // fila circular
        frente = (frente + 1) % MAXTAM;
        this->tamanho--;
        return aux;
    };
    void Limpa()
    {
        frente = 0;
        tras = 0;
        this->tamanho = 0;
    };
    Tipo Frente(){
        return itens[frente];
    }

private:
    int frente;
    int tras;
    static const int MAXTAM = 1000;
    Tipo itens[MAXTAM];
};

#endif
