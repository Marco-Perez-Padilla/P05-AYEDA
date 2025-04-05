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

#ifndef SEQUENCE_H
#define SEQUENCE_H


#include <list>
#include <algorithm> // find()

#include "exceptions.h"

/**
 * @brief Abstract class that represents the kind of dispersion technics (open or close) we'll use.
 *        It has a virtual operator that will be the specialized functions in each sub-class 
 * @param Key class to be interpreted as a Key for the hashes
 */
template <class Key> class Sequence {
 public:
  virtual ~Sequence() {}
  virtual bool search(const Key&) const = 0;
  virtual bool insert(const Key&) = 0;
  virtual Key operator[](const unsigned int) const = 0;
};
 

/**
 * @brief Sub-class that specializes the dynamic sequence in a hash table
 * @param Key class to be interpreted as a Key for the hashes
 */
template<class Key> class DynamicSequence : public Sequence<Key> {
 private:
  std::list<Key> values_;
 public:
  // Search and insert methods
  bool search(const Key&) const override;
  bool insert(const Key&) override;
  // [] overload 
  Key operator[](const unsigned int) const override;
};


/**
 * @brief Search method to search an element in the linked list with the data
 * @param Key type, element to be searched
 * @return true if the element has been found, false otherwise
 */
template<class Key> bool DynamicSequence<Key>::search(const Key& key) const {
  if (key.isEmpty()) {
    return false;
  }
  return std::find(values_.begin(), values_.end(), key) != values_.end();
}


/**
 * @brief Insert method to insert an element in the  linked list with the data
 * @param Key type, element to be inserted
 * @return true if the element can be inserted (if it wasn't previously on the sequence), false otherwise
 */
template<class Key> bool DynamicSequence<Key>::insert(const Key& key) {
  if (key.isEmpty()) {
    return false;
  }
  if (!search(key)) {
    values_.push_back(key);
    return true;
  } else {
    return false;
  }
}


/**
 * @brief Overload of [] operator to access an element on the sequence
 * @param Position of the element to be acceded
 * @return Key element at the given position
 */
template <class Key> Key DynamicSequence<Key>::operator[](const unsigned int position) const {
  if (position >= values_.size()) {
    throw WrongPosition();
  }
  auto it = values_.begin();
  std::advance(it, position);
  return *it;
}


/**
 * @brief Sub-class that specializes the static sequence in a hash table
 * @param Key class to be interpreted as a Key for the hashes
 */
template <class Key> class StaticSequence : public Sequence<Key> {
 private:
  Key* values_;
  unsigned block_size_;
  unsigned size_;
 public:
  // Constructor
  explicit StaticSequence(unsigned);
  // Destructor
  ~StaticSequence();
  // Getter
  const unsigned getSize() {return size_;}
  // full method
  virtual bool isFull() const;
  // Search and insert methods
  bool search(const Key&) const override;
  bool insert(const Key&) override;
  // [] overload 
  Key operator[](const unsigned int) const override;
  Key& operator[](const unsigned int);
};


/**
 * @brief constructor for the static sequence
 */
template<class Key> StaticSequence<Key>::StaticSequence(unsigned block_size) : block_size_(block_size), size_(0) {
  if (block_size_ == 0) {
    throw BlockSizeZeroException();
  }
  values_ = new Key[block_size_];
  for (unsigned i {0}; i < block_size_; ++i) {
    values_[i] = Key(-1);
  }
}


/**
 * @brief Default destructor for the static sequence
 */
template<class Key> StaticSequence<Key>::~StaticSequence() {
  delete[] values_;
}


/**
 * @brief Method that checks id a sequence is full or not
 * @return true if it's full. False otherwise
 */
template<class Key> bool StaticSequence<Key>::isFull() const {
  return size_ >= block_size_;
}


/**
 * @brief Search method to search an element in the array with the data
 * @param Key type, element to be searched
 * @return true if the element has been found, false otherwise
 */
template<class Key> bool StaticSequence<Key>::search(const Key& key) const {
  if (key.isEmpty()) {
    return false;
  }
  return std::find(values_, values_ + size_, key) != values_ + size_;
}


/**
 * @brief Insert method to insert an element in the array with the data
 * @param Key type, element to be inserted
 * @return true if the element can be inserted (if it wasn't previously on the sequence nor the table is full), false otherwise
 */
template <class Key> bool StaticSequence<Key>::insert(const Key& key) {
  if (key.isEmpty()) {
    return false;
  }
  if (isFull() || search(key)) {
    return false;
  } else {
    values_[size_] = key;
    ++size_;
    return true;
  }
}


/**
 * @brief Overload of [] operator to access an element on the sequence
 * @param Position of the element to be acceded
 * @return Key element at the given position
 */
template <class Key> Key StaticSequence<Key>::operator[](const unsigned int position) const {
  if (position >= block_size_) {
    throw WrongPosition();
  }
  return values_[position];
}


template <class Key> Key& StaticSequence<Key>::operator[](const unsigned int position) {
  if (position >= block_size_) {
    throw WrongPosition();
  }
  return values_[position];
}


#endif