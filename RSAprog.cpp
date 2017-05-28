#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int gcd(int p,int q);//最大公約数
int lcm(int p,int q);//最小公倍数
void swap(int *a,int *b);//入れ替え

int main(int argc, char const *argv[])
{
	printf("%d\n",gcd(12,24));
	return 0;
}

int gcd(int p,int q){
	int temp;
	int a = p;
	int b = q;

	if(a<b){swap(&a,&b);}

	while(temp!=0){
		a = b;
		b = temp;
		temp = a % b;
	}
	return b;
}

int lcm(int p,int q){

}
void swap(int *a,int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}
