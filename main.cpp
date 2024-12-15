#include <iostream>
#include <string>

using namespace std;

/**
 * Estructura Alumno para manejar los datos de un alumno
 * Consta de un campo "nombre" de tipo string
 * y campo "nota" de tipo float
 */
struct Alumno {
    string nombre; // Campo nombre (string)
    float nota; // Campo nota (float)
};


/**
 * Pide la nota del alumno mediante entrada por teclado
 * Comprueba que la nota está entre 0 y 10 y si no es así
 * vuelve a pedir al usuario la introducción de la nota
 * @return Un valor entre 0 y 10, correspondiente a una nota numérica
 */
float inputNota() {
    float nota;
    do {
        std::cout << "Introduce una nota numerica de 0 a 10:";
        cin >> nota;
    } while (nota < 0 || nota > 10);
    return nota;
}


/**
 * Pide el nombre y apellidos del alumno mediante entrada por teclado
 * Comprueba que el texto no esté vacío, de lo contrario
 * vuelve a pedir al usuario la introducción del dato
 * @return Un string con el nombre y apellidos
 */
string inputNombre() {
    string nombre;
    do {
        cout << "Introduce un nombre para el alumno:";
        getline(cin, nombre);
        if (nombre.empty()) {
            cout << "El nombre no puede quedar vacio!!!\n";
        }
    } while (nombre.empty());
    return nombre;
}


/**
 * Apoyándose en los métodos inputNota e inputNombre
 * obtiene los datos de un alumno: nombre y nota para crear una
 * estructura Alumno de manera dinámica, inicializar sus campos nombre
 * y apellido con los datos introducidos por el usuario,
 * para finalmente devolver un puntero al Alumno
 * @return Puntero a la memoria reservada dinámicamente
 * para almacenar una estructura de tipo Alumno
 */
Alumno *inputAlumno() {
    Alumno *alumno = new Alumno;
    cout << "Introduce datos del alumno...\n";
    alumno->nombre = inputNombre();
    alumno->nota = inputNota();
    return alumno;
}


/**
 * Estructura para manejar una lista de alumnos
 * El campo capacidad especifica el número máximo de alumnos que podrá
 * manejar la lista
 * El campo num reflejará la cantidad real de alumnos que hay en la lista
 * El campo alumnos servirá para apuntar a memoria dinámica, concretamente
 * debe manejar un "array" de punteros a estructura de tipo Alumno
 */
struct ListaAlumnos {
    int capacidad;
    int num;
    Alumno **alumnos;
};

/**
 * Pide al usuario la capacidad maxima de almacenar Alumnos en una lista
 * Comprueba que el valor es un número positivo mayor que cero,
 * si no es así, vuelve a preguntar al usuario
 * @return Un valor positivo distinto de cero
 */
int inputCapacidad() {
    int capacidad;
    do {
        cout << "Introduce capacidad maxima de la lista de alumnos:";
        cin >> capacidad;
        if (capacidad <= 0) {
            cout << "La capacidad tiene que ser un valor positivo!\n";
        }
    } while (capacidad <= 0);
    return capacidad;
}


/**
 * A partir de valor entero proporcionado como argumento de llamada que indica
 * el máximo número de alumnos que queremos alojar en la lista
 * reserva memoria dinámicamente para crear la estructura ListaAlumnos
 * e inicializa apropiadamente sus campos capacidad y num
 * además de reservar dinámicamente la memoria para los punteros a las
 * estructuras Alumno necesarias de manera contigua en memoria
 * @param capacidad Número máximo de alumnos que queremos que tenga la lista
 * @return devuelve un puntero que apunta a la zona de memoria reservada para
 * los datos de la estructura ListaAlumnos
 */
ListaAlumnos *crearLista(const int capacidad) {
    ListaAlumnos *lista = new ListaAlumnos;
    lista->capacidad = capacidad;
    lista->num = 0;
    lista->alumnos = new Alumno *[lista->capacidad];
    return lista;
}

