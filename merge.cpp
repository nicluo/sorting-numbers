#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

void printUsage(char* name) {
    std::cout << "usage: " << name << " -o output_file -f input_file ..." << std::endl;
}

struct Seq {
    int value;
    std::ifstream source;
    
    Seq(char* filename) : source(filename) {}
    
    bool operator < (const Seq& rhs) { return value < rhs.value; }
};

bool next(Seq* seq) {
    if (seq->source.good()) {
        seq->source >> seq->value;
        return true;
    }
    
    return false;
}

struct Node {
    Seq* seq;
    Node* left;
    Node* right;
    
    Node(Seq* seq) : seq(seq), left(nullptr), right(nullptr) {}
    
    bool operator < (const Node& rhs) { return *seq < *(rhs.seq); }
};

Node* insert(Node* node, Node* tree) {
    if(tree == NULL) {
        return node;
    }
    
    if(*node < *tree) {
        tree->left = insert(node, tree->left);
    } else {
        tree->right = insert(node, tree->right);
    }
    
    return tree;
}

Node* getMinimum(Node* tree) {
    /* Should never reach this base case */
    if (tree == NULL) {
        return NULL;
    }
    
    /* Keep traversing to the left */
    if (tree->left == NULL) {
        return tree;
    } else {
        return getMinimum(tree->left);
    }
}

Node* popMinimum(Node* tree) {
    /* Should never reach this base case */
    if (tree == NULL) {
        return NULL;
    }
    
    /* If there are no left childs, this must be the minimum, since we're
     popping this element, this should be replaced by the right child node.
     In this case, the right child node should be removed. */
    if (tree->left == NULL) {
        if(tree->right == NULL) {
            return NULL;
        } else {
            Node* right = tree->right;
            tree->right = NULL;
            return right;
        }
    } else {
        tree->left = popMinimum(tree->left);
        return tree;
    }
}

void merge(std::vector<Seq*>& sequences, std::ofstream& output) {
    Node* tree = NULL;
    
    /* Initialize nodes and build the tree from non-empty sequences */
    for (Seq* s : sequences) {
        Node* node = new Node(s);
        tree = insert(node, tree);
    }
    
    while(tree != NULL) {
        /* Get and pop minimum element */
        Node* minimum = getMinimum(tree);
        tree = popMinimum(tree);
        
        output << minimum->seq->value << "\n";
        
        /* Since the minimum element is a sequence, if it has a next value,
         we can re-insert into the tree for the next iteration */
        if(next(minimum->seq)) {
            tree = insert(minimum, tree);
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
