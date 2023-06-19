#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <assert.h>
#include <string>
using namespace std;
bool compareString (string s1 ,string  s2){
    int x = s1.compare(s2);
    if (x==0){
        return true;
    }
    else {
        return false;
    }
}


int search (vector <string> data ,int index , string cache[] , int size){
    int audit[size];
    for (int i =0 ; i<size ; i++ ){
for (int j = index ; j<data.size() ; j++){
if(compareString(data[j], cache[i])){
    audit[i] = j;
}
}
    }
 int   maxindex =0;
 int max = 0;
 for (int i =0 ; i<size; i++){
    if(audit[i]==0){
        maxindex = i;
        break;
    }
    if (audit[i]>max){
        max = audit[i];
        maxindex = i;
    }
 }

return maxindex;

}
void createfile(int size , int miss , int compmiss,int capacitymiss , vector<string> hitmissdata, string filename, string policy ,string cachesize){
   
    string name = "21116007_"+policy+"_"+filename+"_"+cachesize+".out";
   ofstream MyFile(name);
   MyFile << "TOTAL_ACCESSES = ";
   MyFile << size;
   MyFile << ".\n";
   MyFile << "TOTAL_MISSES = "  ;
   MyFile << miss;
   MyFile << ".\n";
   MyFile << "COMPULSORY_MISSES = " ;
   MyFile << compmiss;
   MyFile << ".\n";
   MyFile <<"CAPACITY_MISSES = " ;
   MyFile << capacitymiss;
   MyFile << ".\n";
   for (int i ; i<hitmissdata.size() ; i++){
    MyFile <<hitmissdata[i];
     MyFile << ".\n";
   }

  MyFile.close();
}

bool ispresent(string cache[], int size , string entry){
    int index;
    bool present = false;
for (int i =0 ; i<size ; i++){
    if (compareString(entry,cache[i])){
index =i;
present = true;
    }
}
return present;

}
int presentindex(string cache[], int size , string entry){
    int index;
    bool present = false;
for (int i =0 ; i<size ; i++){
    if (compareString(entry,cache[i])){
index =i;
present = true;

    }
}
return index;

}
int compulsory(vector <string> data  ){
    vector <string> dt ;
    int count;
    dt.push_back(data[0]);
    for ( int i =0 ; i<data.size(); i++){
        for ( int j =0 ; j< dt.size() ; j++){
            if(compareString(dt[j] ,data[i])){

            }
            else{
count++;
            }
        }
if(count == dt.size()){
    dt.push_back(data[i]);
}

    }
    int miss = dt.size();
    return miss;

}

string* arrayswap(string cache[] , int size, int current , string entry ){

string* newcache = new string[size]; 
for (int i = current ; i<size-1  ; i++){
newcache[i] = cache[i+1];

}
newcache[size-1] = entry;
for (int i = 0 ; i <current ; i++){
    newcache [i] = cache[i];
}
return newcache;
}


int main(int argc, char *argv[]) 
{
std::string current_exec_name = argv[0];
  std::vector<std::string> all_args;
  assert(argc==4);   
  all_args.assign(argv + 1, argv + argc);
string replPolicy = all_args[0];
  
   
    ifstream inFile(all_args[1].c_str());
     int numberOfCacheBlocks = stoi(all_args[2]);
     string cachesize = all_args[2];
     std::vector<std::string> data;
     
     if (inFile.is_open())
    {
        
        
         while (!inFile.eof())
        {
        string  x;
        inFile >> x;
        data.push_back(x);
        
        
        }
        data.pop_back();
 
    }

    else {
        cerr << "Can't find input file " <<  endl;
        assert(0);
    }
cout<<data.size()<<endl;
if (compareString(all_args[0],"LRU")){
    vector <string> hitmiss;
    int hits = 0;
    int misses = 0;
    int blocks = numberOfCacheBlocks;
    string cacheblock[blocks];
    
    for (int i = 0 ; i<data.size(); i++){
         if (ispresent(cacheblock , blocks, data[i])){
int index = presentindex(cacheblock , blocks, data[i]);

string* cacheblock1 = arrayswap(cacheblock , blocks , index , data[i]);
for (int j =0 ; j<blocks; j++){
    cacheblock[j] = cacheblock1[j];
}
hits++;
hitmiss.push_back("HIT");

         }

         else{
            if (i<blocks){
                cacheblock[i] =data[i];
                misses++;
                hitmiss.push_back("MISS");
            }
            else{
string* cacheblock2 = arrayswap(cacheblock ,blocks ,0 ,data[i]);
for (int j =0 ; j<blocks ; j++){
    cacheblock[j] = cacheblock2[j];
  
}
        misses++;
        hitmiss.push_back("MISS");
            }
           }

    }
int comp  = compulsory(data);
int capacity = misses-comp;
createfile (data.size(), misses, comp,capacity,hitmiss ,all_args[1] , all_args[0] , all_args[2] );


}
if (compareString(all_args[0],"OPTIMAL")){
vector <string> hitmiss;
    int hits = 0;
    int misses = 0;
    int blocks = numberOfCacheBlocks;
    string cacheblock[blocks];

for (int i =0 ;i <data.size() ; i++){
if (ispresent(cacheblock ,blocks , data[i])){
   hits++;
hitmiss.push_back("HIT");
}
else {
    if(i<blocks){
        cacheblock[i] = data[i];
              misses++;
              hitmiss.push_back("MISS");
    }
    else {
 int index = search(data, i , cacheblock , blocks);
 cacheblock[index] = data[i];
 misses++;
   hitmiss.push_back("MISS");
    }
}
}
int comp  = compulsory(data);
int capacity = misses-comp;
createfile (data.size(), misses, comp,capacity,hitmiss ,all_args[1] , all_args[0] , all_args[2] );



}


}