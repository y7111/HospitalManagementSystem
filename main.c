#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

long int staticUserName;

struct passwordData{
    long int username;
    double licence;
};
struct shuttleBusData
{
    int no;
    char destination[50];
    char destinationEnd[50];
    int timeyear;
    int timemonth;
    int timeday;
    char stime[20];
    long int timeCode;

};

struct userBusData
{
    long int usernameBus;
    char data[12][200];
    int co;

};
typedef struct medicine
{
    int num;
    wchar_t name[10];
    wchar_t bing[80];
    int quantity;
    float price;
    struct medicine *next;
} medicine;
typedef struct bed{
int room;
int beds;
wchar_t state[40];
int num;
wchar_t name[40];
struct bed *next;
}bed;
typedef struct hospital {
    int num;           // 序号
    wchar_t name[40];  // 中文名字
    wchar_t gender[10];// 性别
    int age;           // 年龄
    wchar_t bing[50];  // 病情
    wchar_t state[50]; // 状态
    struct hospital *next;
} node;

//函数定义
void totalsystem();//总系统
void patientsystem();//病患管理系统
void bedsystem(node *head);//住院管理系统
void bedadd(bed *head,node *head1);//住院办理
void beddelete(bed *head,node *head1);//出院办理
void printList(node *new_node);//输出名单（病患）
void printbed(bed *new_node);//输出名单（住院）
void freeList(node *head);//释放结构体
void freebed(bed *head);
void swapLists(node **head1, node **head2) ;
node* read(FILE *fp);//读入名单（病患）
bed* readbed(FILE *fp);//读入名单（住院）
void numfind(int num1,node *head);//按病患号查找
void namefind(node *head);//按姓名查找
node* reversenode(node *head);//链表逆序
bed* reversebed(bed *head);
void zengtian();//
void bing(node*head);
void printall(medicine *newmedicine);
void freeListl(medicine *head);
void calculatePrice(medicine *head);
medicine* readl(FILE *fp);
void update(int s,node*head);//更改
void write_node(FILE*file,const node*a);
void del(int s,node*head);//删除
//main函数
int userRegistration(void);//用户注册
int userLogIn(void);//用户登录
void printPasswordDatabase(void);//打印数据库
void printPasswordDatabaseTemp(void);//打印临时数据库
double encryptionModule(long int seed,char NMpassword[25]);//加密算法模块
int changePassword(long int CUsername);//用户修改密码
int deleteUser(long int CUsername);//删除用户
//int deleteUserSP(long int CUsername);
int shuttleBusDatabaseRestruction(void);//班车线路录入
int databaseInitialization(void);//班车车次数据库初始化（更改可选时间）
int printfShuttleBusDatabase(void);//打印班车车次数据库
int userBusReservation(long int Busername);//用户预约班车
int PrintUserBusReservation(long int Busername);//打印指定用户的预约信息
int PrintUserBusDatabase(void);//打印所有用户的预约信息
int usernameMove(void);//用户预约系统用户名初始化


