#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>


using namespace std;


struct Car
{
   string carName;
   string fuelType;
   string carBody;
   int horsePower;
   int cityMPG;
   int highwayMPG;
   float price;
};


int partition(vector<Car>& cars, int low, int high)
{
   float pivot = cars[high].price;
   int i = low - 1;


   for(int j = low; j < high; j++)
   {
       if(cars[j].price > pivot)
       {
           i++;
           swap(cars[i], cars[j]);
       }
   }


   swap(cars[i + 1], cars[high]);
   return i + 1;
}


void quickSort(vector<Car>& cars, int low, int high)
{
   if(low < high)
   {
       int p = partition(cars, low, high);
       quickSort(cars, low, p - 1);
       quickSort(cars, p + 1, high);
   }
}


int main()
{
   vector<Car> cars;


   ifstream file("CarPrice_Assignment.csv");


   if(!file)
   {
       cout << "File not found!";
       return 0;
   }


   string line;


   getline(file, line);


   while(getline(file, line))
   {
       stringstream ss(line);
       string data[26];


       for(int i = 0; i < 26; i++)
       {
           getline(ss, data[i], ',');
       }


       try
       {
           Car c;


           c.carName = data[2];
           c.fuelType = data[3];
           c.carBody = data[6];
           c.horsePower = stoi(data[21]);
           c.cityMPG = stoi(data[23]);
           c.highwayMPG = stoi(data[24]);
           c.price = stof(data[25]);


           cars.push_back(c);
       }
       catch(...)
       {
           continue;
       }
   }


   file.close();


   quickSort(cars, 0, cars.size() - 1);


   cout << "\nCars Sorted By Price (Highest to Lowest)\n\n";


   cout << left
        << setw(5) << "No."
        << setw(28) << "Car Name"
        << setw(10) << "Fuel"
        << setw(15) << "Body"
        << setw(12) << "HP"
        << setw(10) << "City"
        << setw(10) << "Highway"
        << setw(12) << "Price"
        << endl;


   cout << "---------------------------------------------------------------------------------------------\n";


   int limit = 20;


if(cars.size() < limit)
   limit = cars.size();


for(int i = 0; i < limit; i++)
   {
       cout << left
            << setw(5) << i + 1
            << setw(28) << cars[i].carName.substr(0,27)
            << setw(10) << cars[i].fuelType
            << setw(15) << cars[i].carBody
            << setw(12) << cars[i].horsePower
            << setw(10) << cars[i].cityMPG
            << setw(10) << cars[i].highwayMPG
            << setw(12) << cars[i].price
            << endl;
   }
