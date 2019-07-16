#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include <malloc/malloc.h>

#define   MAX_LEN  20
#define   STU_NUM  60
#define   COURSE_NUM  6
#define   LEN sizeof(struct Student)

typedef struct Student
{
    long num;                    //人数
    char name[MAX_LEN];          //姓名
    float score[COURSE_NUM];     //课程数量
    float sum;                   //总分
    float aver;                  //平均分
    struct Student *next;        //链表指针域
}STU;

int   Menu(void);//创建菜单
STU  *Creat(int n, int m);   //创建链表并录入信息
void  Print(STU *head, int n, int m);                  //打印函数
void  AverSumofEveryCourse(STU *head, int n, int m);   //计算每个学生的总分和平均分
void  AverSumofEveryStudent(STU *head, int n, int m);  //计算每门课程的总分和平均分
STU  *SortbyScore(STU *head, int n);                   //按每个学生的总分由高到低排出名次表
STU  *SortbyNum(STU *head);                            //按学号由小到大排出成绩表
void  SearchbyNum(STU *head, int n, int m);            //按学号查询学生排名及其考试成绩
void  SearchbyName(STU *head, int n, int m);           //按姓名查询学生排名及其考试成绩
void  WritetoFile(STU *head, int n, int m);            //将每个学生的纪录信息写入文件
STU  *ReadfromFile(STU *head, int *n, int *m);         //从文件中读出每个学生的纪录信息并显示



int main()
{
    int n = 0,m = 0;
    int i;
    STU *head;  //定义头节点
    head = (STU *)malloc(LEN);
    while(1)
    {
        i=Menu();
        switch(i)
        {
            case 1:
                printf("\t\t\t******************************************************************************\n");
                printf("\t\t\tInput student number(n<=30):\n"); //输入学生数
                printf("\t\t\t");
                scanf("%d", &n);
                printf("\t\t\tInput course number(m<=6):\n");
                printf("\t\t\t");
                scanf("%d", &m);
                printf("Press the trash bar in the lower right corner\n");
                printf("\t\t\tInput student's ID, name and score:\n");
                head = Creat(n, m);
                break;
            case 2:
                AverSumofEveryStudent(head, n, m);
                break;
            case 3:
                AverSumofEveryCourse(head, n, m);
                break;
            case 4:
                printf("\n\n\n");
                printf("\t\t\tSort in ascending order by score:\n");
                head = SortbyScore(head, n);
                Print(head, n, m);
                break;
            case 5:
                printf("\n\n\n");
                printf("\t\t\tSort in ascending order by number:\n");
                head = SortbyNum(head);
                Print(head, n, m);
                break;
            case 6:
                printf("\n\n\n");
                printf("\t\t\t******************************************************************************\n");
                printf("\t\t\tInput the number you want to search:\n");
                SearchbyNum(head, n, m);
                break;
            case 7:
                printf("\n\n\n");
                printf("\t\t\t******************************************************************************\n");
                printf("\t\t\tInput the name you want to search:\n");
                SearchbyName(head, n, m);
                break;
            case 8:
                printf("\n\n\n");
                Print(head, n, m);
                break;
            case 9:
                WritetoFile(head, n, m);
                break;
            case 0:
                printf("\n\n\n");
                printf("\t\t\t******************************************************************************\n");
                printf("\t\t\tEnd of program!\n");
                printf("\t\t\t******************************************************************************\n");
                return 0;
            default:
                printf("\n\n\n");
                printf("\t\t\t******************************************************************************\n");
                printf("\t\t\tInput error!\n");
                printf("\t\t\t******************************************************************************\n");
        }
    }
}




