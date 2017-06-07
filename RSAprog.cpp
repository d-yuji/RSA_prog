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

void encryption();
void decryption();

int Pow2[33];


int main(int argc, char const *argv[])
{
	string str("Hello_world");
	int p = 227;
	int q = 4099;
	int n = p*q;

	Pow2[0] = 1;
	for (int i = 1; i < 31; ++i){
		Pow2[i] = Pow2[i-1]*2;
	}

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
void encryption(string message,int e,int n,string result){
/*
	message 暗号化する文字列
	e 文字列を累乗する値
	n 文字列をmodする値
	result 暗号化された文字列
	PowM 文字の値を2のべき乗した値からmod nした値の配列
	enc 暗号化された値
	indexPow2 2のべき乗のインデックス
*/
	int PowM[33];
	int enc;
	int indexPow2 = 0;

	for(int i=0;i<message.length();i++){
		enc = 1;
		PowM[0] = 1;
		PowM[1] = message[i];
		indexPow2 = 0;

		for(int j = 2; j<31; j++){
			PowM[j] = (PowM[j-1]*PowM[j-1])%n;
		}

		while(true){
			if(Pow2[indexPow2] > e){
				break;
			}
			if(e&Pow2[indexPow2] > 0){
				enc = enc * PowM[indexPow2];
				if(enc > n){
					enc = enc %n;
				}
			}
			indexPow2++;
		}
		result[i] = enc;

	}
}


