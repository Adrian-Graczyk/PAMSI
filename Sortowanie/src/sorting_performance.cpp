#include "timer.hpp"
#include "sorting/sorting.hpp"


#include <thread>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std::chrono_literals;

void readData(char const* path, std::vector<int>& tab)
{
    std::ifstream ifs{path, std::fstream::binary};

    while(ifs)
    {
        int element;
        ifs.read(reinterpret_cast<char*>(&element), sizeof(element));

        if(ifs)
        {
            tab.push_back(element);
        }
    }
}

void display(std::vector<int>& tab)
{
    std::cout<<std::endl<<"tablica:"<<std::endl;
    for(int i=0; i<tab.size(); i++)
    std::cout<<tab[i]<<std::endl;
}

int main(int argc, char* argv[])
{
    Timer timer;
    
    std::vector<char const*> files = {"sort_data_1000000.bin","sort_data_5000000.bin", "sort_data_10000000.bin","sort_data_15000000.bin",
    "sort_data_30000000.bin","sort_data_50000000.bin","sort_data_100000000.bin","sort_data_150000000.bin"};
    std::vector<char const*> data_size = {"1000000","5000000","10000000","15000000","30000000","50000000","100000000","150000000"};
    std::vector<char const*>  sort_type= {"Quick", "Merge", "Heap"};


    for(int i=0; i<files.size(); i++)
    {
        std::vector<int> tab;
        std::cout << "Merge sort for data size: "<<data_size[i]<<std::endl;
        readData(files[i], tab);
        timer.start();
        mergeSort(tab, 0, tab.size()-1);
        timer.stop();
        std::cout << "Sorting time: " << timer.sInterval() << std::endl<<std::endl;
    }

    for(int i=0; i<files.size(); i++)
    {
        std::vector<int> tab;
        std::cout << "Quick sort for data size: "<<data_size[i]<<std::endl;
        readData(files[i], tab);
        timer.start();
        quickSort(tab, 0, tab.size()-1);
        timer.stop();
        std::cout << "Sorting time: " << timer.sInterval() << std::endl<<std::endl;  
    }   

   for(int i=0; i<files.size(); i++)
    {
        std::vector<int> tab;
        std::cout << "heap sort for data size: "<<data_size[i]<<std::endl;
        readData(files[i], tab);
        timer.start();
        heapSort(tab);
        timer.stop();
        std::cout << "Sorting time: " << timer.sInterval() << std::endl<<std::endl;
    } 



    // Sposób prezentacji dla lepszego porównania 
    /*for(int i=0; i<files.size(); i++)
    {
        std::cout<<std::endl<< "sort for data size: "<<data_size[i]<<std::endl<<std::endl;

        std::vector<int> tab, tab2, tab3;
        readData(files[i], tab);
        readData(files[i], tab2);
        readData(files[i], tab3);

        timer.start();
        quickSort(tab, 0, tab.size()-1);
        timer.stop();
        std::cout<<"Quick sorting time: " << timer.sInterval() << std::endl<<std::endl;

        timer.start();
        mergeSort(tab2, 0, tab2.size()-1);
        timer.stop();
        std::cout<<"Merge sorting time: " << timer.sInterval() << std::endl<<std::endl;

        timer.start();
        heapSort(tab3);
        timer.stop();
        std::cout<<"Heap sorting time: " << timer.sInterval() << std::endl<<std::endl; 
    } */



    return 0;
}
