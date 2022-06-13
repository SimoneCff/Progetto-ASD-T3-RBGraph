//
//  Edge.h
//  ASD-T3-RBGraph
//
//  Created by Simone Cioffi on 09/06/22.
//

#ifndef Edge_hpp
#define Edge_hpp

template <class T> class Vertex;

template <class T> class Edge {
private:
    int ID;
    Vertex<T> * source; //vertice d'inizio dell'arco
    Vertex<T> * destination; //Vertice di destinazione
    
    //Metodi set privati, accessibili solo dal builder
    void setSource(Vertex<T> * newSource);
    void setDestination(Vertex<T> * newDestination);
public:
    //Builder
    Edge(Vertex<T> * S, Vertex<T> * D, int NID) {
        setSource(S);
        setDestination(D);
        this->ID=NID;
    }
    
    // Destroyer
    ~Edge() { }
    
    //metodi get publici
    Vertex <T> * getSource();
    Vertex <T> * getDestination();
    int getID();
};

template <class T> void Edge<T>::setSource(Vertex<T> * newSource) {
    this->source=newSource;
}

template <class T> void Edge<T>::setDestination(Vertex<T> * newDestination) {
    this->destination=newDestination;
}

template <class T> Vertex <T> * Edge<T>::getSource(){
    return this->source;
    
}

template <class T> Vertex <T> * Edge<T>::getDestination(){
    return this->destination;
}

template <class T> int Edge<T>::getID(){
    return this->ID;
}

#endif /* Edge_h */
