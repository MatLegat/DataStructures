#pragma once

#include "Rand.h"

class Carro {
private:
	int tamanho, destino;

public:
	Carro() {
		Rand rand = Rand();
		tamanho = 2 + rand.get0toX(8);
		destino = rand.get0toX(9);
	}

	int getTamanho() {
		return tamanho;
	}

	int getDestino() {
		return destino;
	}
};
