#include <bits/stdc++.h>
using namespace std;
#define MAXS 1000
#define MAXC 93
#define MAXW 500

class AhoCorasick
{
private:
    vector<string> arr;
    string text;
    int g[MAXS][MAXC];
    int f[MAXS];
    bitset<MAXW> out[MAXS];
    void initialize(vector<string> arr, string text)
    {
        this->arr = arr;
        this->text = text;
        memset(g,-1,sizeof g);
        memset(f,0,sizeof f);
    }
    void buildMachine()
    {
        int state = 0,currState = 0,index = 0;
        string str;
        ///Building a trie, each new node gets the next number as node-name.
        for(int i = 0; i<arr.size(); i++)
        {
            str = arr[i];
            currState = 0;

            for(int j = 0; j<str.size(); j++)
            {
                index = str[j] - 33;
                if(g[currState][index] == -1)
                {
                    g[currState][index] = ++state;
                }
                currState = g[currState][index];
            }
            out[currState].set(i);
            ///stores whether i'th indexed string of arr, ends at state 'currState' or not. Thus adding the string to output by using 1 bit, hhh very memory efficient.
        }
        ///Failure function
        queue<int>q;
        int s,fail;
        for(int i = 0; i<MAXC; i++)
        {
            if(g[0][i] != -1)
            {
                f[g[0][i]] = 0; ///here, depth is 1
                q.push(g[0][i]);
            }
            else
            {
                g[0][i] = 0; ///Necessary in failure alg below, non-existing char back to state 0. To stop infinite loop at line 68.
            }
        }
        while(! q.empty())
        {
            s = q.front();
            q.pop();
            for(int i= 0; i<MAXC; i++)
            {
                if(g[s][i] != -1)
                {
                    q.push(g[s][i]);
                    fail = f[s]; ///here is the perfect place to calculate failure of g[s][i],cuz here 'state:s' is (depth-1) state of 'state:g[s][i]'.
                    while(g[fail][i] == -1)
                    {
                        fail = f[fail];
                    }
                    fail = g[fail][i];
                    f[g[s][i]] = fail;
                    out[g[s][i]] |= out[fail]; ///merging output of the node & it's failure node.
                    ///Read the paper of aho-corasick,published in 1975.
                }
            }
        }
    }
    int nextState(int s, char ch)
    {
        int index = ch - 33;
        while(g[s][index] == -1)   ///If non-existing state, use failure function to support automaton.
        {
            s = f[s];
        }
        return g[s][index];
    }
public:
    AhoCorasick() {}
    void search(vector<string> arr, string text)
    {
        initialize(arr,text);
        buildMachine();
        int state = 0;
        for(int i = 0; i<text.size(); i++)
        {
            state = nextState(state,text[i]); /// traverse the trie state/node for the text
            if(out[state].count() > 0) /// if the state has at least one output
            {
                for(int j = 0; j<arr.size(); j++) ///For finding position of search strings.
                {
                    if(out[state].test(j)) /// if j'th string is in the output of state, means a match is found.
                    {
                        cout<<arr[j]<<" IS MATCHED AT POSITION: "<<i-arr[j].size()+1<<endl;
                    }
                }
            }
        }
    }
};

int main()
{
    vector<string> arr = {"he", "she", "hers", "his","!@#"};
    string text = "ahishers!@#";
    AhoCorasick alg;
    alg.search(arr,text);
    return 0;
}