int main() {
    // 设置区域为支持中文的环境
    setlocale(LC_ALL, "");
        int logStateCheck=0;
    int st;
//printPasswordDatabase();
//PrintUserBusDatabase();

reChooseUserFuncation:
    printf("XX医院信息管理系统\n用户登录请按1\n用户注册请按2\n修改密码请按3\n删除用户请按4\n");
    scanf("%d",&st);
    switch (st)
  {
case 1:
    if(userLogIn()==1)
        logStateCheck=1;
    break;
case 2:
    if(userRegistration()==1)
        logStateCheck=1;
    break;
case 3:
    printf("请先登录\n");
    if(userLogIn()==1)
        logStateCheck=1;
    if(logStateCheck==1)
       {changePassword(staticUserName);}
    break;
case 4:
    printf("请先登录\n");
    if(userLogIn()==1)
        {logStateCheck=1 ;}
    if(logStateCheck==1);
    {
    printf("请再次确认您要删除用户（此操作不可逆）\n确认请按1\n取消请按2\n");
    int ensure=0;
    scanf("%d",&ensure);
    if(ensure==1)
        deleteUser(staticUserName);
    break;
    }
    break;
default:
    printf("没有此选项\n");
    goto reChooseUserFuncation;
    break;
  }
  if(logStateCheck==1)
    {totalsystem();}
    else
    {
        return 0;
    }
}
//函数
//总系统
void totalsystem()
{
     FILE *fp=fopen("hospital.txt", "r, ccs=UTF-8");
    if (fp == NULL)
        {
        printf("无法打开文件");
        return 1;
        }
    node *head=NULL;
    head=read(fp);
    fclose(fp);
    while(1)
    {
    printf("欢迎进入XX医院后台系统\n");
    int judge;
    printf("如需进入病患管理系统请输入1\n如需进入住院管理系统请输入2\n如需进入班车管理系统请输入3\n如需进入药品管理系统请输入4\n如需退出系统请输入5\n");
    scanf("%d",&judge);
    if(judge==1) {patientsystem();}
    else if(judge==2){bedsystem(head);}
        else if(judge==3){    usernameMove();
    printf("欢迎进入职工班车预约系统\n职工可预约第二天的班车车次\n");
rechoosebusfunction:
    printf("班车预约请按1\n预约信息查询请按2\n");
    int functionChoose;
    scanf("%d",&functionChoose);
switch (functionChoose)
{
    case 1:printfShuttleBusDatabase();userBusReservation(staticUserName);PrintUserBusReservation(staticUserName);break;
    case 2:PrintUserBusReservation(staticUserName);break;
    default:printf("没有此选项！请重新选择/n");goto rechoosebusfunction;break;
}}
        else if(judge==4){medicinesystem();}
        else if(judge==5){printf("欢迎下次使用");break;}
    }
}
//住院管理系统
void bedsystem(node *head1)
{
    FILE *fp=fopen("bedspace.txt", "r, ccs=UTF-8");
    if (fp == NULL)
        {
        printf("无法打开文件");
        return 1;
        }
    bed *head=NULL;
    head=readbed(fp);
    fclose(fp);
    int judge;
    printf("欢迎进入医院住院系统\n");
    while(1)
    {
    printf("如需查看病床状态请输入1\n如需办理住院请输入2\n如需办理出院请输入3\n退出系统请输入\n");
    scanf("%d",&judge);
    if(judge==1){printbed(head);}
    else if(judge==2){bedadd(head,head1);}
        else if(judge==3){beddelete(head,head1);}
         else if(judge==4) {break;}
        else {printf("请重新输入");}
    }
}
//病患管理系统
void patientsystem()
{
        FILE *fp=fopen("hospital.txt", "r, ccs=UTF-8");
    if (fp == NULL)
        {
        printf("无法打开文件");
        return 1;
        }
    node *head=NULL;
    head=read(fp);
    fclose(fp);
    int judge;
    printf("欢迎进入医院病患人员系统\n");
    while(1)
    {
    printf("如需查找人员请输入1\n如需修改人员信息请输入2\n如需增加人员请输入3\n如需删除人员请输入4\n退出系统请输入5\n");
    scanf("%d",&judge);
        if(judge==1){ bing(head);}
        else if(judge==2){int s;
            printf("输入修改人的编号\n");
            scanf("%d",&s);
            update(s,head);}
        else if(judge==3){zengtian();}
        else if(judge==4)
             {
                 int q;
                printf("请输入要删除患者的编号\n");
                scanf("%d",&q);
               del(q,head);
             }
         else if(judge==5) {break;}
        else {printf("请重新输入");}
    }
    freeList(head);
}
//住院办理
void bedadd(bed *head,node *head1)
{
    wchar_t  a1[40]=L"已入住";
    wchar_t  a2[40]=L"未入住";
    int a,t=0,t1=0,num1,num2,k=0;
    node *p;p=head1;
    bed *o;o=head;
    bed *q;q=head;
    bed *w;w=head;
    printf("请输入住院患者病患号\n");
    scanf("%d",&a);
    while(p!=NULL)
    {
        if(a==p->num)
        {
            t=1;
            break;
        }
        p=p->next;
    }
    if(t==0)
    {
        printf("未找到该患者，请先添加此患者\n");
        return 1;
    }
    while(o!=NULL)
    {
        if(a==o->num)
        {
            t1=1;
            break;
        }
        o=o->next;
    }
    if(t1==1)
    {
        printf("患者%ls已经入住\n",p->name);
        return 1;
    }
    printf("房间号       床位        入住状态\n");
            printf("---------------------------------------\n");
    while(q!=NULL)
    {
        if(strstr(q->state,a2)!=NULL)
        {
            wprintf( L"%-6d        %-3d         %-14ls\n",q->room,q->beds,q->state);
        }
        q=q->next;
    }
    wprintf(L"住院患者：%ls\n请选择要入住的房间号和床位\n",p->name);
    scanf("%d %d",&num1,&num2);
    q=head;
    while(q!=NULL)
    {
         if(strstr(q->state,a2)!=NULL&&q->room==num1&&q->beds==num2)
         {
             printf("已成功选择%d房间 %d号床\n",num1,num2);
             strcpy(q->state,a1);
             q->num=p->num;
             strcpy(q->name,p->name);
             k=1;
             break;
         }
            q=q->next;
    }
    if(k==0){printf("不存在该房间或该床位已有人\n");}
}
//出院办理
void beddelete(bed *head,node *head1)
{
    wchar_t  a1[40]=L"已入住";
    wchar_t  a2[40]=L"未入住";
    wchar_t  a3[40]=L"无    ";
    int a,t=0,t1=0,num1,num2,k=0;
    node *p;p=head1;
    bed *o;o=head;
    bed *q;q=head;
    bed *w;w=head;
    printf("请输入出院患者病患号\n");
    scanf("%d",&a);
    while(p!=NULL)
    {
        if(a==p->num)
        {
            t=1;
            break;
        }
        p=p->next;
    }
    if(t==0)
    {
        printf("未找到该患者，请先添加此患者\n");
        return 1;
    }
    while(o!=NULL)
    {
        if(a==o->num)
        {
            t1=1;
            break;
        }
        o=o->next;
    }
    if(t1==0)
    {
        printf("患者%ls已经入住\n",p->name);
        return 1;
    }
    printf("房间号       床位        入住状态    病患号   姓名\n");
            printf("---------------------------------------\n");
    while(q!=NULL)
    {
        if(q->num==a)
        {
            wprintf( L"%-6d        %-3d         %-14ls   %d  %-14ls\n",q->room,q->beds,q->state,q->num,q->name);
            break;
        }
        q=q->next;
    }
    printf("患者%ls已经成功出院。恭喜！\n");
    strcpy(q->state,a2);
    q->num=0;
    strcpy(q->name,a3);
}
//链表逆序
node* reversenode(node *head)
{
    if(head==NULL||head->next==NULL)
    {
        return head;
    }
    node *newhead;
    newhead=reversenode(head->next);
    (head->next)->next=head;
    head->next=NULL;
    return newhead;
}
void swapLists(node **head1,node **head2)
{
    node *temp = *head1;
    *head1 = *head2;
    *head2 = temp;
}
//输出名单（病患）
void printList(node *new_node) {
    node *h;h=new_node;
    int t=1,a,x=1;node *p,*q;p=new_node;q=p;
    while(h!=NULL)
    {
        h=h->next;
        x++;
    }
    h=new_node;
    for(int i=1;i<=x;i++)
    {
        while((h->next)!=NULL)
        {
            if((h->num)>(h->next->num))
            {
               swapLists(h,h->next) ;
            }
            else{h=h->next;}
        }
        h=new_node;
    }
    printf("序号   病患号   姓名           性别   年龄                病情                       状态\n");
    printf("-------------------------------------------------------------------------------------------\n");
    while (new_node != NULL) {
        wprintf( L"%03d     %-6d   %-12ls %-5ls %-3d          %8ls                      %-14ls\n",t,
                new_node->num,
                new_node->name,
                new_node->gender,
                new_node->age,
                new_node->bing,
                new_node->state);
        new_node = new_node->next;
        t++;
    }
    p=reversenode(q);t=1;
    printf("如需倒序输出请输入1，否则请输入2\n");
    scanf("%d",&a);
    if(a==1){
    printf("序号   病患号   姓名           性别   年龄                病情                       状态\n");
    printf("-------------------------------------------------------------------------------------------\n");
    while (p != NULL) {
        wprintf( L"%03d     %-6d   %-12ls %-5ls %-3d          %8ls                      %-14ls\n",t,
                p->num,
                p->name,
                p->gender,
                p->age,
                p->bing,
                p->state);
        p = p->next;
        t++;
    }
    }
}
//输出名单（住院）
void printbed(bed *new_node) {
    int a;bed *p,*q;p=new_node;q=p;
    printf("房间号   床位     入住状态        病患号   姓名\n");
    printf("-------------------------------------------------------------------------------------------\n");
    while (new_node != NULL) {
        wprintf( L"%-6d    %-3d      %-10ls   %03d     %-14ls\n",new_node->room,new_node->beds,
                new_node->state,new_node->num,new_node->name);
        new_node = new_node->next;
    }
}
//释放结构体
void freeList(node *head) {
    while (head != NULL) {
        node *temp = head;
        head = head->next;
        free(temp);
    }
}
//释放结构体
void freebed(bed *head) {
    while (head != NULL) {
        bed *temp = head;
        head = head->next;
        free(temp);
    }
}
//读入名单（病患）
node* read(FILE *fp)
{
    node *head = NULL, *new_node, *end = NULL;
    wchar_t buffer[512];
    while (fgetws(buffer, sizeof(buffer) / sizeof(wchar_t), fp)) {
        new_node = (node *)malloc(sizeof(node));
        if (new_node == NULL) {
            perror("内存分配失败");
            freeList(head);
            fclose(fp);
            return 1;
        }
        new_node->next = NULL;
        if (swscanf(buffer, L"%d %39ls %9ls %d %49ls %49ls",
                    &new_node->num,
                    new_node->name,
                    new_node->gender,
                    &new_node->age,
                    new_node->bing,
                    new_node->state) != 6) {
            //fwprintf(stderr, L"行格式错误: %ls", buffer);
            free(new_node);
            continue;
        }

        if (head == NULL) {
            head = new_node;
            end = new_node;
        } else {
            end->next = new_node;
            end = new_node;
        }
    }
    return head;
}
//读入名单（住院）
bed* readbed(FILE *fp)
{
    bed *head = NULL, *new_node, *end = NULL;
    wchar_t buffer[512];
    while (fgetws(buffer, sizeof(buffer) / sizeof(wchar_t), fp)) {
        new_node = (bed *)malloc(sizeof(bed));
        if (new_node == NULL) {
            perror("内存分配失败");
            freebed(head);
            fclose(fp);
            return 1;
        }
        new_node->next = NULL;
        if (swscanf(buffer, L"%d %d %49ls %03d %49ls",&new_node->room,&new_node->beds,
                    new_node->state,&new_node->num,new_node->name) !=3)
        {
           // fwprintf(stderr, L"行格式错误: %ls", buffer);
            //free(new_node);
            //continue;
        }

        if (head == NULL) {
            head = new_node;
            end = new_node;
        } else {
            end->next = new_node;
            end = new_node;
        }
    }
    end->next=NULL;
    return head;
}
//按病患号查找
void numfind(int num1,node *head)
{
    node *p;
    p=head;
    int a=0;
    while(p!=NULL)
    {
        if(p->num==num1)
        {
            printf("病患号   姓名           性别   年龄       病情              状态\n");
            printf("-------------------------------------------------------------------------\n");
            wprintf(L"%-6d   %-12ls  %-5ls %-3d  %8ls %14ls\n",p->num,p->name,p->gender,p->age,p->bing,p->state);
            a=1;
            break;
        }
        p=p->next;
    }
    if(a==0) {printf("未查找到该患者\n"); }
}
//按姓名查找
void namefind(node *head)
{
    wchar_t name1[40];
    scanf("%ls",name1);
    node *p;
    p=head;
    int a=0,d=1;
    while(p!=NULL)
    {
        if(strstr(p->name,name1)!=NULL) a=1;
        p=p->next;
    }
    p=head;
    if(a==1){
    printf("序号  病患号  姓名           性别   年龄       病情              状态\n");
    printf("-----------------------------------------------------------------------\n");
    while(p!=NULL)
    {
        if(strstr(p->name,name1)!=NULL)
        {
            wprintf(L"%03d %-6d %-12ls %-5ls %-3d  %8ls %14ls\n",d,p->num,p->name,p->gender,p->age,p->bing,p->state);
            a=1;d++;
        }
        p=p->next;
    }
    }
       if(a==0){printf("未查找到该患者\n") ;}
}
void zengtian()
{
    FILE *fp;
    node myNode;

    setlocale(LC_ALL, "");

    wprintf(L"请输入序号：");
    wscanf(L"%d", &myNode.num);

    wprintf(L"请输入名字：");
    wscanf(L"%ls", myNode.name);

    wprintf(L"请输入性别：");
    wscanf(L"%ls", myNode.gender);

    wprintf(L"请输入年龄：");
    wscanf(L"%d", &myNode.age);

    wprintf(L"请输入病情：");
    wscanf(L"%ls", myNode.bing);

    wprintf(L"请输入状态：");
    wscanf(L"%ls", myNode.state);

    fp = _wfopen(L"hospital.txt", L"a, ccs=UTF-8");
    if (fp == NULL) {
        wprintf(L"文件打开失败！\n");
        return;
    }


    fwprintf(fp, L"%d   %ls    %ls    %d    %ls    %ls\n",
             myNode.num, myNode.name, myNode.gender,
             myNode.age, myNode.bing, myNode.state);

    fclose(fp);
    wprintf(L"数据已成功添加到文件中。\n");
}

