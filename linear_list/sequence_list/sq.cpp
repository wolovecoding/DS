//
// Created by easylet on 2022/7/7.
//

#include <cstdlib>
#include "iostream"

using namespace std;


#define MAXSIZE 50  //定义线性表（顺序表）的长度
#define InitSize 100
typedef int ElemType;   //ElemType  线性表的类型

/**
 * 此顺序表限定条件：
 *
 * */

typedef struct {
    ElemType data[MAXSIZE] = {0} ;  //为空就是默认分配，这种想法挺不错。
    int length = 0;
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
 *        元素类型为ElemType，而不是int
 *
 * */
bool deleteMin_01(SSqList &L,int &deleteVal){// 参数传入错误，一般返回数，都要多加一个参数 “&地址”， 写多了java，这别忘了
    if(L.length==0)
        return false;
    int pos = 0;  //当前最小元素的位置， 当前最小元素位置在0位置
    L.length--;
    for (int i = 0; i < L.length; ++i) {
        if(L.data[i]<L.data[pos]){
            pos = i;
        }
    }

    deleteVal = L.data[pos];
    while (pos-1<L.length){
        L.data[pos] = L.data[pos+1];
        pos++;
    }
    return true;
}

/**
 * 王道 p18页， 综合应用题第二题
 *  问题：顺序表   逆置  空间复杂度O(1)
 *
 *  基本设计思想：  使用一个中间变量，将第i个和第n-i个元素互换。   进行n/2次
 *
 * */
void reverse_02(SSqList &L){
    ElemType temp = 0;  //空间复杂度 1
    for (int i = 0; i < L.length/2; ++i) {
        temp = L.data[i];
        L.data[i] = L.data[L.length-i-1];
        L.data[L.length-i-1] = temp;
    }
}

/**********************************************************
 * 王道 p18页， 综合应用题第3题
 *
 *  首先看他问的是什么，然后再看时间复杂度和空间复杂度
 *      删除所有值为x的元素，--》只需要遍历一遍就行。  X错误
 *
 *      顺序表删除元素后要移动元素
 * */
void dao_03(SSqList &L,ElemType x){

}

/**
 *  王道 p18 , 第4题
 *      没有要求时间复杂度和空间复杂度
 *      要求，st不合理或顺序表为空，显示错误并退出
 *
 *   基本设计思想：
 *      吸收第3题的思想，  用k记录当前不在这个返回内的元素个数，遍历一篇数组时，如果在这个值之间的元素会被后面不在这个之间的覆盖掉
 * */
bool dao_04(SSqList &L,ElemType s,ElemType t){
    if (L.length==0){
        cout<<"顺序表为空！！";
        return false;
    }
    if (s>=t){
        cout<<"给定值不合法！！";
        return false;
    }

    int k=0;  //记录当前不在此返回内的元素个数。
    for(int i=0;i<L.length;++i){
        if (L.data[i]>t||L.data[i]<s){   //找不在要删除返回之间的,
            L.data[k] = L.data[i];
            k++;
        }
    }
    L.length = k;
    return true;
}
/**
 *
 * 王道 p18 , 第5题
 *      函数同4
 * */

/**
 *  王道 p18 , 第6题
 *      删除所有其值重复的元素。
 *      错因：  没注意到  是  **有序**  顺序表
 *
 *   基本设计思想：  （要用到第三题的思想）
 *      遍历有序顺序表，每次判断是否和前一个元素不相等，不相等就k++,；每次把当前位置元素赋给k位置的元素
 * */
void dao_06(SSqList &L){
    if (L.length==1)
        return;
    int k = 0;
    for (int i = 1; i < L.length; ++i) {
        if (L.data[i]!=L.data[i-1]){
            k++;
            L.data[k] = L.data[i];
        }
    }
    L.length = k+1;
}

/**
 *  王道 p18  , 第7题
 *      将两个  有序  顺序表河滨为一个新的有序顺序表，并由函数返回结果的顺序表
 *
 *      基本设计思想：
 *          创建一个长为m+n的顺序表，当做合并的顺序表。
 *          为每个顺序表设置一个指针，从0开始，每次比较对应位置的元素，小的放到新表里。
 *
 *   **问题** ： 函数返回值，也能 Type & 吗？
 *
 * */
SSqList *dao_07(SSqList &A,SSqList &B){
    SSqList C; C.length=0; //这里最好给数组容量设计大点。
    if (MAXSIZE<A.length+B.length){
        cout<<"容量不够！！";
        exit(0);
    }
    ElemType a=0,b=0,c=0;  //a,b,c对应顺序表的当前对应位置。
    //while (a+b<A.length+B.length+1){   //错误形式：while (a+b<A.length+B.length)   +2也是错误的，因为if和else只会进去一个
    //思路错误，如果有一个到头了，但另一个没到头，再次比较时，就会越界比较。
    while (a<A.length&&b<B.length){
        if (A.data[a]<B.data[b]){
            C.data[c++] = A.data[a++];
            C.length++;
        } else{
            C.data[c++] = B.data[b++];
            C.length++;
        }
    }
    while (a==A.length&&b<B.length){
        C.data[c++] = B.data[b++];
        C.length++;
    }
    while (b==B.length&&a<A.length){
        C.data[c++] = A.data[a++];
        C.length++;
    }
    return &C ;
}
/*
 * 针对第7题的，对两个顺序表进行初始化操作。
 * SSqList A; SSqList B; int a =0; int b = 0;
    for (int i = 0; i < 10; ++i) {
        if (i%2==0){
            A.data[a++]=i;
            A.length++;
        } else{
            B.data[b++]=i;
            B.length++;
        }
    }
 * */



int main(){
    SSqList A; SSqList B; int a =0; int b = 0;
    for (int i = 0; i < 10; ++i) {
        if (i%2==0){
            A.data[a++]=i;
            A.length++;
        } else{
            B.data[b++]=i;
            B.length++;
        }
    }
    SSqList* dao07 = dao_07(A, B);

    

    return 1;
}


