#include <iostream>
#include <chrono>

const int MAX = 128; // Tamaño máximo de matriz
const int BLOCK_SIZE = 16; // Tamaño del bloque (puedes ajustarlo para obtener un mejor rendimiento)

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

void multiplyMatricesBlock(const double A[][MAX], const double B[][MAX], double C[][MAX], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			C[i][j] = 0.0;
		}
	}
	
	// Seis bucles anidados para multiplicación por bloques
	for (int i = 0; i < size; i += BLOCK_SIZE) {
		for (int j = 0; j < size; j += BLOCK_SIZE) {
			for (int k = 0; k < size; k += BLOCK_SIZE) {
				// Multiplica los bloques
				for (int ii = i; ii < std::min(i + BLOCK_SIZE, size); ii++) {
					for (int jj = j; jj < std::min(j + BLOCK_SIZE, size); jj++) {
						for (int kk = k; kk < std::min(k + BLOCK_SIZE, size); kk++) {
							C[ii][jj] += A[ii][kk] * B[kk][jj];
						}
					}
				}
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
		
	
		auto start = std::chrono::high_resolution_clock::now();
		multiplyMatricesV1(A, B, C, size);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::nano> durationV1 = end - start;
		std::cout << "Tiempo de ejecucion (Version 1) para matrices de tamano " << size << "x" << size << ": " 
			<< durationV1.count() << " nanosegundos" << std::endl;
		

		start = std::chrono::high_resolution_clock::now();
		multiplyMatricesBlock(A, B, C, size);
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::nano> durationBlock = end - start;
		std::cout << "Tiempo de ejecucion (Multiplicacion por Bloques) para matrices de tamano " << size << "x" << size << ": " 
			<< durationBlock.count() << " nanosegundos" << std::endl;
	}
	//Al probar ambos enfoques, deberías observar mejoras significativas para matrices grandes 
	//al usar la versión por bloques, debido al mejor aprovechamiento de la jerarquía de memoria.
	return 0;
}