void bing(node*head)
{
    while(1)
            {
                  int judge1;
                  printf("请选择查找方式\n");
                  printf("姓名关键字查找请输入1\n病患号查找请输入2\n查看所有患者名单请输入3\n退出查找请输入4\n");
                  scanf("%d",&judge1);
                  if(judge1==1)
                  {
                      printf("请输入患者姓名关键字\n");
                      namefind(head);
                  }
                  else if(judge1==2)
                  {
                      printf("请输入病患号\n");
                      int num1;
                      scanf("%d",&num1);
                      numfind(num1,head);
                      break;
                  }
                  else if(judge1==3)
                  {
                      printList(head);
                  }
                   else if(judge1==4){break;}
                 else {printf("请重新输入");}
              }
}
void freeListl(medicine *head)
{
    while (head != NULL)
    {
        medicine *temp = head;
        head = head->next;
        free(temp);
    }
}

// 读取文件并构建链表
medicine* readl(FILE *fp)
{
    medicine *head = NULL, *new_node, *end = NULL;
    wchar_t buffer[1024];
    while (fgetws(buffer, sizeof(buffer) / sizeof(wchar_t), fp))
    {
        new_node = (medicine *)malloc(sizeof(medicine));
        if (new_node == NULL)
        {
            perror("内存分配失败");
            freeListl(head);
            fclose(fp);
            return NULL;
        }
        new_node->next = NULL;
        if (swscanf(buffer, L"%3d %9ls %79ls %d %f",
                     &new_node->num,
                     new_node->name,
                     new_node->bing,
                     &new_node->quantity,
                     &new_node->price) != 5)
        {
            fwprintf(stderr, L"行格式错误: %ls", buffer);
            free(new_node);
            continue;
        }
        if (head == NULL)
        {
            head = new_node;
            end = new_node;
        }
        else
        {
            end->next = new_node;
            end = new_node;
        }
    }
    fclose(fp);
    return head;
}

