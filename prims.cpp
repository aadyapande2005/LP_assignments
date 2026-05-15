#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

// Function for Prim's MST
void primMST(int V, vector<pii> adj[])
{
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);

    // Start from vertex 0
    key[0] = 0;
    pq.push({0, 0}); // {weight, vertex}

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        // Traverse adjacent vertices
        for (auto edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;

            // Update if smaller weight found
            if (!inMST[v] && weight < key[v])
            {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    // Print MST
    cout << "Edge \tWeight\n";

    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i
             << " \t" << key[i] << endl;
    }
}

int main()
{
    int V = 5;

    vector<pii> adj[V];

    // Adding edges
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});

    adj[0].push_back({3, 6});
    adj[3].push_back({0, 6});

    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});

    adj[1].push_back({3, 8});
    adj[3].push_back({1, 8});

    adj[1].push_back({4, 5});
    adj[4].push_back({1, 5});

    adj[2].push_back({4, 7});
    adj[4].push_back({2, 7});

    adj[3].push_back({4, 9});
    adj[4].push_back({3, 9});

    primMST(V, adj);

    return 0;
}