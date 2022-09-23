//
//  BST.h
//  ASD-T3-RBGraph
//
//  Created by Simone Cioffi on 06/06/22.
//

#ifndef BST_hpp
#define BST_hpp

#include "Node.hpp"
#include <iostream>
#include <vector>

using namespace std;

template <class T> class BST {
private:
    int nodes; // num nodes
    //Setting Nodo Radice
    Node<T> * root;
    
    //Nodo Sentine*lla NIL per IL RB
    Node<T> * NIL = new Node<T>();
    
    //Transplant
    void transplant(Node <T> * Cnode, Node<T> * Tnode);
    void setNodeList(vector<Node<T> *> * V);
    
    int getNodes(); //ritorni i numeri di id

protected:
    //Accessibile sia da BST e dalle classi derivabili , RBTree
    void setRoot(Node<T> * NRoot);
    
public:
    //Costruttore
    BST(){
        //Inizializzazione BST = Insieme nullo
        setRoot(getNIL());
        this->nodes = 0;
        nodes++;
    };
    
    //Distruttore
    virtual ~BST();
    
    //Metodi Set & Get
    Node <T> * getRoot();
    Node <T> * getNIL();
    
    //Visite BST
    void PreorderV(Node <T> * currentN); //Visita Anticipata
    void InorderV(Node <T> * currentN); //Visista  Simmetrica
    void PostorderV(Node <T> * currentN); //Visita Differita
    
    //Ricerca Nodo nel BST
    Node <T> * SearchNode(int key, Node<T> * currentN);
    
    //Min & Max nek BST
    Node <T> * getMinimum(Node <T> * currentN);
    Node <T> * getMaximum(Node <T> * currentN);
    
    //Successor & Predecessor
    Node <T> * getSuccessor(Node <T> * currentN);
    Node <T> * getPredecessor(Node <T> * currentN);
    
    //Inserimento & cancellazione
    Node <T> * InsertNode(T Data); // l'algoritmo di insert crea il nodo stesso tramite la chiave  e il dato satellite, ritorna il puntatore per favorire il RB_Insert
    void deleteNode(Node <T> * Dnode);
    
    //function per scorrere nell'albero BST/RB per i nodi adiacenti
    vector<T> * VectorizeInorder(Node<T> * Current, vector<T> * Vector);
    vector<T> * BuildV();
    
};

template <class T> BST<T>::~BST(){
    //Distruttore per distruggere l'albero
    while (this->getRoot() != getNIL()) {
        deleteNode(getRoot());
    }
    delete getNIL();
}

template <class T> void BST<T>::setRoot(Node <T> * NRoot) {
    this->root=NRoot;
}

template <class T> Node <T> * BST<T>::getRoot(){
    return this->root;
}

template <class T> Node <T> * BST<T>::getNIL(){
    return this->NIL;
}

template <class T> void BST<T>::PreorderV(Node <T> * currentN){
    if (currentN != getNIL()){
        cout << currentN->getKey() << " " << currentN->getData() << endl;
        PreorderV(currentN->getLChild());
        PreorderV(currentN->getRChild());
    }
}


template <class T> void BST<T>::InorderV(Node <T> * currentN){
    if (currentN != getNIL()){
        InorderV(currentN->getLChild());
        cout << currentN->getKey() << " ";
        InorderV(currentN->getRChild());
    }
}

template <class T> void BST<T>::PostorderV(Node <T> * currentN){
    if (currentN != getNIL()){
        PostorderV(currentN->getLChild());
        PostorderV(currentN->getRChild());
        cout << currentN->getKey() << " ";
    }
}

template <class T> Node<T> * BST<T>::SearchNode(int key, Node<T> * currentN){
    if (currentN == getNIL() || currentN == NULL) return nullptr;
    if (key == currentN->getData()->getData()) return currentN;
    if (key < currentN->getData()->getData()){
        return SearchNode(key, currentN->getLChild());
    }else {
        return SearchNode(key, currentN->getRChild());
    }
}

