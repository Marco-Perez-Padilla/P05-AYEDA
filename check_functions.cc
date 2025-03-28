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

** Archivo check_functions.cc: Implementación de las funciones de chequeo de parámetros.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      22/03/2025 - Creacion (primera version) del codigo
**      23/03/2025 - Adicion funcion para manejar opciones del comando
**      24/03/2025 - Adicion funcion para manejar errores del comando
**      27/03/2025 - Adicion de errores relacionados con metodos de ordenacion
**      28/03/2025 - Adicion de mensajes de error para errores de argumentos nuevos
**      28/03/2025 - Adicion de menu para la funcion de ordenacion ShellSort
**/

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <expected>
#include <string_view>
#include <vector>
#include <limits>

#include "check_functions.h"


// Including libreries for compatibility among operative systems
#ifdef _WIN32
  #include <conio.h>  // _getch() for pressanykey
  #define CLEAR "cls" // Macro for clrscr in Windows
#else
  #define CLEAR "clear" // Macro for clrscr in Linux
#endif


/**
 * @brief Checks if a given string is made out of (only) numbers or not
 * @param string
 * @return bool
 */
bool ValidateNumber (const std::string& line) {
  if (!line.empty()) {
    for (char chr : line) {
      if (!std::isdigit(chr)) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}


/**
 * @brief Prints Help to the user
 */
void Help () {
    std::cout << "./p05_hash_program [--help | -h] [-ts <s>] [-fd <f>] [-hash <open|close>] [-bs <s] [-fe <f>] [-size <s>] [-ord <m>] [-init <i> [f]] [-trace <y|n>] -- //FILL LATER\n"
              << "Usage:                ./p04_hash_program [--help | -h] [-ts <s>] [-fd <f>] [-hash <open|close>] [-bs <s] [-fe <f>] [-size <s>] [-ord <m>] [-init <i> [f]] [-trace <y|n>]\n"
              << "    [--help | -h]:       Optional argument. Prints this help\n"
              << "    [-ts <s>]:           Optional argument. Initializes a hash table with the size specified by <s>, positive number greater than 0. Default table size is 1000\n"
              << "    [-fd <f>]:           Optional argument: Specifies with <f> the distribution function to be used in the hash table (module function as default). Its codes are as follows:\n"
              << "                              - 0: Module function\n"
              << "                              - 1: Sum function\n"
              << "                              - 2: Pseudo-random function\n"
              << "    [-hash <open|close>] Optional argument: If used with <open>, hash table with use dynamic sequence. If <close> specified, static sequence (hash table will use static sequence by default as well) \n"
              << "    [-bs <s>]:           Optional argument. Initializes the blocks of the hash table with the size specified by <s>, positive number greater than 0. Default block size is 1\n"
              << "    [-fe <f>]:           Optional argument: Specifies with <f> the exploration function to be used in the hash table (linear exploration as default) in a close table hash. Its codes are as follows:\n"
              << "                              - 0: Linear exploration\n"
              << "                              - 1: Quadratic exploration\n"
              << "                              - 2: Double Dispersion\n"
              << "                              - 3: Redispersion\n"
              << "    [-size <s>]:         Optional argument: Initializes the size of the sequence to be sorted (10 as default) with the size specified by <s>, natural number greater than zero.\n"
              << "    [-ord <m>]:          Optional argument: Specifies with <m> the sort function to be used in the sequence (insertion method as default) in a close table hash. Its codes are as follows:\n"
              << "                              - 0: Insertion sort method\n"
              << "                              - 1: Shaker sort method\n"
              << "                              - 2: QuickSort method\n"
              << "                              - 3: HeapSort method\n"
              << "                              - 4: ShellSort method. Adds to the menu an option to select alpha between 0 and 1\n"
              << "    [-init <i>]:          Optional argument: Specifies with <i> the way data will be introduced:\n"
              << "                              - manual: Introduces manually the <s> number of elements of the sequence\n"
              << "                              - random: Introduces randomly the <s> number of elements of the sequence\n"
              << "                              - file [f]: Introduces the <s> from a file which name is specified with <f>, mandatory field\n"
              << "    [-trace <y|n>] Optional argument: If used with <y>, the program will print the trace of the selected sort method. If <n>, this funcitonality will be deactivated\n";

}


/**
 * @brief Prints how to use the program
 */
void Usage() {
  std::cout << "How to use: ./p05_hash_program [--help | -h] [-ts <s>] [-fd <f>] [-hash <open|close>] [-bs <s] [-fe <f>] [-size <s>] [-ord <m>] [-init <i> [f]] [-trace <y|n>]\n"
            << "Try './p05_hash_program [--help | -h]' for further information\n";
}


/**
 * @brief Function that processes the arguments given through command line
 * @param argc
 * @param argv
 * @return Program options struct with all the options if no error has occured. Enum parse args error otherwise with the specified error
 */
std::expected<program_options, parse_args_errors> parse_args(int argc, char* argv[]) {
  bool table_size = false;
  bool dispersion_function = false;
  bool open_hash = false;
  bool block_size = false;
  bool exploration_function = false;
  bool sequence_size = false;
  bool ordenation_function = false;
  bool mode = false;
  bool trace = false;
  bool file = false;

  std::vector<std::string_view> args(argv + 1, argv + argc);
  program_options options;

  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    if (*it == "-h" || *it == "--help") {
      options.show_help = true;
    } else if (*it == "-ts") {
      table_size = true;
      continue;
    } else if (*it == "-fd") {
      dispersion_function = true;
      continue;
    } else if (*it == "-hash") {
      open_hash = true;
      continue;
    } else if (*it == "-bs") {
      block_size = true;
      continue;
    } else if (*it == "-fe") {
      exploration_function = true;
      continue;
    } else if (*it == "-size") {
      sequence_size = true;
      continue;
    } else if (*it == "-ord") {
      ordenation_function = true;
      continue;
    } else if (*it == "-init") {
      mode = true;
      continue;
    } else if (*it == "-trace") {
      trace = true;
      continue;
    } else if (table_size == true) {
      table_size = false;
      if (ValidateNumber(std::string(*it)) && std::stoi(std::string(*it)) > 0) {
        options.table_size = std::stoi(std::string(*it));
      } else {
        return std::unexpected(parse_args_errors::table_size_error);
      }
    } else if (dispersion_function == true) {
      dispersion_function = false;
      if (ValidateNumber(std::string(*it))) {
        int disp_func = std::stoi(std::string(*it));
        if (disp_func < 0 || disp_func > 2) {
          return std::unexpected(parse_args_errors::dispersion_function_error);
        } else {
          options.dispersion_function = disp_func;
        }
      } else {
        return std::unexpected(parse_args_errors::dispersion_function_error);
      }
    } else if (exploration_function == true) {
      exploration_function = false;
      if (ValidateNumber(std::string(*it))) {
        int expl_func = std::stoi(std::string(*it));
        if (expl_func < 0 || expl_func > 3) {
          return std::unexpected(parse_args_errors::exploration_function_error);
        } else {
          options.exploration_function = expl_func;
        }
      } else {
        return std::unexpected(parse_args_errors::exploration_function_error);
      }
    } else if (open_hash == true) {
      open_hash = false;
      if (std::string(*it) == "open") {
        options.open_close_hash = 1;
      } else if (std::string(*it) == "close"){
        options.open_close_hash = 0;
      } else {
        return std::unexpected(parse_args_errors::hash_error);
      }
    } else if (block_size == true) {
      block_size = false;
      if (ValidateNumber(std::string(*it)) && std::stoi(std::string(*it)) > 0) {
        options.block_size = std::stoi(std::string(*it));
      } else {
        return std::unexpected(parse_args_errors::block_size_error);
      }
    } else if (sequence_size == true) {
      sequence_size = false;
      if (ValidateNumber(std::string(*it)) && std::stoi(std::string(*it)) > 0) {
        options.sequence_size = std::stoi(std::string(*it));
      } else {
        return std::unexpected(parse_args_errors::sequence_size_error);
      }
    } else if (ordenation_function == true) {
      ordenation_function = false;
      if (ValidateNumber(std::string(*it))) {
        int ord_func = std::stoi(std::string(*it));
        if (ord_func < 0 || ord_func > 4) {
          return std::unexpected(parse_args_errors::ordenation_function_error);
        } else {
          options.ordenation_function = ord_func;
        }
      } else {
        return std::unexpected(parse_args_errors::ordenation_function_error);
      }
    } else if (mode == true) {
      mode = false;
      if (std::string(*it) == "manual") {
        options.mode = 0;
      } else if (std::string(*it) == "random"){
        options.mode = 1;
      } else if (std::string(*it) == "file"){
        options.mode = 2;
        file = true;
        continue;
      } else {
        return std::unexpected(parse_args_errors::mode_error);
      }
    } else if (!it->starts_with("-") && file == true) {
      file = false;
      std::string file_name = std::string(*it);
      if (file_name.empty()) {
        return std::unexpected(parse_args_errors::file_error);
      } else {
        options.file = file_name;
      }
    } else if (trace == true) {
      trace = false;
      if (std::string(*it) == "y") {
        options.open_close_hash = 1;
      } else if (std::string(*it) == "n"){
        options.open_close_hash = 0;
      } else {
        return std::unexpected(parse_args_errors::trace_error);
      }
    } else {
      return std::unexpected(parse_args_errors::unknown_option); 
    }
  }

  if (file == true && options.file.empty()) {
    return std::unexpected(parse_args_errors::missing_argument);
  }

  return options; 
}


/**
 * @brief function that waits for the user to press any key
 */
void pressanykey() {
  #ifdef _WIN32
    _getch(); // Windows
  #else
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Linux
    std::cin.get(); 
  #endif
}


/**
 * @brief function to clear the standard ouput
 */
void clrscr() {
  system(CLEAR);
}


/**
* @brief Start menu to choose an option of the following
* @param char option to be used
*/
void menu (char &opcion) {
 std::cout << "i. [i]nsert new NIF, number with 8 digits" << std::endl;     
 std::cout << "s. [s]earch a specified NIF in the table hash" << std::endl;         
 std::cout << "q. [q]uit program" << std::endl;
 std::cout << "Introduce the action to execute  > ";
 std::cin >> opcion;
};


/**
* @brief Start menu to choose an option of the following
* @param char option to be used
*/
void ShellSortMenu (char &opcion) {
  std::cout << "i. [i]nsert new NIF, number with 8 digits" << std::endl;     
  std::cout << "s. [s]earch a specified NIF in the table hash" << std::endl;
  std::cout << "a. Select [a]lpha value, between 0 and 1" << std::endl;         
  std::cout << "q. [q]uit program" << std::endl;
  std::cout << "Introduce the action to execute  > ";
  std::cin >> opcion;
};


/**
 * @brief Function that processes error messages from std::unexpected
 * @param expected options after command line
 * @return 0 if an error occurred
 */
bool ProcessArgsErrors(const std::expected<program_options, parse_args_errors>& options) {
  if (!options.has_value()) {
    if (options.error() == parse_args_errors::unknown_option) {
      std::cerr << "fatal error: Unknown option" << std::endl;;
    } else if (options.error() == parse_args_errors::table_size_error) {
      std::cerr << "fatal error: Table size, it must be a non negative number superior than 0" << std::endl;
    } else if (options.error() == parse_args_errors::block_size_error) {
      std::cerr << "fatal error: Block size, it must be a non negative number superior than 0" << std::endl;
    } else if (options.error() == parse_args_errors::dispersion_function_error) {
      std::cerr << "fatal error: Dispersion function code must be 0, 1 or 2" << std::endl;
    } else if (options.error() == parse_args_errors::exploration_function_error) {
      std::cerr << "fatal error: Dispersion function code must be 0, 1, 2 or 3" << std::endl;
    } else if (options.error() == parse_args_errors::hash_error) {
      std::cerr << "fatal error: Hash code must be 'open' or 'close'" << std::endl;
    } else if (options.error() == parse_args_errors::sequence_size_error) {
      std::cerr << "fatal error: Sequence size, it must be a non negative number superior than 0" << std::endl;
    } else if (options.error() == parse_args_errors::ordenation_function_error) {
      std::cerr << "fatal error: Ordenation function code must be 0, 1, 2, 3 or 4" << std::endl;
    } else if (options.error() == parse_args_errors::mode_error) {
      std::cerr << "fatal error: Specified insertion mode must be 'manual' or 'random' or 'file'" << std::endl;
    } else if (options.error() == parse_args_errors::file_error) {
      std::cerr << "fatal error: Insertion mode file selected. It must be followed by a file name not empty" << std::endl; 
    } else if (options.error() == parse_args_errors::trace_error) {
      std::cerr << "fatal error: Trace must be specified with 'y' or 'n'" << std::endl;
    } else if (options.error() == parse_args_errors::missing_argument) {
      std::cerr << "fatal error. Missing argument after file insertions mode selected" << std::endl;
    }
    Usage();
    return 0;
  }
  return 1;
}