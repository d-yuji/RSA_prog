#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>

using namespace std;

int gcd(int p,int q);//最大公約数
int lcm(int p,int q);//最小公倍数
void swap(int *a,int *b);//入れ替え
int makeE(int l);
int makeD(int l,int e);

int main(int argc, char const *argv[])
{
	string str("Hello_world");
	int p = 227;
	int q = 4099;
	int n = p*q;
	int lambda = lcm(p-1,q-1);
	int e = makeE(lambda);
	int d = makeD(lambda,e);

	printf("%d %d %d %d\n",n,lambda,e,d);
	return 0;
}

int gcd(int p,int q){
	int temp;
	int a = p;
	int b = q;

	if(a<b){swap(&a,&b);}
	temp = a % b;
	while(temp!=0){
		a = b;
		b = temp;
		temp = a % b;
	}
	return b;
}

int lcm(int p,int q){
	return p*q/gcd(p,q);
}
void swap(int *a,int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}

int makeE(int l){
	int e = 2;
	while(1){
		if(e==1||gcd(l,e)==1){
			break;
		}
		e++;
	}
	return e;
}
int makeD(int l,int e){
	int d = 2;
	while(1){
		if(d==l||(e*d)%l == 1){
			break;
		}
		d++;
	}
	return d;
}