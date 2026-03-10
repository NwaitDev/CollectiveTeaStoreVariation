#!/bin/bash
OLDPATH=$PWD 
if [ ! -d "compiler/distribution" ]; then
  git clone https://gricad-gitlab.univ-grenoble-alpes.fr/verimag/bip/compiler.git
fi

cd compiler/distribution
if [ ! -f "build/bipc-latest/bin/bipc.sh" ]; then
  ./wrap.sh # compiling the compiler
fi

head -20 setenv.sh > setenv2.sh # last lines of the file may cause an error so we will ignore them
chmod u+x setenv2.sh
source ./setenv2.sh # setting the BIP environment
export $(printenv | grep BIP)
export PATH=$PATH
cd build/bipc-latest/bin
echo "$PWD/bipc.sh \"\$@\"" > /usr/local/bin/bipc # aliasing the compiler script
chmod u+x /usr/local/bin/bipc
cd $OLDPATH
