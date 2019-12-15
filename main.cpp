#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#define size 81
struct Customer{
    char ID[11];	//顾客ID
    char Name[81];	//姓名
    char Gender[7];	//性别
    char Phone[12];	//电话
    char Password[81];	//密码
    char Email[81];	//邮箱
    char Addr[81];	//收货地址
    float Balance;	//账户余额
}CUST,cust[81],customer[81];

struct Item{
    char Num[7];   //商品编号
    char Market[81];  //所属超市
    char SaleStart[81];//折扣开始
    char SaleEnd[81];//折扣结束
    float SellPrice;//售价
    float PurchasePrice;//进货价格
    float SalePrice;//折扣价
    int Sales;
    int Stock;
    char Name[81];
    int Discount;
}goods[81],temp[81],sort;

struct Cart{
    char Num[7];      //商品编号
    char Name[81];   //商品名称
    char Market[81];   // 所属超市
    char SaleStart[81];  //折扣开始
    char SaleEnd[81];   //折扣结束
    float SellPrice;    //卖价
    float SalePrice;    //折扣价
    int Stock;
    char CUSTID[81];       //库存
}CART[81];

struct Order{
    char Num[7];      //订单编号
    char Category[2]; //商品种类
    char Name[81];    //商品名称
    char Market[81];  //所属超市
    char SaleStart[81];//折扣开始
    char SaleEnd[81];//折扣结束
    float SellPrice;  //售价
    float PurchasePrice;//进货价格
    float SalePrice;//折扣价
    int Sales;
    int Stock;//库存
    int Amount;
    char SaleDay[81];
    char ID[11];
    char OrderNum[30];
    int Pay;
    float Total;
}order[81];

struct mag{
    char magid[81];//管理员ID
    char code[81];//管理员密码
    char market[81];//管理员所属超市
    char name[81];//管理员名字
    char email[81];//管理员邮箱
    
}manager[50];//管理员结构体

int LoginStatus=0;
int ItemNum;
int TempNum;

/*顾客函数*/
int ReadGoods();//读取商品数据
int ReadOrder();//读取订单

void Customer();// 顾客功能
void Administration();
void CUSTLogin();//顾客登陆比对用户名密码
void CUSTLoginSuccess();//顾客登陆成功选择功能
void SearchItem();//商品查询
void Add2Cart();//加入购物车
void CARTFUNC();
void Order();//用户订单界面
int Pay(int);//显示用户已付款／未付款订单
void NotPay();//显示未付款订单后，用户选择操作
void Paying(int);//付款
void CancelPay();//取消订单
void Info();
void SignUp();//顾客注册
int IsEmail(char *str);//判断邮箱格式合法性
void SearchItemName();//按商品名查找
void SearchMarketName();//按超市名查找
void SearchDiscount();//筛选折扣商品
void SearchPrice();// 价格排序
void SearchSales();//销量排序
void All2Temp();
void Delect();

//*******************************************************************管理员函数*********************************************************************************//
void login();//管理员登录
void comeIn();//进入
void readManagerFile();//读取管理员信息

void ordermanage();//订单管理
void readOrderFile();//读取订单信息到order
void searchOrderInfor();//订单中查询商品订单
void calOrderInfor();//统计订单信息
void ToTemp();//读取订单信息到temp

void TurnOverView();//统计营业额
void SalesRank();//按销量对商品排序
void TurnOverRank();//按营业额对商品排序
void ProfitView();//判断利润最高和最低商品
void UnSoldNStock();//

void goodsmanage();//商品管理
void readCommodityFile();//读取商品信息到commodity
void searchgoods();//查找商品信息
void addgoods();//添加商品


void personalmanage();//个人信息管理
void codeRevise();//修改密码
void emailRevise(); //修改邮箱


char option;//每一次选择时的变量
int managerNum;//管理员人数
int goodsNum;//商品数
int orderNum;//订单数1
int yourNum;
char market[size];//登陆后管理员所在超市

/*主程序 */
int main(){
    char option;
    printf ("-------网上超市管理系统-------\n");
    while(1)
    {
        printf("\t1. 我是顾客\n");
        printf("\t2. 我是管理员\n");
        printf("\t0. 退出程序\n");
        printf("\t请输入数字选择：");
        rewind(stdin);
        scanf("%c",&option);
        switch(option)
        {
            case '1':
                Customer();
                break;
            case '2':
                login();
                break;
            case '0':
                return(0);
            default:
                printf ("\t你的输入有误，请重新输入\n\n");
        }
    }
}

/*函数定义*/
int ReadGoods(){//读取商品数据文件
    FILE *fp;
    fp = fopen("good.txt","r");
    if(fp==NULL){
        printf("不存在商品数据\n");
        getchar();
        exit(1);}
    for (ItemNum=0;!feof(fp);ItemNum++){//写入结构体
        fscanf(fp,"%s%s%s%f%f%d%d%f%s%s%d\n"
               ,goods[ItemNum].Name,goods[ItemNum].Num,goods[ItemNum].Market,&goods[ItemNum].SellPrice
               ,&goods[ItemNum].PurchasePrice,&goods[ItemNum].Sales,&goods[ItemNum].Stock,&goods[ItemNum].SalePrice
               ,goods[ItemNum].SaleStart,goods[ItemNum].SaleEnd,&goods[ItemNum].Discount);
    }
    fclose(fp);
    return (ItemNum);
}
int ReadOrder()
{
    int i=0;
    FILE *outFile;
    outFile=fopen("order.txt","r");
    while(fscanf(outFile,"%s %s %s %s %s %f %f %f %d %d %d %s %s %s %d %f",order[i].Num,order[i].Name,order[i].Market,order[i].SaleStart,order[i].SaleEnd,&order[i].SellPrice,&order[i].PurchasePrice,&order[i].SalePrice,&order[i].Sales,&order[i].Stock,&order[i].Amount,order[i].SaleDay,order[i].ID,order[i].OrderNum,&order[i].Pay,&order[i].Total)!=EOF)
    {
        i++;
    }
    return (i);
}

