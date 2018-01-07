#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <queue>

void printUsage(char* name) {
    std::cout << "usage: " << name << " -o output_file -f input_file ..." << std::endl;
}

struct Seq {
    int value;
    std::ifstream source;
    
    Seq(char* filename) : source(filename) {}
};

bool next(Seq* seq) {
    if (seq->source.good()) {
        seq->source >> seq->value;
        return true;
    }
    
    return false;
}

void merge(std::vector<Seq*>& sequences, std::ofstream& output) {
    /* Greater<Seq*> comparator for Seq* to create min heap */
    auto comp = []( const Seq* lhs, const Seq* rhs ) { return lhs->value > rhs->value; };
    std::priority_queue<Seq*, std::vector<Seq*>, decltype(comp)> pq(sequences.begin(), sequences.end(), comp);
    
    while(!pq.empty()) {
        Seq* top = pq.top();
        pq.pop();
        
        output << top->value << '\n';
        if(next(top)) {
            pq.push(top);
        }
    }
}

int main(int argc, char *argv[]) {
    /* Must provide -o and -f */
    if (argc < 5 || strncmp(argv[1], "-o", 3) != 0 || strncmp(argv[3], "-f", 3) != 0) {
        printUsage(argv[0]);
        return 1;
    }
    
    char* outputFilename = argv[2];
    std::ofstream output(outputFilename);
    
    std::vector<Seq*> sequences = std::vector<Seq*>();
    
    for (int i = 4; i < argc; i++) {
        char* inputFilename = argv[i];
        Seq* seq = new Seq(inputFilename);
        if(next(seq)) {
            sequences.push_back(seq);
        }
    }
    
    merge(sequences, output);
    output.close();
    
    return 0;
}
