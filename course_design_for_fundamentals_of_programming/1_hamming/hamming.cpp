#include <stdio.h>

//题目约定好了，数据位有7个，校验位有4个，所以本程序很多地方是硬编码的7和4，移植性不高
int main(void){
	unsigned int n;
	scanf("%u", &n);
	int s[4]={0};

	for(int s_idx = 0; s_idx < 4; s_idx++){
		int first = 1;
		for(int i = 1; i <= 11; i++){
			if(i >> s_idx & 1 == 1){
				if(first){
					s[s_idx] = ((n >> (i-1)) & 1);
				}
				else{
					s[s_idx] = (((n >> (i-1)) & 1) ^ s[s_idx]);
				}
				first = 0;
			}
		}
	}

	int s_d = 0;
	for(int s_idx = 0; s_idx < 4; s_idx++){
		for(int i = 0; i < s_idx; i++){
			s[s_idx] <<= 1;   //*2
		}
		s_d += s[s_idx];
	}

	for(int i = 11; i >= 1; i--){
		if(!(i==1 || i==2 || i==4 || i==8)){
			if(i != s_d){
				printf("%d", ((n >> (i-1)) & 1));
			}
			else{
				if(((n >> (i-1)) & 1) == 1){
					printf("0");
				}                                    //我试了一下直接~   但是会出现一个-1   推测是补码之类的问题
				else{                                //所以这里是手动写的取反
					printf("1");
				}                                    //AI说这里其实可以直接^1，就可以特定位取反了      哦当然1得先左移右移一下
			}
		}

	}

	return 0;
}