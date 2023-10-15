#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cctype>
#include <thread>
#include <chrono>
#include <queue>
#include <process.h>

using namespace std;

// Metodos generales
void limpiarBufferTeclas()
{
	while (_kbhit())
	{
		_getch();
	}
}

void esperar(int segundos)
{
	std::this_thread::sleep_for(std::chrono::seconds(segundos));
}

// Metodos procesos
void procesoCitas()
{
	system("cls");
	int totalPacientesAtenididos = 0;
	int tiempoAtencion = 0;
	char interrupcionUsuario;
	bool salirProceso = false;
	int tiempoEjecucionHilo = 0;

	for (int numPaciente = 0; numPaciente <= 10; numPaciente++)
	{

		while (tiempoAtencion <= 5)
		{

			if (_kbhit())
			{
				interrupcionUsuario = _getch();
				interrupcionUsuario = toupper(interrupcionUsuario);

				if (interrupcionUsuario == 'I')
				{
					tiempoAtencion--;
					tiempoEjecucionHilo--;

					system("cls");
					printf("SALIENDO HILO CITAS...\n");
					printf("TIEMPO TOTAL EJECUCION HILO: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

					printf("INTERRUPCION POR USUARIO\n");
					printf("Tiempo usado por el paciente: %d/5\n", tiempoAtencion);
					printf("Interrupcion generada atendiendo al paciente numero %d\n", numPaciente);
					system("pause");
					salirProceso = true;
					break;
				}
			}

			system("cls");
			printf("HILO CITAS EN EJECUCION\n");
			printf("TIEMPO ACTUAL DE EJECUCION: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

			printf("TIEMPO ATENCION ACTUAL: %d\n", tiempoAtencion);
			printf("Atentiendo paciente numero %d\n\n", numPaciente);
			printf("Presione tecla I para terminar el proceso\n");

			esperar(1);
			tiempoAtencion++;
			tiempoEjecucionHilo++;
		}

		if (salirProceso)
		{
			break;
		}

		if (tiempoAtencion >= 5)
		{
			tiempoAtencion--;
			tiempoEjecucionHilo--;

			system("cls");
			printf("HILO CITAS EN EJECUCION\n");
			printf("TIEMPO ACTUAL DE EJECUCION: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

			printf("INTERRUPCION NORMAL\n");
			printf("Se atendio con exito al paciente numero %d\n", numPaciente);
			esperar(5);
		}

		totalPacientesAtenididos = numPaciente;

		// Reiniciar tiempo para otros pacientes
		tiempoAtencion = 0;
	}

	if (totalPacientesAtenididos == 10)
	{
		system("cls");
		printf("SALIENDO HILO CITAS...\n");
		printf("TIEMPO TOTAL EJECUCION HILO: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

		printf("INTERRUPCION NORMAL\n");
		printf("Todos los pacientes fueron atentidos con exito!");
		system("pause");
	}
}

void procesoEmergencias()
{
	int totalPacientesAtendidos = 0;
	int tiempoProceso = 0;
	char interrupcionUsuario;
	int numPaciente = 0;
	int tiempoEjecucionHilo = 0;

	while (tiempoProceso <= 25 && totalPacientesAtendidos < 10)
	{
		system("cls");
		printf("HILO EMERGENCIAS EN EJECUCION\n");
		printf("TIEMPO ACTUAL DE EJECUCION: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

		if (_kbhit())
		{
			interrupcionUsuario = _getch();
			interrupcionUsuario = toupper(interrupcionUsuario);

			if (interrupcionUsuario == 'S' && tiempoProceso >= 20)
			{
				system("cls");
				printf("SALIENDO HILO EMERGENCIAS...\n");
				printf("TIEMPO TOTAL EJECUCION HILO: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

				printf("INTERRUPCION POR USUARIO\n");
				printf("Interrupcion generada atendiendo al paciente numero %d\n", numPaciente);
				esperar(5);
				break;
			}
			else if (interrupcionUsuario == 'P')
			{
				numPaciente++;
				totalPacientesAtendidos = numPaciente;
			}
		}

		printf("Atendiendo paciente numero %d\n\n", numPaciente);

		printf("Presione tecla P para avanzar paciente\n");
		printf("A los 20 tiempos puede finalizar el proceso con la tecla S\n");

		limpiarBufferTeclas();

		esperar(1);
		tiempoProceso++;
		tiempoEjecucionHilo++;
	}

	tiempoEjecucionHilo--;
	system("cls");
	printf("SALIENDO HILO EMERGENCIAS...\n");

	printf("TIEMPO TOTAL EJECUCION HILO: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

	printf("INTERRUPCION NORMAL\n");
	printf("Pacientes totales atendidos: %d\n", totalPacientesAtendidos);
	system("pause");
}

// Estructura de datos para representar un paciente dentro de la cola Proceso III
struct Pacientes
{
	int numeroPaciente;
	int tiempoAtencion;
	string TipoAtencion;
};

void procesoCirujias()
{
	int tiempoEjecucionHilo = 0;
	int quantum = 5;

	queue<Pacientes> colaCirujias;

	colaCirujias.push({1, 7, "Rojo"});
	colaCirujias.push({2, 8, "Normal"});
	colaCirujias.push({3, 5, "Normal"});
	colaCirujias.push({4, 11, "Rojo"});
	colaCirujias.push({5, 9, "Verde"});
	colaCirujias.push({6, 3, "Normal"});

	int tiempoRestanteAtencion;

	while (!colaCirujias.empty())
	{
		Pacientes pacienteActual = colaCirujias.front();

		// Eliminar el pacienteActual temporalmente
		colaCirujias.pop();

		int tiempoSobrante;

		// Validar casos donde paciente tiempoAtencion es menor / mayor que el quantum (5)
		if (pacienteActual.tiempoAtencion >= quantum)
		{
			// Ejem: 7 - 5 = 2 de tiempo sobrante;
			tiempoSobrante = pacienteActual.tiempoAtencion - quantum;
			tiempoRestanteAtencion = quantum;
		}
		else
		{
			// No necesita de mas iteraciones para completar la cirujia
			tiempoSobrante = 0;
			tiempoRestanteAtencion = pacienteActual.tiempoAtencion;
		}

		if (pacienteActual.TipoAtencion == "Rojo" || pacienteActual.TipoAtencion == "Verde")
		{

			while (tiempoRestanteAtencion >= 0 && pacienteActual.tiempoAtencion != 0)
			{
				system("cls");
				printf("HILO CIRUGIAS EN EJECUCION\n");
				printf("TIEMPO ACTUAL DE EJECUCION: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

				printf("ATENDIENDO PACIENTE NUMERO: %d\n", pacienteActual.numeroPaciente);
				printf("PACIENTE TIPO: %s\n\n", pacienteActual.TipoAtencion.c_str());
				printf("TIEMPO QUE NECESITA EL PACIENTE PARA CIRUJIA: %d\n", pacienteActual.tiempoAtencion);
				printf("TIEMPO RESTANTE: %d\n", tiempoRestanteAtencion);

				esperar(1);
				tiempoRestanteAtencion -= 1;
				tiempoEjecucionHilo++;
			}

			tiempoEjecucionHilo--;
			// Para saber si el proceso de cirujia continua o termino
			if (tiempoSobrante != 0)
			{
				system("cls");
				printf("HILO CIRUGIAS EN EJECUCION\n");
				printf("TIEMPO ACTUAL DE EJECUCION: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

				printf("INTERRUPCION NORMAL\n");
				printf("PACIENTE NUMERO %d EN PROCESO DE ATENCION\n", pacienteActual.numeroPaciente);
				printf("TIEMPO SOBRANTE: %d \n\n", tiempoSobrante);
				esperar(5);

				pacienteActual.tiempoAtencion = tiempoSobrante;
				colaCirujias.push(pacienteActual);
			}
			else
			{
				system("cls");
				printf("HILO CIRUGIAS EN EJECUCION\n");
				printf("TIEMPO ACTUAL DE EJECUCION: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

				printf("INTERRUPCION NORMAL\n");
				printf("PACIENTE NUMERO %d ATENDIDO CORRECTAMENTE\n", pacienteActual.numeroPaciente);
				printf("TIEMPO SOBRANTE: %d \n\n", tiempoSobrante);
				esperar(5);
			}
		}
		else
		{

			while (tiempoRestanteAtencion >= 0)
			{
				system("cls");
				printf("HILO CIRUGIAS EN EJECUCION\n");
				printf("TIEMPO ACTUAL DE EJECUCION: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

				printf("ATENDIENDO PACIENTE NUMERO: %d\n", pacienteActual.numeroPaciente);
				printf("TIEMPO QUE NECESITA EL PACIENTE PARA CIRUJIA: %d\n", pacienteActual.tiempoAtencion);
				printf("PACIENTE TIPO: %s\n\n", pacienteActual.TipoAtencion.c_str());
				printf("TIEMPO RESTANTE: %d\n", tiempoRestanteAtencion);

				esperar(1);
				tiempoRestanteAtencion -= 1;
				tiempoEjecucionHilo++;
			}

			tiempoEjecucionHilo--;
			// Como es normal no se agrega de nuevo a la Queue porque no necesita de su tiempo restante
			system("cls");
			printf("HILO CIRUGIAS EN EJECUCION\n");
			printf("TIEMPO ACTUAL DE EJECUCION: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

			printf("INTERRUPCION NORMAL\n");
			printf("PACIENTE NUMERO %d ATENDIDO CORRECTAMENTE\n", pacienteActual.numeroPaciente);
			printf("TIEMPO SOBRANTE: %d \n\n", tiempoSobrante);
			printf("Nota: Por ser paciente normal no necesitara su tiempo sobrante\n");
			esperar(5);
		}

		// Reiniciar tiempos restantes para demas pacientes e iteraciones
		tiempoRestanteAtencion = 0;
	}

	system("cls");
	printf("SALIENDO HILO CIRUGIAS...\n");
	printf("TIEMPO TOTAL EJECUCION HILO: %d s\n----------------------------------\n\n", tiempoEjecucionHilo);

	printf("INTERRUPCION NORMAL\n");
	printf("TIEMPO TOTAL EMPLEADO EN LA SALA: %d tiempos\n", tiempoEjecucionHilo);
	system("pause");
}

// Declaración de funciones para seguimiento de hilos
void hiloProcesoCitas()
{
	thread threadCitas;

	system("cls");
	printf("HILO CITAS CREADO\n--------------------------\n");
	esperar(5);

	threadCitas = thread(procesoCitas);

	// Join elimina el hilo posterior a terminar su ejecución
	threadCitas.join();

	system("cls");
	printf("HILO CITAS TERMINADO\n-----------------------\n");
	esperar(5);
}

void hiloProcesoEmergencias()
{
	thread threadEmergencias;

	system("cls");
	printf("HILO EMERGENCIAS CREADO\n------------------------\n");
	esperar(5);

	threadEmergencias = thread(procesoEmergencias);

	threadEmergencias.join();

	system("cls");
	printf("HILO EMERGENCIAS TERMINADO\n---------------------------\n");
	esperar(5);
}

void hiloProcesoCirugias()
{
	thread threadCirugias;

	system("cls");
	printf("HILO DE CIRUGIAS CREADO\n------------------------\n");
	esperar(5);

	threadCirugias = thread(procesoCirujias);

	threadCirugias.join();

	system("cls");
	printf("HILO DE CIRUGIAS TERMINADO\n---------------------------");
	esperar(5);
}

int main()
{
	int contadorBucle = 0;
	char procesoSeleccionado;

	while (true)
	{
		system("cls");

		printf("MENU PRINCIPAL DE PROCESOS\n");
		printf("1-Proceso atencion de citas\n");
		printf("2-Proceso atencion de emergencias\n");
		printf("3-Proceso atencion de cirugias\n");
		printf("A-Finalizar proceso\n");

		procesoSeleccionado = _getch();
		procesoSeleccionado = toupper(procesoSeleccionado);

		if (procesoSeleccionado == 'A')
		{
			break;
		}

		switch (procesoSeleccionado)
		{
		case '1':
			hiloProcesoCitas();
			break;
		case '2':
			hiloProcesoEmergencias();
			break;
		case '3':
			hiloProcesoCirugias();
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