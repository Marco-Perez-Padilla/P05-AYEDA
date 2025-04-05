/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Algoritmos y Estructuras de Datos Avanzadas
** Curso: 2º
** Practica 5: Algoritmos de ordenación
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 22/03/2025

** Archivo sequence.h: Declaracion e implementacion de la plantilla para las secuencias estáticas y dinámicas
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      22/03/2025 - Creacion (primera version) del codigo
**      23/03/2025 - Creación de sub-clases dinamica y estatica
**      23/03/2025 - Adicion comprobacion block size no 0
**      28/03/2025 - Adicion sobrecarga metodo []
**/

#ifndef ORDENATION_METHODS_H
#define ORDENATION_METHODS_H

#include <vector>
#include "sequence.h"


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


template <class Key> void ShakeSort(StaticSequence<Key>& sequence, unsigned size, bool trace = false) {
  unsigned ini = 0; 
  unsigned fin = size - 1 ; 
  unsigned cam = size;
  unsigned iteration = 0;
  
  while (ini < fin) {
    for (int j = fin; j > ini; j--) {
      if (sequence[j] < sequence[j-1]) {
        std::swap(sequence[j-1],sequence[j]);
        cam = j ;
      } 
    }

    ini = cam + 1 ;

    if (trace) {
      iteration++;
      std::cout << "First step in interation " << iteration << ": ";
      for (unsigned k = 0; k < size; k++) {
        std::cout << sequence[k] << " ";
      }
      std::cout << std::endl;
    }

    for (int j = ini; j <= fin; j++) {
      if (sequence[j] < sequence[j-1]) {
        std::swap(sequence[j-1],sequence[j]) ;
        cam = j;
      } 
    }

    fin = cam;

    if (trace) {
      std::cout << "Second step in iteration " << iteration << ": ";
      for (unsigned k = 0; k < size; k++) {
        std::cout << sequence[k] << " ";
      }
      std::cout << std::endl;
    }

    ++iteration;
  } 
}


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


// Wrapper function
template <class Key> void QuickSort(StaticSequence<Key>& sequence, unsigned size, bool trace = false) {
  unsigned int iteration = 0;
  RecursiveQuickSort(sequence, 0, size - 1, trace, iteration);
}


template <class Key> void HeapSort(StaticSequence<Key>& sequence, unsigned size, bool trace = false) {
  for (int i = (size/2) - 1; i >= 0; i--) {
    if (trace) {
      std::cout << "First step after " << i << " iteration:" << std::endl;
    }
    baja(i, sequence, size);
  }
  for (int i = size -1; i > 0; i--) {
    if (trace) {
      std::cout << "Second step after " << i << " iteration:" << std::endl;
    }
    std::swap(sequence[0], sequence[i]);
    baja(0, sequence, i, trace);
  }
}


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


template <class Key> void ShellSort(StaticSequence<Key>& sequence, unsigned size, float alpha, bool trace = false) {
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
          std::cout << "  Movido " << sequence[j] << " de pos " << j << " a " << j + delta << "\n";
        }
      }
      sequence[j] = temp;
    }

    if (trace) {
      std::cout << "Estado actual: ";
      for (unsigned k = 0; k < size; ++k) {
        std::cout << sequence[k] << " ";
      }
      std::cout << "\n";
    }
  }
}


#endif