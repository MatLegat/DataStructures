#pragma once

#include "FilaEnc.h"
#include "Carro.h"

class Pista : public FilaEnc < Carro * > {
private:
	int totalDeCarros = 0;  // Numero de total carros que entraram na pista.
	int carrosQueSairam = 0;
	int tamanhoOcupado = 0;
	int const ID, tamanhoPista, velocidade, frequencia, variancia;

public:
	Pista(int ID, int tamanhoPista, int velocidade, int frequencia, int variancia) :
		ID(ID), tamanhoPista(tamanhoPista), velocidade(velocidade), frequencia(frequencia), variancia(variancia) {
	}

	Pista(int ID, int tamanhoPista, int velocidade) :
		ID(ID), tamanhoPista(tamanhoPista), velocidade(velocidade), frequencia(0), variancia(0)  {
	}

	bool cabeCarro(Carro *carro) {
		int tamanhoOcupadoNovo = carro->getTamanho();
		if (!filaVazia())
			tamanhoOcupadoNovo += 3;  // Adiciona espaço de segurança se não for o primeiro carro.
		if (tamanhoOcupado + tamanhoOcupadoNovo <= tamanhoPista) {
			return true;
		}
		else
			return false;
	}

	void incluiCarro(Carro *carro) {
		if (!cabeCarro(carro))
			throw "ERRO LOTADO";
		totalDeCarros++;
		int tamanhoOcupadoNovo = carro->getTamanho();
		if (!filaVazia())
			tamanhoOcupado += 3;  // Adiciona além do tamanho do carro o espaço de segurança caso não seja o primeiro carro.
		tamanhoOcupado += tamanhoOcupadoNovo;
		inclui(carro);
	}

	Carro *retiraCarro() {
		Carro *carro = retira();
		tamanhoOcupado -= carro->getTamanho(); // Tamanho do carro.
		if (!filaVazia())
			tamanhoOcupado -= 3; // Espaço de segurança.
		carrosQueSairam++;
		return carro;
	}

	int tempoPercorrePista() {
		return tamanhoPista / (velocidade / 3.6);  // Converte velocidade de km/h p/ m/s e calcula o tempo que um carro leva para percorrer a pista.
	}

	int getFrequencia() {
		if (frequencia == 0)
			return 999999999;
		else
			return frequencia;
	}

	int getVariancia() {
		return variancia;
	}

	int getTotalDeCarros() {
		return totalDeCarros;
	}
	int getCarrosQueSairam() {
		return carrosQueSairam;
	}
};
