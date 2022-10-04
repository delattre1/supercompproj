#include <iostream>
#include <iomanip>
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


void exchangeCities(City &c1, City &c2) {
  City tmpCity = c1;
  c1 = c2;
  c2 = tmpCity;
}

float travelThroughCities(std::vector<City> cities) {
  // Percorrer todos os elementos do vector
  // Calcula a distancia total e devolve esse valor
  City origCity, destCity;
  float dist, travelledDistance;

  for (int idx=0; idx < cities.size(); idx++) {
    if (idx == cities.size()) {
      // Get distance to get back to the first city
      origCity = cities.back();
      destCity = cities.front();
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

void findBestRoute(std::vector<City> &citiesShortestDistance, std::vector<City> cities, int left, int right, double &shortestDistance, long int &nleaf) {
  if (left == right) {
    nleaf++;
    double dist = travelThroughCities(cities);
    if (dist < shortestDistance) {
      shortestDistance = dist;
      citiesShortestDistance = cities;
    }
    return;
  }

  for (int i = left; i <= right; i++) {
    exchangeCities(cities[left], cities[i]);
    findBestRoute(citiesShortestDistance, cities, left + 1, right, shortestDistance, nleaf);
    exchangeCities(cities[left], cities[i]);
  }
}

int main() {
  int qtyCities;
  float travelledDistance = 0;
  long int nleaf = 0;

  std::vector<City> cities, citiesCopy;
  std::vector<int>  visitedCities;
  std::vector<City> citiesShortestDistance;

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

  double shortestDistance = travelThroughCities(cities);
  citiesShortestDistance = cities;

  findBestRoute(citiesShortestDistance, cities, 0, cities.size() - 1, shortestDistance, nleaf);
  std::cerr << "num_leaf " << nleaf / qtyCities << std::endl;
  std::cout << shortestDistance << std::setprecision(2) << " 1" << std::endl;

  for (City city : citiesShortestDistance)
    std::cout << city.id << " ";
  std::cout << std::endl;
}
