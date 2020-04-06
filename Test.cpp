
#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>
using namespace family;

TEST_CASE("Init Tree") {

    family::Tree T ("John Snow"); // Yosef is the "root" of the tree (the youngest person).
	T.addFather("John Snow", "Rhaegar Targaryen")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("John Snow", "Lyanna Stark");  // Tells the tree that the mother of Yosef is Rachel.

    T.addFather("Lyanna Stark","Richard Stark");
    T.addMother("Lyanna Stark","Unknown");
    
    T.addFather("Rhaegar Targaryen","Aerys Targaryen");
	T.addMother("Rhaegar Targaryen","Rhaella Targaryen");
    
    //T.display();     

    CHECK(T.root);
    CHECK(T.root->father);
    CHECK(T.root->mother);
    CHECK(T.root->mother->mother);
    CHECK(T.root->father->father);  

    CHECK(T.root->name=="John Snow");
    CHECK(T.root->father->name=="Rhaegar Targaryen");
    CHECK(T.root->mother->name=="Lyanna Stark");
    CHECK(T.root->mother->mother->name=="Unknown");
    CHECK(T.root->mother->father->name=="Richard Stark");
    CHECK(T.root->father->father->name=="Aerys Targaryen");

    CHECK(T.relation("Rhaegar Targaryen")=="father");
    CHECK(T.relation("Richard Stark")=="grandfather");
    CHECK(T.relation("Rhaella Targaryen")=="grandmother");
    CHECK(T.relation("Aerys Targaryen")=="grandfather");
    CHECK(T.relation("John Snow")=="me");

    CHECK(T.relation("Halisi")=="unrelated");
    CHECK(T.relation("Jamey Lannister")=="unrelated");
    CHECK(T.relation("Katelyn Stark")=="unrelated");
    CHECK(T.relation("ariya")=="unrelated");

    CHECK(T.find("father")=="Rhaegar Targaryen");
    CHECK(T.find("mother")=="Lyanna Stark");
    CHECK(T.find("me")=="John Snow");
    

    CHECK_THROWS(T.find("uncle")); 
    CHECK_THROWS(T.find("bro")); 
    CHECK_THROWS(T.find("sis")); 
    CHECK_THROWS(T.find("wife")); 

    T.remove("Richard Stark");
    T.remove("Rhaella Targaryen");
    T.remove("Aerys Targaryen");
    T.remove("Katelyn Stark");
    T.remove("Rhaegar Targaryen");

    T.addFather("John Snow","Nedd");
    T.addMother("John Snow","KateLyn");
    CHECK(T.root);
    CHECK(T.root->father);
    CHECK(T.root->mother);
    CHECK(!T.root->mother->father);
    CHECK(!T.root->mother->mother);
    CHECK(!T.root->father->father);
    CHECK(!T.root->father->mother);

    CHECK(T.relation("Nedd")=="father");
    CHECK(T.relation("KateLyn")=="mother");
    CHECK(T.relation("Bran")=="unrelated");
    CHECK(T.relation("Ayman")=="unrelated");
    CHECK(T.relation("Daddy")=="unrelated");



    CHECK(T.relation("Richard Stark")=="unrelated");
    CHECK(T.relation("Rhaella Targaryen")=="unrelated");
    CHECK(T.relation("Aerys Targaryen")=="unrelated");
    CHECK(T.relation("Katelyn Stark")=="unrelated");
    CHECK(T.relation("Rhaegar Targaryen")=="unrelated");

    

    family::Tree K("Cersei Lannister");
    K.addMother("Cersei Lannister","Joanna Lannister");
    K.addFather("Cersei Lannister","Tywin Lannister");
    K.addMother("Tywin Lannister","Lady of Florent House");
    K.addFather("Tywin Lannister","Tytos Lannister");
    K.addFather("Tytos Lannister","Tybolt");
    K.addMother("Tytos Lannister","Mother of Tytos");
    K.addFather("Tybolt","Damon the Gray Lion");

    CHECK(K.root);
    CHECK(K.root->father);
    CHECK(K.root->mother);
    CHECK(K.root->father->father);
    CHECK(!K.root->mother->father);
    CHECK(!K.root->mother->father);
    CHECK(K.root->father->father->father);

    CHECK(K.root->name=="Cersei Lannister");
    CHECK(K.root->mother->name=="Joanna Lannister");
    CHECK(K.root->father->name=="Tywin Lannister");
    CHECK(K.root->father->father->name == "Tytos Lannister");
    CHECK(K.root->father->father->father->name == "Tybolt");
    CHECK(K.root->father->father->mother->name == "Mother of Tytos");

    CHECK(K.relation("Tybolt")=="great-grandfather");
    CHECK(K.relation("Joanna Lannister")=="mother");
    CHECK(K.relation("Tywin Lannister")=="father");
    CHECK(K.relation("Tytos Lannister")=="grandfather");
    CHECK(K.relation("Mother of Tytos")=="great-grandmother");
    CHECK(K.relation("Cersei Lannister")=="me");
    CHECK(K.relation("Lady of Florent House")=="grandmother");

    CHECK(K.relation("Halisi")=="unrelated");
    CHECK(K.relation("Jamey Lannister")=="unrelated");
    CHECK(K.relation("Katelyn Stark")=="unrelated");
    CHECK(K.relation("Brandon")=="unrelated");
    CHECK(K.relation("White Walker")=="unrelated");

    CHECK(K.find("father")=="Tywin Lannister");
    CHECK(K.find("mother")=="Joanna Lannister");
    CHECK(K.find("me")=="Cersei Lannister");

    CHECK_THROWS(K.find("uncle")); 
    CHECK_THROWS(K.find("bro")); 
    CHECK_THROWS(K.find("sis")); 
    CHECK_THROWS(K.find("wife")); 
    CHECK_THROWS(K.find("love")); 
    CHECK_THROWS(K.find("hate")); 


    K.remove("Tywin Lannister");
    CHECK(T.root);
    CHECK(T.root->mother);
    CHECK(K.relation("Tyboly")=="unrelated");
    CHECK(K.relation("Tywin Lannister")=="unrelated");
    CHECK(K.relation("Mother of Tytos")=="unrelated");
    CHECK(K.relation("Damon the Gray Lion")=="unrelated");
    CHECK(K.relation("Cersei")=="unrelated");
    CHECK(K.relation("Cersei Lannister")=="me");

}
TEST_CASE("Init Tree2"){
    family::Tree T ("");
    CHECK(T.root->name=="");
    CHECK(!T.root->father);
    CHECK(!T.root->mother);

    CHECK_THROWS(T.find("uncle")); 
    CHECK_THROWS(T.find("bro")); 
    CHECK_THROWS(T.find("sis")); 
    CHECK_THROWS(T.find("wife")); 

    CHECK(T.find("me")=="");
    CHECK(T.relation("Tyboly")=="unrelated");
    CHECK(T.relation("Toy")=="unrelated");
    CHECK(T.relation("Seasame")=="unrelated");



}
TEST_CASE("empty tree"){
    family::Tree* K = new Tree();
    CHECK(K->root);
    CHECK(!K->root->father);
    CHECK(!K->root->mother);
   

}

