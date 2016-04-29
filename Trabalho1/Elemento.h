#ifndef ELEMENTO_HEADER
#define ELEMENTO_HEADER

template<typename T>

class Elemento {
private:
	T *info = NULL;
	Elemento<T>* _next = NULL;

public:
	Elemento(const T& info, Elemento<T>* next) : info(new T(info)), _next(next) {}

	~Elemento() {
		delete info;
	}

	Elemento<T>* getProximo() const {
		return _next;
	}

	T getInfo() const {
		return *info;
	}

	void setProximo(Elemento<T>* next) {
		_next = next;
	}

	// Próximo método criado por Matteus Legat.
	void destrucaoEncadeada() {  // Destrói todos os próximos elementos
		if (_next == NULL) {  // SE for o último da lista, volta para elemento ant.
			return;
		}
		else {
			_next->destrucaoEncadeada();  // Chama destruç.enc. do prox. elemento
			delete _next;  // libera proximo elemento depois que proximo for chamado
		}
	}
};

#endif