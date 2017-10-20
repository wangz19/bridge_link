#include <string>
#include <iostream>
#include <cassert>
#include "graph.h"


// ====================================================================================

Point::Point(int x_, int y_) : x(x_),y(y_) {
  // Points must have positive coordinates
  assert (x_ >= 0);
  assert (y_ >= 0);
}

// helper function for printing Points
std::ostream& operator<<(std::ostream &ostr, const Point &p) {
  ostr << "(" << p.get_x() << "," << p.get_y() << ")";
  return ostr;
}

// ====================================================================================

Edge::Edge(const Point &a_, const Point &b_) : a(a_),b(b_) {
  // Edges must be horizontal or vertical
  assert ((a_.get_x() == b_.get_x() && a_.get_y() != b_.get_y()) ||
          (a_.get_x() != b_.get_x() && a_.get_y() == b_.get_y()));
}

// ====================================================================================

Node::Node(const Point &p, int n) \
: right_ptr(NULL),left_ptr(NULL),up_ptr(NULL),down_ptr(NULL),pt(p),num_paths(n),avaliable_link(n){
  // Nodes/islands must have at least one Edge/bridge.  At most 2
  // Edges/bridges can connect a pair of Nodes/islands.  Edges/bridges
  // may only run horizontal or vertical and cannot cross other
  // Edges/bridges.  This a Node/island can support at most 8 bridges.
  assert (n >= 1 && n <= 8);
}

// ====================================================================================

// helper function for printing Edges
std::ostream& operator<<(std::ostream &ostr, const Edge &e) {
  ostr << e.get_a() << "," << e.get_b();
  return ostr;
}

// ====================================================================================

Graph::Graph() {
  // We track the maximum dimensions of the graph.
  max_x = 0;
  max_y = 0;
}


void Graph::addNode(const Point &p, int n) {
  // Incrementally track the maximum dimensions of the graph.
  max_x = std::max(p.get_x(),max_x);
  max_y = std::max(p.get_y(),max_y);
  nodes.push_back(Node(p,n));
}


void Graph::addEdge(const Point &a, const Point &b) {
  assert (a.get_x() <= max_x);
  assert (a.get_y() <= max_y);
  assert (b.get_x() <= max_x);
  assert (b.get_y() <= max_y);
  edges.push_back(Edge(a,b));
  
}


void Graph::printSolution() const {
  std::cout << "Solution:" << std::endl;
  for (int i = 0; i < edges.size(); i++) {
    std::cout << edges[i] << std::endl;
  }
}


