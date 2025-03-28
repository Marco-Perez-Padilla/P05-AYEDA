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

** Archivo dispersion.h: Declaracion e implementacion de la clase abstracta para trabajar con funciones
**                       de dispersión, así como las sub-clases que representan e implementan dichas funciones.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      22/03/2025 - Creacion (primera version) del codigo
**/

#ifndef DISPERSION_H
#define DISPERSION_H


#include <cstdlib> //rand(), srand()


/**
 * @brief Abstract class that represents the dispersion functions we'll use for the hash table.
 *        It has a virtual operator that will be the specialized functions in each sub-class 
 * @param Key class to be interpreted as a Key for the hashes
 */
template <class Key> class DispersionFunction {
 public:
  virtual unsigned operator() (const Key&) const = 0;
};


/**
 * @brief Sub-class that specializes the module dispersion function
 * @param Key class to be interpreted as a Key for the hashes
 */
template <class Key> class ModuleDispersion : public DispersionFunction<Key> {
 private:
  unsigned table_size_;
 public:
  explicit ModuleDispersion(unsigned table_size) : table_size_(table_size) {}
  unsigned operator()(const Key& key) const override {
    return key % table_size_;
  }
};


/**
 * @brief Sub-class that specializes the sum dispersion function
 * @param Key class to be interpreted as a Key for the hashes
 */
template <class Key> class SumDispersion : public DispersionFunction<Key> {
 private:
  unsigned table_size_;
 public:
  explicit SumDispersion(unsigned table_size) : table_size_(table_size) {}
  unsigned operator()(const Key& key) const override {
    // Convert the string to a number
    long key_number = static_cast<long>(key);
    long sum {0};
    // Sum its digits
    while (key_number > 0) {
      sum += key_number % 10;
      key_number /= 10;
    }
    return sum % table_size_;
  }
};


/**
 * @brief Sub-class that specializes the pseudo-random dispersion function using the key as seed
 * @param Key class to be interpreted as a Key for the hashes
 */
template <class Key> class PseudoRandomDispersion : public DispersionFunction<Key> {
 private:
  unsigned table_size_;
 public:
  explicit PseudoRandomDispersion (unsigned table_size) : table_size_(table_size) {}
  unsigned operator()(const Key& key) const override {
    // Generate the seed
    srand(static_cast<long>(key));  
    // Generate the random number
    return rand() % table_size_;
  }
};


#endif