template <class T> Node<T> * BST<T>::getMinimum(Node <T> * currentN){
    while (currentN->getLChild() != getNIL()){
        currentN = currentN->getLChild();
    }
    return currentN;
}

template <class T> Node<T> * BST<T>::getMaximum(Node <T> * currentN){
    while (currentN->getRChild() != getNIL()){
        currentN = currentN->getRChild();
    }
    return currentN;
}

template <class T> Node <T> * BST<T>::getSuccessor(Node <T> * currentN){
            if (currentN->getRChild() !=getNIL()){
                return getMinimum(currentN->getRChild());
            }
            Node<T> p = currentN->getParent();
            while (p != getNIL() && currentN == p->getRChild()){
                currentN = p;
                p = p->getParent();
            }
            return p;
}

template <class T> Node <T> * BST<T>::getPredecessor(Node <T> * currentN){
            if (currentN->getLChild() != getNIL()){
                return getMaximum(currentN->getLChild());
            }
            Node<T> p = currentN->getParent();
            while (p !=  getNIL() && currentN == p->getLChild()){
                currentN = p;
                p = p->getParent();
            }
            return p;
}

template <class T> Node <T> * BST<T>::InsertNode(T Data){
            //Creazione Nodo
            int keys = getNodes()+1;
            Node<T> * NewNode = new Node<T>(keys, Data);
            NewNode->setParent(getNIL());
            NewNode->setRChild(getNIL());
            NewNode->setLChild(getNIL());
            //Inserimento Radice Albero
            Node<T> * Parent = getNIL();
            Node<T> * Current = getRoot();
            
            //Ricerca posizionamento nodo
            while (Current != getNIL()) {
                Parent = Current;
                if (Data->getData() < Current->getData()->getData()){
                    Current = Current->getLChild();
                } else
                    Current = Current->getRChild();
            }
            NewNode->setParent(Parent);
            
            //Inserisce nuovo nodo nella sua posizione
            if (Parent == getNIL()){
                setRoot(NewNode);
            } else if(Data->getData() < Parent->getData()->getData()){
                Parent->setLChild(NewNode);
            } else {
                Parent->setRChild(NewNode);
            }
            this->nodes++;
            return NewNode;
}
        
template <class T> void BST<T>::transplant(Node <T> * Cnode, Node<T> * Tnode){
            
            if (Cnode->getParent() == getNIL()){
                setRoot(Tnode);
            } else if (Cnode == Cnode->getParent()->getLChild()){
                Cnode->getParent()->setLChild(Tnode);
            } else {
                Cnode->getParent()->setRChild(Tnode);
            }
            
            if (Tnode != getNIL()){
                Tnode->setParent(Cnode->getParent());
            }
}
        
template <class T> void BST<T>::deleteNode(Node <T> * Dnode){
            
            if (Dnode == getNIL()) return; //nel caso sia il nodo sentinella
            
            if (Dnode->getLChild() == getNIL()){
                transplant(Dnode,Dnode->getRChild());
            } else if (Dnode->getRChild() == getNIL()){
                transplant(Dnode,Dnode->getLChild());
            }
            else {
                Node<T> * current = getMinimum(Dnode->getLChild());
                if (current->getParent() != Dnode){
                    transplant(current,current->getRChild());
                    current->setRChild(Dnode->getRChild());
                    current->getRChild()->setParent(current);
                }
                transplant(Dnode,current);
                current->setLChild(Dnode->getLChild());
                current->getLChild()->setParent(current);
            }
}

template <class T> int BST<T>::getNodes(){
    return this->nodes;
}

template <class T>  vector<T> * BST<T>::VectorizeInorder(Node<T> * Current, vector<T> * Vector) {
    if (Current != NIL && Current != nullptr) {
        VectorizeInorder(Current->getLChild(), Vector);
        Vector->push_back(Current->getData());
        VectorizeInorder(Current->getRChild(), Vector);
    }
    return Vector;
}

template <class T> vector<T> * BST<T>::BuildV() {
    vector<T> * Vec= new vector<T>;
    VectorizeInorder(getRoot(), Vec);
    return Vec;
}

#endif /* BST_h */
