#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "FileOperations.h"
#include "Route.h"
#include "GraphFunctions.h"

using namespace std;

class ShortestPathFinder {
public:
    ShortestPathFinder(int argc, char* argv[]) {
        if (argc > 1) citiesFilename = argv[1];
        else getInput("Enter filename containing cities: ", citiesFilename);

        if (argc > 2) routesFilename = argv[2];
        else getInput("Enter filename containing routes: ", routesFilename);

        if (argc > 3) outputFilename = argv[3];
        else getInput("Enter filename for output (.html): ", outputFilename);

        if (argc > 4) origin = argv[4];
        else getInput("Origin: ", origin);

        if (argc > 5) destination = argv[5];
        else getInput("Destination: ", destination);

        if (argc > 6) preference = argv[6];
        else getInput("Enter a preference (fastest/cheapest): ", preference);

        biPreference = preference == "cheapest";
    }

    void run() {
        Graph graph(citiesFilename, routesFilename);

        if (graph.getCity(origin) == nullptr || graph.getCity(destination) == nullptr) {
            cout << "Invalid entry" << endl;
            return;
        }

        graph.Dijkstras(origin, biPreference);

        stack<Location*> cityStack = graph.cityStacker(destination);
        stack<Route*> routeStack = graph.routeStacker(destination, biPreference);

        outputGenerator(outputFilename.c_str(), cityStack, routeStack, biPreference);
    }

private:
    string citiesFilename;
    string routesFilename;
    string outputFilename;
    string origin;
    string destination;
    string preference;
    bool biPreference;

    void getInput(const string& prompt, string& input) {
        cout << prompt;
        cin >> input;
    }
};

int main(int argc, char* argv[]) {
    ShortestPathFinder pathFinder(argc, argv);
    pathFinder.run();
    return 0;
}
