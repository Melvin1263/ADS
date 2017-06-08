#include <iostream>
#include <string>
#include "P4_graph.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void displayMenu()
{
    std::cout << "Working on Grphs. Please choose:" << std::endl
              << "1) Graph einlesen" << std::endl
              << "2) Tiefensuche" << std::endl
              << "3) Breitensuche "<< std::endl
              << "4) Prim" << std:: endl
              << "5) Kruskal" << std::endl
              << "6) Print Graph as nodelist" << std::endl
              << "0) for quit" << std::endl
              << "?> ";
}


int main() {


    //Insert a switch-case to call your algorithms
    //Maybe you can copy from older Projects
    Graph* myGraph = new Graph();
    int menuwahl=-1;
    int key=-1;

    myGraph->init("graph1.txt");
    std::cout << "MST (krus): " << myGraph->kruskal() << std::endl;
    std::cout << "MST (prim): " << myGraph->prim(0) << std::endl;

    while(menuwahl != 0){

        do{
            displayMenu();
            std::cin >> menuwahl;
        }while(menuwahl>6 || menuwahl <0);

        //Read Graph
        if(menuwahl==1)
        {
            std::string path;
            std::cout << "Insert path of Graphfile: " << std::endl;
            std::cin >> path;

            bool done = myGraph->init(path);

            if(done)
                std::cout << "Initialize graph successful" << std::endl;
            else
                std::cout << "Cannot read file" << std::endl;
        }

        //Depthsearch
        if(menuwahl==2)
        {

            std::cout << "Choose a startkey: " << std::endl;
            std::cin >> key;

            //This way:
            if(myGraph->depthSearchIter(key))
                std::cout << "Depthsearch successful!" << std::endl;
            else
                std::cout << "Depthsearch not successful!" << std::endl;

            //Or this:
            //myGraph.depthSearchRek(key);
        }

        //Breadthsearch
        if(menuwahl==3){

            std::cout << "Choose a startkey: " << std::endl;
            std::cin >> key;

            //This way:
            if(myGraph->breadthSearchIter(key))
                std::cout << "Breadthsearch successful!" << std::endl;
            else
                std::cout << "Breadthsearch not successful!" << std::endl;

            //Or this:
            //myGraph->breadthSearchRek(key);
        }

        //Prim
        if(menuwahl==4){
            std::cout << "Choose a startkey: " << std::endl;
            std::cin >> key;
            myGraph->prim(key);
        }

        //Kruskal
        if(menuwahl==5){
            myGraph->kruskal();
        }

        //Print function
        if(menuwahl==6){
            bool done = myGraph->print();

            if(done)
                std::cout << "Print graph successful" << std::endl;
            else
                std::cout << "Not able to print" << std::endl;
        }

        //Quit
        if(menuwahl==0){
            delete myGraph;
        }
    }

    return 0;
}