/**
 * Libera toda la memoria reservada por la lista de alumnos
 * Para ello, libera
 * la memoria reservada para cada Alumno
 * la memoria reservada para el "array" de punteros a estructura Alumno
 * la memoria de los campos de la propia estructura ListaAlumnos
 * @param lista Puntero a una estructura de tipo ListaAlumnos
 */
void destruirLista(ListaAlumnos *lista) {
    if (lista == nullptr) return;
    for (int i = 0; i < lista->num; ++i) {
        delete lista->alumnos[i]; // Liberamos la memoria reservada por el alumno i-esimo de la lista
        lista->alumnos[i] = nullptr; //Hacer que el puntero no quede colgante
    }

    delete[] lista->alumnos; // Libera los punteros a estructuras Alumno
    lista->alumnos = nullptr;
    delete lista; // Libera la memoria reservada por la estructura ListaAlumnos
}


/**
 * Método que comprueba si una lista proporcionada como argumento de llamada
 * tiene o no alumnos insertados en ella
 * @param lista Puntero a una estructura de tipo ListaAlumnos
 * @return valor bool verdadero si la lista no tiene ningún alumno añadido o
 * falso si la lista ya tiene al menos un alumno
 */
inline bool estaVacia(const ListaAlumnos *lista) {
    //Aquí aprovechamos que el operador or es por cortocircuito,
    //si lo primero es cierto no se evalúa lo segundo
    //Ya que si no hay lista, no hay numero que comprobar si es cero
    return lista == nullptr or lista->num == 0;
}


/**
 * Método que comprueba si una lista proporcionada como argumento de llamada
 * tiene el máximo de alumnos que puede manejar ya añadidos
 * @param lista Puntero a una estructura de tipo ListaAlumnos
 * @return Valor booleano verdadero si la lista ha llegado al máximo de su capacidad o
 * falso si la lista todavía permite añadir algún alumno más
 */
inline bool estaLlena(const ListaAlumnos *lista) {
    // Aprovechamos que el operador and cortocircuita y no
    // sigue evaluando el segundo operando (derecha) si el primero es falso
    return lista != nullptr and lista->num == lista->capacidad;
}


/**
 * Añade un nuevo alumno a la lista después del último alumno de la lista
 * @param lista Puntero a una estructura de tipo ListaAlumnos
 * @param alumno Puntero a una estructura de tipo Alumno con el alumno a añadir
 * @return Verdadero si se ha podido añadir el alumno porque la lista no estaba
 * llena todavía o falso en caso contrario
 */
bool addAlumno(ListaAlumnos *lista, Alumno *alumno) {
    if (alumno == nullptr) return false; // Si no hay alumno no hay nada que insertar
    if (estaLlena(lista)) return false; // Si la lista está llena tampoco
    lista->alumnos[lista->num++] = alumno; //Copia la dirección del alumno e incrementa num
    return true;
}


/**
 * Calcula la nota media de los alumnos de una lista de alumnos proporcionada
 * en un parámetro de entrada de tipo puntero a ListaAlumnos
 * @param lista Puntero a una estructura de tipo ListaAlumnos
 * @return Un float con el valor calculado de la nota media de los alumnos
 */
float getNotaMedia(const ListaAlumnos *lista) {
    if (estaVacia(lista)) return 0;
    float suma = 0;
    for (int i = 0; i < lista->num; i++) {
        suma += lista->alumnos[i]->nota; //Sumamos las notas de todos los alumnos
    }
    return suma / static_cast<float>(lista->num); //suma dividida por total alumnos
}


/**
 * Recorre la lista de alumnos para encontrar el alumno con mayor nota de todos
 * Debe comprobar si la lista está vacía y en ese caso devolver un puntero nulo
 * Si la lista no está vacía debe devolver un puntero de tipo Alumno con
 * la dirección de memoria donde se ubican los datos del alumno
 * @param lista Puntero a una estructura de tipo ListaAlumnos
 * @return Un puntero a la estructura de tipo Alumno que en la lista tiene mayor nota
 */
