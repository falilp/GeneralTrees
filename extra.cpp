#include <iostream>
#include "agen.h"

#pragma region AGEN
/**
 * TODO: Implementa un subprograma que, dado un árbol general, calcula su grado. 
*/

template <typename tValue>
unsigned int grado(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else{
        typename Agen<tValue>::nodo auxiliarNode = agen.hijoIzqdo(node);
        unsigned int grado = 0;

        while(auxiliarNode != agen.NODO_NULO){
            grado++;
            auxiliarNode = agen.hermDrcho(auxiliarNode);
        }

        return std::max(grado,std::max(grado(agen,agen.hermDrcho(node)),grado(agen,agen.hijoIzqdo(node))));
    }
}

template <typename tValue>
unsigned int gradoAgen(const Agen<tValue> &agen){
    if(agen.arbolVacio()) return 0;
    else return grado(agen,agen.raiz());
}


/**
 * TODO: Implementa un subprograma que devuelve el porcentaje de descendientes propios de un árbol general que sean múltiplos de 3. 
 * ! (puede hacerse o por elementos de los descendientes o por el numero de nodos)
*/

template <typename tValue>
unsigned int contarDescendientes(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else return 1 + contarDescendientes(agen,agen.hermDrcho(node)) + contarDescendientes(agen,agen.hijoIzqdo(node));
}

template <typename tValue>
unsigned int multiplosDeTres(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else if(contarDescendientes(agen,agen.hijoIzqdo(node))%3 == 0) return 1 + 
        multiplosDeTres(agen,agen.hermDrcho(node)) + 
        multiplosDeTres(agen,agen.hijoIzqdo(node));
    else return multiplosDeTres(agen,agen.hermDrcho(node)) + 
        multiplosDeTres(agen,agen.hijoIzqdo(node));
}

template <typename tValue>
unsigned int descendientesMultiplosDeTres(const Agen<tValue> &agen){
    if(agen.arbolVacio()) return 0;
    else return  100*(descendientesMultiplosDeTres(agen,agen,raiz())/contarDescendientes(agen,agen.hijoIzqdo(agen.raiz())));
}


/**
 * TODO: Dado un árbol general de tipo genérico tValue, calcular el número de nodos que, al ser hermanos, tienen la misma raíz y sus subárboles se reflejan.
 * ! Se refleja que tiene la misma estructura ramificada.
*/

template <typename tValue>
bool reflejos(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node1, const typename Agen<tValue>::nodo node2){
    if(node1 == agen.NODO_NULO && node2 == agen.NODO_NULO) return true;
    else if(node1 != agen.NODO_NULO && node2 != agen.NODO_NULO) return true &&
        reflejos(agen,agen.hermDrcho(node1),agen.hermDrcho(node2)) &&
        reflejos(agen,agen.hijoIzqdo(node1),agen.hijoIzqdo(node2));
    else return false;
}

template <typename tValue>
unsigned int numeroReflejado(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else{
        unsigned int contador = 0;
        typename Agen<tValue>::nodo compareNode = node;
        typename Agen<tValue>::nodo auxliarNode = node;
        compareNode = agen.hermDrcho(compareNode);

        while(auxliarNode != node){
            if(reflejos(agen,agen.hijoIzqdo(auxliarNode),agen.hijoIzqdo(compareNode))) contador++;
            auxliarNode = agen.hermDrcho(auxliarNode);
        }

        return contador + numeroReflejado(agen,agen.hermDrcho(node)) + numeroReflejado(agen,agen.hijoIzqdo(node));
    }
}

template <typename tValue>
unsigned int hermanosReflejados(const Agen<tValue> &agen){
    if(agen.arbolVacio()) return 0;
    else return numeroReflejado(agen,agen.hijoIzqdo(agen.raiz()));
}


/**
 * TODO: Árboles semejantes son aquellos cuyas hojas coinciden en posición y elemento.
*/

template <typename tValue>
bool mismoElemento(const Agen<tValue> &agen1, const Agen<tValue> &agen2, 
const typename Agen<tValue>::nodo node1, const typename Agen<tValue>::nodo node2){
    return agen1.elemento(node1) == agen2.elemento(node2);
}

template <typename tValue>
bool esHoja(const Agen<tValue> &agen1, const Agen<tValue> &agen2, 
const typename Agen<tValue>::nodo node1, const typename Agen<tValue>::nodo node2){
    return agen1.hijoIzqdo(node1) == agen1.NODO_NULO && agen2.hijoIzqdo(node2) == agen2.NODO_NULO;
}

