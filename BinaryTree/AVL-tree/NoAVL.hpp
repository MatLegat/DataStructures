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
    explicit NoAVL(const T& dado) {
        altura = 1;
        this->dado = new T(dado);
        esquerda = NULL;
        direita = NULL;
    }

    virtual ~NoAVL() {}

    int getAltura() {
        return altura;
    }

    void updateAltura(NoAVL<T> *arv) {
        int alturaMaiorFilho;
        if (arv->esquerda == NULL) {
            if (arv->direita == NULL)
                alturaMaiorFilho = 0;
            else
                alturaMaiorFilho = arv->direita->getAltura();
        } else if (direita == NULL) {
            alturaMaiorFilho = arv->esquerda->getAltura();  // esquerda!=NULL
        } else {  // Nenhum null
            int alturaDireita = direita->getAltura();
            int alturaEsquerda = esquerda->getAltura();
            if (alturaDireita > alturaEsquerda)
                alturaMaiorFilho = alturaDireita;
            else
                alturaMaiorFilho = alturaEsquerda;
        }
        arv->altura = 1 + alturaMaiorFilho;
        //  return altura = 1 + alturaMaiorFilho;
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

    int getBalanco(NoAVL<T>* arv) {
        if (arv->esquerda == NULL) {
            if (arv->direita == NULL)
                return 0;
            else
                return -1 * arv->direita->altura;
        } else if (arv->direita == NULL) {
            return arv->esquerda->altura;
        } else {
            return arv->esquerda->altura - arv->direita->altura > 1;
        }
    }

    NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv) {
	    if (arv == NULL) {
	        return new NoAVL<T>(dado);
        } else if (dado < *arv->getDado()) {
            // Inserção à esquerda.
            arv->esquerda = inserir(dado, arv->esquerda);
            if (getBalanco(arv) > 1) {
                if (dado < *arv->esquerda->dado)
                    arv = rodaDireita(arv);
                else
                    arv = rodaDireitaDuplo(arv);
            }
        } else {
            // direita
            arv->direita = inserir(dado, arv->direita);
            if (getBalanco(arv) > 1) {
                if (dado > *arv->direita->dado)
                    arv = rodaEsquerda(arv);
                else
                    arv = rodaEsquerdaDuplo(arv);
            }
        }
    	updateAltura(arv);
        return arv;
	}

    NoAVL<T>* remover(NoAVL<T>* arv, const T& dado) {
		NoAVL<T> *t;  // Auxiliar
		if (arv == NULL)
		    arv = new NoAVL<T>(dado);
		    return arv;
		if (*arv->dado == dado) {  // Encontrou dado para remover
			if (arv->esquerda == NULL || arv->direita == NULL) {  // Tem 1 filho
				if (arv->esquerda == NULL)
				    t = arv->direita;
				else
				    t = arv->esquerda;
				delete arv;
				return t;
			} else {  // nao tem filho
			    // Coloca o menor dado da direita no lugar
				for (t = arv->direita; t->esquerda != NULL; t = t->esquerda) {}
				arv->dado = t->dado;
				arv->direita = remover(arv->direita, *t->dado);
				return equilibra(arv);
			}
		}

		if (dado < *arv->dado)
		    arv->esquerda = remover(arv->esquerda, dado);
		else
		    arv->direita = remover(arv->direita, dado);

		return equilibra(arv);
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

    NoAVL<T>* equilibra(NoAVL<T> *arv) {
    	if (getBalanco(arv) > 1) {
    		if (getBalanco(arv->esquerda) > 0) {
	    		arv = rodaEsquerda(arv);
		    } else {
			    arv = rodaEsquerdaDuplo(arv);
		    }
	    } else if (getBalanco(arv) < -1) {
	    	if (getBalanco(arv->direita) > 0) {
			    arv = rodaDireitaDuplo(arv);
		    } else {
		    	arv = rodaDireita(arv);
		    }
	    }
	    return arv;

	/*
		updateAltura(arv);
		if (getBalanco(arv) > 1) {  // arv->esquerda maior
			if (getBalanco(arv->esquerda) < 0)  // arv->esquerda->direita maior
				arv->esquerda = rodaDireita(arv->esquerda);  // rotaçao dupla
			arv = rodaEsquerda(arv);  // simples sem a anterior
		} else {
		    if (getBalanco(arv) < 1) {  // arv->direita maior
			    if (getBalanco(arv->direita) > 0)  // arv->direita->esquerda maior
				    arv->direita = rodaEsquerda(arv->direita);  // Caso dupla
			    arv = rodaDireita(arv);
		    }
		}
		return arv; */
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
