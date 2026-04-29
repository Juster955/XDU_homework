#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
图像二值化
图像n*n，每个元素是[0, L)范围
邻域定义为Neighbor(i, j, r)   0<= x, y < n && |x-i| <= r && |y-j| <= r 
邻域平均值 <= 阈值   0
邻域平均值 >= 阈值   1

命令行参数给出gray路径、mono路径、r、t
gray2mono 【gray路径】 【mono路径】 -r=3 -t=128

我的实际操作：在powershell进入项目根目录XDU_homework
输入下面两个命令
gcc .\course_design_for_fundamentals_of_programming\1_image_binarization\gray2mono.c -o .\course_design_for_fundamentals_of_programming\1_image_binarization\gray2mono.exe
.\course_design_for_fundamentals_of_programming\1_image_binarization\gray2mono .\course_design_for_fundamentals_of_programming\1_image_binarization\gray.bmp .\course_design_for_fundamentals_of_programming\1_image_binarization\mono.bmp -r=3 -t=128
*/

/*
gray.bmp是我在网上尝试搜索后，从https://gitcode.com/open-source-toolkit/083c1/blob/main/lena.zip下载的
*/

/*
搜索得知.bmp文件：
文件头到位图的偏移量offBits         偏移量000Ah
位图宽度width                      偏移量0012h
位图高度height                     偏移量0016h
*/
int main(int argc, char* argv[]){          //这里我直接就main完成所有过程了，没有单独写其他函数
    //这里对齐的注释是大体步骤
                                           //这里对齐的注释是一些说明
                                                          //这里对齐的注释是一些疑惑

    //创建文件指针并检查
    FILE *fGray = fopen(argv[1], "rb");
    FILE *fMono = fopen(argv[2], "rb+");
    if(fGray==NULL || fMono==NULL){
        printf("文件指针出错");
        exit(-1);
    }





    //创建二维数组grayMat和monoMat并读取n
    int grayMat[256][256];                  //我事先看了一下从网上下载的gray.bmp，是256*256的，所以这里我给了256个的二维数组
    int monoMat[256][256];
    
    fseek(fGray, 0x0012, SEEK_SET);                      //这里我在网上查的偏移量是0012h。h是干嘛的？是标明是十六进制吗？另外这里该怎么处理十六进制，直接写0x吗？
    int n;
    fread(&n, 4, 1, fGray);                              //这里4和1能直接这么写吗
    
    fseek(fGray, 0x0016, SEEK_SET);                      //同一个fGray能反复的fseek吗
    int verificatioN;                       //验证一下宽和高是否一致，即gray.bmp是否是正方形
    fread(&verificatioN, 4, 1, fGray);
    if(abs(verificatioN) != n){             //搜索得知.bmp文件头的宽度有可能是负数，所以这里使用绝对值进行比较
        printf("读取错误，宽和高不一致");
        exit(-1);
    }

    fseek(fGray, 0, SEEK_SET);                           //需要让fGray回到文件开头吗





    //对fGray跳转到指定位置，读取，并复制到grayMat
    fseek(fGray, 0x000A, SEEK_SET);          //先获取要跳转的偏移量
    char offSet[10];                                     //这里offSet给多大好呢，先给个10吧
    fread(offSet, 4, 1, fGray);     
                                             
    int idx = 0;                            //把十六进制的offSet转成十进制
    char offSetHexStr[20];                  //搜索得知有个好用的strtol
    for(int i = 0; i < 10; i++){
        offSetHexStr[idx] = offSet[i]%10;                 //这里先把offSet由2个数字一组的十六进制的char转换为从尾到头的十六进制字符串
        idx++;                                            //但是这里如果offSet含A~F的话，就不能这么直接%10和/10处理了
        offSetHexStr[idx] = offSet[i]/10;                 //但我想不到别的解决方案了，就只能先这样了
        idx++;                                            //测试的时候我发现，我的gray.bmp得到的offSet是0x0454，所以这里暂时没有问题
    }
    int len = strlen(offSetHexStr);
    for(int i = 0; i < len/2; i++){
        char temp = offSetHexStr[i];
        offSetHexStr[i] = offSetHexStr[len-i-1];           //这里再把从尾到头的offSetHexStr变成从头到尾的，即调换一下顺序，方便后续使用offSetHexStr
        offSetHexStr[len-i-1] = temp;
    }

    for(int i = 0; i < len; i++){                          //找了半天bug，strtol一直有问题。原来是这里要把offSetHexStr[i]从4变成'4'
        offSetHexStr[i] += '0';
    }

    char *endptr; 
    long int offSetDecimal = strtol(offSetHexStr, &endptr, 16);
    if(*endptr != '\0'){
        printf("转换失败");
        exit(-1);
    }

    fseek(fGray, offSetDecimal, SEEK_SET);   //再跳转到图像二维数组的主体部分

    int nowOffSet;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            nowOffSet = offSetDecimal + (i * n + j);       //我十分怀疑这里某个地方写错了。因为最终得到的mono.bmp几乎是纯黑的，只有左下角有一些白色。不知道问题出在哪里。
            fseek(fGray, nowOffSet, SEEK_SET);             //在网上搜索的时候，bmp格式越搜越复杂，最后放弃了。还是妥协了，问了AI。
            fread(&(grayMat[i][j]), 1, 1, fGray);
        }
    }

    
    
    
    //操作grayMat二值化，得到monoMat
    int r, t;                                  //r来自argv[3]    t来自argv[4]
    sscanf(argv[3], "-r=%d", &r);                           //这里这么写格式化，是不是要求有点太高了啊，必须得是-r=%d才行，--r或者有空格就不行
    sscanf(argv[4], "-t=%d", &t);  
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int sum = 0;
            int count = 0;                                  //四层循环吗，那很慢了
            for(int x = i-r; x <= i+r; x++){
                for(int y = j-r; y <= j+r; y++){
                    if(x >= 0 && x < n && y >= 0 && y < n){
                        sum += grayMat[x][y];
                        count++;
                    }
                }
            }
            if(sum * 1.0 / count <= t){
                monoMat[i][j] = 0;
            }
            else{
                monoMat[i][j] = 1;
            }
        }
    }


    
    
    //对fMono跳转到指定位置，并从grayMat复制过来，写入
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            nowOffSet = offSetDecimal + (i * n + j);
            fseek(fMono, nowOffSet, SEEK_SET);
            fwrite(&monoMat[i][j], 1, 1, fMono);
        }
    }


    //用完了，fclose
    fclose(fGray);
    fclose(fMono);

    return 0;
}

