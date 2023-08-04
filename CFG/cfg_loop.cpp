#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

string input_file;
string output_file = "cfg.txt";
ofstream outfile;

map<string,vector<string>> graph;
int intermediate_count = 1;

bool find_string(string str,string str1){
    size_t found = str.find(str1);
    if (found != string::npos)
        return true;
    else
        return false;
}

bool find_char(string str,char ch){
    size_t found = str.find(ch);
    if (found != string::npos)
        return true;
    else
        return false;
}

string if_block(vector<string> v,string curr);
string else_block(vector<string> v,string curr);
string else_if_block(vector<string> v,string curr);
void for_block(vector<string> v,string curr);
void while_block(vector<string> v,string curr);
string case_block(vector<string> v,string curr);
string always_block(vector<string> v,string curr);

vector<string> parse_for(string str){
    vector<string> v;
    v.push_back("for");
    string cond = "";
    int cnt = 0;
    for(auto i:str){
        if(i == '('){
            cnt++;
            continue;
        }
        else if(i == ')'){
            cnt--;
            continue;
        }
        if(cnt > 0){
            if(i == ';'){
                v.push_back(cond);
                cond = "";
            }
            else
                cond += i;
        }
    }
    v.push_back(cond);
    return v;
}

vector<string> parse_while(string str){
    vector<string> v;
    v.push_back("while");
    string cond = "";
    int cnt = 0;
    for(auto i:str){
        if(i == '('){
            cnt++;
            continue;
        }
        else if(i == ')'){
            cnt--;
            if(cnt == 0)
                break;
            continue;
        }
        if(cnt > 0){
            cond += i;
        }
    }
    v.push_back(cond);
    return v;
}

string if_block(vector<string> v,string curr){
    int i = 0;
    string start = "";
    string end = "";
    while(i < v.size()){
        string str = v[i];
        if(find_string(str,"else if")){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"else") && !(find_string(str,"end")) ){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"if") && !find_string(str,"fifo")){
            if(end != ""){
                start = end;
            }
            else
                start = curr;
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr,curr);
            string intermediate_node = "intermediate node "+to_string(intermediate_count);
            intermediate_count++;
            cout<<temp<<"  -->  "<<intermediate_node<<endl;
            outfile<<temp<<"  -->  "<<intermediate_node<<endl;
            end = intermediate_node;
        }
        else if(find_string(str,"for")){
            vector<string> for_arr = parse_for(str);
            cout<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            outfile<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+for_arr[2]+" )";
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"while")){
            vector<string> while_arr = parse_while(str);
            cout<<curr<<"  -->  "<<while_arr[0]<<endl;
            outfile<<curr<<"  -->  "<<while_arr[0]<<endl;
            cout<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            outfile<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+while_arr[1]+" )";
            cout<<while_arr[0]<<"  -->  "<<temp<<endl;
            outfile<<while_arr[0]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"case") && !(find_string(str,"endcase"))){
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
            str=v[i];
            vector<string> arr;
            while(find_string(str,"endcase") == false){
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr,curr);
        }
        else{
            if(end != ""){
                curr = end;
                start = "";
                end = "";
            }
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
        }
    }
    if(end == "")
        return curr;
    return end;
}

string else_if_block(vector<string> v,string curr){
    int i = 0;
    string start = "";
    string end = "";
    while(i < v.size()){
        string str = v[i];
        if(find_string(str,"else if")){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"else") && !(find_string(str,"end")) ){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"if") && !find_string(str,"fifo")){
            if(end != ""){
                start = end;
            }
            else
                start = curr;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++; 
            string temp = if_block(arr,curr);
            string intermediate_node = "intermediate node "+to_string(intermediate_count);
            intermediate_count++;
            cout<<temp<<"  -->  "<<intermediate_node<<endl;
            outfile<<temp<<"  -->  "<<intermediate_node<<endl;
            end = intermediate_node;
        }
        else if(find_string(str,"for")){
            vector<string> for_arr = parse_for(str);
            cout<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            outfile<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+for_arr[2]+" )";
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"while")){
            vector<string> while_arr = parse_while(str);
            cout<<curr<<"  -->  "<<while_arr[0]<<endl;
            outfile<<curr<<"  -->  "<<while_arr[0]<<endl;
            cout<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            outfile<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+while_arr[1]+" )";
            cout<<while_arr[0]<<"  -->  "<<temp<<endl;
            outfile<<while_arr[0]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"case") && !(find_string(str,"endcase"))){
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
            str=v[i];
            vector<string> arr;
            while(find_string(str,"endcase") == false){
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr,curr);
        }
        else{
            if(end != ""){
                curr = end;
                start = "";
                end = "";
            }
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
        }
    }
    if(end == "")
        return curr;
    return end;
}

