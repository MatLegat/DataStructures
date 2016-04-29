#include <iostream>
#include <time.h>
#include "Relogio.h" 
#include "Semaphore.h"
#include "Pista.h"
#include "Evento.h"
#include "EventoCriaCarro.h"
#include "EventoMudaSinal.h"
#include "NomePista.h"

using namespace std;

Semaphore *semaforo;
double tempoSimulacao, tempoSemNorte, tempoSemSul, tempoSemLeste, tempoSemOeste;
Pista **pistas = new Pista*[14];
Relogio <Evento*> relogio;

void verificaDado(double dado) {
	if (dado <= 0) {
		cout << "ERRO: DEVE SER INSERIDO UM VALOR MAIOR DO QUE ZERO\n";
		exit(1);
	}
}

void perguntaDados() {
	cout << "Insira o tempo (em HORAS) a ser simulado: ";
	cin >> tempoSimulacao;
	verificaDado(tempoSimulacao);
	cout << "Insira o tempo (em MINUTOS) em que o semaforo NORTE ficara aberto: ";
	cin >> tempoSemNorte;
	verificaDado(tempoSemNorte);
	cout << "Insira o tempo (em MINUTOS) em que o semaforo SUL ficara aberto: ";
	cin >> tempoSemSul;
	verificaDado(tempoSemSul);
	cout << "Insira o tempo (em MINUTOS) em que o semaforo LESTE ficara aberto: ";
	cin >> tempoSemLeste;
	verificaDado(tempoSemLeste);
	cout << "Insira o tempo (em MINUTOS) em que o semaforo OESTE ficara aberto: ";
	cin >> tempoSemOeste;
	verificaDado(tempoSemOeste);
};

void iniciaSemaforo() {
	semaforo = new Semaphore(tempoSemNorte, tempoSemSul, tempoSemLeste, tempoSemOeste);
}

void iniciaPistas() {
	//SEMAFORO 1
	Pista *O1leste = new Pista(0, 2000, 80, 10, 2);
	pistas[0] = O1leste;
	Pista *N1sul = new Pista(1, 500, 60, 20, 5);
	pistas[1] = N1sul;
	Pista *S1norte = new Pista(2, 500, 60, 30, 7);
	pistas[2] = S1norte;
	Pista *C1oeste = new Pista(3, 300, 60);
	pistas[3] = C1oeste;
	//SEMAFORO 2
	Pista *C1leste = new Pista(4, 300, 60);
	pistas[4] = C1leste;
	Pista *N2sul = new Pista(5, 500, 40, 20, 5);
	pistas[5] = N2sul;
	Pista *S2norte = new Pista(6, 500, 40, 60, 15);
	pistas[6] = S2norte;
	Pista *L1oeste = new Pista(7, 400, 30, 10, 2);
	pistas[7] = L1oeste;
	//SUMIDOUROS
	Pista *O1oeste = new Pista(8, 2000, 80);
	pistas[8] = O1oeste;
	Pista *N1norte = new Pista(9, 500, 60);
	pistas[9] = N1norte;
	Pista *S1sul = new Pista(10, 500, 60);
	pistas[10] = S1sul;
	Pista *N2norte = new Pista(11, 500, 40);
	pistas[11] = N2norte;
	Pista *S2sul = new Pista(12, 500, 40);
	pistas[12] = S2sul;
	Pista *L1leste = new Pista(13, 400, 30);
	pistas[13] = L1leste;
}

void iniciaEventos(){
	relogio.adicionaNoInicio(new EventoMudaSinal(&relogio, semaforo, tempoSemNorte * 60));
	relogio.adicionaNoInicio(new EventoCriaCarro(&relogio, semaforo, 0, pistas, 0));
	relogio.adicionaNoInicio(new EventoCriaCarro(&relogio, semaforo, 0, pistas, 1));
	relogio.adicionaNoInicio(new EventoCriaCarro(&relogio, semaforo, 0, pistas, 2));
	relogio.adicionaNoInicio(new EventoCriaCarro(&relogio, semaforo, 0, pistas, 5));
	relogio.adicionaNoInicio(new EventoCriaCarro(&relogio, semaforo, 0, pistas, 6));
	relogio.adicionaNoInicio(new EventoCriaCarro(&relogio, semaforo, 0, pistas, 7));
}

void imprimeResultado() {
	cout << "\n/-----------/\n/ RESULTADO /\n/-----------/\n\n";
	cout << "SISTEMA: entraram " << relogio.getTotalDeCarros() << " carros e sairam " << relogio.getCarrosQueSairam();
	cout << " carros (" << (relogio.getTotalDeCarros() - relogio.getCarrosQueSairam()) << " presos).\n";
	cout << "        " << relogio.getCarrosQueTentaramEntrar() - relogio.getTotalDeCarros();
	cout << " carro(s) esperando para entrar no sistema.\n";
        for (int k = 0; k < 14; k++) {
		cout << getNomePista(k) << ": entraram " << pistas[k]->getTotalDeCarros() << " carros e sairam ";
		cout << pistas[k]->getCarrosQueSairam() << " carros (";
		cout << (pistas[k]->getTotalDeCarros() - pistas[k]->getCarrosQueSairam()) << " presos).\n";
        }
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	perguntaDados();
	cout << "\n/--------------------/\n/-SIMULACAO INICIADA-/\n/--------------------/\n\n";
	cout << "\nOBS: Eh possivel ativar/desativar impressao do log no #define da classe Evento.\n";
	iniciaSemaforo();
	iniciaPistas();
	iniciaEventos();
	while (relogio.lerDoInicio()->getTempo() < tempoSimulacao * 60 * 60) {  // tempoSimulacao está em HORAS
		relogio.retiraDoInicio()->executaEvento();
	}
	cout << "\nOBS: Eh possivel ativar/desativar impressao do log no #define da classe Evento.\n";
	imprimeResultado();
	delete pistas;
	delete semaforo;
	//system("pause");
	return 0;
}

