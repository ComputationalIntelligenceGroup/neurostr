#ifndef NEUROSTR_TOOLS_FEATURES_H_
#define NEUROSTR_TOOLS_FEATURES_H_


inline std::string escape_string(const std::string& s){
   return "\""+s+"\"";
 }
 
inline std::string escape_string(const char *c){
   return escape_string(std::string(c));
 }

// Note: This should be done with rapidjson
inline void print_measures(std::map<std::string, float>& m , 
                            std::ostream& os )
{
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

#endif  // NEUROSTR_TOOLS_FEATURES_H_