template <typename tValue>
bool esIntermedio(const Agen<tValue> &agen1, const Agen<tValue> &agen2, 
const typename Agen<tValue>::nodo node1, const typename Agen<tValue>::nodo node2){
    return node1 != agen1.NODO_NULO && node2 != agen2.NODO_NULO &&
        agen1.hijoIzqdo(node1) != agen1.NODO_NULO && agen2.hijoIzqdo(node2) != agen2.NODO_NULO;
}

template <typename tValue>
bool semejantes(const Agen<tValue> &agen1, const Agen<tValue> &agen2, 
const typename Agen<tValue>::nodo node1, const typename Agen<tValue>::nodo node2){
    if(node1 == agen.NODO_NULO && node2 == agen.NODO_NULO) return true;
    else if(esHoja(agen1,agen2,node1,node2) && mismoElemento(agen1,agen2,node1,node2)) return true && 
        semejantes(agen1,agen2,agen1.hermDrcho(node1),agen2.hermDrcho(node2));        
    else if(esIntermedio(agen1,agen2,node1,node2)) return true && 
        semejantes(agen1,agen2,agen1.hermDrcho(node1),agen2.hermDrcho(node2)) &&
        semejantes(agen1,agen2,agen1.hijoIzqdo(node1),agen2.hijoIzqdo(node2));
    else return false;
}

template <typename tValue>
bool arbolesSemejantes(const Agen<tValue> &agen1, const Agen<tValue> &agen2){
    if(agen1.arbolVacio() && agen2.arbolVacio()) return true;
    else if(!agen1.arbolVacio() && !agen2.arbolVacio()) return semejantes(agen1,agen2,agen1.raiz(),agen2.raiz());
    else return false;
}


/** 
 * TODO: El desequilibrio de un árbol general es la diferencia máxima en los pesos.
 * ! De los subárboles de N, el peso del nodo es el número de nodos hoja.
*/

template <typename tValue>
bool esHojaAgen(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    return agen.hijoIzqdo(node) == agen.NODO_NULO;
}

template <typename tValue>
unsigned int contarNodosHojaAgen(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else if(esHojaAgen(agen,node)) return 1 + contarNodosAgen(agen,agen.hermDrcho(node));
    else return contarNodosAgen(agen,agen.hermDrcho(node)) + contarNodosAgen(agen,agen.hijoIzqdo(node));
}

template <typename tValue>
unsigned int desequilibrio(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else{
        unsigned int diferencia = 0;
        unsigned int maximoHojas = 0;
        unsigned int minimoHojas = UINT_MAX;;
        typename Agen<tValue>::nodo auxiliarNode = agen.hijoIzqdo(node);

        while(auxiliarNode != agen.NODO_NULO){
            maximoHojas = std::max(maximoHojas,contarNodosHojaAgen(agen,auxiliarNode));
            minimoHojas = std::min(minimoHojas,contarNodosHojaAgen(agen,auxiliarNode));
            auxiliarNode = agen.hermDrcho(auxiliarNode);
        }

        diferencia = std::abs(maximoHojas - minimoHojas);
        return std::max(diferencia,std::max(desequilibrio(agen,agen.hermDrcho(node)),desequilibrio(agen,agen.hijoIzqdo(node))));
    }
}

template <typename tValue>
unsigned int desequilibrioAgen(const Agen<tValue> &agen){
    if(agen.arbolVacio()) return 0;
    else return desequilibrio(agen,agen.raiz());
}


/**
 * TODO: Implementa un subprograma que, dado un árbol y un nodo dentro de dicho árbol, determina la profundidad de este nodo en el árbol.
*/

template <typename tValue>
unsigned int profundidadNodo(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(agen.arbolVacio() || agen.padre(node) == agen.NODO_NULO) return 0;
    else return 1 + profundidadNodo(agen,agen.padre(node));
}


/**
 * TODO: El desequilibrio de un árbol general se define como la diferencia máxima entre las alturas de los subárboles.
 * TODO: más bajo y más alto de cada nivel. Implementa un subprograma que calcula el grado de desequilibrio de un árbol general.
*/

template <typename tValue>
unsigned int alturaNodoAgen(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else return 1 + std::max(alturaNodoAgen(agen,agen.hermDrcho(node)),
        alturaNodoAgen(agen,agen.hijoIzqdo(node)));
}

