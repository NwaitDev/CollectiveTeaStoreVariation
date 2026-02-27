#!/bin/bash
OLDELPASO=$PWD
git clone https://gricad-gitlab.univ-grenoble-alpes.fr/verimag/bip/compiler.git
cd compiler/distribution
./wrap.sh # compiling the compiler
chmod u+x setenv.sh
source ./setenv.sh # setting the BIP environment
export $(printenv | grep BIP)
export PATH=$PATH
cd build/bipc-latest/bin
echo "$PWD/bipc.sh \"\$@\"" > ~/.local/bin/bipc # aliasing the compiler script
chmod u+x ~/.local/bin/bipc
cd $OLDELPASO