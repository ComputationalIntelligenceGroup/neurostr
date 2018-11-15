#ifndef NEUROSTR_TOOLS_NODE_FEATURES_H_
#define NEUROSTR_TOOLS_NODE_FEATURES_H_

#include <stdio.h>

#include <string>
#include <iostream>
#include <algorithm>
#include <boost/format.hpp> 

#include <neurostr/core/log.h>
#include <neurostr/core/neuron.h>

#include <neurostr/measure/universal_measure.h>
#include <neurostr/measure/branch_measure.h>
#include <neurostr/measure/neurite_measure.h>
#include <neurostr/measure/node_measure.h>
#include <neurostr/measure/aggregate.h>
#include <neurostr/measure/measure_operations.h>

#include <neurostr/selector/neurite_selector.h>

#include <neurostr/io/parser_dispatcher.h> 
#include <neurostr/measure/lmeasure_decl.h> 
#include <neurostr/tools/features_tools.h>

namespace ns = neurostr::selector;
namespace nm = neurostr::measure; 
namespace nlm = neurostr::measure::lmeasure;

std::map<std::string, float> get_node_measures(const neurostr::Node& n){
  std::map<std::string, float> m; // measures 
                                          
  // Node (compartment) length
  m.emplace( "node_length" , nm::node_length_to_parent(n)); 
  m.emplace( "node_root_dist", nm::node_distance_to_root(n)); 
  // Node path distance to root
  m.emplace( "node_root_path", nm::node_path_to_root(n)); 
  m.emplace( "x", n.x()); 
  m.emplace( "y", n.y()); 
  m.emplace( "z", n.z()); 

  m.emplace( "diameter", n.radius()*2.0);

  auto zemo = ns::node_subtree_terminals(n); 
  int tdegree = std::distance(zemo.begin(), zemo.end());
  m.emplace( "terminal_degree", tdegree); 

  auto parent = nm::vector_from_parent(n); 
  m.emplace( "change_x", parent.get<0>()); 
  m.emplace( "change_y", parent.get<1>()); 
  m.emplace( "change_z", parent.get<2>()); 

  m.emplace( "node_order", nm::node_in_branch_order(n)); 

  m.emplace( "node_local_elongation", nm::node_local_elongation_angle(n));
  std::pair<float, float> orientation = nm::node_local_orientation(n);
  m.emplace( "node_local_orientation.a", orientation.first ); 
  m.emplace( "node_local_orientation.e", orientation.second ); 
  m.emplace( "extreme_angle", (float) nm::extreme_angle(n));
  
  return m;
  
}
 
void print_node_id(const neurostr::Node& n, std::ostream& os){
  const neurostr::Branch& b = n.branch();
  os << escape_string("neuron") << " : " << escape_string(b.neurite().neuron().id()) << ", ";
  os << escape_string("neurite") << " : " << b.neurite().id() << ", ";
  os << escape_string("neurite_type") << " : ";

  //auto avg_direction = nm::nodeset_avg_orientation(ns::neuron_node_selector(b.neurite().neuron())); 

  if(b.neurite().type() == neurostr::NeuriteType::kAxon){ 
    os << escape_string("Axon");
  } else if(b.neurite().type() == neurostr::NeuriteType::kApical){ 
    os << escape_string("Apical");
  } else if(b.neurite().type() == neurostr::NeuriteType::kDendrite){ 
    os << escape_string("Dendrite");
  } else {
    os << escape_string("Unknown");
  }
  
  os << ", " << escape_string("branch") << " : " << escape_string(b.idString()) ;
  os << ", " << escape_string("node") << " : " << n.id() ;
}


void print_node_measures(const neurostr::Node& b, std::ostream& os){
  os << "{" ;
  // Print neurite ID
  print_node_id(b,os);
  os << ", ";
  
  // Get measures
  auto m = get_node_measures(b);
  
  // Print them
  print_measures(m,os);
  
  // End obj
  os << "}";
}


void compute_node_features(std::ostream& outstream, std::string ifile, bool omitapical = false, bool omitaxon = false, bool omitdend = false, bool correct = false)
{ 
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  
  // Measure each neurite and output report
  bool first = true;
  outstream << "[" << std::endl;
  
  // For each neuron
  for(auto n_it = r->begin(); n_it != r->end(); ++n_it){
    neurostr::Neuron& n = *n_it;
    
    /** Remove **/
    if(omitapical) n.erase_apical();
    if(omitaxon) n.erase_axon();
    if(omitdend) n.erase_dendrites();
    if(correct) n.correct(); 
 
    std::vector<ns::const_node_reference> nodes;
    nodes = ns::neuron_node_selector(n); 
  
    // Select branches
    for(auto it = nodes.begin(); it != nodes.end(); ++it){
      if(!first){
        outstream << " , ";
      }
      first = false;
      
      print_node_measures(*it, outstream);
    }  
  }
  
  outstream << "]" << std::endl;
  
}

#endif  // NEUROSTR_TOOLS_NODE_FEATURES_H_
