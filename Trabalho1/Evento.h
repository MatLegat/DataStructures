#pragma once

#include "Relogio.h"
#include "Pista.h"
#include "Semaphore.h"

// Deixar como true para ativar impressao do log, false para desativar:
#define PRINTLOG true

class Evento {
protected:
	Relogio<Evento*> *clock;
	Semaphore *semaforo;
	int tempoDaExecucao;
	int const tipo;  // tipo == 1 -> MudaSinal, tipo == 2 -> MudaPista, tipo == 3 -> CriaCarro
	bool printLog = PRINTLOG;
public:

	virtual Pista *getPistaOrigem() = 0;
	virtual void executaEvento() = 0;

	Evento(Relogio<Evento*> *clock, Semaphore *semaforo, int tempoDaExecucao, int tipo)
		: clock(clock), semaforo(semaforo), tempoDaExecucao(tempoDaExecucao), tipo(tipo) {}

	int positProxMudaPista(Pista *p) {
		for (int k = 0; true; k++) {
			Evento *atual = clock->lerDaPosicao(k);
			if (atual->getTipo() == 2 && atual->getPistaOrigem() == p) {
				return k;
			}
		}
	}

	int positProxMudaSinal() {
		for (int k = 0; true; k++) {
			if (clock->lerDaPosicao(k)->getTipo() == 1) {
				return k;
			}
		}
	}

	void adicionaDepoisLiberarEspaco(Evento *e, Pista *destino) {
		int positProxMudaPista = this->positProxMudaPista(destino);
		e->setTempo(clock->lerDaPosicao(positProxMudaPista)->getTempo());
		clock->adicionaNaPosicao(e, positProxMudaPista + 1);
	}

	void adicionaDepoisMudaSinal(Evento *e) {
		int positProxMudaSinal = this->positProxMudaSinal();
		e->setTempo(clock->lerDaPosicao(positProxMudaSinal)->getTempo());
		clock->adicionaNaPosicao(e, positProxMudaSinal + 1);
	}

	int getTipo() {
		return tipo;
	}

	int getTempo() {
		return tempoDaExecucao;
	}

	void setTempo(int tempoDaExecucao) {
		this->tempoDaExecucao = tempoDaExecucao;
	}

	void atrasa(int tempo) {
		tempoDaExecucao += tempo;
	}

	// Relationals operators overloading para adicionar em ordem com base no tempo do evento.
	bool operator <(const Evento& another) {
		if (tempoDaExecucao < another.tempoDaExecucao) {
			return true;
		}
		return false;
	}
	bool operator >(const Evento& another) {
		if (tempoDaExecucao > another.tempoDaExecucao) {
			return true;
		}
		return false;
	}
	bool operator >=(const Evento& another) {
		return !(*this < another);
	}
	bool operator <=(const Evento& another) {
		return !(*this > another);
	}
};
