#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;

class node{
    public:
    char val;   //值
    int freq;   //次數
    node *l;
    node *r;
    
    node(char V, int F, node* L, node* R){
        val = V;
        freq = F;
        l = L;
        r = R;
    }
};
vector<node*> forest;
int *f = new int[256]();
string *C = new string[256];
bool cp(node *a, node *b){
    return a->freq > b->freq;
}

node* buildTree(){
    for(int i = 0; i < 256; i++){
        if(f[i] == 0) continue;
        forest.push_back(new node(char(i), f[i], nullptr, nullptr));
    }
    int s = forest.size() - 1;
    node *parent;
    for(int i = 0; i < s; i++){
        sort(forest.begin(), forest.end(), cp);
        node *ls = forest.back(); 
        forest.pop_back();
        node *rs = forest.back(); 
        forest.pop_back();
        if(ls->freq > rs->freq) parent = new node(-1, ls->freq + rs->freq, rs, ls);
        else parent = new node(-1, ls->freq + rs->freq, ls, rs);
        forest.push_back(parent);
    }
    return parent;
}

void Code(node *p, string s, ofstream &O){
    if(p->l == nullptr || p->r == nullptr){
        O << "'" << setw(2);
        if(int(p->val) != 10)
            O << p->val << "' (f = ";
        else O << "\\n' (f = ";
        O << setw(3) <<  f[p->val] << ") --> " << s << endl;
        C[p->val] = s;
        return;
    }
    if(p->l) Code(p->l, string(s + "0"), O);
    if(p->r) Code(p->r, string(s + "1"), O);
}

void decode(node *p, ifstream &I, ofstream &O){
    node *T = p;
    char ch;
    while((ch = I.get()) != EOF){
        if(T->l == nullptr || T->r == nullptr){
            O << T->val;
            T = p;
        }
        if(ch == '0') T = T->l;
        else T = T->r;
    }
    O << T->val;
    return;
}

int main(){
    char c;
    ifstream in;
    ofstream out;
    in.open("input.txt");
    if(!in.is_open()){
        cerr << "Failed to open file.\n";
        return 1;
    }
    while((c = in.get()) != EOF) f[c]++;
    in.close();
    
    out.open("code.txt");
    if(!out.is_open()){
        cerr << "Failed to open file.\n";
        return 1;
    }
    node *R = buildTree();
    Code(R, string(""), out);
    out.close();
    
    /*****Encode*****/
    in.open("input.txt");
    out.open("encoded.txt");
    if(!in.is_open() || !out.is_open()){
        cerr << "Failed to open file.\n";
        return 1;
    }
    while((c = in.get()) != EOF) out << C[c];
    in.close();
    out.close();

    /*****Compress*****/
    in.open("encoded.txt");
    out.open("input.enc");
    if(!in.is_open() || !out.is_open()){
        cerr << "Failed to open file.\n";
        return 1;
    }
    in.seekg (0, in.end);
    int length = in.tellg();
    in.seekg (0, in.beg);
    char *buffer = new char[8];  
    for(int i = 0; i < length / 8; i++){
        in.read(buffer,sizeof(buffer));
        string bf = buffer;
        bitset<8> bs(bf);
        out << char(bs.to_ulong());
    }
    delete []buffer;
    while((c = in.get()) != EOF) out << c;
    in.close();
    out.close();

    /*****Decompress*****/
    in.open("input.enc");
    out.open("decoded.txt");
    if(!in.is_open() || !out.is_open()){
        cerr << "Failed to open file.\n";
        return 1;
    }
    for(int i = 0; i < length / 8; i++){
        //c = ;
        int j = int(in.get());
        bitset<8> bs2(j); 
        out << bs2;
    }
    while((c = in.get()) != EOF) out << c;
    in.close();
    out.close();

    /*****Decode*****/
    in.open("decoded.txt");
    out.open("output.txt");
    if(!in.is_open() || !out.is_open()){
        cerr << "Failed to open file.\n";
        return 1;
    }
    decode(R, in, out);
    in.close();
    out.close();

    return 0;
}

