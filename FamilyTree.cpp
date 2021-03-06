#include "FamilyTree.hpp"
#include <iostream>
#include <string>
#define COUNT 10

struct Mexception : std::exception {
        const char* what() const throw() {
            const char* ex = "Error,illegal operation";
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
        if(t->father) throw Mexception();
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
        if(t->mother) throw Mexception();
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
    if(relation(son)=="unrelated") throw Mexception();       
    Node*temp = root;
    addF(temp,son,dad,1);
    Tree& tr = *this;
    return tr;
}
Tree& Tree::addMother(std::string son, std::string mom){
    if(relation(son)=="unrelated") throw Mexception();
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

    if(t->father==NULL && t->mother!=NULL) return name_locate(t->mother,relation);
    else if(t->father!=NULL && t->mother==NULL) return name_locate(t->father,relation);
    else if(t->father!=NULL && t->mother!=NULL){
        if(name_locate(t->father,relation)!="") return name_locate(t->father,relation);
        if(name_locate(t->mother,relation)!="") return name_locate(t->mother,relation);
    }
    return "";


}

std::string Tree::find(std::string relation){
    std::string ans = "";
    if(root->relation==relation) return root->name;
    else {
        if(root->father!=NULL) ans= name_locate(root->father,relation);
        if(root->mother!=NULL && ans=="") ans= name_locate(root->mother,relation);
        //else if(root->mother!=NULL && root->father!=NULL) ans= name_locate(root->mother,relation)+name_locate(root->father,relation);
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
void Tree::freeALL(Node* t){
    if(t->father){
        freeALL(t->father);
    }
    if(t->mother){
        freeALL(t->mother);
    }
    if(!t->father && !t->mother) delete(t);
}


void Tree::remove_sub(Node* t,std::string name){
    if(t->father){
        if(t->father->name==name){
            freeALL(t->father);
            t->father=NULL;
        }
        else remove_sub(t->father,name);
    }
    if(t->mother){
        if(t->mother->name==name){
            freeALL(t->mother);
            t->mother=NULL;

        }
        else remove_sub(t->mother,name);
    }

  

}

void Tree::remove(std::string name){
    if(relation(name)=="unrelated") throw Mexception();
    if(root->name==name) throw Mexception();
    if(root->father){
        if(root->father->name==name){
            freeALL(root->father);
            root->father=NULL;
        }
        else remove_sub(root->father,name);
    }
    if(root->mother){
        if(root->mother->name==name){
            freeALL(root->mother);
            root->mother=NULL;

        }
        else remove_sub(root->mother,name);
    }
    
    

}
