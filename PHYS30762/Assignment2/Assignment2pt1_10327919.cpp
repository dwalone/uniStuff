// PHYS 30762 Programming in C++
// Assignment 2 pt 1
// Rutwik Mudholkar 09/02/21
// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<limits>
#include<string>

// Functions to compute mean and standard deviation
double mean_calculation(double *marks, int Ndata)
{
    double sum{};
    for(int i{}; i<Ndata; i++)
    {
        sum += marks[i];
    }
    return sum/Ndata;
}

double sd_calculation(double *marks, double mean, int Ndata)
{
    double sum{};
    for(int i{}; i<Ndata; i++)
    {
        sum += std::pow(marks[i]-mean, 2);
    }
    return std::pow(sum/(Ndata-1), 0.5);    
}

// Main function
int main()
{
    char data_file[100];

    // Ask user to enter filename
    std::cout<<"Enter data filename: ";
    std::cin>>data_file;

    // Open file and check if successful
    std::fstream course_stream(data_file);
    while(course_stream.good()==0) 
    {
        std::cout << "File not found, try again : ";
        std::cin >> data_file; 
        course_stream.open(data_file);      
    }

    // Get number of courses
    int Ndata{};
    std::string line;
    while(std::getline(course_stream, line))
    {
        Ndata += 1;       
    }
    course_stream.clear();
    course_stream.seekg(0);

    // Allocate memory for data 
    double* marks = new double[Ndata];

    // Read data from file
    for(int i{}; i<Ndata; i++) 
    {
        std::getline(course_stream, line);
        std::stringstream(line) >> marks[i];     
    }

    // Close file
    course_stream.close();

    // Print number of courses read in
    std::cout<<"Number of courses : "<<Ndata<<std::endl;

    // Compute mean, standard deviation and  standard error of mean
    double mean = mean_calculation(marks, Ndata);
    double sd = sd_calculation(marks, mean, Ndata);
    std::cout<<std::setprecision(3)<<"Mean mark : "<<mean<<std::endl;
    std::cout<<std::setprecision(3)<<"Standard deviation of mark : "<<sd<<std::endl;
    std::cout<<std::setprecision(3)<<"Standard error in mean : "<<sd/std::pow(Ndata, 0.5)<<std::endl;

    // Free memory
    delete[] marks;

    return 0;
}