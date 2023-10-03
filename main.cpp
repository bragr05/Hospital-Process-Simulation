#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cctype>
#include <thread>
#include <chrono>
#include <queue>

using namespace std;

// Metodos generales
void esperar(int segundos){
	std::this_thread::sleep_for(std::chrono::seconds(segundos));
}

void limpiarBufferTeclas(){
	while (_kbhit()) {
        _getch();
    }
}



// Metodos procesos
void procesoCitas(){
	system("cls");
	printf("1-Proceso atencion de cita seleccionado \n");
	esperar(1);
	
	int totalPacientesAtenididos = 0;
	int tiempoAtencion = 0;
	char interrupcionUsuario;
	bool salirProceso = false;
	
	for(int numPaciente=0; numPaciente<=10;numPaciente++){
		
		while(tiempoAtencion <= 5){	
			

			if(_kbhit()){
				interrupcionUsuario = _getch();
				interrupcionUsuario = toupper(interrupcionUsuario);
				
				if(interrupcionUsuario == 'I'){
					system("cls");
					printf("INTERRUPCION POR USUARIO\n");
					printf("TIEMPO ATENCION PACIENTE: %d\n", tiempoAtencion);
					printf("Interrupcion generada atendiendo al paciente numero %d\n", numPaciente);
					system("pause");
					salirProceso = true;
					break;
				}
			
			}
			
			system("cls");
			printf("TIEMPO ATENCION ACTUAL: %d\n", tiempoAtencion);
			printf("Atentiendo paciente numero %d\n\n", numPaciente);
			printf("Presione tecla I para terminar el proceso\n");
			
			tiempoAtencion++;
			esperar(1);
		}
		
		if(salirProceso){
			break;
		}
		
		
		if(tiempoAtencion >= 5){
			system("cls");
			printf("INTERRUPCION NORMAL\n");
			printf("Se atendio con exito al paciente numero %d\n", numPaciente);
			esperar(2);
		}	
		
		
		totalPacientesAtenididos = numPaciente;
		
		// Reiniciar tiempo para otros pacientes
		tiempoAtencion = 0;
	}
	
	
	if(totalPacientesAtenididos == 10){
		system("cls");
		printf("INTERRUPCION NORMAL\n");
		printf("Todos los pacientes fueron atentidos con exito!");
		system("pause");
	}	
}


void procesoEmergencias() {
    system("cls");
    printf("2-Proceso atencion de emergencias\n");
    esperar(1);

    int totalPacientesAtendidos = 0;
    int tiempoProceso = 0;
    char interrupcionUsuario;
    int numPaciente = 0;

    while (tiempoProceso <= 25 && totalPacientesAtendidos < 10) {

        if (_kbhit()) {
            interrupcionUsuario = _getch();
            interrupcionUsuario = toupper(interrupcionUsuario);

            if (interrupcionUsuario == 'S' && tiempoProceso >= 20) {
                system("cls");
                printf("INTERRUPCION POR USUARIO\n");
                printf("TIEMPO PROCESO: %d\n", tiempoProceso);
                printf("Interrupcion generada atendiendo al paciente numero %d\n", numPaciente);
                esperar(4);
                break;
            }else if(interrupcionUsuario == 'P'){
            	numPaciente++;
            	totalPacientesAtendidos = numPaciente;
			}
        }
        
        system("cls");
        printf("TIEMPO ATENCION ACTUAL: %d\n", tiempoProceso);
        printf("Atendiendo paciente numero %d\n\n", numPaciente);
        
        printf("Presione tecla P para avanzar paciente\n");
        printf("A los 20 tiempos puede finalizar el proceso con la tecla S\n");
        
        limpiarBufferTeclas();
        
		esperar(1);
        tiempoProceso++;
    }
    
    system("cls");
    printf("INTERRUPCION NORMAL\n");
    printf("TIEMPO TOTAL PROCESO: %d\n", tiempoProceso - 1);
	printf("PACIENTES TOTALES ATENDIDOS: %d\n", totalPacientesAtendidos);
	system("pause");
}