// 创建菜单
int   Menu(void)
{
    int i;
    printf("\n\n");
    printf("\t\t                         学生成绩管理系统V7.0\n");
    printf("\t\t******************************************************************************\n");
    printf("\t\t*                Management for Students' scores                             *\n");
    printf("\t\t*                1.  Input record                                            *\n");
    printf("\t\t*                2.  Caculate total and average score of every course        *\n");
    printf("\t\t*                3.  Caculate total and average score of every student       *\n");
    printf("\t\t*                4.  Sort in descending order by score                       *\n");
    printf("\t\t*                5.  Sort in ascending order by number                       *\n");
    printf("\t\t*                6.  Search by number                                        *\n");
    printf("\t\t*                7.  Search by name                                          *\n");
    printf("\t\t*                8.  List record                                             *\n");
    printf("\t\t*                9.  Write to a file                                         *\n");

    printf("\t\t*                0.  Exit                                                    *\n");
    printf("\t\t******************************************************************************\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t\tPlease Press the trash bar in the lower right and cornerInput your choice:");
    scanf("%d",&i);
    return i;
}

// 创建链表
STU *Creat(int n, int m) {
    STU *head = NULL;
    STU *p1, *p2 = NULL;
    int i, j;
    // system("cls");
    for (i = 1; i<n + 1; i++)
    {
        p1 = (STU *)malloc(LEN);
        printf("\t\t\tID:");
        scanf("%ld", &p1->num);
        printf("\t\t\tname:");
        scanf("%s", p1->name);
        for (j = 0; j<m; j++)
        {
            printf("\t\t\tsubject %d:",j+1);
            scanf("%f", &p1->score[j]);
        }
        p1->next = NULL;
        if (i == 1)
        {
            head = p2 = p1;
        }
        else
        {
            p2->next = p1;
            p2 = p1;
        }
    }
    return head;
}

void  AverSumofEveryStudent(STU *head, int n, int m)
{
    STU *p;
    int i, j;
    p = head;
    printf ("1");
    if (head != NULL)
    {
        printf("\n\n\n");
        printf("\t\t\t******************************************************************************\n");
        for (i = 0; i<n; i++)
        {
            p->sum = 0.0;
            for (j = 0; j<m; j++)
            {
                p->sum += p->score[j];
            }
            p->aver = p->sum / m;
            printf("\t\t\tstudent %d:    sum=%.2f , aver=%.2f\n", i + 1, p->sum, p->aver);
            p = p->next;
        }
        printf("\t\t\t******************************************************************************\n");
    }
}

void  AverSumofEveryCourse(STU *head, int n, int m)
{
    STU *p;
    int i, j = 1;
    char ch;
    float sum;
    p = head;
    if (head != NULL)
    {
        printf("\t\t\t******************************************************************************\n");
        for (i = 0; i<m; i++)
        {
            p = head;
            sum = 0.0;
            do {
                sum += p->score[i];
                p = p->next;
            } while (p != NULL);
            
            printf("\t\t\tcourse %d:    sum=%.0f , aver=%.0f\n", j, sum, sum / n);
            j++;
        }
        printf("\t\t\t******************************************************************************\n");
        
    }
}

STU  *SortbyScore(STU *head, int n)
{
    STU *endpt;    //控制循环比较
    STU *p;        //临时指针变量
    STU *p1, *p2;
    
    p1 = (STU *)malloc(LEN);
    p1->next = head;        //注意理解：我们增加一个节点，放在第一个节点的前面，主要是为了便于比较。因为第一个节点没有前驱，我们不能交换地址
    head = p1;                 //让head指向p1节点，排序完成后，我们再把p1节点释放掉
    
    for (endpt = NULL; endpt != head; endpt = p)
    {
        for (p = p1 = head; p1->next->next != endpt; p1 = p1->next)
        {
            if (p1->next->sum < p1->next->next->sum)  //如果前面的节点键值比后面节点的键值大，则交换
            {
                p2 = p1->next->next;
                p1->next->next = p2->next;
                p2->next = p1->next;
                p1->next = p2;
                p = p1->next->next;
            }
        }
    }
    
    p1 = head;              //把p1的信息去掉
    head = head->next;       //让head指向排序后的第一个节点
    free(p1);          //释放p1
    p1 = NULL;          //p1置为NULL，保证不产生“野指针”，即地址不确定的指针变量
    
    return head;
}

