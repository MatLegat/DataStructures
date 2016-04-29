#pragma once

#include "NomePista.h"
#include "Evento.h"
#include "EventoMudaPista.h"
#include "Semaphore.h"
#include "Pista.h"
#include "Carro.h"
#include "Relogio.h"

class EventoCriaCarro : public Evento {
private:
	Pista **pistas;
	int posicaoPistaOndeCriar;
	Carro *carro;

public:
	EventoCriaCarro(Relogio<Evento*> *clock, Semaphore *semaforo, int tempoDaExecucao, Pista **pistas, int posicaoPistaOndeCriar)
		: Evento(clock, semaforo, tempoDaExecucao, 3), pistas(pistas), posicaoPistaOndeCriar(posicaoPistaOndeCriar), carro(NULL) {}
	
	Pista *getPistaOrigem(){
		return NULL;
	}

	void executaEvento() {
		Pista *destino = pistas[posicaoPistaOndeCriar];
		if (carro == NULL) { // Se é a primeira tentativa de execução desse evento (ainda nao tem carro):
			carro = new Carro();
			// Cria evento depois da frequencia com uma variancia para criar novo carro:
			EventoCriaCarro *novo = new EventoCriaCarro(clock, semaforo, tempoDaExecucao, pistas, posicaoPistaOndeCriar);
			int freq = destino->getFrequencia();
			int var = destino->getVariancia();
			novo->atrasa(freq - var + Rand().get0toX(2 * var));
			clock->adicionaEmOrdem(novo);
			clock->novoCarroTentandoEntrar();
		}
		if (destino->cabeCarro(carro)) {
			// se cabe -> inclui carro na pista:
			destino->incluiCarro(carro);
			if (printLog) {
				cout << "Tempo " << tempoDaExecucao << ": Carro entrou no sistema pela pista ";
				cout << getNomePista(posicaoPistaOndeCriar) << ".\n";
			}
			clock->novoCarroEntrou();  // Pede para adicionar 1 ao contador de carros
			// Cria evento para carro tentar trocar de pista quando terminar de percorrê-la
			EventoMudaPista *novo =new EventoMudaPista(clock, semaforo, tempoDaExecucao + destino->tempoPercorrePista(), pistas, posicaoPistaOndeCriar);
			clock->adicionaEmOrdem(novo);
		}
		else {  // Não tem espaço
			adicionaDepoisLiberarEspaco(this, destino);
		}
	}


};
