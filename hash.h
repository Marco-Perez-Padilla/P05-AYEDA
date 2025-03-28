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

** Archivo hash.h: Declaracion e implementacion de la Hash Table mediante el uso de funciones de
**                 exploracion, secuencias y dispersion. Manejo de colisiones
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      22/03/2025 - Creacion (primera version) del codigo
**      23/03/2025 - Adicion de DynamicSequence specialization
**/

#ifndef HASH_H
#define HASH_H

#include "exceptions.h"
#include "dispersion.h"
#include "exploration.h"
#include "sequence.h"

/**
 * @brief HashTable class that
 * @param Key class to be interpreted as a Key for the hash table
 * @param Container static or dynamic in which the data will be allocated in
 */
template <class Key, class Container = StaticSequence<Key>> class HashTable {
 private:
  unsigned table_size_; // Size of the table
  Container** table_; // Array of arrays (pointer of pointers)
  DispersionFunction<Key>& fd_; // Dispersion function to be used
  ExplorationFunction<Key>& fe_; // Exploration function to be used
  unsigned block_size_; // Size of each block
 public:
  // Constructor
  HashTable(unsigned, DispersionFunction<Key>&, ExplorationFunction<Key>&, unsigned);
  //Destructor
  virtual ~HashTable();
  // Search and insert methods
  bool search(const Key&) const;
  bool insert(const Key&);
};


/**
 * @brief Constructor for the HashTable. Creates the table
 * @param unsigned maximum size of the table
 * @param DispersionFunction& to be used
 * @param ExplorationFunction& to be used
 * @param unsigned maximum size of each container
 */
template<class Key, class Container> HashTable<Key, Container>::HashTable(unsigned table_size, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe, unsigned block_size) : table_size_(table_size), fd_(fd), fe_(fe), block_size_(block_size) {
  // Assign the memory to the table
  table_ = new Container*[table_size_];
  // Create a container for each position
  for (unsigned i {0}; i < table_size_; ++i) {
    table_[i] = new Container(block_size_);
  }
}


/**
 * @brief Default destructor for HashTable class
 */
template<class Key, class Container> HashTable<Key, Container>::~HashTable() {
  for (unsigned i {0}; i < table_size_; ++i) {
    delete table_[i];
  }
  delete[] table_;
}


/**
 * @brief search method for close hashing. It defines the search depending on the fe
 * @param Key object to be searched
 */
template<class Key, class Container> bool HashTable<Key, Container>::search(const Key& key) const {
  unsigned i = fd_(key);
  unsigned counter {0};
  // Search it with the current hash given by fd
  do {
    if (table_[i]->search(key)) {
      return true; // True if found
    } else if (!table_[i]->isFull()) {
      return false; // False if it's full
    }
    // Next step
    i = fe_(key, counter) % table_size_;
    ++counter;
  } while (counter < table_size_); // Repeat until the counter is greater or equal than table_size_

  return false;
}


/**
 * @brief insert method for close hashing. It defines the insertion depending on the fe
 * @param Key object to be inserted
 */
template<class Key, class Container> bool HashTable<Key, Container>::insert(const Key& key) {
  unsigned i = fd_(key);
  unsigned counter {0};
  do {
    // Try to insert it with the current hash. If succeed, return true
    if (table_[i]->insert(key)) {
      return true;
    } else { // Otherwise recalculate with fe
      i = fe_(key, counter) % table_size_;
      ++counter;
    }
  } while (counter < table_size_); // Repeat until counter is greater or equal than table_size_

  throw ClosedInsertException(); // Throw an exception if it wasn't possible to insert it
}


/**
 * @brief HashTable class specialization for open hashing with dynamic sequence
 * @param Key class to be interpreted as a Key for the hash table
 */
template <class Key> class HashTable<Key, DynamicSequence<Key>> {
 private:
  unsigned table_size_;
  DynamicSequence<Key>* table_;
  DispersionFunction<Key>& fd_;
 public:
  // Constructor
  HashTable(unsigned, DispersionFunction<Key>&);
  //Destructor
  ~HashTable();
  // Search and insert methods
  bool search(const Key&) const;
  bool insert(const Key&);
};


/**
 * @brief Constructor for the HashTable. Creates the table
 * @param unsigned maximum size of the table
 * @param DispersionFunction& to be used
 * @param ExplorationFunction& to be used
 * @param unsigned maximum size of each container
 */
template<class Key> HashTable<Key, DynamicSequence<Key>>::HashTable(unsigned table_size, DispersionFunction<Key>& fd) : table_size_(table_size), fd_(fd) {
  // Assign the memory to the table
  table_ = new DynamicSequence<Key>[table_size_];
}


/**
 * @brief Default destructor for HashTable class
 */
template<class Key> HashTable<Key, DynamicSequence<Key>>::~HashTable() {
  delete[] table_;
}


/**
 * @brief search method for open hashing
 * @param Key object to be searched
 */
template<class Key> bool HashTable<Key, DynamicSequence<Key>>::search(const Key& key) const {
  unsigned i = fd_(key) % table_size_;
  return table_[i].search(key);
}


/**
 * @brief insert method for close hashing
 * @param Key object to be inserted
 */
template<class Key> bool HashTable<Key, DynamicSequence<Key>>::insert(const Key& key) {
  unsigned i = fd_(key) % table_size_;
  return table_[i].insert(key);
}


#endif