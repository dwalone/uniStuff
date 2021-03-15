// PHYS 30762 Programming in C++
// Assignment 4
// Rutwik Mudholkar 01/03/21
// Simple demonstration of a C++ class
#include<iostream>
#include<string>
#include<vector>
#include<cmath>

class galaxy
{
private:
    std::string hubble_type{};
    double redshift{};
    double total_mass{};
    double stellar_mass_fraction{};
    std::vector<galaxy> satellites; 

public:
    // Constructors
    galaxy() = default;

    galaxy(std::string galaxy_hubble_type, double galaxy_redshift, double galaxy_total_mass, double galaxy_stellar_mass_fraction)
    {
        hubble_type = galaxy_hubble_type; 
        redshift = galaxy_redshift; 
        total_mass = galaxy_total_mass; 
        stellar_mass_fraction = galaxy_stellar_mass_fraction;
    }

    // Destructor
    ~galaxy() {return;}

    // Return stellar mass (M_* = f_* x M_tot)
    double stellar_mass() {return stellar_mass_fraction * total_mass;}
    // Change galaxy's Hubble type
    void change_type(std::string new_type) {hubble_type = new_type;}
    // Prototype for function to print out an object's data
    void print_data(int idx, std::string galaxy_or_satellite);
    // Add satellite galaxy
    void add_satellite(galaxy satellite) {satellites.push_back(satellite);}

};

// Print out an object's data
void galaxy::print_data(int idx, std::string galaxy_or_satellite)
{
    std::cout.precision(3); // 2 significant figures
    std::cout<<galaxy_or_satellite<<" "<<idx<<" : ["
    <<hubble_type<<", "<<redshift<<", "<<total_mass<<", "<<stellar_mass_fraction<<"]"<<std::endl;

    if (galaxy_or_satellite == "Galaxy")
    {
        std::cout<<"Number of satellites : "<<satellites.size()<<std::endl;
    }

    // Recursion for satellites    
    for(auto satellite_it=satellites.begin(); satellite_it<satellites.end(); ++satellite_it)
    {
        satellite_it->print_data(satellite_it-satellites.begin()+1, "Satellite");
    }

    return;
}

// End of class and associated member functions

// Main program
int main()
{
    const double solar_mass{1.9891e30};

    std::vector<galaxy> galaxy_data;

    // Example using default constructor
    galaxy g1; 

    // Example using parameterised constructor
    galaxy g2{"Irr", 6.4, (1.1e10)*solar_mass, 0.035};
    galaxy g2s1{"Sa", 5.3, (2.3e7)*solar_mass, 0.001};
    galaxy g2s2{"Sb", 4.2, (3.5e7)*solar_mass, 0.002};

    galaxy g3{"E0", 9.2, (8.7e11)*solar_mass, 0.044};
    galaxy g3s1{"E5", 6.5, (2.1e8)*solar_mass, 0.0003};

    // Change Hubble type from Irr to S0
    g2.change_type("S0");

    // Add satellite galaxies
    g2.add_satellite(g2s1);
    g2.add_satellite(g2s2);
    g3.add_satellite(g3s1);

    // print out data
    galaxy_data.push_back(g1);
    galaxy_data.push_back(g2);
    galaxy_data.push_back(g3);

    std::cout<<"Galaxy/Satellite [n] : [Hubble type, redshift, total mass (kg), stellar mass fraction]"<<std::endl;
    std::cout<<std::endl;

    for(auto galaxy_it=galaxy_data.begin(); galaxy_it<galaxy_data.end(); ++galaxy_it)
    {
        galaxy_it->print_data(galaxy_it-galaxy_data.begin()+1, "Galaxy");

        // Get and print out stellar mass
        std::cout<<"Galaxy stellar mass : "<<galaxy_it->stellar_mass()<<" kg"<<std::endl;
        std::cout<<std::endl;
    }

    return 0;
}