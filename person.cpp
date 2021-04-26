#include "person.h"
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

Person::Person(const char *name_, Person* father_, Person* mother_){
    name = new char[strlen(name_)+1];
    strcpy(name, name_);
    father = father_;
    mother = mother_;
    capacity = 1;
    numChildren = 0;
    children = new Person*[capacity];
}

/*Person::~Person(){
   for (int i=0; i<=capacity*2; i++){
	delete children[i];
	children[i] = NULL;
    }	
   delete[] children;
   delete[] name;
   delete mother;
   delete father;
   
}*/

void Person::addChild(Person *newChild){
    if(numChildren == capacity) expand(&children, &capacity);
    
    children[numChildren++] = newChild;
}

void Person::printAncestors(){
    cout << endl << "Ancestors of " << name << endl;
    printLineage('u', 0);
}

void Person::printDecendents(){
    cout << endl << "Decendents of " << name << endl;
    printLineage('d', 0);
}

void Person::printLineage(char dir, int level){
    char *temp = compute_relation(level);

    if(dir == 'd'){
        for(int i = 0; i < numChildren; i++){
            cout << temp << "child: " << children[i]->getName() << endl;
            children[i]->printLineage(dir, level + 1);
        }
    } else {
        if(mother){
            cout << temp << "mother: " << mother->getName() << endl;
            mother->printLineage(dir, level + 1);
        }
        if(father){
            cout << temp << "father: " << father->getName() << endl;
            father->printLineage(dir, level + 1);
        }
    }
   delete[] temp;
}

/* helper function to compute the lineage
* if level = 0 then returns the empty string
* if level >= 1 then returns ("great ")^(level - 1) + "grand "
*/
char* Person::compute_relation(int level){
    if(level == 0) return strcpy(new char[1], "");

    char *temp = strcpy(new char[(level*6) + 7], "");
    
    for(int i = 2; i <= level; i++){
        strcat(temp, "great ");
    }
	strcat(temp, "grand ");
    return temp;
}

/* non-member function which doubles the size of t
 * NOTE: t's type will be a pointer to an array of pointers
 */
void expand(Person* **t, int *MAX){
  Person **temp = 0;
  temp = new Person*[2 * *MAX];
  for (int i =0; i<= 2* *MAX-1;i++){
	temp[i] = NULL;
  }
  memcpy(temp, *t, *MAX * sizeof(**t));
  /*for (int i =0; i<= *MAX; i++){
        delete *t[i];
	*t[i] = NULL;
  }*/
  delete[] *t;
  *t = NULL;
  *MAX *= 2;
  *t = temp;
}
