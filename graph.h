#include <vector>

// ====================================================================================
// A Point is just a 2D coordinate.

class Point {
public:
  // constructor
  Point(int x_, int y_);
  // accessors
  int get_x() const { return x; }
  int get_y() const { return y; }
private:
  // representation
  int x;
  int y;
};

// helper function for printing Points
std::ostream& operator<<(std::ostream &ostr, const Point &p);

// ====================================================================================
// An Edge is a vertical or horizontal line segment connecting 2 points.

class Edge {
public:
  // constructor
  Edge(const Point &a_, const Point &b_);
  // accessors
  const Point& get_a() const { return a; }
  const Point& get_b() const { return b; }
private:
  // representation
  Point a;
  Point b;
};

// helper function for printing Edges
std::ostream& operator<<(std::ostream &ostr, const Edge &e);

// ====================================================================================
// A Node is a Point with a count of the number of Edges that should touch it.

class Node {
public:
  Node(const Point &p, int n);
  // accessors
  const Point& get_pt() const { return pt; }
  int get_num_paths() const { return num_paths; }

  Node* right_ptr;    // store pointer to connected node
  Node* left_ptr;
  Node* up_ptr;
  Node* down_ptr;

private:
  Point pt;
  int num_paths;
  int avaliable_link;



};

// ====================================================================================
// A Graph is a collection of Nodes and Edges that can be printed.

class Graph {
public:
  // constructor
  Graph();
  // modifiers
  void addNode(const Point &p, int n);
  void addEdge(const Point &a, const Point &b);
  void clearEdge(){edges.clear();}
  int get_max_x(){return max_x;}
  int get_max_y(){return max_y;}
  int get_bridge(){return edges.size();}
  // get the final bridge number if complete
  int get_complete();

  // Member function
  bool checkValid();
  bool p_on_graph(const Point & p);
  void findNeighbour();
  // print helper functions
  void printSolution() const;
  void printGraph() const;
private:
  // representation
  int max_x;
  int max_y;
  std::vector<Node> nodes;
  std::vector<Edge> edges;
};

// ====================================================================================
