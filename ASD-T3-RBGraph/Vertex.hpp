//
//  Vertex.h
//  ASD-T3-RBGraph
//
//  Created by Simone Cioffi on 09/06/22.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include "RBtree.hpp" //Necessario per la adjacenyList del RBgraph
#include <limits>

//Define per i colori dei vertici per la visita BFS
#define WHITE 1
#define GRAY 2
#define BLACK 3

template <class T> class Edge;

template <class T> class Vertex{
private:
    int ID;  //ID vertice
    T data; //Dato satelitte vertice
    
    // Dati per il BFS
    unsigned int d; // distanza dal vertice s
    Vertex<T> * pi;// nodo predecessore
    unsigned int color; // Colore vertice
    
    //Lista d'adiacenza tramite RBtree
    RBtree<Vertex<T> *> * adjList;
    
    //metodo privato
    void setAdjList(RBtree<Vertex <T> *> * newAdjList);

public:
    Vertex(T data, int NID) {
        setD(std::numeric_limits<int>::max());
        setPI(NULL);
        setColor(WHITE);
        this->ID = NID;
        setAdjList(new RBtree<Vertex <T> *>);
        this->data = data;
    }
    
    ~Vertex() {
        delete getAdjList();
    }
    
    //Setter & Getter
    RBtree<Vertex<T>*> * getAdjList();
    int getD();
    Vertex<T> * getPI();
    int getColor();
    int getID();
    T getData();
    
    void setD(int NewD);
    void setPI(Vertex<T> * NewPI);
    void setColor(int NewColor);
    
    void InsertNewEdge(Vertex <T> * NewAdj); //aggiunta nuovo arco, ovvero nodo al RBtree
    void DeleteEdge(Vertex<T> * DeleteAdj); //Cancellazione arco, ovvero nodo nel RBtree
    bool SearchEdge(Vertex<T> * SearchedVertex); //Ricerca Vertice richiesto nel RBTree
};

template <class T> void Vertex<T>::setAdjList(RBtree<Vertex <T> *> * newAdjList) {
    this->adjList=newAdjList;
}


template <class T> void Vertex<T>::setD(int NewD){
    this->d = NewD;
}

template <class T> void Vertex<T>::setPI(Vertex<T> * NewPI) {
    this->pi=NewPI;
}

template <class T> void Vertex<T>::setColor(int NewColor){
    this->color=NewColor;
}

template <class T> RBtree<Vertex<T>*> * Vertex<T>::getAdjList(){
    return this->adjList;
}

template <class T> int Vertex<T>::getD(){
    return this->d;
}

template <class T>  Vertex<T> * Vertex<T>::getPI(){
    return this->pi;
}

template <class T> int Vertex<T>::getColor() {
    return this->color;
}

template <class T> T Vertex<T>::getData(){
    return this->data;
}

template <class T> int Vertex<T>::getID(){
    return this->ID;
}


template <class T> void Vertex<T>::InsertNewEdge(Vertex <T> * NewAdj){
    this->adjList->RB_Insert(NewAdj);
}

template <class T> void Vertex<T>::DeleteEdge(Vertex<T> * DeleteAdj){
    Node<Vertex<T> *> * Dnode = getAdjList()->SearchNode(DeleteAdj->getID(), getAdjList()->getRoot());
    getAdjList()->RB_Delete(Dnode);
}


template <class T> bool Vertex<T>::SearchEdge(Vertex<T> * SearchedVertex){
    if (this->adjList.SearchNode(SearchedVertex->getID(), getAdjList()->getRoot()) != getAdjList()->getNIL()) { //se é presente ritorna true , se no false
        return true;
    } else {
        return false;
    }
}


#endif /* Vertex_h */
