// Assignment 1
// Rutwik Mudholkar 09/02/21
// Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include<cmath>
#include<limits>

double find_energy_of_level(int n, int z) {
    double level_energy;
    level_energy = 13.6*std::pow(z, 2)*std::pow(n, -2);
    return level_energy;     
}

int main() {

    const double ev_to_j{1.602e-19};
    char repeat{'y'};

    while (repeat == 'y') {
        int z;
        int n_i;
        int n_j;
        char unit;

        std::cout << "Atomic number : ";
        std::cin >> z; 
        while(std::cin.fail() || z < 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Must be a positive integer, try again : ";
            std::cin >> z;        
        }   


        std::cout << "Initial quantum number : ";
        std::cin >> n_i; 
        while(std::cin.fail() || n_i < 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Must be a positive integer, try again : ";
            std::cin >> n_i;        
        }

        std::cout << "Final quantum number : ";
        std::cin >> n_j; 
        while(std::cin.fail() || n_j > n_i || n_j < 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Must be a positive integer less than initial quantum number : ";
            std::cin >> n_j;        
        }


        std::cout << "In J or eV? [J/e] : ";
        std::cin >> unit; 
        while(std::cin.fail() || (unit != 'J' && unit != 'e')) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input; In J or eV? [J/e] : ";
            std::cin >> unit;        
        }

        if (unit=='e') {
            std::cout<<"Energy of transition : "
                <<std::setprecision(3)
                <<find_energy_of_level(n_j, z) - find_energy_of_level(n_i, z)
                <<" eV"
                <<std::endl;
        }
        
        else {
            std::cout<<"Energy of transition : "
                <<std::setprecision(3)
                <<(find_energy_of_level(n_j, z) - find_energy_of_level(n_i, z))*ev_to_j
                <<" J"
                <<std::endl;
        }

        std::cout << "Repeat? [y/n]: ";
        std::cin >> repeat;
        while(std::cin.fail() || (repeat != 'y' && repeat != 'n')) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input; Repeat? [y/n]: ";
            std::cin >> repeat;        
        } 

    }
    return 0;
}
