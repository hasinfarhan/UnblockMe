#include <bits/stdc++.h>
using namespace std;

int sz=6;

struct bar{
    int ori;         //0->unsettled;1->hor ; 2->ver
    int x1;
    int y1;
    int x2;
    int y2;
    char name;
};

vector<bar> gen(vector<string>state)
{
    map<char,bool>chk;
    vector<bar>data;
    map<char,bar>hold;
    vector<char>lst;

    for(int i=0;i<sz;i++)    {
        for(int j=0;j<sz;j++)    {
            char c=state[i][j];
            bar b;
            if(c!='.'&&!chk[c])    {
                chk[c]=1;
                b.ori=0;
                b.name=c;
                b.x1=j;
                b.y1=i;
                b.x2=j;
                b.y2=i;
                lst.push_back(c);
                hold[c]=b;
            }

            else if(c!='.'&&chk[c])    {
                b=hold[c];
                b.x2=j;
                b.y2=i;
                if(b.y1==b.y2)    b.ori=1;
                else if(b.x1==b.x2)    b.ori=2;
                hold[c]=b;
            }

        }
    }

    for(int i=0;i<lst.size();i++)    data.push_back(hold[lst[i]]);

    return data;


}


struct node{
    vector<string>state;
    vector<bar>data;
};


int goalx;
int goaly;
bool possibility;
string solution;

map<vector<string>,int>vis;
map<string,bool>moveVis;
map<vector<string>,string>moves;

bool check(bar b,vector<string>state,char dir)
{
        if(b.ori==1&&dir=='+')    return (b.x2<sz&&state[b.y2][b.x2]=='.');
        if(b.ori==1&&dir=='-')    return (b.x1>=0&&state[b.y1][b.x1]=='.');
        if(b.ori==2&&dir=='+')    return (b.y2<sz&&state[b.y2][b.x2]=='.');
        if(b.ori==2&&dir=='-')    return (b.y1>=0&&state[b.y1][b.x1]=='.');
}

string moveProc(string s)
{
    char prev='#';
    string soln="";
    for(int i=0;i<s.length();i++)    {
        if(s[i]!='+'&&s[i]!='-')    {
            if(s[i]!=prev)    {
                soln+=s[i];
                prev=s[i];
            }
        }
        else    soln+=s[i];
    }
    return soln;
}

int stepCount(string s)
{
    char prev='#';
    int cnt=0;
    for(int i=0;i<s.length();i++)    {
        if(s[i]!='+'&&s[i]!='-')    {
            if(s[i]!=prev)    {
                prev=s[i];
                cnt++;
            }
        }
    }
    return cnt;
}

void SOLVE(node source)
{

    possibility=false;
    solution="";

    queue<node>bfs;
    bfs.push(source);
    moves[source.state]="";
    vis[source.state]=1;
    moveVis[moves[source.state]]=1;

    while(!bfs.empty())    {
        node now=bfs.front();
        for(int i=0;i<now.data.size();i++)    {
            vector<string>nextState;
            vector<string>prev;
            vector<bar>nextData;
            string moving;
            bar c=now.data[i];
            node next;

            if(c.ori==1)    {
                //moving_right
                nextState=now.state;
                nextData=now.data;
                while(1)    {
                    c.x1++;
                    c.x2++;
                    if(!check(c,nextState,'+'))    break;
                    prev=nextState;
                    nextState[c.y1][c.x1-1]='.';
                    nextState[c.y2][c.x2]=c.name;
                    nextData[i]=c;
                    moving=moves[prev]+c.name+"+";

                    if(!vis[nextState]||(moveProc(moving).length()<=vis[nextState]&&!moveVis[moving]))    {
                        next.data=nextData;
                        next.state=nextState;
                        moves[next.state]=moving;
                        vis[next.state]=moveProc(moving).length();
                        moveVis[moving]=1;
                        bfs.push(next);
                        //goal_condition_check

                        if(c.y2==goaly&&c.x2==goalx)    {
                            if(!possibility)    {
                                possibility=true;
                                solution=moveProc(moving);
                            }
                            else if(moveProc(moving).length()<solution.length())    solution=moveProc(moving);
                        }
                    }
                }

                //moving_left
                nextState=now.state;
                nextData=now.data;
                c=now.data[i];

                while(1)    {
                    c.x1--;
                    c.x2--;
                    if(!check(c,nextState,'-'))    break;
                    prev=nextState;
                    nextState[c.y2][c.x2+1]='.';
                    nextState[c.y1][c.x1]=c.name;
                    nextData[i]=c;
                    moving=moves[prev]+c.name+"-";


                    if(!vis[nextState]||(moveProc(moving).length()<=vis[nextState]&&!moveVis[moving]))    {
                        next.data=nextData;
                        next.state=nextState;
                        moves[next.state]=moving;
                        vis[next.state]=moveProc(moving).length();
                        moveVis[moving]=1;
                        bfs.push(next);
                    }
                }

            }

            else    {
                //moving_down
                nextState=now.state;
                nextData=now.data;
                while(1)    {
                    c.y1++;
                    c.y2++;

                    if(!check(c,nextState,'+'))    break;
                    prev=nextState;
                    nextState[c.y1-1][c.x1]='.';
                    nextState[c.y2][c.x2]=c.name;
                    nextData[i]=c;
                    moving=moves[prev]+c.name+"+";

                    if(!vis[nextState]||(moveProc(moving).length()<=vis[nextState]&&!moveVis[moving]))    {
                        next.data=nextData;
                        next.state=nextState;
                        moves[next.state]=moving;
                        vis[next.state]=moveProc(moving).length();
                        moveVis[moving]=1;
                        bfs.push(next);
                    }
                }

                //moving_up
                nextState=now.state;
                nextData=now.data;
                c=now.data[i];
                while(1)    {
                    c.y1--;
                    c.y2--;

                    if(!check(c,nextState,'-'))    break;
                    prev=nextState;
                    nextState[c.y2+1][c.x2]='.';
                    nextState[c.y1][c.x1]=c.name;
                    nextData[i]=c;
                    moving=moves[prev]+c.name+"-";

                    if(!vis[nextState]||(moveProc(moving).length()<=vis[nextState]&&!moveVis[moving]))    {
                         next.data=nextData;
                        next.state=nextState;
                        moves[next.state]=moving;
                        vis[next.state]=moveProc(moving).length();
                        moveVis[moving]=1;
                        bfs.push(next);
                    }
                }
            }

        }
        bfs.pop();
    }

    if(!possibility)    cout<<"No solution exists!"<<endl<<endl;
    else    {
        cout<<"Unblocked in "<<stepCount(solution)<<" steps!"<<endl;
        cout<<"Steps: "<<solution<<endl<<endl;
    }
}

int main()
{
    while(true)    {
        string in;
        vector<string>grid;

        for(int i=0;i<sz;i++)    {
            cin>>in;
            if(in.find("A")!=string::npos)    {goalx=sz-1;goaly=i;}
            if(in=="END")    return 0;
            grid.push_back(in);
        }
        cout<<endl;

        node scene;
        scene.state=grid;
        scene.data=gen(grid);

        vis.clear();
        moves.clear();
        moveVis.clear();

        SOLVE(scene);

    }

    return 0;
}


// testcases

/*

......
......
AA...B
.....B
......
......

..EEDD
.....C
AAFIHC
..FIHB
.GGI.B
..JJJB

..EEDD
.....C
AAF.HC
..F.HB
.GG..B
.....B

..EE..
......
AA.C.B
...C.B
...C..
..FF..

.....C
.....C
AA...C
.....B
.....B
.....B
*/
