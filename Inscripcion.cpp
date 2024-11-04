#include "Inscripcion.h"
#include <iostream>

Inscripcion::Inscripcion() {}

void mensaje(){
    std::cout << "mensaje de objeto inscripcion." << std::endl; // Mensaje de depuración
}

Candidato Inscripcion::CrearMarca() {
    Candidato candidatos;
    string ced, nomb, apel;
    int votos, idprd;

    ced = "-999999999999";
    nomb = "$$$$$";
    apel = "$$$$$";
    votos = -999999999999;
    idprd = -999999999999;

    candidatos.setCedula(ced);
    candidatos.setNombre(nomb);
    candidatos.setApellido(apel);
    candidatos.setIdPartido(idprd);
    //candidatos.setEstatusInicial();

    return candidatos;
}

bool Inscripcion::verificarDisponibilidad(Candidato cand){
    if (cand.getIdPartido() < 0 || cand.getIdPartido() >= 5) {
        std::cout << "ID de partido no válido." << std::endl;
        return false;
    }
    if (candidatosPorPartido[cand.getIdPartido()] >= 5) {
        std::cout << "El partido ya tiene 5 candidatos inscritos." << std::endl;
        return false;
    }
    if (candidatos.Contar() >= 25) {
        std::cout << "Se alcanzó el máximo de 25 candidatos." << std::endl;
        return false;
    }

    std::cout << "\n Disponibilidad Aprobada" << std::endl; // Mensaje de depuración
    return true;
}

void Inscripcion::RegistrarCandidato(Candidato cand) {

    candidatos.InsertarNodoCola(cand);

    candidatosPorPartido[cand.getIdPartido()]++;
    std::cout << "Candidato inscrito exitosamente en RegistrarCandidato." << std::endl; // Mensaje de depuración
}

void Inscripcion::EliminarCandidato(string cedCandidato) {


    std::cout << "Entrando a EliminarCandidato." << std::endl; // Mensaje de depuración
    // Declara dos objetos de tipo Candidato: candAux y marca

    Candidato candAux, marca;
    // Declara una variable booleana para indicar si se encontró el candidato
    bool encontrado = false;
    // Crea un objeto "marca" que se usará como marcador
    marca = CrearMarca();

// Verifica si la lista de candidatos no está llena
    if (!candidatos.Llena()) {
// Inserta el marcador al final de la lista de candidatos
        candidatos.InsertarNodoCola(marca);
 // Mientras no se haya encontrado el candidato
        while (true){

           // Remueve el último nodo de la lista de candidatos y lo almacena en candAux
            candidatos.RemoverNodoCola(candAux);
          
          // Si el candidato removido es el marcador, se ha llegado al final de la lista

            if (candAux.getCedula() == marca.getCedula()) { break; }

           // Si el candidato removido tiene la cédula que se quiere eliminar
            if (candAux.getCedula() == cedCandidato) {

                    std::cout << "\n\nCandidato eliminado\n\n";
                    encontrado = true;
                    candidatosPorPartido[candAux.getIdPartido()]; // Actualizamos el contador de candidatos por partido
// Si no es el candidato a eliminar, se reinserta en lalista
            } else { candidatos.InsertarNodoCola(candAux); }
        }
      // Si no se encontró el candidato, se imprime un mensaje
        if (!encontrado) { std::cout << "Candidato no encontrado." << std::endl; }
    }
}

void Inscripcion::MostrarCandidatos() {

    nodo<Candidato>* actual = candidatos.ObtPrimero();
    if (!actual) {
        std::cout << "No hay candidatos inscritos en la cola." << std::endl;
        return;
    }

    std::cout << "Candidatos inscritos: \n" << std::endl;
    while (actual) {
        Candidato candidatoActual = candidatos.ObtInfo(actual);
        candidatoActual.mostrarInformacion();
        actual = candidatos.ObtProx(actual);
    }
}