// 根据病名查找药物
void findMedicineByDisease(medicine *head)
{
    wchar_t disease[80];
    wprintf(L"请输入病名：");
    fgetws(disease, sizeof(disease) / sizeof(wchar_t), stdin);

    // 去掉末尾的换行符
    size_t len = wcslen(disease);
    if (disease[len - 1] == L'\n')
    {
        disease[len - 1] = L'\0';
    }

    int found = 0;
    wprintf(L"以下是适用该病症的药物：\n");
    while (head != NULL)
    {
        if (wcsstr(head->bing, disease) != NULL)
        {
            wprintf(L"药品名称：%ls\n", head->name);
            found = 1;
        }
        head = head->next;
    }

    if (!found)
    {
        wprintf(L"未找到适用该病症的药物。\n");
    }
}


void calculatePrice(medicine *head)
{
    wchar_t disease[80];
    wprintf(L"请输入病名：");
    fgetws(disease, sizeof(disease) / sizeof(wchar_t), stdin);

    // 去掉末尾的换行符
    size_t len = wcslen(disease);
    if (disease[len - 1] == L'\n')
    {
        disease[len - 1] = L'\0';
    }

    int found = 0; // 标志是否找到药品
    while (1)
    {
        if (wcsstr(head->bing, disease) != NULL)
        {
            wprintf(L"找到适用该病症的药物：\n");
            wprintf(L"药品名称：%ls\n", head->name);
            wprintf(L"价格：%.2f\n", head->price);
            wprintf(L"库存：%d\n", head->quantity);

            found = 1; // 标记找到药品

            wprintf(L"请输入购买数量：");
            int quantity;
            scanf("%d", &quantity);
            getchar(); // 清除换行符

            if (quantity > head->quantity)
            {
                wprintf(L"库存不足，仅剩 %d 件。\n", head->quantity);
            }
            else
            {
                float totalPrice=quantity * head->price;
                head->quantity=head->quantity-quantity; // 减少库存
                wprintf(L"购买成功！总价为：%.2f\n", totalPrice);
            }
            break; // 停止查找
        }
        head = head->next;
    }

    if (!found)
    {
        wprintf(L"未找到适用该病症的药物。\n");
    }
}



// 打印药品信息
void printall(medicine *newmedicine)
{
    printf("序号  药品名称                    适用症状                    库存             价格\n");
    printf("-----------------------------------------------------------------------------------\n");
    while (newmedicine != NULL)
    {
        wprintf(L"%03d     %-20ls %-30ls %-10d     %.2f\n",
            newmedicine->num,
            newmedicine->name,
            newmedicine->bing,
            newmedicine->quantity,
            newmedicine->price);
        newmedicine = newmedicine->next;
    }
}

// 主系统
void medicinesystem()
{
    FILE *fp = fopen("medicine.txt", "r, ccs=UTF-8");
    if (fp == NULL)
    {
        wprintf(L"无法打开文件\n");
        return;
    }

    medicine *head = readl(fp);
    if (head == NULL)
    {
        wprintf(L"药品信息读取失败。\n");
        return;
    }

    while (1)
    {
        int choice;
        printf("\n请选择功能：\n");
        printf("1. 查看药品储存情况\n");
        printf("2. 对症下药\n");
        printf("3. 开药\n");
        printf("4. 退出\n");
        printf("输入选项：");
        scanf("%d", &choice);
        getchar(); // 处理换行符

        switch (choice)
        {
            case 1:
                printall(head);
                break;
            case 2:
                findMedicineByDisease(head);
                break;
            case 3:
                calculatePrice(head);
                break;
            case 4:
                //freeList(head);
                totalsystem();
                wprintf(L"程序已退出。\n");
                return 1;
            default:
                wprintf(L"无效选项，请重试。\n");
                break;
        }
    }
}









