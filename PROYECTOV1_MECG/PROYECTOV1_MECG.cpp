#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime> 
struct Cancion {
    std::string nombre;
    std::string artista;
    std::string duracion;
};

void eliminarCorchetes(std::string& str) {
    size_t inicio = str.find('{');
    while (inicio != std::string::npos) {
        size_t fin = str.find('}', inicio);
        if (fin != std::string::npos) {
            str.erase(inicio, 1); // Elimina '{'
            str.erase(fin - 1, 1); // Elimina '}'
        }
        inicio = str.find('{', fin);
    }
}

void mostrarMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Leer el documento" << std::endl;
    std::cout << "2. Ordenar el documento" << std::endl;
    std::cout << "3. Guardar el documento" << std::endl;
    std::cout << "4. Reproducir Musica" << std::endl;
    std::cout << "5. Cerrar el programa" << std::endl;
    std::cout << "Seleccione una opcion: ";
}

void mostrarSubMenuOrdenamiento() {
    std::cout << "Submenu de Ordenamiento:" << std::endl;
    std::cout << "1. Ordenar por Nombre" << std::endl;
    std::cout << "2. Ordenar por Artista" << std::endl;
    std::cout << "3. Ordenar por Duracion" << std::endl;
    std::cout << "4. Regresar al Menu Principal" << std::endl;
    std::cout << "Seleccione una opcion: ";
}

