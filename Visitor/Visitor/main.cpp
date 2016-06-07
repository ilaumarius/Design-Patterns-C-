//
//  main.cpp
//  Visitor
//
//  Created by Marius Ilau on 07/06/16.
//  Copyright © 2016 Marius Ilau. All rights reserved.
//


#include <iostream>
#include <string>
using namespace std;

// 1. Add an accept(Visitor) method to the "element" hierarchy
class Element
{
public:
    virtual void accept(class Visitor &v) = 0;
};

class This: public Element
{
public:
    /*virtual*/void accept(Visitor &v);
    string thiss()
    {
        return "This";
    }
};

class That: public Element
{
public:
    /*virtual*/void accept(Visitor &v);
    string that()
    {
        return "That";
    }
};

class TheOther: public Element
{
public:
    /*virtual*/void accept(Visitor &v);
    string theOther()
    {
        return "TheOther";
    }
};

// 2. Create a "visitor" base class w/ a visit() method for every "element" type
class Visitor
{
public:
    virtual void visit(This *e) = 0;
    virtual void visit(That *e) = 0;
    virtual void visit(TheOther *e) = 0;
};

/*virtual*/void This::accept(Visitor &v)
{
    v.visit(this);
}

/*virtual*/void That::accept(Visitor &v)
{
    v.visit(this);
}

/*virtual*/void TheOther::accept(Visitor &v)
{
    v.visit(this);
}

// 3. Create a "visitor" derived class for each "operation" to do on "elements"
class UpVisitor: public Visitor
{
    /*virtual*/void visit(This *e)
    {
        cout << "do Up on " + e->thiss() << '\n';
    }
    /*virtual*/void visit(That *e)
    {
        cout << "do Up on " + e->that() << '\n';
    }
    /*virtual*/void visit(TheOther *e)
    {
        cout << "do Up on " + e->theOther() << '\n';
    }
};

class DownVisitor: public Visitor
{
    /*virtual*/void visit(This *e)
    {
        cout << "do Down on " + e->thiss() << '\n';
    }
    /*virtual*/void visit(That *e)
    {
        cout << "do Down on " + e->that() << '\n';
    }
    /*virtual*/void visit(TheOther *e)
    {
        cout << "do Down on " + e->theOther() << '\n';
    }
};

int main()
{
    Element *list[] =
    {
        new This(), new That(), new TheOther()
    };
    UpVisitor up; // 4. Client creates
    DownVisitor down; //    "visitor" objects
    for (int i = 0; i < 3; i++)
        //    and passes each
        list[i]->accept(up);
    //    to accept() calls
    for (int i = 0; i < 3; i++)
        list[i]->accept(down);
    
    return 0;
}
/*
#include <iostream>
using namespace std;

class Visitor
{
public:
    virtual void VisitPortocala (class Portocala *) = 0;
    virtual void VisitLamaie (class Lamaie *) = 0;
    virtual void VisitGrapefruit (class Grapefruit *) = 0;
protected:
    Visitor();
};

class Fruct  // element interface
{
public:
    
//    virtual ~Fruct();
    virtual void Accept(Visitor &) = 0;
    
protected:
    Fruct();
    char * culoare;
    int masa;
    
};

class Mar : public Fruct
{
public:

    Mar();
    Mar(char * c, int m)
    {
        this->culoare = c;
        this->masa = m;
    }
    virtual void Accept(Visitor & v);
};

class Portocala : public Fruct
{
public:
    Portocala();
    Portocala(char *c, int m, int cv)
    {
        this->culoare = c;
        this->masa = m;
        this->Cvit = cv;
    }
    int getCvit() { return this->Cvit;}
    virtual void Accept(Visitor & v) { v.VisitPortocala(this);}
private:
    int Cvit;
};

class Lamaie : public Fruct
{
public:
    Lamaie();
    Lamaie(char *c, int m, int cv)
    {
        this->culoare = c;
        this->masa = m;
        this->Cvit = cv;
    }
    int getCvit() { return this->Cvit;}
    virtual void Accept(Visitor & v) { v.VisitLamaie(this);}
private:
    int Cvit;
};

class Grapefruit : public Fruct
{
public:
    Grapefruit();
    Grapefruit(char *c, int m, int cv)
    {
        this->culoare = c;
        this->masa = m;
        this->Cvit = cv;
    }
    int getCvit() { return this->Cvit;}
    virtual void Accept(Visitor & v) { v.VisitGrapefruit(this);}
private:
    int Cvit;
};

class CvitVisitor : public Visitor
{
    void VisitPortocala (Portocala * p)
    {
        cout<<"O portocala are: "<<p->getCvit()<<endl;
    }
    void VisitLamaie (Lamaie * l)
    {
        cout<<"O lamaie are: "<<l->getCvit()<<endl;
    }
    void VisitGrapefruit (Grapefruit * g)
    {
        cout<<"Un grapefruit are: "<<g->getCvit()<<endl;
    }
public:
    CvitVisitor();
};


int main(int argc, const char * argv[])
{
    // insert code here...
    Fruct * v[4];
    Portocala p("orange", 2, 10);
    Lamaie l("galbena", 3, 11);
    Grapefruit g("roz", 4,12);
    CvitVisitor x;
    
    v[1] = &p;
    v[2] = &l;
    v[3] = &g;
    
    for(int i = 1; i<4;i++)
        v[i]->Accept(x);
    
    return 0;
}
*/