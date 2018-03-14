#!/usr/bin/env bash

readonly NEUROSTR_INSTALL_GIT="https://gitlab.com/mmichiels/neurostr_install.git"
readonly TOOLS_DIR="/opt/neurostr_compile_install"
readonly TOOLS_FILES_DIR="/opt/neurostr_compile_install/neurostr_install"

install_windows () {
  cd /opt
  mkdir neurostr_compile_install
  cd neurostr_compile_install

  #-----Install CMake------
  if [ ! -f "./already_run_in_windows.log" ]; then #It means it's the first time we are running the script
    touch already_run_in_windows.log
    #----Download Eigen3-----
    cd /opt
    wget --timeout=5 --tries=10 http://bitbucket.org/eigen/eigen/get/3.3.4.tar.gz
    tar xvf 3.3.4.tar.gz
    rm 3.3.4.tar.gz

    cd $TOOLS_DIR

    wget https://cmake.org/files/v3.9/cmake-3.9.4.tar.gz
    tar -xzf cmake-3.9.4.tar.gz
    rm cmake-3.9.4.tar.gz
    cd cmake-3.9.4
    ./bootstrap
    make -j 8
    make install -j 8


    apt-get install -y git
  	apt-get install libspdlog-dev
  	apt-get install rapidjson-dev
  	apt-get install libeigen3-dev
    echo 'EIGEN3_INCLUDE_DIR="/opt/eigen-eigen-5a0156e40feb"' >> /etc/environment


    cd $TOOLS_DIR

    git clone $NEUROSTR_INSTALL_GIT
    mkdir /toolchains_cmake

    sudo apt-get install -y mingw-w64



    cd $TOOLS_DIR

    #----Cross-compile boost----
    wget https://dl.bintray.com/boostorg/release/1.65.1/source/boost_1_65_1.tar.gz
    tar xvf boost_1_65_1.tar.gz
    rm boost_1_65_1.tar.gz

    cd boost_1_65_1

    sudo apt-get update
    sudo apt-get install -y build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev

    cd $TOOLS_DIR

    #---Update spdlog-----
    git clone https://github.com/gabime/spdlog.git
    #(remplazar la carpeta C:\workspace\neurostr\bundled\spdlog por la carpeta include/spdlog que nos hemos descargado)
    rm -R -f $WORKDIR/bundled/spdlog
    cp -r spdlog/include/spdlog $WORKDIR/bundled/spdlog

    #---Update basen.hpp----
    wget https://raw.githubusercontent.com/azawadzki/base-n/master/include/basen.hpp
    #(remplazar el fichero C:\workspace\neurostr\bundled\basen.hpp por el que nos hemos descargado)
    rm -f $WORKDIR/bundled/basen.hpp
    cp basen.hpp $WORKDIR/bundled/basen.hpp

    #---Fix geometry.h----
    #(Remplazar C:\workspace\neurostr\include\neurostr\core\geometry.h por el files/geometry.h que nos acabamos de bajar)
    rm -f $WORKDIR/include/neurostr/core/geometry.h
    cp $TOOLS_FILES_DIR/files/geometry.h $WORKDIR/include/neurostr/core/geometry.h

  fi


  #----Cross-compile boost----
  cd $TOOLS_DIR
  update-alternatives --set $TOOLCHAIN-g++ "/usr/bin/$TOOLCHAIN-g++-posix"

  cd "$TOOLS_DIR/boost_1_65_1"
  cp tools/build/example/user-config.jam $HOME
  if [ "$ARCHITECTURE" == "64" ]; then
    echo "using gcc: $TOOLCHAIN-g++ ;" >> $HOME/user-config.jam
  else
    echo "using gcc : i686 : $TOOLCHAIN-g++ ;" >> $HOME/user-config.jam
  fi


  if [ ! -f "/usr/$TOOLCHAIN/lib/libboost_filesystem.a" ]; then #If boost has not been installed yet
    #---------Configure and build Boost-------------
    ./bootstrap.sh mingw \
        toolset=$TOOLSET \
        target-os=$TARGET \
        address-model=$ARCHITECTURE \
        link=shared,static \
        threading=multi \
        threadapi=win32 \
        --prefix=/usr/$TOOLCHAIN


    ./b2 install \
        toolset=$TOOLSET \
        target-os=$TARGET \
        address-model=$ARCHITECTURE \
        link=shared,static \
        threading=multi \
        threadapi=win32 \
        --prefix=/usr/$TOOLCHAIN \
        --layout=system release

  fi


  #---Cross-compile neurostr using Cmake:----
  cd $WORKDIR
  cp $TOOLS_FILES_DIR/files/$TOOLCHAIN_FILE /toolchains_cmake/
  cp $TOOLS_FILES_DIR/files/CMakeLists_crosscompile_ubuntu_to_windows.txt ./CMakeLists.txt

  rm -R -f build
  mkdir build
  cd build

  cmake -DCMAKE_TOOLCHAIN_FILE=/toolchains_cmake/$TOOLCHAIN_FILE ..
  make neurostr -j 8
  make tools -j 8

}

