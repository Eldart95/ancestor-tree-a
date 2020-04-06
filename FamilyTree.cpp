#include "FamilyTree.hpp"
#include <iostream>
#include <string>
#define COUNT 10

struct Mexception : std::exception {
        const char* what() const throw() {
            const char* ex = "The three cant handle this relation";
            return ex;
            }
    };

using namespace family;
Node::Node(){

}
Node::Node(std::string n){
    name = n;
    mother = NULL;
    father = NULL;
    son = NULL;
}
Tree::Tree(){
    Node* temp = new Node();
    root=temp;
}

Tree::~Tree(){
    freeALL(root);
    delete(root);

}
Tree::Tree(std::string n){
    Node* temp = new Node(n);
    root = temp;
    root->relation="me";
}


Tree& Tree::T(std::string root){
    return *this;
} 
void Tree::addF(Node* t,std::string son,std::string dad,int count){
    if(t->name==son){
        Node* temp = new Node(dad);
        t->father=temp;
        if(count==1) t->father->relation="father";
        else if(count==2) t->father->relation="grandfather";
        else{
            for(int i=0;i<count-2;i++){
                t->father->relation+="great-";
            }
            t->father->relation+="grandfather";
        }
        
    }
    
    count++;
    if(t->father!=NULL) addF(t->father,son,dad,count);
    if(t->mother!=NULL) addF(t->mother,son,dad,count);
}
void Tree::addM(Node* t,std::string son,std::string mom,int count){
    if(t->name==son){
        Node* temp = new Node(mom);
        t->mother=temp;
        if(count==1) t->mother->relation="mother";
        else if(count==2) t->mother->relation="grandmother";
        else {
            for(int i=0;i<count-2;i++){
                t->mother->relation+="great-";
            }
            t->mother->relation+="grandmother";
        }
        
    }
    count++;
    if(t->father!=NULL) addM(t->father,son,mom,count);
    if(t->mother!=NULL) addM(t->mother,son,mom,count);
}
   
Tree& Tree::addFather(std::string son, std::string dad){
            
    Node*temp = root;
    addF(temp,son,dad,1);
    Tree& tr = *this;
    return tr;
}
Tree& Tree::addMother(std::string son, std::string mom){
    Node* temp = root;
    addM(temp,son,mom,1); 
    Tree& tr = *this;
    return tr;

}
// std::string Tree::relation_locate(Node* t,std::string name){
//     if(t->father==NULL && t->mother==NULL) {
//         return "";
//     }
    
//     if(t->father!=NULL && t->father->name==name) return "grandfather";
//     if(t->mother!=NULL && t->mother->name==name) return "grandmother";

//     if(t->father==NULL && t->mother!=NULL) return "great-"+relation_locate(t->mother,name);
//     else if(t->father!=NULL && t->mother==NULL) return "great-"+relation_locate(t->father,name);
//     else if(t->father!=NULL && t->mother!=NULL) return "great-"+relation_locate(t->father,name)+relation_locate(t->mother,name);
//     return "";
 

// }
std::string Tree::relation_locate(Node* t,std::string name){
    if(t->name==name) return t->relation;

    else if(t->father==NULL && t->mother!=NULL) return relation_locate(t->mother,name);
    else if(t->father!=NULL && t->mother==NULL) return relation_locate(t->father,name);
    else if(t->father!=NULL && t->mother!=NULL) return relation_locate(t->father,name)+relation_locate(t->mother,name);
    return "";
 

}
std::string Tree::relation(std::string name){
    std::string ans="";
    if(root->name==name) return root->relation;
    else {
        if(root->father!=NULL && root->mother==NULL) ans+= relation_locate(root->father,name);
        else if(root->mother!=NULL && root->father==NULL) ans+= relation_locate(root->mother,name);
        else if(root->mother!=NULL && root->father!=NULL) ans+= relation_locate(root->father,name)+relation_locate(root->mother,name);
    }
    if(ans=="") return "unrelated";
    return ans;
    

}

// std::string Tree::relation(std::string name){
//     Node* t = root;
//     std::string ans="";
//     if(root->name==name) return "me";
//     else if(root->father!=NULL && root->father->name==name) return "father";
//     else if(root->mother!=NULL && root->mother->name==name) return "mother";
//     if(t->father->father!=NULL && t->father->father->name==name) return "grandfather";
//     if(t->father->mother!=NULL && t->father->mother->name==name) return "grandmother";
//     if(t->mother->father!=NULL && t->mother->father->name==name) return "grandfather";
//     if(t->mother->mother!=NULL && t->mother->mother->name==name) return "grandmother";
   
//     ans = relation_locate(t,name);
//     ans = ans.substr(6);
//     if(ans[ans.length()-1]=='-') ans ="unrelated";
    
    
//     return ans;

// }


std::string Tree::name_locate(Node* t,std::string relation){
    if(t->relation==relation) return t->name;

    else if(t->father==NULL && t->mother!=NULL) return name_locate(t->mother,relation);
    else if(t->father!=NULL && t->mother==NULL) return name_locate(t->father,relation);
    else if(t->father!=NULL && t->mother!=NULL) return name_locate(t->father,relation)+name_locate(t->mother,relation);
    return "";


}

std::string Tree::find(std::string relation){
    std::string ans = "";
    if(root->relation==relation) return root->name;
    else {
        if(root->father!=NULL && root->mother==NULL) ans+= name_locate(root->father,relation);
        else if(root->mother!=NULL && root->father==NULL) ans+= name_locate(root->mother,relation);
        else if(root->mother!=NULL && root->father!=NULL) ans+= name_locate(root->mother,relation)+name_locate(root->father,relation);
    }
    if(ans=="") {
        throw Mexception();
    }
    return ans;

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
void Tree::freeALL(Node* temp){
    if(temp->father!=NULL) freeALL(temp->father);
    if(temp->mother!=NULL) freeALL(temp->mother);
    if(temp->father==NULL && temp->mother==NULL) delete(temp);
}

void Tree::remove_sub(Node* t,std::string name){
    if(t->father!=NULL && t->father->name==name){
        if(t->father->father!=NULL) freeALL(t->father);
        if(t->father->mother!=NULL) freeALL(t->mother);
        delete(t->father);
        t->father=NULL;
        return;
    }
    else if(t->mother!=NULL && t->mother->name==name){
        if(t->mother->father!=NULL) freeALL(t->father);
        if(t->mother->mother!=NULL) freeALL(t->mother);
        delete(t->mother);
        t->mother=NULL;
        return; 
    }
    else {
        if(t->father!=NULL ) remove_sub(t->father,name);
        if(t->mother!=NULL ) remove_sub(t->mother,name);
    }

}

void Tree::remove(std::string name){
    if(root->father!=NULL && root->father->name==name)  remove_sub(root,name);
    if(root->mother!=NULL && root->mother->name==name)  remove_sub(root,name);
    
    if(root->name==name){
        if(root->father!=NULL) freeALL(root->father);
        if(root->mother!=NULL) freeALL(root->mother);
        delete(root);
        return;
    }
    
    else {
        if(root->father!=NULL) remove_sub(root->father,name);
        if(root->mother!=NULL) remove_sub(root->mother,name);
    }
}