void Customer(){//顾客功能界面
    char option;
    system("cls");
    printf("\t1. 登陆\n");
    printf("\t2. 注册\n");
    printf("\t3. 商品查询\n");
    printf("\t0. 退出程序\n");
    printf("\t请输入数字选择：");
    while(1)
    {
        rewind(stdin);
        scanf("%c",&option);
        switch(option)
        {
            case '1':
                CUSTLogin();//顾客登陆
                break;
            case '2':
                SignUp();//注册
                break;
            case '3':
                SearchItem();//商品查询
                break;
            case '0':
                exit(0); //退出程序
            default:
                printf ("\t你的输入有误，请重新输入\n\n");
                break;
        }
    }
}
void CUSTLogin(){//顾客登录确认用户名和密码
    char CheckID[11];
    char CheckPassword[81];
    int i=0,j=0;
    char CustID[11],name[81],gender[7],phone[12],pass[81],email[81],addr[81];
    float balance;
    FILE *CID;
    CID = fopen("CustomerID.txt","r");
    system("cls");
    printf("***登录系统***\n");
    printf("请输入您的ID：");
    rewind(stdin);
    scanf("%s",CheckID);
    while(fscanf(CID, "%s%s%s%s%s%s%s%f\n",CustID,name,gender,phone,pass,email,addr,&balance) != EOF){
        if (strcmp(CheckID,CustID)==0){
            strcpy(CUST.ID,CustID);
            strcpy(CUST.Name,name);
            strcpy(CUST.Gender,gender);
            strcpy(CUST.Phone,phone);
            CUST.Balance=balance;
            strcpy(CUST.Email,email);
            strcpy(CUST.Password,pass);
            strcpy(CUST.Addr,addr);
            break;
        }
        if(feof(CID)){
            printf("您输入的ID不存在，请注册或重新登陆.\n按回车返回");
            getchar();
            getchar();
            return Customer();
        }
    }
    
    fclose(CID);
    printf("请输入密码:");
    scanf("%s",CheckPassword);
    while(strcmp(CheckPassword,pass)!=0)
    {
        printf("密码无效\n");
        printf("请重新输入密码 :");
        scanf("%s",CheckPassword);
    }
    CUSTLoginSuccess();
}
void CUSTLoginSuccess(){//顾客登陆成功显示菜单
    char option;
    LoginStatus = 1;
    system("cls");
    printf("\t顾客您好！\n");
    printf("\t1. 商品查询\n");
    printf("\t2. 购物车\n");
    printf("\t3. 订单查询\n");
    printf("\t4. 个人信息修改\n");
    printf("\t请输入数字选择：");
    rewind(stdin);
    while(1){
        scanf("%c",&option);
        switch(option){
            case '1':
                SearchItem();//商品查询
                break;
            case '2':
                CARTFUNC();//购物车
                break;
            case '3':
                Order();
                break;
            case '4':
                Info();//个人信息修改
                break;
            default:
                printf ("\t您的输入有误，请重新输入:");
        }
    }
}
void SignUp(){//顾客注册
    FILE *CID;
    char id[11],name[81],gender[81],phone[81],password[81],email[81],addr[81];
    char GetGender='0';
    float balance;
    int length,i,j=1;
    system("cls");
    //注册ID
    while(j){
        printf("请输入要注册的ID(6-10位字母与数字的组合)：\n");
        rewind(stdin);
        scanf("%s",id);
        length=strlen(id);
        if (length<6||length>10){
            printf("请输入正确长度的ID\n\n");
            j=1;
        }
        else{
            for (i=0;i<length;i++){
                if(isalnum(id[i])){
                    j=0;
                    continue;}
                else {
                    printf("请输入字母与数字组成的合法ID\n");
                    j=1;
                    break;
                }
            }
        }
    }
    
    //注册密码
    printf("请输入密码：");
    rewind(stdin);
    scanf("%s",password);
    
    //注册姓名
    printf("请输入您的姓名：");
    rewind(stdin);
    scanf("%s",name);
    
    //选择性别
    printf("请输入数字选择您的性别(1.男性	2.女性)：");
    while(GetGender=='0'){
        rewind(stdin);
        scanf("%c",&GetGender);
        switch(GetGender){
            case '1':
                strcpy(gender,"Male");
                break;
            case '2':
                strcpy(gender,"Female");
                break;
            default:
                printf("请输入有效数字选项:");
                GetGender = '0';
        }
    }
    
    //注册电话
    printf("请输入您的11位电话号码：");
    j=1;
    while(j) {
        rewind(stdin);
        scanf("%s",phone);
        length=strlen(phone);
        if (length!=11){
            printf("电话号码有误，请重新输入：");
            j=1;
        }
        else{
            j=0;
        }
    }
    
    //注册邮箱
    printf("请输入您的邮箱（***@***.***）：");
    while(1){
        rewind(stdin);
        scanf("%s",email);
        if(IsEmail(email))
            break;
        else
            printf("邮箱格式不正确，请重新输入:") ;
    }
    
    
    //注册地址
    printf("请输入您的地址 ：");
    rewind(stdin);
    scanf("%s",addr);
    
    //账户充值
    printf("请为您的账户充值 ：");
    rewind(stdin);
    scanf("%f",&balance);
    
    CID = fopen("CustomerID.txt","a+");
    fprintf(CID, "%s %s %s %s %s %s %s %.2f\n",id,name,gender,phone,password,email,addr,balance);
    fclose(CID);
    printf("\n注册成功！输入回车返回上一页");
    getchar();
    getchar();
    return Customer();
}
int IsEmail(char *str){//验证邮箱格式正误
    char a1[32]={0};
    char a2[32]={0};
    char a3[32]={0};
    char a4[32]={0};
    if(sscanf(str,"%[a-zA_Z0-9_-]@%[a-zA-Z0-9._-]",a1,a2) < 2)
    {
        return 0;
    }
    if(sscanf(a2,"%[a-zA_Z0-9_-].%[a-zA_Z0-9_-.]",a3,a4) <2)
    {
        return 0;
    }
    int i = 1;
    char c;
    
    while((c=a4[i])!='\0')
    {
        if(c == '.'&&a4[i-1] == '.')
            return 0;
        ++i;
    }
    
    if(a4[0] == '.' || a4[i-1] =='.')
        return 0;
    return 1;
}
void SearchItem(){//商品查询方式选择
    char option;
    system("cls");
    ReadGoods();
    printf ("****商品查询****\n");
    printf ("1.根据商品名称查询\n");
    printf ("2.根据超市名称查询\n");
    printf ("3.根据价格排序所有商品\n");
    printf ("4.根据销量排序所有商品\n");
    printf ("请输入数字选择：");
    while(1)
    {
        rewind(stdin);
        scanf("%c",&option);
        switch(option)
        {
            case '1':
                SearchItemName();//根据商品名称查询
                break;
            case '2':
                SearchMarketName();//根据超市名称查询
                break;
            case '3':
                All2Temp();
                SearchPrice();
                break;
            case '4':
                All2Temp();
                SearchSales();
            default:
                printf ("您的输入有误，请重新输入:");
        }
    }
}
void Add2Cart(){//加入购物车
    FILE *cart;
    char option[7];
    int i;
    printf("\n----------------------------------------------------------");
    printf("\n输入商品编号加入购物车\n输入‘1’筛选折扣商品\n输入‘2’按价格排序\n输入‘3’按销量排序\n输入‘0’返回上一页\n请输入选项：");
    rewind(stdin);
    scanf("%s",option);
    if(strncmp(option,"1",1)==0) {
        SearchDiscount(); //折扣信息筛选
    }
    if(strncmp(option,"2",1)==0) {
        SearchPrice();//价格排序
    }
    if(strncmp(option,"3",1)==0) {
        SearchSales();//销量排序
    }
    if(strncmp(option,"0",1)==0) {
        return SearchItem();//返回商品查询
    }
    if (LoginStatus==0){//未登录操作
        printf("\n您尚未登陆，请登录后再进行操作！\n");
        printf("输入回车返回登陆界面");
        getchar();
        getchar();
        return Customer();
    }
    for(i=0;i<ItemNum;i++){
        if(strncmp(option,goods[i].Num,6)!=0){ //输入的商品编号未符合
            continue;}
        if(strncmp(option,goods[i].Num,6)==0){ //输入的商品编号符合
            cart=fopen("cart.txt","a+");
            fprintf(cart,"%s %s %s %s %f %d %d %f %s %s\n"
                    ,CUST.ID
                    ,goods[i].Name,goods[i].Num,goods[i].Market,goods[i].SellPrice
                    ,goods[i].Sales,goods[i].Stock,goods[i].SalePrice
                    ,goods[i].SaleStart,goods[i].SaleEnd);
            fclose(cart);
            printf("成功加入购物车！回车返回上一页");
            getchar();
            getchar();
            return SearchItem();
        }
    }
    //输入的商品编号不存在
    printf("您输入的商品编号不存在，输入回车返回");
    getchar();
    getchar();
    return SearchItem();//返回商品查询
}
void SearchItemName(){//商品名称搜索
    char name[81];//商品名称
    char option[7];
    int i,j=0;
    
    system("cls");
    printf ("****请输入商品名称进行搜索：");
    rewind(stdin);
    scanf("%s",name);
    printf("此处是表头\n");
    for(i=0;i<ItemNum;i++){
        if(strncmp(name,goods[i].Name,10)!=0)
            continue;
        else{	//显示匹配项
            printf("%s %s %s %.2f %d %d %.2f %s %s\n"
                   ,goods[i].Name,goods[i].Num,goods[i].Market,goods[i].SellPrice
                   ,goods[i].Sales,goods[i].Stock,goods[i].SalePrice
                   ,goods[i].SaleStart,goods[i].SaleEnd);
            temp[j]=goods[i];
            j++;
            TempNum=j;
        }
    }
    if(j==0){ //无搜索结果
        printf("\n您搜索的商品尚未上架，输入回车回到上一页");
        getchar();
        getchar();
        return SearchItem();//返回商品查询
    }
    Add2Cart();
}
void SearchMarketName(){//超市名称搜索
    FILE *cart;
    char name[81];//超市名称
    char option[7];
    int i,j=0;
    
    system("cls");
    printf ("****请输入超市名称进行搜索：");
    rewind(stdin);
    scanf("%s",name);
    printf("此处是表头\n");
    for(i=0;i<ItemNum;i++){
        if(strncmp(name,goods[i].Market,10)!=0)
            continue;
        else{	//显示匹配项
            printf("%s %s %s %f %d %d %f %s %s\n"
                   ,goods[i].Name,goods[i].Num,goods[i].Market,goods[i].SellPrice
                   ,goods[i].Sales,goods[i].Stock,goods[i].SalePrice
                   ,goods[i].SaleStart,goods[i].SaleEnd);
            temp[j]=goods[i];
            j++;
            TempNum=j;
        }
    }
    if(j==0){ //无搜索结果
        printf("\n您搜索的超市尚未入驻本系统，输入回车回到上一页");
        getchar();
        getchar();
        return SearchItem();//返回商品查询
    }
    Add2Cart();
}
void SearchDiscount(){//折扣信息筛选
    int i,j=0;
    system("cls");
    printf ("****查询折扣商品****\n");
    printf("此处是表头\n");
    for(i=0;i<TempNum;i++){
        if(temp[i].Discount==0)
            continue;
        else{	//显示匹配项
            printf("%s %s %s %f %d %d %f %s %s\n"
                   ,temp[i].Name,temp[i].Num,temp[i].Market,temp[i].SellPrice
                   ,temp[i].Sales,temp[i].Stock,temp[i].SalePrice
                   ,temp[i].SaleStart,temp[i].SaleEnd);
            j++;
        }
    }
    if(j==0){ //无搜索结果
        printf("您搜索的商品无折扣信息，输入回车返回上一页");
        getchar();
        getchar();
        return SearchItem();//返回商品查询
    }
    Add2Cart();
}
void SearchPrice(){// 价格排序
    int i,j;
    system("cls");
    printf ("****按价格排序****\n");
    for (i = 0; i < TempNum - 1; i++)
        for (j = 0; j < TempNum - 1 - i; j++)
            if (temp[j].SellPrice > temp[j+1].SellPrice) {
                sort = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = sort;
            }
    for(i=0 ; i<TempNum ; i++)
        printf("%s %s %s %.2f %d %d %.2f %s %s\n"
               ,temp[i].Name,temp[i].Num,temp[i].Market,temp[i].SellPrice
               ,temp[i].Sales,temp[i].Stock,temp[i].SalePrice
               ,temp[i].SaleStart,temp[i].SaleEnd);
    return Add2Cart();
}
void SearchSales(){//销量排序
    int i,j;
    system("cls");
    printf ("****按销量排序****\n");
    for (i = 0; i < TempNum - 1; i++)
        for (j = 0; j < TempNum - 1 - i; j++)
            if (temp[j].Sales > temp[j+1].Sales) {
                sort = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = sort;
            }
    for(i=0 ; i<TempNum ; i++)
        printf("%s %s %s %.2f %d %d %.2f %s %s\n"
               ,temp[i].Name,temp[i].Num,temp[i].Market,temp[i].SellPrice
               ,temp[i].Sales,temp[i].Stock,temp[i].SalePrice
               ,temp[i].SaleStart,temp[i].SaleEnd);
    return Add2Cart();
}
void All2Temp(){
    int i;
    for(i=0;i<ItemNum;i++){
        temp[i]=goods[i];
    }
    TempNum=ItemNum;
}

