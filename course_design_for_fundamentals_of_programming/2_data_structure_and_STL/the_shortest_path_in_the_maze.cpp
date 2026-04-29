#include <iostream>
#include  <queue>

//定义坐标的结构体，用于一会队列里放坐标数对
typedef struct{
    int x;
    int y;
}Position;


int main(void){
    //迷宫大小n*n  入口(x1, y1)  出口(x2, y2)
    int n, x1, y1, x2, y2;
    std::cin >> n >> x1 >> y1 >> x2 >> y2;
    //把数学的1到n的坐标减一，变成0到n-1的索引
    x1 -= 1;
    x2 -= 1;
    y1 -= 1;
    y2 -= 1;

    //迷宫
    int a[20][20];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cin >> a[i][j];
        }
    }

    //记录走没走过
    bool judge[20][20];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            judge[i][j] = false;
        }
    }
    judge[x1][y1] = true;

    //记录
    Position parent[20][20];

    //队列
    std::queue<Position> q;

    //计数
    int count = 0;

    //方向数组
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    //从入口探索到出口
    //探索时把下右上左放入队列，并存入记录数组
    bool fin = false;
    

    q.push({x1, y1});
    
    //AI说我没有处理无解的情况，会死循环。确实。
    while(!fin){
        int nx, ny;
        Position cur = q.front();
        for(int i = 0; i < 4; i++){
            nx = cur.x + dx[i];
            ny = cur.y + dy[i];            //↓  气笑了，这里一开始ny < n写成ny > n了，我还找了半天
            if(nx >= 0 && nx < n && ny >= 0 && ny < n && a[nx][ny] == 0 && judge[nx][ny] == false){
                judge[nx][ny] = true;      //依旧气笑了，这里一开始我写成了==true，还是找了半天错误在哪
                if(nx == x2 && ny == y2){
                    parent[nx][ny] = {cur.x, cur.y};
                    fin = true;
                    break;
                }
                else{
                    q.push({nx, ny});
                    parent[nx][ny] = {cur.x, cur.y};
                }
            }
        }
        q.pop();
    }

    //这里我先计数了一遍，一会再同样的过程输出一遍。        //哦AI说，第一个whil用于计数，第二个while用于存储倒序的result。这俩完全可以同一个while同时进行
    //因为题目要求先输出count再输出最短路径
    //但我想不到别的计数方法了
    int i = x2, j = y2;
    while(i != x1 || j != y1){
        int temp_i = i, temp_j = j;
        i = parent[temp_i][temp_j].x;
        j = parent[temp_i][temp_j].y;
        count++;
    }

    //输出parent
    //但是要把0到n-1的索引加一，变成数学的1到n的坐标
    //另外题目要求输出最短路径时，要从入口到出口，而parent存的是上一步的
    //所以这里我选择再开一个，来输出
    Position result[400];
    int idx = count;
    i = x2;
    j = y2;
    while(i != x1 || j != y1){
        result[idx].x = i+1;
        result[idx].y = j+1;
        idx--;

        int temp_i = i, temp_j = j;
        i = parent[temp_i][temp_j].x;
        j = parent[temp_i][temp_j].y;
    }
    result[idx].x = i+1;
    result[idx].y = j+1;

    //开始输出
    std::cout << count << '\n';
    for(int i = 0; i < count+1; i++){
        std::cout << '(' << result[i].x << ',' << result[i].y << ')';
    }
    

    return 0;
}