//用户注册
//注册成功返回1，否则返回0
int userRegistration(void)
{
    printf("注册：\n");
    long int NUname;
    char NUpassword[25];
    FILE *passFile = fopen("passwordDatabase.dat", "ab+"); // 使用 "ab+" 模式读取和写入文件
    if (!passFile)
        {
        printf("错误：无法打开文件！\n注册程序退出\n");
        fclose(passFile);
        return 0;
        }

    // 检查用户名长度的逻辑（8-12位数字）
loop:do {
        printf("请输入工号（8-10位数字）：\n");
        scanf("%ld", &NUname);
        if (NUname < 10000000 || NUname >=10000000000L) {
            printf("工号输入错误！请重新输入。\n");
        }
    } while (NUname < 10000000 || NUname >= 10000000000L);

    // 检查用户名是否已存在
    struct passwordData temp;
    fseek(passFile, 0, SEEK_SET); // 将文件指针移动到文件开头
    while (fread(&temp, sizeof(struct passwordData),1, passFile) == 1)
    {
        if (temp.username == NUname)
        {
            printf("该用户名已存在！请重新输入工号\n");
            fseek(passFile, 0, SEEK_SET);
            goto loop;
        }
    }
    fseek(passFile, 0, SEEK_END); // 将文件指针移动到文件末尾以追加写入

    temp.username=NUname;
// 输入密码并注册
loop1:
    while(getchar()!='\n')
    {continue;}//清空缓冲区
    printf("请输入1-16位密码(允许数字和字母)：\n");
char temp1[25];
    int i=0;
while (1)
{
    temp1[i]=getchar();
    if(temp1[i]==10)
    {
        NUpassword[i]='\0';
        break;
    }
   //限制密码字符的功能
      if(isalnum(temp1[i])==0)
    {
        printf("包含非法字符！请重新输入密码\n");
        i=0;
        goto loop1;
    }

    else
    {
        NUpassword[i]=temp1[i];
        NUpassword[i+1]='\0';
        i++;
    }
    if(i>16)
    {
        printf("密码过长，请重新输入：\n");
        NUpassword[0]='\0';
        i=0;
        goto loop1;
    }
}

     // 读取最多16个字符，留一个字符给字符串结束符

     //客户端数据加密模块
     char NMpassword[25];
     double licence1;
    strcpy(NMpassword, NUpassword);
    licence1=encryptionModule(temp.username,NMpassword);
    temp.licence=licence1;

    // 写入新用户数据到文件
    if (fwrite(&temp, sizeof(struct passwordData), 1, passFile) != 1) {
        printf("错误：写入文件失败！\n注册程序退出\n");
        fclose(passFile);
        return 0;
    }

    printf("注册成功！\n");
    fclose(passFile);
    staticUserName=temp.username;
    return 1;
}





//用户登录
//登录成功返回1，否则返回0
int userLogIn(void)
{
    printf("登录：\n");
    long int LUsername;
    char LUpassword[25];
    FILE *passFile = fopen("passwordDatabase.dat", "ab+");
        if (!passFile)
        {
        printf("错误：无法打开文件！\n登录程序退出\n");
        fclose(passFile);
        return 0;
        }

do {
        printf("请输入工号（8-10位数字）：\n");
        scanf("%ld", &LUsername);
        if (LUsername < 10000000 || LUsername >= 100000000000L) {
            printf("工号输入错误！请重新输入。\n");
        }
    }while (LUsername < 10000000 || LUsername >= 100000000000L);

    struct passwordData temp;
        fseek(passFile, 0, SEEK_SET); // 将文件指针移动到文件开头
    while (fread(&temp, sizeof(struct passwordData), 1, passFile) == 1)
 {
        if (temp.username == LUsername)
        {
            printf("请输入密码：\n");
// 输入密码
loop2:
    while(getchar()!='\n')
    {continue;}//清空缓冲区
    printf("请输入1-16位密码：\n");
    char temp1[25];
    int i=0;
   while (1)
   {
    temp1[i]=getchar();
    if(temp1[i]==10)
    {
        LUpassword[i]='\0';
        break;
    }
       //限制密码字符的功能
      if(isalnum(temp1[i])==0)
    {
        printf("包含非法字符！请重新输入密码\n");
        i=0;
        goto loop2;
    }
    else
    {
        LUpassword[i]=temp1[i];
        LUpassword[i+1]='\0';
        i++;
    }
    if(i>16)
    {
        printf("密码过长，请重新输入：\n");
        LUpassword[0]='\0';
        i=0;
        goto loop2;
    }
    }

    //客户端数据加密模块
     char NMpassword[25];
     double licence1;
    strcpy(NMpassword,LUpassword);
    licence1=encryptionModule(temp.username,NMpassword);

    //判断密码是否相等
    if(temp.licence==licence1)
    {
        printf("登录成功！\n");
        fclose(passFile);
        staticUserName=temp.username;
        return 1;
    }
    else
    {
        printf("密码错误！按回车键重新输入密码\n");
        goto loop2;
    }
        }
 }
            printf("未找到用户名！请先注册\n");
            fclose(passFile);
            return 0;
}



//数据库内容打印
void printPasswordDatabase(void)
{
    FILE *passFile=fopen("passwordDatabase.dat", "ab+");
        if (!passFile)
        {
        perror("错误：文件打开失败！\n");
          }
    struct passwordData temp;
    fseek(passFile, 0, SEEK_SET);
        int i=1;
    while (fread(&temp,sizeof(struct passwordData),1,passFile)==1)
    {
        printf("No.%-5d  username=%ld  licence=%f\n",i,temp.username,temp.licence);
        i++;
    }
    fclose(passFile);
}

//临时数据库内容打印
void printPasswordDatabaseTemp(void)
{
    FILE *passFile=fopen("passwordDatabaseTemp.dat", "ab+");
        if (!passFile)
        {
        perror("错误：文件打开失败！\n");
          }
    struct passwordData temp;
    fseek(passFile, 0, SEEK_SET);
        int i=1;
    while (fread(&temp,sizeof(struct passwordData),1,passFile)==1)
    {
        printf("No.%-5d  username=%ld  licence=%f\n",i,temp.username,temp.licence);
        i++;
    }
    fclose(passFile);
}



//加密算法
double encryptionModule(long int seed,char NMpassword[25])
{
    double licence=0;
    char ab[25];
    double b;
    char arrar[25];
    strcpy(arrar,NMpassword);
    int n=0;
    while(1)
    {
        ab[n]=arrar[n];
        licence+=tan(((seed*ab[n])%360)*3.14159/180)+cos(((seed*ab[n])%360)*3.14159/180);
        n++;
        if(ab[n-1]=='\0')
            break;
    }
    return licence;
}



