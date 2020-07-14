#include "iostream"
#include "cstring"
#include "iomanip"

using namespace std;

const int longCad = 20;
struct costoPorArticulo
{
    char nombreArticulo[longCad];
    int cantidad;
    float precio;
    float costoPorArticulo;
};

void LeerFactura(costoPorArticulo[], int);/*Proceso que lee los datos sobre el nombre, la cantidad y el precio unitario
de cada artículo y los incorpora al arreglo.*/

void CalcularCPA(costoPorArticulo[], int);/*Proceso que CALCULA el Costo Por Artículo e incorpora este valor en el campo
correspondiente de cada artículo en cada casilla del arreglo.*/

void MostrarFactura(costoPorArticulo[], int);/*Proceso que despliega el contenido del arreglo. Mostrando los cuatro datos
de la estructura para cada artículo.*/

float TotalCompra(costoPorArticulo[], int);/*Función que retorna el costo total de la compra, que es la suma de los
costos de cada artículo.*/

void CinRango_float( float*, int, int);
/*Proceso que pide una variable tipo float, y comprueba que esta en un rango determinado. Si no lo esta la vuelve a pedir
el valor hasta que este entre en el rango*/

void CinRango_int( int*, int, int);
/*Proceso que pide una variable tipo int, y comprueba que esta en un rango determinado. Si no lo esta la vuelve a pedir
el valor hasta que este entre en el rango*/

int cantDigitos( int numero);
/*Funcion que retorna la cantidad de digitos que tiene un numero entero ingresado.
Servira para que los datos se muestren adecuadamente de forma alineada*/

void InsertarLineaDe( char, int );
/*Proceso que despliega en la salida el caracter que resive como parametro la cantidad de veces que resive
en el segundo parametro, Util para crear lineas con un determinado caracter, asi como para dejar cierta cantidad
de espacios entre dos salidas distintas*/

int main()
{
    int i, cantidadArticulos;
    cout << endl << "¿Cuantos productos distintos se ingresaran?" << endl;
    CinRango_int(&cantidadArticulos, 0, 100);
    costoPorArticulo Factura[cantidadArticulos];

    LeerFactura( Factura, cantidadArticulos);

    CalcularCPA( Factura, cantidadArticulos);

    MostrarFactura( Factura, cantidadArticulos);

    cout << "\nTotal a Pagar:  " << fixed << setprecision(2) << TotalCompra( Factura, cantidadArticulos);
    cout << "\n";
}

void LeerFactura( costoPorArticulo Factura[], int cantidad)
/*Un proceso que lee los datos sobre el nombre, la cantidad y el precio unitario
de cada artículo y los incorpora al arreglo.*/
{
    int i;/*Variable que sirve de contador*/

    for ( i = 0; i < cantidad; i++)
    {
        cout << "\nIngrese el nombre del Articulo numero " << i + 1 << ": ";

        cin.ignore();/*Sin  esta instruccion, el siguiente paso no funcionaba adecuadamente*/
        cin.getline(Factura[i].nombreArticulo, 40);

        cout << "Ingresa la cantidad de Articulos: ";
        CinRango_int(&Factura[i].cantidad, 0, 1000000);

        cout << "Ingresa el precio unitario por Articulo: ";
        CinRango_float(&Factura[i].precio, 0, 1000000);
    }
    
    InsertarLineaDe( '/', 100);/*separador*/
    cout << "\n\n";
}

void CalcularCPA( costoPorArticulo Factura[], int cantidad)
/*Un proceso que CALCULA el Costo Por Artículo e incorpora este valor en el campo
correspondiente de cada artículo en cada casilla del arreglo.*/
{
    int i;/*Variable que sirve de contador*/

    for ( i = 0; i < cantidad; i++)
    {
        Factura[i].costoPorArticulo = Factura[i].precio * Factura[i].cantidad;
    }
}

