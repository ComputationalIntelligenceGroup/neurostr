#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

#include <neurostr/tools/validator_tool.h>

namespace po = boost::program_options; 

void set_validation_flag( const po::variables_map& map, const std::string& basename,bool& value){
  if( map.count(basename)){
    value = true;
  } else if (map.count( std::string("no") + basename)){
    value = false;
  }
}


/**
 * @brief 
 * @param ac
 * @param av
 * @return 
 */
int main(int ac, char **av)
{
  
  neurostr::log::init_log_cerr();
  //neurostr::log::log_level(neurostr::log::warning); // emit warning error or critical
  
  std::string ifile;

  // Parameters
  float planar_rec_threshold = 1.01;
  float linear_branch_threshold = 1.01;
  int dcount_min = 2;
  int dcount_max = 13;
  
  // Tests
  bool attached = true;
  bool soma = true;
  bool planar = true; 
  bool dendcount = true; 
  bool apcount = true; 
  bool axoncount = true; 
  bool trif = true; 
  bool linear = true; 
  bool zerolen = true; 
  bool intersec = true; 
  bool nodecr = true;
  bool segcoll = false ;
  bool branchcoll = true;
  bool angles =true;
  
  // Print all outs
  bool exhaustive = false;
  
  // Strict mode
  bool nostrict = false;
  
  // nodiams
  bool nodiams = false;
  
  // 2D
  bool bidim = false;
  
  // omits
  bool omitapical = false;
  bool omitaxon = false;
  bool omitdend = false;
  bool omitsoma = false;
  
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "Produce help message")
    ("input", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("exhaustive,e", "Exhaustive report. Include all validation items, not only failures")
    ("attached,A", "Enable neurites attached to soma validation")
    ("noattached,a", "Disable neurites attached to soma validation")
    ("soma,S", "Enable soma validation")
    ("nosoma,s", "Disable soma validation")
    ("planar,P", "Enable planar reconstruction validation")
    ("noplanar,p", "Disable planar reconstruction validation")
    ("dendcnt,D", "Enable dendrite count validation")
    ("nodendcnt,d", "Disable dendrite count validation")
    ("apical,C", "Enable apical count validation")
    ("noapical,c", "Disable apical count validation")
    ("axon,X", "Enable axon count validation")
    ("noaxon,x", "Disable axon count validation")
    ("trifurcation,T", "Enable trifurcation validation")
    ("notrifurcation,t", "Disable trifurcation validation")
    ("linear,L", "Enable linear branches validation")
    ("nolinear,l", "Disable linear branches validation")
    ("zero,Z", "Enable zero length segments validation")
    ("nozero,z", "Disable zero length segments validation")
    ("intersect,I", "Enable intersecting nodes validation")
    ("nointersect,i", "Disable intersecting nodes validation")
    ("decrease,R", "Enable non-decrasing radius validation")
    ("nodecrease,r", "Disable non-decrasing radius validation")
    ("segcoll,V", "Enable segment collision validation")
    ("nosegcoll,v", "Disable segment collision validation")
    ("branchcoll,B", "Enable branch collision validation")
    ("nobranchcoll,b", "Disable branch collision validation")
    ("extremeang,M", "Enable extreme angles validation")
    ("noextremeang,m", "Disable extreme angles validation")
    ("nostrict", "No strict mode")
    ("nodiameters", "Disables diameter-based nodes")
    ("is2D", "Disables validations that assume a 3D reconstruction")
    ("neuron", "Validates the entire neuron")
    ("omitapical", "Ignore the apical dendrite")
    ("omitaxon", "Ignore the axon")
    ("omitdend", "Ignore the non-apical dendrites")
    ("omitsoma", "Disable soma tests")
    ("planarth", po::value< float >(&planar_rec_threshold)->default_value(1.01), "Planar reconstruction threshold")
    ("linearth", po::value< float >(&linear_branch_threshold)->default_value(1.01), "Linear branch threshold")
    ("mindend", po::value< int >(&dcount_min)->default_value(2), "Number of dendrites minimum (in)")
    ("maxdend", po::value< int >(&dcount_max)->default_value(13), "Number of dendrites maximum (out)")
    ;
  
  
  
  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
  po::notify(vm);    

  
	if (vm.count("help")){
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_validator -i test.swc -e" << std::endl << std::endl ;
    return 1;
  }
  
  if(!vm.count("input") || !vm.count("input")){
    std::cout << "ERROR: input/output file required" << std::endl << std::endl;
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_validator -i test.swc -e" << std::endl << std::endl ;
    return 2;
  }
  
  /** Set validation test flags*/
  set_validation_flag(vm,"attached",attached);
  set_validation_flag(vm,"soma",soma);
  set_validation_flag(vm,"planar",planar);
  set_validation_flag(vm,"dendcnt",dendcount);
  set_validation_flag(vm,"apical",apcount);
  set_validation_flag(vm,"axon",axoncount);
  set_validation_flag(vm,"trifurcation",trif);
  set_validation_flag(vm,"linear",linear);
  set_validation_flag(vm,"zero",zerolen);
  set_validation_flag(vm,"intersect",intersec);
  set_validation_flag(vm,"decrease",nodecr);
  set_validation_flag(vm,"segcoll",segcoll);
  set_validation_flag(vm,"branchcoll",branchcoll);
  set_validation_flag(vm,"extremeang",angles);
  
  // Get other flags
  exhaustive = (vm.count("exhaustive") > 0);
  nostrict = (vm.count("nostrict") > 0);
  nodiams = (vm.count("nodiameters") > 0);
  bidim = (vm.count("is2D") > 0);
  
  // ATM these are ignored
  omitapical = (vm.count("omitapical") > 0);
  omitaxon = (vm.count("omitaxon") > 0);
  omitdend = (vm.count("omitdend") > 0);
  omitsoma = (vm.count("omitsoma") > 0);
  
  if((vm.count("neuron") > 0)){
    omitapical = false;
    omitaxon = false;
    omitdend = false;
    omitsoma = false;
  } 
  
  /*** END PARAMETER PARSING */ 
  do_validate(std::cout, ifile, attached, soma, planar, dendcount, apcount, axoncount, trif, linear, zerolen, intersec , nodecr, segcoll , branchcoll, angles, exhaustive, nostrict, nodiams, bidim, omitapical, omitaxon, omitdend, omitsoma, planar_rec_threshold, linear_branch_threshold, dcount_min, dcount_max);

}

