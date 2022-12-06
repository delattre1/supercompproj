g++ -O3 -pedantic -std=c++11 busca-exaustiva/busca-exaustiva.cpp -o busca-exaustiva/busca_exaustiva &&
g++ -O3 -Wall -pedantic -std=c++11 -fopenmp busca-local/busca_local.cpp -o busca-local/busca_local_openmp &&
g++ -O3 -Wall -pedantic -std=c++11 busca-local/busca_local.cpp -o busca-local/busca_local
