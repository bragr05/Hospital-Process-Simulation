#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cctype>
#include <thread>
#include <chrono>
#include <queue>
#include <process.h>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

size_t MEMORY_SIZE = 1024;
void *MEMORIA_RESERVADA;

std::mutex memoria_mutex;
std::condition_variable cv;
bool areaMemoriaDisponible = true;

void cambiarColor(int codColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, codColor);
}

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

bool reservarMemoria(const string &nombreProceso)
{
	unique_lock<mutex> lock(memoria_mutex);
	int tiempoEspera = 0;

	// definir un contador de espera, si este no
	while (!areaMemoriaDisponible && tiempoEspera <= 5)
	{
		cambiarColor(6);
		system("cls");
		printf("\t\tTIEMPO ESPERA: %ds\n-------------------------------------------------------------\n", tiempoEspera);
		printf("RESERVANDO MEMORIA PARA PROCESO: %s...\n", nombreProceso.c_str());
		tiempoEspera++;

		// Reservar el espacio en memoria
		MEMORIA_RESERVADA = malloc(MEMORY_SIZE);

		cv.wait_for(lock, chrono::seconds(1));
		cambiarColor(7);
	}

	// Si areaMemoriaDisponible nunca se coloco en true entonces volver al menu principal
	if (!areaMemoriaDisponible)
	{
		cambiarColor(4);
		system("cls");
		printf("ERROR RUTA DATOS PROCESO: %s\n", nombreProceso.c_str());
		printf("Tiempo de espera agotado. Volviendo al menu principal...\n");
		esperar(3);
		return false;
		cambiarColor(7);
	}

	areaMemoriaDisponible = false;

	cambiarColor(10);
	system("cls");
	printf("\t\tMEMORIA RESERVADA PARA PROCESO: %s\n-------------------------------------------------------------\n", nombreProceso.c_str());
	printf("TOTAL DE MEMORIA RESERVADA: %zu bytes\n", MEMORY_SIZE);
	esperar(3);
	cambiarColor(7);
	return true;
}

void liberarMemoria(const string &nombreProceso)
{
	cambiarColor(9);
	unique_lock<mutex> lock(memoria_mutex);

	areaMemoriaDisponible = true;

	cv.notify_all();

	free(MEMORIA_RESERVADA);
	printf("\t\tMEMORIA LIBERADA PARA PROCESO %s\n-------------------------------------------------------------\n", nombreProceso.c_str());
	printf("TOTAL DE MEMORIA LIBERADA: %zu bytes\n", MEMORY_SIZE);
	esperar(5);
	cambiarColor(7);
}

void imprimirInfoHilo(string NombreHilo, int tiempoEjecucionHilo, bool limpiarPantalla)
{
	if (limpiarPantalla)
	{
		system("cls");
	}

	cambiarColor(3);
	printf("\t\t%s %ds\n", NombreHilo.c_str(), tiempoEjecucionHilo);
	printf("-------------------------------------------------------------\n\n");
	cambiarColor(7);
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

					imprimirInfoHilo("SALIENDO HILO CITAS | TIEMPO TOTAL: ", tiempoEjecucionHilo, true);

					cambiarColor(6);
					printf("INTERRUPCION POR USUARIO\n");
					printf("Tiempo usado por el paciente: %d/5\n", tiempoAtencion);
					printf("Interrupcion generada atendiendo al paciente numero %d\n", numPaciente);
					system("pause");
					cambiarColor(7);
					salirProceso = true;
					break;
				}
			}

			imprimirInfoHilo("HILO CITAS EN EJECUCION", tiempoEjecucionHilo, true);

			printf("TIEMPO ATENCION ACTUAL: %d\n", tiempoAtencion);
			printf("Atentiendo paciente numero %d\n\n", numPaciente);
			cambiarColor(4);
			printf("Presione tecla I para terminar el proceso\n");
			cambiarColor(7);

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

			imprimirInfoHilo("HILO CITAS EN EJECUCION", tiempoEjecucionHilo, true);

			cambiarColor(2);
			printf("INTERRUPCION NORMAL\n");
			printf("Se atendio con exito al paciente numero %d\n", numPaciente);
			cambiarColor(7);
			esperar(5);
		}

		totalPacientesAtenididos = numPaciente;

		// Reiniciar tiempo para otros pacientes
		tiempoAtencion = 0;
	}

	if (totalPacientesAtenididos == 10)
	{
		imprimirInfoHilo("SALIENDO HILO CITAS | TIEMPO TOTAL: ", tiempoEjecucionHilo, true);

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
		imprimirInfoHilo("HILO EMERGENCIAS EN EJECUCION", tiempoEjecucionHilo, true);

		if (_kbhit())
		{
			interrupcionUsuario = _getch();
			interrupcionUsuario = toupper(interrupcionUsuario);

			if (interrupcionUsuario == 'S' && tiempoProceso >= 20)
			{
				imprimirInfoHilo("SALIENDO HILO EMERGENCIAS | TIEMPO TOTAL: ", tiempoEjecucionHilo, true);

				cambiarColor(6);
				printf("INTERRUPCION POR USUARIO\n");
				printf("Interrupcion generada atendiendo al paciente numero %d\n", numPaciente);
				esperar(5);
				cambiarColor(7);
				break;
			}
			else if (interrupcionUsuario == 'P')
			{
				numPaciente++;
				totalPacientesAtendidos = numPaciente;
			}
		}

		printf("Atendiendo paciente numero %d\n\n", numPaciente);

		cambiarColor(13);
		printf("Presione tecla P para avanzar paciente\n");
		cambiarColor(4);
		printf("A los 20 segundos puede finalizar el proceso con la tecla S\n");
		cambiarColor(7);

		limpiarBufferTeclas();

		esperar(1);
		tiempoProceso++;
		tiempoEjecucionHilo++;
	}

	tiempoEjecucionHilo--;

	imprimirInfoHilo("SALIENDO HILO EMERGENCIAS | TIEMPO TOTAL: ", tiempoEjecucionHilo, true);

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

