#include "Node.h"
#include <string>
#include <climits>
#include <queue>

using namespace std;

// searching
int findNode (Node* nodes[20], string*l);
// adding
void addNode (Node* nodes[20], string* l);
void addEdge (Node* nodes[20], int adj[20][20], string* l_a, string* l_b, int w);
// removing
void removeNode (Node* nodes[20], int adj[20][20], string* l);
void removeEdge (Node* nodes[20], int adj[20][20], string* l_a, string* l_b);
// shortest path
void dijkstra (Node* nodes[20], int adj[20][20], string* l_a, string* l_b);
// debugging
void printAdj (Node* nodes[20], int adj[20][20]);



// main function
int main () {
  int adj[20][20];
  Node* nodes[20];
  for (int i = 0; i < 20; i++) {
    nodes[i] = NULL;
  }
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      adj[i][j] = -1;
    }
  }

  cout << "Beginning Graph Creator." << endl;
  bool running = true;

  while (running) {
    string input;
    cout << endl << "COMMANDS" << endl;
    cout << "ADD VERTEX - add vertex" << endl;
    cout << "ADD EDGE - add edge" << endl;
    cout << "RM VERTEX - remove vertex" << endl;
    cout << "RM EDGE - remove edge" << endl;
    cout << "SHORTEST PATH - find shortest path" << endl;
    cout << "PRINT - print adj matrix" << endl;
    cout << "QUIT - quit" << endl << endl;
    
    getline(cin, input);

    if (input == "ADD VERTEX") {
      string l_in; string* l; 
      cout << "Enter label for vertex:" << endl;
      getline (cin, l_in);
      l = new string(l_in);
      addNode (nodes, l);
    }
    else if (input == "ADD EDGE") {
      string l_a_in, l_b_in; string* l_a; string* l_b; int w;
      cout << "Enter label of first node:" << endl;
      getline (cin, l_a_in);
      cout << "Enter label of second node:" << endl;
      getline (cin, l_b_in);
      cout << "Enter weight of the edge:" << endl;
      cin >> w; cin.get();
      l_a = new string(l_a_in);
      l_b = new string(l_b_in);
      addEdge (nodes, adj, l_a, l_b, w);
    }
    else if (input == "RM VERTEX") {
      string l_in; string* l;
      cout << "Enter label for the vertex:" << endl;
      getline (cin, l_in);
      l = new string(l_in);
      removeNode (nodes, adj, l);
    }
    else if (input == "RM EDGE") {
      string l_a_in, l_b_in; string* l_a; string* l_b; 
      cout << "Enter label of first node:" << endl;
      getline (cin, l_a_in);
      cout << "Enter label of second node:" << endl;
      getline (cin, l_b_in);
      l_a = new string(l_a_in);
      l_b = new string(l_b_in);
      removeEdge (nodes, adj, l_a, l_b);
    }
    else if (input == "SHORTEST PATH") {
      string l_a_in, l_b_in; string* l_a; string* l_b;
      cout << "Enter label of the source node:" << endl;
      getline (cin, l_a_in);
      cout << "Enter label of the destination node:" << endl;
      getline (cin, l_b_in);
      l_a = new string(l_a_in);
      l_b = new string(l_b_in);
      dijkstra (nodes, adj, l_a, l_b);
    }
    else if (input == "PRINT") {
      printAdj(nodes, adj);
    }
    else if (input == "QUIT") {
      running = false;
    }
    else {
      cout << "Huh?" << endl;
    }
  }
  
  return 0;
}



// find a node's index from its label
int findNode (Node* nodes[20], string* l) {
  for (int i = 0; i < 20; i++) {
    if (nodes[i] && *nodes[i]->getLabel() == *l) {
      return i;
    }
  }
  cout << "Couldn't find that node." << endl;
  return -1;
}

// add node to graph
void addNode (Node* nodes[20], string* l) {
  Node* n = new Node(l);
  int i = 0;
  while (nodes[i]) { i++; }
  nodes[i] = n;
  return;
}

// add edge to adjacency table
void addEdge (Node* nodes[20], int adj[20][20], string* l_a, string* l_b, int w) {
  int a = findNode (nodes, l_a);
  int b = findNode (nodes, l_b);

  if (a == -1 || b == -1) { return; }
  
  adj[a][b] = w;
  return;
}

// remove node from the adjacency table
void removeNode (Node* nodes[20], int adj[20][20], string* l) {
  int n = findNode (nodes, l);

  if (n == -1) { return; }

  for (int i = 0; i < 20; i++) {
    adj[n][i] = -1;
    adj[i][n] = -1;
  }

  delete nodes[n];
  nodes[n] = NULL;

  return;
}

// remove edge from the adjacency table
void removeEdge (Node* nodes[20], int adj[20][20], string* l_a, string* l_b) {
  int a = findNode (nodes, l_a);
  int b = findNode (nodes, l_b);

  if (a == -1 || b == -1) { return; }
  
  adj[a][b] = -1;
  return;
}

// shortest path
void dijkstra (Node* nodes[20], int adj[20][20], string* l_a, string* l_b) {
  int dist[20], prev[20];
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  bool visited[20];

  int n = findNode(nodes, l_a);
  int d = findNode(nodes, l_b);
  if (n == -1 || d == -1) {
    return;
  }
  
  for (int i = 0; i < 20; i++) {
    dist[i] = INT_MAX;
    prev[i] = -1;
    visited[i] = false;
  }
  prev[n] = -1;
  dist[n] = 0;
  pq.push({0, n});

  while (!pq.empty()) {
    auto [w, cur] = pq.top();
    pq.pop();
    if (!visited[cur]) {
      visited[cur] = true;
      for (int i = 0; i < 20; i++) {
	if (adj[cur][i] != -1 && dist[i] > dist[cur] + adj[cur][i]) {
	  dist[i] = dist[cur] + adj[cur][i];
	  prev[i] = cur;
	  pq.push({dist[i], i});
	}
      }
    }
  }
  
  // backtrack print
  if (dist[d] != INT_MAX) {
    int path[20];
    int i = 0, cur = d;
    while (prev[cur] != -1 && cur != 0) {
      path[i] = cur;
      cur = prev[cur];
      i++;
    }
    path[i] = cur;
    
    cout << "Length of shortest path: " << dist[d] << endl;
    cout << "Path: ";
    for (int j = i; j >= 0; j--) {
      cout << *nodes[path[j]]->getLabel() << " ";
    }
    cout << endl;
  }
  else {
    cout << "No path exists." << endl;
  }
}

// print the adjacency table (debugging)
void printAdj (Node* nodes[20], int adj[20][20]) {
  cout << "   ";
  for (int i = 0; i < 20; i++) {
    if (nodes[i])
      cout << *nodes[i]->getLabel() << " ";
  }
  cout << endl;
  for (int i = 0; i < 20; i++) {
    if (nodes[i]) {
      cout << *nodes[i]->getLabel() << " ";
      for (int j = 0; j < 20; j++) {
	if (nodes[j])
	  cout << adj[i][j] << " ";
      }
      cout << endl;
    }
  }
}
