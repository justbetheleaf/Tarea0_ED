// Tarea0.cpp 
// Amanda Ramírez y Mariana Torres

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include "ArrayStack.h"
#include "LinkedStack.h"
#include "ctype.h"

// para no tener que poner std siempre 
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::isalpha;

void eliminarEspaciosBlancos(string& expresion) {
    string nuevaExpresion = "";
    for (int i = 0; i < expresion.length(); i++) {
        if (expresion[i] != ' ') {
            nuevaExpresion += expresion[i];
        }
    }
    expresion = nuevaExpresion;
}

string obtenerToken(string& expresion) {
    string token = "";
    for (int i = 0; i < expresion.length(); i++) {
        if (!isdigit(expresion[i])) {
            if (token == "") {
                token += expresion[i];
            }
            break;
        }
        token += expresion[i];
    }

    expresion.erase(0, token.length());
    return token;
}

string obtenerTipoToken(string token) {
    if (token == "(" || token == ")") {
        return "parentesis";
    }
    else if (token == "*" || token == "/" || token == "+" || token == "-" || token == "^") {
        return "operador";
    }
    return "numero";
}

int obtenerValorPrecendencia(char token) {
    if (token == '+' || token == '-') {
        return 1;
    }
    else if (token == '*' || token == '/') {
        return 2;
    }
    else if (token == '^') {
        return 3;
    }
    else if (token == ')') {
        return 0;
    }
    return 0;
}

double operaciones(char operador, double x, double y){

    double result = 0;
    cout << "Resultado: " << x << operador << y << "= ";

    switch (operador)
    {
    case '+':
        result = x + y;
        break;
    case '-':
        result = x - y;
        break;
    case '*':
        result = x * y;
        break;
    case '/':
        result = x / y;
        break;
    case '^':
        result = pow(x, y);
        break;

        return result;


    }

}

int main() {
    setlocale(LC_ALL, "spanish"); // para evitar errores en las tildes

    try {
        string tipoPila;
        cout << "Indique el tipo de pila que desea utilizar (1- LinkedStack 2- ArrayStack): ";
        getline(cin, tipoPila);

        //Agregar una validacion del valor ingresado por el usuario***

        //Dependinedo del tipo de pila seleccionado se crea el objeto
        Stack<char>* pilaOperadores{};
        Stack<double>* pilaNumeros{};
        if (tipoPila == "1")
        {
            pilaOperadores = new LinkedStack<char>();
            pilaNumeros = new LinkedStack<double>();
        }
        else if (tipoPila == "2") {
            pilaOperadores = new ArrayStack<char>(5);
            pilaNumeros = new ArrayStack<double>(5);
        }

        else {
            cout << "\nExpresión no válida" << endl;
        }

        //Recibimos la expresion
        string expresion;
        cout << "Escriba la expresión a evaluar: ";
        getline(cin, expresion);



        //Eliminar los espacios en blanco
        eliminarEspaciosBlancos(expresion);

        //Recorre la expresion
        while (expresion.length() > 0) {
            //Obtener token
            string token;
            token = obtenerToken(expresion);

            string tipoToken = obtenerTipoToken(token);
            cout << "Token " + token + " tipo " + tipoToken + "\n";

            if (tipoToken == "numero") {
                double numero = stoi(token);
                pilaNumeros->push(numero);
                cout << "Valor de  Pila Numeros: ";
                pilaNumeros->print();
                cout << "\n";

            }
            else {
                char operador = token[0];

                while (!pilaOperadores->isEmpty()) {

                    if (operador == '(') {
                        pilaOperadores->push(operador);
                        cout << "Valor de Pila Operadores: ";
                        pilaOperadores->print();
                        cout << "\n";

                    }

                    if (operador == ')' && pilaOperadores->topValue() != '(') {

                        double peo = operaciones(pilaOperadores->pop(), pilaNumeros->pop(), pilaNumeros->pop());
                        cout << peo;
                        pilaNumeros->push(peo);
                        if (pilaOperadores->topValue() == '(') {
                            pilaOperadores->pop();
                        }
                        cout << "\n";
                        cout << "Valor de  Pila Numeros: ";
                        pilaNumeros->print();
                        cout << "\n";
                        break;
                    
                    }
                    else if (operador == ')' && pilaOperadores->topValue() == '(') {
                        pilaOperadores->pop();
                    }
                
                    if (obtenerValorPrecendencia(pilaOperadores->topValue()) >= obtenerValorPrecendencia(operador) && operador != '(' && operador != ')') {
                    
                        double peo = operaciones(pilaOperadores->pop(), pilaNumeros->pop(), pilaNumeros->pop());
                        cout << peo;
                        pilaNumeros->push(peo);
                        pilaOperadores->push(operador);
                        cout << "\n";
                        cout << "Valor de  Pila Numeros: ";
                        pilaNumeros->print();
                        cout << "\n";
                        break;

                    }

                    else {
                        if (operador != ')') {
                            pilaOperadores->push(operador);
                            break;

                        }
                        break;
                    }
                }

                if (pilaOperadores->isEmpty() && operador != ')') {
                    pilaOperadores->push(operador);
                } 

                cout << "Valor de Pila Operadores: ";
                pilaOperadores->print();
                cout << "\n";


            }
        }

        while (!pilaOperadores->isEmpty()) {
            cout << "\n" << "Valor de Pila Operadores FINAL: [ " << pilaOperadores->topValue() << " ]" << "\n";

            if (pilaOperadores->topValue() == '(') {
                pilaOperadores->pop();
            }
            else if (pilaOperadores->topValue() == ')') {
                pilaOperadores->pop();
            }
            else {
                double peo = operaciones(pilaOperadores->pop(), pilaNumeros->pop(), pilaNumeros->pop());
                cout << peo;
                pilaNumeros->push(peo);
            }

        }

    }
    catch (...) {
        cout << "\nHay un error en la expresión" << endl;
    }

    return 0;
}