void imprimirCola(queue<Pacientes> colaCirujias)
{
	int codColor;
	printf("\n\t\tVISUALIZACION DE LAS CIRUGIAS\n\n");

	cout << left << setw(20) << "| Numero Paciente" << setw(20) << "| Tiempo Atencion" << setw(20) << "| Tipo Atencion     |" << endl;
	cout << setfill('-') << setw(20) << "| " << setw(20) << "| " << setw(20) << "| "
		 << "|" << setfill(' ') << endl;

	while (!colaCirujias.empty())
	{
		Pacientes paciente = colaCirujias.front();
		if (paciente.TipoAtencion == "Rojo")
		{
			codColor = 4;
		}
		else if (paciente.TipoAtencion == "Verde")
		{
			codColor = 2;
		}
		else
		{
			codColor = 7;
		}
		cambiarColor(codColor);
		cout << left << setw(20) << "| " + to_string(paciente.numeroPaciente) << setw(20) << "| " + to_string(paciente.tiempoAtencion) + "s" << setw(20) << "| " + paciente.TipoAtencion << "|" << endl;
		cambiarColor(7);
		colaCirujias.pop();
	}
	cambiarColor(7);
	printf("\n\n");
}

void imprimirInformacionDuranteAtencion(queue<Pacientes> colaCirujias, int tiempoEjecucionHilo, Pacientes pacienteActual, int tiempoRestanteAtencion)
{
	imprimirInfoHilo("HILO CIRUGIAS EN EJECUCION", tiempoEjecucionHilo, true);
	imprimirCola(colaCirujias);

	cambiarColor(6);
	printf("\nATENDIENDO PACIENTE NUMERO: %d\n", pacienteActual.numeroPaciente);
	printf("PACIENTE TIPO: %s\n", pacienteActual.TipoAtencion.c_str());
	printf("TIEMPO QUE NECESITA EL PACIENTE PARA CIRUJIA: %d\n", pacienteActual.tiempoAtencion);
	cambiarColor(3);
	printf("\t\t\nTIEMPO RESTANTE: %d\n\n", tiempoRestanteAtencion);
	cambiarColor(7);
	esperar(1);
}

