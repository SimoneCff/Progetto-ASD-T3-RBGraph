//
//  RBtree.h
//  ASD-T3-RBGraph
//
//  Created by Simone Cioffi on 07/06/22.
//

#ifndef RBtree_hpp
#define RBtree_hpp

#include "BST.hpp"

template <class T> class RBtree: public BST<T> { //RBTree che eredita la classe BST
private:
     //counter per i nodi
     // left & right rotate privati, accessibili solo dalla funzione RBTransplant
    void left_rotate(Node <T> * Cnode);
    void right_rotate(Node <T> * Cnode);
    void RBTransplant(Node <T> * Cnode, Node<T> * Tnode);
    void RBDeleteFixUp(Node <T> * Cnode);
    
public:
    void RB_Insert(T data);
    void RB_Delete(Node <T> * Dnode);
    
};

template <class T> void RBtree<T>::left_rotate(Node <T> * Cnode) {
    Node <T> * Onode = Cnode->getRChild();
    Cnode->setRChild(Onode->getLChild());
    
    if (Onode->getLChild() != this->getNIL()) {
        Onode->getLChild()->setParent(Cnode);
    }
    Onode->setParent(Cnode->getParent());
    
    if (Cnode->getParent() == this->getNIL()) {
        this->setRoot(Onode);}
    else if (Cnode == Cnode->getParent()->getLChild()){
        Cnode->getParent()->setLChild(Onode);
    } else {
        Cnode->getParent()->setRChild(Onode);
    }
    
    Onode->setLChild(Cnode);
    Cnode->setParent(Onode);
}

template <class T> void RBtree<T>::right_rotate(Node <T> * Cnode) {
    Node <T> * Onode = Cnode->getLChild();
    Cnode->setRChild(Onode->getRChild());
    
    if (Onode->getRChild() != this->getNIL()) {
        Onode->getRChild()->setParent(Cnode);
    }
    Onode->setParent(Cnode->getParent());
    
    if (Cnode->getParent() == this->getNIL()) {
        this->setRoot(Onode);}
    else if (Cnode == Cnode->getParent()->getLChild()){
        Cnode->getParent()->setLChild(Onode);
    } else {
        Cnode->getParent()->setRChild(Onode);
    }
    
    Onode->setRChild(Cnode);
    Cnode->setParent(Onode);
}

template <class T> void RBtree<T>::RB_Insert(T data) {
    Node<T> * NewNode = this->InsertNode(data); // X
    NewNode->setColor(RED);

    
    while (NewNode != this->getRoot() && (NewNode->getParent()->getColor() == RED)) {
        if (NewNode->getParent() == NewNode->getParent()->getParent()->getLChild()){
            Node <T> * ONode = NewNode->getParent()->getParent()->getRChild(); //Y
            if (ONode->getColor() == RED) {
                NewNode->getParent()->setColor(BLACK);
                ONode->setColor(BLACK);
                NewNode->getParent()->getParent()->setColor(RED);
                NewNode=NewNode->getParent()->getParent();
            } else {
                if (NewNode == NewNode->getParent()->getRChild()){
                NewNode=NewNode->getParent();
                left_rotate(NewNode);
                }
                NewNode->getParent()->setColor(BLACK);
                NewNode->getParent()->getParent()->setColor(RED);
                right_rotate(NewNode->getParent()->getParent());
            }
        } else {
            Node <T> * ONode = NewNode->getParent()->getParent()->getRChild(); //Y
            if (ONode->getColor() == RED) {
                NewNode->getParent()->setColor(BLACK);
                ONode->setColor(BLACK);
                NewNode->getParent()->getParent()->setColor(RED);
                NewNode=NewNode->getParent()->getParent();
            } else {
                if (NewNode == NewNode->getParent()->getLChild()){
                NewNode=NewNode->getParent();
                right_rotate(NewNode);
                }
                NewNode->getParent()->setColor(BLACK);
                NewNode->getParent()->getParent()->setColor(RED);
                left_rotate(NewNode->getParent()->getParent());
            }
        }
    }
    this->getRoot()->setColor(BLACK);
}

