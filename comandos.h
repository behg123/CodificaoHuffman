#ifndef COMANDOS_H
#define COMANDOS_H

#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

//-----------------------------------------------------------------------//
// Struct de arvore
//-----------------------------------------------------------------------//
struct TArvore
{
    char letra;
    int frequencia;
    TArvore *esq;
    TArvore *dir;

    TArvore()
    {
        this->frequencia = 0;
        this->esq = nullptr;
        this->dir = nullptr;
    }

    TArvore(char letra, int frequencia, TArvore *esq, TArvore *dir)
    {
        this->letra = letra;
        this->frequencia = frequencia;
        this->esq = esq;
        this->dir = dir;
    }

    TArvore(TArvore *&l)
    {
        this->letra = l->letra;
        this->frequencia = l->frequencia;
        this->esq = l->esq;
        this->dir = l->dir;
    }
};

struct TListaArvore
{
    TArvore *raiz;
    int quantidadeLetras;
};

//-----------------------------------------------------------------------//
// Struct de lista que contem a arvore
//-----------------------------------------------------------------------//
struct THuffman
{
    TArvore dado;
    THuffman *proximo;

    THuffman()
    {
        this->dado.frequencia = 0;
        this->dado.dir = this->dado.esq = nullptr;
        this->proximo = nullptr;
    }

    THuffman(char letra, int frequencia, TArvore *dir, TArvore *esq, THuffman *proximo)
    {
        this->dado.letra = letra;
        this->dado.frequencia = frequencia;
        this->dado.dir = dir;
        this->dado.esq = esq;
        this->proximo = proximo;
    }

    THuffman(TArvore *&l)
    {
        this->dado.letra = l->letra;
        this->dado.frequencia = l->frequencia;
        this->dado.esq = l->esq;
        this->dado.dir = l->dir;
    }
};

struct TListaHuffman
{
    THuffman *inicio;
};

//-----------------------------------------------------------------------//
// Struct do dicionario
//-----------------------------------------------------------------------//
struct TDicionario
{
    char letra;
    string numero;
    TDicionario *proximo;

    TDicionario(char letra, string numero, TDicionario *proximo)
    {
        this->letra = letra;
        this->numero = numero;
        this->proximo = proximo;
    }
    TDicionario(TDicionario *novo){
        this->letra = novo->letra;
        this->numero = novo->numero;
        this->proximo = novo->proximo;

    }
};

struct TListaDicionario
{
    TDicionario *inicio;
};

//-----------------------------------------------------------------------//
// Inicialização de listas
//-----------------------------------------------------------------------//
void InicializarArvore(TListaArvore &l)
{
    l.raiz = nullptr;
    l.quantidadeLetras = 0;
}

void InicializarDicionario(TListaDicionario &d)
{
    d.inicio = nullptr;
}

void InicializarHuffman(TListaHuffman &h)
{
    h.inicio = nullptr;
}

//-----------------------------------------------------------------------//-//
// Bubblesort
//-----------------------------------------------------------------------//-//
void BubbleSortLetras(TListaHuffman &h, int quantidadeLetras)
{
    for (int i = 1; i < quantidadeLetras; i++)
    {
        THuffman *nav = h.inicio;

        for (int k = 1; k < quantidadeLetras - i; k++)
        {
            while (nav->proximo != nullptr)
            {
                THuffman *prox = nav->proximo;
                if (nav->dado.frequencia > prox->dado.frequencia)
                {
                    swap(nav->dado.letra, prox->dado.letra);
                    swap(nav->dado.frequencia, prox->dado.frequencia);
                    swap(nav->dado.dir, prox->dado.dir);
                    swap(nav->dado.esq, prox->dado.esq);
                }
                nav = nav->proximo;
            }
        }
    }
}

//-----------------------------------------------------------------------//
// Inserção
//-----------------------------------------------------------------------//
void InserirNo(TListaHuffman &h, char m)
{
    THuffman *novo = new THuffman(m, 1, nullptr, nullptr, h.inicio);

    h.inicio = novo;
}

void InserirNo(TListaHuffman &h, TArvore *&m)
{
    THuffman *novo = new THuffman(m->letra, m->frequencia, m->esq, m->dir, h.inicio);

    h.inicio = novo;
}

void InserirArvore(TListaArvore &l, TArvore *&m)
{
    TArvore *novo = new TArvore(m->letra, m->frequencia, m->esq, m->dir);

    l.raiz = novo;
}

//-----------------------------------------------------------------------//
// Remoção
//-----------------------------------------------------------------------//
void RemoverNo(TListaHuffman &h)
{
    THuffman *nav = new THuffman();
    if (h.inicio != nullptr)
    {
        nav = h.inicio;
        h.inicio = nav->proximo;
        nav->proximo = nullptr;
    }
}

#endif
