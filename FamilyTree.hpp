#pragma once
#include <iostream>
#include <string>
namespace family{
    class Tree{
        
        
        struct Node* root;
        public:
        Tree();
        ~Tree();
        Tree(std::string root);
        Tree& T(std::string person);
        Tree& addFather(std::string son ,std::string dad);
        Tree& addMother(std::string son, std::string mom);
        std::string relation(std::string name);
        std::string find(std::string relation);
        void display();
        void remove(std::string name);
        private:
        void addF(Node* temp,std::string son,std::string dad);
        void addM(Node* t,std::string son,std::string mom);
        void disp(Node* t,int n);
        std::string relation_locate(Node* t,std::string name);

};
    struct Node{
            public:
            std::string name;
            struct Node* mother;
            struct Node* father;
            struct Node* son;
            public:
            Node(std::string name);
    
        };

}