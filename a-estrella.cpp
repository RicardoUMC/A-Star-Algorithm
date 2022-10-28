#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>

using namespace std;

struct Arista
{
    struct Nodo *objetivo;
    double costo;
};

typedef Arista *arista_ptr_t;

struct Nodo
{
    string ciudad;
    double puntaje_g;
    double puntaje_h;
    double puntaje_f = 0;

    vector<arista_ptr_t> adyacentes;

    Nodo* padre;
};

typedef Nodo* nodo_ptr_t;

struct Lista
{
    nodo_ptr_t nodo_asociado;
    Lista* nodo_sig;
};

typedef Lista* lista_ptr_t;

void AgregaNodo(nodo_ptr_t &nodo, string ciudad, double heuristica);
void AsociaArista(nodo_ptr_t &origen, nodo_ptr_t &destino, double costo);
void ImprimeCiudades(nodo_ptr_t &nodo);

void ImprimeLista(lista_ptr_t &lista, string nombre)
{
    cout << "Lista " + nombre << ":\n";
    for (lista_ptr_t i = lista; i != NULL; i = i->nodo_sig)
    {
        cout << i->nodo_asociado->ciudad << "->";
    }
    cout << endl;
}

void AgregaEnLista(lista_ptr_t &lista, nodo_ptr_t &agregado, bool prioridad)
{
    if (lista == NULL)
    {
        lista = new(Lista);
        lista->nodo_asociado = agregado;
        lista->nodo_sig = NULL;
        cout << "Inserta al inicio (p)" << endl;
    }

    else
    {
        lista_ptr_t auxiliar = new(Lista);

        lista_ptr_t actual = lista;
        while (actual->nodo_sig != NULL && prioridad && (agregado->puntaje_f >= actual->nodo_sig->nodo_asociado->puntaje_f))
        {
            actual = actual->nodo_sig;
        }

        if (actual == lista && agregado->puntaje_f <= actual->nodo_asociado->puntaje_f)
        {
            cout << "Inserta al inicio" << endl;
            auxiliar->nodo_sig = lista;
            lista = auxiliar;
        }
        else if (actual->nodo_sig == NULL)
        {
            cout << "Inserta al final" << endl;
            auxiliar->nodo_sig = NULL;
            actual->nodo_sig = auxiliar;
        }
        else if (actual->nodo_sig != NULL)
        {
            cout << "Inserta en medio" << endl;
            auxiliar->nodo_sig = actual->nodo_sig;
            actual->nodo_sig = auxiliar;
        }
    } 

    // lista->nodo_asociado->puntaje_g = agregado->puntaje_g;
    // lista->nodo_asociado->puntaje_h = agregado->puntaje_h;
    // lista->nodo_asociado->puntaje_f = agregado->puntaje_f;
    // lista->nodo_asociado->ciudad = agregado->ciudad;
    // lista->nodo_asociado->adyacentes = agregado->adyacentes;
}

nodo_ptr_t EliminaEnLista(lista_ptr_t &lista, nodo_ptr_t eliminado)
{
    lista_ptr_t auxiliar = new(Lista);
    lista_ptr_t actual = lista;
    nodo_ptr_t regreso = new(Nodo);

    while (actual->nodo_sig != NULL && actual->nodo_asociado != eliminado)
    {
        auxiliar = actual;
        actual = actual->nodo_sig;
    }

    regreso = actual->nodo_asociado;

    if (actual == lista && actual->nodo_asociado == eliminado)
    {
        if (actual->nodo_sig != NULL)
        {
            lista = actual->nodo_sig;
        }
        else
        {
            lista = NULL;
        }
        delete actual;
        actual = lista;
        cout << "Nodo eliminado correctamente al inicio." << endl;
    }
    else if (actual->nodo_sig == NULL && actual->nodo_asociado == eliminado)
    {
        auxiliar->nodo_sig = NULL;
        delete actual;
        actual = auxiliar;
        cout << "Nodo eliminado correctamente al final." << endl;
    }
    else if (actual->nodo_sig != NULL)
    {
        auxiliar->nodo_sig = actual->nodo_sig;
        delete actual;
        actual = auxiliar;
        cout << "Nodo eliminado correctamente en medio." << endl;
    }
    return regreso;
}

bool BuscaEnLista(lista_ptr_t &lista, nodo_ptr_t &nodo)
{
    lista_ptr_t auxiliar;
    lista_ptr_t actual = lista;

    bool presente = false;
    while (actual->nodo_sig != NULL && actual->nodo_asociado != nodo)
    {
        auxiliar = actual;
        actual = actual->nodo_sig;
    }

    if (actual->nodo_asociado == nodo) presente = true;

    return presente;
}

