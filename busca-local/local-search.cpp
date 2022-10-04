#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm> // std::random_shuffle
#include <limits>


struct City {  
  int id;
  float x,y;
};

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
  std::cout << "(x,y): ";
  for (int i=0; i < cities.size(); i++) {
    std::cout << "(" << cities[i].x << "," << cities[i].y << ") ";
  }
  std::cout << std::endl;
}

void cerrCitiesIdx(std::vector<City> cities) {
  for (int i=0; i < cities.size(); i++) {
    std::cerr << cities[i].id << " ";
  }
   std::cerr << std::endl;
}

float travelThroughCities(std::vector<City> cities) {
  // Percorrer todos os elementos do vector
  // Calcula a distancia total e devolve esse valor
  City origCity, destCity;
  float dist, travelledDistance;

  for (int idx=0; idx < cities.size(); idx++) {
    if (idx == cities.size()) {
      // Get distance to get back to the first city
      origCity = cities.front();
      destCity = cities.back();
    }

    else {
      origCity = cities[idx];
      destCity = cities[idx + 1];
    }

    dist = getDistance(origCity, destCity);
    travelledDistance += dist;
  }
  return travelledDistance;
}


float swapCities(std::vector<City> *pCities) {
  // Receives a vector of cities
  // In a loop swap pairs of cities, and check if it's more efficient
  // When it is, keep swaping, else stop
  std::vector<City> cities = *pCities;
  std::vector<City> citiesMinDistance = cities;

  //printCities(cities);
  float travelledDistance;
  float minDistance =  travelThroughCities(cities);

  City c1, c2;
  int idx1 = 0;
  int idx2 = 1;

  for (int idx1=0; idx1 < cities.size() - 1; idx1++) {
    for (int idx2=idx1+1; idx2 < cities.size(); idx2++) {
      c1 = cities[idx1];
      c2 = cities[idx2];

      cities[idx1] = c2;
      cities[idx2] = c1;
      travelledDistance = travelThroughCities(cities);
      
      //DEBUG
      //std::cout << "minD: " << minDistance << ", foundDist: " << travelledDistance << std::endl;
      //std::cout << "idx1, idx2: " << idx1 << ", " << idx2 << " | ";
      //printCities(cities);

      if (travelledDistance < minDistance) {
        minDistance = travelledDistance;
        citiesMinDistance = cities;
      }
      else {
        // The swap did not improve
        // Return minDistance and current distribution of cities;
        *pCities = cities;
        return minDistance;
      }
    }
  }
  *pCities = cities;
  return minDistance;
}

int main() {
  int qtyCities;
  float travelledDistance = 0;

  std::vector<City> cities, citiesCopy;
  std::vector<int>  visitedCities;

  //Fill array of cities
  std::cin >> qtyCities;
  int times_to_shuffle = 10 * qtyCities;
  City auxCity;
  for (int i=0; i < qtyCities; i++) {
    auxCity.id = i;
    std::cin >> auxCity.x;
    std::cin >> auxCity.y;
    cities.push_back(auxCity);
  }
  
  citiesCopy = cities;
  // Apos receber o vector de cidades
  // Shuffle 10 vezes e salvar cada shuffle como o elemento de outro vector
  // Para cada shuffle, vai rodar o sort e tentar encontrar o minimo local
  unsigned seed = 0;
  std::vector<std::vector<City>> shuffledCities; // [[randomCities1], [randomCities2], ... [randomCities10]]
  
  //DO THE SHUFFLING (create vector with TIMES_TO_SHUFFLE copies of cities in random positions)
  for (int i=0; i < times_to_shuffle; i++) {
    std::shuffle (citiesCopy.begin(), citiesCopy.end(), std::default_random_engine(seed));
    shuffledCities.push_back(citiesCopy);
  }
  
  float dist;
  float shortestDistance = -1;
  std::vector<City> citiesShortestDistance;
  
  for (int i=0; i < times_to_shuffle; i++) {
    // For each shuffled vector of cities;
    // Run the swapping
    std::vector<City> currentCities = shuffledCities[i];
    dist = swapCities(&currentCities);

    // A cada sorteio e busca pelo mínimo local 
    // (após o todo o processo de trocas para aquele sorteio), 
    // seu programa deverá mostra em uma linha da saída de erros a seguinte linha:
    std::cerr << "local: " << dist << " ";
    // Imprime a sequencia de cidades
    cerrCitiesIdx(currentCities); 

    if (shortestDistance == -1) {
      shortestDistance = dist;
      citiesShortestDistance = currentCities;
    };

    if (shortestDistance == -1 or dist < shortestDistance) {
      shortestDistance = dist;
      citiesShortestDistance = currentCities;
    }
    //std::cout << "shortest: " << shortestDistance << " --- result --- idx: " << i << " dist: " << dist << "\n" << std::endl;
  }

  int isOptimalSolution = 0;
  std::cout << shortestDistance << " " << isOptimalSolution << std::endl; 

  //std::cout << "--FINISHED--\n" << std::endl;
  //printCities(citiesShortestDistance);


  for (int i=0; i < citiesShortestDistance.size(); i++) {
    std::cout << citiesShortestDistance[i].id << " ";
  }
  std::cout << std::endl;
}
