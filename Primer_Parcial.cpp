#include <iostream>
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;
const char *nombre_archivo = "archivo.dat";
const char *nombre_auxiliar = "auxiliar.dat";
struct Empleado
{
	int codigo;
	char nombre[20];
	char apellido[20];
	char puesto[20];
	float sueldoBase;
	float bonificacion;
	float sueldoTotal;
};
void ingresarEmpleado();
void verEmpleado();
void buscarEmpleado();
void modificarEmpleado();
void eliminarEmpleado();
void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}
int main()
{
	int opc;
	system("color 02");
	do
	{
		system("cls");
		cout<<"-----Sistema de Registro de Empleados-----\n\n";
		cout<<"1.-----------------------Ingresar empleado\n";
		cout<<"2.-----------------Ver todos los empleados\n";
		cout<<"3.-------------------------Buscar empleado\n";
		cout<<"4.----------------------Modificar empleado\n";
		cout<<"5.-----------------------Eliminar empleado\n";
		cout<<"6.-----------------------------------Salir\n";
		cin>>opc;
		switch (opc)
		{
			case 1:
				ingresarEmpleado();
				break;
			case 2:
				verEmpleado();
				break;
			case 3:
				buscarEmpleado();
				break;
			case 4: 
				modificarEmpleado();
				break;
			case 5:
				eliminarEmpleado();
				break;
			case 6:
				cout<<"Tenga un buen dia";
				break;
			default:
				cout<<"Ha ingresado una opcion invalida";
				getch();
		}
	}while(opc != 6);
}
void ingresarEmpleado()
{
	char continuar;
	FILE* archivo = fopen(nombre_archivo, "ab");
	Empleado empleado;
	string nombre,apellido,puesto;
	do
	{
		system ("cls");
		fflush(stdin);
		cout<<"Ingreso de empleados: \n";
		cout<<"________________________________\n";
		cout<<"\nIngrese el codigo del empleado: ";
		cin>>empleado.codigo;
		cin.ignore();
		cout<<"\nIngrese el nombre del empleado: ";
		getline(cin,nombre);
		strcpy(empleado.nombre, nombre.c_str());
		cout<<"\nIngrese el apellido del empleado: ";
		getline(cin,apellido);
		strcpy(empleado.apellido, apellido.c_str());
		cout<<"\nIngrese el puesto del empleado: ";
		getline(cin,puesto);
		strcpy(empleado.puesto, puesto.c_str());
		cout<<"\nIngrese el sueldo base del empleado: ";
		cin>>empleado.sueldoBase;
		cin.ignore();
		cout<<"\nIngrese la bonificacion del empleado: ";
		cin>>empleado.bonificacion;
		cin.ignore();
		empleado.sueldoTotal = empleado.sueldoBase + empleado.bonificacion;
		
		fwrite(&empleado, sizeof(Empleado), 1, archivo);
		cout<<"Desea registrar otro empleado s/n: ";
		cin>>continuar;
	} while(continuar=='s' || continuar=='S');
	fclose(archivo);
}

