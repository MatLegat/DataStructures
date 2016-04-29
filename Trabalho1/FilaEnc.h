#pragma once

#include "Elemento.h"

template <typename T>

class FilaEnc {
private:
	int tamanho;
	Elemento<T> *start, *end;

public:
	FilaEnc<T>() {  // Inicializa a fila
		start = NULL;
		end = NULL;
		tamanho = 0;
	}

	~FilaEnc() {
		limparFila();
	}

	void inclui(const T& dado) {
		Elemento<T> *novo = new Elemento<T>(dado, NULL);  // Aloca e cria novo
		if (novo == NULL)  // SE novo elemento não foi criado:
			throw "FILA CHEIA";
		if (filaVazia()) {  // Caso especial: fila vazia -> definir como inicio
			start = novo;
		}
		else {  // definir como proximo do final antigo
			end->setProximo(novo);
		}
		end = novo;
		tamanho++;
	}

	T retira() {
		Elemento<T> *excluir;
		T retorno;
		if (filaVazia()) {
			throw "FILA VAZIA";
		}
		excluir = start;
		retorno = start->getInfo();  // Armazena info para retorna-la depois
		start = start->getProximo();
		if (tamanho == 1) {  // Caso especial: fila unitaria -> start==end
			end = NULL;
		}
		tamanho--;
		delete excluir;
		return retorno;
	}

	T ultimo() {
		if (filaVazia()) {
			throw "FILA VAZIA";
		}
		return end->getInfo();
	}

	T primeiro() {
		if (filaVazia()) {
			throw "FILA VAZIA";
		}
		return start->getInfo();
	}

	bool filaVazia() {
		if (tamanho == 0) {
			return true;
		}
		return false;
	}

	void limparFila() {
		if (!filaVazia()) {
			start->destrucaoEncadeada();
			delete start;
			tamanho = 0;
		}
	}
};
