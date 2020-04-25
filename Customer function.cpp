//(1) 登录管理模块：主要实现登录身份的管理、密码管理
#include <iostream> 
#include <fstream> 
#include <string> 
#include <iomanip> 
using namespace std; 
class Logo 
{ 
private: 
string name; 
string password; 
public: 
int in(); // 接受用户登录请求，决定是否允许登入
void reg(); // 用户注册
void print(); // 用户登录界面提示
}; 
int Logo::in() 
{ 
string n,p; 
int i=0,j=0; //j 值表示是否存在此用户
cout<<"输入姓名 "<<endl; 
cin>>n; 
cout<<"输入密码 "<<endl; 
cin>>p; 
ifstream input; 
input.open ("logoinfo.txt"); 
while(!input.eof ()) 
{ 
input>>name>>password; 
if(name==n&&p==password) 
{ 
i=1; 
} 
if(n==name) 
j=1; 
} 
input.close (); 
if(j==0) 
cout<<" 用户不存在，请先注册 !"<<endl; 
return i; //i 值为 1 表示登录成功；为 0 时表示登录失败
} 
void Logo::reg () // 
{ 
ofstream output; 
output.open ("logoinfo.txt",ios::out|ios::app); 
cout<<"输入你的姓名： "<<endl; 
cin>>name; 
cout<<"输入密码 (有效位数 8-16)"<<endl; 
cin>>password; 
while(password.size ()<8||password.size ()>16) 
{ 
cout<<" 密码无效，请重新输入 "<<endl; 
cin>>password; 
} 
output<<name<<' '<<password<<endl; 
output.close (); 
cout<<"注册成功 "<<endl; 
} 
void Logo::print () 
{ 
cout<<setw(40)<<" 欢迎使用房屋中介管理系统 "<<endl; 
cout<<"请选择操作： "<<endl; 
cout<<"\t\t\t1 、用户登录 "<<endl; 
cout<<"\t\t\t2 、用户注册 "<<endl; 
} 
//(2) 房屋信息管理模块：房屋信息的增、删、改、查。
// 类 House，name(物业名称 ),place(地段 ),type(户型 ),direction( 朝向 ),area(面积 ),equip(房屋设
施),price( 价格 ), 
// 使用文件“ houseinfo.txt ”,"hsize.txt" 
class House 
{ 
private: 
string name,place,type,direction,equip; 
float area,price; 
public: 
string getname1() 
{ return House::name;} 
unsigned long hsize; 
void add(); // 增加一条房屋信息
void del(); // 删除一条房屋信息
void alter(); // 修改一条房屋记录
void select(); // 查找房屋信息
void set(string n,string p,string t,string d,string e,float a,float pr) 
{ 
name=n; 
place=p; 
type=t; 
direction=d; 
equip=e; 
area=a; 
price=pr; 
} 
void print() 
{ 
fstream inout; 
inout.open("houseinfo.txt",ios::out|ios::app); 
inout<<name<<' '<<place<<' '<<type<<' '<<direction<<' '<<equip<<' '<<area<<' 
'<<price<<endl; 
inout.close(); 
} 
}; 
void House::add () // 仅特殊用户能增加操作
{ 
fstream isize; 
isize.open ("hsize.txt",ios::in); 
isize>>hsize; 
isize.close(); // 对文件 hsize.txt 操作，读出房屋的信息条数；
fstream inout; 
inout.open ("houseinfo.txt",ios::out|ios::app); 
cout<<"输入物业名称： "<<endl; 
cin>>name; 
cout<<"输入房屋地段： "<<endl; 
cin>>place; 
cout<<"输入房屋户型： "<<endl; 
cin>>type; 
cout<<"输入房屋朝向： "<<endl; 
cin>>direction; 
cout<<"输入房屋设施： "<<endl; 
cin>>equip; 
cout<<"输入房屋面积： "<<endl; 
cin>>area; 
cout<<"输入房屋价格： "<<endl; 
cin>>price; 
inout<<name<<' '<<place<<' '<<type<<' '<<direction<<' '<<equip<<' '<<area<<' 
'<<price<<endl; 
inout.close (); 
hsize++; 
fstream osize; 
osize.open ("hsize.txt",ios::out); 
osize<<hsize; 
osize.close (); // 对文件 hsize.txt 操作，写入新的房屋的信息条数
cout<<"房屋信息更新完成。 "<<endl; 
} 
void House::del() 
{ 
string isname; 
fstream isize; 
isize.open ("hsize.txt",ios::in); 
isize>>hsize; 
isize.close(); // 对文件 hsize.txt 操作，读出房屋的信息条数；
cout<<"输入你需要删除的物业名字： "<<endl; 
cin>>isname; 
House *a=new House[hsize]; 
int i=0,flag=0; 
ifstream input; 
input.open ("houseinfo.txt",ios::in); 
while(!input.eof ()) 
{ 
input>>name>>place>>type>>direction>>equip>>area>>price; 
if(name==isname) 
{ 
flag++; //flag 记录要删除房屋的个数
continue; 
} 
else 
{ 
a[i].set (name,place,type,direction,equip,area,price); 
i++; 
} 
} 
input.close(); 
ofstream output; 
output.open("houseinfo.txt",ios::out); 
for(i=0;i<hsize-flag;i++) 
a[i].print(); 
output.close(); 
fstream osize; 
osize.open ("hsize.txt",ios::out); 
osize<<hsize-flag; 
osize.close (); 
} 
void House::alter() 
{ 
cout<<"输入你需要更新的物业名字即 "<<endl; 
House::del(); 
cout<<"输入更新后房屋信息 "<<endl; 
House::add (); 
} 
void House::select() 
{ 
string hname; 
fstream inout; 
cout<<"输入你要查询的物业名称 "<<endl; 
cin>>hname; 
inout.open ("houseinfo.txt",ios::in); 
while(!inout.eof ()) 
{ 
inout>>name>>place>>type>>direction>>equip>>area>>price; 
if(name==hname) 
{ 
cout<<" 物业名称 "<<name<<endl; 
cout<<" 房屋地段 "<<place<<endl; 
cout<<" 房屋户型 "<<type<<endl; 
cout<<" 房屋朝向 "<<direction<<endl; 
cout<<" 房屋设施 "<<equip<<endl; 
cout<<" 房屋面积 "<<area<<endl; 
cout<<" 房屋价格 "<<price<<endl; 
} 
else 
continue; 
} 
inout.close (); 
} 
//(3) 顾客管理模块，顾客信息的增、删、改、查。
// 类 Customer cname(顾客姓名），tel( 联系方式 ), 
// 使用文件“ coustomerinfo.txt ”,"csize.txt" 
class Customer 
{ 
private: 
string cname,tel; 
public: 
string getname2() 
{ return Customer::cname;} 
unsigned long csize; 
void add(); // 增加一条客户信息
void del(); // 删除一条客户信息
void alter(); // 修改一条客户记录
void select(); // 查找客户信息
void set(string cn,string te) 
{ 
cname=cn; 
tel=te; 
} 
void print() 
{ 
fstream inout; 
inout.open("customerinfo.txt",ios::out|ios::app); 
inout<<cname<<' '<<tel<<endl; 
inout.close(); 
} 
}; 
void Customer::add () // 仅特殊用户能增加操作
{ 
fstream isize; 
isize.open ("csize.txt",ios::in); 
isize>>csize; 
isize.close(); // 对文件 csize.txt 操作，读出客户的信息条数；
fstream inout; 
inout.open ("customerinfo.txt",ios::out|ios::app); 
cout<<"输入客户名称： "<<endl; 
cin>>cname; 
cout<<"输入客户联系方式： "<<endl; 
cin>>tel; 
inout<<cname<<' '<<tel<<endl; 
inout.close (); 
csize++; 
fstream osize; 
osize.open ("csize.txt",ios::out); 
osize<<csize; 
osize.close (); // 对文件 csize.txt 操作，写入新的客户的信息条数
cout<<"客户信息更新完成。 "<<endl; 
} 
void Customer::del() 
{ 
string isname; 
fstream isize; 
isize.open ("csize.txt",ios::in); 
isize>>csize; 
isize.close(); // 对文件 csize.txt 操作，读出客户的信息条数；
cout<<"输入你需要删除的客户名字： "<<endl; 
cin>>isname; 
Customer *b=new Customer[csize]; 
int i=0,flag=0; 
ifstream input; 
input.open ("customerinfo.txt",ios::in); 
while(!input.eof ()) 
{ 
input>>cname>>tel; 
if(cname==isname) 
{ 
flag++; //flag 记录要删除客户的个数
continue; 
} 
else 
{ 
b[i].set (cname,tel); 
i++; 
} 
} 
input.close(); 
ofstream output; 
output.open("customerinfo.txt",ios::out); 
for(i=0;i<csize-flag;i++) 
b[i].print(); 
output.close(); 
fstream osize; 
osize.open ("csize.txt",ios::out); 
osize<<csize-flag; 
osize.close (); 
} 
void Customer::alter() 
{ 
cout<<"输入你需要更新的客户名字即 "<<endl; 
Customer::del(); 
cout<<"输入更新后客户信息 "<<endl; 
Customer::add (); 
} 
void Customer::select() 
{ 
string find; 
fstream inout; 
cout<<"输入你要查询的客户名称 "<<endl; 
cin>>find; 
inout.open ("customerinfo.txt",ios::in); 
while(!inout.eof ()) 
{ 
inout>>cname>>tel; 
if(cname==find) 
{ 
cout<<" 客户姓名 "<<cname<<endl; 
cout<<" 客户联系方式 "<<tel<<endl; 
} 
else 
continue; 
} 
inout.close (); 
} 
//(4) 统计模块 tj 类， size统计数
class tj 
{ 
private: 
int size; 
public: 
void hsum() // 统计房屋总数
{ 
fstream input; 
input.open ("houseinfo.txt",ios::in); 
input>>size; 
input.close (); 
cout<<"房屋总数为： "<<size<<endl; 
} 
void csum() // 统计顾客总数
{ 
fstream input; 
input.open ("customer.txt",ios::in); 
input>>size; 
input.close (); 
cout<<"顾客的总数为： "<<size<<endl; 
} 
}; 
int main() 
{ 
Logo customer; 
int i,flag1,flag2,flag3,flag4,flag5,flag6,flag7; 
customer.print (); // 登录管理提示
cin>>flag1; 
if(flag1==1) 
{ 
flag2=customer.in (); // 用户登录
while(flag2==0) 
{ 
cout<<"\t\t\t 您登录失败。 "<<endl; 
cout<<"\t\t\t3 退出系统 "<<endl; 
cout<<"\t\t\t 其他数字重新登录 "<<endl; 
cout<<"\t\t\t 请选择： "<<endl; 
cin>>i; 
if(i==3) 
return 0; 
flag2=customer.in (); 
} 
} 
else if(flag1==2) 
{ 
customer.reg (); // 新用户注册
cout<<" 你将退出系统，如需其他操作请重新登录系统 "<<endl; 
return 0; 
} 
else { 
cout<<" 输入有误 "<<endl; 
return 0; 
} 
system("cls"); 
cout<<"恭喜您登录成功！ "<<endl; 
cout<<setw(40)<<"( 主菜单 )请选择操作类型： "<<endl; 
cout<<"\t\t\t1 表示房屋信 / 客户息查询 ;"<<endl; 
cout<<"\t\t\t2 表示房屋 / 顾客信息进行增删改 ;"<<endl; 
cout<<"\t\t\t3 表示进行相关信息统计 "<<endl; 
cin>>flag3; 
switch(flag3) 
{ 
case 1: 
system("cls"); 
cout<<" 欢迎进入信息查询系统 "<<endl; 
cout<<setw(40)<<" 输入查询的方面： "<<endl; 
cout<<"\t\t\t1 表示房屋 "<<endl; 
cout<<"\t\t\t2 表示顾客 "<<endl; 
cin>>flag4; 
if(flag4==1) 
{ 
House H; 
H.select (); 
} 
else if(flag4==2) 
{ 
Customer C; 
C.select (); 
} 
else cout<<"输入错误！ "<<endl; 
break; 
case 2: 
{ 
cout<<setw(35)<<" 选择操作： "<<endl; 
cout<<"\t\t\t1 表示对房屋操作 "<<endl; 
cout<<"\t\t\t2 表示对顾客操作 "<<endl; 
cin>>flag5; 
cout<<setw(37)<<" 输入操作类型 :"<<endl; 
cout<<"\t\t\t1 表示信息增加 "<<endl; 
cout<<"\t\t\t2 表示修改信息 "<<endl; 
cout<<"\t\t\t3 表示删除信息 "<<endl; 
cin>>flag6; 
if(flag5==1) 
{ 
House H1; 
if(flag6==1) 
H1.add (); 
else if (flag6==2) 
H1.alter (); 
else if(flag6==3) 
H1.del (); 
else cout<<" 输入错误！ "<<endl; 
} 
else if(flag5==2) 
{ 
Customer C1; 
if(flag6==1) 
C1.add (); 
else if (flag6==2) 
C1.alter (); 
else if(flag6==3) 
C1.del (); 
else cout<<" 输入错误！ "<<endl; 
} 
else cout<<"输入错误！ "<<endl; 
break; 
} 
case 3: 
{ 
system("cls"); 
tj T; 
cout<<"\t\t\t1 表示对房屋总数进行统计 "<<endl; 
cout<<"\t\t\t2 表示对顾客总数统计 "<<endl; 
cin>>flag7; 
switch(flag7) 
{ 
case 1: 
T.hsum (); 
break; 
case 2: 
T.csum (); 
break; 
default: cout<<" 输入错误！ "<<endl; 
} 
} 
break; 
default:cout<<"error!"<<endl; 
} 
return 0; 
} 