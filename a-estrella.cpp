#include <iostream>
#include <string>
#include <vector>
#include <vector>

using namespace std;

struct Arista
{
    struct Nodo *objetivo;
    double costo;
};

struct Nodo
{
    string ciudad;
    double puntaje_g;
    double puntaje_h;
    double puntaje_f = 0;

    vector<Arista*> adyacentes;

    struct Nodo* padre;
};

typedef Nodo *nodo_ptr_t;
typedef Arista *arista_ptr_t;

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

void imprimeCiudades(nodo_ptr_t &nodo)
{
    cout << endl << "Ciudades cercanas a " + nodo->ciudad << ":\n";
    for (size_t i = 0; i < nodo->adyacentes.size(); i++)
    {
        cout << nodo->adyacentes[i]->objetivo->ciudad << '\n';
    }
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

    // Giurgiu
    AsociaArista(Giurgiu, Bucharest, 90);

    return 0;
}