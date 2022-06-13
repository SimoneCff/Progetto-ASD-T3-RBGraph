//
//  Node.hpp
//  ASD-T3-RBGraph
//
//  Created by Simone Cioffi on 06/06/22.
//

#ifndef Node_hpp
#define Node_hpp


//Setting colori nodi RB come true e false
enum colors {BLACK,RED};

//Setting Template Nodo RB

template <class T> class Node {
private:
    //Setting chiave e colore Nodo
    int key;
    bool colors;
    //Setting Puntatore Padre, Figlio dx e Figlio sx
    Node<T> * parent;
    Node<T> * Lchild;
    Node<T> * Rchild;
    //Setting dati satellite
    T data;
    
public:
    //Setting Costruttori
    
    // Costruttore Default & Nodo NIL;
    Node () : parent {nullptr}, Lchild {nullptr}, Rchild {nullptr} {
        setkey(0);
        setColor(BLACK);
        setData(NULL);
    }
    
    //Costruttore con valori
    Node (int key, T data) : parent {nullptr}, Lchild {nullptr}, Rchild {nullptr} {
        setkey(key);
        setColor(BLACK);
        setData(data);
    }
    
    //Setting Destroyer
    virtual ~Node() {}
    
    //Metodi Setter
    void setkey(int NKey);
    void setColor(bool NColor);
    void setParent(Node<T> * NParent);
    void setLChild(Node<T> * NLChild);
    void setRChild(Node<T> * NRChild);
    void setData(T NData);
    
    //Metodi Getter
    int getKey();
    bool getColor();
    Node <T> * getParent();
    Node <T> * getLChild();
    Node <T> * getRChild();
    T getData();
    
};

//Settig Metodi Setter
template <class T> void Node<T>::setkey(int Nkey){
    this->key=Nkey;
}

template <class T> void Node<T>::setColor(bool NColor){
    this->colors=NColor;
}

template <class T> void Node<T>::setParent(Node<T> * NParent){
    this->parent=NParent;
}

template <class T> void Node<T>::setLChild(Node<T> * NLChild){
    this->Lchild=NLChild;
}

template <class T> void Node<T>::setRChild(Node<T> * NRChild){
    this->Rchild=NRChild;
}
template <class T> void Node<T>::setData(T  NData){
    this->data=NData;
}

//Setting metodi Getter
template <class T> int Node<T>::getKey(){
    return this->key;
}

template <class T> bool Node<T>::getColor(){
    return this->colors;
}

template <class T> Node <T> * Node<T>::getParent(){
    return this->parent;
}

template <class T> Node <T> * Node<T>::getLChild(){
    return this->Lchild;
}

template <class T> Node <T> * Node<T>::getRChild(){
    return this->Rchild;
}

template <class T> T  Node<T>::getData(){
    return this->data;
}

#endif /* Node_hpp */
