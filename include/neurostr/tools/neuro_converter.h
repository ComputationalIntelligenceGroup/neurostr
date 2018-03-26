#include <string>
#include <iostream>
#include <algorithm>
#include <exception>

#include <boost/format.hpp> 

#include <neurostr/core/log.h>
#include <neurostr/io/parser_dispatcher.h>
#include <neurostr/io/SWCWriter.h>
#include <neurostr/io/JSONWriter.h>

void convert(std::string ifile, std::string ofile, std::string ext, bool correct = false, float eps = 0.0) 
{ 

  // Create ofstream /ifstreams
  std::ofstream ofs(ofile);
  
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  
  // Simpify / correct
  for(auto it = r->begin(); it != r->end(); ++it){
    if(correct) it->correct();
    if(eps != 0.0 ){
      it->simplify(eps);
    }
  } 
  
  // Select a writer depending on the extension
  if(ext == "swc"){
    if(r->size() > 1){
      NSTR_LOG_(warn, "The output SWC file will only contain the first neuron in the reconstruction. The rest are ignored");
    }
    neurostr::io::SWCWriter writer(ofs);
    writer.write(*(r->begin()));  // Writes first neuron 
  } else if (ext == "json"){
    neurostr::io::JSONWriter writer(ofs);
    writer.write(*r);
  } 
  
  // Close stream - Reconstruction should be autom. free'd (unique_ptr)
  ofs.close(); 
}
