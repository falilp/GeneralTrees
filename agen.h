#ifndef AGEN_H
#define AGEN_H
#include <cassert>

    template <typename T> class Agen {
    struct celda; // declaración adelantada privada
    public:
        typedef celda* nodo;
        static const nodo NODO_NULO;
        //Post: Construye un árbol vacío.
        Agen(); // constructor

        //Pre: El árbol está vacío.
        //Post: Inserta el nodo raíz de A cuyo contenido será e.
        void insertarRaiz(const T& e);

        //Pre: n es un nodo del árbol.
        //Post: Inserta el elemento e como hijo izquierdo del nodo n. Si ya existe hijo 
        //izquierdo, éste se convierte en el hermano derecho del nuevo nodo.
        void insertarHijoIzqdo(nodo n, const T& e);

        //Pre: n es un nodo del árbol y no es el nodo raíz.
        //Post: Inserta el elemento e como hermano derecho del nodo n del árbol. 
        //Si ya existe hermano derecho, éste se convierte en el hermano derecho 
        //del nuevo nodo.
        void insertarHermDrcho(nodo n, const T& e);

        //Pre: n es un nodo del árbol. Existe hijoIzqdo(n) y es una hoja.
        //Post: Destruye el hijo izquierdo del nodo n. El segundo hijo, si existe, 
        //se convierte en el nuevo hijo izquierdo de n
        void eliminarHijoIzqdo(nodo n);

        //Pre: n es un nodo del árbol. Existe hermDrcho(n) y es una hoja.
        //Post: Destruye el hermano derecho del nodo n. El siguiente hermano 
        //se convierte en el nuevo hermano derecho de n.
        void eliminarHermDrcho(nodo n);

        //Pre: El árbol no está vacío y raiz() es una hoja.
        //Post: Destruye el nodo raíz. El árbol queda vacío.
        void eliminarRaiz();

        //Post : Devuelve true si el árbol está vacío y false en caso contrario.
        bool arbolVacio() const;

        //Pre: n es un nodo del árbol.
        //Post: Devuelve el elemento del nodo n.
        const T& elemento(nodo n) const; // acceso a elto, lectura
        T& elemento(nodo n); // acceso a elto, lectura/escritura

        //Post: Devuelve el nodo raíz del árbol. Si el árbol está vacío, devuelve NODO_NULO.
        nodo raiz() const;

        //Pre: n es un nodo del árbol.
        //Post: Devuelve el padre del nodo n. Si n es el nodo raíz, devuelve NODO_NULO.
        nodo padre(nodo n) const;

        
        //Pre: n es un nodo del árbol.
        //Post: Devuelve el hijo izquierdo del nodo n. Si no existe, devuelve NODO_NULO.
        nodo hijoIzqdo(nodo n) const;

        //Pre: n es un nodo del árbol.
        //Post: Devuelve el hermano derecho del nodo n. Si no existe, devuelve 
        //NODO_NULO.
        nodo hermDrcho(nodo n) const;

        Agen(const Agen<T>& a); // ctor. de copia
        Agen<T>& operator =(const Agen<T>& a); // asignación de árboles
        ~Agen(); // destructor
    private:
        struct celda {
            T elto;
            nodo padre, hizq, heder;
            celda(const T& e, nodo p = NODO_NULO): elto(e),
            padre(p), hizq(NODO_NULO), heder(NODO_NULO) {}
        };
        nodo r; // nodo raíz del árbol
        void destruirNodos(nodo& n);
        nodo copiar(nodo n);
};

/* Definición del nodo nulo */
template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(nullptr);

/*--------------------------------------------------------*/
/* Métodos públicos */
/*--------------------------------------------------------*/
template <typename T>
inline Agen<T>::Agen() : r(NODO_NULO) {}

template <typename T>
inline void Agen<T>::insertarRaiz(const T& e)
{
    assert(r == NODO_NULO); // Árbol vacío.
    r = new celda(e);
}

template <typename T>
inline void Agen<T>::insertarHijoIzqdo(Agen<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    nodo hizqdo = n->hizq; // Hijo izqdo. actual.
    n->hizq = new celda(e, n);
    n->hizq->heder = hizqdo; // El actual hijo izqdo. se convierte en
    // hermano drcho. del nuevo hijo.
}