//删除用户
//删除成功返回1，否则返回0
int deleteUser(long int CUsername)
{
        FILE *passFile = fopen("passwordDatabase.dat", "ab+");
            if (!passFile)
        {
        printf("错误：无法打开文件！");
        fclose(passFile);
        return 0;
        }


        struct passwordData temp;
        struct passwordData tempC;
        fseek(passFile, 0, SEEK_SET); // 将文件指针移动到文件开头

    while (fread(&temp, sizeof(struct passwordData), 1, passFile) == 1)
 {
        if (temp.username == CUsername)
        {
        FILE *passFileTemp = fopen("passwordDatabaseTemp.dat", "ab+");
            if (!passFileTemp)
        {
        printf("错误：无法创建临时文件！");
        fclose(passFileTemp);
        return 0;
        }

            int t=0;
            t=ftell(passFile);
            t=t/sizeof(struct passwordData);

        fseek(passFile, 0, SEEK_SET);
        fseek(passFileTemp, 0, SEEK_SET);

        //文件复制操作
        int d=1;
        while(d!=t)
        {
            fread(&tempC,sizeof(struct passwordData),1,passFile);
            fwrite(&tempC,sizeof(struct passwordData),1,passFileTemp);
            d++;
        }
            long int s;
            s=sizeof(struct passwordData);
            fseek(passFile,s,SEEK_CUR);

        //文件复制操作
        while(fread(&tempC,sizeof(struct passwordData),1,passFile)==1)
        {
            fwrite(&tempC,sizeof(struct passwordData),1,passFileTemp);
        }

            fclose(passFile);
            fclose(passFileTemp);
            remove("passwordDatabase.dat");
            rename("passwordDatabaseTemp.dat","passwordDatabase.dat");
            printf("删除用户成功。\n");
            return 1;


        }
 }
            printf("错误：未找到用户名！\n");
            fclose(passFile);
            return 0;
}



//更改密码（请注意：只有在已登陆的状态下才能开放此功能，并且这个函数自身没有检测是否为登录状态的功能）：
//要求传入用户名这个参数。
//更改成功返回1，否则返回0
int changePassword(long int CUsername)
{
        FILE *passFile = fopen("passwordDatabase.dat", "ab+");
            if (!passFile)
        {
        printf("错误：无法打开文件！");
        fclose(passFile);
        return 0;
        }


        struct passwordData temp;
        struct passwordData tempC;
        fseek(passFile, 0, SEEK_SET); // 将文件指针移动到文件开头

    while (fread(&temp, sizeof(struct passwordData), 1, passFile) == 1)
 {
        if (temp.username == CUsername)
        {
        FILE *passFileTemp = fopen("passwordDatabaseTemp.dat", "ab+");
            if (!passFileTemp)
        {
        printf("错误：无法创建临时文件！");
        fclose(passFileTemp);
        return 0;
        }

            int t=0;
            t=ftell(passFile);
            t=t/sizeof(struct passwordData);
//printf("t=%d\n",t);
        fseek(passFile, 0, SEEK_SET);
        fseek(passFileTemp, 0, SEEK_SET);



        //文件复制操作
        int d=1;
        while(d!=t)
        {
            fread(&tempC,sizeof(struct passwordData),1,passFile);
            fwrite(&tempC,sizeof(struct passwordData),1,passFileTemp);
            d++;
        }


// 输入密码
printf("按回车键输入新密码\n");
char LUpassword[25];
loop3:
    while(getchar()!='\n')
    {continue;}//清空缓冲区
    printf("请输入1-16位新密码(允许数字和字母)：\n");
    char temp1[25];
    int i=0;
   while (1)
   {
    temp1[i]=getchar();
    if(temp1[i]==10)
    {
        LUpassword[i]='\0';
        break;
    }
       //限制密码字符的功能
      if(isalnum(temp1[i])==0)
    {
        printf("包含非法字符！请重新输入密码\n");
        i=0;
        goto loop3;
    }
    else
    {
        LUpassword[i]=temp1[i];
        LUpassword[i+1]='\0';
        i++;
    }
    if(i>16)
    {
        printf("密码过长，请重新输入：\n");
        LUpassword[0]='\0';
        i=0;
        goto loop3;
    }
    }

    //客户端数据加密模块
     char NMpassword[25];
     double licence1;
    strcpy(NMpassword,LUpassword);
    licence1=encryptionModule(temp.username,NMpassword);
    tempC.licence=licence1;
    tempC.username=CUsername;


    long int w;
    w=sizeof(struct passwordData);
    fseek(passFile,w,SEEK_CUR);
    fwrite(&tempC,sizeof(struct passwordData),1,passFileTemp);

        //文件复制操作
        while(fread(&tempC,sizeof(struct passwordData),1,passFile)==1)
        {
            fwrite(&tempC,sizeof(struct passwordData),1,passFileTemp);
        }

            fclose(passFile);
            fclose(passFileTemp);
            remove("passwordDatabase.dat");
            rename("passwordDatabaseTemp.dat","passwordDatabase.dat");
            printf("更改密码成功！\n");
            return 1;


        }
 }
            printf("错误：未找到用户名！\n");
            fclose(passFile);
            return 0;
}






//录入信息，用一次就不用了
int shuttleBusDatabaseRestruction(void)
{
    printf("班车信息录入\n");
    FILE *busDatabaseFile=fopen("shuttleBusDatabase.dat","ab+");
    if(!busDatabaseFile)
    {
        printf("错误！打开文件失败\nERROR_FILE_B1\n");
        fclose(busDatabaseFile);
        return 0;
    }
    struct shuttleBusData temp;
    fseek(busDatabaseFile,0,SEEK_SET);
    int n;
    printf("输入几个车次？\n");
    scanf("%d",&n);
    for (int i=0;i<n;i++)
    {
        printf("请输入车次编号：\n");
        scanf("%d",&temp.no);
        printf("始发地：\n");
        scanf("%s",temp.destination);
        printf("终到地：\n");
        scanf("%s",temp.destinationEnd);
        printf("请输入每天固定的发车时段:\n");
        scanf("%s",temp.stime);
        fwrite(&temp,sizeof(struct shuttleBusData),1,busDatabaseFile);
    }
    fclose(busDatabaseFile);
    return 1;

}

