#include "FamilyTree.hpp"
#include <iostream>
#include <string>
#define COUNT 10
using namespace family;
Node::Node(std::string n){
    name = n;
    mother = NULL;
    father = NULL;
    son = NULL;
}
Tree::Tree(){
    root=NULL;
}

Tree::~Tree(){

}
Tree::Tree(std::string n){
    Node* temp = new Node(n);
    root = temp;
    
}


Tree& Tree::T(std::string root){
    Tree t = Tree(root);
    Tree& tr = t;
    
    return tr; 
    
} 
void Tree::addF(Node* t,std::string son,std::string dad){
    if(t->name==son){
        Node* temp = new Node(dad);
        t->father=temp;
        return;
    }

    if(t->father!=NULL) return addF(t->father,son,dad);
    if(t->mother!=NULL) return addF(t->mother,son,dad);
}
void Tree::addM(Node* t,std::string son,std::string mom){
    if(t->name==son){
        Node* temp = new Node(mom);
        t->mother=temp;
        return;
    }

    if(t->father!=NULL) return addM(t->father,son,mom);
    if(t->mother!=NULL) return addM(t->mother,son,mom);
}
   
Tree& Tree::addFather(std::string son, std::string dad){
    Tree& tr = *this;
    addF(root,son,dad);
    return tr;
}
Tree& Tree::addMother(std::string son, std::string mom){
    Tree& tr = *this;
    addM(root,son,mom); 
    return tr;

}
std::string Tree::relation_locate(Node* t,std::string name){
    if(t==NULL) return "unrelated";
    if(t->name == name) return "me";
   
    if(t->father==NULL || t->mother==NULL) return"";
    if(t->father->name==name){
        return "father";
    }
    if(t->mother->name==name){
        return "mother";
    }
    std::cout << "OK";    
    if(t->mother->mother->name==name || t->father->mother->name==name){
   
        return "grandmother";
    }
    else if(t->father->father->name==name || t->mother->father->name==name){
        return "grandfather";
    }
    else return "great+"+relation_locate(t->father,name)+relation_locate(t->mother,name);

}

std::string Tree::relation(std::string name){
    return relation_locate(root,name);

}

std::string Tree::find(std::string relation){

}
void Tree::disp(Node* root, int n){
    if(root == NULL) return;
    n+=COUNT;
    disp(root->mother,n);
    std::cout << std::endl;
    for (int i = COUNT; i < n; i++)  {std::cout<<" ";}  
    std::cout<<root->name<<"\n";  

    disp(root->father, n);
}

void Tree::display(){
    disp(root,0);

}

void Tree::remove(std::string name){
    
}
