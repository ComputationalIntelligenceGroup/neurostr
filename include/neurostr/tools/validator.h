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
