#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

vector<tuple<string, string, string>> fsmstates;
string null = "NULL";
string default_state = "";

bool nested(string str)
{
    string str1 = "if";
    size_t found = str.find(str1);
    if (found != string::npos)
        return true;

    return false;
}

bool findend(string str)
{
    string str1 = "end";
    size_t found = str.find(str1);
    if (found != string::npos)
        return true;

    return false;
}

bool findelse(string str)
{
    string str1 = "else";
    size_t found = str.find(str1);
    if (found != string::npos)
        return true;

    return false;
}

bool findnstate(string str, string state)
{

    size_t found = str.find(state);
    if (found != string::npos)
        return true;

    return false;
}

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
    ifstream f("sample_input6.v");
    string str;
    string temp;
    string condition;
    stack<string> st;
    string nst = "";
    int flag_nst = 0;
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
                if(word == "endcase"){
                    return;
                }
                if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '.' || str[i] == '_' || str[i] == '\'' || (str[i] >= 'A' && str[i] <= 'Z'))
                {
                    word = word + str[i];
                    // cout << word << " " << temp << endl;
                    if (word == nst && flag == 1 && flag_nst == 1)
                    {
                        word = "";
                        int z = str.length() - 2;
                        string qwe = "";
                        while (str[z] != ' ')
                        {
                            qwe = str[z--] + qwe;
                        }
                        if (temp != "default")
                        {
                            // cout << temp << " ----> " << null << " ----> " << qwe << endl;
                            fsmstates.push_back(make_tuple(temp, null, qwe));
                        }
                        else
                        {
                            // cout << temp << " ---->" << qwe << endl;
                            default_state = qwe;
                        }
                    }
                    if (word == "else" && flag == 1 && str[i + 1] != ' ')
                    {
                        int countbegin = 0;
                        string findbegin = str.substr(str.length() - 5, 5);
                        getline(f, str);
                        j++, l++;
                        if (findbegin == "begin")
                        {
                            countbegin++;
                            while (!findend(str) && !findnstate(str, nst) && !nested(str))
                            {
                                getline(f, str);
                                j++, l++;
                            }
                            if (findend(str))
                            {
                                word = "";
                                flag = 0;
                                break;
                            }
                            else if (findnstate(str, nst))
                            {
                                string nstate = "";
                                for (int k = str.length() - 2; str[k] != ' '; k--)
                                {
                                    nstate = str[k] + nstate;
                                }
                                string fcond = "";
                                stack<string> tempst;
                                while (!st.empty())
                                {
                                    string w = st.top();
                                    // cout<<w<<endl;
                                    st.pop();
                                    tempst.push(w);
                                    fcond = fcond + "!" + w + " & ";
                                }
                                fcond=fcond.substr(0,fcond.length()-3);
                                // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                word = "";
                                flag = 0;
                                break;
                            }

                            else if (nested(str))
                            {
                                findbegin = str.substr(str.length() - 5, 5);
                                string nifcond = cond(str);
                                getline(f, str);
                                j++, l++;
                                if (findbegin == "begin")
                                {
                                    countbegin++;
                                    while (!findend(str) && !findnstate(str, nst))
                                    {
                                        getline(f, str);
                                        j++, l++;
                                    }
                                    if (findend(str))
                                    {
                                        getline(f, str);
                                        j++, l++;
                                        if (!findelse(str))
                                        {
                                            word = "";
                                            flag = 0;
                                            break;
                                        }
                                        else
                                        {
                                            findbegin = str.substr(str.length() - 5, 5);
                                            getline(f, str);
                                            j++, l++;
                                            if (findbegin != "begin")
                                            {
                                                if (findnstate(str, nst))
                                                {
                                                    string nstate = "";
                                                    for (int k = str.length() - 2; str[k] != ' '; k--)
                                                    {
                                                        nstate = str[k] + nstate;
                                                    }
                                                    string fcond = "";
                                                    stack<string> tempst;
                                                    while (!st.empty())
                                                    {
                                                        string w = st.top();
                                                        // cout<<w<<endl;
                                                        st.pop();
                                                        tempst.push(w);
                                                        fcond = fcond + "!" + w + " & ";
                                                    }
                                                    fcond=fcond.substr(0,fcond.length()-3);
                                                    // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                                    fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                                    word = "";
                                                    flag = 0;
                                                    break;
                                                }
                                                else
                                                {
                                                    word = "";
                                                    flag = 0;
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                countbegin++;
                                                while (!findend(str) && !findnstate(str, nst))
                                                {
                                                    getline(f, str);
                                                    j++, l++;
                                                }
                                                if (findend(str))
                                                {
                                                    word = "";
                                                    flag = 0;
                                                    break;
                                                }
                                                else
                                                {
                                                    string nstate = "";
                                                    for (int k = str.length() - 2; str[k] != ' '; k--)
                                                    {
                                                        nstate = str[k] + nstate;
                                                    }
                                                    string fcond = "";
                                                    stack<string> tempst;
                                                    while (!st.empty())
                                                    {
                                                        string w = st.top();
                                                        // cout<<w<<endl;
                                                        st.pop();
                                                        tempst.push(w);
                                                        fcond = fcond + "!" + w + " & ";
                                                    }
                                                    fcond=fcond.substr(0,fcond.length()-3);
                                                    // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                                    fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                                    word = "";
                                                    flag = 0;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    else if (findnstate(str, nst))
                                    {
                                        string nstate = "";
                                        for (int k = str.length() - 2; str[k] != ' '; k--)
                                        {
                                            nstate = str[k] + nstate;
                                        }
                                        string fcond = "";
                                        stack<string> tempst;
                                        while (!st.empty())
                                        {
                                            string w = st.top();
                                            // cout<<w<<endl;
                                            st.pop();
                                            tempst.push(w);
                                            fcond = fcond + "!" + w + " & ";
                                        }
                                        fcond = fcond + nifcond;
                                        fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                        // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                        while (!tempst.empty())
                                        {
                                            st.push(tempst.top());
                                            tempst.pop();
                                        }
                                        st.push(nifcond);
                                        word = "";

                                        getline(f, str);
                                        j++, l++;
                                        while (!findend(str))
                                        {
                                            getline(f, str);
                                            j++, l++;
                                        }
                                        countbegin--;
                                        getline(f, str);
                                        j++, l++;
                                        if (findelse(str))
                                        {
                                            findbegin = str.substr(str.length() - 5, 5);
                                            getline(f, str);
                                            j++, l++;
                                            if (findbegin == "begin")
                                            {
                                                while (!findend(str) && !findnstate(str, nst))
                                                {
                                                    getline(f, str);
                                                    j++, l++;
                                                }
                                                if (findend(str))
                                                {
                                                    word = "";
                                                    flag = 0;
                                                    break;
                                                }
                                                else if (findnstate(str, nst))
                                                {
                                                    string nstate = "";
                                                    for (int k = str.length() - 2; str[k] != ' '; k--)
                                                    {
                                                        nstate = str[k] + nstate;
                                                    }
                                                    string fcond = "";
                                                    stack<string> tempst;
                                                    while (!st.empty())
                                                    {
                                                        string w = st.top();
                                                        // cout<<w<<endl;
                                                        st.pop();
                                                        tempst.push(w);
                                                        fcond = fcond + "!" + w + " & ";
                                                    }
                                                    fcond=fcond.substr(0,fcond.length()-3);
                                                    // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                                    fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                                    word = "";
                                                    flag = 0;
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                if (findnstate(str, nst))
                                                {
                                                    string nstate = "";
                                                    for (int k = str.length() - 2; str[k] != ' '; k--)
                                                    {
                                                        nstate = str[k] + nstate;
                                                    }
                                                    string fcond = "";
                                                    stack<string> tempst;
                                                    while (!st.empty())
                                                    {
                                                        string w = st.top();
                                                        // cout<<w<<endl;
                                                        st.pop();
                                                        tempst.push(w);
                                                        fcond = fcond + "!" + w + " & ";
                                                    }
                                                    fcond=fcond.substr(0,fcond.length()-3);
                                                    // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                                    fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                                    word = "";
                                                    flag = 0;
                                                    break;
                                                }
                                                else
                                                {
                                                    word = "";
                                                    flag = 0;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        countbegin--;
                                    }
                                }
                                else
                                {
                                    if (findnstate(str, nst))
                                    {
                                        string nstate = "";
                                        for (int k = str.length() - 2; str[k] != ' '; k--)
                                        {
                                            nstate = str[k] + nstate;
                                        }
                                        string fcond = "";
                                        stack<string> tempst;
                                        while (!st.empty())
                                        {
                                            string w = st.top();
                                            // cout<<w<<endl;
                                            st.pop();
                                            tempst.push(w);
                                            fcond = fcond + "!" + w + " & ";
                                        }
                                        fcond = fcond + nifcond;
                                        fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                        // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                        while (!tempst.empty())
                                        {
                                            st.push(tempst.top());
                                            tempst.pop();
                                        }
                                        st.push(nifcond);
                                        word = "";
                                    }
                                    else
                                    {
                                        word = "";
                                        flag = 0;
                                        break;
                                    }
                                }
                            }
                            if (findnstate(str, nst))
                            {
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
                                // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                fsmstates.push_back(make_tuple(temp, fcond, nstate));
                            }
                            else
                            {
                                while (!st.empty())
                                {
                                    st.pop();
                                }
                                word = "";
                                flag = 0;
                                break;
                            }
                        }
                        else
                        {
                            if (findnstate(str, nst))
                            {
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
                                // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                fsmstates.push_back(make_tuple(temp, fcond, nstate));
                            }
                            else
                            {
                                word = "";
                                flag = 0;
                                break;
                            }
                        }
                        word = "";
                        flag = 0;
                        break;
                    }
                }
                else if (str[i] == ':')
                {
                    while (!st.empty())
                    {
                        st.pop();
                    }
                    flag = 1;
                    if (word != "")
                    {
                        temp = word;
                    }
                    word = "";
                }
                else if (word == "if" && flag == 1)
                {
                    int countbegin = 0;
                    condition = cond(str);
                    string findbegin = str.substr(str.length() - 5, 5);
                    getline(f, str);
                    j++, l++;
                    if (findbegin == "begin")
                    {
                        countbegin++;
                        if (nst != "")
                        {
                            while (!findnstate(str, nst) && !nested(str))
                            {
                                getline(f, str);
                                j++, l++;
                            }
                        }
                        if (nested(str))
                        {
                            string findbegin2 = str.substr(str.length() - 5, 5);
                            if (findbegin2 == "begin")
                                countbegin++;
                            string ifcond = cond(str);
                            getline(f, str);
                            j++, l++;
                            while (!findnstate(str, nst))
                            {
                                getline(f, str);
                                j++, l++;
                            }
                            string nstate = "";
                            int k = str.length() - 2;
                            while (str[k] != ' ')
                            {
                                nstate = str[k--] + nstate;
                            }
                            if (flag_nst == 0)
                            {
                                flag_nst = 1;
                                k -= 3;
                                while (str[k] != ' ' && str[k] != '	')
                                {
                                    nst = str[k--] + nst;
                                }
                            }
                            // cout << temp << " ----> " << condition << " & " << ifcond << " ----> " << nstate << endl;
                            fsmstates.push_back(make_tuple(temp, condition + " & " + ifcond, nstate));
                            getline(f, str);
                            j++, l++;
                            if (findend(str))
                                countbegin--;
                            if (countbegin == 0)
                            {
                                st.push(condition);
                                word = "";
                                break;
                            }
                            getline(f, str);
                            j++, l++;
                            if (findend(str))
                                countbegin--;
                            if (countbegin == 0)
                            {
                                st.push(condition);
                                word = "";
                                break;
                            }
                            while (!findnstate(str, nst))
                            {
                                getline(f, str);
                                j++, l++;
                            }
                            nstate = "";
                            k = str.length() - 2;
                            while (str[k] != ' ')
                            {
                                nstate = str[k--] + nstate;
                            }
                            // cout << temp << " ----> " << condition << " & "
                            //      << "! " << ifcond << " ----> " << nstate << endl;
                            fsmstates.push_back(make_tuple(temp, condition + " & " + "! " + ifcond, nstate));
                        }
                        else
                        {
                            if (flag_nst == 1)
                            {
                                while (!findnstate(str, nst))
                                {
                                    getline(f, str);
                                    j++, l++;
                                }
                            }
                            string nstate = "";
                            int k = str.length() - 2;
                            while (str[k] != ' ')
                            {
                                nstate = str[k--] + nstate;
                            }
                            if (flag_nst == 0)
                            {
                                flag_nst = 1;
                                k -= 3;
                                while (str[k] != ' ' && str[k] != '	')
                                {
                                    nst = str[k--] + nst;
                                }
                            }
                            // cout << temp << " ----> " << condition << " ----> " << nstate << endl;
                            fsmstates.push_back(make_tuple(temp, condition, nstate));
                        }
                        st.push(condition);
                        word = "";
                        break;
                    }
                    else
                    {
                        if (flag_nst == 1)
                        {
                            string line1state = "";
                            int k = 0;
                            while (str[k] == ' ' || str[k] == '	')
                                k++;
                            while (str[k] != ' ')
                            {
                                line1state += str[k++];
                            }
                            if (line1state == nst)
                            {
                                string nstate = "";
                                k = str.length() - 2;
                                while (str[k] != ' ')
                                {
                                    nstate = str[k--] + nstate;
                                }
                                // cout << temp << " ----> " << condition << " ----> " << nstate << endl;
                                fsmstates.push_back(make_tuple(temp, condition, nstate));
                            }
                            else
                                break;
                        }
                        else
                        {
                            string nstate = "";
                            int k = str.length() - 2;
                            while (str[k] != ' ')
                            {
                                nstate = str[k--] + nstate;
                            }
                            if (flag_nst == 0)
                            {
                                flag_nst = 1;
                                k -= 3;
                                while (str[k] != ' ' && str[k] != '	')
                                {
                                    nst = str[k--] + nst;
                                }
                            }
                            fsmstates.push_back(make_tuple(temp, condition, nstate));
                            // cout << temp << " ----> " << condition << " ----> " << nstate << endl;
                        }
                    }
                    st.push(condition);
                    word = "";
                    break;
                }
                else if (word == "else" && i + 2 < str.length() && str.substr(i + 1, 2) == "if" && flag == 1)
                {
                    string fcond = "";
                    i += 2;
                    condition = cond(str);
                    getline(f, str);
                    j++, l++;
                    while (!findnstate(str, nst))
                    {
                        if (nested(str))
                        {
                            fcond = cond(str) + " & ";
                        }
                        getline(f, str);
                        j++, l++;
                    }
                    string nstate = "";
                    for (int k = str.length() - 2; str[k] != ' '; k--)
                    {
                        nstate = str[k] + nstate;
                    }
                    stack<string> tempst;
                    while (!st.empty())
                    {
                        string w = st.top();
                        // cout<<w<<endl;
                        st.pop();
                        tempst.push(w);
                        fcond = fcond + "!" + w + " & ";
                    }
                    fcond = fcond + condition;
                    fsmstates.push_back(make_tuple(temp, fcond, nstate));
                    // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
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
                    int countbegin = 0;
                    string findbegin = str.substr(str.length() - 5, 5);
                    getline(f, str);
                    j++, l++;
                    if (findbegin == "begin")
                    {
                        countbegin++;
                        while (!findend(str) && !findnstate(str, nst) && !nested(str))
                        {
                            getline(f, str);
                            j++, l++;
                        }
                        if (findend(str))
                        {
                            word = "";
                            flag = 0;
                            break;
                        }
                        else if (findnstate(str, nst))
                        {
                            string nstate = "";
                            for (int k = str.length() - 2; str[k] != ' '; k--)
                            {
                                nstate = str[k] + nstate;
                            }
                            string fcond = "";
                            stack<string> tempst;
                            while (!st.empty())
                            {
                                string w = st.top();
                                // cout<<w<<endl;
                                st.pop();
                                tempst.push(w);
                                fcond = fcond + "!" + w + " & ";
                            }
                            fcond=fcond.substr(0,fcond.length()-3);
                            // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                            fsmstates.push_back(make_tuple(temp, fcond, nstate));
                            word = "";
                            flag = 0;
                            break;
                        }

                        else if (nested(str))
                        {
                            findbegin = str.substr(str.length() - 5, 5);
                            string nifcond = cond(str);
                            getline(f, str);
                            j++, l++;
                            if (findbegin == "begin")
                            {
                                countbegin++;
                                while (!findend(str) && !findnstate(str, nst))
                                {
                                    getline(f, str);
                                    j++, l++;
                                }
                                if (findend(str))
                                {
                                    getline(f, str);
                                    j++, l++;
                                    if (!findelse(str))
                                    {
                                        word = "";
                                        flag = 0;
                                        break;
                                    }
                                    else
                                    {
                                        findbegin = str.substr(str.length() - 5, 5);
                                        getline(f, str);
                                        j++, l++;
                                        if (findbegin != "begin")
                                        {
                                            if (findnstate(str, nst))
                                            {
                                                string nstate = "";
                                                for (int k = str.length() - 2; str[k] != ' '; k--)
                                                {
                                                    nstate = str[k] + nstate;
                                                }
                                                string fcond = "";
                                                stack<string> tempst;
                                                while (!st.empty())
                                                {
                                                    string w = st.top();
                                                    // cout<<w<<endl;
                                                    st.pop();
                                                    tempst.push(w);
                                                    fcond = fcond + "!" + w + " & ";
                                                }
                                                fcond=fcond.substr(0,fcond.length()-3);
                                                // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                                fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                                word = "";
                                                flag = 0;
                                                break;
                                            }
                                            else
                                            {
                                                word = "";
                                                flag = 0;
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            countbegin++;
                                            while (!findend(str) && !findnstate(str, nst))
                                            {
                                                getline(f, str);
                                                j++, l++;
                                            }
                                            if (findend(str))
                                            {
                                                word = "";
                                                flag = 0;
                                                break;
                                            }
                                            else
                                            {
                                                string nstate = "";
                                                for (int k = str.length() - 2; str[k] != ' '; k--)
                                                {
                                                    nstate = str[k] + nstate;
                                                }
                                                string fcond = "";
                                                stack<string> tempst;
                                                while (!st.empty())
                                                {
                                                    string w = st.top();
                                                    // cout<<w<<endl;
                                                    st.pop();
                                                    tempst.push(w);
                                                    fcond = fcond + "!" + w + " & ";
                                                }
                                                fcond=fcond.substr(0,fcond.length()-3);
                                                // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                                fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                                word = "";
                                                flag = 0;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else if (findnstate(str, nst))
                                {
                                    string nstate = "";
                                    for (int k = str.length() - 2; str[k] != ' '; k--)
                                    {
                                        nstate = str[k] + nstate;
                                    }
                                    string fcond = "";
                                    stack<string> tempst;
                                    while (!st.empty())
                                    {
                                        string w = st.top();
                                        // cout<<w<<endl;
                                        st.pop();
                                        tempst.push(w);
                                        fcond = fcond + "!" + w + " & ";
                                    }
                                    fcond = fcond + nifcond;
                                    fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                    // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                    while (!tempst.empty())
                                    {
                                        st.push(tempst.top());
                                        tempst.pop();
                                    }
                                    st.push(nifcond);
                                    word = "";

                                    getline(f, str);
                                    j++, l++;
                                    while (!findend(str))
                                    {
                                        getline(f, str);
                                        j++, l++;
                                    }
                                    countbegin--;
                                    getline(f, str);
                                    j++, l++;
                                    if (findelse(str))
                                    {
                                        findbegin = str.substr(str.length() - 5, 5);
                                        getline(f, str);
                                        j++, l++;
                                        if (findbegin == "begin")
                                        {
                                            while (!findend(str) && !findnstate(str, nst))
                                            {
                                                getline(f, str);
                                                j++, l++;
                                            }
                                            if (findend(str))
                                            {
                                                word = "";
                                                flag = 0;
                                                break;
                                            }
                                            else if (findnstate(str, nst))
                                            {
                                                string nstate = "";
                                                for (int k = str.length() - 2; str[k] != ' '; k--)
                                                {
                                                    nstate = str[k] + nstate;
                                                }
                                                string fcond = "";
                                                stack<string> tempst;
                                                while (!st.empty())
                                                {
                                                    string w = st.top();
                                                    // cout<<w<<endl;
                                                    st.pop();
                                                    tempst.push(w);
                                                    fcond = fcond + "!" + w + " & ";
                                                }
                                                fcond=fcond.substr(0,fcond.length()-3);
                                                // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                                fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                                word = "";
                                                flag = 0;
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            if (findnstate(str, nst))
                                            {
                                                string nstate = "";
                                                for (int k = str.length() - 2; str[k] != ' '; k--)
                                                {
                                                    nstate = str[k] + nstate;
                                                }
                                                string fcond = "";
                                                stack<string> tempst;
                                                while (!st.empty())
                                                {
                                                    string w = st.top();
                                                    // cout<<w<<endl;
                                                    st.pop();
                                                    tempst.push(w);
                                                    fcond = fcond + "!" + w + " & ";
                                                }
                                                fcond=fcond.substr(0,fcond.length()-3);
                                                // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                                fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                                word = "";
                                                flag = 0;
                                                break;
                                            }
                                            else
                                            {
                                                word = "";
                                                flag = 0;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    countbegin--;
                                }
                            }
                            else
                            {
                                if (findnstate(str, nst))
                                {
                                    string nstate = "";
                                    for (int k = str.length() - 2; str[k] != ' '; k--)
                                    {
                                        nstate = str[k] + nstate;
                                    }
                                    string fcond = "";
                                    stack<string> tempst;
                                    while (!st.empty())
                                    {
                                        string w = st.top();
                                        // cout<<w<<endl;
                                        st.pop();
                                        tempst.push(w);
                                        fcond = fcond + "!" + w + " & ";
                                    }
                                    fcond = fcond + nifcond;
                                    fsmstates.push_back(make_tuple(temp, fcond, nstate));
                                    // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                                    while (!tempst.empty())
                                    {
                                        st.push(tempst.top());
                                        tempst.pop();
                                    }
                                    st.push(nifcond);
                                    word = "";
                                }
                                else
                                {
                                    word = "";
                                    flag = 0;
                                    break;
                                }
                            }
                        }
                        if (findnstate(str, nst))
                        {
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
                            // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                            fsmstates.push_back(make_tuple(temp, fcond, nstate));
                        }
                        else
                        {
                            while (!st.empty())
                            {
                                st.pop();
                            }
                            word = "";
                            flag = 0;
                            break;
                        }
                    }
                    else
                    {
                        if (findnstate(str, nst))
                        {
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
                            // cout << temp << " ----> " << fcond << " ----> " << nstate << endl;
                            fsmstates.push_back(make_tuple(temp, fcond, nstate));
                        }
                        else
                        {
                            word = "";
                            flag = 0;
                            break;
                        }
                    }
                    word = "";
                    flag = 0;
                    break;
                }
                else if (str[i] == ' ')
                {
                    if (flag == 0 && word != "")
                    {
                        // cout << word << " " << temp << endl;
                        temp = word;
                    }
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
    auto start = high_resolution_clock::now();

    ifstream file("sample_input6.v");
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

    cout<<"Default state --- " << default_state<<endl<<endl<<endl;
    set<string> allstates;
    set<string> states_self_loops;
    int self_loops = 0;
    int transitions = 0;

    for (auto it : fsmstates)
    {
        cout << get<0>(it) << " ----> " << get<1>(it) << " ----> " << get<2>(it) << endl<< endl;
        if (get<0>(it) == get<2>(it))
        {
            self_loops++;
            states_self_loops.insert(get<0>(it));
        }
        else
            transitions++;
        allstates.insert(get<0>(it));
        allstates.insert(get<2>(it));
    }

    cout << endl
         << endl;

    cout << "Total no of states = " << allstates.size() << endl
         << "All states are :-  " << endl;
    for (auto it : allstates)
    {
        cout << it << " , ";
    }
    cout << endl
         << endl;

    cout << "No of self loops = " << self_loops << endl;
    cout << "No of transitions = " << transitions << endl
         << endl;
    cout << "States having self loops :-  ";
    if (self_loops == 0)
        cout << "No states have self loops";
    else
    {
        for (auto it : states_self_loops)
        {
            cout << it << " , ";
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << endl;
    cout << endl;
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
}