#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

void printUsage(char* name) {
    std::cout << "usage: " << name << " -f input_file" << std::endl;
}

std::vector<int> readFromFile(char* filename) {
    std::vector<int> values = std::vector<int>();
    
    /* Open input file */
    std::ifstream in(filename);
    
    /* Read all integers from file */
    if(in) {
        int v;
        while(in >> v) {
            values.push_back(v);
        }
    }
    
    in.close();
    
    return values;
}

void writeToFile(char* filename, std::vector<int> &values) {
    /* Open output file */
    std::ofstream out;
    out.open(filename, std::ofstream::out);
    
    /* Write all integers to file */
    for(int v : values) {
        out << v << "\n";
    }
    
    out.close();
}

void swap(std::vector<int> &values, int firstIndex, int secondIndex) {
    int tmp = values[firstIndex];
    values[firstIndex] = values[secondIndex];
    values[secondIndex] = tmp;
}

void sortHelper(std::vector<int> &values, int start, int end) {
    /* Check if already sorted */
    if(end - start <= 1) return;

    /* Pick the first element as the pivot,
       we already know the elements are random
       so this is as good as a random pivot */
    int pivot = values[start];

    int swapIndex = start + 1;
    for(int index = start + 1; index < end; index++) {
        /* Move elements smaller than pivot value to the front
           of the list */
        if(values[index] < pivot) {
            swap(values, index, swapIndex);
            swapIndex++;
        }
    }

    /* Swap pivot to appropriate point in list,
       since elements to the left of the pivot are smaller,
       and the pivot is at the zeroth position,
       it should swap with a smaller value, i.e. swapIndex - 1 */
    swap(values, start, swapIndex - 1);

    /* Sort sublists */
    sortHelper(values, start, swapIndex);
    sortHelper(values, swapIndex, end);
}

void sort(std::vector<int> &values) {
    sortHelper(values, 0, values.size());
}

int main(int argc, char *argv[]) {
    /* Must provide -f */
    if (argc != 3 || strncmp(argv[1], "-f", 3) != 0) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::vector<int> values = readFromFile(argv[2]);
    sort(values);
    writeToFile(argv[2], values);
    
    return 0;
}