int main() {
    std::ifstream archivo;
    std::vector<Cancion> canciones;
    std::string linea;
    int contador = 0;
    bool ordenado = false;
    int opcion;
    int subopcion;
    int cancionSeleccionada = -1;

    do {
        mostrarMenu();
        std::cin >> opcion;

        int cancionSeleccionada = -1;
        bool enReproduccion = false; // Para controlar si hay una cancion en reproduccion
        int cancionActual = -1;      // Para rastrear la cancion actual en reproduccion
        std::srand(static_cast<unsigned int>(std::time(nullptr))); // Inicializar la semilla para numeros aleatorios


        switch (opcion) {
        case 1: {
            // Leer el documento
            canciones.clear();
            contador = 0;
            ordenado = false;
            archivo.close();
            archivo.open("archivo.txt");
            if (!archivo.is_open()) {
                std::cerr << "No se pudo abrir el archivo." << std::endl;
            }
            else {
                while (std::getline(archivo, linea)) {
                    size_t pos1 = linea.find("||");
                    size_t pos2 = linea.find("||", pos1 + 2);

                    if (pos1 != std::string::npos && pos2 != std::string::npos) {
                        std::string nombre = linea.substr(1, pos1 - 1);
                        std::string artista = linea.substr(pos1 + 2, pos2 - (pos1 + 2));
                        std::string duracion = linea.substr(pos2 + 2, linea.length() - 3);

                        eliminarCorchetes(nombre);
                        eliminarCorchetes(artista);
                        eliminarCorchetes(duracion);

                        Cancion cancion;
                        cancion.nombre = nombre;
                        cancion.artista = artista;
                        cancion.duracion = duracion;

                        canciones.push_back(cancion);

                        std::cout << std::to_string(contador + 1) << ". " << nombre << " || " << artista << " || " << duracion << std::endl;
                        contador++;
                    }
                }
            }
            break;
        }
        case 2: {
            // Submenu de ordenamiento
            do {
                mostrarSubMenuOrdenamiento();
                std::cin >> subopcion;
                if (canciones.empty()) {
                    std::cout << "Primero lee el documento antes de ordenarlo." << std::endl;
                }
                else {
                    switch (subopcion) {
                    case 1: {
                        std::sort(canciones.begin(), canciones.end(), [](const Cancion& a, const Cancion& b) {
                            // Ordenar por Nombre
                            return a.nombre < b.nombre;
                            });
                        ordenado = true;
                        std::cout << "Documento ordenado por Nombre:" << std::endl;
                        break;
                    }
                    case 2: {
                        std::sort(canciones.begin(), canciones.end(), [](const Cancion& a, const Cancion& b) {
                            // Ordenar por Artista
                            return a.artista < b.artista;
                            });
                        ordenado = true;
                        std::cout << "Documento ordenado por Artista:" << std::endl;
                        break;
                    }
                    case 3: {
                        bool mostrarListado = true;
                        std::sort(canciones.begin(), canciones.end(), [&mostrarListado](const Cancion& a, const Cancion& b) {
                            // Ordenar por Duracion
                            return a.duracion < b.duracion;
                            });

                        ordenado = true;
                        if (mostrarListado) {
                            std::cout << "Documento ordenado por Duracion:" << std::endl;
                            for (size_t i = 0; i < canciones.size(); ++i) {
                                std::cout << std::to_string(i + 1) << ". " << canciones[i].nombre << " || " << canciones[i].artista << " || " << canciones[i].duracion << std::endl;
                            }
                        }
                        break;
                    }
                    case 4: {
                        std::cout << "Regresando al Menu Principal." << std::endl;
                        break;
                    }
                    default: {
                        std::cerr << "Opcion no valida en el submenu de ordenamiento." << std::endl;
                    }
                    }

                    if (subopcion != 4) {
                        for (size_t i = 0; i < canciones.size(); ++i) {
                            std::cout << std::to_string(i + 1) << ". " << canciones[i].nombre << " || " << canciones[i].artista << " || " << canciones[i].duracion << std::endl;
                        }
                    }
                }
            } while (subopcion != 4);
            break;
        }
        case 3: {
            if (canciones.empty()) {
                std::cout << "No hay canciones para guardar." << std::endl;
            }
            else {
                std::ofstream archivoSalida("C:/Users/migue/OneDrive/Desktop/Proyecto 1/archivo_ordenado.txt");
                if (!archivoSalida.is_open()) {
                    std::cerr << "No se pudo abrir el archivo de salida." << std::endl;
                }
                else {
                    for (const Cancion& cancion : canciones) {
                        archivoSalida << "{" << cancion.nombre << "||" << cancion.artista << "||" << cancion.duracion << "}" << "\n";
                    }
                    archivoSalida.close();
                    std::cout << "Documento guardado como 'archivo_ordenado.txt'." << std::endl;
                }
            }
            break;
        }
        case 4: { // Reproducir Musica
            if (canciones.empty()) {
                std::cout << "Primero lee el documento antes de reproducir musica." << std::endl;
            }
            else {
                int subopcionReproduccion;

                do {
                    // Submenu de Reproduccion
                    std::cout << "Submenu de Reproduccion:" << std::endl;
                    std::cout << "1. Reproducir aleatoriamente" << std::endl;
                    std::cout << "2. Seleccionar cancion" << std::endl;
                    std::cout << "3. Siguiente cancion" << std::endl;
                    std::cout << "4. Cancion anterior" << std::endl;
                    std::cout << "5. Pausa" << std::endl;
                    std::cout << "6. Regresar al Menu Principal" << std::endl;
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> subopcionReproduccion;

                    switch (subopcionReproduccion) {
                    case 1: // Reproducir aleatoriamente
                        if (canciones.size() > 0) {
                            int aleatorio = std::rand() % canciones.size(); // Generar un indice aleatorio
                            cancionActual = aleatorio;
                            std::cout << "Reproduciendo aleatoriamente: " << canciones[cancionActual].nombre << " || " << canciones[cancionActual].artista << " || " << canciones[cancionActual].duracion << std::endl;
                            enReproduccion = true;
                        }
                        else {
                            std::cout << "No hay canciones para reproducir." << std::endl;
                        }
                        break;

                    case 2: // Seleccionar cancion
                        if (canciones.size() > 0) {
                            std::cout << "Seleccione una cancion para reproducir (ingrese el numero): ";
                            std::cin >> cancionSeleccionada;
                            if (cancionSeleccionada >= 0 && cancionSeleccionada < static_cast<int>(canciones.size())) {
                                cancionActual = cancionSeleccionada;
                                std::cout << "Reproduciendo: " << canciones[cancionActual].nombre << " || " << canciones[cancionActual].artista << " || " << canciones[cancionActual].duracion << std::endl;
                                enReproduccion = true;
                            }
                            else {
                                std::cerr << "Seleccion de cancion no valida." << std::endl;
                            }
                        }
                        else {
                            std::cout << "No hay canciones para reproducir." << std::endl;
                        }
                        break;

                    case 3: // Siguiente cancion
                        if (enReproduccion && cancionActual < static_cast<int>(canciones.size()) - 1) {
                            cancionActual++;
                            std::cout << "Reproduciendo siguiente cancion: " << canciones[cancionActual].nombre << " || " << canciones[cancionActual].artista << " || " << canciones[cancionActual].duracion << std::endl;
                        }
                        else {
                            std::cout << "No se puede reproducir la siguiente cancion." << std::endl;
                        }
                        break;

                    case 4: // Cancion anterior
                        if (enReproduccion && cancionActual > 0) {
                            cancionActual--;
                            std::cout << "Reproduciendo cancion anterior: " << canciones[cancionActual].nombre << " || " << canciones[cancionActual].artista << " || " << canciones[cancionActual].duracion << std::endl;
                        }
                        else {
                            std::cout << "No se puede reproducir la cancion anterior." << std::endl;
                        }
                        break;

                    case 5: // Pausa
                        if (enReproduccion) {
                            std::cout << "Pausando: " << canciones[cancionActual].nombre << " || " << canciones[cancionActual].artista << " || " << canciones[cancionActual].duracion << std::endl;
                            enReproduccion = false;
                        }
                        else {
                            std::cout << "No hay canciones en reproduccion." << std::endl;
                        }
                        break;

                    case 6: // Regresar al Menu Principal
                        std::cout << "Regresando al Menu Principal." << std::endl;
                        break;

                    default:
                        std::cerr << "Opcion no valida en el submenu de reproduccion." << std::endl;
                    }
                } while (subopcionReproduccion != 6);
            }
            break;
        }

        case 5: {
            std::cout << "Cerrando el programa." << std::endl;
            break;
        }
        default: {
            std::cerr << "Opcion no valida." << std::endl;
        }
        }
    } while (opcion != 6);

    archivo.close();

    return 0;
}
