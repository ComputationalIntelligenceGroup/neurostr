#include <stdio.h>

#include <stdio.h>

#include <string>
#include <iostream>
#include <algorithm>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/format.hpp>

#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>

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

namespace po = boost::program_options;
namespace ns = neurostr::selector;
namespace nm = neurostr::measure; 
namespace nlm = neurostr::measure::lmeasure;

 std::string escape_string(const std::string& s){
   return "\""+s+"\"";
 }
 
 std::string escape_string(const char *c){
   return escape_string(std::string(c));
 }
 
 
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

// Note: This should be done with rapidjson
void print_measures(std::map<std::string, float>& m , 
                            std::ostream& os ){
  bool first = true;
  // Measures json element
  os << escape_string("measures") << " : { ";   

  // Print each measure
  for(auto it = m.begin(); it!=m.end();++it ){
    
    // If values vector is not empty
    if(!std::isnan(it->second)){
      if(first){
        first = false;
      } else {
        os << ", ";
      }      
    
     // Print key and value
      os << escape_string(it->first) << " : " << std::to_string(it->second) ;
    
    } // End if value is nan
    
  } // End for loop
  os << " }"; // Close measures
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

/**
 * @brief 
 * @param ac
 * @param av
 * @return 
 */
int main(int ac, char **av)
{
  // Log errors in std::cerr
  neurostr::log::init_log_cerr();
  neurostr::log::enable_log();
  
  std::string ifile;
  
  // omits
  bool omitapical = false;
  bool omitaxon = false;
  bool omitdend = false;
  bool correct = false;
  
  std::string selection;
  
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "Produce help message")
    ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("correct,c", "Try to correct the errors in the reconstruction")
    ("selection,s", po::value< std::string >(&selection) -> default_value("all"), "Branch subset: all, terminal, nonterminal, preterminal or root")
    ("omitapical", "Ignore the apical dendrite")
    ("omitaxon", "Ignore the axon")
    ("omitdend", "Ignore the non-apical dendrites");
  
  
  
  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
  po::notify(vm);    
  
	if (vm.count("help")){
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_branchfeature -i test.swc " << std::endl << std::endl ;
    return 1;
  }
  
  if(!vm.count("input") || !vm.count("input")){
    std::cout << "ERROR: input file required" << std::endl << std::endl;
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_branchfeature -i test.swc " << std::endl << std::endl ;
    return 2;
  }
  
  
  omitapical = (vm.count("omitapical") > 0);
  omitaxon = (vm.count("omitaxon") > 0);
  omitdend = (vm.count("omitdend") > 0);
  correct = (vm.count("correct") > 0);
  
  /*** END PARAMETER PARSING */
  
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  
  // Measure each neurite and output report
  bool first = true;
  std::cout << "[" << std::endl;
  
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
        std::cout << " , ";
      }
      first = false;
      
      print_node_measures(*it, std::cout);
    }  
  }
  
  std::cout << "]" << std::endl;
  
}