//**购物车**//
void CARTFUNC(){
    FILE *cart,*order,*good;
    char idnum[7],option;
    char* saleday;
    char OrderNum;
    int numpack,decision,a=1,i=1,j=0,k=0,Pay=0;
    float Total;
    while(i==1)
    {
        printf("\t***购物车***\n");
        cart=fopen("cart.txt","a+");
        while(fscanf(cart,"%s%s%s%s%s%f%f%d%s",CART[j].Num,CART[j].Name,CART[j].Market,CART[j].SaleStart,
                     CART[j].SaleEnd,&CART[j].SellPrice,&CART[j].SalePrice,&CART[j].Stock,CART[j].CUSTID)!=EOF)
        {
            if(strncmp(CART[j].CUSTID,CUST.ID,6)==0)
                printf("%s %s %s %s %s %.2f %.2f %d\n",CART[j].Num,CART[j].Name,CART[j].Market,
                       CART[j].SaleStart,CART[j].SaleEnd,CART[j].SellPrice,CART[j].SalePrice,CART[j].Stock);
            else{
                continue;
            }
            j++;
        }   //显示所有商品
        
        printf("\n1.选择您想购买的商品\n2.返回\n");
        rewind(stdin);
        scanf("%c",&option);
        switch(option)
        {
            case'1':
                break;
            case'2':
                CUSTLoginSuccess();
                break;
            default:
                printf("输入有误！\n");
                a=0;
                CARTFUNC();
                break;
        }      //选择下一步行动
        
        
        printf("\n请输入正确的商品编号:\n");
        rewind(stdin);
        scanf("%s",idnum);
        while(a==1){
            if(strcmp(idnum,CART[j].Num)==0)
            { break;	}
            else{
                j--;
                while(j<0){
                    system("cls");
                    
                    printf("您输入的商品不存在！请按回车以重新选择\n");
                    getchar();
                    getchar();
                    a=0;
                    return CARTFUNC();
                    //return CUSTLoginSuccess();
                    break;
                }}
            
        }            //选择正确的商品
        while(1){
            printf("请输入您想购买的商品数量:\n");
            scanf("%d",&numpack);
            rewind(stdin);
            if(numpack>CART[j].Stock)
            {
                printf("库存不足，库存仅剩%d\n",CART[j].Stock);
            }
            else
                break;}      //选择正确的商品数量
        
        Total=(float)numpack*CART[j].SalePrice;
        order=fopen("order.txt","a+");
        struct tm *ptr;
        time_t lt;
        lt =time(NULL);
        ptr=gmtime(&lt);
        saleday=ctime(&lt);    //显示时间
        
        good=fopen("good.txt","r");
        while(fscanf(good,"%s %s %s %f %f %d %d %f %s %s %d",goods[k].Name,goods[k].Num,goods[k].Market,
                     &goods[k].SellPrice,&goods[k].PurchasePrice,&goods[k].Sales,&goods[k].Stock,&goods[k].SalePrice,
                     goods[k].SaleStart,goods[k].SaleEnd,&goods[k].Discount)!=EOF)
        {
            k++;
        }
        while(a==1){
            if(strcmp(idnum,goods[k].Num)==0)
            { break;	}
            else{
                k--;
                while(k<0){
                    system("cls");
                    printf("您输入的商品不存在！请按回车以重新选择\n");
                    getchar();
                    getchar();
                    a=0;
                    return CARTFUNC();
                    break;
                }} //读取商品信息
            
        }
        //Ordernum=21.00;
        //fprintf(order,"%s %s %s %s %s %s %.2f %.2f %d %.2f %d %d %s %s %.2f %s %.2f\n",CART[j].Num,
        //CART[j].Category,CART[j].Name,CART[j].Market,CART[j].SaleStart,CART[j].SaleEnd,CART[j].SellPrice,
        //goods[k].PurchasePrice,goods[k].SalePrice,goods[k].Sales,CART[j].Stock,numpack,saleday,
        //CUST.ID,Ordernum,Pay,Total);
        
        fclose(order);
        
        printf("1.继续选择商品\n2.立即付款\n");
        scanf("%d",&decision);
        rewind(stdin);
        i=decision;
        system("cls");
    }
    
    Order();
    
}
//**订单管理**//
void Order()
{
    printf("\t欢迎来到订单界面！\n");
    printf("\t1.查看已付款订单\n");
    printf("\t2.查看未付款订单\n");
    printf("\t3.返回\n");
    printf("\t请输入数字选择:");
    rewind(stdin);
    scanf("%c",&option);
    while(1)
    {
        switch(option)
        {
            case '1':
                Pay(1);
                break;
            case '2':
                NotPay();
                break;
            case '3':
                CUSTLoginSuccess();
            default:
                printf("\t你的输入有误，请重新输入：");
                rewind(stdin);
                scanf("%c",&option);
                
        }
    }
    
}

//显示已付款/未付款订单函数