void verEmpleado()
{
	system ("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	if(!archivo) 
	{
		archivo = fopen(nombre_archivo, "w+b");
	}
	Empleado empleado;
	int fila = 3;
	fread ( &empleado, sizeof(Empleado), 1, archivo );
	cout<<"_____________________________________MOSTRANDO EMPLEADOS______________________________________________________________\n";
	gotoxy(0,1);
	cout<<"| Codigo:";
	gotoxy(10,1);
	cout<<"| Nombre:";
	gotoxy(32,1);
	cout<<"| Apellido:";
	gotoxy(52,1);
	cout<<"| Puesto";
	gotoxy(72,1);
	cout<<"| Sueldo";
	gotoxy(87,1);
	cout<<"| Bonificacion:";
	gotoxy(105,1);
	cout<<"| Sueldo total:";
	do
	{
		gotoxy(0,fila);
		cout<<"_______________________________________________________________________________________________________________________\n";
		fila+=1;
		gotoxy(0,fila);
		cout<<empleado.codigo;
		gotoxy(10,fila);
		cout<<empleado.nombre;
		gotoxy(32,fila);
		cout<<empleado.apellido;
		gotoxy(52,fila);
		cout<<empleado.puesto;
		gotoxy(72,fila);
		cout<<"Q."<<empleado.sueldoBase;
		gotoxy(87,fila);
		cout<<"Q."<<empleado.bonificacion;
		gotoxy(105,fila);
		cout<<"Q."<<empleado.sueldoTotal;
		fila +=1;
		
		fread(&empleado, sizeof(Empleado), 1, archivo);
	}while(feof(archivo)==0);
	fclose(archivo);
	cout<<"\n\nPresione cualquier tecla para continuar";
	getch();
}

void buscarEmpleado()
{
	FILE* archivo = fopen(nombre_archivo, "rb");
	int indice=0,pos=0,cod=0;
	Empleado empleado;
	system("cls");
	cout<<"Ingrese el codigo del empleado que desea buscar: ";
	cin>>cod;
	fread (&empleado, sizeof(Empleado), 1, archivo);
	do
	{
		if (empleado.codigo == cod)
		{
			pos=indice;
		}
		fread (&empleado, sizeof(Empleado), 1, archivo);
		indice +=1;
	}while(feof(archivo)==0);
	cout<<"____________"<<cod<<"____________\n";
	fseek (archivo, pos*sizeof(Empleado),SEEK_SET);
	fread ( &empleado, sizeof(Empleado), 1, archivo );
	cout<<"Codigo: "<<empleado.codigo<<endl;
	cout<<"Nombre: "<<empleado.nombre<<endl;
	cout<<"Apellido: "<<empleado.apellido<<endl;
	cout<<"Puesto: "<<empleado.puesto<<endl;
	cout<<"Sueldo: Q."<<empleado.sueldoBase<<endl;
	cout<<"Bonificacion: Q."<<empleado.bonificacion<<endl;
	cout<<"Sueldo total: Q."<<empleado.sueldoTotal<<endl;
	fclose(archivo);
	cout<<"\n\nPresione cualquier tecla para continuar";
	getch();
}

void modificarEmpleado()
{
	FILE* archivo = fopen(nombre_archivo, "r+b");
	int indice=0,pos=0,cod=0;
	string nombre,apellido,puesto;	
	Empleado empleado;
	system("cls");
	cout<<"Ingrese el codigo del empleado que desea modificar: ";
	cin>>cod;
	fread (&empleado, sizeof(Empleado), 1, archivo);
	do
	{
		if(empleado.codigo == cod)
		{
			pos=indice;
		}
		fread (&empleado, sizeof(Empleado), 1, archivo);
		indice +=1;
	}while(feof(archivo)==0);
	cout<<"____________REGISTRO_A_MODIFICAR____________\n";
	fseek (archivo, pos*sizeof(Empleado),SEEK_SET);
	fread ( &empleado, sizeof(Empleado), 1, archivo );
	cout<<"Codigo: "<<empleado.codigo<<endl;
	cout<<"Nombre: "<<empleado.nombre<<endl;
	cout<<"Apellido: "<<empleado.apellido<<endl;
	cout<<"Puesto: "<<empleado.puesto<<endl;
	cout<<"Sueldo: Q."<<empleado.sueldoBase<<endl;
	cout<<"Bonificacion: Q."<<empleado.bonificacion<<endl;
	cout<<"Sueldo total: Q."<<empleado.sueldoTotal<<endl;
	cout<<"____________________________________________\n";
	cout<<"___________________MODIFICANDO______________\n";
	fseek ( archivo, pos*sizeof(Empleado), SEEK_SET );
	cout<<"\nIngrese el nuevo codigo: ";
	cin>>empleado.codigo;
	cin.ignore();
	cout<<"\nIngrese el nuevo nombre del empleado: ";
	getline(cin,nombre);
	strcpy(empleado.nombre, nombre.c_str());
	cout<<"\nIngrese el nuevo apellido del empleado: ";
	getline(cin,apellido);
	strcpy(empleado.apellido, apellido.c_str());
	cout<<"\nIngrese el nuevo puesto del empleado: ";
	getline(cin,puesto);
	strcpy(empleado.puesto, puesto.c_str());
	cout<<"\nIngrese el nuevo sueldo base del empleado: ";
	cin>>empleado.sueldoBase;
	cin.ignore();
	cout<<"\nIngrese la nueva bonificacion del empleado: ";
	cin>>empleado.bonificacion;
	cin.ignore();
	empleado.sueldoTotal = empleado.sueldoBase + empleado.bonificacion;
	fwrite( &empleado, sizeof(Empleado), 1, archivo );
	fclose(archivo);
	verEmpleado();
}

void eliminarEmpleado()
{
	system("cls");
    Empleado empleado;
    FILE *auxiliar = fopen(nombre_auxiliar, "w+b");
    FILE *archivo = fopen(nombre_archivo, "r+b");
    int indice=0,pos=0,cod=0;
    string nada="nada";
    cout << "Ingrese el codigo del empleado que desea eliminar: ";
    cin >> cod;
    fread (&empleado, sizeof(Empleado), 1, archivo);
	do
	{
		if(empleado.codigo == cod)
		{
			pos=indice;
		}
		fread (&empleado, sizeof(Empleado), 1, archivo);
		indice +=1;
	}while(feof(archivo)==0);
    fseek(archivo, pos*sizeof(Empleado), SEEK_SET);
    empleado.codigo = -1;
    strcpy(empleado.nombre, nada.c_str());
    strcpy(empleado.apellido, nada.c_str());
    strcpy(empleado.puesto, nada.c_str());
    empleado.sueldoBase = 0;
    empleado.bonificacion = 0;
    empleado.sueldoTotal = 0;
    fwrite(&empleado, sizeof(Empleado), 1, archivo);
    fclose(archivo);

    archivo = fopen(nombre_archivo, "r+b");

    fread(&empleado, sizeof(Empleado), 1, archivo);
    auxiliar = fopen(nombre_auxiliar, "a+b");
    do
    {
        if (empleado.codigo == -1)
        {
            cout << "Archivo eliminado";
        }
        if (empleado.codigo >= 0)
        {
            fwrite(&empleado, sizeof(Empleado), 1, auxiliar);
        }
        fread(&empleado, sizeof(Empleado), 1, archivo);
    } while (feof(archivo) == 0);
    fclose(auxiliar);
    fclose(archivo);

    archivo = fopen(nombre_archivo, "w");
    fclose(archivo);

    auxiliar = fopen(nombre_auxiliar, "r+b");

    fread(&empleado, sizeof(Empleado), 1, auxiliar);
    archivo = fopen(nombre_archivo, "a+b");
    do
    {
        fwrite(&empleado, sizeof(Empleado), 1, archivo);
        fread(&empleado, sizeof(Empleado), 1, auxiliar);
    } while (feof(auxiliar) == 0);
    fclose(archivo);
    fclose(auxiliar);

    auxiliar = fopen(nombre_auxiliar, "w");
    fclose(auxiliar);

    verEmpleado();
}
