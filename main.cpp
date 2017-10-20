#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "graph.h"


// Graph connect(const Graph &g, const Node &start_node){

//     Graph final_g(g);
//     std::vector<Node> connected_islands;
//     // find all the neibour nodes connected with start_nodes
//     final_g.findNeighbour(start_node,connected_islands);

//     if (final_g.get_bridge() == final_g.get_complete()){
//       return final_g;
//     }
//     if (!final_g.checkValid()){
//       return Graph(g);
//     }
//     else{
//       Point p1 = start_node.get_pt();
//       int connector_size = connected_islands.size();
//       for (unsigned i = 0; i< connector_size; i++){
//         Point p2 = connected_islands[i].get_pt();
//         final_g.addEdge(p1,p2); // connect them for the first time
//         if (final_g.checkValid()){ // check if graph is valid i
//           final_g.addEdge(p1,p2);
//           if (final_g.checkValid()){
//           continue;
//         }
//       }
//       else{
//         connect(g, connected_islands[i]);
//       }
//     }
//   }



// }


int main(int argc, char* argv[] ) {

  
  // Parse the arguments
  if (argc < 2) {
    std::cout << "ERROR!  Must specify input file" << std::endl;
    exit(1);
  }
  std::ifstream istr(argv[1]);
  if (!istr.good()) {
    std::cout << "ERROR!  Could not open input file '" << argv[1] << "'" << std::endl;
    exit(1);
  }
  bool find_all_solutions = false;
  bool connected = false;
  for (int i = 2; i < argc; i++) {
    if (argv[i] == std::string("--find_all_solutions")) {
      find_all_solutions = true;
    } else if (argv[i] == std::string("--connected")) {
      connected = true;
    } else {
      std::cout << "ERROR!  Unknown argument '" << argv[i] << "'" << std::endl;
      exit(1);
    }
  }


  // Create an empty graph object
  Graph g;
  // Read in the puzzle from the input file
  int x,y,n;
  std::vector<Point> pts;
  while (istr >> x >> y >> n) {
    pts.push_back(Point(x,y));
    g.addNode(Point(x,y),n);
  }

  // start from node with biggest number

  // check p_on_graph();
  // assert(g.p_on_graph(Point()))
  g.findNeighbour();



  
  // // The statements below hardcode the solution to puzzle1.txt.
  // // You should remove this code and replace it with a general solver.
  // if (argv[1] == std::string("puzzle1.txt")) {
  //   g.addEdge(pts[0],pts[1]);
  //   g.addEdge(pts[0],pts[1]);
  //   g.addEdge(pts[1],pts[2]);
  //   g.addEdge(pts[1],pts[2]);
  //   g.addEdge(pts[2],pts[3]);
  //   // Recurrsion method
  //   // print the edges (any order is ok)
  //   g.printSolution();
  //   g.printGraph();
  // }
  // else if(argv[1] == std::string("puzzle2.txt")){
  //   g.addEdge(pts[0],pts[1]);
  //   g.addEdge(pts[0],pts[1]);
  //   g.addEdge(pts[0],pts[2]);
  //   g.addEdge(pts[0],pts[2]);
  //   g.addEdge(pts[0],pts[3]);
  //   g.addEdge(pts[0],pts[3]);
  //   g.addEdge(pts[0],pts[4]);
  //   g.addEdge(pts[0],pts[4]);

  //   g.printSolution(); 
  //   g.printGraph();
  // }
  // else if(argv[1] == std::string("puzzle3.txt") && find_all_solutions==false){
  //   g.addEdge(pts[0],pts[1]);
  //   g.addEdge(pts[2],pts[3]);
  //   g.addEdge(pts[2],pts[3]);
  //   g.addEdge(pts[4],pts[5]);

  //   g.printSolution(); 
  //   g.printGraph();
  // }
  // else if(argv[1] == std::string("puzzle3.txt") && find_all_solutions==true){
  //   g.addEdge(pts[0],pts[1]);
  //   g.addEdge(pts[2],pts[3]);
  //   g.addEdge(pts[2],pts[3]);
  //   g.addEdge(pts[4],pts[5]);
  //   g.printSolution();
  //   g.printGraph(); 
  //   g.clearEdge();



  //   g.addEdge(pts[0],pts[2]);
  //   g.addEdge(pts[1],pts[3]);
  //   g.addEdge(pts[2],pts[4]);
  //   g.addEdge(pts[3],pts[5]);

  //   g.printSolution();
  //   g.printGraph(); 
  //   g.clearEdge();

  //   g.addEdge(pts[0],pts[2]);
  //   g.addEdge(pts[2],pts[3]);
  //   g.addEdge(pts[1],pts[3]);
  //   g.addEdge(pts[4],pts[5]);

  //   g.printSolution();
  //   g.printGraph(); 
  //   g.clearEdge();


  //   g.addEdge(pts[0],pts[1]);
  //   g.addEdge(pts[2],pts[3]);
  //   g.addEdge(pts[2],pts[4]);
  //   g.addEdge(pts[3],pts[5]);

  //   g.printSolution();
  //   g.printGraph(); 
  //   g.clearEdge();

  //   int count = 4;

  //   std::cout << "Found " << count << " solution(s)" << std::endl;
  // }

  // print a visualization of the (solved or unsolved) puzzle
  

}