void A_Estrella(nodo_ptr_t &inicio, nodo_ptr_t &final)
{
    lista_ptr_t col_prio = NULL;
    lista_ptr_t explorados = NULL;

    inicio->puntaje_g = 0;

    AgregaEnLista(col_prio, inicio, true);

    // ImprimeLista(col_prio, "Prioridad");
    bool encontrado = false;
    while (col_prio != NULL && !encontrado)
    {
        nodo_ptr_t presente = new (Nodo);
        presente = EliminaEnLista(col_prio, col_prio->nodo_asociado);

        AgregaEnLista(explorados, presente, false);

        if (presente == final) encontrado = true;

        for (size_t i = 0; i < presente->adyacentes.size(); i++)
        {
            nodo_ptr_t hijo = new Nodo();
            hijo = presente->adyacentes[i]->objetivo;
            double costo = presente->adyacentes[i]->costo;
            double puntaje_g_temp = presente->puntaje_g + costo;
            double puntaje_f_temp = puntaje_g_temp + hijo->puntaje_h;

            /*if hijo node has been evaluated and
            the newer f_score is higher, skip*/
            if (BuscaEnLista(explorados, hijo) && (puntaje_f_temp >= hijo->puntaje_f)) continue;

            /*else if hijo node is not in queue or
            newer f_score is lower*/
            else if(BuscaEnLista(col_prio, hijo) || puntaje_f_temp < hijo->puntaje_f) 
            {
                hijo->padre = presente;
                hijo->puntaje_g = puntaje_g_temp;
                hijo->puntaje_f = puntaje_f_temp;
                if (BuscaEnLista(col_prio, hijo)) EliminaEnLista(col_prio, hijo);

                AgregaEnLista(col_prio, hijo, true);
            }
        }
    }
    
}

void ImprimeCamino(nodo_ptr_t meta)
{
    vector<string> camino;
    for (nodo_ptr_t nodo = meta; nodo != NULL; nodo = nodo->padre)
        camino.push_back(nodo->ciudad);

    for (auto i = camino.cbegin(); i != camino.cend(); i++)
        cout << *i << endl;
}


