#pragma once
#include <iostream>
#include <string>
namespace family{
class Tree{
    private:
    Node root;
    Node father;
    Node mother;
    public:
    Tree(std::string root);
    Tree& T(std::string person);
    Tree& addFather(std::string son ,std::string dad);
    Tree& addMother(std::string son, std::string mom);
    std::string relation(std::string name);
    std::string find(std::string relation);
    void display();
    void remove(std::string name);

};
class Node{
    private:
    std::string name;
    public:
    Node(std::string person);
    
};
}