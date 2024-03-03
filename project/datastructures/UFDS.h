/*
 * UFDS.h
 * A simple implementation of Union-Find Disjoint Set (UFDS), required by Kruskal's algorithm.
 *
 * Created on: 25/01/2022
 *      Author: Gonçalo Leão
 */

#ifndef WATER_SUPPLY_UFDS
#define WATER_SUPPLY_UFDS

#include <vector>

class UFDS {
public:
    UFDS(unsigned int N);
    unsigned long findSet(unsigned int i);
    bool isSameSet(unsigned int i, unsigned int j);
    void linkSets(unsigned int i, unsigned int j);
private:
    std::vector<unsigned int> path; // Ancestor of node i (which can be itself). It is used to determine if two nodes are part of the same set.
    std::vector<unsigned int> rank; // Upper bound for the height of a tree whose root is node i.
};


#endif //WATER_SUPPLY_UFDS