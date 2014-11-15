#include "FileStream.h"
#include "CvtUtil.h"
#include "Math.h"
using namespace std;
using namespace egg;

vector<Int32> loadOrderedDatas(const string& _fileName){
	vector<Int32> result;
	FileStream fs(_fileName,FileStream::ReadOnly);
	while(!fs.eof()){
		string line=fs.getLine(true);
		result.push_back(CvtUtil::toInt32(line));
	}
	fs.close();
	return result;
}

Int32 binarySearch(const Int32* _src, Uint32 _low, Uint32 _high, Int32 _target){
	Uint32 low=_low,hight=_high,mid=0;
	while(low<=hight){
		mid=(low+hight)/2;
		if(_src[mid]==_target){
			return mid;
		}else if(_src[mid]<_target){
			low=mid+1;
		}else{
			hight=mid-1;
		}
	}
	return -1;
}

int main(){
	Int32 target=115771;
	vector<Int32> orderedDatas=loadOrderedDatas("Ordered.txt");
	Int32 result2=binarySearch(orderedDatas.data(),0,orderedDatas.size()-1,target);

	return 0;
}