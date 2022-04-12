#include <bits/stdc++.h>
#include <stack>
using namespace std;

string cond(string s)
{
    string output = "";
    stack<char> st;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            st.push(s[i]);
            output = output + s[i];
        }
        else if (s[i] == ')')
        {
            st.pop();
            output = output + s[i];
        }
        else if (!st.empty())
        {
            output = output + s[i];
        }
    }
    return output;
}

void fsm(int line)
{
    int l = line;
    ifstream f("input_1.v");
    string str;
    string temp;
    string condition;
    stack<string> st;
    int flag = 0;
    for (int j = 1; j <= l; j++)
    {
        getline(f, str);
        l++;
        if (j > line)
        {
            string word = "";
            for (int i = 0; i < str.length(); i++)
            {
                if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '.' || str[i] == '_' || str[i] == '\'' || (str[i] >= 'A' && str[i] <= 'Z'))
                {
                    word = word + str[i];
                    // cout << word <<" "<<temp <<endl;

                }
                else if (str[i] == ':')
                {
                    flag = 1;
                    // cout << word <<" "<<temp <<endl;
                }
                else if (word == "if" && flag == 1)
                {
                    condition = cond(str);
                    getline(f, str);
                    j++, l++;
                    string nstate = "";
                    for (int k = str.length() - 2; str[k] != ' '; k--)
                    {
                        nstate = str[k] + nstate;
                    }
                    cout << temp << " ----> " << condition << " ----> " << nstate << endl;
                    st.push(condition);
                    word = "";
                    break;
                }
                else if (word == "else" && str.substr(i + 1, 2) == "if" && flag == 1)
                {
                    i += 2;
                    condition = cond(str);
                    getline(f, str);
                    j++, l++;
                    string nstate = "";
                    for (int k = str.length() - 2; str[k] != ' '; k--)
                    {
                        nstate = str[k] + nstate;
                    }
                    stack<string> tempst;
                    string fcond = "";
                    while (!st.empty())
                    {
                        string w = st.top();
                        st.pop();
                        tempst.push(w);
                        fcond = fcond + "!" + w + " & ";
                    }
                    fcond = fcond + condition;
                    cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                    while (!tempst.empty())
                    {
                        st.push(tempst.top());
                        tempst.pop();
                    }
                    st.push(condition);
                    word = "";
                    break;
                }
                else if (word == "else" && flag == 1)
                {
                    getline(f, str);
                    j++, l++;
                    string nstate = "";
                    for (int k = str.length() - 2; str[k] != ' '; k--)
                    {
                        nstate = str[k] + nstate;
                    }
                    string fcond = "";
                    while (!st.empty())
                    {
                        string w = st.top();
                        st.pop();

                        fcond = fcond + "!" + w + " & ";
                    }
                    fcond = fcond.substr(0, fcond.length() - 3);
                    cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                    word = "";
                    flag=0;
                    break;
                }
                else if (str[i] == ' ')
                {
                    if(flag==0 && word!="")
                        temp = word;
                    word = "";
                }
                else if (str[i] == '/')
                {
                    break;
                }
            }
            if (word == "endcase")
            {
                return;
            }
        }
    }
}

int main()
{
    ifstream file("input_1.v");
    string str;
    int cnt = 1;
    while (getline(file, str))
    {
        string word = "";
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '/')
            {
                break;
            }
            else if (word == "case")
            {
                fsm(cnt);
                word = "";
            }
            else if (str[i] == ' ' || str[i] == '(' || str[i] == ';' || str[i] == ',')
            {
                if (word != "")
                {
                    word = "";
                }
            }

            else if (str[i] == ':' || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '.' || str[i] == '_' || str[i] == '\'' || (str[i] >= 'A' && str[i] <= 'Z'))
            {
                word = word + str[i];
            }
        }
        word = "";
        cnt++;
    }
}