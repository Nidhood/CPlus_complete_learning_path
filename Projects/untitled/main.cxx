#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Polynomial.h"

//g++ -std=c++11 -o main main.cxx
typedef double TScalar; //Se define 0 el tipo de dato que se va a utilizar
typedef Polynomial<TScalar> TPolynomial; //Se define un template para el polinomio
typedef std::vector<TPolynomial> TPolynomials; //se define un vector de tipo TPolynomial el cual guarda polinomios

int main(int argc, char* argv[]) {
    if (argc < 2) {   //Estan inciando una condicion if() donde Si el argumento (variable) es menor a 2, entonces se ejecuta el siguiente bloque de codigo.
        std::cout << "Usage: " << argv[0] << " input" << std::endl;  //Esta linea de codigo imprime en pantalla el mensaje "Usage: argv[ 0 ], cuando se cumple la condicion anterior
        return 1;  // retorna un entero de valor 1
    }

    std::string input_filename = argv[1];   //Esta linea de codigo define una variable input_filename como un string y le asigna el valor


    // Abrir archivo de texto
    std::ifstream input("../" + input_filename);
    if (!input) {   //Si el archivo no se puede abrir, entonces se ejecuta el siguiente bloque de codigo
        std::cout << "Error opening \"" << input_filename << "\"" << std::endl;  //Se imprime en pantalla el mensaje "Error opening " y el nombre del archivo
        return 1;     // retorna un entero de valor 1   
    }

    // Datos para el análisis
    TPolynomials polys;   //Esta linea nos esta dando el tipo de dato TPolynomials y le asignamos el nombre polys

    // Leer la línea que contiene el número de polinomios
    std::string input_line;  //Se define una variable input_line como un string
    std::getline(input, input_line);  //Se lee la linea de texto del archivo input y se asigna a la variable input_line
    unsigned int nPolys = std::atoi(input_line.c_str()); // Convertido a c_str() ya que std::atoi espera un const char*

    // Leer polinomios
    for (unsigned int p = 0; p < nPolys; ++p) {  //Este for() recorre el archivo input y lee cada linea de texto
        // Crear polinomio vacío
        polys.push_back(TPolynomial());  //Esta linea de codigo crea un nuevo objeto TPolynomial y lo asigna al final del vector polys

        // Leer línea
        std::getline(input, input_line); //Se lee la linea de texto del archivo input y se asigna a la variable input_line

        // Tokenizar
        std::stringstream tokens(input_line);   //Se define una variable tokens como un stringstream y se le asigna el valor de la variable input_line

        // Extraer datos de los tokens
        std::string token;  //Define la variable token como un string
        while (tokens >> token) {    //Se realiza el codigo que este dentro de los corchetes mientras el valor de la variable tokens sea mayor a token
            unsigned int degree = std::atoi(token.c_str()); //Tenemos una variable sin signo de tipo entero llamada degree y se le asigna el valor de la variable token convertido a entero
            tokens >> token; //Se lee la linea de texto del archivo input y se asigna a la variable token
            TScalar coefficient = std::atof(token.c_str());  //Se define una variable de tipo flotante llamada coefficient y se le asigna el valor de la variable token

            // Actualizar polinomio
            polys[p].SetCoefficient(degree, coefficient);  //Se le asigna el valor de la variable coefficient a la posicion de la variable degree del vector polys
        }
        std::cout << "Input " << p << " = " << polys[p] << std::endl;  //Se imprime en pantalla el mensaje "Input " y el valor de la variable p y el mensaje " = " y el valor del vector polys en la posicion p
    }

    // Ejecutar operaciones deseadas
    bool stop = false;  //Se define un booleano llamado stop y se le asigna el valor de false
    while (std::getline(input, input_line) && !stop) {
        // Tokenizar
        std::stringstream tokens(input_line);

        // Obtener operador y operandos
        char type;
        tokens >> type;

        if (type != 'E') {
            switch (type) {
                case 'A': {
                    unsigned int a_id, b_id;
                    tokens >> a_id >> b_id;
                    if (a_id < polys.size() && b_id < polys.size()) {
                        std::cout
                            << "Suma (" << a_id << ", " << b_id << ") = "
                            << (polys[a_id] + polys[b_id]) << std::endl;
                    } else {
                        std::cout << "Índices de polinomios no válidos para la suma" << std::endl;
                    }
                    break;
                }
                case 'M': {
                    unsigned int a_id, b_id;
                    tokens >> a_id >> b_id;
                    if (a_id < polys.size() && b_id < polys.size()) {
                        std::cout
                            << "Multiplicación (" << a_id << ", " << b_id << ") = "
                            << (polys[a_id] * polys[b_id]) << std::endl;
                    } else {
                        std::cout << "Índices de polinomios no válidos para la multiplicación" << std::endl;
                    }
                    break;
                }
                case 'P': {
                    unsigned int id;
                    TScalar x;
                    tokens >> id >> x;
                    if (id < polys.size()) {
                        std::cout
                            << "Polinomio (" << id << ", " << x << ") = "
                            << polys[id](x) << std::endl;
                    } else {
                        std::cout << "Índice de polinomio no válido para la evaluación" << std::endl;
                    }
                    break;
                }
                default:
                    break;
            }
        } else {
            stop = true;
        }
    }


    // Cerrar archivo de texto
    input.close();

    return 0;
}