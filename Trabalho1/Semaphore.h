#pragma once

class Semaphore {
public:
	bool abertoN = true;
	bool abertoS = false;
	bool abertoL = false;
	bool abertoO = false;
	int const tempoSemNorte, tempoSemSul, tempoSemLeste, tempoSemOeste;  // Tempos em segundos

	// Recebe tempo em minutos e armazena em segundos.
	Semaphore(double tempoSemNorte, double tempoSemSul, double tempoSemLeste, double tempoSemOeste)
		: tempoSemNorte(tempoSemNorte * 60), tempoSemSul(60 * tempoSemSul),
		tempoSemLeste(60 * tempoSemLeste), tempoSemOeste(60 * tempoSemOeste) {}

	int getTempoCiclo() {
		return tempoSemNorte + tempoSemSul + tempoSemLeste + tempoSemOeste;
	}
};
