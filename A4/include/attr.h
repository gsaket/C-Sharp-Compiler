#include<bits/stdc++.h>
using namespace std;

#define X first
#define Y second
#define pb push_back

struct Attr{
    string name;
    int width;//memory for this particular entry
    bool isarray;
    string type;
    Attr* elem; // array element

    // Initialization
    vector<Attr*> var_dec;
    vector<Attr*> init_list;
    Attr* init;

    int line;
    vector<string> code;
    string place;

    // switch case
    bool sw_default;
    Attr* sw_lbl;
    vector<Attr*> sw_sec;

    // method
    string ret_typ;
    vector<Attr*> par_lst;

    // invocation
    vector<Attr*> arg_lst;

    //TODO need to handle array type
    /*
     *Attr(string name, bool basic, bool array, bool pointer, int width, int length):name(name), basic(basic), array(array),\
     *    array(array), pointer(pointer), width(width), length(length){}
     */
    Attr(){
        isarray=false;
        init=NULL;
        elem=NULL;
        sw_default=false;
        sw_lbl=NULL;
        ret_typ="void";
    }
};


class SymTable{
public :
    SymTable* parent;
    vector<SymTable*> children;
    //set<string> Entries;
    // Identifier -> {type, category}
    map<string, pair<string,string> > Node;
    // For function, we store {arg_num, arg_types}
    map<string, pair<int ,vector<string> > > Args;
    int width;
    int temp_count;

    SymTable(SymTable* prev=NULL){
        parent=prev;
        temp_count=0;
    }


    void insertVariable(string typ, string id){
        pair<string,string> Temp;
        Temp.X = typ;
        Temp.Y = "variable";
        Node[id]=Temp;
    }

    void insertTemp(string typ, string id){
        pair<string,string> Temp;
        Temp.X = typ;
        Temp.Y = "temporary";
        Node[id]=Temp;
    }

    void insertArray(string typ, string id){
        pair<string,string> Temp;
        Temp.X = typ;
        Temp.Y = "array";
        Node[id]=Temp;
    }

    void insertFunc(string id, string ret_typ, vector<string> par_typs, int par_num){
        pair<string,string> Temp;
        Temp.X = ret_typ; // remember it is return type for function
        Temp.Y = "function";
        Node[id]=Temp;
        pair<int ,vector<string> > Temp_;
        Temp_.X=par_num;
        Temp_.Y=par_typs;
        Args[id]=Temp_;
    }

    string getTemp(string typ){
        temp_count++;
        string temp="TP";
        while(1){
            if(Node.find(temp+to_string(temp_count)) == Node.end()){
                break;
            }
            temp_count++;
        }
        temp=temp+to_string(temp_count);
        insertTemp(typ,temp);
        return temp;
    }

    bool lookup(string s){
        if(Node.find(s) != Node.end()){
            return true;
        }
        if(parent == NULL){
            return false;
        }
        return parent->lookup(s);
    }
};