// Estructura de datos para representar un paciente dentro de la cola Proceso III
struct Pacientes{
	int numeroPaciente;
	int tiempoAtencion;
	string TipoAtencion;
};

void procesoCirujias(){
	system("cls");
	printf("3-Proceso atencion de cirugias\n");
	esperar(1);
	
	int quantum = 5;
	
	
	queue<Pacientes> colaCirujias;
	
	colaCirujias.push({1, 7, "Rojo"});
	colaCirujias.push({2, 8, "Normal"});
	colaCirujias.push({3, 5, "Normal"});
	colaCirujias.push({4, 11, "Rojo"});
	colaCirujias.push({5, 9, "Verde"});
	colaCirujias.push({6, 3, "Normal"});
	
	
	int tiempoRestantePacienteActual;
	int tiempoTotalAtencionPaciente;
	
	while (!colaCirujias.empty()) 
	{
	    Pacientes pacienteActual = colaCirujias.front();
	    
	    // Elimianr el pacienteActual temporalmente
	    colaCirujias.pop();
	    
	    
	    
	    if (pacienteActual.TipoAtencion == "Rojo" || pacienteActual.TipoAtencion == "Verde"){
	    	
	    	
		}else{
			
			int tiempoSobrante;
			
			// Validar casos donde paciente tiempoAtencion es menor / mayor que el quantum (5)
			if(pacienteActual.tiempoAtencion >= quantum){
				// Ejem: 8 - 5 = 3 de tiempo sobrante;
				tiempoSobrante = pacienteActual.tiempoAtencion - quantum;
				tiempoRestantePacienteActual = quantum;
				tiempoTotalAtencionPaciente = quantum;
			}else{
				// Ejem: 5 - 3 = 2 de tiempo sobrante;
				tiempoSobrante = quantum - pacienteActual.tiempoAtencion;
				tiempoRestantePacienteActual = pacienteActual.tiempoAtencion;
				tiempoTotalAtencionPaciente = pacienteActual.tiempoAtencion;;
			}		

			while(tiempoRestantePacienteActual >= 0){		
				system("cls");
				printf("ATENDIENDO PACIENTE NUMERO: %d\n", pacienteActual.numeroPaciente);
				printf("PACIENTE TIPO: %s\n\n", pacienteActual.TipoAtencion.c_str());
				printf("TIEMPO TOTAL PARA SER ATENDIDO: %d\n", tiempoTotalAtencionPaciente);
				printf("TIEMPO RESTANTE: %d\n", tiempoRestantePacienteActual);
				
				
				esperar(1);
				tiempoRestantePacienteActual-=1;
			}
			
			// Como es normal no se agrega de nuevo a la Queue porque no necesita de su tiempo restante
			system("cls");
			printf("INTERRUPCION NORMAL\n");
			printf("PACIENTE NUMERO %d ATENDIDO CORRECTAMENTE\n", pacienteActual.numeroPaciente);
			printf("TIEMPO SOBRANTE: %d \n\n", tiempoSobrante);
			printf("Nota: Por ser paciente normal no necesitara su tiempo sobrante\n");
			esperar(5);

		}

		tiempoRestantePacienteActual=0;
		
	}

}


int main(){
	int contadorBucle = 0;
	char procesoSeleccionado;
	
	while(true){
		system("cls");
		
		printf("MENU PRINCIPAL DE PROCESOS\n");
		printf("1-Proceso atencion de citas\n");
		printf("2-Proceso atencion de emergencias\n");
		printf("3-Proceso atencion de cirugias\n");
		printf("A-Finalizar proceso\n");
		
		procesoSeleccionado = _getch();
		procesoSeleccionado = toupper(procesoSeleccionado);
		
		
		if (procesoSeleccionado == 'A') {
			
            break; 
        }
		
		
		switch(procesoSeleccionado){
			case '1':
				procesoCitas();
				break;
			case '2': 
				procesoEmergencias();
				break;
			case '3':
				procesoCirujias();
				break;
			default:
				system("cls");
            	printf("Proceso seleccionado invalido!\n");
            	esperar(1);
				
		}
		
		contadorBucle++;
	};
	
	printf("Procesos Finalizados\n");
	return 0;
	
}