//初始化班车发车日期
int databaseInitialization(void)
{
    FILE *busDatabaseFile=fopen("shuttleBusDatabase.dat","ab+");
    if(!busDatabaseFile)
    {
        printf("错误！打开文件失败\nERROR_FILE_B2\n");
        fclose(busDatabaseFile);
        return 0;
    }
    struct shuttleBusData temp;
    struct shuttleBusData tempC;

    time_t timeTemp=time(NULL);//获取时间
    struct tm *ptm=localtime(&timeTemp);//获取当地现在的时间

    FILE *busDatabaseFileTemp=fopen("shuttleBusDatabaseTemp.dat","ab+");
    if(!busDatabaseFile)
    {
        printf("错误！创建临时文件失败\nERROR_FILE_B_T1\n");
        fclose(busDatabaseFileTemp);
        return 0;
    }

    fseek(busDatabaseFile,0,SEEK_SET);
    fseek(busDatabaseFileTemp,0,SEEK_SET);



    while(fread(&tempC,sizeof(struct shuttleBusData),1,busDatabaseFile)==1)
    {
        tempC.timeyear=ptm->tm_year+1900;
        tempC.timemonth=ptm->tm_mon+1;
        tempC.timeday=ptm->tm_mday+1;
        switch (tempC.timemonth)
       {    case 1:if(tempC.timeday==32) tempC.timeday=1;break;
            case 2:if(tempC.timeday==29) tempC.timeday=1;break;
            case 3:if(tempC.timeday==32) tempC.timeday=1;break;
            case 4:if(tempC.timeday==31) tempC.timeday=1;break;
            case 5:if(tempC.timeday==32) tempC.timeday=1;break;
            case 6:if(tempC.timeday==31) tempC.timeday=1;break;
            case 7:if(tempC.timeday==32) tempC.timeday=1;break;
            case 8:if(tempC.timeday==32) tempC.timeday=1;break;
            case 9:if(tempC.timeday==31) tempC.timeday=1;break;
            case 10:if(tempC.timeday==32) tempC.timeday=1;break;
            case 11:if(tempC.timeday==31) tempC.timeday=1;break;
            case 12:if(tempC.timeday==32) tempC.timeday=1;break;}
        tempC.timeCode=(tempC.timeyear)*10000+(tempC.timemonth)*100+tempC.timeday;
        fwrite(&tempC,sizeof(struct shuttleBusData),1,busDatabaseFileTemp);
    }
    fclose(busDatabaseFile);
    fclose(busDatabaseFileTemp);
    remove ("shuttleBusDatabase.dat");
    rename ("shuttleBusDatabaseTemp.dat","shuttleBusDatabase.dat");
    return 1;
}

//打印班车发车列表
int printfShuttleBusDatabase(void)
{
    databaseInitialization();

    printf("职工班车发车信息如下：\n");
    FILE *busDatabaseFile=fopen("shuttleBusDatabase.dat","ab+");
    if(!busDatabaseFile)
    {
        printf("错误！打开文件失败\nERROR_FILE_B3\n");
        fclose(busDatabaseFile);
        return 0;
    }
    struct shuttleBusData temp;
    fseek(busDatabaseFile,0,SEEK_SET);
        printf("    车次编号             始发==>终到                     发车时间\n");
    while(fread(&temp,sizeof(struct shuttleBusData),1,busDatabaseFile)==1)
    {
        printf("%8d       %s==>%s     %d年%d月%d日  %s\n",temp.no,temp.destination,temp.destinationEnd,temp.timeyear,temp.timemonth,temp.timeday,temp.stime);
    }
    fclose(busDatabaseFile);
    return 1;
}



//核心功能：用户预约
int userBusReservation(long int Busername)
{
    FILE *userBusDataFile=fopen("userBusData.dat","ab+");
    fseek(userBusDataFile,0,SEEK_SET);
    struct userBusData tempB;


    while(fread(&tempB,sizeof(struct userBusData),1,userBusDataFile)==1)
    {
        if(tempB.usernameBus==Busername)
        {
                FILE *busDatabaseFile=fopen("shuttleBusDatabase.dat","ab+");
                struct shuttleBusData temp;
                fseek(busDatabaseFile,0,SEEK_SET);
reChooseBus:
    printf("请输入您要预约的车次编号：\n");
    int nu;
    scanf("%d",&nu);
    while(fread(&temp,sizeof(struct shuttleBusData),1,busDatabaseFile)==1)
    {
        if(temp.no==nu)
        {
            //将十条数据的存储空间依次前移，
            for(int i=1;i<=10;i++)
            {
                memcpy(tempB.data[i-1],tempB.data[i],200);
            }
                memset(tempB.data[10],'\0',sizeof(tempB.data[10]));

            sprintf(tempB.data[10],"%8d       %s==>%s     %d年%d月%d日  %s\n",temp.no,temp.destination,temp.destinationEnd,temp.timeyear,temp.timemonth,temp.timeday,temp.stime);
            fseek(userBusDataFile,-sizeof(struct userBusData),SEEK_CUR);

            //文件复制操作
            FILE *userBusDataTempFile=fopen("userBusDataTemp.dat","ab+");
            fseek(userBusDataTempFile,0,SEEK_SET);
            struct userBusData TempX;
            long int t=ftell(userBusDataFile);
            t=t/sizeof(struct userBusData);
            long int d=0;
            fseek(userBusDataFile,0,SEEK_SET);
            while(d!=t)
            {
                fread(&TempX,sizeof(struct userBusData),1,userBusDataFile);
                fwrite(&TempX,sizeof(struct userBusData),1,userBusDataTempFile);
                d++;
            }

            //memset(userBusDataFile,0,sizeof(struct userBusData));
            fseek(userBusDataFile,sizeof(struct userBusData),SEEK_CUR);
            fwrite(&tempB,sizeof(struct userBusData),1,userBusDataTempFile);

                while(fread(&TempX,sizeof(struct userBusData),1,userBusDataFile)==1)
            {
                fwrite(&TempX,sizeof(struct userBusData),1,userBusDataTempFile);
            }
            fclose(userBusDataFile);
            fclose(busDatabaseFile);
            fclose(userBusDataTempFile);
            remove("userBusData.dat");
            rename("userBusDataTemp.dat","userBusData.dat");
            return 1;
        }

    }

            printf("车次编号不存在！请重新选择\n");
            goto reChooseBus;

    fclose(busDatabaseFile);
    return 0;
        }
    }
}


