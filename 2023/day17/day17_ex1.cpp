#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node {
    int x
    int y
    int weight;
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
void findShortestPaths(vector<vector int> city, Node source, int n) {
    // crée un min-heap et pousse le nœud source ayant une distance de 0
    priority_queue<Node, vector<Node>, comp> min_heap;
    min_heap.push({source.x, source.y, 0});
 
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
 
    // la distance de la source à elle-même est nulle
    dist[source.y][source.x] = 0;
 
    // array booléen pour suivre les sommets pour lesquels le minimum le coût est déjà trouvé
    vector<Node> done(n);
    done.push_back(source);
 
    // stocke le prédécesseur d'un sommet (dans un chemin d'impression)
    vector<Node> prev(n);
 
    // exécuter jusqu'à ce que le Min-Heap soit vide
    while (!min_heap.empty()) {
        // Supprime et renvoie le meilleur sommet
        Node node = min_heap.top();
        min_heap.pop();
  
        // faire pour chaque voisin `v` de `u`
        for (int x = -1; x <= 1; x ++) {
            for (int y = -1; y <= 1; y ++) {
                if (x != 0 && y != 0)
                    Node v = city[node.y + y][node.x + x];
 
                // Etape détente
                if (done.find(v) != done.endl && (dist[node.y][node.x] + v.weight) < dist[v.y][v.x])
                {
                    dist[v.y][v.x] = dist[node.y][node.x] + v.weight;
                    prev[v] = u;
                    min_heap.push({v.x, v.y, dist[v.y][v.x]});
                }
            }
        }
 
        // marque le sommet `u` comme terminé pour qu'il ne soit plus repris
        done.push_back(node);
    }
 
    // for (int i = 0; i < n; i++)
    // {
    //     if (i != source && dist[i] != INT_MAX)
    //     {
    //         cout << "Path (" << source << " —> " << i << "): Minimum cost = "
    //              << dist[i] << ", Route = [";
    //         printPath(prev, i, source);
    //         cout << "]" << endl;
    //     }
    // }
}

int main () {
    ifstream myfile("day17_testInput.txt");
    // ifstream myfile("day17_input.txt");
    string                  input;
    vector<vector<int>      city;
    int             e_sum = 0;

    if (myfile.is_open()) {
        while (getline(myfile, input)) {
            city.push_back(input);
        }
    }
    cout << e_sum << endl;
}