#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<double,double>
#define X first
#define Y second
#define rep(i,a) for(int i=0;i<(int)a;i++)
#define repp(i,a,b) for(int i=(int)a;i<(int)b;i++)
#define fill(a,x) memset(a,x,sizeof(a))
#define foreach( gg, itit) for( typeof(gg.begin()) itit=gg.begin();itit!=gg.end();itit++ )
#define mp make_pair
#define pb push_back
#define all(s) s.begin(),s.end()
#define present(c,x) ((c).find(x) != (c).end())
const int mod  = 1e9+7;
const int N = 1e6+10;
const ll INF = 1e18;
#define E5 100005

#define ld long double
//#define double long double
const ld EPS=1e-12;

vector<string> vec;

int main(){
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	ifstream fin("input.y");
	int cnt=0;
	string head="";
	string text="";
	int hflag=0;
	while(!fin.eof()){
		string s;
		fin>>s;
		if(head == ""){
			head = s;
			hflag = 1;
		}else if(!(s == "|" || s == ";" || s == ":")){
			if(s[0] != '\'')
			vec.pb(s);
			else{
				string s_="\\";
				rep(i,2)s_+=s[i];
				s_+="\\";
				s_+=s[2];
				vec.pb(s_);
			}
		}
		if(s == "|" || s == ";"){
			text += " { ";
			text += "T.clear();";
			text += "T.pb(\""+head+"\");";
			rep(i,vec.size())text += "T.pb(\""+vec[i]+"\");";
			text += "R.pb(T);";
			text += " }";
			text += "\n\t ";
			vec.clear();
		}
		if(s == ";"){
			head = "";
		}
		//text += " ";
		text += s;
		if(hflag == 1){
			hflag = 0;
			text += "\n\t ";
		}else{
			if(!(s == ":" || s == ";" || s == "|")){
				text += " ";
			}
		}
		if(s == ":" || s == "|"){
			text += " ";
		}
		if(s == ";"){
			text += "\n";
		}
		cnt++;
		//if(cnt == 20)break;
	}
	cout<<text<<endl;
	return 0;
}

