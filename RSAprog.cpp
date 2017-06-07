#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>

#define POWNUM 32 //最大のべき数
#define MAXMESSAGE 512 //最大の文字数

using namespace std;

int gcd(int p,int q);//最大公約数
int lcm(int p,int q);//最小公倍数
void swap(int *a,int *b);//入れ替え
int makeE(int l);//eの作成
int makeD(int l,int e);//dの作成
void encryption(string message,int mlength,int e,int n,int *encResult);//暗号化
void decryption(int *encResult,int mlength,int d,int n,int *decResult);//復号化

int Pow2[POWNUM];

int main(int argc, char const *argv[]){

	string message("Hello World!!");
	int encResult[MAXMESSAGE];
	int decResult[MAXMESSAGE];
	int mlength = message.length();

	int p = 227;
	int q = 4099;
	int n = p*q;

	Pow2[0] = 1;
	for (int i = 1; i < POWNUM; i++){
		Pow2[i] = Pow2[i-1]*2;
	}

	int lambda = lcm(p-1,q-1);
	int e = makeE(lambda);
	int d = makeD(lambda,e);

	printf("plain text\n");
	printf("%s\n",message.c_str());
	
	printf("n:%d lambda:%d e:%d d:%d\n",n,lambda,e,d);
	
	encryption(message,mlength,e,n,encResult);

	printf("encryption results::\n");
	for (int i = 0; i < mlength; i++){
		printf("%d ",encResult[i]);
	}
	printf("\n");

	decryption(encResult,message.length(),d,n,decResult);

	printf("decryption results\n");
	for (int i = 0; i < mlength; i++){
		printf("%c",(char)decResult[i]);
	}
	printf("\n");
	
	return 0;
}

int gcd(int p,int q){
	int temp;
	int a = p;
	int b = q;

	if(a < b){swap(&a,&b);}

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
		if(e == 1||gcd(l,e) == 1){
			break;
		}
		e++;
	}
	return e;
}
int makeD(int l,int e){
	int d = 2;
	while(1){
		if(d == l||(e*d)%l == 1){
			break;
		}
		d++;
	}
	return d;
}
void encryption(string message,int mlength,int e,int n,int* encResult){
	long int PowM[POWNUM];// m^2k mod n (k > 1) の配列
	long int enc;//暗号化された値
	int indexPow2 = 0;//2の冪乗のインデックス

	for(int i = 0;i < mlength;i++){
		enc = 1;
		PowM[0] = message[i] % n;
		indexPow2 = 0;

		for(int j = 1; j < POWNUM-1; j++){
			PowM[j] = (PowM[j-1] * PowM[j-1]) % n;
		}

		while(Pow2[indexPow2] <= e){
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

void decryption(int *encResult,int mlength,int d,int n,int* decResult){
	long int PowD[POWNUM];
	long int dec;
	int indexPow2 = 0;

	for(int i = 0; i < mlength; i++){
		dec = 1;
		PowD[0] = encResult[i] % n;
		indexPow2 = 0;

		for(int j = 1; j < POWNUM-1; j++){
			PowD[j] = (PowD[j-1] * PowD[j-1]) % n;
		}

		while(Pow2[indexPow2] <= d){
			if((d&Pow2[indexPow2]) > 0){
				dec = dec * PowD[indexPow2];
				dec = dec % n;
			}
			indexPow2++;
		}
		// printf("dec::%d:%ld\n",i,dec);
		decResult[i] = dec;
	}
	return;
}

