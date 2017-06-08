#include "P4_graph.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <functional>
#include <set>

Graph::Graph(): _ger(false), _gew(false)
{
    _anzKnoten = 0;
    _nodes.clear();
}

Graph::~Graph()
{
    for (int i = 0; i < _nodes.size(); i++) {
        delete _nodes[i];
    }
    _nodes.clear();
}

//Get the node pointer by given key
GraphNode* Graph::GetNodeByKey(int key)
{
    for(int i = 0; i < _anzKnoten; i++)
    {
        GraphNode* currentNode = _nodes[i];
        if(currentNode->_key == key)
        {
            return currentNode;
        }
    }
    return nullptr;
}

//iterate all nodes and set _visited to false
void Graph::setAllUnvisited()
{
    for(int i = 0; i < _nodes.size(); i++)
    {
        GraphNode* currentNode = _nodes[i];
        currentNode->_visited = false;
    }
}

//Check if all nodes are set to visited
bool Graph::checkVisited()
{
    for(int i = 0; i < _nodes.size(); i++)
    {
        GraphNode* currentNode = _nodes[i];
        if(currentNode->_visited == false)
            return false;
    }
    return true;
}

bool Graph::init(std::string path)
{

    std::ifstream file;
    file.open(path, std::ios_base::in);

    if (!file)
    {
        std::cout << "Cannot open file." << std::endl;
    }
    else
    {
        std::cout << "Start reading" << std::endl;

        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);

        std::cout << "Insert _anzKnoten" << std::endl;
        iss >> _anzKnoten;

        std::cout << "Create all Nodes" << std::endl;
        //Alle Knoten anlegen
        for(int i = 0; i < _anzKnoten; i++)
        {
            GraphNode* currentNode = new GraphNode(i);
            _nodes.push_back(currentNode);
        }

        std::cout << "Start creating edges" << std::endl;
        while (std::getline(file, line))
        {
            std::istringstream edges(line);
            int from, value, to;
            if (!(edges >> from >> to >> value)) { break; } // error

            std::cout << "From: " << from << " To: " << to << " Value: " << value << std::endl;
            GraphNode* currentNode = GetNodeByKey(from);
            GraphNode* currentNeighbour = GetNodeByKey(to);
            //Hinrichrung:
            GraphNode::edge edge(currentNeighbour, value);
            currentNode->_edges.push_back(edge);
            //Rückrichtung:
            GraphNode::edge backEdge(currentNode, value);
            currentNeighbour->_edges.push_back(backEdge);
        }
       return true;
    }

    return false;
}

bool Graph::print()
{
    if(_nodes.empty()) return false;
    //Print with Node ID: 1st neighbour, 2nd neighbour ...
    for(int i = 0; i < _anzKnoten; i++)
    {
        GraphNode* currentNode = _nodes[i];
        std::cout << currentNode->_key << " ";
        for(int k = 0; k < currentNode->_edges.size(); k++)
        {
            if(!currentNode->_edges.empty()){
                GraphNode::edge currentEdge = currentNode->_edges[k];
                std::cout << " -> " << currentEdge.node->_key << " [" << currentEdge.value << "] ";
            }
        }
        std::cout << std::endl;

    }

    return true;
}

//Implement here the depth-/breadfirstthsearch and Prim & Kruskal

//Implement this:
bool Graph::depthSearchRek(int startKey)
{
    return true;
}

bool Graph::breadthSearchIter(int startKey)
{
    std::queue<GraphNode*> st;
    st.push(_nodes[startKey]);

    // Zurücksetzten aller besuchten Knoten
    setAllUnvisited();

    while (!st.empty())
    {
        // Nehme obersten Knoten und Lösche diesen
        std::stack<GraphNode*>::value_type n = st.front();
        st.pop();

        // Knoten als besucht makieren.
        n->_visited = true;

        // Alle Kanten zur Queue hinzufügen
        for (auto e : n->_edges)
        {
            // nur die Hinzufuegen die noch nicht besucht worden sind.
            //if(!_nodes[n->_key]->_visited)
            if (!e.node->_visited)
            {
                //e.node->_visited = true;
                st.push(e.node);
            }
                
        }
    }

    // Nachträglicher check unserer Breitensuche
    return checkVisited();
}

