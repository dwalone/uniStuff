// PHYS 30762 Programming in C++
// Assignment 2 pt 2
// Rutwik Mudholkar 09/02/21
// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<limits>
#include<string>
#include<vector>
#include<algorithm>

// Functions to compute mean and standard deviation
double mean_calculation(std::vector<double> marks)
{
    double sum{};
    for (auto iterator=marks.begin(); iterator!=marks.end(); iterator++)
    {
        sum += *iterator;
    }
    return sum/marks.size();
}

double sd_calculation(std::vector<double> marks, double mean)
{
    double sum{};
    for (auto iterator=marks.begin(); iterator!=marks.end(); iterator++)
    {
        sum += std::pow(*iterator-mean, 2);
    }
    return std::pow(sum/(marks.size()-1), 0.5);    
}

// Function to order courses by name
bool cmp(const std::string &lhs, const std::string &rhs) 
{
    return lhs[8] < rhs[8];
}

// Main function
int main()
{
    char data_file[100];
    int year;
    std::vector<std::string> courses;
    std::vector<double> marks;

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

    // Ask user to enter year
    std::cout<<"Enter a year : ";
    std::cin>>year;
    while(std::cin.fail() || year < 1 || year > 4) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Must be 1, 2, 3 or 4 : ";
        std::cin >> year;        
    }


    // Get courses and marks for year
    std::string line;
    int divider_pos;
    int course_year;
    double mark;
    while(std::getline(course_stream, line))
    {
        divider_pos = line.find_first_of(" ");
        course_year = static_cast<int>(line[divider_pos + 1]) - 48;
        if (course_year == year)
        {
            courses.push_back(line.substr(divider_pos+1));
            std::stringstream(line) >> mark;
            marks.push_back(mark);
        }       
    }

    // Ask user for order type
    bool sort_type;
    std::cout<<"Sort by Code or Title? [0/1] : ";
    std::cin>>sort_type;
    while(std::cin.fail()) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, Sort by Code or Title? [0/1] : ";
        std::cin >> sort_type;        
    }   

    // Order courses
    std::vector<std::string>::iterator iterator;
    if (sort_type)
    {
        std::sort(courses.begin(), courses.end(), cmp);
    } else {
        std::sort(courses.begin(), courses.end());
    }
    
    // Print ordered courses
    for(iterator=courses.begin(); iterator<courses.end(); iterator++)
    {
        std::cout<<*iterator<<std::endl;
    }

    // Print number of courses read in
    std::cout<<"Number of courses : "<<courses.size()<<std::endl;

    // Compute mean, standard deviation and  standard error of mean
    double mean = mean_calculation(marks);
    double sd = sd_calculation(marks, mean);
    std::cout<<std::setprecision(3)<<"Mean mark : "<<mean<<std::endl;
    std::cout<<std::setprecision(3)<<"Standard deviation of mark : "<<sd<<std::endl;
    std::cout<<std::setprecision(3)<<"Standard error in mean : "<<sd/std::pow(courses.size(), 0.5)<<std::endl;

    return 0;
}