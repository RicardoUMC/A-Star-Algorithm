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

int main(void)
{
    //Creación de ciudades
    nodo_ptr_t Arad = new Nodo();
    AgregaNodo(Arad,"Arad",366);
    
    nodo_ptr_t Zerind = new Nodo();
    AgregaNodo(Zerind,"Zerind",374);
    
    nodo_ptr_t Oradea = new Nodo();
    AgregaNodo(Oradea,"Oradea",380);
    
    nodo_ptr_t Sibiu = new Nodo();
    Sibiu->ciudad = "Sibiu";
    Sibiu->puntaje_h = 253;
    
    nodo_ptr_t Fagaras = new Nodo();
    Fagaras->ciudad = "Fagaras";
    Fagaras->puntaje_h = 178;
    
    nodo_ptr_t Rimnicu = new Nodo();
    Rimnicu->ciudad = "Rimnicu Vilcea";
    Rimnicu->puntaje_h = 193;
    
    nodo_ptr_t Pitesti = new Nodo();
    Pitesti->ciudad = "Pitesti";
    Pitesti->puntaje_h = 98;
    
    nodo_ptr_t Timisoara = new Nodo();
    Timisoara->ciudad = "Timisoara";
    Timisoara->puntaje_h = 329;
    
    nodo_ptr_t Lugoj = new Nodo();
    Lugoj->ciudad = "Lugoj";
    Lugoj->puntaje_h = 244;
    
    nodo_ptr_t Mehadia = new Nodo();
    Mehadia->ciudad = "Mehadia";
    Mehadia->puntaje_h = 241;
    
    nodo_ptr_t Drobeta = new Nodo();
    Drobeta->ciudad = "Drobeta";
    Drobeta->puntaje_h = 242;
    
    nodo_ptr_t Craiova = new Nodo();
    Craiova->ciudad = "Craiova";
    Craiova->puntaje_h = 160;
    
    nodo_ptr_t Bucharest = new Nodo();
    Bucharest->ciudad = "Bucharest";
    Bucharest->puntaje_h = 0;
    
    nodo_ptr_t Giurgiu = new Nodo();
    Giurgiu->ciudad = "Giurgiu";
    Giurgiu->puntaje_h = 77;
    

    // Creación de las aristas conexiones entre ciudades

    // Arad
    arista_ptr_t a1 = new Arista();
    a1->objetivo = Zerind;
    a1->costo = 75;

    arista_ptr_t a2 = new Arista();
    a2->objetivo = Sibiu;
    a2->costo = 140;
    
    arista_ptr_t a3 = new Arista();
    a3->objetivo = Timisoara;
    a3->costo = 118;

    Arad->adyacentes.push_back(a1);
    Arad->adyacentes.push_back(a2);
    Arad->adyacentes.push_back(a3);

    // Zerind
    arista_ptr_t a4 = new Arista();
    a4->objetivo = Arad;
    a4->costo = 75;

    arista_ptr_t a5 = new Arista();
    a5->objetivo = Oradea;
    a5->costo = 71;
    
    Zerind->adyacentes.push_back(a4);
    Zerind->adyacentes.push_back(a5);

    // Oradea
    arista_ptr_t a6 = new Arista();
    a6->objetivo = Zerind;
    a6->costo = 71;

    arista_ptr_t a7 = new Arista();
    a7->objetivo = Sibiu;
    a7->costo = 151;

    Oradea->adyacentes.push_back(a6);
    Oradea->adyacentes.push_back(a7);

    // Sibiu
    arista_ptr_t a8 = new Arista();
    a8->objetivo = Arad;
    a8->costo = 140;

    arista_ptr_t a9 = new Arista();
    a9->objetivo = Oradea;
    a9->costo = 151;

    arista_ptr_t a10 = new Arista();
    a10->objetivo = Fagaras;
    a10->costo = 99;

    arista_ptr_t a11 = new Arista();
    a11->objetivo = Rimnicu;
    a11->costo = 80;

    Sibiu->adyacentes.push_back(a8);
    Sibiu->adyacentes.push_back(a9);
    Sibiu->adyacentes.push_back(a10);
    Sibiu->adyacentes.push_back(a11);

    // Fagaras
    arista_ptr_t a12 = new Arista();
    a12->objetivo = Sibiu;
    a12->costo = 99;

    arista_ptr_t a13 = new Arista();
    a13->objetivo = Bucharest;
    a13->costo = 211;

    Fagaras->adyacentes.push_back(a12);
    Fagaras->adyacentes.push_back(a13);

    // Rimnicu Vilcea
    arista_ptr_t a14 = new Arista();
    a14->objetivo = Sibiu;
    a14->costo = 80;

    arista_ptr_t a15 = new Arista();
    a15->objetivo = Craiova;
    a15->costo = 146;

    arista_ptr_t a16 = new Arista();
    a16->objetivo = Pitesti;
    a16->costo = 97;

    Rimnicu->adyacentes.push_back(a14);
    Rimnicu->adyacentes.push_back(a15);
    Rimnicu->adyacentes.push_back(a16);

    // Pitesti
    arista_ptr_t a17 = new Arista();
    a17->objetivo = Rimnicu;
    a17->costo = 97;

    arista_ptr_t a18 = new Arista();
    a18->objetivo = Craiova;
    a18->costo = 138;

    arista_ptr_t a19 = new Arista();
    a19->objetivo = Bucharest;
    a19->costo = 101;

    Pitesti->adyacentes.push_back(a17);
    Pitesti->adyacentes.push_back(a18);
    Pitesti->adyacentes.push_back(a19);

    // Timisoara
    arista_ptr_t a20 = new Arista();
    a20->objetivo = Arad;
    a20->costo = 118;

    arista_ptr_t a21 = new Arista();
    a21->objetivo = Lugoj;
    a21->costo = 111;

    Timisoara->adyacentes.push_back(a20);
    Timisoara->adyacentes.push_back(a21);

    // Lugoj
    arista_ptr_t a22 = new Arista();
    a22->objetivo = Timisoara;
    a22->costo = 111;

    arista_ptr_t a23 = new Arista();
    a23->objetivo = Mehadia;
    a23->costo = 70;

    Lugoj->adyacentes.push_back(a22);
    Lugoj->adyacentes.push_back(a23);

    // Mehadia
    arista_ptr_t a24 = new Arista();
    a24->objetivo = Lugoj;
    a24->costo = 70;

    arista_ptr_t a25 = new Arista();
    a25->objetivo = Mehadia;
    a25->costo = 75;

    Mehadia->adyacentes.push_back(a24);
    Mehadia->adyacentes.push_back(a25);

    // Drobeta
    arista_ptr_t a26 = new Arista();
    a26->objetivo = Mehadia;;
    a26->costo = 75;

    arista_ptr_t a27 = new Arista();
    a27->objetivo = Craiova;
    a27->costo = 120;

    Drobeta->adyacentes.push_back(a26);
    Drobeta->adyacentes.push_back(a27);

    // Craiova
    arista_ptr_t a28 = new Arista();
    a28->objetivo = Drobeta;
    a28->costo = 120;

    arista_ptr_t a29 = new Arista();
    a29->objetivo = Rimnicu;
    a29->costo = 146;

    arista_ptr_t a30 = new Arista();
    a30->objetivo = Pitesti;
    a30->costo = 138;

    Craiova->adyacentes.push_back(a28);
    Craiova->adyacentes.push_back(a29);
    Craiova->adyacentes.push_back(a30);

    for (size_t i = 0; i < Arad->adyacentes.size(); i++)
    {
        cout << Arad->adyacentes[i]->objetivo->ciudad << endl;
    }

    return 0;
}