void imprimirInformacionPostAtencion(queue<Pacientes> colaCirujias, int tiempoEjecucionHilo, Pacientes pacienteActual, int tiempoSobrante)
{
	imprimirInfoHilo("HILO CIRUGIAS EN EJECUCION", tiempoEjecucionHilo, true);
	imprimirCola(colaCirujias);

	// Para determinar si se atendio ya con exito o continua
	string mensaje = (tiempoSobrante != 0) ? "EN PROCESO DE ATENCION" : "ATENDIDO CORRECTAMENTE";

	cambiarColor(2);
	printf("\nINTERRUPCION NORMAL\n");
	printf("PACIENTE NUMERO %d %s\n\n", pacienteActual.numeroPaciente, mensaje.c_str());
	printf("\t\tTIEMPO SOBRANTE: %d \n\n", tiempoSobrante);
	cambiarColor(7);
	system("pause");
}

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
				imprimirInformacionDuranteAtencion(colaCirujias, tiempoEjecucionHilo, pacienteActual, tiempoRestanteAtencion);
				tiempoRestanteAtencion -= 1;
				tiempoEjecucionHilo++;
			}

			tiempoEjecucionHilo--;
			// Para saber si el proceso de cirujia continua o termino
			if (tiempoSobrante != 0)
			{
				imprimirInformacionPostAtencion(colaCirujias, tiempoEjecucionHilo, pacienteActual, tiempoSobrante);
				pacienteActual.tiempoAtencion = tiempoSobrante;
				colaCirujias.push(pacienteActual);
			}
			else
			{
				imprimirInformacionPostAtencion(colaCirujias, tiempoEjecucionHilo, pacienteActual, tiempoSobrante);
			}
		}
		else
		{

			while (tiempoRestanteAtencion >= 0)
			{
				imprimirInformacionDuranteAtencion(colaCirujias, tiempoEjecucionHilo, pacienteActual, tiempoRestanteAtencion);
				tiempoRestanteAtencion -= 1;
				tiempoEjecucionHilo++;
			}

			tiempoEjecucionHilo--;
			imprimirInformacionPostAtencion(colaCirujias, tiempoEjecucionHilo, pacienteActual, tiempoSobrante);
		}

		colaCirujias.pop();
		// Reiniciar tiempos restantes para demas pacientes e iteraciones
		tiempoRestanteAtencion = 0;
	}

	imprimirInfoHilo("SALIENDO HILO CIRUGIAS | TIEMPO TOTAL: ", tiempoEjecucionHilo, true);

	printf("INTERRUPCION NORMAL\n");
	printf("TIEMPO TOTAL EMPLEADO EN LA SALA: %ds\n", tiempoEjecucionHilo);
	system("pause");
}

// Declaración de funciones para seguimiento de hilos
void hiloProcesoCitas()
{
	string nombreProceso = "CITAS";
	bool memoriaReservada = reservarMemoria(nombreProceso);

	// Si no se pudo reservar memoria regresar el menu principal
	if (!memoriaReservada)
	{
		return;
	}

	thread threadCitas;

	system("cls");
	cambiarColor(2);
	printf("\t\tHILO CITAS CREADO\n-------------------------------------------------------------\n");
	esperar(3);
	cambiarColor(7);

	threadCitas = thread(procesoCitas);

	// Join elimina el hilo posterior a terminar su ejecución
	threadCitas.join();

	system("cls");
	cambiarColor(11);
	printf("\t\t\tHILO CITAS TERMINADO\n-------------------------------------------------------------\n");
	liberarMemoria(nombreProceso);
	esperar(5);
	cambiarColor(7);
}

void hiloProcesoEmergencias()
{
	string nombreProceso = "EMERGENCIAS";
	bool memoriaReservada = reservarMemoria(nombreProceso);

	// Si no se pudo reservar memoria regresar el menu principal
	if (!memoriaReservada)
	{
		return;
	}

	thread threadEmergencias;

	system("cls");
	cambiarColor(2);
	printf("\t\tHILO EMERGENCIAS CREADO\n-------------------------------------------------------------\n");
	esperar(3);
	cambiarColor(7);

	threadEmergencias = thread(procesoEmergencias);

	threadEmergencias.join();

	system("cls");
	cambiarColor(11);
	printf("\t\t\tHILO EMERGENCIAS TERMINADO\n-------------------------------------------------------------\n");
	liberarMemoria(nombreProceso);
	esperar(5);
	cambiarColor(7);
}

void hiloProcesoCirugias()
{
	string nombreProceso = "CIRUGIAS";
	bool memoriaReservada = reservarMemoria(nombreProceso);

	// Si no se pudo reservar memoria regresar el menu principal
	if (!memoriaReservada)
	{
		return;
	}

	thread threadCirugias;

	system("cls");
	cambiarColor(2);
	printf("\t\tHILO DE CIRUGIAS CREADO\n-------------------------------------------------------------\n");
	esperar(3);
	cambiarColor(7);

	threadCirugias = thread(procesoCirujias);

	threadCirugias.join();

	system("cls");
	cambiarColor(11);
	printf("\t\t\tHILO DE CIRUGIAS TERMINADO\n-------------------------------------------------------------\n");
	liberarMemoria(nombreProceso);
	esperar(5);
	cambiarColor(7);
}

int main()
{
	int contadorBucle = 0;
	char procesoSeleccionado;

	while (true)
	{
		system("cls");
		cambiarColor(14);
		printf("\t\tMENU PRINCIPAL DE PROCESOS\n-------------------------------------------------------------\n");
		printf("\t1-Proceso atencion de citas\n");
		printf("\t2-Proceso atencion de emergencias\n");
		printf("\t3-Proceso atencion de cirugias\n\n");
		cambiarColor(4);
		printf("\tA-Finalizar proceso\n");
		cambiarColor(7);

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