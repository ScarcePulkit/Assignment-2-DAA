/**
 * @file main2.cpp
 * @brief This file contains the implementation of the Least Segment Squares algorithm
 * @details This file contains the implementation of the Least Segment Squares algorithm
 *         for the problem of finding the optimal cost of the line fitting
 *        problem.
 * 
 * 
*/
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define in(n) int n; cin>>n;
#define w(x) int x; cin>>x; while(x--)
#define int long long
#define str(s) string s; cin>>s;
#define sz(x) static_cast<int>(x.size())
#define endl "\n"
#define dbg(x) cerr << #x << "->" << x << "\n"
#define prnt(x) cerr<<#x<<'{';for(auto T:x)cerr<<T<<' ';cerr<<"}\n";
#define prntp(x) cerr<<#x<<'{';for(auto T:x)cerr<<T.first<<'-'<<T.second<<' ';cerr<<"}\n";
const int mod = 1000000007;
#define INF numeric_limits<double>::infinity()
const int MAX=10000;
#define FAST cin.tie(0)->sync_with_stdio(0);
 
typedef tree <int, null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update>
        pbds;
 
 
 /**
  * 
  * @brief This is the point structure which contains the x and y coordinate of the point
  * @param x This is the x coordinate of the point
  * @param y This is the y coordinate of the point
  * 
 */
struct point{
    double x,y;
};
 
    /**
    * 
    * @brief This is the compare function which is used to sort the points according to the x coordinate
    * @param a This is the first point
    * @param b This is the second point
    * @return bool This returns true if the x coordinate of the first point is greater than the second point
    * 
    */
static bool cmp(point &a,point &b){
    return a.x>b.x;
}
 
 
/**
 * @brief This is the main function which is used to calculate the optimal cost of the line fitting problem
 * @param points This is the vector of points which contains the x and y coordinate of the points
 * @param n This is the number of points
 * @param c This is the constant which is used to calculate the cost
 * @return double This returns the optimal cost of the line fitting problem
 * 
 */ 
void calculate_cost(vector<vector<double>>& e,vector<double>&dp,vector<double>&segments,int n,int c){
    dp[0]=0;
    for(int j=1;j<=n;j++){
        double val=INF;
        int k=0;
        for(int i=1;i<=j;i++){
            if(e[i][j]+dp[i-1]<val){
                val=e[i][j]+dp[i-1];
                k=i;
            }
        }
        dp[j]=val+c;
        segments[j]=k;
    }
}
 
 
/**
 * @brief This is the function which is used to print the optimal cost of the line fitting problem
 * @param dp This is the vector which contains the optimal cost of the line fitting problem
 * @param n This is the number of points
 * @return void This returns nothing
 * 
 * 
*/
void print_cost(vector<double>&dp,int n){
    cout<<"The optimal cost is: ";
    cout<<dp[n]<<endl;
}
 
