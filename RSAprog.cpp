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

void encryption(string message,int e,int n,int* encResult);
void decryption(int *encResult,int elength,int d,int n,int *decResult);

int Pow2[33];


int main(int argc, char const *argv[])
{
	string message("Hello World!");
	int encResult[512];
	int decResult[512];
	int mlength = message.length();
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

	printf("plain text\n");
	printf("%s\n",message.c_str());
	
	printf("n:%d lambda:%d e:%d d:%d\n",n,lambda,e,d);
	
	encryption(message,e,n,encResult);

	printf("encryption results::\n");
	for (int i = 0; i < mlength; ++i){
		printf("%d ",encResult[i]);
	}
	printf("\n");

	decryption(encResult,message.length(),d,n,decResult);

	printf("decryption results\n");
	for (int i = 0; i < mlength; ++i){
		printf("%c",(char)decResult[i]);
	}
	printf("\n");
	
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
void encryption(string message,int e,int n,int* encResult){
	/*
		message 暗号化する文字列
		e 文字列を累乗する値
		n 文字列をmodする値
		encResult 暗号化された文字列
		PowM 文字の値を2のべき乗した値からmod nした値の配列
		enc 暗号化された値
		indexPow2 2のべき乗のインデックス
	*/
	long int PowM[33];
	long int enc;
	int indexPow2 = 0;
	int mlength = message.length();
	long int temp;

	for(int i=0;i < mlength;i++){
		enc = 1;
		PowM[0] = message[i]%n;
		indexPow2 = 0;
		for(int j = 1; j<31; j++){
			temp = PowM[j-1]*PowM[j-1];
			PowM[j] = temp%n;
		}

		while(true){
			if(Pow2[indexPow2] > e){
				break;
			}
			if((e&Pow2[indexPow2]) > 0){
				enc = enc * PowM[indexPow2];
				enc = enc %n;
			}
			indexPow2++;
		}
		// printf("enc::%d:%ld\n",i,enc);
		encResult[i] = enc;
	}
	return;
}

void decryption(int *encResult,int elength,int d,int n,int* decResult){
	long int PowD[33];
	long int dec;
	int indexPow2 = 0;
	long int temp;

	for(int i=0; i < elength;i++){
		dec = 1;
		PowD[0] = encResult[i] % n;
		indexPow2 = 0;
		for(int j = 1; j<31; j++){
			temp = PowD[j-1]*PowD[j-1];
			PowD[j] = temp%n;
		}

		while(true){
			if(Pow2[indexPow2] > d){
				break;
			}
			if((d&Pow2[indexPow2]) > 0){
				dec = dec * PowD[indexPow2];
				dec = dec%n;
			}
			indexPow2++;
		}
		// printf("dec::%d:%ld\n",i,dec);
		decResult[i] = dec;
	}
	return;
}