STU *SortbyNum(STU *head)
{
    STU *first;    //为原链表剩下用于直接插入排序的节点头指针
    STU *t;        //临时指针变量：插入节点
    STU *p, *q;     //临时指针变量
    
    first = head->next;      //原链表剩下用于直接插入排序的节点链表：可根据图12来理解
    head->next = NULL;       //只含有一个节点的链表的有序链表：可根据图11来理解
    
    while (first != NULL)        //遍历剩下无序的链表
    {
        //注意：这里for语句就是体现直接插入排序思想的地方
        for (t = first, q = head; ((q != NULL) && (q->num < t->num)); p = q, q = q->next);  //无序节点在有序链表中找插入的位置
        
        first = first->next; //无序链表中的节点离开，以便它插入到有序链表中
        
        if (q == head)      //插在第一个节点之前
        {
            head = t;
        }
        else            //p是q的前驱
        {
            p->next = t;
        }
        t->next = q;     //完成插入动作
        //first = first->next;
    }
    return head;
}

void  SearchbyNum(STU *head, int n, int m)
{
    long num;
    int i;
    int flag = 1;
    printf("\t\t\t");
    scanf("%ld", &num);
    STU *p;
    p = head;
    if (head != NULL)
    {
        do {
            if (p->num == num)
            {
                printf("\t\t\t");
                printf("%ld\t%s\t", p->num, p->name);
                for (i = 0; i<m; i++)
                {
                    printf("%.0f\t", p->score[i]);
                }
                printf("%.0f\t%.0f\n", p->sum, p->sum / m);
                flag = 0;
                
            }
            p = p->next;
            
        } while (p != NULL);
        if (flag)
        {
            printf("\t\t\t");
            printf("Not found!\n");
        }
    }
    printf("\t\t\t******************************************************************************\n");
}

void  SearchbyName(STU *head, int n, int m)
{
    char name[MAX_LEN];
    int i;
    int flag = 1;
    printf("\t\t\t");
    scanf("%s", name);
    STU *p;
    p = head;
    if (head != NULL)
    {
        do {
            if (strcmp(name, p->name) == 0)
            {
                printf("\t\t\t");
                printf("%ld\t%s\t", p->num, p->name);
                for (i = 0; i<m; i++)
                {
                    printf("%.0f\t", p->score[i]);
                }
                printf("%.0f\t%.0f\n", p->sum, p->sum / m);
                flag = 0;
            }
            p = p->next;
            
        } while (p != NULL);
        if (flag)
        {
            printf("\t\t\t");
            printf("Not found!\n");
        }
    }
    printf("\t\t\t******************************************************************************\n");
}

void Print(STU *head, int n, int m)
{
    STU *p;
    int i;
    p = head;
    
    if (head != NULL)        //只要不是空链表，就输出链表中所有节点
    {
        printf("\t\t\t******************************************************************************\n");
        do
        {
            
            printf("\t\t\t%ld\t%s\t", p->num, p->name);
            for (i = 0; i<m; i++)
            {
                printf("%.0f\t", p->score[i]);
            }
            printf("%.0f\t%.0f\n", p->sum, p->sum / m);
            p = p->next;     //移到下一个节点
        } while (p != NULL);
        printf("\t\t\t******************************************************************************\n");
    }
}

void  WritetoFile(STU *head, int n, int m)
{
    STU *p;
    p = head;
    FILE *fp;
    int i, j;
    printf("\n\n\n");
    printf("\t\t\t******************************************************************************\n");
    if ((fp = fopen("student.txt", "w")) == NULL)
    {
        printf("\t\t\tFail to open student.txt\n");
        return;
    }
    fprintf(fp, "%d\t%d\n", n, m);
    for (i = 0; i<n; i++)
    {
        fprintf(fp, "%12ld%12s", p->num, p->name);
        for (j = 0; j<m; j++)
        {
            fprintf(fp, "%12.0f", p->score[j]);
        }
        fprintf(fp, "%12.0f%12.0f\n", p->sum, p->sum / m);
        
        p = p->next;
    }
    printf("\t\t\tExport Successfully!\n");
    fclose(fp);
    printf("\t\t\t******************************************************************************\n");
    
}
