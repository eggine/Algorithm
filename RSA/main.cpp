#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//���Բ���
bool isPrime(long _num){
	int sqrtNum=sqrt(double(_num));
	if(_num==1||_num==0)
		return false;
	while(sqrtNum>=2){
		if(_num%sqrtNum==0)
			return false;
		sqrtNum--;
	}
	return true;
}

//�����������
long createRndInteger(int _digit){
	int maxNum=pow(2.0f,_digit+1)-1;
	return rand()%maxNum;
}

//�����������
long createRndPrime(int _digit){
	long ri=createRndInteger(_digit);
	while(isPrime(ri)==false){
		ri=createRndInteger(_digit);
	}
	return ri;
}

//շת���
long computeGCD(long _min,long _max){
	if(_min>_max)
		swap(_min,_max);
	long mod=_max%_min;
	if(mod==0){
		return _min;
	}else{
		return computeGCD(_min,mod);
	}
}

//��չŷ������㷨�����ax+by=1
pair<long,long> extEuclid(long _a,long _b){

}

typedef pair<long,long> SecretKey;

SecretKey generatePublicKey(){
	return make_pair(0,0);
}

SecretKey generatePrivateKey(){
	return make_pair(0,0);
}

int main(){
	int p=createRndPrime(20);
	int q=createRndPrime(20);
	long m=computeGCD(10,21);
	return 0;
}