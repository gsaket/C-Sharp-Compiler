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


vector<vector<string> > vec;
vector<string> tmp;

vector<vector<string> > derivation;
vector<string> tp_;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ifstream fin("out");
	while(!fin.eof()){
		string s;
		fin>>s;
		if(s == "->"){
			;// nothing
		}else if(s == ";"){
			vec.pb(tmp);
			tmp.clear();
		}else{
			tmp.pb(s);
		}
	}

	tmp.clear();
	tmp.pb("compilation_unit");
	derivation.pb(tmp);
	rep(i,vec.size()){
		tp_.clear();
		int n=(int)(tmp.size());
		int flag=1;
		for(int j=n-1;j>=0;j--){
			if(flag == 0){
				tp_.pb(tmp[j]);
			}else{
				if(tmp[j] == vec[i][0]){
					flag = 0;
					for(int k=(int)(vec[i].size())-1;k>=1;k--){
						tp_.pb(vec[i][k]);
					}
				}else{
					tp_.pb(tmp[j]);
				}
			}
		}
		reverse(tp_.begin(),tp_.end());
		derivation.pb(tp_);
		tmp.clear();
		rep(i,tp_.size()){
			tmp.pb(tp_[i]);
		}
	}
	/*
	 *rep(i,derivation.size()){
	 *    rep(j,derivation[i].size()){
	 *        cout<<derivation[i][j]<<" ";
	 *    }
	 *    cout<<endl;
	 *}
	 */

	string html="<!DOCTYPE html>\n<html><head></head>\n";
	html += "<body><right>\n";

	rep(i,derivation.size()){
		int idx=-1;
		if(i<(int)(derivation.size())-1)
		rep(j,derivation[i].size()){
			if(derivation[i][j] == vec[i][0]){
				idx=j;
			}
		}
		rep(j,derivation[i].size()){
			if(j == idx){
				html += "<font size = \"2\" color=\"red\"> "+derivation[i][j]+" </font>\n";
			}
			html += "<font size = \"2\"> "+derivation[i][j]+" </font>\n";
		}
		html += "<br><br>\n";
	}
	html+="</right></body>\n</html>\n";
	cout<<html<<endl;
	return 0;
}

