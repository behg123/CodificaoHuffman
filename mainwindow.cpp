#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
#include <QMessageBox>
#include <QDebug>
#include <QtCore>
#include <QList>
#include <QListView>
#include <QString>
#include <QListWidgetItem>
#include <QtAlgorithms>
#include <QStackedWidget>
#include <QMessageBox>
#include "Huffman.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMessageBox::about(this, "Instruções","Primeiro codifique o texto, após isso, pegue a codificação huffman sem espaço e insira no decodificar.");
    connect(ui->botaoCodificar, SIGNAL(clicked(bool)), this, SLOT(CodificarTexto()));
    connect(ui->botaoCodificar, &QPushButton::clicked,ui->entrada,&QLineEdit::clear);
    connect(ui->botaoDecodificar, SIGNAL(clicked(bool)), this, SLOT(DecodificarTexto()));
    connect(ui->botaoDecodificar, &QPushButton::clicked,ui->entrada2,&QLineEdit::clear);
    connect(ui->entrada, &QLineEdit::returnPressed,ui->botaoCodificar,&QPushButton::click);
}

MainWindow::~MainWindow()
{
    delete ui;
}

TListaDicionario Dicionario;

void MainWindow::CodificarTexto()
{
    ui->textoCodificado->clear();
    ui->Linha1->clear();
    ui->tree->clear();
    //-----------------------------------------------------------------------//
    // Criação de Variaveis
    //-----------------------------------------------------------------------//
    QString FraseQ = ui->entrada->text();
    string frase = FraseQ.toStdString();
    string fraseDec;
    string fraseEnc;
    string FraseEncEspaco;
    //-----------------------------------------------------------------------//
    // Criação e inicialização
    //-----------------------------------------------------------------------//
    TListaArvore arvore;
    TListaDicionario dicionario;
    TListaHuffman huffman;
    InicializarDicionario(dicionario);
    InicializarArvore(arvore);
    InicializarHuffman(huffman);

    //-----------------------------------------------------------------------//
    // Criação da árvore
    //-----------------------------------------------------------------------//
    LeituraArquivos(huffman, arvore, frase, ui->criarArvore);
    CriarArvore(huffman, arvore);



    //-----------------------------------------------------------------------//
    // Print das informações úteis
    //-----------------------------------------------------------------------//
    // Print do Dicionario
    cout << "Dicionario:\n";
    PreFixa(arvore.raiz, "");

    //Print da frase codificada
    fraseEnc = FraseEncriptografada(arvore.raiz, dicionario, frase, FraseEncEspaco);
    cout << "\nFrase codificada (Sem espaço):\n" << fraseEnc;
    FraseEncEspaco = FraseEncriptografadaEspaco(arvore.raiz, dicionario, frase, FraseEncEspaco);
    cout << "\nFrase codificada (Com espaço):\n" << FraseEncEspaco;

    //Print da árvore
    cout << "\nArvore\n";
    PrintarArvore(arvore.raiz,"", 0);


    //-----------------------------------------------------------------------//
    // Print das informações na interface gráfica
    //-----------------------------------------------------------------------//s
    int i = 1;
    TDicionario *nav = dicionario.inicio;

    Dicionario.inicio = dicionario.inicio;

    while (nav != nullptr)
    {
        QString aux(QChar(nav->letra));
        QString aux2 = QString::fromStdString(nav->numero);
        ui->Linha1->insertItem(i, "Letra: " + aux + "\t|\tCodigo: " + aux2);
        nav = nav->proximo;
        i++;
    }

    PrintarArvoreInterface(arvore.raiz, "", 0, ui->tree);
    QString aux = QString::fromStdString(FraseEncEspaco);
    QString aux2 = QString::fromStdString(fraseEnc);
    ui->textoCodificado->insertPlainText("Com espaço:\n" + aux + "\nSem espaço:\n" +  aux2);

}

void MainWindow::DecodificarTexto(){

    QString FraseQ = ui->entrada2->text();
    string fraseEnc = FraseQ.toStdString();
    string fraseDec;

    //-----------------------------------------------------------------------//
    // Decodificação
    //-----------------------------------------------------------------------//
    Decodificar(fraseEnc, fraseDec, Dicionario);
    cout << "\nFrase Decodificada:\n" << fraseDec;
    //-----------------------------------------------------------------------//
    // Criação de uma nova árvore baseada na frase decodificada
    //-----------------------------------------------------------------------//
    TListaArvore novaArvore;
    TListaHuffman novoHuffman;
    InicializarArvore(novaArvore);
    InicializarHuffman(novoHuffman);
    LeituraArquivos(novoHuffman, novaArvore, fraseDec);

    CriarArvore(novoHuffman, novaArvore);

    cout << "\nNova arvore:\n";
    PrintarArvore(novaArvore.raiz,"", 0);


    QString aux = QString::fromStdString(fraseDec);
    ui->fraseOriginal->insertPlainText(aux);

    PrintarArvoreInterface(novaArvore.raiz, "", 0, ui->novaArvore);
}


