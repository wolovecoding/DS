//
// Created by easylet on 2022/7/7.
//

#include <cstdlib>
#include <stdio.h>

#define MAXSIZE 50  //定义线性表（顺序表）的长度
#define InitSize 100
typedef int ElemType;   //ElemType  线性表的类型

/**
 * 此顺序表限定条件：
 *
 * */

typedef struct {
    ElemType data[MAXSIZE] = {5,3,4,2,6};  //顺序表直接在这里搞吧
    int length = 5;
}SSqList;  //static sequence list


//顺序表方式需要有返回值，  因为顺序表一般不会动态扩容。  这个i是第几个位置，从1开始
bool ListInsert(SSqList &L,int i,ElemType e){  //i 是从1到length
    if(i>L.length+1||i<1||L.length==MAXSIZE){ //长度不合法   L。length+1 要注意.  或数组满了
        return false;
    }

    for (int j = L.length; j >=i; --j) {
        L.data[j] = L.data[j-1];
    }
    L.data[i-1] = e;
    return true;
}

void printAll(SSqList &L){
    for (int i = 0; i < L.length; ++i) {
        printf("%d  ",L.data[i]);
    }
}


/**
 *   王道 p18页， 综合应用题第一题
 *
 *  基本设计思想：
 *      这里是要遍历数组先找到最小的元素位置， ---》可以通过加一个int 变量存当前最小元素位置，当遍历完数组，可得最小元素位置
 *      存储最小元素
 *      从最小元素位置后一位开始，每个数组元素往前移一位。
 *
 * 易错点：返回值--》bool类型，不是int类型。
 *        函数参数别忘了int 类型的了，放删除数的地址
 *        &是C++对C的补充， 相当于引用，加上&就是双向的了
 *        没有考虑数组长度为0的情况。
 *
 * */
bool deleteMin_01(SSqList &L,int &deleteVal){// 参数传入错误，一般返回数，都要多加一个参数 “&地址”， 写多了java，这别忘了
    if(L.length==0)
        return false;
    int pos = 0;  //当前最小元素的位置， 当前最小元素位置在0位置
    for (int i = 0; i < L.length; ++i) {
        if(L.data[i]<L.data[pos]){
            pos = i;
        }
    }
    int res = L.data[pos];
    while (pos-1<L.length){
        L.data[pos] = L.data[pos+1];
    }
    return true;
}

int main(){
    SSqList sSqList;
    int deleteVal = 0;
    deleteMin_01(sSqList,deleteVal);

    return 0;
}