Alumno *getAlumnoMaxNota(const ListaAlumnos *lista) {
    if (estaVacia(lista)) return nullptr;
    Alumno *max = lista->alumnos[0]; // Asumimos que el primer alumno es el de la nota maxima
    for (int i = 1; i < lista->num; i++) { // Comparamos con la nota de los siguientes
        if (lista->alumnos[i]->nota > max->nota) { // Si la nota del alumno i-esimo es mayor
            max = lista->alumnos[i]; // Este alumno i-esimo se convierte en el alumno de max nota
        }
    }
    return max;
}


/**
 * Si la lista esta vacía, no existe ningún alumno en ella que este suspendido,
 * por tanto, el método devuelve false.
 * Si la lista contiene alumnos, se recorre hasta que se comprueben todas
 * las notas de todos los alumnos o hasta que se encuentre un alumno
 * cuya nota es inferior a 5
 * Si se llega al final de la lista sin encontrar un alumno con nota inferior
 * a 5 se devuelve falso, si se encuentra antes un alumno con nota inferior
 * a 5 se devuelve verdadero
 * @param lista Puntero a una estructura de tipo ListaAlumnos
 * @return Un bool con valor true si en la lista al menos un alumno tiene una
 * nota inferior a 5 y falso en caso contrario o si la lista esta vacía
 */
bool existeAlumnoSuspenso(const ListaAlumnos *lista) {
    if (estaVacia(lista)) return false;
    for (int i = 0; i < lista->num; i++) {
        if (lista->alumnos[i]->nota < 5) return true;
    }
    return false;
}


/**
 * Caso de uso de la aplicación elegido por el usuario mediante menu
 * cuando quiere añadir un nuevo alumno a la lista
 * El método debe comprobar si la lista proporcionada está llena o no
 * Si lo está debe mostrar un mensaje de error y terminar
 * Si no, procede con la llamada a las instrucciones que insertan un nuevo
 * alumno en la lista
 * @param lista Referencia a una estructura de tipo ListaAlumnos
 */
void addAlumno(ListaAlumnos &lista) {
    if (estaLlena(&lista)) {
        std::cout << "Lista llena, no se puede insertar el alumno" << endl;
        return;
    }
    addAlumno(&lista, inputAlumno());
}


/**
 * Imprime por consola en una línea de texto los datos de nombre y nota del
 * alumno proporcionado como argumento de llamada
 * @param alumno Puntero a estructura constante de tipo Alumno que apunta
 * al alumno que se va a mostrar por la consola
 */
void printAlumno(const Alumno *alumno) {
    if (alumno == nullptr) return;
    cout << "Nombre:" << alumno->nombre << "\tNota:" << alumno->nota << endl;
}


/**
 * Caso de uso de la aplicación elegido por el usuario mediante menu
 * cuando quiere visualizar los datos de la lista
 * El método debe comprobar si la lista proporcionada está vacía o no
 * Si está vacía debe mostrar un mensaje indicando que está vacía
 * Si no, delegando en el método printAlumno recorre e imprime uno tras
 * otro los alumnos de la lista
 * @param lista Referencia constante a una estructura de tipo ListaAlumnos
 */
void printLista(const ListaAlumnos &lista) {
    if (estaVacia(&lista)) {
        cout << "Lista vacia!!!" << endl;
        return;
    }
    cout << "ALUMNOS:" << endl;
    for (int i = 0; i < lista.num; i++) {
        printAlumno(lista.alumnos[i]);
    }
}


/**
 * Caso de uso de la aplicación elegido por el usuario mediante menu
 * cuando quiere visualizar la nota media de los alumnos
 * El método debe comprobar si la lista proporcionada está vacía o no
 * Si está vacía debe mostrar un mensaje indicando que está vacía y
 * no se va a calcular ninguna nota media
 * Si no, obtiene la media mediante una llamada al método que devuelve
 * la nota media de los alumnos de una lista de alumnos definido anteriormente
 * y la imprime por consola
 * @param lista Referencia constante a una estructura de tipo ListaAlumnos
 */
void printNotaMedia(const ListaAlumnos &lista) {
    if (estaVacia(&lista)) {
        cout << "Lista vacia, no se puede calcular ninguna media!!!" << endl;
        return;
    }
    const float media = getNotaMedia(&lista);
    cout << "Nota media: " << media << endl;
}