int PrintUserBusReservation(long int Busername)
{
    FILE *userBusDataFile=fopen("userBusData.dat","ab+");
    struct userBusData tempB;
    fseek(userBusDataFile,0,SEEK_SET);
    while(fread(&tempB,sizeof(struct userBusData),1,userBusDataFile)==1)
    {
        if(tempB.usernameBus==Busername)
        {
            printf("\n用户%ld的班车预约信息（保留最近十条历史记录）：\n",tempB.usernameBus);
            printf("    车次编号             始发==>终到                     发车时间\n");
            printf("--------------------------------------------------------------------------\n");
            for(int n=10;n>=0;n--)
            {
                printf("%s",tempB.data[n]);
            }
            printf("\n");
            fclose(userBusDataFile);
            return 1;
        }

    }
        printf("错误！未在userBusData中找到用户名！\n");
        fclose(userBusDataFile);
        return 0;
}



int PrintUserBusDatabase(void)
{
    FILE *userBusDataFile=fopen("userBusData.dat","ab+");
    struct userBusData tempB;
    while(fread(&tempB,sizeof(struct userBusData),1,userBusDataFile)==1)
    {

            printf("username=%ld\n",tempB.usernameBus);
            printf("    车次编号             始发==>终到                     发车时间\n");
            printf("--------------------------------------------------------------------------\n");
            for(int n=10;n>=0;n--)
            {
                printf("%s",tempB.data[n]);
            }
            printf("\n");

    }
        fclose(userBusDataFile);
        return 1;
}




int usernameMove(void)
{
    FILE *passFile = fopen("passwordDatabase.dat", "ab+");
    FILE *userBusDataFile=fopen("userBusData.dat","ab+");
    struct passwordData temp;
    struct userBusData tempB;

    fseek(passFile,0,SEEK_SET);
    fseek(userBusDataFile,0,SEEK_SET);
back:
    while(fread(&temp,sizeof(struct passwordData),1,passFile)==1)
    {
            while(fread(&tempB,sizeof(struct userBusData),1,userBusDataFile)==1)
            {
                if(tempB.usernameBus!=temp.username)
                {
                    continue;
                }
                else
                {
                    goto Noadd;
                }
            }


            fseek(userBusDataFile,0,SEEK_END);
            tempB.usernameBus=temp.username;
            for(int i=0;i<=10;i++)
                for(int g=0;g<+198;g++)
                        tempB.data[i][g]='\0';
            fwrite(&tempB,sizeof(struct userBusData),1,userBusDataFile);
            fseek(userBusDataFile,0,SEEK_SET);
            while(0)
            {
                Noadd:
                fseek(userBusDataFile,0,SEEK_SET);
                goto back;
            }
    }
    fclose(passFile);
    fclose(userBusDataFile);
    return 0;
}
//一种初始化的思路：全程用passfile里的用户名查找，再存到bus的文件里头，不多加一步存储了。
void update(int s,node*head)
{
    setlocale(LC_ALL,"");
    node*o;
    printf("请输入修改完的修改人信息\n");
     o=(node*)malloc(sizeof(node));
        scanf("%d",&o->num);
        wchar_t temp_name[40];
        wchar_t temp_gender[10];
        wchar_t temp_bing[50];
        wchar_t temp_state[50];
        wscanf(L"%39ls",temp_name);
        wscanf(L"%9ls",temp_gender);
        scanf("%d",&o->age);
        wscanf(L"%49ls",temp_bing);
        wscanf(L"%49ls",temp_state);
        wcscpy(o->name,temp_name);
        wcscpy(o->gender,temp_gender);
        wcscpy(o->bing,temp_bing);
        wcscpy(o->state,temp_state);
    FILE*fp=fopen("hospital.txt","w+, ccs=UTF-8");
    if(fp==NULL)
    {
        perror("fail to open");
    }
    node*newnode;
    newnode=head;
    while(1)
    {
        if(newnode==NULL)
            break;
        if(newnode->num==s)
        {
            newnode->age=o->age;
            strcpy(newnode->bing,o->bing);
            strcpy(newnode->state,o->state);
        }
        newnode=newnode->next;
    }
    node*temp;
    temp=head;
    while (temp!=NULL)
        {
                write_node(fp, temp);
                temp=temp->next;
            }
    fclose(fp);
    free(o);
}
void write_node(FILE*fp,const node*a)
{
    fwprintf(fp,L"%d %ls %ls %d %ls %ls\n",a->num,a->name,a->gender,a->age,a->bing,a->state);
}
void del(int s,node*head)
{
    setlocale(LC_ALL,"");
    FILE*fp=fopen("hospital.txt","w+, ccs=UTF-8");
    if(fp==NULL)
    {
        perror("fail to open");
    }
    node*newnode;
    newnode=head;
    node*befor;
    befor=NULL;
    node*after;
    after=head->next;
    while(newnode!=NULL)
    {
        if(newnode->num==s)
        {
            befor->next=after;
            break;
        }
        befor=newnode;
        newnode=newnode->next;
        after=after->next;
    }
    node*temp;
    temp=head;
    while (temp!=NULL)
        {
                write_node(fp, temp);
                temp=temp->next;
            }
    fclose(fp);
    printf("已删除\n");
}