void MostrarFactura( costoPorArticulo Factura[], int cantidad)
/*Proceso que despliega el contenido del arreglo. Mostrando los cuatro datos
de la estructura para cada artículo.*/
{
    int i;/*Variable que sirve de contador*/

    cout << "\n\n            Factura NO 00026220\n";
    cout << "\nUniversidad Centroamericana Jose Simeon Cañas\n";
    cout << "\n   Materia: Fundamentos de Programacion\n";
    cout << "\nSeccion: 01     Encargado: Guillermo Gutierrez\n";

    InsertarLineaDe('-', 100);
    cout << "\n\nCantidad  Descripcion           Precio     Total$\n";

    InsertarLineaDe('-', 100);/*separador*/
    cout << "\n";

    for ( i = 0; i < cantidad; i++)
    {
        cout << Factura[i].cantidad;
        InsertarLineaDe(' ', 10 - cantDigitos(Factura[i].cantidad));
        /*Al hacer esta resta, el numero de caracteres desde el inicio hasta la siguiente salida, permanece constante
        EJ:
        11 tiene dos digitos(caracteres), 10 -2 = 8, Sumando esos 8 espacios en blanco + los digitos del principio se
        vuelve a obtener 10.
        
        111 tiene 3 digitos(caracteres), 10 -3 = 7, Sumando esos 7 espacios en blanco + los digitos del principio se
        vuelve a obtener 10.
        Gracias a esto todos los elemtos que "salgan" despues, permaneceran alineados independientemente la cantidad
        de digitos que hayan, siempre que estos no pasen de 10*/

        cout <<  Factura[i].nombreArticulo;
        InsertarLineaDe(' ', (25 - strlen(Factura[i].nombreArticulo))- cantDigitos(Factura[i].precio));
        /*Este caso cuenta  con dos restas. La primera tiene la misma funcion que la anterior
        La segunda resta los digitos entero(por ser valor int el parametro de cantDigitos) de la siguiente salida.
        Esto se hace para que queden alineados los puntos decimales, en lugar de las primeras cifras*/

        cout << fixed << setprecision(2) << Factura[i].precio;
        InsertarLineaDe(' ', 8 - cantDigitos(Factura[i].costoPorArticulo));
        /*Aqui no se plica el primer caso, por que en la salida anterior simpre habra dos decimales luego del punto
        (gracias al setprecision) por lo que no se perdera la alineacion.
        Igualmente se vuelve a aplicar el segundo caso, para que los puntos decimales permanescan alineados*/

        cout << fixed << setprecision(2) << Factura[i].costoPorArticulo << endl;
        
    }
    InsertarLineaDe('-', 100);/*separador*/
}

float TotalCompra( costoPorArticulo Factura[], int cantidad)
/*Función que retorna el costo total de la compra, que es la suma de los
costos de cada artículo.*/
{
    int i; /*Variable que sirve de contador*/
    double CompraTotal = 0;/*Variable que almacenara el valor de la sumatoria. Empieza con valor igual a 0*/

    for ( i = 0; i < cantidad; i++)
    {
        CompraTotal += Factura[i].costoPorArticulo;
    }

    return CompraTotal;
}

void CinRango_float( float* variable, int min, int max)
/*Proceso que pide una variable tipo float, y comprueba que esta en un rango determinado. Si no lo esta vuelve a pedir
el valor hasta que este entre en el rango*/
{
    cin >> * variable;

    while (*variable > max|| *variable < min)
    {
        cout << "La variable ingresada se sale del rango. Intente con otro valor: ";
        cin >> * variable;
    }
}

void CinRango_int( int* variable, int min, int max)
/*Proceso que pide una variable tipo int, y comprueba que esta en un rango determinado. Si no lo esta, vuelve a pedir
el valor hasta que este entre en el rango*/
{
    cin >> * variable;

    while( min >  *variable ||* variable > max)
    {
        cout << "La variable ingresada se sale del rango. Intente con otro valor: ";
        cin >> * variable;
    }
}

void InsertarLineaDe( char caracter, int i)
/*Proceso que despliega en la salida el caracter que resive como parametro la cantidad de veces que resive
en el segundo parametro, Util para crear lineas con un determinado caracter, asi como para dejar cierta cantidad
de espacios entre dos salidas distintas*/
{
    while (0 < i )
    {
        cout << caracter;
        i--;
    }
}

int cantDigitos( int numero)
/*Funcion que retorna la cantidad de digitos que tiene un numero entero ingresado.
Esa informacion servira para que los datos numericos se muestren adecuadamente de forma alineada*/
{
    float i = 1;
    int digitos = 0;

    do
    {
        digitos++;
        i *= 10;
    }while( numero / i >= 1);

    return digitos;
}