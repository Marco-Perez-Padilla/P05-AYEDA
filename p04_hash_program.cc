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

** Archivo p04_hash_program.cc: programa cliente.
**      Contiene la funcion main del proyecto que usa las templates para crear una tabla hash, y hacer busquedas e inserciones en la misma
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      22/03/2025 - Creacion (primera version) del codigo
**      23/03/2025 - Primera version funcional. Instanciacion de las plantillas
**      23/03/2025 - Creacion del menu
**      24/03/2025 - Adicion manejo de errores
**/

#include <iostream>

#include "check_functions.h"
#include "nif.h"
#include "hash.h"
#include "dispersion.h"
#include "exploration.h"


int main(int argc, char* argv[]) {

  auto options = parse_args(argc,argv);

  bool errors = ProcessArgsErrors(options);
  if (errors == 0) {
    exit(EXIT_FAILURE);
  }

  if (options.value().show_help) {
    Help(); 
    return 0;
  }

  // Getting the values given by the user in command line
  const unsigned table_size = options.value().table_size;
  const unsigned block_size = options.value().block_size;
  const unsigned fd_option = options.value().dispersion_function;
  const unsigned fe_option = options.value().exploration_function;
  const unsigned close_option = options.value().open_close_hash;
  
  // Process Dispersion Function
  DispersionFunction<NIF>* fd = nullptr;
  if (fd_option == 0) {
    fd = new ModuleDispersion<NIF>(table_size);
  } else if (fd_option == 1) {
    fd = new SumDispersion<NIF>(table_size);
  } else if (fd_option == 2) {
    fd = new PseudoRandomDispersion<NIF>(table_size);
  }

  // If closed
  if (close_option == 0) {
    // Process Exploration Function
    ExplorationFunction<NIF>* fe = nullptr;
    if (fe_option == 0) {
      fe = new LinearExploration<NIF>();
    } else if (fe_option == 1) {
      fe = new QuadraticExploration<NIF>();
    } else if (fe_option == 2) {
      fe = new DoubleDispersionExploration<NIF>(*fd);
    } else if (fe_option == 3) {
      fe = new RedispersionExploration<NIF>(table_size);
    }
    HashTable<NIF, StaticSequence<NIF>> closed_table(table_size, *fd, *fe, block_size);
    char option;
    
    std::cout << "Welcome to the menu. Here you can insert or search a NIF in the specified hash table" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    pressanykey();
      
    long inserted_nif;

    do {
      clrscr();
      NIF random_nif;
      menu(option);
      switch (option) {
        case 'i':
          std::cout << "Insert NIF: ";
          std::cin >> inserted_nif;
          if (inserted_nif < 0) {
            closed_table.insert(random_nif);
            std::cout << "Inserted NIF wasn't valid. Introducing random NIF: " << random_nif << std::endl;
          } else {
            try {
              closed_table.insert(NIF(inserted_nif));
              std::cout << "NIF " << inserted_nif << " succesfully inserted" << std::endl;
            } catch(const NifLongException& error) {
              std::cerr << error.what() << std::endl;
            } catch(const ClosedInsertException& error) {
              std::cerr << error.what() << std::endl;
            }
          }
          std::cout << "Press any key to continue..." << std::endl;
          pressanykey();
        break;
          
        case 's':
          std::cout << "Search NIF: ";
          std::cin >> inserted_nif;
          if (inserted_nif < 0) {
            std::cout << "NIF " << inserted_nif << " not valid" << std::endl; 
          } else {
            if(closed_table.search(NIF(inserted_nif))) {
              std::cout << "NIF " << inserted_nif << " found" << std::endl; 
            } else {
              std::cout << "NIF " << inserted_nif << " not found" << std::endl; 
            }
          }
          std::cout << "Press any key to continue..." << std::endl;
          pressanykey();
        break;
      }
    } while (option != 'q');
  } else { // If opened
    HashTable<NIF, DynamicSequence<NIF>> open_table(table_size, *fd);

    char option;
    std::cout << "Welcome to the menu. Here you can insert or search a NIF in the specified hash table" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    pressanykey();
    clrscr();
  
    long inserted_nif;

    do {
      clrscr();
      NIF random_nif;
      menu(option);
      switch (option) {
        case 'i':
          std::cout << "Insert NIF: ";
          std::cin >> inserted_nif;
          if (inserted_nif < 0) {
            try {
              open_table.insert(random_nif);
              std::cout << "Inserted NIF wasn't valid. Introducing random NIF: " << random_nif << std::endl;
            } catch (const NifLongException& error) {
              std::cerr << error.what() << std::endl;
            }
          } else {
            open_table.insert(NIF(inserted_nif));
            std::cout << "NIF " << inserted_nif << " succesfully inserted" << std::endl;
          }
          std::cout << "Press any key to continue..." << std::endl;
          pressanykey();
        break;
        
        case 's':
          std::cout << "Search NIF: ";
          std::cin >> inserted_nif;
          if (inserted_nif < 0) {
            std::cout << "NIF " << inserted_nif << " not valid" << std::endl; 
          } else {
            if(open_table.search(NIF(inserted_nif))) {
              std::cout << "NIF " << inserted_nif << " found" << std::endl; 
            } else {
              std::cout << "NIF " << inserted_nif << " not found" << std::endl; 
            }
          }
          std::cout << "Press any key to continue..." << std::endl;
          pressanykey();
        break;
      }
    } while (option != 'q');
  }

  return 0;
}