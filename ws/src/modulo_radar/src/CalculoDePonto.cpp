#include <cmath>

class CalculoDePonto() {
    public:
        CalculoDePonto(){}

        double calcularDistanciaY(double distance, double angle){
            return cos(anguloEmRad(angle)) * distance;
        }

        double calcularDistanciaX(double distance, double angle){
            return sin(anguloEmRad(angle)) * distance;
        }
        
    private:
        auto anguloEmRad = [](double angle) {
            return angle * (3.14 / 180);
        }
}