#include <bitset>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class BitStream{
public:
	inline char getBit(int _id){
		int a=_id/8;
		int b=_id%8;
		int c=mBits[a];
		return (c<<b)&(0x80);
	}
	inline void addBit(char _bit){
		int a=mBitNum/8;
		int b=mBitNum%8;
		if(a<mBits.size()){
			mBits.push_back(0);
		}
		mBits.back();
		mBitNum+=1;
	}
protected:
	int mBitNum;
	vector<char> mBits;
};

//��������
class HuffmanTree{
public:
	class Node{
	public:
		inline Node():mCode(0),mFreq(0),mLeftChild(0),mRightChild(0){}

		char mChar;//Ҷ�ӽڵ���������ַ�
		char mCode;//0��1
		int mFreq;
		Node* mLeftChild;
		Node* mRightChild;
	};
public:
	HuffmanTree(const char* _str){
		//�����սڵ�
		mNodeNum=256+255;//�������Ľڵ���������
		mNodes=new Node*[mNodeNum];
		for(int i=0;i<mNodeNum;i++){
			mNodes[i]=new Node();
			mNodes[i]->mChar=i;
		}
		//ͳ���ַ�Ƶ��
		int len=strlen(_str);
		for(int i=0;i<len;i++){
			++(mNodes[_str[i]]->mFreq);
		}
		//��Ƶ��ð�������ַ�
		int innerLoops=255;
		for(int i=0;i<256;i++){
			for(int j=0;j<innerLoops;j++){
				if(mNodes[j]->mFreq>mNodes[j+1]->mFreq){
					swap(mNodes[j],mNodes[j+1]);
				}
				--innerLoops;
			}
		}
		//������������
		int leftID=0,rightID=255;//���һ���ַ�
		while(leftID<rightID){
			//���ӽڵ�
			Node* parent=mNodes[rightID+1];
			parent->mLeftChild=mNodes[leftID];
			parent->mLeftChild->mCode='0';
			parent->mRightChild=mNodes[leftID+1];
			parent->mRightChild->mCode='1';
			parent->mFreq=mNodes[leftID]->mFreq+mNodes[leftID+1]->mFreq;
			leftID+=2;
			rightID+=1;
			//���¼���Ľڵ�ִ��һ�β�������
			for(int i=leftID;i<rightID;i++){
				if(parent->mFreq<mNodes[i]->mFreq){
					memmove(&(mNodes[i+1]),&(mNodes[i]),(rightID-i)*4);
					mNodes[i]=parent;
					break;
				}
			}
		}
		//������ȱ������������
		buildEncodeTable(getRoot()->mLeftChild);
		buildEncodeTable(getRoot()->mRightChild);
		//�����ݱ���
		for(int i=0;i<len;i++){
			string encodeStr=mEncodeTable.find(_str[i])->second;
			for(int j=0;j<encodeStr.length();j++)
				mEncodeResult.push_back(encodeStr[j]);
		}
	}

	string decode(){
		vector<char> cbuf;
		Node* node=getRoot();
		for(int i=0;i<mEncodeResult.size();i++){
			if(mEncodeResult[i]=='0'){
				node=node->mLeftChild;
			}else{
				node=node->mRightChild;
			}
			if(node==0){//����Ҷ�ӽڵ�
				cbuf.push_back(node->mChar);
				node=getRoot();//���¿�ʼ
			}
		}
		cbuf.push_back('\0');
		return string(cbuf.data());
	}

	inline Node* getRoot(){
		return mNodes[mNodeNum-1];
	}
protected:
	void buildEncodeTable(Node* _node){
		mEncodeStack.push_back(_node->mCode);
		if(_node->mLeftChild)
			buildEncodeTable(_node->mLeftChild);
		if(_node->mRightChild)
			buildEncodeTable(_node->mRightChild);
		int i=0;
		char cbuf[256];
		for(;i<mEncodeStack.size();i++)
			cbuf[i]=mEncodeStack[i];
		cbuf[i+1]='\0';//�ս��
		mEncodeTable.insert(make_pair(_node->mChar,string(cbuf)));
		mEncodeStack.pop_back();
	}
protected:
	int mNodeNum;
	Node** mNodes;//ָ����ٲ���
	vector<char> mEncodeStack;
	vector<char> mEncodeResult;
	unordered_map<char,string> mEncodeTable;
};

int main(){
	const char* str=
		"Chapter Graphs surveys the most important graph processing problems  "
		"including depth-first search breadth first search minimum spanning trees and "
		"shortest paths";
	HuffmanTree* hfmTree=new HuffmanTree(str);
	cout<<hfmTree->decode()<<endl;
}