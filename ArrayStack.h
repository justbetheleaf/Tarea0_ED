#pragma once

#define DEFAULT_MAX_SIZE 1024

#include <stdexcept>
#include <iostream>
#include "Stack.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayStack : public Stack<E>
{
private:
	E* elements;
	int max;
	int top;

public:
	ArrayStack(int max = DEFAULT_MAX_SIZE) {
		elements = new E[max];
		this->max = max;
		top = 0;
	}
	~ArrayStack() {
		delete[] elements;
	}
	void push(E element) {
		if (top == max) {
			
			//Crear un arreglo del doble del tamaño
			E* nuevaPila = new E[max * 2];
			
			//Copiar los elementos del viejo arreglo al nuevo.
			for (int i = 0; i < top; ++i) {
				nuevaPila[i] = elements[i];  // Paso 2: Copiar elementos del viejo arreglo al nuevo
			}

			//Eliminar el arreglo viejo de la memoria.
			delete elements;

			//Hacer que el atributo elements apunte al nuevo arreglo.
			elements = nuevaPila;

			//Hacer que el atributo max valga el doble.
			max = max * 2;
		}
		elements[top] = element;
		top++;
	}
	E pop() {
		if (top == 0) {
			throw runtime_error("Stack underflow.");
		}
		top--;
		return elements[top];
	}
	E topValue() {
		if (top == 0) {
			throw runtime_error("Stack is empty.");
		}
		return elements[top - 1];
	}
	void clear() {
		top = 0;
	}
	bool isEmpty() {
		return top == 0;
	}
	int getSize() {
		return top;
	}
	void print() {
		cout << "[ ";
		for (int i = 0; i <= top - 1; i++) {
			cout << elements[i] << " ";
		}
		cout << "]" << endl;
	}
};

