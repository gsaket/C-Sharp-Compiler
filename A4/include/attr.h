#include<bits/stdc++.h>
using namespace std;


struct Attr{
    string name;
    int width;//memory for this particular entry
    bool isarray;
    string type;
    Attr* elem; // array element
    vector<Attr*> var_dec;
    vector<Attr*> init_list;
    Attr* init;
    int line;
    vector<string> code;
    string place;
    //TODO need to handle array type
    /*
     *Attr(string name, bool basic, bool array, bool pointer, int width, int length):name(name), basic(basic), array(array),\
     *    array(array), pointer(pointer), width(width), length(length){}
     */
    Attr(){
        isarray=false;
        init=NULL;
        elem=NULL;
    }
};


class SymTable{
public :
    SymTable* parent;
    vector<SymTable*> children;
    set<string> Entries;
    int width;
    int temp_count;

    SymTable(SymTable* prev=NULL){
        parent=prev;
        temp_count=0;
    }
    string getTemp(){
        temp_count++;
        string temp="TP";
        while(1){
            if(Entries.find(temp+to_string(temp_count)) == Entries.end()){
                break;
            }
            temp_count++;
        }
        temp=temp+to_string(temp_count);
        Entries.insert(temp);
        return temp;
    }
    bool lookup(string s){
        if(Entries.find(s) != Entries.end()){
            return true;
        }
        if(parent == NULL){
            return false;
        }
        return parent->lookup(s);
    }
};