/**
 * Caso de uso de la aplicación elegido por el usuario mediante menu
 * cuando quiere visualizar los datos del alumno con mayor nota
 * El método debe comprobar si la lista proporcionada está vacía o no
 * Si está vacía debe mostrar un mensaje indicando que está vacía y
 * no se buscará ningún alumno
 * Si no, obtiene un puntero al alumno con mejor nota de una lista de alumnos
 * mediante una llamada al método que busca el alumno con la nota maxima
 * en una lista y si este puntero no es un puntero nulo imprime los datos
 * del alumno apoyándose el el método para imprimir los datos de un alumno
 * @param lista Referencia constante a una estructura de tipo ListaAlumnos
 */
void printAlumnoMaxNota(const ListaAlumnos &lista) {
    if (estaVacia(&lista)) {
        cout << "Lista vacia, no se buscara alumno!!!" << endl;
        return;
    }
    Alumno *alumno = getAlumnoMaxNota(&lista);
    if (alumno != nullptr) {
        printAlumno(alumno);
    }
}


/**
 * Caso de uso de la aplicación elegido por el usuario mediante menu
 * cuando quiere comprobar si existe algún alumno en la lista que no haya
 * aprobado
 * El método debe comprobar si la lista proporcionada está vacía o no
 * Si está vacía debe mostrar un mensaje indicando que está vacía y
 * no procede buscar
 * Si no, mediante una llamada al método que comprueba a partir de una lista
 * de alumnos si existe alguno suspenso o no obtiene el resultado y muestra por
 * pantalla un texto que diga Si en caso de ser verdadero o No en caso de ser falso
 * el resultado
 * @param lista Referencia constante a una estructura de tipo ListaAlumnos
 */
void printCheckAlumnoSuspenso(const ListaAlumnos &lista) {
    if (estaVacia(&lista)) {
        cout << "Lista vacia, no procede!!!" << endl;
        return;
    }
    bool alumnoSuspenso = existeAlumnoSuspenso(&lista);
    cout << "Hay alumnos suspendidos: " << (alumnoSuspenso ? "Si" : "No") << endl;
}


/**
 * Imprime el menú de opciones de la aplicación
 */
void printMenu() {
    cout << "\nOperaciones:" << endl;
    cout << "1. Insertar nuevo alumno" << endl;
    cout << "2. Imprimir lista de alumnos" << endl;
    cout << "3. Mostrar la nota media" << endl;
    cout << "4. Ver alumno con maxima nota" << endl;
    cout << "5. Comprobar si existe algun alumno suspendido" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion:";
}


/**
 * método principal y de entrada a la aplicación
 * Inicialización:
 * Crea una estructura Lista de alumnos mediante una llamada al método
 * para crear la lista y al cual le proporciona la capacidad deseada
 *
 * El programa entra en un bucle donde muestra un menu de opciones
 * al usuario y pide que introduzca la opción elegida por teclado
 * Según la opción elegida se llamará a la función que corresponda
 * con el caso de uso de para la operación elegida
 * Si la opción es 0, que equivale a salir, no se repite el bucle
 * y el programa continua para proceder con las operaciones de limpieza
 * antes de finalizar
 * Limpieza:
 * Libera toda la memoria dinámica reservada por el programa
 * @return
 */
int main() {
    const int capacidad = inputCapacidad();
    ListaAlumnos *lista = crearLista(capacidad);

    int opcion;
    do {
        printMenu();
        cin >> opcion;
        cin.get();
        switch (opcion) {
            case 1: addAlumno(*lista);
                break;
            case 2: printLista(*lista);
                break;
            case 3: printNotaMedia(*lista);
                break;
            case 4: printAlumnoMaxNota(*lista);
                break;
            case 5: printCheckAlumnoSuspenso(*lista);
                break;
            case 0:
                cout << "Saliendo del programa...";
                break;
            default: cout << "Opcion incorrecta!" << endl;
        }
    } while (opcion != 0);

    destruirLista(lista);
    lista = nullptr;
    return 0;
}
