
#ifndef WATERSUPPLYMANAGER_NODE_H
#define WATERSUPPLYMANAGER_NODE_H

#include <string>

class Node {
private:
    int id;
    std::string code;
public:
    Node(int id, std::string code): id(id), code(code) {};
    int getId() const;
    std::string getCode() const;
};


#endif //WATERSUPPLYMANAGER_NODE_H
