#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "leitura.h"
#include <iostream>
#include <QString>
#include <QListWidget>
#include <QPlainTextEdit>
using namespace std;

//-----------------------------------------------------------------------//
// Sobrecargas
//-----------------------------------------------------------------------//
ostream &operator<<(ostream &os, TArvore *c)
{

    os << "Letra: " << c->letra << "\nFrequencia: " << c->frequencia << "\n";
    return os;
}

//-----------------------------------------------------------------------//
// Prefixas
//-----------------------------------------------------------------------//
void PreFixa(TArvore *&no, string codigo)
{
    if (no->dir != nullptr && no->esq != nullptr)
    {
        PreFixa(no->esq, codigo + "0");
        PreFixa(no->dir, codigo + "1");
    }
    else
    {
        cout << "| " << no->letra << " | " << codigo << " \n";
    }
}

void PreFixa(TArvore *&no, string codigo, string &frase, string &fraseEspaco, char letra, TListaDicionario &dicionario)
{
    bool inserir = true;
    if (no->letra == letra)
    {
        frase += codigo;
        fraseEspaco += codigo + "   ";

        TDicionario *nav = dicionario.inicio;
        while (nav != nullptr)
        {
            if (nav->letra == letra)
            {
                inserir = false;
            }
            nav = nav->proximo;
        }
        if (inserir)
        {

            TDicionario *novo = new TDicionario(letra, codigo, dicionario.inicio);
            dicionario.inicio = novo;
        }
    }
    else if (no->dir != nullptr && no->esq != nullptr)
    {
        PreFixa(no->esq, codigo + "0", frase, fraseEspaco, letra, dicionario);
        PreFixa(no->dir, codigo + "1", frase, fraseEspaco, letra, dicionario);
    }
}

//-----------------------------------------------------------------------//
// Criação da árvore
//-----------------------------------------------------------------------//
void CriarArvore(TListaHuffman &h, TListaArvore &a)
{

    int quantidade = a.quantidadeLetras;
    TArvore *primeiro = nullptr;
    TArvore *segundo = nullptr;
    TArvore *novoNo = nullptr;

    for (int i = a.quantidadeLetras; i > 1; i--)
    {
        primeiro = new TArvore(h.inicio->dado);
        RemoverNo(h);
        segundo = new TArvore(h.inicio->dado);
        RemoverNo(h);
        novoNo = new TArvore('*', primeiro->frequencia + segundo->frequencia,
                             primeiro, segundo);

        InserirNo(h, novoNo);
        BubbleSortLetras(h, a.quantidadeLetras);
    }
    a.raiz = new TArvore(h.inicio->dado);
}

//-----------------------------------------------------------------------//
// Print da árvore
//-----------------------------------------------------------------------//
void PrintarArvore(TArvore *&no, string codigo, int camada)
{
    if (no->dir != nullptr && no->esq != nullptr)
    {
        cout  << codigo << " " << "Letra : " << no->letra << " | Frequencia: " << no->frequencia << " | Camada: " << camada << endl;
        PrintarArvore(no->esq, codigo + "_____", camada + 1);
        PrintarArvore(no->dir, codigo + "_____", camada + 1);
    }
    else
    {
        cout  << codigo << " " << "Letra : " << no->letra << " | Frequencia: " << no->frequencia << " | Camada: " << camada << endl;
    }
}

void PrintarArvoreInterface(TArvore *&no, string espaco, int camada, QListWidget *&item)
{
    QString aux(QChar(no->letra));
    QString aux2 = QString::number(camada);
    QString aux3 = QString::fromStdString(espaco);

    if (no->dir != nullptr && no->esq != nullptr)
    {
        item->insertItem(camada, aux3 + "Letra:  " + aux + "\tCamada:  " + aux2);
        PrintarArvoreInterface(no->esq, espaco + "\t", camada + 1, item);
        PrintarArvoreInterface(no->dir, espaco + "\t", camada + 1, item);
    }
    else
    {
        item->insertItem(camada, aux3 + "Letra: " + aux + "\tCamada: " + aux2);
    }
}
//-----------------------------------------------------------------------//
// Encriptografar a frase
//-----------------------------------------------------------------------//
string FraseEncriptografada(TArvore *&no, TListaDicionario &dicionario, string frase, string fraseEspaco)
{
    string fraseEnc;
    for (int i = 0; i < frase.length(); i++)
    {
        char letra = frase.at(i);
        PreFixa(no, "", fraseEnc, fraseEspaco, letra , dicionario);
    }
    return fraseEnc;
}

string FraseEncriptografadaEspaco(TArvore *&no, TListaDicionario &dicionario, string frase, string fraseEspaco)
{
    string fraseEnc;
    for (int i = 0; i < frase.length(); i++)
    {
        char letra = frase.at(i);
        PreFixa(no, "", fraseEnc, fraseEspaco, letra , dicionario);
    }
    return fraseEspaco;
}

//-----------------------------------------------------------------------//
// Decodificar a frase
//-----------------------------------------------------------------------//
void Decodificar(string fraseEnc, string &fraseDec, TListaDicionario dicionario)
{
    int i = 0, j = 0;
    TDicionario *nav = dicionario.inicio;
    while (i < fraseEnc.length())
    {

        while (nav != nullptr)
        {
            if (fraseEnc.substr(i, nav->numero.length()) == nav->numero)
            {
                i += nav->numero.length();
                break;

            }
            else
            {
                nav = nav->proximo;
            }
        }

        fraseDec += nav->letra;
        nav = dicionario.inicio;
    }
}

#endif