template <typename T>
inline void Agen<T>::insertarHermDrcho(Agen<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n != r); // n no es la raíz.
    nodo hedrcho = n->heder; // Hermano drcho. actual
    n->heder = new celda(e, n->padre);
    n->heder->heder = hedrcho; // El actual hermano drcho. se convierte
    // en hermano drcho. del nuevo.
}

template <typename T>
inline void Agen<T>::eliminarHijoIzqdo(Agen<T>::nodo n)
{
    nodo hizqdo;
    assert(n != NODO_NULO);
    hizqdo = n->hizq;
    assert(hizqdo != NODO_NULO); // Existe hijo izqdo.
    assert(hizqdo->hizq == NODO_NULO); // Hijo izqdo. es hoja.
    // El hermano drcho. pasa a ser el nuevo hijo izqdo.
    n->hizq = hizqdo->heder;
    delete hizqdo;
}

template <typename T>
inline void Agen<T>::eliminarHermDrcho(Agen<T>::nodo n)
{
    nodo hedrcho;
    assert(n != NODO_NULO);
    hedrcho = n->heder;
    assert(hedrcho != NODO_NULO); // Existe hermano drcho.
    assert(hedrcho->hizq == NODO_NULO); // Hermano drcho. es hoja.
    // El hermano del hermano se convierte en el
    // nuevo hermano drcho. de n.
    n->heder = hedrcho->heder;
    delete hedrcho;
}

template <typename T>
inline void Agen<T>::eliminarRaiz()
{
    assert(r != NODO_NULO); // Árbol no vacío.
    assert(r->hizq == NODO_NULO); // La raíz es hoja.
    delete(r);
    r = NODO_NULO;
}

template <typename T>
inline bool Agen<T>::arbolVacio() const
{
    return (r == NODO_NULO);
}

template <typename T>
inline const T& Agen<T>::elemento(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline T& Agen<T>::elemento(Agen<T>::nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::raiz() const
{
    return r;
}

template <typename T> inline
typename Agen<T>::nodo Agen<T>::padre(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}

template <typename T> inline
typename Agen<T>::nodo Agen<T>::hijoIzqdo(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}

template <typename T> inline
typename Agen<T>::nodo Agen<T>::hermDrcho(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->heder;
}

template <typename T>
inline Agen<T>::Agen(const Agen<T>& A)
{
    r = copiar(A.r); // Copiar raíz y descendientes.
}

template <typename T>
Agen<T>& Agen<T>::operator =(const Agen<T>& A)
{
    if (this != &A) // Evitar autoasignación.
    {
        this->~Agen(); // Vaciar el árbol.
        r = copiar(A.r); // Copiar raíz y descendientes.
    }
    return *this;
}

template <typename T>
inline Agen<T>::~Agen()
{
    destruirNodos(r); // Vaciar el árbol.
}

/*--------------------------------------------------------*/
/* Métodos privados */
/*--------------------------------------------------------*/
// Destruye un nodo y todos sus descendientes
template <typename T>
void Agen<T>::destruirNodos(Agen<T>::nodo& n)
{
    if (n != NODO_NULO)
    {
        if (n->hizq != NODO_NULO)
        { // Destruir hermanos del hijo izqdo.
            nodo hedrcho = n->hizq->heder;
            while (hedrcho != NODO_NULO)
            {
                n->hizq->heder = hedrcho->heder;
                destruirNodos(hedrcho);
                hedrcho = n->hizq->heder;
            }
            destruirNodos(n->hizq); // Destruir el hijo izqdo.
        }
        delete(n);
        n = NODO_NULO;
    }
}

// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Agen<T>::nodo Agen<T>::copiar(Agen<T>::nodo n)
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO) {
        m = new celda(n->elto); // Copiar n.
        if (n->hizq != NODO_NULO) { // n tiene descendientes.
            m->hizq = copiar(n->hizq); // Copiar primer subárbol.
            m->hizq->padre = m;
            // Copiar el resto de subárboles.
            nodo hijo = m->hizq; // Último subárbol copiado.
            nodo hedrcho = n->hizq->heder; // Siguiente subárbol a copiar
            while (hedrcho != NODO_NULO) {
                hijo = hijo->heder = copiar(hedrcho);
                hijo->padre = m;
                hedrcho = hedrcho->heder;
            }
        }
    }
    return m;
}
#endif // AGEN_H