install_ubuntu() {
  cd /opt
  mkdir neurostr_compile_install
  cd neurostr_compile_install

  if [ ! -f "./already_run_in_ubuntu.log" ]; then #It means it's the first time we are running the script
    touch already_run_in_ubuntu.log

    #----Download Eigen3-----
    cd /opt
    wget --timeout=5 --tries=10 http://bitbucket.org/eigen/eigen/get/3.3.4.tar.gz
    tar xvf 3.3.4.tar.gz
    rm 3.3.4.tar.gz

    cd $TOOLS_DIR

    #----Install cmake------
  	wget https://cmake.org/files/v3.9/cmake-3.9.4.tar.gz
  	tar -xzf cmake-3.9.4.tar.gz
  	rm cmake-3.9.4.tar.gz
  	cd cmake-3.9.4
  	./bootstrap
  	make -j 8
  	make install -j 8

    #----Download header libraries dependencies------
  	apt-get install -y git
  	apt-get install libspdlog-dev
  	apt-get install rapidjson-dev
  	apt-get install libeigen3-dev
    echo 'EIGEN3_INCLUDE_DIR="/opt/eigen-eigen-5a0156e40feb"' >> /etc/environment

  	cd $TOOLS_DIR

    #----Compile boost------
  	wget https://dl.bintray.com/boostorg/release/1.65.1/source/boost_1_65_1.tar.gz
  	tar xvf boost_1_65_1.tar.gz
  	rm boost_1_65_1.tar.gz
  	cd boost_1_65_1
  	sudo apt-get update
	  sudo apt-get install -y build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev
    sudo apt-get install gcc-multilib g++-multilib

    cd $TOOLS_DIR
    git clone $NEUROSTR_INSTALL_GIT

  fi

  cd "$TOOLS_DIR/boost_1_65_1"
  cp tools/build/example/user-config.jam $HOME

  cd $WORKDIR
  if [ "$ARCHITECTURE" == "64" ]; then
    BOOST_DIR="/usr"
    rm -f ./CMakeLists.txt
    cp  $TOOLS_FILES_DIR/files/CMakeLists_ubuntu_64_bits.txt ./CMakeLists.txt
  elif [ "$ARCHITECTURE" == "32" ]; then
    BOOST_DIR="/usr/boost_ubuntu_32_bits"
    rm -f ./CMakeLists.txt
    cp  $TOOLS_FILES_DIR/files/CMakeLists_ubuntu_32_bits.txt ./CMakeLists.txt
  fi




  if [ ! -f "$BOOST_DIR/lib/libboost_filesystem.a" ]; then #If boost has not been installed yet
  if [ "$ARCHITECTURE" == "64" ]; then
    ./bootstrap.sh --prefix=$BOOST_DIR

    ./b2 install
  elif [ "$ARCHITECTURE" == "32" ]; then
    ./bootstrap.sh address-model=$ARCHITECTURE \
    --prefix=$BOOST_DIR

    ./b2 install address-model=$ARCHITECTURE
  fi



  fi

  #----Compile neurostr using CMake------

  cd $WORKDIR

  rm -R -f build
  mkdir build
  cd build
  if [ "$ARCHITECTURE" == "64" ]; then
    cmake ..
  elif [ "$ARCHITECTURE" == "32" ]; then
    cmake -DCMAKE_CXX_FLAGS=-m32 -DCMAKE_C_FLAGS=-m32 ..
  fi

	make neurostr -j 8
	make tools -j 8
}