int Pay(int a)
{
    int i=0;
    int j=0;
    int k=0;
    float OrderTotal=0;//订单总金额
    int OrderAmount=0;//文件中订单总数
    int OrderMinus=0;//文件中订单总数，用于判断没有相关订单时减去
    //导入订单数据
    OrderAmount=ReadOrder();
    OrderMinus=ReadOrder();
    //输出已付款／未付款订单
    for(j=0;j<OrderAmount;j++)
    {
        if(j<k)
            continue;
        
        if((strcmp(CUST.ID,order[j].ID)==0)&&(order[j].Pay==a))
        {
            OrderTotal=order[j].Total;
            printf("\t商品编号 商品号 数量 单价 总价\n");
            printf("\t%s %s %d %.2f %.2f\n",order[j].Num,order[j].Name,order[j].Amount,order[j].SalePrice,order[j].Total);
            if(k==OrderAmount-1)//如果该订单是单独一个商品在文件最末
            {
                printf("\t订单编号：%s ",order[k].OrderNum);
                printf("\t购买日期：%s ",order[k].SaleDay);
                printf("\t订单总价：%.2f\n",OrderTotal);
                printf("\n");
            }
            
            for(k=j+1;k<OrderAmount;k++)
            {
                
                if(strcmp(order[k].OrderNum,order[j].OrderNum)==0)
                {
                    if(k==OrderAmount-1)//如果该订单最后一个商品在文件最末
                    {
                        printf("\t%s %s %d %.2f %.2f\n",order[k].Num,order[k].Name,order[k].Amount,order[k].SalePrice,order[k].Total);
                        OrderTotal+=order[k].Total;
                        printf("\t订单编号：%s ",order[k-1].OrderNum);
                        printf("\t购买日期：%s ",order[k-1].SaleDay);
                        printf("\t订单总价：%.2f\n",OrderTotal);
                        printf("\n");
                    }
                    else
                    {
                        printf("\t%s %s %d %.2f %.2f\n",order[k].Num,order[k].Name,order[k].Amount,order[k].SalePrice,order[k].Total);
                        OrderTotal+=order[k].Total;
                    }
                }
                else
                {
                    printf("\t订单编号：%s ",order[k-1].OrderNum);
                    printf("\t购买日期：%s ",order[k-1].SaleDay);
                    printf("\t订单总价：%.2f\n",OrderTotal);
                    printf("\n");
                    break;
                }
                
            }
            
        }
        else
            OrderMinus--;
    }
    
    //判断是否没有相关订单
    if (OrderMinus==0)
    {
        printf("\t您没有相关的订单！！请重新查询\n\n");
        Order();
    }
    if(a==1)
    {
        printf("\t输入任意键返回上一级！");
        rewind(stdin);
        getchar ();
        system("cls");
        Order();
    }
    return  OrderAmount;
}

//未付款函数
void NotPay()
{
    int OrderAmount=0;//文件中订单总数
    OrderAmount=Pay(0);//输出未付款订单
    printf("\t1.付款\n");
    printf("\t2.取消订单\n");
    printf("\t3.退出订单界面\n");
    printf("\t请输入您想选择的操作数字:");
    rewind(stdin);
    scanf("%c",&option);
    while(1)//若输入错误，则一直循环
    {
        switch(option)
        {
            case '1':
                Paying(OrderAmount);
                break;
            case '2':
                CancelPay();
                break;
            case '3':
                system("cls");
                Order();
                break;
            default:
                printf("\t你的输入有误，请重新输入：");
                rewind(stdin);
                scanf("%c",&option);
        }
    }
    
}

//付款

void Paying(int OrderAmount)
{
    char PayNum[81];//接受用户输入的订单号
    int CustomerNum=0;//文件中用户数量
    int GoodNum=0;//文件中商品数量
    int i=0;
    int j=0,k=0;
    int count[20];//用于记录文件中订单号与用户输入订单号相同的结构体序号
    int CountNum=0;
    float OrderTotal=0;//订单总额
    FILE *outFile1;
    FILE *inFile1;
    FILE *inFile2;
    FILE *inFile3;
    //读取客户信息文件
    outFile1=fopen("CustomerID.txt","r");
    while(fscanf(outFile1,"%s %s %s %s %s %s %s %f",customer[i].ID,customer[i].Name,customer[i].Gender,customer[i].Phone,customer[i].Password,customer[i].Email,customer[i].Addr,&customer[i].Balance)!=EOF)
    {
        i++;
    }
    CustomerNum=i;
    fclose(outFile1);
    //读取商品信息文件
    GoodNum=ReadGoods();
    //定位相关客户
    for(j=0;j<CustomerNum;j++)
    {
        if (strcmp(CUST.ID,customer[j].ID)==0)
            break;
        
    }/*DANGEROUS j*/
    
    printf("\t请输入您想操作付款的一个订单号，（例:acb123199702251307）:");
    rewind(stdin);
    scanf("%s",PayNum);
    //输入验证
    i=0;
    for(k=0;k<OrderAmount;k++)
    {
        if(strcmp(order[k].OrderNum,PayNum)!=0)
            i++;
    }
    while(i==OrderAmount)
    {
        printf("\t您输入了一个错误的订单号，请重新输入：");
        rewind(stdin);
        scanf("%s",PayNum);
        i=0;
        for(k=0;k<OrderAmount;k++)
        {
            if(strcmp(order[k].OrderNum,PayNum)!=0)
                i++;
        }
    }
    
    //找出订单编号与用户输入相同的，计算总价，修改支付状态，记录序号
    int b=0;
    for(i=0;i<OrderAmount;i++)
    {
        if(strcmp(order[i].OrderNum,PayNum)==0)
        {
            OrderTotal+=order[i].Total;
            order[i].Pay=1;
            count[b++]=i;
        }
        
    }
    CountNum=b;
    //扣款
    customer[j].Balance-=OrderTotal;
    //导出变化后的CustomerID.txt
    inFile1=fopen("CustomerID.txt","w");
    for(k=0;k<CustomerNum;k++)
    {
        fprintf(inFile1,"%s %s %s %s %s %s %s %.2f\n",customer[k].ID,customer[k].Name,customer[k].Gender,customer[k].Phone,customer[k].Password,customer[k].Email,customer[k].Addr,customer[k].Balance);
    }
    fclose(inFile1);
    //导出变化后的order.txt
    inFile2=fopen("order.txt","w");
    for(i=0;i<OrderAmount;i++)
    {
        
        fprintf(inFile2,"%s %s %s %s %s %.2f %.2f %.2f %d %d %d %s %s %s %d %.2f\n",order[i].Num,order[i].Name,order[i].Market,order[i].SaleStart,order[i].SaleEnd,order[i].SellPrice,order[i].PurchasePrice,order[i].SalePrice,order[i].Sales,order[i].Stock,order[i].Amount,order[i].SaleDay,order[i].ID,order[i].OrderNum,order[i].Pay,order[i].Total);
    }
    fclose(inFile2);
    //修改商品库存和销量
    for(i=0;i<GoodNum;i++)
    {
        for(k=0;k<CountNum;k++)
        {
            j=count[k];
            if((strcmp(order[j].Name,goods[i].Name)==0)&&(strcmp(order[j].Market,goods[i].Market)==0))
            {
                goods[i].Sales+=order[j].Amount;
                goods[i].Stock-=order[j].Amount;
            }
        }
    }
    //导出变化后的good.txt
    inFile3=fopen("good.txt","w");
    for(i=0;i<GoodNum;i++)
    {
        
        fprintf(inFile3,"%s %s %s %.2f %.2f %d %d %.2f %s %s %d\n",goods[i].Name,goods[i].Num,goods[i].Market,goods[i].SellPrice,goods[i].PurchasePrice,goods[i].Sales,goods[i].Stock,goods[i].SalePrice,goods[i].SaleStart,goods[i].SaleEnd,goods[i].Discount);
    }
    fclose(inFile3);
    
    printf("\t您已完成支付\n");
    printf("\t1.继续付款\n");
    printf("\t2.返回\n");
    printf("\t请输入数字选择:");
    rewind(stdin);
    scanf("%c",&option);
    while(1)
    {
        switch(option)
        {
            case '1':
                Paying(OrderAmount);
                break;
            case '2':
                system("cls");
                Order();
                break;
            default:
                printf("\t你的输入有误，请重新输入：");
                rewind(stdin);
                scanf("%c",&option);
        }
    }
    
}

//取消订单
void CancelPay()
{
    char PayNum[81];//接受用户输入的订单编号
    int i=0;
    int k=0;
    int OrderAmount=0;//文件中订单总数
    FILE *inFile;
    //导入订单
    OrderAmount=ReadOrder();
    //用户输入
    printf("\t请输入您想操作的一个订单号（例:acb123199702251307）:");
    rewind(stdin);
    scanf("%s",PayNum);
    
    //输入验证
    i=0;
    for(k=0;k<OrderAmount;k++)
    {
        if(strcmp(order[k].OrderNum,PayNum)!=0)
            i++;
    }
    while(i==OrderAmount)
    {
        printf("\t您输入了一个错误的订单号，请重新输入：");
        rewind(stdin);
        scanf("%s",PayNum);
        i=0;
        for(k=0;k<OrderAmount;k++)
        {
            if(strcmp(order[k].OrderNum,PayNum)!=0)
                i++;
        }
    }
    //输出取消后的订单文件
    inFile=fopen("order.txt","w");
    for(k=0;k<OrderAmount;k++)
    {
        if(strcmp(order[k].OrderNum,PayNum)!=0)
        {
            fprintf(inFile,"%s %s %s %s %s %.2f %.2f %.2f %d %d %d %s %s %s %d %.2f\n",order[k].Num,order[k].Name,order[k].Market,order[k].SaleStart,order[k].SaleEnd,order[k].SellPrice,order[k].PurchasePrice,order[k].SalePrice,order[k].Sales,order[k].Stock,order[k].Amount,order[k].SaleDay,order[k].ID,order[k].OrderNum,order[k].Pay,order[k].Total);
        }
        
    }
    
    
    fclose(inFile);
    printf("\t%s取消成功！\n",PayNum);
    printf("\t1.继续取消订单\n");
    printf("\t2.返回\n");
    printf("\t请输入数字选择:");
    rewind(stdin);
    scanf("%c",&option);
    while(1)
    {
        switch(option)
        {
            case '1':
                CancelPay();
                break;
            case '2':
                system("cls");
                Order();
                break;
            default:
                printf("\t你的输入有误，请重新输入：");
                rewind(stdin);
                scanf("%c",&option);
        }
    }
}


