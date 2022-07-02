//
//  Graph.hpp
//  ASD-T3-RBGraph
//
//  Created by Simone Cioffi on 09/06/22.
//

#ifndef Graph_hpp
#define Graph_hpp

#include "Vertex.hpp"
#include "Edge.hpp"
#include <vector>
#include <queue>

using namespace std;

template <class T> class Graph {
private:
    vector<Vertex<T> *> * Vertices; //Vettore dei Vertici
    vector<Edge<T>* > * Edges ;// vettore dei archi
    
    //Set Privati
    void setVertices(vector<Vertex<T> *> * NVert);
    void setEdges(vector<Edge<T>* > * NEdg);
    
public:
    Graph() {
        setVertices(new vector<Vertex<T> *>);
        setEdges(new vector<Edge<T> *>);
    }
    
    ~Graph() {
        for (int i=0; i<getVertices()->size(); i++) delete getVertices()->at(i); //Cancellazione Vertici
        getVertices()->clear();
        delete getVertices();
        
        for (int i=0; i<getEdges()->size(); i++) delete getEdges()->at(i); //Cancellazione Archi
        getEdges()->clear();
        delete getEdges();
    }
    
    vector<Vertex<T> *> * getVertices();
    vector<Edge<T> *> * getEdges();
    
    Vertex<T> * searchVertex(int id);
    
    void addVertex(Vertex<T> * Nvertex);
    void addEdge(Edge<T> * Nedge);
    bool findEdge(Edge<T> * FEdge);
    Edge<T> * findEdgeID(int i, int j);
    void delEdge(Edge<T> * Nedge);
    void BFS(Vertex<T> * Source);
};

template <class T> void Graph<T>::setVertices(vector<Vertex<T> *> * NVert) {
    this->Vertices=NVert;
}

template <class T> void Graph<T>::setEdges(vector<Edge<T>* > * NEdg) {
    this->Edges=NEdg;
}


template <class T> vector<Vertex<T> *> * Graph<T>::getVertices() {
    return this->Vertices;
}

template <class T> vector<Edge<T> *> * Graph<T>::getEdges() {
    return this->Edges;
}


template <class T> void Graph<T>::addVertex(Vertex<T> * Nvertex){
    this->Vertices->push_back(Nvertex);
}

template <class T> void Graph<T>::addEdge(Edge<T> * Nedge){
    //Add new Edge inside Vertex
    this->Edges->push_back(Nedge);
    //Add Dest inside adj of Source
    Nedge->getSource()->InsertNewEdge(Nedge->getDestination());
}

template <class T> bool Graph<T>::findEdge(Edge<T> * FEdge){
    for (auto& Edge : *(getEdges())) {
        if (Edge == FEdge){
            return true;
        }
    }
    return false;
}

template <class T> void Graph<T>::BFS(Vertex<T> * Source) {
    std::queue<Vertex<T> *> BFSQueue;
    
    for (auto& node : *(getVertices())) {
        if (node!= Source) {
        node->setColor(WHITE);
        node->setPI(NULL);
        node->setD(std::numeric_limits<T>::max());
        }
    }
    Source->setColor(GRAY);
    Source->setD(0);
    Source->setPI(NULL);
    
    BFSQueue.push(Source);
    
    while (!BFSQueue.empty()){
        Vertex<T> * u = BFSQueue.front();
        BFSQueue.pop();
        
        for (auto& v: * (u->getAdjList()->BuildV())){
            if (v->getColor()==WHITE){
                v->setColor(GRAY);
                v->setPI(u);
                v->setD(u->getD()+1);
                BFSQueue.push(v);
            }
        }
        u->setColor(BLACK);
    }
    
}

template <class T> Vertex<T> * Graph<T>::searchVertex(int id){
    //essendo l'id la posizione nel vettore
    if (id > getVertices()->size()) {
        return nullptr;
    } else {
    return this->Vertices->at(id);
    }
}

template <class T> Edge<T> * Graph<T>::findEdgeID(int i, int j) {
    for (auto& Edge : *(getEdges())){
        if (Edge->getSource()->getID() == i && Edge->getDestination()->getID()== j) {
            return Edge;
        }
    }
    return nullptr;
}

template <class T> void Graph<T>::delEdge(Edge<T> * Nedge){
    //remove edge from adjlist of source
    Nedge->getSource()->DeleteEdge(Nedge->getDestination());
    
    //Remove edge from vector
    getEdges()->erase(getEdges()->begin()+Nedge->getID()-1);
    delete Nedge;
}

#endif /* Graph_h */
