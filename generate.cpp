#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

void printUsage(char* name) {
    std::cout << "usage: " << name << " -n number_to_generate -o output_file" << std::endl;
}

void printInvalidArgument() {
    std::cout << "invalid argument" << std::endl;
}

int main(int argc, char *argv[]) {
    /* Must provide -n and -o argument */
    if (argc != 5 || strncmp(argv[1], "-n", 3) != 0 || strncmp(argv[3], "-o", 3) != 0) {
        printUsage(argv[0]);
        return 1;
    }
    
    /* Parse n */
    int n = 10;
    
    try {
        int nArg = std::stoi(argv[2]);
        n = nArg;
    } catch (std::invalid_argument &e) {
        printInvalidArgument();
        printUsage(argv[0]);
        return 1;
    }
    
    /* Open output file */
    char* outputFilename = argv[4];
    std::ofstream out;
    out.open(outputFilename, std::ofstream::out);
    
    /* Seed random number generator with current time */
    std::srand(std::time(0));
    
    /* Print n random numbers */
    for (int i = 0; i < n; i++) {
        out << std::rand() << "\n";
    }
    
    /* Flush and close output file */
    out.close();
        
    return 0;
}
