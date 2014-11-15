#include "FileStream.h"
#include "Random.h"
#include "Timer.h"
using namespace std;
using namespace egg;

vector<Int32> loadUnorderedDatas(const string& _fileName){
	vector<Int32> result;
	FileStream fs(_fileName,FileStream::ReadOnly);
	while(!fs.eof()){
		string line=fs.getLine(true);
		result.push_back(StringUtil::parseString<Uint32>(line));
	}
	fs.close();
	return result;
}

void saveOrderedDatas(const string& _fileName,const vector<Int32>& _orderedData){
	FileStream fs(_fileName,FileStream::WriteOnly);
	for(Uint32 i=0;i<_orderedData.size();i++){
		string& str=StringUtil::toString(_orderedData[i])+"\n";
		fs.write(str.c_str(),str.length());
	}
	fs.close();
}

vector<Int32> bubbleSort(const Int32* _src,Uint32 _size){
	//复制待排序数据到目标数组
	vector<Int32> dest(_size);
	for(Uint32 i=0;i<_size;i++)
		dest[i]=_src[i];
	//在目标数组执行冒泡排序
	if(_size>1){
		Uint32 times=_size-1;
		while(times>0){
			for(Uint32 i=0;i<times;i++){
				if(dest[i]>dest[i+1]){
					swap(dest[i],dest[i+1]);
				}
			}
			times--;
		}
	}
	return dest;
}

vector<Int32> insertSort(const Int32* _src,Uint32 _size){
	//复制待排序数据到目标数组
	vector<Int32> dest(_size);
	for(Uint32 i=0;i<_size;i++)
		dest[i]=_src[i];
	//在目标数组执行冒泡排序
	if(_size>1){
		Uint32 times=_size-1;
		while(times>0){
			for(Uint32 i=0;i<times;i++){
				if(dest[i]>dest[i+1]){
					swap(dest[i],dest[i+1]);
				}
			}
			times--;
		}
	}
	return dest;
}

vector<Int32> mergeSort(const Int32* _src,Uint32 _size){
	vector<Int32> temp;
	if(_size<10){
		//对小于10个元素的分组直接冒泡排序
		temp=bubbleSort(_src,_size);
	}else{
		//待排序数据分2组
		Uint32 md=_size*0.5;
		vector<Int32> ordered1=mergeSort(&_src[0],md);
		vector<Int32> ordered2=mergeSort(&_src[md],_size-md);
		Uint32 id1=0,id2=0,tempSize=ordered1.size()+ordered2.size();
		temp.reserve(tempSize);
		//合并排序好的2组数据
		for(Uint32 i=0;i<tempSize;i++){
			if(id1==ordered1.size()){
				temp.push_back(ordered2[id2]);
				id2++;
			}else if(id2==ordered2.size()){
				temp.push_back(ordered1[id1]);
				id1++;
			}else if(ordered1[id1]<ordered2[id2]){
				temp.push_back(ordered1[id1]);
				id1++;
			}else{
				temp.push_back(ordered2[id2]);
				id2++;
			}
		}
	}
	return temp;
}

void heapSort(const vector<Int32>& _in,vector<Int32>& _out){

}

int main(){
	vector<Int32> unorderedDatas=loadUnorderedDatas("largeW.txt");
	//vector<Int32> bubbleResult=bubbleSort(unorderedDatas.data(),unorderedDatas.size());
	//saveOrderedDatas("largeW_bubble.txt",bubbleResult);
	//vector<Int32> mergeResult=mergeSort(unorderedDatas.data(),unorderedDatas.size());
	//saveOrderedDatas("largeW_merge.txt",mergeResult);

	Timer ticker;
	Random rand;
	const Uint32 testNum=1000000;
	Int32* testData=new Int32[testNum];
	for(Uint32 i=0;i<testNum;i++){
		testData[i]=rand.iRand(0,testNum);
	}
	Float64 start=ticker.getSeconds();
	//vector<Int32> bubbleResult=bubbleSort(testData,testNum);
	vector<Int32> mergeResult=mergeSort(unorderedDatas.data(),unorderedDatas.size());
	Float64 elapse=ticker.getSeconds()-start;
	cout<<elapse<<endl;

	saveOrderedDatas("largeW_merge.txt",mergeResult);

	return 0;
}