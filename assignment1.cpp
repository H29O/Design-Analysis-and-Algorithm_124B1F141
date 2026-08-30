#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;


struct Order
{
   string orderID;
   string orderDate;
};


void merge(vector<Order>& orders, int left, int mid, int right)
{
   int n1 = mid - left + 1;
   int n2 = right - mid;
   vector<Order> L(n1), R(n2);
   for (int i = 0; i < n1; i++)
       L[i] = orders[left + i];
   for (int j = 0; j < n2; j++)
       R[j] = orders[mid + 1 + j];
   int i = 0;
   int j = 0;
   int k = left;
   while (i < n1 && j < n2)
   {
       if (L[i].orderDate <= R[j].orderDate)
       {
           orders[k] = L[i];
           i++;
       }
       else
       {
           orders[k] = R[j];
           j++;
       }
       k++;
   }
   while (i < n1)
   {
       orders[k] = L[i];
       i++;
       k++;
   }
   while (j < n2)
   {
       orders[k] = R[j];
       j++;
       k++;
   }
}
void mergeSort(vector<Order>& orders, int left, int right)
{
   if (left < right)
   {
       int mid = left + (right - left) / 2;


       mergeSort(orders, left, mid);
       mergeSort(orders, mid + 1, right);
       merge(orders, left, mid, right);
   }
}
int main()
{
   ifstream file("ecommerce_dataset_+1m.csv");
   if (!file)
   {
       cout << "Error opening file!" << endl;
       return 1;
   }
   cout << "File opened successfully!" << endl;
   string line;
   // Skip the header row
   getline(file, line);
   vector<Order> orders;
   while (getline(file, line))
   {
      stringstream ss(line);
      Order order;
      getline(ss, order.orderID, ',');
      getline(ss, order.orderDate, ',');
      orders.push_back(order);
   }
   cout << "Total Orders Read : " << orders.size() << endl;
   mergeSort(orders, 0, orders.size() - 1);
   cout << "\nFirst 20 Sorted Customer Orders:\n\n";
   cout << "Order ID\tOrder Date\n";
   cout << "-----------------------------------------------\n";
   for (int i = 0; i < 20 && i < orders.size(); i++)
   {
      cout << orders[i].orderID << "\t" << orders[i].orderDate << endl;
   }
   file.close();
   return 0;