string else_block(vector<string> v,string curr){
    int i = 0;
    string start = "";
    string end = "";
    while(i < v.size()){
        string str = v[i];
        if(find_string(str,"else if")){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"else") && !(find_string(str,"end")) ){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"if") && !find_string(str,"fifo")){
            if(end != ""){
                start = end;
            }
            else
                start = curr;
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr,curr);
            string intermediate_node = "intermediate node "+to_string(intermediate_count);
            intermediate_count++;
            cout<<temp<<"  -->  "<<intermediate_node<<endl;
            outfile<<temp<<"  -->  "<<intermediate_node<<endl;
            end = intermediate_node;
        }
        else if(find_string(str,"for")){
            vector<string> for_arr = parse_for(str);
            cout<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            outfile<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+for_arr[2]+" )";
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"while")){
            vector<string> while_arr = parse_while(str);
            cout<<curr<<"  -->  "<<while_arr[0]<<endl;
            outfile<<curr<<"  -->  "<<while_arr[0]<<endl;
            cout<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            outfile<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+while_arr[1]+" )";
            cout<<while_arr[0]<<"  -->  "<<temp<<endl;
            outfile<<while_arr[0]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"case") && !(find_string(str,"endcase"))){
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
            str=v[i];
            vector<string> arr;
            while(find_string(str,"endcase") == false){
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr,curr);
        }
        else{
            if(end != ""){
                curr = end;
                start = "";
                end = "";
            }
            cout<<curr<<"  -->  "<<str<<endl; 
            outfile<<curr<<"  -->  "<<str<<endl; 
            curr = str;
            i++;
        }
    }
    if(end == "")
        return curr;
    return end;
}

void for_block(vector<string> v,string curr){
    vector<string> for_arr = parse_for(curr);
    int i = 0;
    string start = "";
    string end = "";
    curr = for_arr[2];
    while(i < v.size()){
        string str = v[i];
        if(find_string(str,"else if")){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"else") && !(find_string(str,"end")) ){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"if") && !find_string(str,"fifo")){
            if(end != ""){
                start = end;
            }
            else
                start = curr;
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr,curr);
            string intermediate_node = "intermediate node "+to_string(intermediate_count);
            intermediate_count++;
            cout<<temp<<"  -->  "<<intermediate_node<<endl;
            outfile<<temp<<"  -->  "<<intermediate_node<<endl;
            end = intermediate_node;
        }
        else if(find_string(str,"for")){
            vector<string> for_arr = parse_for(str);
            cout<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            outfile<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+for_arr[2]+" )";
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"while")){
            vector<string> while_arr = parse_while(str);
            cout<<curr<<"  -->  "<<while_arr[0]<<endl;
            outfile<<curr<<"  -->  "<<while_arr[0]<<endl;
            cout<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            outfile<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+while_arr[1]+" )";
            cout<<while_arr[0]<<"  -->  "<<temp<<endl;
            outfile<<while_arr[0]<<"  -->  "<<temp<<endl;
            curr = temp;
        }

        else if(find_string(str,"case") && !(find_string(str,"endcase"))){
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
            str=v[i];
            vector<string> arr;
            while(find_string(str,"endcase") == false){
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr,curr);
        }
        else{
            if(end != ""){
                curr = end;
                start = "";
                end = "";
            }
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
        }
    
    }
    cout<<curr<<"  -->  "<<for_arr[3]<<endl;
    outfile<<curr<<"  -->  "<<for_arr[3]<<endl;
    curr = for_arr[3];
    cout<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
    outfile<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
    return;
}

void while_block(vector<string> v,string curr){
    vector<string> while_arr = parse_while(curr);
    int i = 0;
    string start = "";
    string end = "";
    curr = while_arr[1];
    while(i < v.size()){
        string str = v[i];
        if(find_string(str,"else if")){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"else") && !(find_string(str,"end")) ){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"if") && !find_string(str,"fifo")){
            if(end != ""){
                start = end;
            }
            else
                start = curr;
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr,curr);
            string intermediate_node = "intermediate node "+to_string(intermediate_count);
            intermediate_count++;
            cout<<temp<<"  -->  "<<intermediate_node<<endl;
            outfile<<temp<<"  -->  "<<intermediate_node<<endl;
            end = intermediate_node;
        }
        else if(find_string(str,"for")){
            vector<string> for_arr = parse_for(str);
            cout<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            outfile<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+for_arr[2]+" )";
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"while")){
            vector<string> while_arr = parse_while(str);
            cout<<curr<<"  -->  "<<while_arr[0]<<endl;
            outfile<<curr<<"  -->  "<<while_arr[0]<<endl;
            cout<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            outfile<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+while_arr[1]+" )";
            cout<<while_arr[0]<<"  -->  "<<temp<<endl;
            outfile<<while_arr[0]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"case") && !(find_string(str,"endcase"))){
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
            str=v[i];
            vector<string> arr;
            while(find_string(str,"endcase") == false){
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr,curr);
        }
        else{
            if(end != ""){
                curr = end;
                start = "";
                end = "";
            }
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
        }
    
    }
    cout<<curr<<"  -->  "<<while_arr[0]<<endl;
    outfile<<curr<<"  -->  "<<while_arr[0]<<endl;
    curr = while_arr[0];
    return;
}

