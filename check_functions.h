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

** Archivo check_functions.h: Declaracion de las funciones de chequeo de parámetros.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      22/03/2025 - Creacion (primera version) del codigo
**      23/03/2025 - Adicion funcion para manejar opciones del comando
**      24/03/2025 - Adicion funcion para manejar errores del comando
**      27/03/2025 - Adicion de errores relacionados con metodos de ordenacion
**/

#include <iostream>
#include <string>
#include <expected>


// Enum of errors in arguments
enum class parse_args_errors {
 missing_argument,
 table_size_error,
 dispersion_function_error,
 exploration_function_error,
 hash_error,
 block_size_error,
 sequence_size_error,
 ordenation_function_error,
 mode_error,
 trace_error,
 file_error,
 unknown_option,
};


// Struct that storages the values given in command line
struct program_options {
 bool show_help = false;
 int table_size = 1000; // table size 1000 as default
 int dispersion_function = 0; // Module function as default
 int exploration_function = 0; // Linear function as default
 int open_close_hash = 0; // close hash (static sequence) as default
 int block_size = 1; // block size 1 as default
 int sequence_size = 10; // sequence size 1 as default
 int ordenation_function = 0; // Insertion method as default
 int mode = 0; // Manual mode as default
 int trace = 0; // No trace as default
 std::string file;
};
 
bool ValidateFile (const std::string& name);
void CheckFileError (const std::string& name);
void ValidateCommand(int argc, char* argv[]);
bool ValidateNumber (const std::string& line);
void Help ();
void Usage();
void pressanykey();
void clrscr();
void menu(char &option);
bool ProcessArgsErrors(const std::expected<program_options, parse_args_errors>& options);
std::expected<program_options, parse_args_errors> parse_args(int argc, char* argv[]);