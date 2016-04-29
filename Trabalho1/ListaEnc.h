#pragma once
#include "Elemento.h"
template<typename T>

class ListaEnc {
public:
	ListaEnc<T>	() {
		size = 0;
		head = NULL;
	}

	~ListaEnc() {
		destroiLista();
	}

	// inicio
	void adicionaNoInicio(const T& dado) {
		Elemento<T> *novo = new Elemento<T>(dado, head);  // Aloca e cria novo
		if (novo == NULL)  // SE novo elemento não foi criado:
			throw "LISTA CHEIA";
		head = novo;
		size++;
	}

	T retiraDoInicio() {
		Elemento<T> *saiu;  // Variável auxiliar p/ 1º elemento
		if (listaVazia())
			throw "LISTA VAZIA";
		saiu = head;
		T retorno = saiu->getInfo();  // Variável auxiliar p/ info
		head = saiu->getProximo();
		size--;
		//	delete saiu;
		return retorno;
	}

	void eliminaDoInicio() {
		Elemento<T> *saiu;  // Variável auxiliar p/ 1º elemento
		if (listaVazia)
			throw "LISTA VAZIA";
		saiu = head;
		head = saiu->getProximo();
		size--;
		delete saiu;  // libera
	}

	// posicao
	void adicionaNaPosicao(const T& dado, int pos) {
		if (pos > size)
			throw "POSIÇÃO INVÁLIDA";
		if (pos == 0) {
			adicionaNoInicio(dado);
			return;
		}
		Elemento<T> *novo = new Elemento<T>(dado, NULL);  // Aloca e cria novo
		if (novo == NULL) {
			throw "LISTA CHEIA";
		}
		Elemento<T> *anterior;  // variável auxiliar
		anterior = head;
		for (int k = 0; k < pos - 1; k++) {  // segue a lista até chegar na posiçã
			anterior = anterior->getProximo();
		}
		novo->setProximo(anterior->getProximo());
		anterior->setProximo(novo);
		size++;
	}

	int posicao(const T& dado) const {
		Elemento<T> *atual = head;
		for (int k = 0; k < size; k++) {  // busca pelo elemento
			if (atual->getInfo() == dado)
				return k;   // retorna posição
			atual = atual->getProximo();
		}
		throw "ELEMENTO NÃO PRESENTE";
	}

	T* posicaoMem(const T& dado) const {  // busca pelo elemento
		Elemento<T> *atual = head;
		for (int k = 0; k < size; k++) {
			if (atual->getInfo() == dado)
				return &atual->getInfo();   // retorna endereço
			atual = atual->getProximo();
		}
		throw "ELEMENTO NÃO PRESENTE";
	}

	bool contem(const T& dado) {
		Elemento<T> *atual = head;
		for (int k = 0; k < size; k++) {    // busca pelo elemento
			if (atual->getInfo() == dado)
				return true;
			atual = atual->getProximo();
		}
		return false;
	}

	T retiraDaPosicao(int pos) {
		if (pos >= size)
			throw "POSIÇÃO INVÁLIDA";
		if (pos == 0)
			return retiraDoInicio();
		Elemento<T> *anterior, *eliminar;
		anterior = head;
		for (int k = 0; k < pos - 1; k++) {  // segue a lista até posição
			anterior = anterior->getProximo();
		}
		eliminar = anterior->getProximo();
		T retorno = eliminar->getInfo();
		anterior->setProximo(eliminar->getProximo());
		size--;
		delete eliminar;
		return retorno;
	}

	// fim
	void adiciona(const T& dado) {
		adicionaNaPosicao(dado, size);  // Adiciona no fim da lista
	}

	T retira() {
		if (listaVazia())
			throw "LISTA VAZIA";
		return retiraDaPosicao(size - 1);  // Retira  do fim da lista
	}

	// especifico
	T retiraEspecifico(const T& dado) {
		Elemento<T> *atual = head;
		Elemento<T> *anterior = head;
		for (int k = 0; k < size - 1; k++) {  // busca pelo elemento
			if (atual->getInfo() == dado) {
				T retorno = atual->getInfo();
				anterior->setProximo(atual->getProximo());
				delete atual;
				return retorno;
			}
			anterior = atual;
			atual = atual->getProximo();
		}
		throw "ELEMENTO NAO ESTÁ NA LISTA";
	}

	void adicionaEmOrdem(const T& data) {
		if (listaVazia())
			return adicionaNoInicio(data);
		Elemento<T> *atual;
		atual = head;
		int posit = 0;
		while (atual->getProximo() != NULL && !menor(data, atual->getInfo())) {
			// Busca posição para inserir
			atual = atual->getProximo();
			posit++;
		}
		if (maior(data, atual->getInfo()))  // ENTAO parou porque acabou a lista
			adicionaNaPosicao(data, posit + 1);
		else
			adicionaNaPosicao(data, posit);
	}

	bool listaVazia() const {
		if (size == 0)
			return true;
		else
			return false;
	}

	bool igual(T dado1, T dado2) {
		if (dado1 == dado2)
			return true;
		return false;
	}

	bool maior(T dado1, T dado2) {
		if (*dado1 > *dado2)
			return true;
		return false;
	}

	bool menor(T dado1, T dado2) {
		if (*dado1 < *dado2)
			return true;
		return false;
	}

	void destroiLista() {
		if (!listaVazia()) {
			head->destrucaoEncadeada();
			delete head;
			size = 0;
		}
	}

	// Métodos novos para ajudar
	T lerDaPosicao(int pos) {
		if (pos >= size)
			throw "POSIÇÃO INVÁLIDA";
		if (pos == 0)
			return lerDoInicio();
		Elemento<T> *anterior;
		anterior = head;
		for (int k = 0; k < pos - 1; k++) {  // segue a lista até posição
			anterior = anterior->getProximo();
		}
		return anterior->getProximo()->getInfo();  //Retorna elemento da posição pos sem retirar
	}

	T lerDoInicio() {
		return head->getInfo();  // Retorna 1º elemento sem retirar
	}

private:
	Elemento<T>* head;
	int size;
};
