//
//  main.cpp
//  Builder
//
//  Created by Marius Ilau on 07/06/16.
//  Copyright © 2016 Marius Ilau. All rights reserved.
//

#include <iostream>
using namespace std;

enum PersistenceType {File,Queue,Pathway};

struct PersistenceAttribute
{
    PersistenceType type;
    char value[30];
};

class DistrWorkPackage
{
public:
    DistrWorkPackage(char * type){ sprintf(_desc, "Distributed Work Package for: %s", type);}
    void setFile(char *f, char *v)
    {
        sprintf(_temp, "\n  File(%s): %s", f, v);
        strcat(_desc, _temp);
    }
    void setQueue(char *q,char *v)
    {
        sprintf(_temp, "\n  Queue(%s): %s", q, v);
        strcat(_desc, _temp);
    }
    void setPathway(char *p,char *v)
    {
        sprintf(_temp, "\n  Pathway(%s): %s", p, v);
        strcat(_desc, _temp);
    }
    const char* getState() { return _desc;}
private:
    char _desc[200],_temp[80];
};

class Builder   // interfata pentru builderi
{
public:
    virtual void configureFile(char *) = 0;
    virtual void configureQueue(char *) = 0;
    virtual void configurePathway(char *) = 0;
    DistrWorkPackage * getResult() {return _result;}
protected:
    DistrWorkPackage * _result;
};

class UnixBuilder : public Builder // builder 1 - Unix
{
public:
    UnixBuilder() { _result = new DistrWorkPackage("Unix");}
    void configureFile(char * name) {_result->setFile("flat file", name);}
    void configureQueue(char *name) {_result->setQueue("FIFO", name);}
    void configurePathway(char *name) {_result->setPathway("thread", name);}
};

class VmsBuilder : public Builder // builder 2 - VMS
{
public:
    VmsBuilder() {_result = new DistrWorkPackage("VMS");}
    void configureFile(char * name) {_result->setFile("ISAM", name);}
    void configureQueue(char * name) {_result->setFile("Priority Queue", name);}
    void configurePathway(char * name) {_result->setPathway("LWP", name);}
};

class Reader // Director Class
{
public:
    void setBuilder(Builder * b) {_builder=b;}
    void construct(PersistenceAttribute[],int);
private:
    Builder * _builder;
};

void Reader::construct(PersistenceAttribute list[], int nr)  // functia de constructie
{
    for(int i = 0; i < nr; i++)
        if(list[i].type == File)
            _builder->configureFile(list[i].value);
        else if (list[i].type == Queue)
            _builder->configureQueue(list[i].value);
        else if (list[i].type == Pathway)
            _builder->configurePathway(list[i].value);
}


int main(int argc, const char * argv[])
{
    // insert code here...
    
    const int NUM_ENTRIES = 6;   // exemplu
    PersistenceAttribute input[NUM_ENTRIES] =
    {
        {
            File, "state.dat"
        }
        ,
        {
            File, "config.sys"
        }
        ,
        {
            Queue, "compute"
        }
        ,
        {
            Queue, "log"
        }
        ,
        {
            Pathway, "authentication"
        }
        , 
        {
            Pathway, "error processing"
        }
    };

    UnixBuilder b1;
    VmsBuilder v1;
    Reader r;
    
    // setare + constructie pt UNIX
    r.setBuilder(&b1);
    r.construct(input, NUM_ENTRIES);
    cout<<b1.getResult()->getState()<<endl;
    
    //setare + constructie pt VMS
    r.setBuilder(&v1);
    r.construct(input, NUM_ENTRIES);
    cout<<v1.getResult()->getState()<<endl;
    
    return 0;
}

