//这个文件没啥意义，只是用来试函数的
#include<iostream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

int main(void){
    string line;
    getline(cin,line);
    for (auto it1 = line.begin(); it1 != line.end(); it1++)
	{
		*it1 = tolower(*it1);
	}
    
    istringstream is(line);
    string str;
    vector<string> res;
    while(getline(is,str,' '))
    res.push_back(str);
    
    cout<<res[3]<<endl;
    for(auto i=0;i<res.size();i++){
        cout<<res[i]<<endl;
    }
    return 1 ;
}