template <typename tValue>
unsigned int desequilibrioAlturas(const Agen<tValue> &agen, const typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return 0;
    else{
        unsigned int auxiliar = 0;
        unsigned int maximaAltura = 0;
        unsigned int minimaAltura = UINT_MAX;
        typename Agen<tValue>::nodo auxiliarNode = agen.hijoIzqdo(node);

        while(auxiliarNode != agen.NODO_NULO){
            auxiliar = alturaNodoAgen(agen,auxiliar);
            maximaAltura = std::max(auxiliar,maximaAltura);
            minimaAltura = std::max(auxiliar,minimaAltura);
            auxiliarNode = agen.hermDrcho(auxiliarNode);
        }

        return std::max(std::abs(maximaAltura-minimaAltura),
            std::max(desequilibrioAlturas(agen,agen.hermDrcho(node)),
            desequilibrioAlturas(agen,agen.hijoIzqdo(node))));
    }
}

template <typename tValue>
unsigned int desequilibrioAgenAlturas(const Agen<tValue> &agen){
    if(agen.arbolVacio()) return 0;
    else return desequilibrioAlturas(agen,agen.raiz());
}


/**
 * TODO: Dado un árbol general de números enteros A y un número entero x, implemente un subprograma que realice la poda de A de x. 
 * !Se supone que no hay elementos repetidos en A. 
*/

template <typename tValue>
void podarElemento(Agen<tValue> &agen, typename Agen<tValue>::nodo node){
    if(node != agen.NODO_NULO){
        while(agen.hijoIzqdo(node) != agen.NODO_NULO){
            podarElemento(agen,agen.hijoIzqdo(node));
            agen.eliminarHijoIzqdo(node);
        }
    }
}

template <typename tValue>
void buscarElemento(Agen<tValue> &agen, typename Agen<tValue>::nodo node, const tValue elemento){
    if(node != agen.NODO_NULO){
        if(agen.elemento(node) == elemento) podarElemento(agen,node);
        else{
            buscarElemento(agen,agen.hermDrcho(node),elemento);
            buscarElemento(agen,agen.hijoIzqdo(node),elemento);
        }
        /** 
         * ! Tambien se puede hacer asi
         * typename Agen<tValue>::nodo auxNode = agen.hijoIzqdo(node);
         * 
         * while(auxNode != agen.NODO_NULO){
         *      if(X == agen.elemento(auxNode)) podarElemento(agen,auxNode);
         *      else{
         *          buscarElemento(agen,auxNode,X);
         *          auxNode = agen.hermDrcho(auxNode);
         *      }
         * }
        */
    }
}

template <typename tValue>
void podaElementoAgen(Agen<tValue> &agen, const tValue elemento){
    if(!agen.arbolVacio()) buscarElemento(agen,agen.raiz(),elemento);
}


/**
 * TODO: Implementa una funcion generica que transforme un arbol General de un tipo generico tValue, 
 * TODO: eliminando los descendientes propios de todos aquellos nodos cuyo contenido sea, 
 * TODO: al mismo tiempo mayor o igual que sus ascendientes propios y menor o igual que sus descnedientes propios.
*/
template <typename tValue>
bool ascendentes(Agen<tValue> &agen, typename Agen<tValue>::nodo node){
    if(node == agen.NODO_NULO) return true;
    else return (agen.elemento(node) >= agen.elemento(agen.padre(node))) && ascendentes(agen,agen.padre(node));
}

template <typename tValue>
bool comprobarMenor(Agen<tValue> &agen, typename Agen<tValue>::nodo node, const tValue &valor){
    return (valor <= agen.elemento(agen.hijoIzqdo(node))) && (valor <= agen.elemento(agen.hermDrcho(node)));
}

template <typename tValue>
bool descendientes(Agen<tValue> &agen, typename Agen<tValue>::nodo node, const tValue &valor){
    if(node == agen.NODO_NULO) return true;
    else if(comprobarMenor(agen,node,agen.elemento(node))) return true && 
        descendientes(agen,agen.hijoIzqdo(node),valor) &&
        descendientes(agen,agen.hermDrcho(node),valor);
    else return false;
}