//**个人信息修改**//
void Info(){
    //修改用的函数
    void altphone();//修改电话
    void altcode();//修改密码
    void altmail();//修改邮箱
    void altaddress();//修改地址
    //
    FILE*CustomerID;
    int a=1;
    char option;
    
    printf("****个人信息修改****\n");
    printf("\t1.修改电话\n");
    printf("\t2.修改密码\n");
    printf("\t3.修改邮箱\n");
    printf("\t4.修改地址\n");
    printf("\t5.返回\n");
    printf("请选择正确的数字：");
    while(a==1)
    {
        rewind(stdin);
        scanf("%c",&option);
        switch(option)
        {
            case '1':
                a=0;
                altphone();
                break;
            case '2':
                altcode();
                a=0;
                break;
            case '3':
                a=0;
                altmail();
                break;
            case '4':
                altaddress();
                break;
            case '5':
                a=0;
                CUSTLoginSuccess();
                break;
            default:
                printf("\t你的输入有误 请重新输入:");
                break;
        }
    }
}

//修改电话号码//

void altphone(){
    FILE*CustomerID;
    char phonenum[12];
    int i=1,length;
    
    system("cls");
    printf("您的电话号码是： %s",CUST.Phone);
    printf("\n请输入新的电话号码:");
    while(i==1){
        rewind(stdin);
        scanf("%s",phonenum);
        length=strlen(phonenum);
        if (length!=11){
            printf("电话号码有误，请重新输入：");
            i=1;
        }
        else{
            i=0;
        }
    }   //判断电话格式
    
    
    Delect();
    CustomerID=fopen("CustomerID.txt","a+");
    strcpy(CUST.Phone,phonenum);
    fprintf(CustomerID,"%s %s %s %s %s %s %s %.2f\n",CUST.ID,CUST.Name,CUST.Gender,
            CUST.Phone,CUST.Password,CUST.Email,CUST.Addr,CUST.Balance);
    fclose(CustomerID);
    
    printf("修改成功！\n");
    
    Info();
	   
}
//修改密码//
void altcode(){
    FILE*CustomerID;
    char code[81];
    
    printf("Your code is %s",CUST.Password);
    printf("\nPlease input your new password:");
    rewind(stdin);
    scanf("%s",code);
    Delect();
    CustomerID=fopen("CustomerID.txt","a+");
    strcpy(CUST.Password,code);
    fprintf(CustomerID,"%s %s %s %s %s %s %s %.2f\n",CUST.ID,CUST.Name,CUST.Gender,
            CUST.Phone,CUST.Password,CUST.Email,CUST.Addr,CUST.Balance);
    fclose(CustomerID);
    printf("修改成功！请按回车返回重新登录\n");
    getchar();
    getchar();
    CUSTLogin();
}
//修改邮箱//
void  altmail(){
    FILE*CustomerID;
    char  mail[81];
    printf("Your e-mail is %s",CUST.Email);
    printf("\nPlease input your new email:");
    while(1){
        rewind(stdin);
        scanf("%s",mail);
        if(IsEmail(mail))
            break;
        else
            printf("邮箱格式不正确，请重新输入:") ;
    }
    Delect();
    CustomerID=fopen("CustomerID.txt","a+");
    strcpy(CUST.Email,mail);
    fprintf(CustomerID,"%s %s %s %s %s %s %s %.2f\n",CUST.ID,CUST.Name,CUST.Gender,
            CUST.Phone,CUST.Password,CUST.Email,CUST.Addr,CUST.Balance);
    fclose(CustomerID);
    printf("修改成功！\n");
    Info();
}
//修改地址//
void altaddress(){
    FILE *CustomerID;
    char  address[81];
    
    printf("Your address is %s",CUST.Addr);
    printf("\nPlease input your new address:");
    scanf("%s",address);
    Delect();
    CustomerID=fopen("CustomerID.txt","a+");
    strcpy(CUST.Addr,address);
    fprintf(CustomerID,"%s %s %s %s %s %s %s %.2f\n",CUST.ID,CUST.Name,CUST.Gender,
            CUST.Phone,CUST.Password,CUST.Email,CUST.Addr,CUST.Balance);
    fclose(CustomerID);
    printf("修改成功！\n");
    Info();
}

//删除原用户信息//
void  Delect(){
    FILE*CustomerID,*fp;
    int j=0,a=0,b=0,t=0;
    char CustID[11],name[81],gender[7],phone[12],pass[81],email[81],addr[81];
    float balance;
    CustomerID=fopen("CustomerID.txt","r");
    while(fscanf(CustomerID,"%s%s%s%s%s%s%s%f",cust[j].ID,cust[j].Name,cust[j].Gender,
                 cust[j].Phone,cust[j].Password,cust[j].Email,cust[j].Addr,&cust[j].Balance)!=EOF)
    {
        j++;
    }
    fclose(CustomerID);
    fp=fopen("CustomerID.txt","w");
    for(a=0;a<j;a++)
    {
        if(strcmp(CUST.ID,cust[a].ID)!=0)
        {t++;}
        else
            break;
    }
    
    for(b=a;b<j;b++)
    {
        cust[b]=cust[b+1];
    }
    j=j-1;
    
    
    for(;j>0;j--)
    {
        fprintf(fp,"%s %s %s %s %s %s %s %.2f\n",cust[j-1].ID,cust[j-1].Name,cust[j-1].Gender,
                cust[j-1].Phone,cust[j-1].Password,cust[j-1].Email,cust[j-1].Addr,cust[j-1].Balance);
    }
    fclose(fp);//删除原有客户信息
    j=j+1;
}

//************************************************************管理员部分********************************************************************//
void readCommodityFile()//
{
    FILE *op2;
    op2=fopen("good.txt","r");
    
    if(op2==NULL)
    {
        printf("文件出错了！");
        getchar();
        exit(1);
    }
    
    for(goodsNum=0;!feof(op2);goodsNum++)
        fscanf(op2,"%s%s%s%f%f%d%d%f%s%s%d\n",goods[goodsNum].Name,goods[goodsNum].Num,goods[goodsNum].Market,&goods[goodsNum].SellPrice
               ,&goods[goodsNum].PurchasePrice,&goods[goodsNum].Sales
               ,&goods[goodsNum].Stock,&goods[goodsNum].SalePrice
               ,goods[goodsNum].SaleStart,goods[goodsNum].SaleEnd,&goods[goodsNum].Discount);
    
    fclose(op2);
}

//*读取管理员信息函数*//
void readManagerFile()
{
    FILE *op1;
    op1=fopen("manager.txt","r");
    
    if(op1==NULL)
    {
        printf("文件出错了");
        getchar();
        exit(1);
    }
    for(managerNum=0;!feof(op1);managerNum++)
    {
        fscanf(op1,"%s%s%s%s%s\n",manager[managerNum].magid,manager[managerNum].market,manager[managerNum].name,manager[managerNum].email,manager[managerNum].code);
    }
    
    
    fclose(op1);
}

void readOrderFile()////
{
    FILE *op3;
    
    op3=fopen("order.txt","r");
    
    if(op3==NULL)
    {
        printf("文件出错了！");
        getchar();
        exit(1);
    }
    
    for(orderNum=0;!feof(op3);orderNum++)
        fscanf(op3,"%s%s%s%s%s%s%f%f%f%d%d%d%s%s%s%d%f\n",order[orderNum].Num,order[orderNum].Category,order[orderNum].Name,order[orderNum].Market,order[orderNum].SaleStart,order[orderNum].SaleEnd,&order[orderNum].SellPrice,&order[orderNum].PurchasePrice,&order[orderNum].SalePrice,&order[orderNum].Sales,&order[orderNum].Stock,&order[orderNum].Amount,order[orderNum].SaleDay,order[orderNum].ID,order[orderNum].OrderNum,&order[orderNum].Pay,&order[orderNum].Total);
    fclose(op3);
}