int main(void)
{
    //Creación de ciudades
    nodo_ptr_t Arad = new Nodo();
    AgregaNodo(Arad, "Arad", 366);
    
    nodo_ptr_t Zerind = new Nodo();
    AgregaNodo(Zerind, "Zerind", 374);
    
    nodo_ptr_t Oradea = new Nodo();
    AgregaNodo(Oradea, "Oradea", 380);
    
    nodo_ptr_t Sibiu = new Nodo();
    AgregaNodo(Sibiu, "Sibiu", 253);
    
    nodo_ptr_t Fagaras = new Nodo();
    AgregaNodo(Fagaras, "Fagaras", 178);
    
    nodo_ptr_t Rimnicu = new Nodo();
    AgregaNodo(Rimnicu, "Rimnicu Vilcea", 193);
    
    nodo_ptr_t Pitesti = new Nodo();
    AgregaNodo(Pitesti, "Pitesti", 98);
    
    nodo_ptr_t Timisoara = new Nodo();
    AgregaNodo(Timisoara, "Timisoara", 329);
    
    nodo_ptr_t Lugoj = new Nodo();
    AgregaNodo(Lugoj, "Lugoj", 244);
    
    nodo_ptr_t Mehadia = new Nodo();
    AgregaNodo(Mehadia, "Mehadia", 241);
    
    nodo_ptr_t Drobeta = new Nodo();
    AgregaNodo(Drobeta, "Drobeta", 242);
    
    nodo_ptr_t Craiova = new Nodo();
    AgregaNodo(Craiova, "Craiova", 160);
    
    nodo_ptr_t Bucharest = new Nodo();
    AgregaNodo(Bucharest, "Bucharest", 0);
    
    nodo_ptr_t Giurgiu = new Nodo();
    AgregaNodo(Giurgiu, "Giurgiu", 77);

    nodo_ptr_t Urziceni = new Nodo();
    AgregaNodo(Urziceni, "Urziceni", 80);

    nodo_ptr_t Hirsova = new Nodo();
    AgregaNodo(Hirsova, "Hirsova", 151);

    nodo_ptr_t Eforie = new Nodo();
    AgregaNodo(Eforie, "Eforie", 161);

    nodo_ptr_t Vaslui = new Nodo();
    AgregaNodo(Vaslui, "Vaslui", 199);

    nodo_ptr_t Iasi = new Nodo();
    AgregaNodo(Iasi, "Iasi", 226);

    nodo_ptr_t Neamt = new Nodo();
    AgregaNodo(Neamt, "Neamt", 234);

    // Creación de las aristas conexiones entre ciudades

    // Arad
    AsociaArista(Arad, Zerind, 75);
    AsociaArista(Arad, Sibiu, 140);
    AsociaArista(Arad, Timisoara, 118);

    // Zerind
    AsociaArista(Zerind, Arad, 75);
    AsociaArista(Zerind, Oradea, 71);
    
    // Oradea
    AsociaArista(Oradea, Zerind, 71);
    AsociaArista(Oradea, Sibiu, 151);

    // Sibiu
    AsociaArista(Sibiu, Arad, 140);
    AsociaArista(Sibiu, Oradea, 151);
    AsociaArista(Sibiu, Fagaras, 99);
    AsociaArista(Sibiu, Rimnicu, 80);

    // Fagaras
    AsociaArista(Fagaras, Sibiu, 99);
    AsociaArista(Fagaras, Bucharest, 211);
    
    // Rimnicu Vilcea
    AsociaArista(Rimnicu, Sibiu, 80);
    AsociaArista(Rimnicu, Craiova, 146);
    AsociaArista(Rimnicu, Pitesti, 97);
    
    // Pitesti
    AsociaArista(Pitesti, Rimnicu, 97);
    AsociaArista(Pitesti, Craiova, 138);
    AsociaArista(Pitesti, Bucharest, 101);
    
    // Timisoara
    AsociaArista(Timisoara, Arad, 118);
    AsociaArista(Timisoara, Lugoj, 111);
    
    // Lugoj
    AsociaArista(Lugoj, Timisoara, 111);
    AsociaArista(Lugoj, Mehadia, 70);
    
    // Mehadia
    AsociaArista(Mehadia, Lugoj, 70);
    AsociaArista(Mehadia, Mehadia, 75);
    
    // Drobeta
    AsociaArista(Drobeta, Mehadia, 75);
    AsociaArista(Drobeta, Craiova, 120);

    // Craiova
    AsociaArista(Craiova, Drobeta, 120);
    AsociaArista(Craiova, Rimnicu, 146);
    AsociaArista(Craiova, Pitesti, 138);
    
    // Bucharest
    AsociaArista(Bucharest, Pitesti, 101);
    AsociaArista(Bucharest, Fagaras, 211);
    AsociaArista(Bucharest, Giurgiu, 90);
    AsociaArista(Bucharest, Urziceni, 85);

    // Giurgiu
    AsociaArista(Giurgiu, Bucharest, 90);

    // Urziceni
    AsociaArista(Urziceni, Bucharest, 85);
    AsociaArista(Urziceni, Hirsova, 98);
    AsociaArista(Urziceni, Vaslui, 142);

    // Hirsova
    AsociaArista(Hirsova, Urziceni, 98);
    AsociaArista(Hirsova, Eforie, 86);

    // Eforie
    AsociaArista(Eforie, Hirsova, 86);

    // Vaslui
    AsociaArista(Vaslui, Urziceni, 142);
    AsociaArista(Vaslui, Iasi, 92);

    // Iasi
    AsociaArista(Iasi, Vaslui, 92);
    AsociaArista(Iasi, Neamt, 87);

    // Neamt
    AsociaArista(Neamt, Iasi, 87);

    // ImprimeCiudades(Bucharest);

    A_Estrella(Arad, Bucharest);

    ImprimeCamino(Bucharest);


    cout << "TERMINA EL PROGRAMA..." << endl;
    return 0;
}

void AgregaNodo(nodo_ptr_t &nodo, string ciudad, double heuristica)
{
    nodo->ciudad = ciudad;
    nodo->puntaje_h = heuristica;
}

void AsociaArista(nodo_ptr_t &origen, nodo_ptr_t &destino, double costo)
{
    arista_ptr_t auxiliar = new Arista();
    auxiliar->objetivo = destino;
    auxiliar->costo = costo;

    origen->adyacentes.push_back(auxiliar);
}

void ImprimeCiudades(nodo_ptr_t &nodo)
{
    cout << endl
         << "Ciudades cercanas a " + nodo->ciudad << ":\n";
    for (size_t i = 0; i < nodo->adyacentes.size(); i++)
    {
        cout << nodo->adyacentes[i]->objetivo->ciudad << '\n';
    }
}