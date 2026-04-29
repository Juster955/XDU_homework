#include <iostream>
#include <stack>
#include <string>

//返回  a x b
int opt(int a, int b, char x){       //这里自己写啥一定要记住啊，一开始我当成(int a, char x, int b)了就错了
    if(x == '-'){
        return (a - b);
    }
    else if(x == '+'){
        return (a + b);
    }
    else if(x == '*'){
        return (a * b);
    }
    else{
        std::cout << "操作符不是加减乘哦";      //我写的这几个检查的cout啊，是一个也没用上啊，我天
        return -1;
    }
}


int main(void){
    std::stack<char> a;    //栈A暂存运算符       //AI建议这个ab可以改成更易于理解的变量名
    std::stack<int> b;     //栈B暂存数字

    int N;
    std::cin >> N;                                        //一开始这里的N我用的是n，就和下边重复了。虽然问题不大，有各自的作用与，但是不易于阅读

    int first = 1;   //AI建议起个is_first之类的名字，更易于理解
    for(int idx = 0; idx < N; idx++){                     //一开始这里的idx我用的是i，就和下边重复了。虽然问题不大，有各自的作用域，但是不易于阅读
        std::string s;
        std::cin >> s;
        int l = s.length();        //s的长度
        
        //开始运算
        for(int i = 0; i < l; i++){        //四种可能：数字   '+''-''*'   '('   ')'
            if(s[i]>= '0' && s[i] <= '9'){
                //结束的时候s[i]是最后一位数字
                int n = 0;
                while(s[i] >= '0' && s[i] <= '9'){          //一开始这里没有用while，只能处理一位数字，就直接s[i]-='0'。改成现在这样就好了，可以处理多位数字了
                    n *= 10;
                    n += s[i]-'0';
                    i++;                          //AI说for循环不建议内部改i，很容易出错。可以换成while
                }
                i--;                                        //外层for循环自带一个i++，所以这里i--了一下
                b.push(n);       //这里我是后改的，所以我忘了b.push()，然后调试的时候发现了这一点，加了个b.push()就好了
            }
            else if(s[i] == '+' || s[i] == '-' || s[i] == '*'){
                //如果 不是 A空或s[i]优先于a栈顶
                while(!(a.empty() || (!a.empty() && (s[i] == '*' || a.top() == '(')))){       //这个判断条件，我显然写的太复杂了，不易于理解，但是就只能先这样了
                    int p = b.top();      //AI建议这个p q y可以换成left right op，更易于理解
                    b.pop();
                    int q = b.top();
                    b.pop();
                    char y = a.top();
                    a.pop();

                    b.push(opt(q, p, y));
                }
                a.push(s[i]);

            }
            else if(s[i] == '('){
                a.push(s[i]);
            }
            else if(s[i] == ')'){
                while(a.top() != '('){
                    int p = b.top();
                    b.pop();
                    int q = b.top();
                    b.pop();
                    char y = a.top();
                    a.pop();

                    b.push(opt(q, p, y));    //有顺序的，pqy不行，qpy才行
                }
                a.pop();                   //处理完()之间的部分后，记得要把'('弹出
            }
            else{
                std::cout << "表达式中不是+-*()哦";
            }
        }

        while(!a.empty()){
            int p = b.top();
            b.pop();
            int q = b.top();
            b.pop();
            char y = a.top();
            a.pop();

            b.push(opt(q, p, y));
        }

        if(!first){
            std::cout << "\n";
        }
        if(!b.empty()){
            std::cout << b.top();
            b.pop();
        }
        else{
            std::cout << "b为空哦";
        }
        first = 0;
    }

    return 0;
}