//*登录程序*//
void login()
{
    char id[size],code[size];//输入ID和密码//
    int i;//循环添加变量//
    printf("****管理员登录****\n");
    readManagerFile();
    while(1)
    {
        printf("您的ID是6-10个数字和字母的组成，请输入您的ID：");
        rewind(stdin);
        gets(id);
        while(strcmp(id,manager[i].magid)!=0)
        {
            i++;
            if(i>managerNum)
            {
                system("cls");
                printf("对不起，恁输入的ID无效,");
                printf("请重新输入 :");
                rewind(stdin);
                gets(id);
                i=0;
            }
        }
        
        printf("您输入的ID正确，请输入密码:");
        rewind(stdin);
        gets(code);
        while(strcmp(code,manager[i].code)!=0)
        {
            system("cls");
            printf("对不起，恁输入的密码错误");
            printf("请重新输入 :");
            rewind(stdin);
            gets(code);
        }
        break;
    }
    yourNum=i;
    printf("管理员您成功登陆");
    strcpy(market,manager[i].market);
    printf("%s界面,",market);
    printf("请按任意键进入\n");
    rewind(stdin);
    getchar();
    system("cls");//清屏//
    comeIn();//进入//
}

//*进入管理员界面函数*//
void comeIn()
{
    printf ("1.进入订单管理\n");
    printf ("2.进入商品管理\n");
    printf("3.个人信息管理\n");
    printf("4.退出\n");
    printf ("请输入数字选择：");
    while(1)
    {
        rewind(stdin);
        scanf("%c",&option);
        switch(option)
        {
            case '1':
                ordermanage();//进入订单管理//
                break;
            case '2':
                goodsmanage();//进入商品管理//
                break;
            case '3':
                personalmanage(); //进入个人信息管理//
            case '4':
                login();//返回登录界面//
                break;
            default:
                printf ("您的输入有误，请重新输入:");
        }
    }
}

void ordermanage()//订单管理
{
    char option;
    system("cls");
    printf ("****订单管理****\n");
    printf ("1.查看用户订单情况\n");
    printf ("2.统计用户订单信息\n");
    printf("3.返回上一级\n");
    printf ("请输入数字选择：");
    while(1)
    {
        rewind(stdin);
        scanf("%c",&option);
        switch(option)
        {
            case '1':
                searchOrderInfor();//查看用户订单情况
                break;
            case '2':
                calOrderInfor();//统计用户订单信息
                break;
            case '3':
                comeIn();//返回上级
                break;
            default:
                printf("------------------------------------------------------\n");
                printf("输入有误，请重新输入\n");
                rewind(stdin);
                getchar();
                system("cls");
                ordermanage();
        }
    }
}

//*搜索订单信息函数*//
void searchOrderInfor()
{
    int i=0,j;
    char goodName[size];
    readOrderFile();//读取订单信息//
    printf("请输入您想要查找的商品:");
    rewind(stdin);
    gets(goodName);
    printf("\n    订单编号          购物日期          商品编号        商品名称         商品数量         单价 \n");
    
    for(j=0;j<orderNum;)
    {
        if((strcmp(goodName,order[j].Name)==0)&&(strcmp(market,order[j].Market)==0))
        {
            printf("%s %5s %10s %15s %15d %15.2f\n",order[j].OrderNum,order[j].SaleDay,order[j].Num,order[j].Name,order[j].Amount,order[j].SellPrice);
            j++;
            i++;
            continue;
        }
        
        if((strcmp(goodName,order[j].Name)!=0)||(strcmp(market,order[j].Market)!=0))
        {
            j++;
            continue;
        }
    }
    
    if(i==0){ //无搜索结果
        printf("-------------------------------------------------------\n");
        printf("您搜索的商品不存在，输入回车返回上一页。");
        rewind(stdin);
        getchar();
        system("cls");
        ordermanage();
    }
    
    printf("-------------------------------------------------------");
    printf("\n输入回车回到上一页");
    rewind(stdin);
    getchar();
    ordermanage();//返回订单管理界面//
    
}

void calOrderInfor()//
{
    char option;
    system("cls");
    printf ("****统计用户订单信息****\n");
    printf ("1.您超市营业期间内的营业额\n");
    printf ("2.按销量对商品进行排序\n");
    printf ("3.按营业额对商品进行排序\n");
    printf ("4.显示利润最高和利润最低的商品\n");
    printf ("5.判断滞销和进货\n");
    printf("6.返回上一级\n");
    printf ("请输入数字选择：");
    
    while(1)
    {
        rewind(stdin);
        scanf("%c",&option);
        switch(option)
        {
            case '1':
                system("cls");
                TurnOverView();//统计营业额
                break;
            case '2':
                SalesRank();//按销量排序
                break;
            case '3':
                TurnOverRank();//按营业额排序
                break;
            case '4':
                ProfitView();//显示利润最高和最低的商品
                break;
            case '5':
                UnSoldNStock();//判断滞销和进货
                break;
            case '6':
                return ordermanage();	//返回上级
                break;
            default:
                printf ("您的输入有误，请重新输入:");
        }
        
        
    }
    
}

void TurnOverView()//
{
    int j;
    int Amount;
    
    float SellPrice;
    float total=0.00;
    readOrderFile();
    for(j=0;j<orderNum;)
    {
        if((order[j].Pay==1)&&(strcmp(market,order[j].Market)==0))
        {
            SellPrice=order[j].SellPrice;
            Amount=order[j].Amount;
            total+=SellPrice*Amount;
            j++;
            continue;
        }
        
        else
            j++;
        continue;
        
    }
    printf("%s的营业额为:%5.2f\n",market,total);
    printf("-------------------------------------------------------");
    printf("\n输入回车回到上一页");
    rewind(stdin);
    getchar();
    return calOrderInfor();
    
    
    
}

void SalesRank()//按销量排序
{
    ToTemp();
    int i,j;
    int Sales1,Sales2;
    system("cls");
    printf ("****按销量从小到大排序****\n");
    for (i = 0; i < goodsNum - 1; i++)
    {
        for (j = 0; j < goodsNum - 1 - i; j++)
        {
            Sales1=temp[j].Sales;
            Sales2=temp[j+1].Sales;
            if (Sales1> Sales2)
            {
                sort = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = sort;
            }
        }
    }
    
    printf("商品名称   商品编号   超市    商品售价    销量      库存     折扣价\n");
    for(i=0 ; i<goodsNum ; i++)
    {
        if(strcmp(market,temp[i].Market)==0)
            printf("%s %10s %9s %8.2f %8d %10d %10.2f\n"
                   ,temp[i].Name,temp[i].Num,temp[i].Market,temp[i].SellPrice
                   ,temp[i].Sales,temp[i].Stock,temp[i].SalePrice);
    }
    printf("-------------------------------------------------------");
    printf("\n输入回车返回到上一页");
    rewind(stdin);
    getchar();
    return calOrderInfor();
}

void TurnOverRank()//按营业额排序
{
    ToTemp();
    int i,j;
    int Sales1,Sales2;
    float SellPrice1,SellPrice2,turnOver1,turnOver2;
    system("cls");
    printf ("****按营业额从小到大排序****\n");
    
    for (i = 0; i < goodsNum - 1; i++)
    {
        for (j = 0; j < goodsNum - 1 - i; j++)
        {
            SellPrice1=temp[j].SellPrice;
            SellPrice2=temp[j+1].SellPrice;
            Sales1=temp[j].Sales;
            Sales2=temp[j+1].Sales;
            turnOver1=SellPrice1*Sales1;
            turnOver2=SellPrice2*Sales2;
            if (turnOver1 > turnOver2)
            {
                sort = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = sort;
            }
        }
    }
    
    printf("商品名称   商品编号   超市    商品售价    销量      库存     折扣价\n");
    for(i=0 ; i<goodsNum ; i++)
    {
        if(strcmp(market,temp[i].Market)==0)
            printf("%s %10s %9s %8.2f %8d %10d %10.2f\n"
                   ,temp[i].Name,temp[i].Num,temp[i].Market,temp[i].SellPrice
                   ,temp[i].Sales,temp[i].Stock,temp[i].SalePrice);
    }
    printf("-------------------------------------------------------");
    printf("\n输入回车返回到上一页");
    rewind(stdin);
    getchar();
    return calOrderInfor();
}

