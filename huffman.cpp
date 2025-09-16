#include<iostream>
#include<queue>
#include<map>
#include<bitset>
#include<fstream>
#include<string>
#include<bits/stdc++.h>
using namespace std;
class node{
    public:
    char ch;
    int freq;
    node* left;
    node* right;
    node(char ch,int freq){
        this->ch=ch;
        this->freq=freq;
    }
};
void pre(node* root){
    if(root==NULL) return;
    cout<<root->ch<<"->"<<root->freq<<endl;
    pre(root->left);
    pre(root->right);
}
bool tree_traversal(char& ch,node* root,string& str){
    if(root==NULL) return false;
    if(root->ch==ch) return true;
    str.push_back('0');
    if(tree_traversal(ch,root->left,str)){
        return true;
    }
    str.pop_back();
    str.push_back('1');
    if(tree_traversal(ch,root->right,str)){
        return true;
    }
    str.pop_back();
    return false;
}
string getpath(node*root,char ch){
    string path;
    tree_traversal(ch,root,path);
    return path;
}


string huffman_coder(string data){
    priority_queue<pair<int,char>,vector<pair<int,char>>,greater<pair<int,char>>>  counttable;
    map<char,int> t;
    for(auto c:data){
        t[c]++;
    }
    for(auto p:t){
        pair<int,char> temp_pair={p.second,p.first};
        counttable.push(temp_pair);
    }
    if(counttable.size()==0) return "";
    if(counttable.size()==1){
        
    }
    node* t1=new node(counttable.top().second,counttable.top().first);
    counttable.pop();
    node* t2=new node(counttable.top().second,counttable.top().first);
    counttable.pop();
    node* curr=new node('/0',t2->freq+t1->freq);
    curr->left=t1;
    curr->right=t2;
    while(counttable.size()>0){
        node* temp=new node(counttable.top().second,counttable.top().first);
        if(temp->freq>=curr->freq){
            node* temp1=new node('/0',curr->freq+temp->freq);
            temp1->left=curr;
            temp1->right=temp;
            curr=temp1;
        }
        else{
           node* temp1=new node('/0',curr->freq+temp->freq);
            temp1->left=temp;
            temp1->right=curr;
            curr=temp1;
        }
        counttable.pop();
    }
    //left-->0
    //right-->1
    //pre(curr);
    map<char,string> encoded_map;
    for(auto p:t){
        encoded_map[p.first]=getpath(curr,p.first);
    }
    //for(auto p:encoded_map){
    //    cout<<p.first<<"->"<<p.second<<endl;
    //}
    string ans;
    for(int i=0;i<data.size();i++){
        ans=ans+encoded_map[data[i]];
    }
    cout<<"Encoded data:"<<ans<<endl;


    return ans;
}
void saveToFile(const string& encoded, const string& filename) {
    ofstream out(filename, ios::binary);
    int bitLength = encoded.size();
    out.write((char*)&bitLength, sizeof(bitLength)); // store length

    unsigned char buffer = 0;
    int count = 0;

    for (char bit : encoded) {
        buffer = buffer << 1 | (bit - '0');
        count++;
        if (count == 8) {
            out.write((char*)&buffer, 1);
            buffer = 0;
            count = 0;
        }
    }

    if (count > 0) { // write remaining bits
        buffer <<= (8 - count);
        out.write((char*)&buffer, 1);
    }
    out.close();
}
int main(){
    int option;
    cout<<"Select an option:"<<endl<<"1.Do you want to give data file."<<endl<<"2.Do you want to give the data."<<endl;
    cout<<"Enter the option number:";
    cin>>option;
    string data="";
    string filename;
    if(option==1){
        string file_name;
        cout<<"Enter the file path:";
        cin>>file_name;
        ifstream my_file("file_name");
        string line;
        while(getline(my_file,line)){
            data.append(line);
        }
        my_file.close();
    }
    if(option==2){
        cout<<"Enter the data:";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        getline (cin, data);
    }
    else{
        cout<<"Invalid option"<<endl;
    }
    string encoded=huffman_coder(data);
    cout<<"Enter the binary file path:";
    cin>>filename;
    savetofile(encoded,filename);
    cout<<"Data encoded successfully."<<endl;
    return 0;
}