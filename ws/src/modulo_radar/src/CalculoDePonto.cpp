#include <cmath>

class CalculoDePonto {
        
    private:
        double anguloEmRad(double angle) {
            return angle * (3.14 / 180);
        };

    public:
        CalculoDePonto(){}

        double calcularDistanciaY(double distance, double angle){
            return cos(anguloEmRad(angle)) * distance;
        }

        double calcularDistanciaX(double distance, double angle){
            return sin(anguloEmRad(angle)) * distance;
        }
};