//
//  main.cpp
//  Composite
//
//  Created by Marius Ilau on 07/06/16.
//  Copyright © 2016 Marius Ilau. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class Component // interfata pentru tipurile de componente
{
public:
    virtual void traverse() = 0;
};

class Leaf : public Component
{
private:
    int value;
public:
    Leaf(int val) : value(val) {};
    void traverse ()
    {
        cout << this->value << " ";
    }
};

class Composite : public Component
{
private:
    vector <Component *> children;
public:
    void add(Component *ele) { this->children.push_back(ele);}
    void traverse()
    {
        for (int i = 0; i < children.size(); i++)
            children[i]->traverse();
    }
};


int main(int argc, const char * argv[])
{
    // insert code here...
    int i;
    Composite containers[4];
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            containers[i].add(new Leaf(i *3+j));
    
    for (i = 1; i < 4; i++)
        containers[0].add(&(containers[i]));
    
    for (i = 0; i < 4; i++)
    {
        containers[i].traverse();
        cout << endl;
    }
    return 0;
}
