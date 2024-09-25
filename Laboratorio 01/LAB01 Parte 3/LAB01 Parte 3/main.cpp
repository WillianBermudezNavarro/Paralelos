#include <iostream>
#include <chrono>

const int MAX = 128; 

// Multiplicar matrices 
void multiplyMatricesV1(const double A[][MAX], const double B[][MAX], double C[][MAX], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			C[i][j] = 0.0;
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// 	Bucles anidados
void multiplyMatricesV2(const double A[][MAX], const double B[][MAX], double C[][MAX], int size) {
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			C[i][j] = 0.0;
		}
	}
	
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++) {
			for (int j = 0; j < size; j++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void printMatrix(const double mat[][MAX], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


int main() {
	const int sizes[] = { 2, 4, 8, 16, 32, 64, 128 }; 
	const int numSizes = sizeof(sizes) / sizeof(sizes[0]);
	
	for (int idx = 0; idx < numSizes; ++idx) {
		int size = sizes[idx];
		
		double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				A[i][j] = i + j + 1; 
				B[i][j] = i + 1;  
			}
		}
		
		// Medir el tiempo de ejecución de la primera version de la multiplicacion de matrices
		auto start = std::chrono::high_resolution_clock::now();
		multiplyMatricesV1(A, B, C, size);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::nano> durationV1 = end - start;
		
		std::cout << "Tiempo de ejecución (Version 1) para matrices de tamano " << size << "x" << size << ": " 
			<< durationV1.count() << " nanosegundos" << std::endl;
		
		// Medir el tiempo de ejecución de la multiplicacion de bucles anidadoss
		start = std::chrono::high_resolution_clock::now();
		multiplyMatricesV2(A, B, C, size);
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::nano> durationV2 = end - start;
		
		std::cout << "Tiempo de ejecución (Version 2) para matrices de tamano " << size << "x" << size << ": " 
			<< durationV2.count() << " nanosegundos" << std::endl;
	}
	
	return 0;
}
