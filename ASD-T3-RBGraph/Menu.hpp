//
//  Menu.hpp
//  ASD-T2-HashGraph
//
//  Created by Simone Cioffi on 31/05/22.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include "Graph.hpp"

using namespace std;

template <class T> class menu {
private:
    ifstream file;
    Graph<T> * RBG; // RBGraph
    
    //private functions per il file txt
    void setfile(string file);
    void checkfile();
    void closefile();
    
    //Richieste menu;
    void CallAdd();
    void CallRemove();
    void CallFind();
    void CallBFS();
    void CallD();

//public section
public:
 menu(){
    cout << "\t-----RBGraph----" << endl;
    cout << "\tApertura File input0_3_1 ... " << endl;
    setfile("input0_3_1.txt");
    checkfile();
    InitRBGraph();
 }
    void interactiveMenu();
    void InitRBGraph();
    
    //Call Func
    
    void setRBG(Graph<T> * newRBG);
    Graph<T> * getRBG();
};


template <class T> void menu<T>::setfile(string file){
    this->file.open(file);
}

template <class T> void menu<T>::checkfile(){
    if (this->file.is_open()){
        cout << "\t File aperto con successo \n" << endl;
    } else{
        //if is not open close all
        cout << "\t Errore Apertura File, uscita in corso" << endl;
        exit(1);
    }
}

template <class T> void menu<T>::closefile(){
    this->file.close();
}

template <class T> void menu<T>::interactiveMenu(){
    int select = 0;
    //Enters Menu
    cout << "\t---Menu RBGraph---\n" << endl;
    cout << "\t Selezionare le seguenti opzioni : \n" <<endl;
    cout << "\t 1): AddEdge;\n \t 2): RemoveEdge;\n \t 3): FindEdge\n \t 4): BFS;\n \t 5): Exit\n" << endl;
    cout << "selezionare opzione tramite numero di riferimento : "<<endl;
    //Select Option
    cin >> select;
    switch (select) {
        case 1:
            //Recall AddEdje
            CallAdd();
            break;
        
        case 2:
            //Recall RemoveEdge;
            CallRemove();
            break;
        
        case 3:
            //Recall FindEdge;
            CallFind();
            break;
        
        case 4:
            //Recall BFS;
            CallBFS();
            break;
        
        case 5:
            closefile();
            cout << "Chiusura Programma \n" << endl;
            exit(0);
            
        default:
            cout << "\n Errore nella selezione , riprovare: " << endl;
            break;
    }
}

template <class T> void menu<T>::InitRBGraph(){
    //init file temp
    int m, n;  //M nodi, N archi
    
    int i, j; // ID Vertici per arco
    
    int k = 0; //counter per  gli id dell'arco
    
    cout << "\t Inizializzazione del RBGraph ..." << endl;
    
    //init RBGraph
    setRBG(new Graph<T>);
    
    this->file.seekg(ios::beg);
    
    file>>m>>n;
    
    if ((0< m && m>1000) || (0 < n && n> 1000)){
        cout << "Il numero di Node e/o Archi non acettato, chiusura file" << endl;
        this->file.close();
        exit(5);
    }
    
    //inserimento nodi
    for (int v = 0; v<=m; v++){
        this->RBG->addVertex(new Vertex(v, v));
    }
    
    this->file.seekg(1, ios::beg); //imposta il puntatore dal secondo rigo;
    
    //Conversione file.txt archi
    while (this->file >> i >> j) { //Mentre ancora legge ed trova coppia di numeri
            m=i; n=j; k++;
            //Inserimento vertici nel RBtree
            getRBG()->addEdge( new Edge(getRBG()->searchVertex(i),getRBG()->searchVertex(j),k));
            k++;
    
    }
    
    cout << "\t RBGraph inizializzato con successo \n" << endl;
}

template <class T> void menu<T>::setRBG(Graph<T> * newRBG){
    this->RBG = newRBG;
}

template <class T> Graph<T> * menu <T>::getRBG() {
    return this->RBG;
}

