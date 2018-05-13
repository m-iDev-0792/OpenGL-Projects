#include <iostream>
#include <vector>
#include <stack>
using namespace std;
//churchman  barbarian
/*enum ops{
	b1ToR=-9,
	c1ToR=-7,
	c1b1ToR=-5,
	c2ToR=-3,
	b2ToR=-1,
	c1b1ToL=5,
	c2ToL=3,
	b2ToL=1,
	c1ToL=7,
	b1ToL=9
};*/
#define b1ToR -9
#define	c1ToR -7
#define	c1b1ToR -5
#define	c2ToR -3
#define	b2ToR -1
#define	c1b1ToL 5
#define	c2ToL 3
#define	b2ToL 1
#define	c1ToL 7
#define	b1ToL 9
enum boatSide{
	left,
	right
};
int totalB=3;
int totalC=4;
int leftCNum=totalC;
int leftBNum=totalB;
int rightCNum=0;
int rightBNum=0;
int boat=boatSide::left;
int stateCheck(){
	if((leftBNum>leftCNum&&leftCNum>0)||(rightBNum>rightCNum&&rightCNum>0)){return 0;}//传教士会被吃
	else if(rightCNum==totalC){return 2;}//成功了，程序应该结束
	else {return 1;}//目前还ok
}

void show(int op){
	switch (op) {
		case c1b1ToR:
			cout << "c1b1ToR" << endl;
			break;
		case b2ToR:
			cout << "b2ToR" << endl;
			break;
		case c2ToR:
			cout << "c2ToR" << endl;
			break;
		case c1b1ToL:
			cout << "c1b1ToL" << endl;
			break;
		case b2ToL:
			cout << "b2ToL" << endl;
			break;
		case c2ToL:
			cout << "c2ToL" << endl;
			break;
		case c1ToL:
			cout<<"c1ToL"<<endl;
			break;
		case c1ToR:
			cout<<"c1ToR"<<endl;
			break;
		case b1ToR:
			cout<<"b1ToR"<<endl;
			break;
		case b1ToL:
			cout<<"b1ToL"<<endl;
			break;
	}
}

bool canMove(int op){
	switch(op){
		case c1b1ToR:
			if(leftCNum<1||leftBNum<1||boat==boatSide::right)return false;
			else return true;
		case b2ToR:
			if(leftBNum<2||boat==boatSide::right)return false;
			else return true;
		case c2ToR:
			if(leftCNum<2||boat==boatSide::right)return false;
			else return true;
		case c1b1ToL:
			if(rightCNum<1||rightBNum<1||boat==boatSide::left)return false;
			else return true;
		case b2ToL:
			if(rightBNum<2||boat==boatSide::left)return false;
			else return true;
		case c2ToL:
			if(rightCNum<2||boat==boatSide::left)return false;
			else return true;
		case c1ToL:
			if(rightCNum<1||boat==boatSide::left)return false;
			else return true;
		case c1ToR:
			if(leftCNum<1||boat==boatSide::right)return false;
			else return true;
		case b1ToR:
			if(leftBNum<1||boat==boatSide::right)return false;
			else return true;
		case b1ToL:
			if(rightBNum<1||boat==boatSide::left)return false;
			else return true;
	}
}
void move(int op){
	switch(op){
		case c1b1ToR:
			leftCNum--;rightCNum++;
			leftBNum--;rightBNum++;
			boat=boatSide::right;
			break;
		case b2ToR:
			leftBNum-=2;rightBNum+=2;
			boat=boatSide::right;
			break;
		case c2ToR:
			leftCNum-=2;rightCNum+=2;
			boat=boatSide::right;
			break;
		case c1b1ToL:
			rightCNum--;leftCNum++;
			rightBNum--;leftBNum++;
			boat=boatSide::left;
			break;
		case b2ToL:
			rightBNum-=2;leftBNum+=2;
			boat=boatSide::left;
			break;
		case c2ToL:
			rightCNum-=2;leftCNum+=2;
			boat=boatSide::left;
			break;
		case c1ToL:
			rightCNum--;leftCNum++;
			boat=boatSide ::left;
			break;
		case c1ToR:
			leftCNum--;rightCNum++;
			boat=boatSide ::right;
			break;
		case b1ToR:
			leftBNum--;rightBNum++;
			boat=boatSide::right;
			break;
		case b1ToL:
			rightBNum--;leftBNum++;
			boat=boatSide::left;
			break;
	}
}
void recover(int op){
	switch(op){
		case c1b1ToR:
			move(c1b1ToL);
			break;
		case b2ToR:
			move(b2ToL);
			break;
		case c2ToR:
			move(c2ToL);
			break;
		case c1b1ToL:
			move(c1b1ToR);
			break;
		case b2ToL:
			move(b2ToR);
			break;
		case c2ToL:
			move(c2ToR);
			break;
		case c1ToL:
			move(c1ToR);
			break;
		case c1ToR:
			move(c1ToL);
			break;
		case b1ToR:
			move(b1ToL);
			break;
		case b1ToL:

			move(b1ToR);
			break;
		default:
			cout<<"default"<<endl;
	}
}
vector<stack<int>> operation;
int main(int argc, char *argv[]) {
	stack<int> fullStack;
	for(int i=-9;i<10;i+=2)fullStack.push(i);

	int step=-1;
	if(stateCheck()==0)goto FINAL;
	step++;
	operation.push_back(fullStack);

	while(step>=0){

		while(!operation[step].empty()){
			//测试能不能进行这个操作
			if(canMove(operation[step].top())){//可以
				move(operation[step].top());
			}else{
				operation[step].pop();//不可以，当前操作出栈，再循环测试
				continue;
			}
			int state=stateCheck();
			if(state==1){
				//进入下一步
				stack<int> temp;
				for(int i=-9;i<10;i+=2){
					if((i+operation[step].top())!=0)
						temp.push(i);
				}
				operation.push_back(temp);
				step++;
				continue;

			}else if(state==0){
				//这操作不可行，尝试其他操作
				recover(operation[step].top());
				operation[step].pop();
				continue;
			}else if(state==2){
				goto FINAL;
			}
		}
		//从循环下来，必是step中的操作都遍历了，都不行，则需要退回到上一步操作
		operation.pop_back();
		step--;
		if(step>=0){
			if(!operation[step].empty()){
				recover(operation[step].top());
				operation[step].pop();
			}
		}
	}
	FINAL:
	if(step<0)cout<<"该情况下无解"<<endl;
	else{
		for (int i = 0; i <= step; ++i) {
			show(operation[i].top());
		}
	}
	return 0;

}