#include <omp.h>
#include <cmath>
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct City {
    int id;
    float x, y;
};

std::vector<City> load_cities(int qtd_cities) {
    std::vector<City> cities;
    City c;
    for (int i = 0; i < qtd_cities; i++) {
        cin >> c.x;
        cin >> c.y;
        c.id = i;
        cities.push_back(c);
    }
    return cities;
}

float get_distance(City c1, City c2) {
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2) * 1.0);
}

float visit_cities(std::vector<City> cities) {
    float dist = 0.0;
    for (size_t i = 0; i < cities.size() - 1; i++) {
        dist += get_distance(cities[i], cities[i + 1]);
    }

    City first_city = cities[0];
    City last_city  = cities[cities.size() - 1];
    dist += get_distance(last_city, first_city);
    return dist;
}

void print_results(float total_dist, std::vector<City> cities) {
    std::cout << total_dist;
    std::cout << " 0" << std::endl;

    for (size_t i = 0; i < cities.size(); i++) {
        std::cout << cities[i].id << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
    int SEED = 777;
    int qtd_cities, qtd_solutions;
    float best_distance;

    std::cin >> qtd_cities;
    qtd_solutions = 10 * qtd_cities;
    default_random_engine generator(SEED);

    // load cities
    std::vector<City> cities = load_cities(qtd_cities);
    std::vector<City> cities_best_distance = cities;
    best_distance = visit_cities(cities_best_distance);

    #pragma omp parallel for

    for (int i = 0; i < qtd_solutions; i++) {
        std::vector<City> solution = cities;
        shuffle(solution.begin(), solution.end(), generator);
        float dist = visit_cities(solution);

        #pragma omp parallel for

        for (int j = 0; j < qtd_cities - 1; j++) {
            swap(solution[j], solution[j + 1]);
            float crnt_dist = visit_cities(solution);
            if (crnt_dist < dist) {
                dist = crnt_dist;
            } else {
                swap(solution[j], solution[j + 1]);
            }
        }

        #pragma omp critical
        {
            if (dist < best_distance) {
                best_distance = dist;
                cities_best_distance = solution;
            }
        }
    }
    print_results(best_distance, cities_best_distance);
    return 0;
}