template <class T> void RBtree<T>::RBTransplant(Node <T> * Cnode, Node<T> * Tnode) {
    if (Cnode->getParent()==this->getNIL()) {
        this->setRoot(Tnode);
    } else if (Cnode == Cnode->getParent()->getLChild()) {
        Cnode->getParent()->setLChild(Tnode);
    } else {
        Cnode->getParent()->setRChild(Tnode);
    }
    if (Tnode != this->getNIL()) {
        Tnode->setParent(Cnode);
    }
}

template <class T> void RBtree<T>::RB_Delete(Node<T> * Dnode) {
    Node<T> * Cnode = Dnode; //Y
    Node<T> * Onode; //X
    bool Ccolor = Cnode->getColor();
    
    if (Dnode->getLChild()==this->getNIL()) {
        Onode = Dnode->getRChild();
        RBTransplant(Dnode,Dnode->getRChild());
    } else if (Dnode->getRChild()==this->getNIL()){
            Onode = Dnode->getLChild();
            RBTransplant(Dnode,Dnode->getLChild());
    } else {
            Cnode=this->getMinimum(Dnode->getRChild());
            Ccolor = Cnode->getColor();
            Onode = Cnode->getRChild();
            
            if (Cnode->getParent()==Dnode){
                Onode->setParent(Cnode);
            } else {
                RBTransplant(Cnode,Cnode->getRChild());
                Cnode->setRChild(Dnode->getRChild());
                Cnode->getRChild()->setParent(Cnode);
            }
            RBTransplant(Dnode,Cnode);
            Cnode->setLChild(Dnode->getLChild());
            Cnode->getLChild()->setParent(Cnode);
            Cnode->setColor(Dnode->getColor());
    }
    if (Ccolor==BLACK) {
        RBDeleteFixUp(Onode);
    }
}
template <class T> void RBtree<T>::RBDeleteFixUp(Node <T> * Cnode){
                Node <T> * Wnode;
                while (Cnode != this->getRoot() && Cnode->getColor()== BLACK){
                    if (Cnode == Cnode->getParent()->getLChild()){
                        Wnode = Cnode->getParent()->getRChild();
                        
                        if (Wnode->getColor() == RED) {
                            Wnode->setColor(BLACK);
                            Cnode->getParent()->setColor(RED);
                            this->left_rotate(Cnode->getParent());
                            Wnode=Cnode->getParent()->getRChild();
                        }
                        
                        if (Wnode->getLChild()->getColor() == BLACK && Wnode->getRChild()->getColor() == BLACK){
                            Wnode->setColor(RED);
                            Cnode=Cnode->getParent();
                        } else {
                            if (Wnode->getRChild()->getColor() == BLACK){
                                Wnode->getLChild()->setColor(BLACK);
                                Wnode->setColor(RED);
                                this->right_rotate(Wnode);
                                Wnode=Cnode->getParent()->getRChild();
                            }
                            
                            Wnode->setColor(Cnode->getParent()->getColor());
                            Cnode->getParent()->setColor(BLACK);
                            Wnode->getRChild()->setColor(BLACK);
                            this->left_rotate(Cnode->getParent());
                            Cnode=this->getRoot();
                        }
                    } else {
                        Wnode = Cnode->getParent()->getLChild();
                        
                        if (Wnode->getColor() == RED) {
                            Wnode->setColor(BLACK);
                            Cnode->getParent()->setColor(RED);
                            this->left_rotate(Cnode->getParent());
                            Wnode=Cnode->getParent()->getLChild();
                        }
                        
                        if (Wnode->getRChild()->getColor() == BLACK && Wnode->getLChild()->getColor() == BLACK){
                            Wnode->setColor(RED);
                            Cnode=Cnode->getParent();
                        } else {
                            if (Wnode->getLChild()->getColor() == BLACK){
                                Wnode->getRChild()->setColor(BLACK);
                                Wnode->setColor(RED);
                                this->left_rotate(Wnode);
                                Wnode=Cnode->getParent()->getLChild();
                            }
                            
                            Wnode->setColor(Cnode->getParent()->getColor());
                            Cnode->getParent()->setColor(BLACK);
                            Wnode->getLChild()->setColor(BLACK);
                            this->right_rotate(Cnode->getParent());
                            Cnode=this->getRoot();
                        }
                        
                    }
                }
}


#endif /* RBtree_h */
