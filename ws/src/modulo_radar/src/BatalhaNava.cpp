#include <memory>
#include "rclcpp/rclcpp.hpp"		// Importa biblioteca ROS 2
#include "std_msgs/msg/string.hpp"	// Importa modelo padrão de mensagem em tópico, tenho que fazer o meu modelo depois
#include <cmath>             		// Importa biblioteca para cálculos trigonométricos em C++
#include <stdio.h>           		// Importa bibliotca para uso de printf
#include <sstream>

// Variaveis

int angulo = 30;      // Armazena o ultimo angulo medido pelo QMC5883P
double distancia = 3; // Armazena a ultima distancia medida pelo LiDAR

// Constantes

double MEDIDA_DE_QUADRO = 1.0; // Define as medidas de cada quadro em metros

// Declaracao de funcoes

double calcularX();     // Calcula o afastamento do alvo no eixo X
double calcularY();     // Calcula o afastamento do alvo no eixo Y
float anguloEmRadi();   // Calcula o equivalente em radianos do angulo em graus

// Nota:
// Depois eu faço a informação vir em radianos para poupar trabalho

// Criacao da entidade para increver no topico radar
class BatalhaNavalSubscriber : public rclcpp::Node
{
public:
  BatalhaNavalSubscriber() 

  // Cria um construtor fazendo o código 
  // seguinte ser iniciado sempre que uma
  // mensagem for publicada no topico
  : Node("batalha_naval_subscriber")
  {
	// Funcao para ouvir a mensagem e armazenar as infos nas variaveis
    auto topic_callback =
      [this](std_msgs::msg::String::UniquePtr msg) -> void {
        RCLCPP_INFO(this->get_logger(), "Eu ouvi: '%s'", msg->data.c_str());
		std::stringstream infos(msg->data); // Armazena a mensagem em uma String

		std::string anguloRecebido;					
		std::string distanciaRecebido;				

		getline(infos, anguloRecebido, '\n');		// Coleta os dados linha a linha
		getline(infos, distanciaRecebido, '\n');	// Coleta os dados linha a linha

		angulo = std::stoi(anguloRecebido);			// Transfere as informações para as respectivas variaveis
		distancia = std::stod(distanciaRecebido);	// Transfere as informações para as respectivas variaveis

		double x = calcularX();
		double y = calcularY();

		// Exibição de resultados
    	RCLCPP_INFO(this->get_logger(), "%d graus = %.2f radianos\n", angulo, anguloEmRadi());
		RCLCPP_INFO(this->get_logger(), "A medida %.2f no angulo %d, indica um obstaculo a %.2f metros a %s e %.2f metros %s\n",
	       distancia,
	       angulo,
	       x,
	       y,
	       (x > 0.0) ? "direita" : "esquerda", // Caso o valor de X seja negativo isso indica que o alvo esta a esquerda
	       (y > 0.0) ? "a frente" : "atras"    // Caso o valor de Y seja negativo isso indica que o alvo esta a atras
	    );
      };
    subscription_ =
      this->create_subscription<std_msgs::msg::String>("radar", 10, topic_callback);
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
	rclcpp::init(argc, argv);
  	rclcpp::spin(std::make_shared<BatalhaNavalSubscriber>());
  	rclcpp::shutdown();
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
    
	return distanciaX;
}

double calcularY() {
    float coseno = cos(anguloEmRadi());
    float distanciaY = coseno * distancia;

	return distanciaY;
}