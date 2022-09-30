#ifndef LEITURA_H
#define LEITURA_H

#include "comandos.h"
#include <fstream>
#include <iostream>
#include <QString>
#include <QListWidget>
#include <QThread>
#include <QWidget>
#include <QListWidgetItem>

using namespace std;

void LeituraArquivos(TListaHuffman &h, TListaArvore &l, string frase, QListWidget *&interface)
{
    bool inserir = true;
    char letra;
    for (int i = 0; i < frase.length(); i++)
    {
        letra = frase.at(i);
        THuffman *nav = h.inicio;
        inserir = true;
        while (nav != nullptr)
        {
            if (nav->dado.letra == letra)
            {
                nav->dado.frequencia++;
                inserir = false;
                int item = 0;
            }
            nav = nav->proximo;
        }
        if (inserir)
        {
            l.quantidadeLetras++;
            InserirNo(h, letra);
        }
    }
    THuffman *nav = h.inicio;
    int i = 0;
    while (nav != nullptr)
    {
        QString aux(QChar(nav->dado.letra));
        QString aux2 = QString::number(nav->dado.frequencia);
        interface->insertItem(i, "Letra: " + aux + "\tFrequencia: " + aux2);
        nav = nav->proximo;
    }
    BubbleSortLetras(h, l.quantidadeLetras);
}

void LeituraArquivos(TListaHuffman &h, TListaArvore &l, string frase)
{
    bool inserir = true;
    char letra;
    for (int i = 0; i < frase.length(); i++)
    {
        letra = frase.at(i);
        THuffman *nav = h.inicio;
        inserir = true;
        while (nav != nullptr)
        {
            if (nav->dado.letra == letra)
            {
                nav->dado.frequencia++;
                inserir = false;
                int item = 0;
            }
            nav = nav->proximo;
        }
        if (inserir)
        {
            l.quantidadeLetras++;
            InserirNo(h, letra);
        }
    }
    BubbleSortLetras(h, l.quantidadeLetras);
}

void DepurarListaLetras(TListaHuffman &l)
{
    for (THuffman *nav = l.inicio; nav != nullptr; nav = nav->proximo)
    {
        cout << nav->dado.letra << " " << nav->dado.frequencia << endl;
    }
}

#endif
