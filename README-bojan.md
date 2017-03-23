# Issues 

## Tilt angle
- lmeasure tilt angle does not match neurostr one 
- Different definitions 
- Neurostr: 
    - NeuroSTR takes full parent vector
    - Remote considers remote daughter whereas LM only uses daugther nodes 
    - Some cases > bifurcation angle. Mostly when 0 tips on either side.   
- LM 
    - Local considers parent last compartment whereas remote considers full parent branch vector. Each only considers daughter compartments. 
    - LM angles too large 


# Debug build cmake 

    cmake -DCMAKE_BUILD_TYPE=Release ..

http://stackoverflow.com/questions/7724569/debug-vs-release-in-cmake

# gdb 

	gdb --args bin/neurostr_neuritefeatures -i ~/code/bbp-data/data/swc-luis/C230998A-I3.swc 

http://stackoverflow.com/questions/18271363/line-by-line-c-c-code-debugging-in-linux-ubuntu
