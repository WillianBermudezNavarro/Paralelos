#include <iostream>

const int MAX = 4; 

int main() {
	double A[MAX][MAX], x[MAX], y[MAX];

	for (int i = 0; i < MAX; i++) {
		x[i] = 1.0; 
		y[i] = 0.0; 
		for (int j = 0; j < MAX; j++) {
			A[i][j] = i + j + 1; 
		}
	}
	std::cout << "Matriz A:" << std::endl;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}
	// Primer 
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			y[i] += A[i][j] * x[j];
		}
	}
	//Accede  A por filas, lo que debería ser más eficiente en términos de caché.
	std::cout << "Vector y despues del primer par de bucles:" << std::endl;
	for (int i = 0; i < MAX; i++) {
		std::cout << y[i] << " ";
	}
	std::cout << std::endl;
	
	// Reinicializar
	for (int i = 0; i < MAX; i++) {
		y[i] = 0.0;
	}
	// Segundo 
	for (int j = 0; j < MAX; j++) {
		for (int i = 0; i < MAX; i++) {
			y[i] += A[i][j] * x[j];
		}
	}
	//Accede  B por columnnas, lo que puede ser menos eficiente debido al patrón de acceso.
	std::cout << "Vector y despues del segundo par de bucles:" << std::endl;
	for (int i = 0; i < MAX; i++) {
		std::cout << y[i] << " ";
	}
	std::cout << std::endl;
	
	return 0;
}