/**
 * @brief This is the function which is used to print the optimal solution of the line fitting problem
 * @param slope This is the vector which contains the slope of the line
 * @param intercept This is the vector which contains the intercept of the line
 * @param s This is the stack which contains the optimal solution of the line fitting problem
 * @return void This returns nothing
*/
void print_solution(vector<vector<double>>& slope,vector<vector<double>> &intercept,stack<int>&s){
    printf("\n Optimal Solution is:\n");
    int i ; int j;
    while(!s.empty()){
        i=s.top();
        s.pop();
        j=s.top();
        s.pop();
        cout<<intercept[i][j]<<" "<<slope[i][j];
        // cout<<"The line is y="<<intercept[i][j]<<"x+ "<<slope[i][j];
        // cout<<" from points "<<i<<" to "<<j<<endl;
    }
}
 
 
/**
 * @brief This is the function which is used to calculate the slope and intercept of the line
 * @param points This is the vector which contains the x and y coordinate of the points
 * @param slope This is the vector which contains the slope of the line
 * @param intercept This is the vector which contains the intercept of the line
 * @param e This is the vector which contains the error of the line
 * @param n This is the number of points
 * @param sumX This is the vector which contains the sum of the x coordinate of the points
 * @param sumY This is the vector which contains the sum of the y coordinate of the points
 * @param sumXY This is the vector which contains the sum of the product of the x and y coordinate of the points
 * @param sumXX This is the vector which contains the sum of the square of the x coordinate of the points
 * @return void This returns nothing
 * 
*/
void calculate_slope_intercept(vector<point>points,vector<vector<double>>& slope,vector<vector<double>> &intercept,vector<vector<double>>& e,int n,vector<double>&sumX,vector<double>&sumY,vector<double>&sumXY,vector<double>&sumXX){
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            double x=sumX[j]-sumX[i-1];
            double y=sumY[j]-sumY[i-1];
            double xy=sumXY[j]-sumXY[i-1];
            double xx=sumXX[j]-sumXX[i-1];
            double m=(j-i+1)*xy-x*y;
            double b=xx*y-x*xy;
            m/=((j-i+1)*xx-x*x);
            b/=((j-i+1)*xx-x*x);
            slope[i][j]=m;
            intercept[i][j]=b;
            double val=0;
            for(int k=i;k<=j;k++){
                val+=(points[k].y-m*points[k].x-b)*(points[k].y-m*points[k].x-b);
            }
            e[i][j]=val;
        }
    }
}
 
 
/**
 * @brief This is the function which is used to calculate the sum of the x,y,xy and xx coordinate of the points
 * @param points This is the vector which contains the x and y coordinate of the points
 * @param sumX This is the vector which contains the sum of the x coordinate of the points
 * @param sumY This is the vector which contains the sum of the y coordinate of the points
 * @param sumXY This is the vector which contains the sum of the product of the x and y coordinate of the points
 * @param sumXX This is the vector which contains the sum of the square of the x coordinate of the points
 * @param n This is the number of points
 * @return void This returns nothing
*/
void preparing_the_recipe(vector<point>points,vector<double>&sumX,vector<double>&sumY,vector<double>&sumXY,vector<double>&sumXX,int n){
    sumX[0]=0;
    sumY[0]=0;
    sumXY[0]=0;
    sumXX[0]=0;
    for(int i=1;i<=n;i++){
        sumX[i]=sumX[i-1]+points[i].x;
        sumY[i]=sumY[i-1]+points[i].y;
        sumXY[i]=sumXY[i-1]+points[i].x*points[i].y;
        sumXX[i]=sumXX[i-1]+points[i].x*points[i].x;
    }
}
 
 
/**
 * @brief This is the main function
 * @return int This returns 0
 * 
*/
int32_t main(){
 
    //taking input for the problem
    freopen("input.txt","r",stdin);
    freopen("output.txt","w+",stdout);
    in(n);
    in(c);
    vector<point>points(n+1);
    for(int i=1;i<=n;i++){
        double x,y;
        cin>>x>>y;
        points[i].x=x;
        points[i].y=y;
    }
    vector<double> sumX(n+1),sumY(n+1),sumXY(n+1),sumXX(n+1);
 
    //sort and reverse the points vector according to the x coordinate
    sort(points.begin(),points.end(),cmp);
    reverse(points.begin(),points.end());
 
    // calculating the sum of x,y,xy and x^2
    preparing_the_recipe(points,sumX,sumY,sumXY,sumXX,n);
    
    
    // double e[n+1][n+1],slope[n+1][n+1],intercept[n+1][n+1];
    vector<vector<double>> e( n+1 , vector<double> (n+1,0.0));
    vector<vector<double>> slope( n+1 , vector<double> (n+1));
    vector<vector<double>> intercept( n+1 , vector<double> (n+1));
 
 
    // memset(e,0.0,sizeof(e));
 
    // calculating the slope and intercept for the line connecting pi,.. pj
    calculate_slope_intercept(points,slope,intercept,e,n,sumX,sumY,sumXY,sumXX);
 
    
    // calculating the optimal cost
    vector<double>dp(n+1,INT_MAX),segments(n+1); // make dp array and segments array
    calculate_cost(e,dp,segments,n,c);
    
    // printing the optimal cost
    print_cost(dp,n);
    
    stack<int>s;
    int j,i=n;
    for(i;i>0;i=j-1){
        j=segments[i];
        s.push(i),s.push(j);
    }
 
    // printing the optimal solution
    print_solution(slope,intercept,s);
    return 0;
 
}
 