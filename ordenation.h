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

** Archivo ordenation.h: Declaracion e implementacion de las plantillas para métodos de ordenación
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      31/03/2025 - Creacion (primera version) del codigo
**/

#ifndef ORDENATION_H
#define ORDENATION_H

#include "sequence.h"
#include "sort_algorithms.h"


/**
 * @brief Abstract class for sorting methods
 */
template <typename Key> class SortMethod {
 protected:
  StaticSequence<Key>& sequence_;
  unsigned size_;
  bool trace_;  

 public:
  SortMethod(StaticSequence<Key>& sequence, unsigned size, bool trace = false) : sequence_(sequence), size_(size), trace_(trace) {}
  virtual ~SortMethod() {}
  virtual void Sort() = 0;
};


/**
 * @brief Sub-class for insertion sort method
 */
template <typename Key> class InsertionSortMethod : public SortMethod<Key> {
 public:
  InsertionSortMethod(StaticSequence<Key>& sequence, unsigned size, bool trace = false) : SortMethod<Key>(sequence, size, trace) {}
  void Sort() override {
    InsertionSort(this->sequence_, this->size_, this->trace_);
  }
};


/**
 * @brief Sub-class for shake sort method
 */
template <typename Key> class ShakeSortMethod : public SortMethod<Key> {
 public:
  ShakeSortMethod(StaticSequence<Key>& sequence, unsigned size, bool trace = false) : SortMethod<Key>(sequence, size, trace) {}
  void Sort() override {
    ShakeSort(this->sequence_, this->size_, this->trace_);
  }
};


/**
 * @brief Sub-class for quick sort method
 */
template <typename Key> class QuickSortMethod : public SortMethod<Key> {
 public:
  QuickSortMethod(StaticSequence<Key>& sequence, unsigned size, bool trace = false) : SortMethod<Key>(sequence, size, trace) {}
  void Sort() override {
    QuickSort(this->sequence_, this->size_, this->trace_);
  }
};


/**
 * @brief Sub-class for heap sort method
 */
template <typename Key> class HeapSortMethod : public SortMethod<Key> {
 public:
  HeapSortMethod(StaticSequence<Key>& sequence, unsigned size, bool trace = false) : SortMethod<Key>(sequence, size, trace) {}
  void Sort() override {
    HeapSort(this->sequence_, this->size_, this->trace_);
  }
};


/**
 * @brief Sub-class for shell sort method
 */
template <typename Key> class ShellSortMethod : public SortMethod<Key> {
 private:
  double alpha_;
 public:
  ShellSortMethod(StaticSequence<Key>& sequence, unsigned size, double alpha, bool trace = false) : SortMethod<Key>(sequence, size, trace), alpha_(alpha) {}
  void Sort() override {
    ShellSort(this->sequence_, this->size_, alpha_, this->trace_);
  }
};


#endif