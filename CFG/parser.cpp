#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

string input_file;
string int1_file;
string int2_file;
string output_file;

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
	return rtrim(ltrim(s));
}

void removeComments(vector<char> program,string int_file){
    ofstream my_file;
    my_file.open(int_file);
    int n = program.size();
    vector<char> output;
    bool s_cmt = false;
    bool m_cmt = false;

    for(int i=0; i < n; i++){
        if(s_cmt == true && program[i] == '\n'){
            my_file<<program[i];
            s_cmt = false;
        }

        else if (m_cmt == true && program[i] == '*' && program[i+1] == '/'){
            m_cmt = false,  i++;
        } 

        else if(s_cmt || m_cmt){
            continue;
        }
 
        else if(program[i] == '/' && program[i+1] == '/'){
            s_cmt = true, i++;
        }
        else if(program[i] == '/' && program[i+1] == '*')
            m_cmt = true,  i++;
 
        else  {
            my_file<<program[i];
        }
    }
    return;
}

bool find_string(string str,string str1){
    size_t found = str.find(str1);
    if (found != string::npos)
        return true;
    else
        return false;
}

bool check_colon_arr(string str){
    size_t ind = str.find(':');
    int len = str.length();
    int flag = 0;
    for(int i=ind;i>=0;i--){
        if(str[i]=='['){
            flag++;
            break;
        }
    }
    for(int i=ind;i<len;i++){
        if(str[i]==']'){
            flag++;
            break;
        }
    }
    if(flag == 2)
        return true;
    return false;
}

