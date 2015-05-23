#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#include <vector>

template <typename T>
class NoAVL  {
 private:
    T* dado;
    int altura;
    NoAVL<T>* esquerda;
    NoAVL<T>* direita;
    std::vector<NoAVL<T>* > elementos;

 public:
    explicit NoAVL(const T& dado) {
        altura = 1;
        this->dado = new T(dado);
    }

    virtual ~NoAVL();

    int getAltura() {
        return altura;
    }

    void updateAltura() {
        if (esquerda == NULL) {
            if (direita == NULL)
                altura = 1;  // Nenhum filho
            else
                altura = 1 + direita->getAltura();  // Altura da direita (único)
        } else if (direita == NULL) {
            // esquerda != NULL, pois ja foi testado antes
            altura = 1 + esquerda->getAltura();  // Altura da esquerda (único)
        } else {  // esquerda != NULL && direita != NULL
            // Considera maior altura:
            int alturaDireita = direita->getAltura();
            int alturaEsquerda = esquerda->getAltura();
            if (alturaDireita > alturaEsquerda)
                altura = alturaDireita + 1;
            else
                altura = alturaEsquerda + 1;
        }
    }

    int getBalanco() {
        if (esquerda == NULL) {
            if (direita == NULL)
                return 0;  // Nenhum filho -> equilibrado
            else
                return -1 * direita->getAltura();  // Altura da direita (único)
        } else if (direita == NULL) {
            // esquerda != NULL, pois ja foi testado antes
            return esquerda->getAltura();  // Altura da esquerda (único)
        } else {  // esquerda != NULL && direita != NULL
            return esquerda->getAltura() - direita->getAltura();
        }
    }

    std::vector<NoAVL<T>* > getElementos() {
        return elementos;
    }

    NoAVL<T>* getEsquerda() {
        return esquerda;
    }

    NoAVL<T>* getDireita() {
        return direita;
    }

    //////////////////////////////- COMPLETAR -/////////////////////////////////
    NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv);
    NoAVL<T>* remover(NoAVL<T>* arv, const T& dado);
    ////////////////////////////////////////////////////////////////////////////

    NoAVL<T> *rodaEsquerda(NoAVL<T> *no) {
		NoAVL<T> *t = no->esquerda;
		no->esquerda = t->direita;
		t->direita = no;
		no->updateAltura();
		t->updateAltura();
		return t;
    }

    NoAVL<T> *rodaDireita(NoAVL<T> *no) {
		NoAVL<T> *t = no->direita;
		no->direita = t->esquerda;
		t->esquerda = no;
		no->updateAltura();
		t->updateAltura();
		return t;
    }

    NoAVL<T>* Equilibra(NoAVL<T> *no) {
		no->updateAltura();
		if (no->esquerda->altura > no->direita->altura + 1) {
			if (no->esquerda->direita->altura > no->esquerda->esquerda->altura)
				no->esquerda = rodaDireita(no->esquerda);  // rotaçao dupla
			no = rodaEsquerda(no);  // simples sem a anterior
		} else {
		    if (no->direita->altura > no->esquerda->altura + 1) {
			    if (no->direita->esquerda->altura > no->direita->direita->altura)
				    no->direita = rodaEsquerda(no->direita);  // Caso dupla
			    no = rodaDireita(no);
		    }
		}
		return no;
	}

    NoAVL<T>* minimo(NoAVL<T>* nodo) {
        if (nodo->getEsquerda() != NULL)
            return minimo(nodo->getEsquerda());
        else
            return nodo;
    }

    T* getDado() {
        return dado;
    }

    T* busca(const T& dado, NoAVL<T>* arv) {
        while (arv != NULL) {
            if (*arv->getDado() != dado) {
                // Esquerda ou direita
                if (*arv->getDado() < dado)
                    arv = arv->getDireita();
                else
                    arv = arv->getEsquerda();
            } else {
                return arv->getDado();
            }
        }
        // return NULL;
        throw "Elemento Nao Existe";
    }

    void preOrdem(NoAVL<T>* nodo) {
        if (nodo != NULL) {
            elementos.push_back(nodo);  // Adiciona atual na pilha
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
        }
    }

    void emOrdem(NoAVL<T>* nodo) {
        if (nodo != NULL) {
            emOrdem(nodo->getEsquerda());  // menores
            elementos.push_back(nodo);  // atual
            emOrdem(nodo->getDireita());  // maiores
        }
    }

    void posOrdem(NoAVL<T>* nodo) {
        if (nodo != NULL) {
            posOrdem(nodo->getEsquerda());
            posOrdem(nodo->getDireita());
            elementos.push_back(nodo);
        }
    }
};

#endif /* NO_AVL_HPP */
