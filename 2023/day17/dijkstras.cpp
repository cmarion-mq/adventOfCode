
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
 
// Structure de données pour stocker une arête de graphe
struct Edge {
    int source, dest, weight;
};
 
// Structure de données pour stocker un nœud de heap
struct Node {
    int vertex, weight;
};
 
// Une classe pour représenter un objet graph
class Graph
{
public:
    // un vector de vectors de `Edge` pour représenter une liste de contiguïté
    vector<vector<Edge>> adjList;
 
    // Constructeur de graphe
    Graph(vector<Edge> const &edges, int n)
    {
        // redimensionne le vector pour contenir `n` éléments de type vector<Edge>
        adjList.resize(n);
 
        // ajoute des arêtes au graphe orienté
        for (Edge const &edge: edges)
        {
            // insère à la fin
            adjList[edge.source].push_back(edge);
        }
    }
};
 
void printPath(vector<int> const &prev, int i, int source)
{
    if (i < 0) {
        return;
    }
    printPath(prev, prev[i], source);
    if (i != source) {
        cout << ", ";
    }
    cout << i;
}
 
// Objet de comparaison à utiliser pour ordonner le heap
struct comp
{
    bool operator()(const Node &lhs, const Node &rhs) const {
        return lhs.weight > rhs.weight;
    }
};
 
// Exécute l'algorithme de Dijkstra sur le graphe donné
void findShortestPaths(Graph const &graph, int source, int n)
{
    // crée un min-heap et pousse le nœud source ayant une distance de 0
    priority_queue<Node, vector<Node>, comp> min_heap;
    min_heap.push({source, 0});
 
    // définit la distance initiale de la source à `v` comme infini
    vector<int> dist(n, INT_MAX);
 
    // la distance de la source à elle-même est nulle
    dist[source] = 0;
 
    // array booléen pour suivre les sommets pour lesquels le minimum
    // le coût est déjà trouvé
    vector<bool> done(n, false);
    done[source] = true;
 
    // stocke le prédécesseur d'un sommet (dans un chemin d'impression)
    vector<int> prev(n, -1);
 
    // exécuter jusqu'à ce que le Min-Heap soit vide
    while (!min_heap.empty())
    {
        // Supprime et renvoie le meilleur sommet
        Node node = min_heap.top();
        min_heap.pop();
 
        // récupère le numéro du sommet
        int u = node.vertex;
 
        // faire pour chaque voisin `v` de `u`
        for (auto i: graph.adjList[u])
        {
            int v = i.dest;
            int weight = i.weight;
 
            // Etape détente
            if (!done[v] && (dist[u] + weight) < dist[v])
            {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                min_heap.push({v, dist[v]});
            }
        }
 
        // marque le sommet `u` comme terminé pour qu'il ne soit plus repris
        done[u] = true;
    }
 
    for (int i = 0; i < n; i++)
    {
        if (i != source && dist[i] != INT_MAX)
        {
            cout << "Path (" << source << " —> " << i << "): Minimum cost = "
                 << dist[i] << ", Route = [";
            printPath(prev, i, source);
            cout << "]" << endl;
        }
    }
}
 
int main()
{
    // initialise les bords selon le diagramme ci-dessus
    // (u, v, w) représente le bord du sommet `u` au sommet `v` ayant le poids `w`
    vector<Edge> edges =
    {
        {0, 1, 10}, {0, 4, 3}, {1, 2, 2}, {1, 4, 4}, {2, 3, 9},
        {3, 2, 7}, {4, 1, 1}, {4, 2, 8}, {4, 3, 2}
    };
 
    // nombre total de nœuds dans le graphe (étiquetés de 0 à 4)
    int n = 5;
 
    // construit le graphe
    Graph graph(edges, n);
 
    // exécute l'algorithme de Dijkstra à partir de chaque nœud
    for (int source = 0; source < n; source++) {
        findShortestPaths(graph, source, n);
    }
 
    return 0;
}



//https://www.techiedelight.com/fr/single-source-shortest-paths-dijkstras-algorithm/