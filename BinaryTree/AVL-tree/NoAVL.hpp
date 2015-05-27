// Copyright [2015] <Matteus Legat>

#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#include <vector>

template <typename T>
class NoAVL {
 private:
    T* dado;
    int altura;
    NoAVL<T>* esquerda;
    NoAVL<T>* direita;
    std::vector<NoAVL<T>* > elementos;

 public:
    explicit NoAVL(const T& dado) : dado(new T(dado)) {
        altura = 0;
        esquerda = NULL;
        direita = NULL;
    }

    virtual ~NoAVL() {
        if (esquerda != NULL)
		    esquerda->~NoAVL();  // Destroi subarvore esquerda
	    if (direita != NULL)
		    direita->~NoAVL();  // Destroi subarvore direita
	    delete dado;
    }

    int getAltura() {
        return altura;
    }

    int getAltura(NoAVL<T>* nodo) {
        if (nodo == NULL)
            return -1;  // Se nodo nao existe
        else
            return nodo->getAltura();
    }

    void updateAltura(NoAVL<T> *arv) {
        int alturaMaiorFilho;
        if (getAltura(arv->esquerda) > getAltura(arv->direita)) {
            // Maior é o esquerdo
            alturaMaiorFilho = getAltura(arv->esquerda);
        } else {
            alturaMaiorFilho = getAltura(arv->direita);
        }
        arv->altura = alturaMaiorFilho + 1;
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

    NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv) {
	    NoAVL<T> *t;  // auxiliar
	    if (dado < *arv->getDado()) {  // Inserção à esquerda.
	        if (arv->esquerda == NULL) {  // Local para inserir / último nodo
	            t = new NoAVL<T>(dado);
	            if (t == NULL) {
	                throw "BAD ALLOC";
                }
                arv->esquerda = t;
            } else {  // nao chegou no fim onde ira inserir
                t = arv->inserir(dado, arv->esquerda);
                arv = equilibra(arv, dado);
			    if (arv->getDado() != t->getDado()) {
			        arv->esquerda = t;
		        }
            }
        } else {  // direita
	        if (arv->direita == NULL) {  // Local para inserir / último nodo
	            t = new NoAVL<T>(dado);
	            if (t == NULL) {
	                throw "BAD ALLOC";
	                }
                arv->direita = t;
            } else {  // nao chegou no fim onde ira inserir
                t = arv->inserir(dado, arv->direita);
                arv = equilibra(arv, dado);
			    if (arv->getDado() != t->getDado()) {
			        arv->direita = t;
		        }
            }
        }
    	updateAltura(arv);
        return arv;
	}

    NoAVL<T>* remover(NoAVL<T>* arv, const T& dado) {
        NoAVL<T> *tmp, *filho;
        if (arv == NULL) {
            return arv;
        } else if (dado < *arv->getDado()) {  // Vá à esquerda.
            arv->esquerda = remover(arv->getEsquerda(), dado);
            arv = equilibra(arv, *(maximo(arv))->getDado());
			updateAltura(arv);
            return arv;
        } else if (dado > *arv->getDado()) {  // Vá à direita.
            arv->direita = (remover(arv->getDireita(), dado));
            arv = equilibra(arv, *(minimo(arv))->getDado());
	    	updateAltura(arv);
            return arv;
        } else {  // Encontrou elemento que quero deletar.
            if (arv->getDireita() != NULL && arv->getEsquerda() != NULL) {
                // 2 filhos.
                tmp = minimo(arv->getDireita());
                arv->dado = (tmp->getDado());
                arv->direita = (remover(arv->getDireita(), *arv->getDado()));
                arv = equilibra(arv, *(minimo(arv))->getDado());
			    updateAltura(arv);
                return arv;
            } else {  // 1 filho.
                tmp = arv;
                if (arv->getDireita() != NULL) {  // Filho à direita.
                    filho = arv->getDireita();
                    return filho;
                } else {
                    // Filho à esquerda.
                    if (arv->getEsquerda() != NULL) {
                        filho = arv->getEsquerda();
                        return filho;
                    } else {  // Folha.
                        delete arv;
                        return NULL;
                    }
                }
            }
        }
    }

    NoAVL<T> *rodaEsquerda(NoAVL<T> *arv) {
		NoAVL<T> *t = arv->esquerda;  // Auxiliar
	    arv->esquerda = t->direita;
	    t->direita = arv;
		updateAltura(arv);
		updateAltura(t);
		return t;
    }

    NoAVL<T> *rodaDireita(NoAVL<T> *arv) {
		NoAVL<T> *t = arv->direita;  // Auxiliar
		arv->direita = t->esquerda;
		t->esquerda = arv;
		updateAltura(arv);
		updateAltura(t);
	    return t;
	}

    NoAVL<T>* rodaEsquerdaDuplo(NoAVL<T> *arv) {
        arv->esquerda = rodaDireita(arv->esquerda);
        return rodaEsquerda(arv);
    }

    NoAVL<T>* rodaDireitaDuplo(NoAVL<T> *arv) {
        arv->direita = rodaEsquerda(arv->direita);
        return rodaDireita(arv);
    }

    NoAVL<T>* equilibra(NoAVL<T> *arv, const T& dado) {
        int alturaEsquerda = getAltura(arv->getEsquerda());
        int alturaDireita = getAltura(arv->getDireita());
        if (dado < *arv->getDado()) {
            if (alturaEsquerda - alturaDireita == 2) {
	            if (dado < *(arv->getEsquerda())->getDado()) {
		            return rodaEsquerda(arv);
	            } else {
		            return rodaEsquerdaDuplo(arv);
	            }
            }
        } else {
            if (alturaDireita - alturaEsquerda == 2) {
	            if (dado > *(arv->getDireita())->getDado()) {
    		        return rodaDireita(arv);
    	        } else {
	        	    return rodaDireitaDuplo(arv);
	            }
            }
        }
        return arv;
    }

    NoAVL<T>* minimo(NoAVL<T>* nodo) {
        if (nodo->getEsquerda() != NULL)
            return minimo(nodo->getEsquerda());
        else
            return nodo;
    }

    NoAVL<T>* maximo(NoAVL<T>* nodo) {
        if (nodo->getDireita() != NULL)
            return maximo(nodo->getDireita());
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
