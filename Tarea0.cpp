// Tarea0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
    string token="";
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

int obtenerValorPrecendencia(string token) {
    if (token == "+" || token == "-") {
        return 1;
    }
    else if (token == "*" || token == "/") {
        return 2;
    }
    else if (token == "^") {
        return 3;
    }
    return 0;
}

bool esPrecedente(string tokenAnterior, string tokenSiguiente) {
    int valorTokenAnterior = obtenerValorPrecendencia(tokenAnterior);
    int valorTokenSiguiente = obtenerValorPrecendencia(tokenSiguiente);

    if (valorTokenSiguiente >= valorTokenAnterior) {
        return true;
    }

    return false;
}

int main()
{
    setlocale(LC_ALL, "spanish"); // para evitar errores en las tildes

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
    else {
        pilaOperadores = new ArrayStack<char>(5);
        pilaNumeros = new ArrayStack<double>(5);
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
        
        //Agregar una validacion para verificar que sea una expresion valida**
        
               
        //Cuando se realiza el llenado de los arreglos tomar en cuenta que si es de
        //tipo ArrayStack este se crea de tamaño 5 y si se llena se debe de crear un 
        //nuevo arreglo del doble del tamaño y mover todos los elementos del arreglo
        //anterior al arreglo nuevo. Recordar destruir el arreglo anterior.
    }
    
    //Probar precendecia**
    //esta funcion le va a servir para validar la precedencia de los operadores durante la
    //ejecucion de la operacion +
    bool precedencia = esPrecedente("^", "-");
    if (precedencia) {
        cout << "Tiene precedencia";
    }
    else {
        cout << "No tiene precedencia";
    }

    return 0;

} 