# Init
FILE="/tmp/out.$$"
GREP="/bin/grep"
#....
# Make sure only root can run our script
if [[ $EUID -ne 0 ]]; then
   echo "Error: This script must be run as root" >&2
   echo "$usage" >&2
   exit 1
fi


usage="

    Usage:
    ./install_neurostr.sh -p <root path neurostr> -a {32|64} -t {ubuntu|windows}

    Example:
    ./install_neurostr.sh -p /home/neurostr -a 64 -t windows

    -h  help
    -p  full root path of neurostr
    -a  architecture (64 or 32)
    -t  target (windows or ubuntu)

    (Binaries will be written in "root_path_neurostr"/build/bin)
    "


if [ $# -eq 0 ]; then
    echo "You must type all the flags"
    echo "$usage" >&2
    exit 1
fi

getopts "hp:a:t:" optname
while [ "$optname" != "?" ] ;
  do
    case "$optname" in
      "h")
        echo "$usage" >&2
        exit 1
        ;;
      "p")
        WORKDIR=$OPTARG
        if [ ! -d "$WORKDIR" ]; then
          echo $'\n Error: path "'$WORKDIR'" does not exists'
          echo "$usage" >&2
          exit 1
        elif [ ! -f "$WORKDIR/CMakeLists.txt" ]; then
          echo $'\n Error: path "'$WORKDIR'" does not contain CMakeLists.txt'
          echo "$usage" >&2
          exit 1
        fi
        ;;
      "a")
        ARCHITECTURE=$OPTARG
        if [ "$ARCHITECTURE" == "64" ]; then
          TOOLCHAIN="x86_64-w64-mingw32"
          TOOLCHAIN_FILE="toolchain_mingw_w64-x86_64.cmake"
        elif [ "$ARCHITECTURE" == "32" ]; then
          TOOLCHAIN="i686-w64-mingw32"
          TOOLCHAIN_FILE="toolchain_mingw_i686-w64-mingw32.cmake"
        else
          echo $'\n Error: Invalid architecture "'$OPTARG'"'
          echo "$usage" >&2
          exit 1
        fi
        ;;
      "t")
        TARGET=$OPTARG
        if [ "$TARGET" != "windows" ] && [ "$TARGET" != "ubuntu" ]; then
          echo $'\n Error: Invalid target "'$OPTARG'"'
          echo "$usage" >&2
          exit 1
        fi
        ;;
      "?")
        echo $'\n Error: Unknown option "'$OPTARG'"'
        echo "$usage" >&2
        exit 1
        ;;
      ":")
        echo $'\n Error: No argument value for option $OPTARG'
        echo "$usage" >&2
        exit 1
        ;;
      *)
      # Should not occur
        echo $'\n Error: Unknown error while processing options'
        echo "$usage" >&2
        exit 1
        ;;
    esac
    getopts "hp:a:t:" optname
  done

#If some flag was not typed
if [ -z "$WORKDIR" ] || [ -z "$ARCHITECTURE" ] || [ -z "$TARGET" ]; then
  echo $'\n Error: You must type all the flags'
  echo "$usage" >&2
  exit 1
fi

echo ""
echo ""
echo "Building WORKDIR: $WORKDIR"
echo "Building for: '$ARCHITECTURE' bits system"
echo "Installing for '$TARGET'"
echo "..."
if [ "$TARGET" = "windows" ]; then
  install_windows
elif [ "$TARGET" = "ubuntu" ]; then
  install_ubuntu
fi

echo "Done!"
echo "Binaries are in '$WORKDIR/build/bin' "