void Graph::printGraph() const {
  // a graph should have at least one node/island
  assert (nodes.size() > 1);
  // the dimensions of the board should be positive
  assert (max_x >= 0);
  assert (max_y >= 0);

  // allocate an empty/blank board, twice as big in each dimension so
  // we can draw lines between the nodes/islands.
  std::vector<std::string> board(2*max_y+1,std::string(2*max_x+1,' '));
  // mark all of the islands with their bridge count
  for (int i = 0; i < nodes.size(); i++) {
    const Point &pt = nodes[i].get_pt(); 
    std::string value = std::to_string(nodes[i].get_num_paths());
    board[2*pt.get_y()][2*pt.get_x()] = value[0];
  }

  // loop over all of the edges/bridges
  for (int i = 0; i < edges.size(); i++) {
    Point a = edges[i].get_a();
    Point b = edges[i].get_b();
    // determine the edge/edge direction
    int diff_x = b.get_x()-a.get_x();
    int diff_y = b.get_y()-a.get_y();
    if (diff_x > 0) diff_x = 1;
    if (diff_x < 0) diff_x = -1;
    if (diff_y > 0) diff_y = 1;
    if (diff_y < 0) diff_y = -1;

    // walk between the islands to draw the bridge
    int x = a.get_x()*2+diff_x;
    int y = a.get_y()*2+diff_y;
    while (x != b.get_x()*2 || y != b.get_y()*2) {
      if (diff_x == 0) {
        // vertical bridge
        assert (diff_y != 0);
        if (board[y][x] == '|') {
          // if we already have a bridge, draw a double vertical bridge
          board[y][x] = '#';
        } else {
          assert (board[y][x] == ' ');
          // otherwise draw a single vertical bridge
          board[y][x] = '|';        
        }
      } else {
        assert (diff_y == 0);
        // horizontal bridge
        if (board[y][x] == '-') {
          // if we already have a brige, draw a double horizontal bridge
          board[y][x] = '=';        
        } else {
          assert (board[y][x] == ' ');
          // otherwise draw a single horizontal bridge
          board[y][x] = '-';        
        }
      }
      x+=diff_x;
      y+=diff_y;
    }
  }
  // surround the board with a border of spaces
  char border = ' ';
  std::cout << std::string(board[0].size()+2,border) << std::endl;
  for (int i = board.size()-1; i >= 0; i--) {
    std::cout << border << board[i] << border << std::endl;
  }
  std::cout << std::string(board[0].size()+2,border) << std::endl;
}


  // check if point is on Graph
  bool Graph::p_on_graph(const Point & p){
    std::vector<Node>::iterator itr;
    for (itr = nodes.begin();itr!=nodes.end();++itr){
      Point my_point = itr->get_pt();
      if ( my_point.get_x() == p.get_x() && my_point.get_y() == p.get_y()){
        return true;
      }
    }
    return false;
  }



  void Graph::findNeighbour(){ //load connectivity 
    std::vector<Node>::iterator itr_i;
    std::vector<Node>::iterator itr_j;
    // naive iteration to find nearest vertical/horizontal neighbours
    for (itr_i = nodes.begin(); itr_i != nodes.end(); ++itr_i){
      int right_tmp = max_x; int left_tmp = max_x; // temp store the near neibour
      int up_tmp = max_y; int down_tmp = max_y;
      for (itr_j = nodes.begin(); itr_j != nodes.end(); ++itr_j){
        int x1 = itr_i->get_pt().get_x(); int y1 = itr_i->get_pt().get_y();
        int x2 = itr_j->get_pt().get_x(); int y2 = itr_j->get_pt().get_y();
        if ((x1 == x2) && (y1 < y2) && ((y2-y1)<=up_tmp)){ // Up nearest Node
          up_tmp = y2-y1;
          itr_i->up_ptr = &(*itr_j); // point to node
        }
        else if((x1 == x2) && (y2 < y1) && ((y1-y2)<=down_tmp)){// Down nearst Node
          down_tmp = y1-y2;
          itr_i->down_ptr = &(*itr_j); // point to node
        }
        else if(y1 == y2 && x2 < x1 && ((x1-x2)<=left_tmp)){// Left nearst Node
          left_tmp = x1-x2;
          itr_i->left_ptr = &(*itr_j); // point to node
        }
        else if(y1 == y2 && x1 < x2 && ((x2-x1)<=right_tmp)){// Right nearst Node
          right_tmp = x2-x1;
          itr_i->right_ptr = &(*itr_j); // point to node
        }
      }
    } 

    // print neibour
    for (itr_i = nodes.begin(); itr_i != nodes.end(); ++itr_i){
      std::cout << "for Node:" << itr_i->get_pt()<<std::endl;
      std::cout << "connected_members are:" ;
      if (itr_i->up_ptr!= NULL)
        std::cout<< itr_i->up_ptr->get_pt()<<" , ";
      if (itr_i->down_ptr!= NULL)
        std::cout<< itr_i->down_ptr->get_pt()<<" , ";
      if (itr_i->left_ptr!= NULL)
        std::cout<< itr_i->left_ptr->get_pt()<<" , ";
      if (itr_i->right_ptr!= NULL)
        std::cout<< itr_i->right_ptr->get_pt()<<" , ";
      
      std::cout << std::endl;
    }
  }

// check if edges are all valid in current graph
  bool Graph::checkValid(){
  
  return true;

  }


// ====================================================================================
