#pragma once

#include "ListaEnc.h"
#include "Pista.h"
template<typename T>

class Relogio : public ListaEnc < T > {
private:
	int totalDeCarros;
	int carrosQueSairam;
	int carrosQueTentaramEntrar;
public:
	Relogio() {}

	void novoCarroEntrou(){
		totalDeCarros++;
	}

	int getTotalDeCarros() {
		return totalDeCarros;
	}

	void novoCarroTentandoEntrar(){
		carrosQueTentaramEntrar++;
	}

	int getCarrosQueTentaramEntrar() {
		return carrosQueTentaramEntrar;
	}


	void saiuCarro(){
		carrosQueSairam++;
	}

	int getCarrosQueSairam() {
		return carrosQueSairam;
	}


};