template <typename tValue>
void eliminacionNodos(Agen<tValue> &agen, typename Agen<tValue>::nodo node){
    if(node != abin.NODO_NULO){
        if(ascendentes(agen,node) && descendientes(agen,node,agen.elemento(node))) podarElemento(agen,node);
        else{
            typename Agen<tValue>::nodo auxiliarNode = agen.hijoIzqdo(node);

            while(auxiliarNode != agen.NODO_NULO){
                eliminacionNodos(agen,auxiliarNode);
                auxiliarNode = agen.hermDrcho(auxiliarNode);
            }
        }
    }
}

template <typename tValue>
void transformarAgen(Agen<tValue> &agen){
    if(!agen.arbolVacio()) eliminacionNodos(agen,agen.raiz());
}

#pragma endregion

#pragma region ROJINEGRO
/**
 * TODO: Una forma de representar una figura plana en blanco y negro consiste en utilizar un
 * TODO: árbol cuaternario en el que cada nodo o tiene exactamente cuatro hijos, o bien es una
 * TODO: hoja. Un nodo hoja puede ser blanco o negro y un nodo interno no tiene color.
 *
 * TODO: Una figura dibujada dentro de un cuadrado de lado 2^k se representa de la forma
 * TODO: siguiente: Se divide el cuadrado en cuatro cuadrantes y cada uno se representa como un
 * TODO: hijo del nodo raíz. Si un cuadrante está completamente negro corresponde a una hoja
 * TODO: negra; si, por el contrario, el cuadrante está completamente blanco, éste corresponde a
 * TODO: una hoja blanca; y si un cuadrante está parcialmente ocupado por negro y blanco,
 * TODO: entonces corresponde a un nodo interno del árbol y este cuadrante se representa
 * TODO: siguiendo el mismo método subdividiéndolo en otros cuatro cuadrantes. Como ejemplo
 * TODO: se muestra una figura en blanco y negro y su árbol asociado, tomando los cuadrantes en
 * TODO: el sentido de las agujas del reloj a parti del cuadrante superior izquierdo.
 * Implementa una función que dado un arbol de esta clase, con k+1 niveles,
 * devuelva la figura asociada, representada como una matriz cuadrada de tamaño 2^k en la
 * quue a cada representa un punto blanco o negro.
*/

#define N 10

enum Color{BLANCO, NEGRO, SINCOLOR};

typedef struct Coordenadas{
    int xInicio, xFin, yInicio, yFin;
}Coordenadas;

void matrizRecursiva(const Agen<Color> &agen, const typename Agen<Color>::nodo node,
Color** &matriz, Coordenadas &coordenadas){
    if(node != agen.NODO_NULO){
        if(agen.elemento(node) == SINCOLOR){
            int cuadrante = 1;
            typename Agen<Color>::nodo auxiliarNode = agen.hijoIzqdo(node);
            
            while(auxiliarNode != agen.NODO_NULO){
                switch(cuadrante){
                    case 1: 
                        coordenadas.xFin /= 2;
                        coordenadas.yFin /= 2;
                        break;
                    case 2: 
                        coordenadas.xInicio = coordenadas.xFin + 1;
                        coordenadas.xFin = (2*coordenadas.xFin) + 1;
                        break;
                    case 3: 
                        coordenadas.yInicio = coordenadas.yFin + 1;
                        coordenadas.yFin = (2*coordenadas.yFin) + 1;
                        break;
                    case 4: 
                        coordenadas.xFin /= 2;
                        coordenadas.xInicio -= (coordenadas.xFin+1);
                        break;
                }

                matrizRecursiva(agen,auxiliarNode,matriz,coordenadas);
                cuadrante++;
                auxiliarNode = agen.hermDrcho(auxiliarNode);
            }
        }else matriz[coordenadas.xInicio][coordenadas.yInicio] = agen.elemento(node);
        //solucion de wuolah:
        /*for(int i=coordenadas.xInicio; i<coordenadas.xFin; i++){
            for(int j=coordenadas.yInicio; j<coordenadas.yFin; j++){
                matriz[i][j] = agen.elemento(node);
            }
        }*/
    }
}

Color** matrizBlancoNegro(const Agen<Color> &agen){
    Color** matriz = new Color*[N];
    for(int i=0; i<N; i++){
        matriz[i] = new Color[N];
    }

    Coordenadas coordenadas;
    coordenadas.xInicio = coordenadas.yInicio = 0;
    coordenadas.xFin = coordenadas.yFin = N-1;
    matrizRecursiva(agen,agen.raiz(),matriz,coordenadas); 

    return matriz;  
}


#pragma endregion