template <class T> void menu<T>::CallAdd(){
    int i, j;
    bool ifind = true, jfind = true;
    
    while(ifind) {
        cout << "\t Inserire ID del vertice Source del nuovo Arco :" << endl;
        cin >> i;
        if (getRBG()->searchVertex(i) == nullptr) {
           cout << "Vertice Source Inesistente, mettere un ID di un Vertice Esistente" << endl;
        } else {
            ifind = false;
        }
    }
    
    while(jfind) {
        cout << "\t Inserire ID del vertice Destination del nuovo Arco :" << endl;
        cin >> j;
        if (getRBG()->searchVertex(j) == nullptr) {
           cout << "Vertice Source Inesistente, mettere un ID di un Vertice Esistente" << endl;
        } else {
            jfind = false;
        }
    }
    
    cout << "Inserimento Edge :" << i << " " << j << endl;
    getRBG()->addEdge(new Edge(getRBG()->searchVertex(i), getRBG()->searchVertex(j), getRBG()->getEdges()->size()+1));
    cout << "Edge Inserito Correttamente, Ritorno al Menu" << endl;
    interactiveMenu();
}

template <class T> void menu<T>::CallRemove() {
    int i, j;
    bool ifind = true, jfind = true;
    
    while(ifind) {
        cout << "\t Inserire ID del vertice Source del nuovo Arco :" << endl;
        cin >> i;
        if (getRBG()->searchVertex(i) == nullptr) {
           cout << "Vertice Source Inesistente, mettere un ID di un Vertice Esistente" << endl;
        } else {
            ifind = false;
        }
    }
    
    while(jfind) {
        cout << "\t Inserire ID del vertice Destination del nuovo Arco :" << endl;
        cin >> j;
        if (getRBG()->searchVertex(j) == nullptr) {
           cout << "Vertice Destination Inesistente, mettere un ID di un Vertice Esistente" << endl;
        } else {
            jfind = false;
        }
    }
    
    cout << "Rimozione Edge :" << i << " " << j << endl;
    
    getRBG()->delEdge(getRBG()->findEdgeID(i, j));
    
    cout << "Edge rimosso con sucesso" << endl;
    interactiveMenu();
}

template <class T> void menu<T>::CallFind() {
    int i, j;
    bool ifind = true, jfind = true;
    
    while(ifind) {
        cout << "\t Inserire ID del vertice Source del nuovo Arco :" << endl;
        cin >> i;
        if (getRBG()->searchVertex(i) == nullptr) {
           cout << "Vertice Source Inesistente, mettere un ID di un Vertice Esistente" << endl;
        } else {
            ifind = false;
        }
    }
    
    while(jfind) {
        cout << "\t Inserire ID del vertice Destination del nuovo Arco :" << endl;
        cin >> j;
        if (getRBG()->searchVertex(j) == nullptr) {
           cout << "Vertice Destination Inesistente, mettere un ID di un Vertice Esistente" << endl;
        } else {
            jfind = false;
        }
    }
    
    cout << "Ricerca Edge :" << i << " " << j << endl;
    
    if (getRBG()->findEdge(getRBG()->findEdgeID(i, j))) {
        cout << "Edge trovato all'interno del RBGraph" << endl;
    } else {
        cout << "Edge non trovato all'interno del RBGraph" << endl;
    }
    interactiveMenu();
}

template <class T> void menu<T>::CallBFS() {
    int s;
    bool sfind = true;
    Vertex<T> * source;
    
    while(sfind) {
        cout << "\t Inserire ID del vertice Source :" << endl;
        cin >> s;
        source = getRBG()->searchVertex(s);
        if ( source == nullptr) {
           cout << "Vertice Source Inesistente, mettere un ID di un Vertice Esistente" << endl;
        } else {
            sfind = false;
        }
    }
    cout << "Inizio BFS con source id : " << s << endl;
    //source->getAdjList()->PreorderV(source->getAdjList()->getRoot());
    getRBG()->BFS(source);
    cout << "Visita BFS effettuata: ecco le distanze dei nodi del RBGraph dal nodo source :" << endl;
    CallD();
    interactiveMenu();
    
}

template <class T> void menu<T>::CallD() {
    for (auto& Vertex: *(getRBG()->getVertices())) {
        cout << "ID_Vertice : " << Vertex->getID() << "Distanza da Source : "<< Vertex->getD() << "Archi " << endl;
    }
}



#endif /* Menu_hpp */