bool Graph::depthSearchIter(int startKey)
{
    std::stack<GraphNode*> st;
    st.push(_nodes[startKey]);

    // Zurücksetzten aller besuchten Knoten
    setAllUnvisited();

    while (!st.empty())
    {
        // Nehme obersten Knoten und Lösche diesen
        std::stack<GraphNode*>::value_type n = st.top();
        st.pop();

        // Knoten als besucht makieren.
        n->_visited = true;

        // Alle Kanten zum Stack hinzufügen
        for (auto e : n->_edges)
        {
            // nur die Hinzufuegen die noch nicht besucht worden sind.
            //if(!_nodes[n->_key]->_visited)
            if (!e.node->_visited)
            {
                //e.node->_visited = true;
                st.push(e.node);
            }

        }
    }

    // Nachträglicher check unserer Tiefensuche
    return checkVisited();
}

void breadthSearchHelper(GraphNode* x)
{
    x->_visited = true;

    std::cout << x->_key << ", ";

    for (auto e : x->_edges)
    {
        if (!e.node->_visited)
            breadthSearchHelper(e.node);
    }
}

bool Graph::breadthSearchRek(int startKey)
{
    //reset all nodes
    setAllUnvisited();

    breadthSearchHelper(_nodes[startKey]);
    std::cout << std::endl;

    //check our breadth search
    return checkVisited();
}

double Graph::prim(int startKey)
{
    std::priority_queue<GraphNode::edge, std::vector<GraphNode::edge>, std::greater<GraphNode::edge>> q;

    // Reset 
    for (auto n : _nodes)
    {
        n->_prev = nullptr;
        n->_visited = false;
        n->_distance = std::numeric_limits<double>::max(); // Auf unendlich setzen
    }

    // Hinzufügen unser Kanten vom Startknoten zur PriorityQueue
    for (auto e : _nodes[startKey]->_edges)
        q.push(e);

    // Starte von unserem Startknoten mit einer Distanz von 0
    // Knoten auf besucht setzen
    GraphNode* curr = _nodes[startKey];
    curr->_distance = 0.0;
    curr->_visited = true;

    // Nun zu allen Kanten gehen
    while (!q.empty())
    {
        // Entnehme die Kante mit dem kleinsten Gewicht
        GraphNode::edge e = q.top();
        q.pop();

        // Überpüfen ob wir schon an diesem Knoten waren
        if (!e.node->_visited)
        {
            // Diestanz zu diesem Knoten setzten
            e.node->_distance = e.value;
            e.node->_prev = curr;
            e.node->_visited = true;
            curr = e.node;

            // Nun alle neu dazugekommenen Kanten zur PQ hinzufügen
            for (auto e : curr->_edges)
            {
                q.push(e);
            }
        }
    }

    // Spanngröße unseres errechneten Baumes auslesen.
    double res = 0.0;

    for (auto n : _nodes)
        res += n->_distance;

    return res;
}

int Graph::getId(GraphNode* n) const
{
    for (int i = 0; i < _nodes.size(); ++i)
    {
        if (_nodes[i] == n)
            return i;
    }

    return -1;
}

std::vector<GraphNode::edge> Graph::getEdges()
{
    std::vector<GraphNode::edge> edges;
    for(auto n : _nodes)
    {
        for(auto e : n->_edges)
            edges.push_back(e);
    }

    return edges;
}

double Graph::kruskal()
{
    std::vector<GraphNode::edge> test = getEdges();
    std::vector<std::pair<int, GraphNode::edge>> edges;
    std::vector<GraphNode::edge> mstEdges;

    UnionFind subSet(_nodes.size());

    // Alle Kanten hinzufügen
    for (int i = 0; i < _nodes.size(); ++i)
    {
        GraphNode* n = _nodes[i];

        n->_visited = false;
        for (auto e : n->_edges)
        {
            bool dup = false;
            // Verhindere Duplikate
            for (auto pair : edges)
            {
                int source = pair.first;
                GraphNode::edge edge = pair.second;

                // Wenn schon in Liste dann ignorieren
                if (e.node == _nodes[source] && edge.node == n)
                {
                    dup = true;
                    break;
                }
            }
            if (!dup) // Wenn nicht in Liste dann hinzufügen
                edges.push_back(std::pair<int, GraphNode::edge>(i, e));

        }
    }

    // Die Kantenliste von klein nach groß sortieren
    std::sort(edges.begin(), edges.end(), [](auto& lhs, auto& rhs) -> bool
    {
        return lhs.second.value < rhs.second.value;
    });

    // Mst Berechnen
    double result = 0.0;

    for (int i = 0; i < edges.size(); ++i)
    {
        int u = edges[i].first;
        int v = getId(edges[i].second.node);

        // Solange u und v nicht zum selben Set gehören,
        // MST weiter aufbauen
        if (subSet.find(u) != subSet.find(v))
        {
            result += edges[i].second.value;

            // Sets miteinander verbinden
            subSet.merge(u, v);
        }
    }

    return result;
}