void ToTemp()//读取订单信息到Temp
{
    FILE *op2;
    op2=fopen("good.txt","r");
    
    if(op2==NULL)
    {
        printf("文件出错了！");
        rewind(stdin);
        getchar();
        exit(1);
    }
    
    for(goodsNum=0;!feof(op2);goodsNum++)
        fscanf(op2,"%s%s%s%f%f%d%d%f%s%s%d\n",temp[goodsNum].Name,temp[goodsNum].Num,temp[goodsNum].Market,&temp[goodsNum].SellPrice
               ,&temp[goodsNum].PurchasePrice,&temp[goodsNum].Sales
               ,&temp[goodsNum].Stock,&temp[goodsNum].SalePrice
               ,temp[goodsNum].SaleStart,temp[goodsNum].SaleEnd,&temp[goodsNum].Discount);
    
    
    fclose(op2);
}

void ProfitView()//显示利润最高和最低的商品
{
    system("cls");
    readCommodityFile();
    int j;
    int Sales=goods[0].Sales;
    float PurchasePrice,SellPrice;
    float profit;
    float max,min;
    char Name1[size],Name2[size];
    PurchasePrice=goods[0].PurchasePrice;
    SellPrice=goods[0].SellPrice;
    profit=Sales*(SellPrice-PurchasePrice);
    max=profit;
    min=profit;
    
    for(j=1;j<goodsNum;)
    {
        if(strcmp(market,goods[j].Market)==0)
            PurchasePrice=goods[j].PurchasePrice;
        SellPrice=goods[j].SellPrice;
        Sales=goods[j].Sales;
        profit=Sales*(SellPrice-PurchasePrice);
        
        if(profit>=max)
        {
            max=profit;
            strcpy(Name1,goods[j].Name);
            j++;
        }
        
        if(profit<=min)
        {
            min=profit;
            strcpy(Name2,goods[j].Name);
            j++;
        }
        
        else
            j++;
        
    }
    
    if(max==(goods[0].SellPrice-goods[0].PurchasePrice)*goods[0].Sales)
        printf("利润最高的商品是:%s \n",goods[0].Name);
    else
        printf("利润最高的商品是:%s \n",Name1);
    
    if(min==(goods[0].SellPrice-goods[0].PurchasePrice)*goods[0].Sales)
        printf("利润最低的商品是:%s \n",goods[0].Name);
    else
        printf("利润最低的商品是:%s \n",Name2);
    
    printf("-------------------------------------------------------");
    printf("\n输入回车回到上一页");
    rewind(stdin);
    getchar();
    return calOrderInfor();
    
}


void UnSoldNStock()//判断滞销和进货
{
    readCommodityFile();
    int i;
    int Sales,Stock1,Stock2;
    float YON;
    printf("需要补货的商品有：\n");
    for(i=0;i<goodsNum;i++)
    {
        Sales=goods[i].Sales;
        Stock2=goods[i].Stock;
        Stock1=Sales+Stock2;
        YON=(float)Sales/Stock1;
        if(YON>=0.5)
            printf("%s\n",goods[i].Name);
    }
    
    printf("-----------------------------------------------------------\n");
    printf("滞销的商品有：\n");
    for(i=0;i<goodsNum;i++)
    {
        Sales=goods[i].Sales;
        Stock2=goods[i].Stock;
        Stock1=Sales+Stock2;
        YON=(float)Sales/Stock1;
        if(strcmp(market,temp[i].Market)==0)
            if(YON<0.3)
                printf("%s\n",goods[i].Name);
    }
    
    printf("-------------------------------------------------------");
    printf("\n输入回车返回到上一页");
    rewind(stdin);
    getchar();
    return calOrderInfor();
}

void goodsmanage()//商品管理
{
    char option;
    system("cls");
    printf ("****商品管理****\n");
    printf ("1.查询上架商品信息\n");
    printf ("2.添加商品\n");
    printf("3.返回上一级\n");
    printf ("请输入数字选择：");
    while(1)
    {
        rewind(stdin);
        scanf("%c",&option);
        switch(option)
        {
            case '1':
                searchgoods();//查询上架商品信息
                break;
            case '2':
                addgoods();//添加商品
                break;
            case '3':
                comeIn();//返回上级
                break;
            default:
                printf("------------------------------------------------------\n");
                printf("输入有误，请按回车重新输入\n");
                rewind(stdin);
                getchar();
                system("cls");
                goodsmanage();
        }
    }
}


void searchgoods()//查询上架商品信息
{
    int i=0,j;
    char goodName[size];
    readCommodityFile();//读取订单信息//
    printf("请输入您想要查找的商品:");
    rewind(stdin);
    gets(goodName);
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("\n商品名称       商品编号         所属超市        商品单价        商品进货价         销量      库存     折扣价 \n");
    
    for(j=0;j<goodsNum;)
    {
        if((strcmp(goodName,goods[j].Name)==0)&&(strcmp(market,goods[j].Market)==0))
        {
            printf("%s %15s %15s %15.2f %15.2f %15d %9d %10.2f\n",goods[j].Name,goods[j].Name,goods[j].Market,goods[j].SellPrice,goods[j].PurchasePrice,goods[j].Sales,goods[j].Stock,goods[j].SalePrice);
            j++;
            i++;
            continue;
        }
        
        if((strcmp(goodName,goods[j].Name)!=0)||(strcmp(market,goods[j].Market)!=0))
        {
            j++;
            continue;
        }
        
    }
    
    if(i==0){ //无搜索结果
        printf("-------------------------------------------------------\n");
        printf("您搜索的商品不存在，输入回车返回上一页。");
        rewind(stdin);
        getchar();
        system("cls");
        goodsmanage();
    }
    
    printf("-------------------------------------------------------");
    printf("\n输入回车回到上一页");
    rewind(stdin);
    getchar();
    goodsmanage();//返回订单管理界面//
}

