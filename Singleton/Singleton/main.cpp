//
//  main.cpp
//  Singleton
//
//  Created by Marius Ilau on 07/06/16.
//  Copyright © 2016 Marius Ilau. All rights reserved.
//

#include <iostream>
using namespace std;

class Singleton
{
public:
    static Singleton* instance()
    {
        if(uniqueInstance == NULL)
        {
            uniqueInstance = new Singleton;
        }
        return uniqueInstance;
    }
    int getValue() {return val;}
    void setValue(int x) {this->val = x;}
    
protected:
    int val;
    Singleton(int x = 0) : val(x) {}
    
private:
    static Singleton* uniqueInstance;
};
Singleton * Singleton::uniqueInstance = 0;

int main(int argc, const char * argv[]) {
    // insert code here...
    Singleton *a=Singleton::instance();
    a->setValue(20);
    Singleton *b=Singleton::instance();
    b->setValue(30);
    Singleton c=*b;
    return 0;
}
