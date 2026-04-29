#include <stdio.h>
#include <string.h>
//我直接就选择用C写
//这题我以为很简单，结果一直出问题，改来改去就改成现在这个样子了。实在是太丑了我的天，难以维护
int main(void){
    char s[22] = {0};   
    char have[100][22];        //已经读过的字符串
    int have_num[100] = {0};   //各个字符串读过的次数
    int have_total=1;            //已经读过的总数，用于索引，同时计数
    have_num[0] = 1;

    //清除前导空格啥的
    int c;
    while((c = getchar()) == ',' || c == '.' || c == '?' || c == '!' || c == ' ' || c == '\'' || c == '\t' || c == '\n' || c == '\r' || c == EOF){
        continue;
    }

    //初始化第一个读入的单词（字符串）  //这里代码太冗余了，和下边while一样
    //读入字符串s
    int idx = 0;
    if(!(c== ',' || c == '.' || c == '?' || c == '!' || c == ' ' || c == '\'' || c == '\t' || c == '\n' || c == '\r' || c == EOF)){
        idx = 1;
        s[0] = c;       //清楚前导空格啥的之后，c会多吃一位
    }
    while(!((c = getchar()) == ',' || c == '.' || c == '?' || c == '!' || c == ' ' || c == '\'' || c == '\t' || c == '\n' || c == '\r' || c == EOF)){
        s[idx] = c;
        idx++;
    }
    s[idx] = '\0';
    for(int i = 0; i < idx; i++){  //此时s有idx个元素
        if(s[i] <= 'Z' && s[i] >= 'A'){
            s[i] = s[i] - 'A' + 'a';
        }
    }
    if(strcmp(s, "s")==0){
        strcpy(s, "is");
    }
    else if(strcmp(s, "m")==0){
        strcpy(s, "am");
    }
    else if(strcmp(s, "re")==0){
        strcpy(s, "are");
    }
    else if(strcmp(s, "#")==0){      //额外检查是否一上来就是#，即0个单词
        printf("0\n");
        return 0;
    }
    else if(s[idx-1] == '#'){        //额外检查是否只有1个单词
        printf("1\n");
        for(int i = 0; i < idx-1; i++){
            printf("%c", s[i]);
        }
        printf(" 1");
        return 0;
    }
    strcpy(have[0], s);


    int no_minusminus = 0;
    //while读入单词，直到读入的单词为#
        //内层while读入一个单词作为字符串s，直到读入字符c为',''.''?''!'' '
    while(strcmp(s, "#") != 0){
        //给s重置
        for(int i = 0; i < 22; i++){
            s[i] = 0;
        }
        idx = 0;

        //读入字符串s
        while(!((c = getchar()) == ',' || c == '.' || c == '?' || c == '!' || c == ' ' || c == '\'' || c == '\t' || c == '\n' || c == '\r' || c == EOF)){
            s[idx] = c;
            idx++;
        }
        s[idx] = '\0';

        //如果s是空的，直接continue
        if(idx == 0){
            continue;
        }
        //处理s特殊情况
        for(int i = 0; i < idx; i++){  //此时s有idx个元素
            if(s[i] <= 'Z' && s[i] >= 'A'){
                s[i] = s[i] - 'A' + 'a';
            }
        }
        if(strcmp(s, "s")==0){
            strcpy(s, "is");
        }
        else if(strcmp(s, "m")==0){
            strcpy(s, "am");
        }
        else if(strcmp(s, "re")==0){
            strcpy(s, "are");
        }
        else if(s[idx-1] == '#'){  //检查单词后边直接#
            if(idx != 1){  //但要排除掉正常的，最后一个字符串只有#的情况
                s[idx-1] = '\0';
                no_minusminus = 1; //这样的话一会就不另外have_total--了
            }
        }

        //判断有没有读过
        int have_this = 0;
        for(int i = 0; i < have_total; i++){
            if(strcmp(s, have[i]) == 0){
                have_num[i]++;
                have_this = 1;
            }
        }
        if(!have_this){
            strcpy(have[have_total], s);
            have_num[have_total] = 1;
            have_total++;
        }

        if(no_minusminus){
            break;
        }
    } 
    if(!no_minusminus){
        have_total--;   //#也算了一个单词（字符串），所以减掉
    }
    printf("%d\n", have_total);
    //排序
    //写到这我才意识到，其实have_num和have应该写成结构体的
    for(int i = 0; i < have_total; i++){
        for(int j = 0; j < have_total - 1; j++){
            if(strcmp(have[j], have[j+1]) > 0){
                //交换have
                char temp[22] = {0};
                strcpy(temp, have[j]);
                strcpy(have[j], have[j+1]);
                strcpy(have[j+1], temp);
                //交换have_num
                int t;
                t = have_num[j];
                have_num[j] = have_num[j+1];
                have_num[j+1] = t;
            }
        }
    }
    int first = 1;
    for(int i = 0; i < have_total; i++){
        if(!first){
            printf("\n");
        }
        printf("%s %d", have[i], have_num[i]);
        first = 0;
    }


    return 0;
}