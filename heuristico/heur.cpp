#include <iostream>
#include <vector>
#include <cmath>

struct City {  
  int id;
  float x,y;
};

bool contains(std::vector<int> visitedCities, int n) {
  for (int i; i < visitedCities.size(); i++) {
    if (visitedCities[i] == n) {return true;}
  }
  return false;
}

float getDistance(City c1, City c2) {
  float d2x  = std::pow((c2.x - c1.x),2);
  float d2y  = std::pow((c2.y - c1.y),2);
  float dist = std::sqrt(d2x + d2y);
  //std::cout << "-- dist func res: " << dist << std::endl;
  return dist;
}

void printVector(std::vector<int> vec) {
  for (int i=0; i < vec.size(); i++) {
    std::cout << vec[i] << ' ';
  }
  std::cout << std::endl;
}

void printCities(std::vector<City> cities) {
  for (int i=0; i < cities.size(); i++) {
    std::cout << "c" << i << " > (x,y): "<< cities[i].x << "," << cities[i].y << std::endl;
  }
}

std::vector<int> travelToNearestCities(std::vector<City> cities, std::vector<int> visitedCities, float * travelledDistance) {
  //std::cout << "\n\n";
  //std::cout << "ENTREI NA FUNCAO NOVAMENTE --";

  // Percorrer todos os elementos do vector
  // Se nao estiver na lista de cidades visitadas -> calcula a distancia 
  // salva o id da cidade com distancia minima na lista de cidades visitadas
  int idMinDist;
  float dist;
  float minDist = -1; 

  int idLastVisited = visitedCities.back();
  City currentCity  = cities[idLastVisited];
  
  // Break recursive function condition
  if (cities.size() == visitedCities.size()) {
    int initialIdx = 0;
    // Voltar para cidade inicial
    dist = getDistance(currentCity, cities[initialIdx]);
    minDist   = dist;
    idMinDist = initialIdx;
    *travelledDistance += minDist;
    //std::cout << travelledDistance;
    return visitedCities;
  }


  //std::cout << "Id cidade da funcao C1: " << idLastVisited << std::endl;

  for (int idx=0; idx < cities.size(); idx++) {
    if (contains(visitedCities, idx)) {
      //std::cout << "POS: "<< i <<  ", CONTEM (continue)" << std::endl;
      continue;
    }

    //std::cout << "POS: "<< i <<  ", NAOCONTEM (calcula)" << std::endl;
    dist = getDistance(currentCity, cities[idx]);
    //std::cout << "Distance: " << dist << std::endl;

    if (minDist == -1) { 
      minDist = dist;
      idMinDist = idx;
    }

    else if (dist < minDist) {
      minDist   = dist;
      idMinDist = idx;
    }
    
    //std::cout << "mindist: " << minDist << " selId: " << idMinDist << " --LOOP--, idx atual: " << idx  << std::endl; //<< " Id cidade do loop C2: " << idx << std::endl;
  }
  
  //std::cout << "SAI DO FOR" << std::endl;
  * travelledDistance += minDist;
  visitedCities.push_back(idMinDist);
  //std::cout << travelledDistance;
  return travelToNearestCities(cities, visitedCities, travelledDistance);
}



int main() {
  int  qtyCities;
  float travelledDistance = 0;
  City auxCity;
  std::vector<City> cities;
  std::vector<int>  visitedCities;

  std::cin  >> qtyCities;
  //Fill array of cities
  for (int i=0; i < qtyCities; i++) {
    auxCity.id = i;
    std::cin >> auxCity.x;
    std::cin >> auxCity.y;
    cities.push_back(auxCity);
  }

  //std::cout << "Filled the array of cities" << std::endl;

  visitedCities.push_back(cities[0].id);
  //printCities(cities);
  visitedCities = travelToNearestCities(cities, visitedCities, &travelledDistance);
  //Show reuslts 
  int isOptimalSolution = 0;
  std::cout << travelledDistance << " " << isOptimalSolution << std::endl; 
  printVector(visitedCities);
  
  //std::cout << "terminou" << std::endl;
}
