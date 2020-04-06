#pragma once
#include <iostream>
#include <string>
namespace family{
    class Tree{
        
        public:
        struct Node* root;
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
        void addF(Node* temp,std::string son,std::string dad,int count);
        void addM(Node* t,std::string son,std::string mom,int count);
        void disp(Node* t,int n);
        std::string name_locate(Node* t,std::string relation);
        std::string relation_locate(Node* t,std::string name);
        void remove_sub(Node* t,std::string name);
        void freeALL(Node* temp);

};
    struct Node{
            public:
            std::string name;
            struct Node* mother;
            struct Node* father;
            struct Node* son;
            std::string relation;
            public:
            Node(std::string name);
            Node();
    
        };

}