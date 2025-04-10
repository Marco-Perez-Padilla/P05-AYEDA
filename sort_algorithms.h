/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Algoritmos y Estructuras de Datos Avanzadas
** Curso: 2º
** Practica 5: Algoritmos de ordenación
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 31/03/2025

** Archivo sequence.h: Declaracion e implementacion de funciones de ordenación
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      31/03/2025 - Creacion (primera version) del codigo
**      02/04/2025 - 
**/

#ifndef ORDENATION_METHODS_H
#define ORDENATION_METHODS_H

#include <vector>
#include "sequence.h"


/**
 * @brief Function that sorts a given sequence using the insertion sort method
 * @param StaticSequence sequence to be sorted
 * @param unsigned size, size of the sequence
 * @param bool trace. Indicates if the function must print the trace or not
 */
template <class Key> void InsertionSort(StaticSequence<Key>& sequence, unsigned size, bool trace = false) {
  for (unsigned i {1}; i < size; i++) {
    Key key = sequence[i];
    int j = i -1;

    while (j >= 0 && sequence[j] > key) {
      sequence[j + 1] = sequence[j];
      j--;
    }
  
    sequence[j + 1] = key;

    if (trace) {
      std::cout << "Iteration " << i << ": ";
      for (unsigned k = 0; k < size; k++) {
        std::cout << sequence[k] << " ";
      }
      std::cout << std::endl;
    }
  }
}


/**
 * @brief Function that sorts a given sequence using the shake sort method
 * @param StaticSequence sequence to be sorted
 * @param unsigned size, size of the sequence
 * @param bool trace. Indicates if the function must print the trace or not
 */
template <class Key> void ShakeSort(StaticSequence<Key>& sequence, unsigned size, bool trace = false) {
  unsigned left = 0;
  unsigned right = size - 1;
  unsigned lastSwap; 
  unsigned iteration = 0;
  
  while (left < right) {
    lastSwap = left;
    for (unsigned j = left; j < right; j++) {
      if (sequence[j] > sequence[j + 1]) {
        std::swap(sequence[j], sequence[j + 1]);
        lastSwap = j;
      }
    }
    right = lastSwap;
    
    if (trace) {
      iteration++;
      std::cout << "Iteration " << iteration << " (first step): ";
      for (unsigned k = 0; k < size; k++) {
        std::cout << sequence[k] << " ";
      }
      std::cout << std::endl;
    }
    
    lastSwap = right;
    for (unsigned j = right; j > left; j--) {
      if (sequence[j - 1] > sequence[j]) {
        std::swap(sequence[j - 1], sequence[j]);
        lastSwap = j;
      }
    }
    left = lastSwap;
    
    if (trace) {
      std::cout << "Iteration " << iteration << " (second step): ";
      for (unsigned k = 0; k < size; k++) {
        std::cout << sequence[k] << " ";
      }
      std::cout << std::endl;
    }
    
    iteration++;
  }
}


/**
 * @brief Function that invokes a recursive function to sort a sequence
 * @param StaticSequence sequence to be sorted
 * @param unsigned size, size of the sequence
 * @param bool trace. Indicates if the function must print the trace or not
 */
template <class Key> void QuickSort(StaticSequence<Key>& sequence, unsigned size, bool trace = false) {
  unsigned int iteration = 0;
  RecursiveQuickSort(sequence, 0, size - 1, trace, iteration);
}


/**
 * @brief Function that sorts a given sequence using the quick sort method
 * @param StaticSequence sequence to be sorted
 * @param int initial position 
 * @param int last position
 * @param bool trace. Indicates if the function must print the trace or not
 */
template <class Key> void RecursiveQuickSort(StaticSequence<Key>& sequence, int ini, int fin, bool trace = false, unsigned int& iteration = 0) {
  if (ini >= fin) {
    return;  
  }

  unsigned int i = ini;
  unsigned int f = fin;
  Key p = sequence[(i + f) / 2];  

  while (i <= f) {
    while (sequence[i] < p) i++;
    while (sequence[f] > p) f--;
    
    if (i <= f) {
      std::swap(sequence[i], sequence[f]);
      i++;
      f--;
    }
  }
  
  if (trace) {
    iteration++;
    std::cout << "Iteration " << iteration << " with pivot " << p << ": ";
    for (unsigned int k = 0; k <= fin; k++) {
      std::cout << sequence[k] << " ";
    }
    std::cout << std::endl;
  }
  
  if (ini < f) RecursiveQuickSort(sequence, ini, f, trace, iteration);
  if (i < fin) RecursiveQuickSort(sequence, i, fin, trace, iteration);
}


/**
 * @brief Function that invokes an auxiliar function to help sorting a sequence
 * @param StaticSequence sequence to be sorted
 * @param unsigned size, size of the sequence
 * @param bool trace. Indicates if the function must print the trace or not
 */
template <class Key> void HeapSort(StaticSequence<Key>& sequence, unsigned size, bool trace = false) {
  for (int i = (size/2) - 1; i >= 0; i--) {
    baja(i, sequence, size);
  }
  for (int i = size -1; i > 0; i--) {
    if (trace) {
      std::cout << "Heap after " << i << " iteration:" << std::endl;
    }
    std::swap(sequence[0], sequence[i]);
    baja(0, sequence, i, trace);
  }
}


/**
 * @brief Auxiliar function to heapify the sequence
 * @param int i iteration
 * @param StaticSequence sequence to be sorted
 * @param int size of the heap
 * @param bool trace. Indicates if the function must print the trace or not
 */
template <class Key> void baja(int i, StaticSequence<Key>& sequence, int heap_size, bool trace = false) {
  while (true) {
    int left = 2*i + 1;  
    int right = left + 1;
    int h;

    if (left >= heap_size) break;  
    
    if (right >= heap_size) {
      h = left;  
    } else {
      h = (sequence[left] > sequence[right]) ? left : right;
    }

    if (sequence[h] <= sequence[i]) break;

    std::swap(sequence[i], sequence[h]);
      
    i = h;  
  }

  if (trace) {
    for (int i {0}; i < heap_size; ++i) {
      std::cout << sequence[i] << " ";
    }
    std::cout << std::endl;
  }
}


/**
 * @brief Function that sorts a given sequence using the shake sort method
 * @param StaticSequence sequence to be sorted
 * @param unsigned size, size of the sequence
 * @param double alpha, variable between 0 and 1
 * @param bool trace. Indicates if the function must print the trace or not
 */
template <class Key> void ShellSort(StaticSequence<Key>& sequence, unsigned size, double alpha, bool trace = false) {
  int delta = size;
  while (delta > 1) {
    delta = static_cast<int>(delta * alpha);
    delta = (delta < 1) ? 1 : delta;  

    if (trace) {
      std::cout << "Delta: " << delta << ". ";
    }

    for (int i = delta; i < size; ++i) {
      Key temp = sequence[i];
      int j = i;

      while (j >= delta && temp < sequence[j - delta]) {
        sequence[j] = sequence[j - delta];
        j -= delta;

        if (trace) {
          std::cout << "  Swapped " << sequence[j] << " from " << j << " to " << j + delta << "\n";
        }
      }
      sequence[j] = temp;
    }

    if (trace) {
      std::cout << "Current state: ";
      for (unsigned k = 0; k < size; ++k) {
        std::cout << sequence[k] << " ";
      }
      std::cout << "\n";
    }
  }
}


#endif