int main()
{
    auto start = high_resolution_clock::now();
    cout<<"Give the input file name :- "<<endl;
    // cin>>input_file;
    cout<<"Give the output file name :- "<<endl;
    // cin>>outfile_file;

    input_file = "check.v";
    int1_file = "intermediate1.txt";
    int2_file = "intermediate2.txt";
    output_file = "my_output.txt";

    ofstream myfile1;
    myfile1.open (int1_file);


    ifstream file1(input_file, ios::binary | ios::ate);
    streamsize size = file1.tellg();
    file1.seekg(0, ios::beg);
    vector<char> buffer(size);

    if(file1.read(buffer.data(), size)){
        removeComments(buffer,int1_file);
    }


    string str;
    int cnt = 1;
    ifstream file2(int1_file);
    ofstream myfile2;
    myfile2.open (int2_file);
    while(getline(file2, str))
    {
        str = trim(str);
        if(str.length() != 0)
            myfile2<<str<<endl;
    }

    ifstream file3(int2_file);
    ofstream outfile;
    outfile.open(output_file);
    cnt = 1;
    while (getline(file3, str))
    {
        if(find_string(str,"else if")){
            if(find_string(str,"end")){
                string qw = "";
                qw += str[0];
                qw += str[1];
                qw += str[2];
                if(qw=="end"){
                    outfile<<"end"<<endl;
                }
                str = str.substr(4,str.length()-4);
            }
            if(find_string(str,"begin")){
                size_t ind = str.find("begin");
                str.erase(ind-1,6);
                outfile<<str<<endl;
                outfile<<"begin"<<endl;
            }
            else{
                outfile<<str<<endl;
                getline(file3,str);
                if(!find_string(str,"begin")){
                    outfile<<"begin"<<endl;
                    outfile<<str<<endl;
                    outfile<<"end"<<endl;
                }
                else{
                    outfile<<"begin"<<endl;
                }
            }
        }
        
        else if(find_string(str,"if") && !find_string(str,"fifo")){
            if(find_string(str,"end") && !find_string(str,"send") ){
                string qw = "";
                qw += str[0];
                qw += str[1];
                qw += str[2];
                if(qw=="end"){
                    outfile<<"end"<<endl;
                }
                str = str.substr(4,str.length()-4);
            }
            if(find_string(str,"begin")){
                size_t ind = str.find("begin");
                str.erase(ind-1,6);
                outfile<<str<<endl;
                outfile<<"begin"<<endl;
            }
            else{
                outfile<<str<<endl;
                getline(file3,str);
                if(!find_string(str,"begin")){
                    outfile<<"begin"<<endl;
                    outfile<<str<<endl;
                    outfile<<"end"<<endl;
                }
                else{
                    outfile<<"begin"<<endl;
                }
            }
        }

        else if(find_string(str,"else")){
            if(find_string(str,"end")){
                string qw = "";
                qw += str[0];
                qw += str[1];
                qw += str[2];
                if(qw=="end"){
                    outfile<<"end"<<endl;
                }
                str = str.substr(4,str.length()-4);
            }
            if(find_string(str,"begin")){
                size_t ind = str.find("begin");
                str.erase(ind-1,6);
                outfile<<str<<endl;
                outfile<<"begin"<<endl;
            }
            else{
                outfile<<str<<endl;
                getline(file3,str);
                if(!find_string(str,"begin")){
                    outfile<<"begin"<<endl;
                    outfile<<str<<endl;
                    outfile<<"end"<<endl;
                }
                else{
                    outfile<<"begin"<<endl;
                }
            }
        }

        else if(find_string(str,"always")){
            int count = 0;
            int len = str.length();
            bool flag = false;
            string qw = "";
            for(int i=0;i<len;i++){
                char c = str[i];
                if(c == '('){
                    count++;
                    flag = true;
                }
                else if(c == ')')
                    count--;
                if(count == 0 && flag){
                    qw += str;
                    break;
                }
                if(i == len-1){
                    qw += str;
                    getline(file3,str);
                    len = str.length();
                    i = -1;
                }
            }
            str = qw;
            if(find_string(str,"end")){
                string qw = "";
                qw += str[0];
                qw += str[1];
                qw += str[2];
                if(qw=="end"){
                    outfile<<"end"<<endl;
                }
                str = str.substr(4,str.length()-4);
            }
            if(find_string(str,"begin")){
                size_t ind = str.find("begin");
                str.erase(ind-1,6);
                outfile<<str<<endl;
                outfile<<"begin"<<endl;
            }
            else{
                outfile<<str<<endl;
                getline(file3,str);
                if(!find_string(str,"begin")){
                    outfile<<"begin"<<endl;
                    outfile<<str<<endl;
                    outfile<<"end"<<endl;
                }
                else{
                    outfile<<"begin"<<endl;
                }
            }
        }

        else if(find_string(str,"for")){
            if(find_string(str,"end")){
                string qw = "";
                qw += str[0];
                qw += str[1];
                qw += str[2];
                if(qw=="end"){
                    outfile<<"end"<<endl;
                }
                str = str.substr(4,str.length()-4);
            }
            if(find_string(str,"begin")){
                size_t ind = str.find("begin");
                str.erase(ind-1,6);
                outfile<<str<<endl;
                outfile<<"begin"<<endl;
            }
            else{
                outfile<<str<<endl;
                getline(file3,str);
                if(!find_string(str,"begin")){
                    outfile<<"begin"<<endl;
                    outfile<<str<<endl;
                    outfile<<"end"<<endl;
                }
                else{
                    outfile<<"begin"<<endl;
                }
            }
        }

        else if(find_string(str,"while")){
            if(find_string(str,"end")){
                string qw = "";
                qw += str[0];
                qw += str[1];
                qw += str[2];
                if(qw=="end"){
                    outfile<<"end"<<endl;
                }
                str = str.substr(4,str.length()-4);
            }
            if(find_string(str,"begin")){
                size_t ind = str.find("begin");
                str.erase(ind-1,6);
                outfile<<str<<endl;
                outfile<<"begin"<<endl;
            }
            else{
                outfile<<str<<endl;
                getline(file3,str);
                if(!find_string(str,"begin")){
                    outfile<<"begin"<<endl;
                    outfile<<str<<endl;
                    outfile<<"end"<<endl;
                }
                else{
                    outfile<<"begin"<<endl;
                }
            }
        }

        else if(find_string(str,":") && !find_string(str,"reg") && !(find_string(str,"wire")) 
                && !(find_string(str,"assign")) && !(find_string(str,"if")) && !(find_string(str,"else")) 
                && !(find_string(str,"function")) && !check_colon_arr(str) )
        {
            if(find_string(str,"end")){
                string qw = "";
                qw += str[0];
                qw += str[1];
                qw += str[2];
                if(qw=="end"){
                    outfile<<"end"<<endl;
                }
                str = str.substr(4,str.length()-4);
            }
            if(find_string(str,"begin")){
                size_t ind = str.find("begin");
                str.erase(ind,5);
                outfile<<str<<endl;
                outfile<<"begin"<<endl;
            }
            else{
                // outfile<<str<<endl;
                string before = str;
                getline(file3,str);
                if(!find_string(str,"begin")){
                    string case_st = "";
                    string nxt_st = "";
                    bool check = false;
                    for(auto i:before){
                        if(!check){
                            case_st += i;
                        }
                        else{
                            if(i==' ')
                                continue;
                            nxt_st += i;
                        }
                        if(i==':'){
                            check = true;
                        }
                    }
                    outfile<<case_st<<endl;
                    outfile<<"begin"<<endl;
                    outfile<<nxt_st<<endl;
                    outfile<<"end"<<endl;
                    if(find_string(str,"endcase")){
                        outfile<<str<<endl;
                    }
                }
                else{
                    outfile<<before<<endl;
                    outfile<<"begin"<<endl;
                }
            }
        }

        else{
            outfile<<str<<endl;
        }
    }

}