void addgoods()//添加商品
{
    FILE *op2;
    op2=fopen("good.txt","r");
    
    if(op2==NULL)
    {
        printf("文件出错了！");
        rewind(stdin);
        getchar();
        exit(1);
    }
    
    for(goodsNum=0;!feof(op2);goodsNum++)
        fscanf(op2,"%s%s%s%f%f%d%d%f%s%s%d\n",goods[goodsNum].Name,goods[goodsNum].Num,goods[goodsNum].Market,&goods[goodsNum].SellPrice
               ,&goods[goodsNum].PurchasePrice,&goods[goodsNum].Sales
               ,&goods[goodsNum].Stock,&goods[goodsNum].SalePrice
               ,goods[goodsNum].SaleStart,goods[goodsNum].SaleEnd,&goods[goodsNum].Discount);
    
    fclose(op2);
    
    char Name[size],goodsnum[size],SuperMarket[size],discountTimeOn[size],discountTimeOff[size],Catagory[size];
    char option,option1;
    int Sales=0,Stock;
    int i,k;
    int length,length2,length3;
    int discount;
    float SellPrice,PurchasePrice,SalePrice,discountprice;
    
    system("cls");
    //添加商品ID
    printf("请输入商品号，格式为2位字母+4位数字：");
    rewind(stdin);
    gets(goodsnum);
    length=strlen(goodsnum);
    while(length!=6)
    {
        printf("请输入正确长度的商品号\n\n");
        gets(goodsnum);
        length=strlen(goodsnum);
    }
    while(1)
    {
        if (isalpha(goodsnum[0])&&isalpha(goodsnum[1])&&isdigit(goodsnum[2])&&isdigit(goodsnum[3])&&isdigit(goodsnum[4])&&isdigit(goodsnum[5]))
            break;
        
        else
            printf("请输入正确格式的商品号\n"); 
        rewind(stdin);
        gets(goodsnum);
    }
    
    //添加商品名称
    printf("请输入商品名称：");
    rewind(stdin);
    gets(Name);
    for (i=0;i<goodsNum;i++)
    {
        if (strcmp(goods[i].Name,Name )==0)
            k=0;
        break;
        if (strcmp(goods[i].Name,Name )!=0)
            k++; 
        continue;
    } 
    if(k=0)
        printf("您输入的商品名称已存在，请重新输入。"); 
    else
        printf("您已成功添加名称。");
    
    //添加商品所属超市
    strcpy(SuperMarket,market);
    
    //添加商品类别
    printf("请输入商品类别：");
    rewind(stdin);
    gets(Catagory);
    
    //添加商品进价
    printf("请输入商品进货价格： ");
    rewind(stdin);
    scanf("%f",&PurchasePrice);
    
    //添加商品单价 
    printf("请输入商品销售单价：");
    rewind(stdin);
    scanf("%f",&SellPrice);
    
    //添加商品折扣价
    printf("请选择商品是否有折扣。1.有折扣 2.无折扣\n");
    rewind(stdin);
    scanf("%c",&option1);
    switch(option1)
    {
        case '1':
            discount=1;
            printf("请输入商品折扣价：");
            rewind(stdin);
            scanf("%f",&discountprice);
            break;
            
        case '2':
            discount=0;
            break;
            
        default:
            printf("请输入1或2\n"); 
            
    }
    
    //添加商品数量
    printf("请输入添加该商品的库存：");
    rewind(stdin);
    scanf("%d",&Stock);
    
    //商品折扣开始时间  
    printf("请输入商品折扣开始时间，格式为yyyy:mm:dd:hh:mm，如果没有折扣，请填写0000:00:00:00:00\n");
    printf("请输入：");
    rewind(stdin);
    scanf("%s",discountTimeOn);
    length2=strlen(discountTimeOn);
    while(length2!=16)
    {
        printf("请输入正确长度的时间: \n"); 
        rewind(stdin);
        gets(discountTimeOn);
        length2=strlen(discountTimeOn);
    }
    
    
    while(1)
    {
        if(isdigit(discountTimeOn[0])&&isdigit(discountTimeOn[1])&&isdigit(discountTimeOn[2])&&isdigit(discountTimeOn[3])
           &&isdigit(discountTimeOn[5])&&isdigit(discountTimeOn[6])&&isdigit(discountTimeOn[8])&&isdigit(discountTimeOn[9])
           &&isdigit(discountTimeOn[11])&&isdigit(discountTimeOn[12])&&isdigit(discountTimeOn[14])&&isdigit(discountTimeOn[15])
           &&discountTimeOn[4]==':'&&discountTimeOn[7]==':'&&discountTimeOn[10]==':'&&discountTimeOn[13]==':')
            printf("您已成功输入商品折扣开始时间。\n");
        break;
        
        //else
        
        printf("您输入的格式有误，请重新输入: ");
        rewind(stdin);
        gets(discountTimeOn);
        
        
    }
    
    //商品折扣结束时间  
    printf("请输入商品折扣结束时间，格式为yyyy:mm:dd:hh:mm，如果没有折扣，请填写0000:00:00:00:00\n");
    printf("请输入： ");
    rewind(stdin);
    scanf("%s",discountTimeOff);
    length3=strlen(discountTimeOff);
    while(length3!=16)
    {
        printf("请输入正确长度的时间: \n");
        rewind(stdin); 
        gets(discountTimeOff);
        length2=strlen(discountTimeOn);
    }
    
    while(1)
    {
        if(isdigit(discountTimeOff[0])&&isdigit(discountTimeOff[1])&&isdigit(discountTimeOff[2])&&isdigit(discountTimeOff[3])
           &&isdigit(discountTimeOff[5])&&isdigit(discountTimeOff[6])&&isdigit(discountTimeOff[8])&&isdigit(discountTimeOff[9])
           &&isdigit(discountTimeOff[11])&&isdigit(discountTimeOff[12])&&isdigit(discountTimeOff[14])&&isdigit(discountTimeOff[15])
           &&discountTimeOff[4]==':'&&discountTimeOff[7]==':'&&discountTimeOff[10]==':'&&discountTimeOff[13]==':')
            printf("您已成功输入商品折扣结束时间。\n"); 
        break;
        
        printf("您输入的格式有误，请重新输入。\n");
        rewind(stdin);
        gets(discountTimeOff);
        
        
    }
    
    //发布、修改、取消
    printf("请输入数字选择发布、修改或取消。1.发布 2.修改 3.取消\n"); 
    rewind(stdin);
    scanf("%c",&option);
    switch(option)
    {
        case '1':
            printf("hhh");	
            op2=fopen("good.txt","a+");
            fprintf(op2, "%s %s %s %5.2f %5.2f %d %d %5.2f %s %s %d\n",Name,goodsnum,SuperMarket,SellPrice,PurchasePrice,Sales,Stock,discountprice,discountTimeOn,discountTimeOff,discount);
            printf("hhhh");
            fclose(op2);
            printf("\n您已成功添加商品！");
            break;
            
        case 2:
            return addgoods(); 
            break;
            
        case 3:
            return goodsmanage();
            break;
            
        default:
            printf("------------------------------------------------------\n");
            printf("输入有误，请按回车重新输入\n");
            rewind(stdin);
            getchar();
            system("cls");
            goodsmanage(); 
    } 
    
    
    
}




void personalmanage()//个人信息管理 
{
    char option;
    system("cls");
    printf ("****个人信息管理****\n");
    printf ("1.修改密码\n");
    printf ("2.修改邮箱\n");
    printf("3.返回上一级\n");
    printf ("请输入数字选择：");
    while(1)
    {
        rewind(stdin);
        scanf("%c",&option);
        switch(option)
        {
            case '1':
                codeRevise(); //修改密码 
                break;
            case '2':
                emailRevise();//修改邮箱 
                break;
            case '3':
                comeIn();//返回上级 
                break; 
            default:
                printf("------------------------------------------------------\n");
                printf("输入有误，请按回车重新输入\n");
                rewind(stdin);
                getchar();
                system("cls");
                personalmanage(); 
        }
    }		
}


void codeRevise()//修改密码 
{
    FILE *op1;
    op1=fopen("manager.txt","r");
    
    if(op1==NULL)
    {
        printf("文件出错了");
        rewind(stdin);
        getchar();
        exit(1);	
    }
    for(managerNum=0;!feof(op1);managerNum++)
    {
        fscanf(op1,"%s%s%s%s%s\n",manager[managerNum].magid,manager[managerNum].market,manager[managerNum].name,manager[managerNum].email,manager[managerNum].code);
    }
    
    fclose(op1);
    
    int i;
    char NewCode[size];
    system("cls");
    printf("请输入新的密码：");
    rewind(stdin);
    gets(NewCode);
    strcpy(manager[yourNum].code,NewCode);
    fopen("manager.txt","w+");
    for(i=0;i<managerNum;i++)
    {
        fprintf(op1,"%s %s %s %s %s\n",manager[i].magid,manager[i].market,manager[i].name,manager[i].email,manager[i].code);
    }
    
    fclose(op1);
    printf("*您的密码修改成功*\n");
    printf("-------------------------------------------------------");
    printf("\n输入回车返回到上一页");
    rewind(stdin);
    getchar(); 
    return personalmanage();
}

void emailRevise()//修改邮箱 
{
   	FILE *op1;
    op1=fopen("manager.txt","r");
    
    if(op1==NULL)
    {
        printf("文件出错了");
        rewind(stdin);
        getchar();
        exit(1);	
    }
    for(managerNum=0;!feof(op1);managerNum++)
    {
        fscanf(op1,"%s%s%s%s%s\n",manager[managerNum].magid,manager[managerNum].market,manager[managerNum].name,manager[managerNum].email,manager[managerNum].code);
    }
    
    fclose(op1);
    
    int i;
    char NewEmail[size];
    system("cls");
    printf("请输入新的邮箱：");
    rewind(stdin);
    gets(NewEmail);
    
    if((isdigit(NewEmail[0])||isalpha(NewEmail[0]))&&(isdigit(NewEmail[1])||isalpha(NewEmail[1]))
       &&(isdigit(NewEmail[2])||isalpha(NewEmail[2]))&&(NewEmail[3]=='@')&&(NewEmail[7]=='.')
       &&(isdigit(NewEmail[4])||isalpha(NewEmail[4]))&&(isdigit(NewEmail[5])||isalpha(NewEmail[5]))
       &&(isdigit(NewEmail[6])||isalpha(NewEmail[6]))&&(isdigit(NewEmail[6])||isalpha(NewEmail[6]))&&(isdigit(NewEmail[8])||isalpha(NewEmail[8]))
       &&(isdigit(NewEmail[9])||isalpha(NewEmail[9]))&&(isdigit(NewEmail[10])||isalpha(NewEmail[10])))
    {
        strcpy(manager[yourNum].email,NewEmail);
        fopen("manager.txt","w+");
        for(i=0;i<managerNum;i++)
        {
            fprintf(op1,"%s %s %s %s %s\n",manager[i].magid,manager[i].market,manager[i].name,manager[i].email,manager[i].code);
        }
        
        fclose(op1);
        printf("*您的邮箱修改成功*\n");
        printf("-------------------------------------------------------");
        printf("\n输入回车返回到上一页");
        rewind(stdin);
        getchar(); 
        return personalmanage();
    }
    
    else
        printf("*您输入的邮箱错误，请重新输入*\n");
    return 	emailRevise();
    
}

