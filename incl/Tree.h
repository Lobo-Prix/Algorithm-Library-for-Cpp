#pragma once

#include "Core.h"

template<class T> struct Tree{
	Tree(int n=0):n(n),g(n){}
	void add_edge(int s,int e,T w){g[s].emplb(e,w),g[e].emplb(s,w);}
	T diameter()const{
		auto x=furthest(0,0,0).se;
		return furthest(x,x,0).fi;
	}
	pint diameterv()const{
		auto x=furthest(0,0,0).se;
		auto y=furthest(x,x,0).se;
		return {x,y};
	}
	int center(){
		auto x=furthest(0,0,0).se;
		auto z=furthest(x,x,0);
		auto [v,c,cd]=fcenter(x,x,0,z.se,z.fi);
		assert(v);
		return c;
	}
	Arr<pair<int,T>> rootize(int r)const{
		Arr<pair<int,T>> res(n,{r,inf<int>()});
		func(void,dfs,int r,int p){
			for(auto [i,w]:g[r])
				if(i!=p)
					res[i]={r,w},dfs(i,r);
		};
		dfs(r,r);
		return res;
	}
	Arr<pair<int,T>> rootize(int r,const Arr<T>& vtxw)const{
		Arr<pair<int,T>> res(n,{r,vtxw[r]});
		func(void,dfs,int r,int p){
			for(auto [i,_]:g[r])
				if(i!=p)
					res[i]={r,vtxw[i]},dfs(i,r);
		};
		dfs(r,r);
		return res;
	}

	int n;
	Arr<Arr<pair<int, T>>> g;

private:
	pint furthest(int x,int p,int d)const{
		pint r={d,x};
		for(auto[i,w]:g[x])
			if(i!=p)
				r=max(r,furthest(i,x,d+w));
		return r;
	}
	tuple<bool,int,int> fcenter(int x,int p,int d,int y,int diam){
		bool valid=x==y;
		int center=x;
		int centerd=max(d,diam-d);
		for(auto[i,w]:g[x])
			if(i!=p){
				auto[v,c,cd]=fcenter(i,x,d+w,y,diam);
				if(v){
					valid=true;
					if(max(d,diam-d)>cd)
						center=c,centerd=max(d,diam-d);
				}
			}
		return {valid,center,centerd};
	}
};