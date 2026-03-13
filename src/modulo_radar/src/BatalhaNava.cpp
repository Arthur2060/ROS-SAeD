#include "rclcpp/rclcpp.hpp" // Importa biblioteca ROS 2
#include <cmath>             // Importa biblioteca para cálculos complexos em C++
#include <stdio.h>           // Importa bibliotca para uso de printf

// Variaveis

int angulo = 30;      // Armazena o ultimo angulo medido pelo QMC5883P
double distancia = 3; // Armazena a ultima distancia medida pelo LiDAR

// Constantes

double MEDIDA_DE_QUADRO = 1.0; // Define as medidas de cada quadro em metros

// Declaracao de funcoes

double calcularX();     // Calcula o afastamento do alvo no eixo X
double calcularY();     // Calcula o afastamento do alvo no eixo Y
float anguloEmRadi();   // Calcula o equivalente em radianos do angulo em graus

// Depois eu faço a informação vir em radianos para poupar trabalho

int main() {
	// Exibindo dados calculados

    printf("%d graus = %.2f radianos\n", angulo, anguloEmRadi);
	printf("A medida %.2f no angulo %d, indica um obstaculo a %.2f metros a %s e %.2f metros %s\n",
	       distancia,
	       angulo,
	       calcularX(),
	       calcularY(),
	       (calcularX() > 0.0) ? "direita" : "esquerda", // Caso o valor de X seja negativo isso indica que o alvo esta a esquerda
	       (calcularY() > 0.0) ? "a frente" : "atras"    // Caso o valor de Y seja negativo isso indica que o alvo esta a atras
	      );

	return 0;
}

// Construcao de funcoes

float anguloEmRadi() {
    float anguloEmRadi = angulo * (M_PI / 180.0);
    
    return anguloEmRadi;
}

double calcularX() {
    float seno = sin(anguloEmRadi());
    float distanciaX = seno * distancia;
    
    printf("Seno(%d) = %.2f\n", angulo, seno);
    printf("%.2f X %.2f = %.2f\n\n", seno, distancia, distanciaX);
	return distanciaX;
}

double calcularY() {
    float coseno = cos(anguloEmRadi());
    float distanciaY = coseno * distancia;
    
    printf("Coseno(%d) = %.2f\n", angulo, coseno);
    printf("%.2f X %.2f = %.2f\n\n", coseno, distancia, distanciaY);
	return distanciaY;
}