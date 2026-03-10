#!/bin/bash
set -e

echo "=== Installation of the BIP compiler ==="
source bipinstaller.sh

echo "=== Compiling Packages/ ==="
cd "Packages"
make

echo "=== Compiling (if necessary) and running MainApp/ ==="
cd "../MainApp"
make run

echo "=== CSV file analysis ==="
python3 analyzeCSV.py

echo "=== Done ==="