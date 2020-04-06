/* 
data-time 2020-04-06 21:41:53

有三种葡萄，每种分别有a,b,c颗。有三个人，第一个人只吃第1,2种葡萄，第二个人只吃第2,3种葡萄，第三个人只吃第1,3种葡萄。
适当安排三个人使得吃完所有的葡萄,并且且三个人中吃的最多的那个人吃得尽量少。

https://www.nowcoder.com/test/question/done?tid=32335143&qid=800546#summary



/*
将一组三个葡萄数想像成三条线段，如果能构成三角形（符合两短相加大于长），则三个人一人吃掉相邻两条边的一半就可以；
如果不能构成三角形（即有一超长边），那么要把超长边平分给两个人吃，
相当于折断长边，现在有4条边肯定能构成四边形，那么有两种情况：
1. 两个人吃完长边后不再吃短边，第三人吃完短边也没有超出另两个人；
2. 两人吃完长边后，如果不帮第三人吃两个短边，会使第三人吃的超过2人。
第一种情况的输出就是长边的1/2；第二种情况则与三角形情况相同，需要所有人均分。
因此，综合来看只有两种情况：所有人平分，或者其中两人平分最多的那种葡萄。这两个哪个大，输出哪个。
*/

/*
总结:还是合并区间内的问题，不过需要进一定的改进优化，使用dp的方式记录
重点在于每个水电站只能被淹没一次。
*/


#include <iostream>
#include <cmath>
using namespace std;
void sort(long list[3]) // 手动冒泡排序
{
    if (list[0]<list[1]) swap(list[0],list[1]);
    if (list[0]<list[2]) swap(list[0],list[2]);
    if (list[1]<list[2]) swap(list[1],list[2]);
}
  
int main()
{
    int n;
    long l[3], sum;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> l[0] >> l[1] >> l[2];
        //排序
        sort(l);
        sum = l[0] + l[1] + l[2];
        //输出所有人平分或者，最大均分的情况
        cout << max((sum + 2) / 3, (l[0] + 1) / 2) << endl;//加2与加1是为上取整
    }
}