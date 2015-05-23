// Copyright [2015] <Matteus Legat>

#ifndef NO_BINARIO_HPP
#define NO_BINARIO_HPP

#include <cstdlib>
#include <vector>

template <typename T>
class NoBinario {
 protected:
    T* dado;
    NoBinario<T>* esquerda;
    NoBinario<T>* direita;
    std::vector<NoBinario<T>* > elementos;  //!< Elementos acessados durante
                                            // o percurso realizado

 public:
    NoBinario<T>(const T& dado) {
        this->dado = new T(dado);
        esquerda = NULL;
        direita = NULL;
        elementos.clear();
    }

    virtual ~NoBinario() {}

    T* getDado() {
       return dado;
    }

    std::vector< NoBinario<T>* > getElementos() {
       return elementos;
    }

    NoBinario<T>* getEsquerda() {
        return esquerda;
    }

    NoBinario<T>* getDireita() {
        return direita;
    }

    /*
    NoBinario<T>* setEsquerda(NoBinario<T>* esq) {
        esquerda = esq;
    }

    NoBinario<T>* setDireita(NoBinario<T>* dir) {
        direita = dir;
    }
    */

    T* busca(const T& dado, NoBinario<T>* arv) {
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

    NoBinario<T>* inserir(const T& dado, NoBinario<T>* arv) {
        NoBinario<T>* aux;
        if (dado < *arv->getDado()) {
            // Inserção à esquerda.
            if (arv->getEsquerda() == NULL) {
                aux = new NoBinario<T>(dado);
                arv->esquerda = aux;
                return arv->getEsquerda();
            } else {
                arv = inserir(dado, arv->getEsquerda());
            }
        } else {
            // Inserção à direita.
            if (arv->getDireita() == NULL) {
                aux = new NoBinario<T>(dado);
                arv->direita = aux;
                return arv->getDireita();
            } else {
                arv = inserir(dado, arv->getDireita());
            }
        }
        return NULL;
    }

    NoBinario<T>* remover(NoBinario<T>* arv, const T& dado) {
        NoBinario<T> *tmp, *filho;
        if (arv == NULL) {
            return arv;
        } else {
            if (dado < *arv->getDado()) {  // Vá à esquerda.
                arv->esquerda = remover(arv->getEsquerda(), dado);
                return arv;
            } else {
                if (dado > *arv->getDado()) {  // Vá à direita.
                    arv->direita = (remover(arv->getDireita(), dado));
                    return arv;
                } else {  // Encontrou elemento que quero deletar.
                    if (arv->getDireita() != NULL &&
                            arv->getEsquerda() != NULL) {
                        // 2 filhos.
                        tmp = minimo(arv->getDireita());
                        arv->dado = (tmp->getDado());
                        arv->direita =
                            (remover(arv->getDireita(), *arv->getDado()));
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
        }
    }

    NoBinario<T>* minimo(NoBinario<T>* nodo) {
        if (nodo->getEsquerda() != NULL)
            return minimo(nodo->getEsquerda());
        else
            return nodo;
    }

    void preOrdem(NoBinario<T>* nodo) {
        if (nodo != NULL) {
            elementos.push_back(nodo);  // Adiciona atual na pilha
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
        }
    }

    void emOrdem(NoBinario<T>* nodo) {
        if (nodo != NULL) {
            emOrdem(nodo->getEsquerda());  // menores
            elementos.push_back(nodo);  // atual
            emOrdem(nodo->getDireita());  // maiores
        }
    }

    void posOrdem(NoBinario<T>* nodo) {
        if (nodo != NULL) {
            posOrdem(nodo->getEsquerda());
            posOrdem(nodo->getDireita());
            elementos.push_back(nodo);
        }
    }
};

#endif /* NO_BINARIO_HPP */
