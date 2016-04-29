#pragma once

#include <iostream>
#include "NomePista.h"
#include "Evento.h"
#include "Pista.h"
#include "Relogio.h"
#include "Semaphore.h"

class EventoMudaPista : public Evento {
private:
	Pista **pistas;
	int posicaoPistaOrigem;

public:
	EventoMudaPista(Relogio<Evento*> *clock, Semaphore *semaforo, int tempoDaExecucao, Pista **pistas, int posicaoPistaOrigem)
		: Evento(clock, semaforo, tempoDaExecucao, 2), pistas(pistas), posicaoPistaOrigem(posicaoPistaOrigem){}

	Pista *getPistaOrigem() {
		return pistas[posicaoPistaOrigem];
	}

	void executaEvento() {
		Pista *origem = pistas[posicaoPistaOrigem];
		// Se o sinal estver fechado:
		if (((posicaoPistaOrigem == 1 || posicaoPistaOrigem == 5) && !semaforo->abertoN) ||
			((posicaoPistaOrigem == 3 || posicaoPistaOrigem == 7) && !semaforo->abertoL) ||
			((posicaoPistaOrigem == 2 || posicaoPistaOrigem == 6) && !semaforo->abertoS) ||
			((posicaoPistaOrigem == 0 || posicaoPistaOrigem == 4) && !semaforo->abertoO)) {
			adicionaDepoisMudaSinal(this);
		}
		else {
			int *destinos;
			if (posicaoPistaOrigem == 0) {  // Se a pista de origem é O1leste
				destinos = new int[10]{ 4, 4, 4, 4, 4, 10, 4, 4, 9, 4};
			}
			else if (posicaoPistaOrigem == 1) {  // Se a pista de origem é N1sul
				destinos = new int[10]{ 4, 10, 4, 4, 8, 4, 4, 4, 4, 4};
			}
			else if (posicaoPistaOrigem == 2) {  // Se a pista de origem é S1norte
				destinos = new int[10]{ 4, 4, 4, 4, 9, 4, 4, 4, 8, 4};
			}
			else if (posicaoPistaOrigem == 3) {  // Se a pista de origem é C1oeste
				destinos = new int[10]{ 9, 8, 9, 8, 8, 10, 10, 10, 8, 9};
			}
			else if (posicaoPistaOrigem == 4) {  // Se a pista de origem é C1leste
				destinos = new int[10]{ 12, 12, 11, 12, 11, 13, 11, 13, 13, 13};
			}
			else if (posicaoPistaOrigem == 5) {  // Se a pista de origem é N2sul
				destinos = new int[10]{ 13, 13, 13, 13, 3, 3, 12, 3, 12, 12};
			}
			else if (posicaoPistaOrigem == 6) {  // Se a pista de origem é S2norte
				destinos = new int[10]{ 12, 13, 13, 3, 13, 3, 13, 3, 12, 12};
			}
			else if (posicaoPistaOrigem == 7) {  // Se a pista de origem é L1oeste
				destinos = new int[10]{ 11, 4, 12, 4, 11, 12, 11, 4, 12, 11};
			}
			else {  // Pistas sumidouros
				// Exclui o carro
				if (printLog) {
					cout << "Tempo " << tempoDaExecucao << ": Carro saiu do sistema pela pista ";
					cout << getNomePista(posicaoPistaOrigem) << ".\n";
				}	
				delete origem->retiraCarro();
				clock->saiuCarro();
				return; // Nenhum novo evento criado
			}
			Carro *carro = origem->primeiro();
			int posicaoDestino = destinos[carro->getDestino()];  // Vê a posicao do destino com base no valor aleatorio do carro
			Pista *destino = pistas[posicaoDestino];
			// Se o carro cabe no destino, troca de pista.
			if (destino->cabeCarro(carro)) {
				destino->incluiCarro(origem->retiraCarro());  // Tira carro da origem e poe no destino
				if (printLog) {			
					cout << "Tempo " << tempoDaExecucao << ": Carro mudou da pista " << getNomePista(posicaoPistaOrigem);
					cout << " para a pista " << getNomePista(posicaoDestino) << ".\n";
				}	
				// Evento para o carro mudar de pista ao chegar no fim do destino:
				// Origem do novo evento é o destino desse.
				EventoMudaPista *novo = new EventoMudaPista(clock, semaforo, tempoDaExecucao + destino->tempoPercorrePista(), pistas, posicaoDestino);
				clock->adicionaEmOrdem(novo);
			}
			// Se o carro não cabe:
			else {
				// Manda tentar denovo após algum evento (MUDA PISTA) que possa liberar espaço no destino.
				adicionaDepoisLiberarEspaco(this, destino);
			}
			delete destinos;
		}
	}
};
