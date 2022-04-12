#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main ()
{
	ifstream file("sample_input2.v");
	string str;
	int cnt=1;
    vector<string> keywords={"always","and","assign","begin","case","default","edge","else","end","endcase","endmodule","endfunction",
                            "endtable","else if","endtask","event","for","forever","function","if","ifnone","initial","inout","input","integer",
                            "join","large","module","nand","not","or","output","parameter","posedge","primitive","pullup",
                            "pulldown","real","realtime","reg","release","repeat","small","specify","table","taSK","time","wait","while","wire"};
	while (getline(file, str)) {
		string word="";
		for(int i=0;i<str.length();i++){
			if(str[i]=='/'){
				break;
			}
			else if(word=="else"){
				if((i+2)<str.length() && str[i+1]=='i' && str[i+2]=='f'){
					word="else if";
                    cout<<"Line no "<<cnt<<" "<<word<<endl;
					i+=3;
                }
				else{
					cout<<"Line no "<<cnt<<" "<<word<<endl;
				}
				word="";
			}
			else if(str[i]==','){
				if(word!=""){
                    if(find(keywords.begin(),keywords.end(),word)!=keywords.end()){
                        cout<<"Line no "<<cnt<<" "<<word<<endl;
                    }
					word="";	
				}
				
			}
			else if(str[i]==';'){
				if(word!=""){
					if(find(keywords.begin(),keywords.end(),word)!=keywords.end()){
                        cout<<"Line no "<<cnt<<" "<<word<<endl;
                    }
					word="";	
				}
			}
			else if(str[i]==':'){
				if(word!=""){
					if(find(keywords.begin(),keywords.end(),word)!=keywords.end()){
                        cout<<"Line no "<<cnt<<" "<<word<<endl;
                    }
					word="";	
				}
			}
			else if(str[i]==' ' || str[i]=='	'){
				if(word!=""){
					if(find(keywords.begin(),keywords.end(),word)!=keywords.end()){
                        cout<<"Line no "<<cnt<<" "<<word<<endl;
                    }
					word="";	
				}
			}
			else if((str[i]>='a' && str[i]<='z') || (str[i]>='0' && str[i]<='9') || str[i]=='-' || str[i]=='.' || str[i]=='_' || str[i]=='\'' || (str[i]>='A' && str[i]<='Z')){
				word=word+str[i];
			}
			else if(str[i]=='('){
				if(word!=""){
					if(find(keywords.begin(),keywords.end(),word)!=keywords.end()){
                        cout<<"Line no "<<cnt<<" "<<word<<endl;
                    }
					word="";	
				}
			}
		}
		if(word!=""){
			if(find(keywords.begin(),keywords.end(),word)!=keywords.end()){
				cout<<"Line no "<<cnt<<" "<<word<<endl;
			}
			word="";	
		}
		cnt++;
	}
}