#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

const int MAX_CLIENTES = 100;
const int CODIGO_INICIAL = 100;
const string ARCHIVO_CLIENTES = "ListaClientes.txt";

typedef struct 
    {
        int codigo;
        string nombre;
        string mail;
        string celular;
    } tCliente;

typedef struct
    {
        tCliente clientes[MAX_CLIENTES];
        int contador;
    } tListaClientes;

void menu(); 
void cargarClientes(tListaClientes &lista);
void guardarClientes(const tListaClientes &lista);
void crearCliente(tListaClientes &lista);
void leerClientes(const tListaClientes &lista);
void mostrarCliente(const tCliente &cliente);
void actualizarCliente(tListaClientes &lista);
void eliminarCliente(tListaClientes &lista);
int buscarCliente(const tListaClientes &lista, int codigo); 

int main()
    {
        menu();
        return 0;
    }

void menu()
    {
        tListaClientes lista;
        lista.contador = 0;
        
        cargarClientes(lista);
        
        int opcion;
        do
            {

                cout << "MENU DE GESTION DE CLIENTES\n";

                cout << "1. Crear nuevo cliente\n";
                cout << "2. Listar todos los clientes\n";
                cout << "3. Mostrar un cliente por codigo\n";
                cout << "4. Actualizar datos de cliente\n";
                cout << "5. Eliminar cliente\n";
                cout << "0. Salir\n";

                cout << "Selecciona una opcion: ";
                cin >> opcion;
                cin.ignore();
                
                switch(opcion)
                    {
                        case 1:
                            crearCliente(lista);  
                            break;
                        case 2:
                            leerClientes(lista);  
                            break;
                        case 3:
                            { 
                                int codigo;
                                cout << "\nIngresa el codigo del cliente: ";
                                cin >> codigo;
                                int pos = buscarCliente(lista, codigo);
                                if (pos != -1)
                                    mostrarCliente(lista.clientes[pos]);
                                else
                                    cout << "\nCliente no encontrado.\n" << endl;
                            }
                            break;
                        case 4:
                            actualizarCliente(lista);
                            break;
                        case 5:
                            eliminarCliente(lista);
                            break;
                        case 0:
                            guardarClientes(lista);
                            cout << "\nDatos guardados. Saliendo...\n" << endl;
                            break;
                        default:
                            cout << "\nOpcion no valida. Intenta nuevamente.\n" << endl;
                    }
            } while (opcion != 0);
    }




void crearCliente(tListaClientes &lista)
    {

        if (lista.contador < MAX_CLIENTES) 
            {

                tCliente nuevo;

                if (lista.contador == 0) 
                {

                    nuevo.codigo = CODIGO_INICIAL; 
                }
                else
                {

                    nuevo.codigo = lista.clientes[lista.contador - 1].codigo + 1; 
                }
                
                cout << "\n\nCREAR NUEVO CLIENTE\n";
                cout << "Codigo asignado: " << nuevo.codigo << endl;
                cout << "Nombre: ";
                getline(cin, nuevo.nombre);
                cout << "Email: ";
                getline(cin, nuevo.mail);
                cout << "Celular: ";
                getline(cin, nuevo.celular);
                

                lista.clientes[lista.contador] = nuevo; 

                lista.contador++;
                
                cout << "\nCliente creado exitosamente!\n" << endl;
                mostrarCliente(nuevo); 

                guardarClientes(lista);
            }
            else 
            {
                cout << "\nNo se pueden agregar mas clientes. Limite alcanzado.\n" << endl;
            }
    }



    void cargarClientes(tListaClientes &lista) 
        {
            ifstream archivo(ARCHIVO_CLIENTES);
            if (archivo.is_open())
                {
                    lista.contador = 0;
                    while (lista.contador < MAX_CLIENTES && archivo >> lista.clientes[lista.contador].codigo)
                        {
                            archivo.ignore();
                            getline(archivo, lista.clientes[lista.contador].nombre);
                            getline(archivo, lista.clientes[lista.contador].mail);
                            getline(archivo, lista.clientes[lista.contador].celular);
                            lista.contador++;
                        }
                    archivo.close();
                }
        }

