#include <bits/stdc++.h>

//Vedansh Rashinkar
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;
class SGTree{
    vector<int>seg;
    public:
        SGTree(int n){
            seg.resize(4*n+1);
        }
        // Build Segment Tree
        void build(int ind,int low,int high,int arr[]){
            if(low==high){
                seg[ind]=arr[low];
                return;
            }
            int mid=(low+high)/2;
            build(2*ind+1,low,mid,arr);
            build(2*ind+2,mid+1,high,arr);
            seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
        }

        //Query Segment Tree
        int query(int ind,int low,int high,int l,int r){
            //No overlap
            // [l r low high]
            // [low high l r]
            if(high<l || r<low){
                return INT_MAX;
            }
            //complete overlap [l low high r]
            if(l<=low && r>=high){
                return seg[ind];
            }
            //partial overlap scene 
            int mid=(low+high)/2;
            int left=query(2*ind+1,low,mid,l,r);
            int right=query(2*ind+2,mid+1,high,l,r);
            return min(left,right);
        }
        // Point Update in Segment Tree
        void update(int ind ,int low,int high,int i,int val){
            if(low==high){
                seg[ind]=val;
                return;
            }
            int mid=(low+high)/2;
            if(i<=mid){
                update(2*ind+1,low,mid,i,val);
            }else{
                update(2*ind+2,mid+1,high,i,val);
            }
            seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
        }
};

void solve(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;++i){
        cin>>arr[i];
    }
    // int seg[4*n];
    SGTree seg(n);
    seg.build(0,0,n-1,arr);
    // build(0,0,n-1,arr,seg);
    int q;
    cin>>q;
    /*
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<query(0,0,n-1,l,r,seg)<<"\n";
    }*/
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int l,r;
            cin>>l>>r;
        
            cout<<seg.query(0,0,n-1,l,r)<<"\n";
        }else{
            int i,val;
            cin>>i>>val;
            seg.update(0,0,n-1,i,val);
            arr[i]=val;
        }
    }

}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    
    solve();
    return 0;
}