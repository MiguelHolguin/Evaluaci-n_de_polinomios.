#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>
#include <random>
#include <string>
#include <fstream>
#include <functional>
#include <iomanip>

class Polinomio {
private:
    std::vector<int> coeficientes;

public:
    Polinomio(const std::vector<int>& coefs) : coeficientes(coefs) {}

    double evaluarTradicional(double valor) const {
        return std::accumulate(coeficientes.begin(), coeficientes.end(), 0.0,
            [valor, potencia = 0](double suma, int coef) mutable {
                return suma + coef * std::pow(valor, potencia++);
            });
    }

    double evaluarOptimizado(double valor) const {
        return std::accumulate(coeficientes.rbegin(), coeficientes.rend(), 0.0,
            [valor](double acumulado, int coef) {
                return acumulado * valor + coef;
            });
    }

    size_t grado() const {
        return coeficientes.size() - 1;
    }
};

class GeneradorAleatorio {
private:
    std::mt19937 generador;
    std::uniform_int_distribution<> distribCoeficientes;
    std::uniform_real_distribution<> distribVariable;

public:
    GeneradorAleatorio() :
        generador(std::random_device{}()),
        distribCoeficientes(-10, 10),
        distribVariable(-10.0, 10.0) {}

    Polinomio crearPolinomio(int grado) {
        std::vector<int> coefs(grado + 1);
        std::generate(coefs.begin(), coefs.end(), [this]() {
            return distribCoeficientes(generador);
        });
        return Polinomio(coefs);
    }

    double obtenerValorX() {
        double x;
        do {
            x = distribVariable(generador);
        } while (std::abs(x) < 1e-10);
        return x;
    }
};

class AnalizadorRendimiento {
private:
    using MetodoEvaluacion = std::function<double(const Polinomio&, double)>;

    static double ejecutarMetodoTradicional(const Polinomio& pol, double x) {
        return pol.evaluarTradicional(x);
    }

    static double ejecutarMetodoOptimizado(const Polinomio& pol, double x) {
        return pol.evaluarOptimizado(x);
    }

public:
    struct ResultadoComparacion {
        int grado;
        long long tiempoTradicional;
        long long tiempoOptimizado;
    };

    static long long medirRendimiento(const Polinomio& polinomio,
                                     double valorX,
                                     MetodoEvaluacion metodo,
                                     int repeticiones) {
        using namespace std::chrono;

        auto inicio = high_resolution_clock::now();
        for (int i = 0; i < repeticiones; ++i) {
            metodo(polinomio, valorX);
        }
        auto fin = high_resolution_clock::now();

        return duration_cast<nanoseconds>(fin - inicio).count() / repeticiones;
    }

    static ResultadoComparacion compararMetodos(int grado, int repeticiones) {
        GeneradorAleatorio generador;
        auto polinomio = generador.crearPolinomio(grado);
        auto x = generador.obtenerValorX();

        long long tiempoTradicional = medirRendimiento(
            polinomio, x, ejecutarMetodoTradicional, repeticiones);

        long long tiempoOptimizado = medirRendimiento(
            polinomio, x, ejecutarMetodoOptimizado, repeticiones);

        return {grado, tiempoTradicional, tiempoOptimizado};
    }
};

class RegistradorResultados {
private:
    std::ofstream archivo;

public:
    RegistradorResultados(const std::string& nombreArchivo) : archivo(nombreArchivo) {
        if (!archivo) {
            throw std::runtime_error("No se pudo abrir el archivo para escritura");
        }
        archivo << "grado,tiempo_tradicional_ns,tiempo_optimizado_ns\n";
    }

    void registrar(const AnalizadorRendimiento::ResultadoComparacion& resultado) {
        archivo << resultado.grado << ","
                << resultado.tiempoTradicional << ","
                << resultado.tiempoOptimizado << "\n";
    }

    ~RegistradorResultados() {
        if (archivo.is_open()) {
            archivo.close();
        }
    }
};

int main() {
    try {
        RegistradorResultados registrador("resultados.csv");
        const int repeticiones = 1000;

        std::cout << "+" << std::string(57, '-') << "+" << std::endl;
        std::cout << "| " << std::left << std::setw(12) << "Grado"
                  << "| " << std::setw(20) << "Tiempo Estandar (ns)"
                  << "| " << std::setw(20) << "Tiempo Horner (ns)"
                  << "|" << std::endl;
        std::cout << "+" << std::string(57, '-') << "+" << std::endl;

        for (int grado = 10; grado <= 1000; grado += 10) {
            auto resultado = AnalizadorRendimiento::compararMetodos(grado, repeticiones);

            std::cout << "| " << std::left << std::setw(12) << resultado.grado
                      << "| " << std::setw(20) << resultado.tiempoTradicional
                      << "| " << std::setw(20) << resultado.tiempoOptimizado
                      << "|" << std::endl;

            registrador.registrar(resultado);
        }

        std::cout << "+" << std::string(62, '-') << "+" << std::endl;
        std::cout << "Analisis completado y resultados guardados en 'resultados.csv'" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
