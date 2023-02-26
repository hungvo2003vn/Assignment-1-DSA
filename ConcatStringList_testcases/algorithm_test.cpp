#include <iostream>
#include<string>
using namespace std;
string update_ans(string tmp, int n){
    
    if(n==0) return "";
    return update_ans(tmp,n-1)+tmp;
}
int close_pos(string s,int L,int cur=1){
    
    if(cur==0) return L-1;
    
    if(s[L]=='(') return close_pos(s,L+1,cur+1);
    else if(s[L]==')') return close_pos(s,L+1,cur-1);
    else return close_pos(s,L+1,cur);
}
string ex(string s, int L, int R, int tail_pos){
    if(L>R) return "";
    
    if('0'<=s[L] && s[L]<='9')
    {
        int times=s[L]-'0';
        int right=close_pos(s,L+2);
        
        string head=ex(s,L+2,right-1,right-1);
        
        if(s[tail_pos]==')') tail_pos--;
        string tail=ex(s,right+1,tail_pos,tail_pos);
        
        return update_ans(head,times) + tail;
    }
    else return s[L]+ex(s,L+1,R,tail_pos);
}
string expand(string s){
    int n=s.length();
    return ex(s,0,n-1,n-1);
}
int main()
{
    cout << expand("2(ab3(cde)x)") << "\n";
    cout << expand("2(x0(y))3(z)") << "\n";

    system("pause");
    return 0;
}

