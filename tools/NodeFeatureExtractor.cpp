#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

#include <neurostr/tools/node_features.h> 

namespace po = boost::program_options;

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
  compute_node_features(std::cout, ifile, omitapical, omitaxon, omitdend, correct); 
}