string case_block(vector<string> v,string curr){
    int i = 0;
    string start = curr;
    string end = "endcase";
    while(i < v.size()){
        string str = v[i];
        if(find_char(str,':')){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = always_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
    }

    return end;
}

string always_block(vector<string> v,string curr){
    int i = 0;
    string start = "";
    string end = "";
    while(i < v.size()){
        string str = v[i];
        if(find_string(str,"else if")){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
        }
        else if(find_string(str,"else") && !(find_string(str,"end")) ){
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr,curr);
            cout<<temp<<"  -->  "<<end<<endl;
            outfile<<temp<<"  -->  "<<end<<endl;
            curr = end;
            end = "";
        }
        else if(find_string(str,"if") && !find_string(str,"fifo")){
            if(end != ""){
                start = end;
            }
            else
                start = curr;
            cout<<start<<"  -->  "<<str<<endl;
            outfile<<start<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr,curr);
            string intermediate_node = "intermediate node "+to_string(intermediate_count);
            intermediate_count++;
            cout<<temp<<"  -->  "<<intermediate_node<<endl;
            outfile<<temp<<"  -->  "<<intermediate_node<<endl;
            end = intermediate_node;
        }
        else if(find_string(str,"for")){
            vector<string> for_arr = parse_for(str);
            cout<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            outfile<<curr<<"  -->  "<<for_arr[0]<<" , "<<for_arr[1]<<endl;
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<for_arr[2]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+for_arr[2]+" )";
            cout<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            outfile<<for_arr[0]<<" , "<<for_arr[1]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"while")){
            vector<string> while_arr = parse_while(str);
            cout<<curr<<"  -->  "<<while_arr[0]<<endl;
            outfile<<curr<<"  -->  "<<while_arr[0]<<endl;
            cout<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            outfile<<while_arr[0]<<"  -->  "<<while_arr[1]<<endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if(str == "begin"){
                count++;
                i++;
                str = v[i];
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr,curr);
            string temp = "";
            temp = temp + "!( "+while_arr[1]+" )";
            cout<<while_arr[0]<<"  -->  "<<temp<<endl;
            outfile<<while_arr[0]<<"  -->  "<<temp<<endl;
            curr = temp;
        }
        else if(find_string(str,"case") && !(find_string(str,"endcase"))){
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
            str=v[i];
            vector<string> arr;
            while(find_string(str,"endcase") == false){
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr,curr);
        }
        else{
            if(end != ""){
                curr = end;
                start = "";
                end = "";
            }
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            i++;
        }
    }
    if(end == "")
        return curr;
    return end;
}

int main()
{
    auto start = high_resolution_clock::now();
    cout<<"Give the input file name :- "<<endl;
    outfile<<"Give the input file name :- "<<endl;
    // cin>>input_file;
    // cout<<"Give the output file name :- "<<endl;
    // cin>>outfile_file;
    // cout<<endl;

    input_file = "my_output.txt";
    // output_file = "cfg.txt";

    outfile.open(output_file);

    string str;
    ifstream file(input_file);
    string curr = "START";

    while(getline(file, str))
    {
        if(find_string(str,"always")){
            graph[curr].push_back(str);
            cout<<curr<<"  -->  "<<str<<endl;
            outfile<<curr<<"  -->  "<<str<<endl;
            curr = str;
            int count = 0;
            vector<string> v;
            getline(file,str);
            if(str == "begin"){
                count++;
                getline(file,str);
            }
            while(count > 0){
                if(str == "begin"){
                    count++;
                }
                else if(str == "end"){
                    count--;
                }
                if(count != 0){
                    v.push_back(str);
                    getline(file,str);
                }
            }
            curr = always_block(v,curr);
        }
        // else if(find_char(str,'=')){
        //     cout<<curr<<"  -->  "<<str<<endl;
        //     outfile<<curr<<"  -->  "<<str<<endl;
        //     curr = str;
        // }
    }
    cout<<curr<<"  -->  "<<"END"<<endl;
    outfile<<curr<<"  -->  "<<"END"<<endl;

}
