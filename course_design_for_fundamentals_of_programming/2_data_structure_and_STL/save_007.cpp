#include <iostream>
#include <cmath>
#include <iomanip>
#include <queue>           //AI说他会选择#include <vector>并using namespace std;
int main(void){
    //输入
    int n, d;
    double r = 15/2.0;     //AI建议这里直接const double r = 7.5;
    std::cin >> n >> d;    //一开始我咋写成`std::cin >> n, d;`了
    int a[100][2];         //鳄鱼坐标     //AI说用变量名crocodiles
    for(int i = 0; i < n; i++){
        std::cin >> a[i][0] >> a[i][1];
    }

    //标记有没有走过
    bool visited[100];             //要标记的是鳄鱼，而不是格子坐标纸。一开始我写的bool visited[101][101]不对
    for(int i = 0; i < n; i++){
        visited[i] = false;
    }

    //如果不踩鳄鱼、直接上岸
    int straight = 0;
    if(r + d >= 50){
        straight = 1;
        return 0;
    }

    int cur = 0;        //目前的鳄鱼编号（下标） //AI说用cur_idx或curr变量名
    //找出距离最近的鳄鱼
    double min = 80;  // 80>50√2       //AI说用min_dist_to_center，不然容易和C++的min混淆
    for(int i = 0; i < n; i++){
        int x = a[i][0];
        int y = a[i][1];
        if(min * min > x * x + y * y){
            min = sqrt(x * x + y * y);
            cur = i;
        }
    }
    std::cout << std::fixed << std::setprecision(1) << min - r << '\n';   //要输出的是鳄鱼到岛边缘距离min-r，而我一开始写成min了，错了
    //如果直接上岸，就输出yes
    if(straight){
        std::cout << "Yes";
        return 0;
    }


    //初始化队列
    std::queue<int> q;  //q存鳄鱼编号（下标）
    //q.push(cur);           //一开始我只是把最近的鳄鱼作为了队列一开始的元素，但其实应该是把所有  距离-r<d  的鳄鱼都入队
    for(int i = 0; i < n; i++){
        int x = a[i][0];
        int y = a[i][1];
        if(sqrt(x*x+y*y) - r <= d){    //一开始这里我写的<d，没考虑等于
            visited[i] = true;
            q.push(i);
        }
    }

    //看min-r是不是<d
    if(!(min - r <= d)){                //一开始这里我写的<d，没考虑等于
        std::cout << "No";
        return 0;
    }
   

    //每次把距离<d的鳄鱼入队，再把当前的出队  //记得标记visted，一开始我又忘了
    //到边界距离<d就break并输出yes
    //没有距离<d的鳄鱼就break并输出no       //这是错误的。因为q里还有下一个呢。
    //visited[cur] = true;                //这也是错误的。位置放错了。每次循环都要标记visited
    while(!q.empty()){
        cur = q.front();
        visited[cur] = true;
        int x = a[cur][0];
        int y = a[cur][1];
        if(50-x<=d || x+50<=d || 50-y<=d || y+50<=d){  //这里一开始我写的<d，没考虑等于的情况
            std::cout << "Yes";
            return 0;
        }
        int have_fish = 0;              //哈，AI说have_fish可以叫has_next或found
        for(int i = 0; i < n; i++){
            if(!visited[i]){
                int nx = a[i][0];
                int ny = a[i][1];
                if((nx-x)*(nx-x)+(ny-y)*(ny-y) <= d*d){
                    have_fish = 1;
                    q.push(i);
                }
            }
        }
        q.pop();
        if(!have_fish){
            continue;
        }
    }
    std::cout << "No";

    return 0;
}