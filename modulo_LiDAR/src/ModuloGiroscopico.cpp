#include <mpu6050.h>
#include <cmath>
#include <vector>
#include <chrono>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

const int TAMANHO_MAPA_VERTICAL = 26;
const int TAMANHO_MAPA_HORIZONTAL = 26;
const float DISTANCIA_MEDIDA = 4.0;
const float DIMENSAO_DE_QUADRO = 1.0;

float calcularDistanciaX(float distancia);
float calcularDistanciaY(float angulo);
std::vector<int> calcularCelula(float distanciaX, float distanciaY);

void configurarAcelerometro();
void configurarGyroscopio();
void configurarTermometro();
void configurarSerial();
void configurarMPU();
void calcularPontos();

bool tabuleiro[TAMANHO_MAPA_VERTICAL][TAMANHO_MAPA_HORIZONTAL] = {};

using namespace std::chrono_literals;

 
class ModuloGiroscopico : public rclcpp::Node
{
public:
  ModuloGiroscopico()
  : Node("modulo_giroscopico"), count_(0)
  {
    configurarAcelerometro();
    configurarGyroscopio();
    configurarTermometro();
    configurarSerial();
    configurarMPU();

    publisher_ = this->create_publisher<std_msgs::msg::String>("Radar", 10);
    auto timer_callback =
      [this]() -> void {
        auto message = std_msgs::msg::String();
        message.data = calcularPontos() + std::to_string(this->count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        this->publisher_->publish(message);
      };
    timer_ = this->create_wall_timer(500ms, timer_callback);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}

float calcularDistanciaY() {
  return sin(getAngleZ()) * DISTANCIA_MEDIDA;
}

std::vector<float> std::vector<int> calcularDistanciaX() {
    const float DISTANCIA_X = calcularDistanciaY()

    float cateto_adjacente = pow(DISTANCIA_X, 2);
    float cateto_oposto = pow(DISTANCIA_MEDIDA, 2) - pow(DISTANCIA_X, 2);
    return {sqrt(cateto_oposto), DISTANCIA_X};
}

std::vector<int> calcularCelula()
{
  const std::vector<float> DISTANCIAS = calcularDistanciaX();

  int X = DISTANCIAS[0] / DIMENSAO_DE_QUADRO;
  int Y = DISTANCIAS[1] / DIMENSAO_DE_QUADRO;
  
  return {Y, X};
}

void configurarSerial() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);
}
void configurarMPU() {
  Serial.println("Adafruit MPU6050 teste!");

  if (!mpu.begin()) {
    Serial.println("Acelerometro nao encontrado!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 pronto!");
}

void configurarAcelerometro() {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
}

void configurarGyroscopio() {
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }
}

void configurarTermometro() {
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
}

void calcularPontos(){
  for (int linha = 0 ; linha <= TAMANHO_MAPA_VERTICAL ; linha++) {
    for (int coluna = 0 ; coluna <= TAMANHO_MAPA_HORIZONTAL ; coluna++) {
      int coordenadas[] = {coluna, linha};
      if (calcularCelula(coluna, linha)[0] == coordenadas[0] &&
          calcularCelula(coluna, linha)[1] == coordenadas[1]
        ) {
        tabuleiro[linha][coluna] = false;
      } else {
        tabuleiro[linha][coluna] = true;
      }
    }
  }

  for (int linha = 0 ; linha <= TAMANHO_MAPA_VERTICAL ; linha++) {
    for (int coluna = 0 ; coluna <= TAMANHO_MAPA_HORIZONTAL ; coluna++) {
      if (tabuleiro[linha][coluna]) {
        Serial.print("[ ]");
      } else {
        Serial.print("[X]");
      }
      Serial.println("");
    }
  }
}