void guardarClientes(const tListaClientes &lista)
    {
        ofstream archivo(ARCHIVO_CLIENTES);
        if (archivo.is_open())
            {
                for (int i = 0; i < lista.contador; i++)
                    {
                        archivo << lista.clientes[i].codigo << endl;
                        archivo << lista.clientes[i].nombre << endl;
                        archivo << lista.clientes[i].mail << endl;
                        archivo << lista.clientes[i].celular << endl;
                    }
                archivo.close();
            }
    }



void leerClientes(const tListaClientes &lista)
    {
        cout << "\nLISTADO DE CLIENTES\n";
        if (lista.contador == 0)
            {
            cout << "\nNo hay clientes registrados.\n" << endl;
            }
            else
                {
                    cout << left << setw(10) << "CODIGO" 
                        << setw(30) << "NOMBRE" 
                        << setw(30) << "EMAIL" 
                        << setw(15) << "CELULAR" << endl;
                    cout << string(85, '=') << endl;
                    
                    for (int i = 0; i < lista.contador; i++)
                        {
                            cout << left << setw(10) << lista.clientes[i].codigo
                                << setw(30) << lista.clientes[i].nombre
                                << setw(30) << lista.clientes[i].mail
                                << setw(15) << lista.clientes[i].celular << endl;
                        }
                }
    }

void mostrarCliente(const tCliente &cliente)
    {
        cout << "\nDATOS DEL CLIENTE\n";
        cout << "Codigo: " << cliente.codigo << endl;
        cout << "Nombre: " << cliente.nombre << endl;
        cout << "Email: " << cliente.mail << endl;
        cout << "Celular: " << cliente.celular << endl;
        cout << "========================" << endl;
    }

void actualizarCliente(tListaClientes &lista)
{
    if (lista.contador == 0) 
        {
            cout << "\nNo hay clientes registrados para actualizar.\n" << endl;
            return;
        }
    
    int codigo;
    cout << "Ingresa el codigo del cliente a actualizar: ";
    cin >> codigo;
    cin.ignore();
    
    int pos = buscarCliente(lista, codigo);
    if (pos == -1) 
        {
            cout << "\nCliente no encontrado.\n" << endl;
            return;
        }

    cout << "\nActualizando datos del cliente (deja en blanco para mantener el valor actual):\n" << endl;
    
    string temp;  
    
    cout << "Nombre actual: " << lista.clientes[pos].nombre << endl; 
    cout << "Nuevo nombre: ";
    getline(cin, temp);
    if (!temp.empty()) lista.clientes[pos].nombre = temp;
    
    cout << "Email actual: " << lista.clientes[pos].mail << endl;
    cout << "Nuevo email: ";
    getline(cin, temp);
    if (!temp.empty()) lista.clientes[pos].mail = temp; 
    
    cout << "Celular actual: " << lista.clientes[pos].celular << endl;
    cout << "Nuevo celular: ";
    getline(cin, temp);
    if (!temp.empty()) lista.clientes[pos].celular = temp;
    
    mostrarCliente(lista.clientes[pos]);
    guardarClientes(lista);
    cout << "\nDatos del cliente actualizados correctamente!\n" << endl;

    
}

void eliminarCliente(tListaClientes &lista)
    {
        int codigo;
        cout << "\nIngresa el codigo del cliente a eliminar: ";
        cin >> codigo;
        
        int pos = buscarCliente(lista, codigo);
        if (pos != -1)
            {
                cout << "\n\nELIMINAR CLIENTE\n";
                mostrarCliente(lista.clientes[pos]);
                
                char confirmar;
                cout << "\nEsta seguro que desea eliminar este cliente? (s/n): ";
                cin >> confirmar;
                
                if (confirmar == 's' || confirmar == 'S')
                    {
                        for (int i = pos; i < lista.contador - 1; i++)
                            {
                                lista.clientes[i] = lista.clientes[i + 1]; 
                            }
                        lista.contador--;
                        
                        cout << "\nCliente eliminado exitosamente!\n" << endl;
                        guardarClientes(lista);
                    }
                    else
                        {
                            cout << "\nOperacion cancelada.\n" << endl;
                        }
            }
            else
            {
                cout << "\nCliente no encontrado.\n" << endl;
            }
    }

int buscarCliente(const tListaClientes &lista, int codigo) 
    {
        for (int i = 0; i < lista.contador; i++)
            {
                if (lista.clientes[i].codigo == codigo)
                    {
                        return i;
                    }
            }
        return -1;
    }