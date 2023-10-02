#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cctype>
#include <thread>
#include <chrono>

//Metodos generales
void esperar(int segundos){
	std::this_thread::sleep_for(std::chrono::seconds(segundos));
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
	
	// Reccorrer los pacientes del 0 1 10
	for(int numPaciente=0; numPaciente<=10;numPaciente++){
		
		// Por cada iteracion del for (pacientes) tendra un tiempoAtencion de 5 tiempos inicializado en 0 y aumenta cada segundo con metodo esperar(1)
		while(tiempoAtencion <= 5){
			system("cls");
			printf("TIEMPO ATENCION ACTUAL: %d\n", tiempoAtencion);
			printf("Atentiendo paciente numero %d\n", numPaciente);
			esperar(1);
			
			
			// _kbhit() permite saber si se tecleo sin interrumpir el proceso
			if(_kbhit()){
				interrupcionUsuario = _getch();
				interrupcionUsuario = toupper(interrupcionUsuario);
				
				// romper el bucle while de ese paciente
				if(interrupcionUsuario == 'I'){
					system("cls");
					printf("INTERRUPCION POR USUARIO\n");
					printf("Interrupcion generada atendiendo al paciente numero %d\n", numPaciente);
					esperar(2);
					salirProceso = true;
					break;
				}
			}
			
			tiempoAtencion++;
			
		}
		
		// romper el for de los demas pacientes si uno de estos presiono la tecla I
		if(salirProceso){
			break;
		}
		
		
		// Si no se presiono la tecla I y llega los 15 tiempos entonces su proceso se realizo con exito	
		if(tiempoAtencion == 5){
			system("cls");
			printf("INTERRUPCION NORMAL\n");
			printf("Se atendio con exito al paciente numero %d\n", numPaciente);
			esperar(3);
		}	
		
		
		totalPacientesAtenididos = numPaciente;
		
		// Reiniciar el tiempo para los demas pacientes si para el anterior no existio una interrupcion
		tiempoAtencion = 0;
	}
	
	
	// Si no exisitio ninguna interrupcion durante el for entonces se atendio a todos con exito
	if(totalPacientesAtenididos == 10){
		system("cls");
		printf("INTERRUPCION NORMAL\n");
		printf("Todos los pacientes fueron atentidos con exito!");
		esperar(3);
	}	
}


void procesoEmergencias(){
	system("cls");
	printf("2-Proceso atencion de emergencias\n");
	esperar(1);
}


void procesoCirujias(){
	system("cls");
	printf("3-Proceso atencion de cirugias\n");
	esperar(1);
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
		printf("E-Finalizar proceso\n");
		
		procesoSeleccionado = _getch();
		procesoSeleccionado = toupper(procesoSeleccionado);
		
		
		if (procesoSeleccionado == 'E') {
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
	return 0;
	
}