#pragma once

#include <iostream>
#include "Evento.h"
#include "Relogio.h"
#include "Semaphore.h"


class EventoMudaSinal : public Evento {
public:
	EventoMudaSinal(Relogio<Evento*> *clock, Semaphore *semaforo, int tempoDaExecucao)
		: Evento(clock, semaforo, tempoDaExecucao, 1) {}

	Pista *getPistaOrigem(){
		return NULL;
	}

	void executaEvento(){
		if (printLog)
			cout << "Tempo " << tempoDaExecucao << ": ";
		EventoMudaSinal *novo = new EventoMudaSinal(clock, semaforo, tempoDaExecucao);
		if (semaforo->abertoN) {
			semaforo->abertoN = false;
			semaforo->abertoL = true;
			novo->atrasa(semaforo->tempoSemLeste);
			if (printLog)
				cout << "Semaforo norte fechou, leste abriu.\n";
		}
		else if (semaforo->abertoL) {
			semaforo->abertoL = false;
			semaforo->abertoS = true;
			novo->atrasa(semaforo->tempoSemSul);
			if (printLog)			
				cout << "Semaforo leste fechou, sul abriu.\n";
		}
		else if (semaforo->abertoS) {
			semaforo->abertoS = false;
			semaforo->abertoO = true;
			novo->atrasa(semaforo->tempoSemOeste);
			if (printLog)			
				cout << "Semaforo sul fechou, oeste abriu.\n";
		}
		else if (semaforo->abertoO) {
			semaforo->abertoO = false;
			semaforo->abertoN = true;
			novo->atrasa(semaforo->tempoSemNorte);
			if (printLog)			
				cout << "Semaforo oeste fechou, norte abriu.\n";
		}
		else {
			throw "NENHUM SEMAFORO ABERTO";
		}
		clock->adicionaEmOrdem(novo);
	}
};
