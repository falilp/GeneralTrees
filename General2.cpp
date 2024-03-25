#include <iostream>
#include "agen.h"

/* Exercise 1: Given a general tree of a generic type tValue, calculate the number of nodes that, being siblings, 
have the same root and their subtrees are reflected. Reflected is that it has the same branching structure.*/
#pragma region Exercise1

template <typename tValue>
bool reflected(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node1, const typename Agen<tValue>::nodo node2){
    if(node1 == agen.NODO_NULO && node2 == agen.NODO_NULO) return true;
    else if(node1 != agen.NODO_NULO && node2 != agen.NODO_NULO) return true && 
                                                                reflected(agen,agen.hermDrcho(node1),agen.hermDrcho(node2)) && 
                                                                reflected(agen,agen.hijoIzqdo(node1),agen.hijoIzqdo(node2));
    else return false;
}

template <typename tValue>
unsigned int siblings(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else{
        unsigned int count = 0;
        typename Agen<tValue>::nodo compareNode = agen.hijoIzqdo(node);
        typename Agen<tValue>::nodo auxiliarNode = agen.hijoIzqdo(node);
        auxiliarNode = agen.hermDrcho(auxiliarNode);

        while(auxiliarNode != agen.NODO_NULO){
            if(reflected(agen,compareNode,auxiliarNode)) count++;
            //count += (reflected(agen,compareNode,auxiliarNode) ? 1 : 0);
            auxiliarNode = agen.hermDrcho(auxiliarNode);
        }

        return count + siblings(agen,agen.hijoIzqdo(node)) + siblings(agen,agen.hermDrcho(node));
    }
}

template <typename tValue>
unsigned int numberSiblings(const Agen<tValue> &agen){
    if(agen.arbolVacio()) return 0;
    else return siblings(agen,agen.raiz());
}

#pragma endregion


/* Exercise 2: Similar trees are those whose leaves match in position and element. */
#pragma region Exercise2

template <typename tValue>
bool isLeaves(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){ return (agen.hijoIzqdo(node) == agen.NODO_NULO) ? true : false; }

template <typename tValue>
bool sameElements(const Agen<tValue> &agen1, const Agen<tValue> &agen2, const typename Agen<tValue>::nodo node1, const typename Agen<tValue>::nodo node2){
    return (agen1.elemento(node1) == agen2.elemento(node2)) ? true : false;
}

template <typename tValue>
bool similars(const Agen<tValue> &agen1, const Agen<tValue> &agen2, const typename Agen<tValue>::nodo node1, const typename Agen<tValue>::nodo node2){
    if(node1 == agen1.NODO_NULO && node2 == agen2.NODO_NULO) return true;
    else if(node1 == agen1.NODO_NULO || node2 == agen2.NODO_NULO) return false;
    else if(node1 != agen1.NODO_NULO && node2 != agen2.NODO_NULO && isLeaves(agen1,node1) && isLeaves(agen2,node2)) return sameElements(agen1,agen2,node1,node2);
    else return similars(agen1,agen2,agen1.hermDrcho(node1),agen2.hermDrcho(node2)) && 
                similars(agen1,agen2,agen1.hermDrcho(node1),agen2.hermDrcho(node2));
}

template <typename tValue>
bool similarTrees(const Agen<tValue> &agen1, const Agen<tValue> &agen2){
    if(agen1.arbolVacio() && agen2.arbolVacio()) return true;
    else if(!agen1.arbolVacio() && !agen2.arbolVacio()) return similars(agen1,agen2,agen1.raiz(),agen2.raiz());
    else return false;
}

#pragma endregion


/* Exercise 3: The imbalance of a general tree is the maximum difference in the weights 
of the subtrees of N, the weight of the node is the number of leaf nodes. */
#pragma region Exercise3

template <typename tValue>
unsigned int numberOfLeafs(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else if(agen.hijoIzqdo(node) == agen.NODO_NULO) return 1 + numberOfLeafs(agen,agen.hermDrcho(node));
    else return numberOfLeafs(agen,agen.hijoIzqdo(node)) + numberOfLeafs(agen,agen.hermDrcho(node));
}

template <typename tValue>
unsigned int imbalanceAgen(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else{
        unsigned int minWeight = UINT_MAX;
        unsigned int maxWeight = 0;
        unsigned int weight = 0;
        typename Agen<tValue>::nodo auxiliarNode = agen.hijoIzqdo(node);

        while(auxiliarNode != agen.NODO_NULO){
            weight = numberOfLeafs(agen,auxiliarNode);
            maxWeight = std::max(maxWeight,weight);
            minWeight = std::min(minWeight,weight);
            auxiliarNode = agen.hermDrcho(auxiliarNode);
        }

        return std::max((maxWeight-minWeight),std::max(imbalanceAgen(agen,agen.hijoIzqdo(node)),imbalanceAgen(agen,agen.hermDrcho(node))));
    }
}

template <typename tValue>
unsigned int maximunImbalance(const Agen<tValue> &agen){
    if(agen.arbolVacio()) return 0;
    else imbalanceAgen(agen,agen.raiz());
}

#pragma endregion

/* Exercise 4: Implements a subprogram that, given a general tree, calculates its degree. */
#pragma region Exercise4

template <typename tValue>
unsigned int calculateDegree(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else{
        typename Agen<tValue>::nodo auxiliarNode = agen.hijoIzqdo(node);
        unsigned int degree = 0;

        while(auxiliarNode != agen.NODO_NULO){
            degree++;
            auxiliarNode = agen.hermDrcho(auxiliarNode);
        }
        
        return std::max(degree,std::max(calculateDegree(agen,agen.hijoIzqdo(node)),calculateDegree(agen,agen.hermDrcho(node))));
    }
}

template <typename tValue>
unsigned int degreeOfAgen(const Agen<tValue> &agen){
    if(agen.arbolVacio()) return 0;
    else return calculateDegree(agen,agen.raiz());
}

#pragma endregion

/* Exercise 5: Implements a generic function that transforms a General tree of a generic type T, eliminating the own 
descendants of all those nodes whose content is, at the same time, greater than or equal to their own ancestors and
less than or equal to their own descendants. */
#pragma region Exercise5

#pragma endregion

/* Exercise 6: Represent a flat figure:
    Quaternary Tree They have exactly 0 or 4 children.
    A leaf node can be white or black.
    Intermediate nodes have no color.
    
The square is divided into 4 quadrants. -> Children of the root node.
    If the quadrant is completely white or black, it means that it corresponds to a black or white sheet.
    If it has both black and white nodes, said quadrant is divided again. */
#pragma region Exercise6

#pragma endregion