#include <stdio.h> 

#include <string>
#include <iostream>
#include <algorithm>
#include <boost/format.hpp> 

#include <neurostr/core/log.h>
#include <neurostr/core/neuron.h>
#include <neurostr/io/parser_dispatcher.h>
#include <neurostr/validator/predefined_validators.h>

namespace po = boost::program_options;
namespace nv = neurostr::validator;

void set_validation_flag( const po::variables_map& map, const std::string& basename,bool& value){
  if( map.count(basename)){
    value = true;
  } else if (map.count( std::string("no") + basename)){
    value = false;
  }
}

template <typename V>
void output_validation(const neurostr::Neuron& n, 
                       const V& validation, 
                       std::ostream& os, 
                       const bool exhaustive,
                       bool& first){
    
    V test = validation;
    test.validate(n);
    
    if(!first)
      std::cout << "," << std::endl;
    
    test.toJSON(os,!exhaustive);
    
    first = false;
};


void validate(std::ostream& outstream, std::string ifile, bool attached = true, bool soma = true, bool planar = true, bool dendcount = true, bool apcount = true, bool axoncount = true, bool trif = true, bool linear = true, bool zerolen = true, bool intersec = true, bool nodecr = true, bool segcoll = false , bool branchcoll = true, bool angles =true, bool exhaustive = false, bool nostrict = false, bool nodiams = false, bool bidim = false, bool omitapical = false, bool omitaxon = false, bool omitdend = false, bool omitsoma = false, float planar_rec_threshold = 1.01, float linear_branch_threshold = 1.01, int dcount_min = 2, int dcount_max = 13)
{ 
  
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  neurostr::Neuron& n = *(r->begin());
  
  /** Remove **/
  if(omitapical) n.erase_apical();
  if(omitaxon) n.erase_axon();
  if(omitdend) n.erase_dendrites();
  
  
  // Run validations and output report
  outstream << "[" << std::endl;

  bool first = true;
  
  // Execute attached
  if(attached && !omitsoma){
    output_validation(n, 
                      nv::neurites_attached_to_soma, 
                      outstream, 
                      exhaustive,
                      first);
  }

  // Execute has soma
  if(soma && !omitsoma){
    output_validation(n, 
                      nv::neuron_has_soma, 
                      outstream, 
                      exhaustive,
                      first);
  }
  
  // Execute planar rec - disabled for 2D
  if(planar && !bidim){
    output_validation(n, 
                      nv::planar_reconstruction_validator_factory(planar_rec_threshold), 
                      outstream, 
                      exhaustive,
                      first);
  }
  
  if(dendcount && !omitdend){
    output_validation(n, 
                      nv::dendrite_count_validator_factory(dcount_min,dcount_max),
                      outstream, 
                      exhaustive,
                      first);
  }
  
  if(apcount && !omitapical){
    output_validation(n, 
                      nv::apical_count_validator_factory(!nostrict),
                      outstream, 
                      exhaustive,
                      first);
  }
  
  if(axoncount && !omitaxon){
    output_validation(n, 
                      nv::axon_count_validator_factory(!nostrict),
                      outstream, 
                      exhaustive,
                      first);
  }
  
  if(trif){
    output_validation(n, 
                      nv::no_trifurcations_validator,
                      outstream, 
                      exhaustive,
                      first);
  }
  
  if(linear){
    output_validation(n, 
                      nv::linear_branches_validator_factory(linear_branch_threshold),
                      outstream, 
                      exhaustive,
                      first);
  }
  
  if(zerolen){
    output_validation(n, 
                      nv::zero_length_segments_validator,
                      outstream, 
                      exhaustive,
                      first);
  }
  
  // Intersecting nodes - disabled when nodiams flag is present
  if(intersec && !nodiams){
    output_validation(n, 
                      nv::radius_length_segments_validator,
                      outstream, 
                      exhaustive,
                      first);
  }

  // Non decreasing radius - disabled when nodiams flag is present
  if(nodecr  && !nodiams ){
    output_validation(n, 
                      nv::increasing_radius_validator,
                      outstream, 
                      exhaustive,
                      first);
  }
  
  if(branchcoll){
    output_validation(n, 
                      nv::branch_collision_validator_factory(nodiams),
                      outstream, 
                      exhaustive,
                      first);
  }

  if(segcoll){
    output_validation(n, 
                      nv::segment_collision_validator,
                      outstream, 
                      exhaustive,
                      first);
  }


  if(angles){
    output_validation(n, 
                      nv::extreme_angles_validator,
                      outstream, 
                      exhaustive,
                      first);
  }
  
  outstream << "]" << std::endl;
  
}
