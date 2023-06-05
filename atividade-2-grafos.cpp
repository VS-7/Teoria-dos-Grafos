#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <sstream>

#define INF INT_MAX

using namespace std;

vector<vector<int>> floydWarshall(const vector<vector<int>>& graph) {
    int num_vertices = graph.size();
    vector<vector<int>> dist(num_vertices, vector<int>(num_vertices, INF));

    // Inicialização das distâncias conhecidas
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (i == j) {
                // faz o tratamento da diagonal da matriz preenchida com zeros.
                dist[i][j] = 0; 
            } else if (graph[i][j] != 0) {
                dist[i][j] = graph[i][j];
            }
        }
    }

    // Calcula as distâncias mínimas
    for (int k = 0; k < num_vertices; k++) {
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    //Faz a matriz de pesos
                    //dist[i][j] = dist[i][k] + dist[k][j];
                    //
                    dist[i][j] = 1;
                }
            }
        }
    }

    return dist;
}

// Função auxiliar para imprimir a matriz de distâncias
void printMatrix(const vector<vector<int>>& matrix) {
    int num_vertices = matrix.size();
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (matrix[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Função para ler a matriz de um arquivo
vector<vector<int>> readMatrixFromFile(const string& filename) {
    vector<vector<int>> matrix;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<int> row;
            stringstream ss(line);
            int value;
            while (ss >> value) {
                row.push_back(value);
            }
            matrix.push_back(row);
        }
        file.close();
    }
    return matrix;
}

int main() {
    // Exemplo de utilização
    vector<vector<int>> graph = readMatrixFromFile("matrix.txt");

    vector<vector<int>> result = floydWarshall(graph);

    // Imprime a matriz de fecho transitivo
    printMatrix(result);

    return 0;
}