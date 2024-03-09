#include <iostream>
#include "agen.h"

#pragma region Exercise1
// exercise 1: Implements a subprogram that, given a general tree, calculates its degree.
template <typename tValue>
unsigned int degree(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else{
        unsigned int degree = 0;
        typename Agen<tValue>::nodo auxNode = agen.hijoIzqdo(node);

        while(auxNode != agen.NODO_NULO){
            degree++;
            auxNode = agen.hermDrcho(auxNode);
        }
        
        return std::max(degree,std::max(degree(agen,agen.hijoIzqdo(node)),degree(agen,agen.hermDrcho(node))));
    }
}
/*other option:
template <typename tValue>
unsigned int degree(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else{
        unsigned int degree = 0;
        typename Agen<tValue>::nodo auxNode = agen.hijoIzqdo(node);

        while(auxNode != agen.NODO_NULO){
            degree++;
            auxNode = agen.hermDrcho(auxNode);
        }

        typename Agen<tValue>::nodo auxNode = agen.hijoIzqdo(node);

        while(auxNode != agen.NODO_NULO){
            degree = std::max(degree,degree(agen,agen.hijoIzqdo(auxNode));
            auxNode = agen.hermDrcho(auxNode);
        }
        return degree;
    }
}
*/
template <typename tValue>
unsigned int degreeGeneralTree(const Agen<tValue> &agen){
    if(agen.arbolVacio()) return 0;
    else return degree(agen,agen.raiz());
}
#pragma endregion

#pragma region Exercise2
// exercise 2: Implements a subprogram that, given a tree and a node within said tree, determines the depth of this node in the tree.
template <typename tValue>
unsigned int depthNodeTree(const Agen<tValue> &agen,const typename Agen<tValue>::nodo node){
    if(agen.arbolVacio() || agen.NODO_NULO == node || agen.padre(node) == agen.NODO_NULO) return 0;
    else return 1 + depthNodeTree(agen,agen.padre(node));
}
#pragma endregion

#pragma region Exercise3
// exercise 3: The imbalance of a general tree is defined as the maximum difference between the heights of the subtrees
// lowest and highest of each level. Implements an applet that calculates the degree of imbalance of a general tree.
template <typename tValue>
unsigned int hight(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else return 1 + std::max(hight(agen,agen.hermDrcho(node)),hight(agen,agen.hijoIzqdo(node)));
}

template <typename tValue>
unsigned int imbalance(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else{
        unsigned int auxiliar = 0; 
        unsigned int max = 0;
        unsigned int min = UINT_MAX;
        typename Agen<tValue>::nodo auxNode = agen.hijoIzqdo(node);

        while(auxNode != agen.NODO_NULO){
            auxiliar = hight(agen,auxNode)-1;
            max = std::max(max,auxiliar);
            min = std::min(min,auxiliar);
            auxNode = agen.hermDrcho(auxNode);
        }
        
        return std::max(std::abs(max-min),std::max(imbalance(agen,agen.hermDrcho(node)),imbalance(agen,agen.hijoIzqdo(node))));
    }
}

template <typename tValue>
unsigned int imbalanceTree(const Agen<tValue> &agen){
    if(agen.arbolVacio()) return 0;
    else return imbalance(agen,agen.raiz());
}
#pragma endregion

#pragma region Exercise4
// exercise 4: Given a general tree of integers A and an integer x, implement an applet that performs the pruning
// from A from x. It is assumed that there are no repeated elements in A.
template<typename tValue>
void pruning(Agen<tValue> &agen, typename Agen<tValue>::nodo node){
    if(node != A.NODO_NULO){
        while(agen.hijoIzqdo(node) != agen.NODO_NULO){
            pruning(agen,ahen.hijoIzqdo(node));
            agen.eliminarHijoIzqdo(node);
        }
    }
}

template<typename tValue>
void findX(Agen<tValue> &agen, tValue X, typename Agen<tValue>::nodo node){
    if(node != agen.NODO_NULO){
        typename Agen<tValue>::nodo auxNode = agen.hijoIzqdo(node);

        while(auxNode != agen.NODO_NULO){
            if(X == agen.elemento(auxNode)) pruning(agen,auxNode);
            else{
                findX(agen,X,auxNode);
                auxNode = agen.hermDrcho(auxNode);
            }
        }
    }
}

template<typename tValue>
void pruningX(Agen<tValue> &agen, tValue X){
    if(!agen.arbolVacio()){
        if(X == agen.elemento(agen.raiz())) pruning(agen,agen.raiz());            
        else findX(agen,X,agen.raiz());
    }
}
#pragma endregion