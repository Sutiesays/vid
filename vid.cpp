#include<iostream>
#include<iomanip>
#include<string.h>
#include<fstream>
#include<stdio.h>
#include <stdlib.h>
#include<string>
#include <windows.h>
#define _CRT_SECURE_N0_WARNINGS
using namespace std;
char num;
//==========================================================定义一个product类
class product
{
public:
	char name[30];     //名称
	char code[20];     //编号
	double price;      //进货价
	double price1;     //出售价
	int amount;        //数量
	int date_year1, date_month1, date_day1;  //入库/出售日期
	product *next;

	//==========================================商品信息的接收函数
	void Accept()
	{
		cout << "请输入商品的编号：";
		cin >> code;
		cout << "请输入商品的名称：";
		cin >> name;
		cout << "请输入商品的进货价(人民币/元)：";
		cin >> price;
		cout << "请输入商品的出售价(人民币/元)：";
		cin >> price1;
		cout << "请输入商品的数量：";
		cin >> amount;
		cout << "请输入商品的入库日期(年-月-日)：";
		scanf_s("%d-%d-%d", &date_year1, &date_month1, &date_day1);
	}
	//=====================================================商品信息的显示
	void Display(int jun)
	{
		cout << "                     " << endl;
		cout << "商品编号："  << code << endl;
		cout << "商品名称：" << name << endl;
		cout << "商品进货价:" << price << endl;
		cout << "商品出售价："  << price1 << endl;
		if (jun == 1)
		{
			cout << "库 存 量：" << amount << endl;
			cout << "入库时间：" << date_year1 << '-' << date_month1 << '-' << date_day1 << endl;
		}
		else {
			cout << "出 售 量：" << amount << endl;
			cout << "出售时间：" << date_year1 << '-' << date_month1 << '-' << date_day1 << endl;
		}
		cout << "                " << endl;
	}

	//===================================================库存商品信息存入文本文件中的函数
	void Store_in()
	{
		fstream in("C:\\Users\\28432\\Desktop\\综合课设\\2109060106-董妍-录像带商店进销存信息管理系统\\vid\\vid\\库存商品1.txt", ios::out | ios::app);
		// 创建了一个名为in的文件输出流对象，并指定了要打开的文件路径。ios::out标志表示以文本方式打开文件，ios::app标志表示在文件末尾追加内容。
		in << code << " " << name << " " << price << " " << price1 << " " << amount << " " << date_year1 << " " << date_month1 << " " << date_day1 << endl; // 将一系列变量的值写入文件

		in.close();
	}

	//========================================================售出商品信息存入文本文件中的函数
	void Sold_out()
	{
		fstream in("C:\\Users\\28432\\Desktop\\综合课设\\2109060106-董妍-录像带商店进销存信息管理系统\\vid\\vid\\库存商品1.txt", ios::out | ios::app);
		in << code << " " << name << " " << price << " " << price1 << " " << amount << " " << date_year1 << " " << date_month1 << " " << date_day1 << endl;

		in.close();
	}

};
//==========================================================定义重写入文件的函数（文件内容被修改时使用）
void Rewrite_in1();
void Rewrite_out1();
product *head = NULL, *head2 = NULL;//head用于库存文件，head2用于出售文件

//============================================================商品进货
int Jinhuo()
{
	bool over = false;  //声明一个布尔变量来判断
	product *s_head, *ptr;
	s_head = new product;    //建立一个对象
	s_head->Accept();      //输入商品信息
	s_head->Store_in();    //将数据写入文本文件
	s_head->next = NULL;
	ptr = s_head;
	while (1)
	{
		cout << "该商品已入存！" << endl;
		cout << "是否要继续存入商品？继续请输入 1 /返回主菜单请输入 2 :";
		do {
			cin >> num;
			if (num == '2')
			{
				over = true; break;
			}
			else if (num == '1')//头插法
			{
				ptr = new product;
				ptr->Accept();
				ptr->Store_in();
				ptr->next = s_head;
				s_head = ptr;
				break;
			}
			else
				cout << "输入错误！请重新输入：";
		} while (1);
		if (over) break;
	}
	if (head == NULL)
	{
		head = s_head;
	}
	else//文件内容不为空，尾插法
	{
		ptr = s_head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = head;
		head = s_head;
	}
	Rewrite_in1();
	system("cls");
	return 0;
}
//===========================================================录像带商品补货
int Buhuo()
{
	product *ptr = NULL;
	char keyword[30];
	bool out = false;
	ptr = head;
	int num2;
	do {
		cout << "请输入要补充的商品的名称或编号：";
		cin >> keyword;
		do {
			while (ptr)
			{
				if (strcmp(keyword, ptr->name) == 0 || strcmp(keyword, ptr->code) == 0)
					break;
				else  ptr = ptr->next;
			}
			if (!ptr)
			{
				cout << "对不起！没有该商品！" << endl;
				cout << "换词查找 1 /其他数字键则返回修改菜单：";
				cin >> num;
				if (num != '1')
				{
					system("cls");
					return 0;
				}
				else break;
			}
			else
			{
				cout << "找到以下商品！" << endl;
				ptr->Display(1);
				cout << "    是否补充？是 1 /查找下一批 2 /否则输入其他任意键:";
				cin >> num;
				if (num == '1')
				{
					do {
						cout << "请输入补货的数量：";
						cin >> num2;
						ptr->amount = ptr->amount + num2;  //将增加的数量同库存数量相加
						Rewrite_in1();
						Rewrite_out1();
						cout << "                           补货成功！" << endl;
						cout << "      继续补货？是输入 1 /跟换商品补货输入 2 /输入其他则返回修改菜单：";
						cin >> num;
						if (num == '2')
						{
							out = true;
							system("cls"); break;
						}
						else if (num != '1')
						{
							system("cls");
							return 1;
						}
					} while (1);
				}
				else if (num == '2')
				{
					ptr = ptr->next;
				}
				else
				{
					cout << "您已决定不补货！请输入任意键返回修改菜单：";
					cin >> num;
					system("cls");
					return 0;
				}
			}
			if (out)
				break;
		} while (1);
	} while (1);
}
//======================================================Shouhuo(1)商品出售，Shouhuo(2)商品退换
int Shouhuo(int ch)
{
	product *ptr = NULL;
	int num1;
	product *o, *ptr_b;
	o = head;
	int count;
	char keyword[30];
	bool out = false;
	if (ch == 1)
		ptr_b = ptr = head;
	else if (ch == 2)
		ptr = head2;
	do {
		if (ch == 1)
			cout << "请输入要出售的商品的名称或编号：";
		else if (ch == 2)
			cout << "请输入要退换的商品的名称或编号：";
		cin >> keyword;
		do {
			while (ptr)
			{
				if (strcmp(keyword, ptr->name) == 0 || strcmp(keyword, ptr->code) == 0)
				{
					count = ptr->amount;
					break;
				}
				ptr = ptr->next;
			}
			if (!ptr)
			{
				cout << "对不起！没有该商品！" << endl;
				cout << "换词查找 1 /其他数字键则返回修改菜单：";
				cin >> num;
				if (num != '1')
				{
					system("cls");
					return 0;
				}
				else break;
			}
			else
			{
				cout << "找到以下商品！" << endl;
				ptr->Display(ch);
				if (ch == 1)
					cout << "    是否出售？是 1 /查找下一批 2 /否则输入其他任意键:";
				else if (ch == 2)
					cout << "    是否退换？是 1 /查找下一批 2 /否则输入其他任意键:";
				cin >> num;
				if (num == '1')
				{
					cout << "请输入的数量：";
					do {
						cin >> num1;

						if (num1 > count)
						{
							if (ch == 1)
							{
								cout << "抱歉！该商品不足" << num1 << "件！最多只能出售" << count << "件！" << endl;
								cout << "请重新输入出售数量（输入0则退回主菜单）：";
							}
							else
							{
								cout << "抱歉！该商品不足" << num1 << "件！最多只能退换" << count << "件！" << endl;
								cout << "请重新输入退换数量（输入0则退回主菜单）：";
							}
							continue;
						}
						else if (num1 <= 0)
						{
							system("cls"); return 0;
						}
						else
						{
							if (ch == 1)
							{
								ptr->amount -= num1;
								ptr_b = new product;        //建立一个新对象，用来出售商品
								strcpy_s(ptr_b->code, ptr->code);
								strcpy_s(ptr_b->name, ptr->name);

								ptr_b->date_year1 = ptr->date_year1;
								ptr_b->date_month1 = ptr->date_month1;
								ptr_b->date_day1 = ptr->date_day1;

								ptr_b->price = ptr->price;
								ptr_b->price1 = ptr->price1;
								ptr_b->amount = num;
								cout << "请输入出售日期：" << endl;
								scanf_s("%d-%d-%d", &ptr_b->date_year1, &ptr_b->date_month1, &ptr_b->date_day1);
								ptr_b->next = head2;
								head2 = ptr_b;
								cout << "━━━━━━━━━━━━━━━━━━━━━━━" << endl;
								cout << "   本次交易成功售出" << num1 << "件该商品" << endl;
								cout << "   本次交易收入为" << num1 * (ptr->price1 - ptr->price) << "元" << endl;;
								cout << "━━━━━━━━━━━━━━━━━━━━━━━" << endl;
							}
							else
							{
								ptr->amount -= num1;   //从出售表中减去
								o->amount += num1;     //加入到库存表中
								cout << "━━━━━━━━━━━━━━━━━━━━━━━" << endl;
								cout << "   本次交易成功退换" << num1 << "件该商品" << endl;
								cout << "   本次交易亏损为" << num1 * (ptr->price1 - ptr->price) << "元" << endl;;
								cout << "━━━━━━━━━━━━━━━━━━━━━━━" << endl;
							}
							Rewrite_in1();
							Rewrite_out1();
							cout << "              " << endl;
							cout << "    操作成功！" << endl;
							cout << "              " << endl;
							cout << "继续返回操作菜单输入 1 /更换商品输入 2 ";
							cin >> num;
							if (num == '2')
							{
								out = true;
								system("cls"); break;
							}
							else if (num == '1')
							{
								system("cls");
								return 1;
							}
						}
					} while (1);
				}
				else if (num == '2')
				{
					ptr = ptr->next;
				}
				else
				{
					if (ch == 1)
						cout << "您已决定不出售该商品！请输入任意键返回出售菜单：";
					else if (ch == 2)
						cout << "您已决定不退换该商品！请输入任意键返回退换菜单：";
					cin >> num;
					system("cls");
					return 0;
				}
			}
			if (out)
				break;
		} while (1);
	} while (1);
}
//==========================================Chakanl(1)库存商品信息查看，Chakan(2)出售商品信息查看，浏览整理商品
int Chakan(int ch)
{
	int count = 0;
	product *ptr=NULL;
	if (ch == 1)
		ptr = head;//指向库存商品
	else if (ch == 2)
		ptr = head2;//指向出售商品
	if (ptr == NULL)
	{
		if (ch == 1)
			cout << "        目前没有库存商品！请存入后再查看！ 请输入任意数字键返回查看菜单：   " << endl;
		else if (ch == 2)
			cout << "        目前没有出售商品！请出售后再查看！ 请输入任意数字键返回查看菜单：  " << endl;
		cin >> num;
		system("cls");
	}
	else
	{
		while (ptr != NULL)
		{
			count++;
			cout << count << '.' << endl;
			if (ch == 1)
				ptr->Display(1);
			else if (ch == 2)
				ptr->Display(2);
			ptr = ptr->next;
		}
		cout << "    " << endl;
		cout << "以上即为所有查询到的商品！请输入任意数字键返回查看菜单：";
		cin >> num;
		system("cls");
	}
	return 0;
}
//===========================================================商品信息检索，查询具体商品
int Chaxun()
{
	char keyword[30];
	product *ptr;
	int count = 0;
	do {
		cout << "请输入您要搜索的商品的名称或编号：";
		cin >> keyword;
		ptr = head;
		while (ptr != NULL)
		{
			if (strstr(ptr->name, keyword) || strstr(ptr->code, keyword))
				count++;
			ptr = ptr->next;
		}
		cout << "共找到" << count << "批可能的库存商品！" << endl;
		if (count != 0)
		{
			ptr = head;
			count = 0;
			while (ptr != NULL)
			{
				if (strstr(ptr->name, keyword) || strstr(ptr->code, keyword))
				{
					count++;
					cout << count << '.' << endl;
					ptr->Display(1);
				}
				ptr = ptr->next;
			}
		}
		count = 0;
		ptr = head2;
		while (ptr != NULL)
		{
			if (strstr(ptr->name, keyword) || strstr(ptr->code, keyword))
				count++;
			ptr = ptr->next;
		}
		cout << "共找到" << count << "批可能的已售出商品！" << endl;
		if (count != 0)
		{
			ptr = head2;
			count = 0;
			while (ptr != NULL)
			{
				if (strstr(ptr->name, keyword) || strstr(ptr->code, keyword))
				{
					count++;
					cout << count << '.' << endl;
					ptr->Display(2);
				}
				ptr = ptr->next;
			}
		}
		cout << "             是否继续？继续 1 /任意数字键返回主菜单 ： ";
		do {
			cin >> num;
			if (num != '1')
			{
				system("cls"); return 0;
			}
			else
			{
				system("cls"); break;
			}
		} while (1);
	} while (1);
}

//=========================================================商品信息删除
void Shanchu(int ch)
{
	char del_word[30];
	product *ptr, *ptr_b=NULL;
	bool back = false;
	if (ch == 1)
		ptr = head;     //指向库存表
	else
		ptr = head2;    //指向出售表
	do {
		cout << "请输入要删除的商品的名称或编号：";
		cin >> del_word;
		do {
			while (ptr)
			{
				if (strcmp(del_word, ptr->name) == 0 || strcmp(del_word, ptr->code) == 0)   //输入的名称和编号与ptr中相符，查找成功跳出while
				{
					break;
				}
				ptr_b = ptr;             //使用strcmp 函数不为0时查找失败，ptr指向下一结点
				ptr = ptr->next;
			}
			if (ptr)
			{
				cout << "找到以下商品：" << endl;
				ptr->Display(ch);
				cout << "是否删除" << ptr->name << "的信息?是 1 /否 2 /寻找下一批 3 ：";
				do {
					cin >> num;
					if (num == '1')
					{
						if (ptr == head)        //删除的是库存商品的头结点
						{
							head = head->next;
							delete ptr;
						}
						else if (ptr == head2)  //删除的是售出商品的头结点
						{
							head2 = head2->next;
							delete ptr;
						}
						else                 //删除的不是头结点
						{
							ptr_b->next = ptr->next;
							delete ptr;
						}
						cout << "已成功删除该商品的信息！请按任意键 返回删除菜单：" << endl;
						cin >> num;
						return;
					}
					else if (num == '2')
					{
						cout << "您已决定不删除该商品信息！请按任意键返回删除菜单：";
						cin >> num;
						return;
					}
					else if (num == '3')
					{
						system("cls");
						ptr_b = ptr;
						ptr = ptr->next;
						break;
					}
					else cout << "\a亲！您的输入有误哦！请重新输入：";
				} while (1);
			}
			else
			{
				cout << "I'm sorry!没有找到您输入的商品！" << endl;
				cout << "是否重新输入？是   1  /  按   返回删除菜单：";
				cin >> num;
				if (num != '1')
				{
					back = true;
					break;
				}
				else break;
			}
		} while (1);
		if (back) break;
	} while (1);
}
//==========================================================商品信息修改
int Xiugai(int ch)//xiugai（1）修改库存商品信息，xiugai（2）修改出售商品信息
{
	product *ptr = NULL;
	char keyword[30];
	bool out = false;
	if (ch == 1)
		ptr = head;
	else if (ch == 2)
		ptr = head2;
	do {
		cout << "请输入要修改的商品的名称或编号：";
		cin >> keyword;
		do {
			while (ptr)
			{
				if (strcmp(keyword, ptr->name) == 0 || strcmp(keyword, ptr->code) == 0)
					break;
				ptr = ptr->next;
			}
			if (!ptr)
			{
				cout << "对不起！没有该商品！" << endl;
				cout << "换词查找 1 /其他数字键则返回修改菜单：";
				cin >> num;
				if (num != '1')
				{
					system("cls");
					return 0;
				}
				else break;
			}
			else
			{
				cout << "找到以下商品！" << endl;
				ptr->Display(ch);
				cout << "    是否修改？是 1 /查找下一批 2 /否则输入其他任意键:";
				cin >> num;
				if (num == '1')
				{
					cout << "  " << endl;
					cout << "|1.全部| 2.编号|3.名称|4.进货价|5.出售价  |" << endl;
					cout << "   " << endl;
					cout << "| 6.数量| 7.进货日期|" << endl;
					cout << "            " << endl;
					do {
						cout << "请输入要修改的项目(输入0则不修改)：";
						cin >> num;
						switch (num)
						{
						case '1':cout << "请输入商品的全部新信息：" << endl;
							ptr->Accept(); break;
						case '2':cout << "请输入商品的新编号：";
							cin >> ptr->code; break;
						case '3':cout << "请输入商品的新名称：";
							cin >> ptr->name; break;
						case '4':cout << "请输入商品的新进货价：";
							cin >> ptr->price; break;
						case '5':cout << "请输入商品的新出售价：";
							cin >> ptr->price1; break;
						case '7':cout << "请输入商品的新数量：";
							cin >> ptr->amount; break;
						case '9':cout << "请输入商品的新进货日期(****-**-**)：";
							scanf_s("%d-%d-%d", &ptr->date_year1, &ptr->date_month1, &ptr->date_day1); break;
						case '0':return 1;
						default:cout << "您已选择不修改该商品信息！请按任意键返回修改菜单：";
							cin >> num; return 1;
						}
						Rewrite_in1();
						Rewrite_out1();
						cout << "                    修改成功！" << endl;
						cout << "返回修改界面输入 1 ； 跟换商品修改输入 2 ：";
						cin >> num;
						if (num == '2')
						{
							out = true;
							system("cls"); break;
						}
						else if (num == '1')
						{
							system("cls");
							return 1;
						}
					} while (1);
				}
				else if (num == '2')
				{
					ptr = ptr->next;
				}
				else
				{
					cout << "您已决定不修改该商品的信息！请输入任意键返回修改菜单：";
					cin >> num;
					system("cls");
					return 0;
				}
			}
			if (out)
				break;
		} while (1);
	} while (1);
}
//===========================================================商品信息修改菜单
int Xiougai_d()
{
	int sh;
	do {
		cout << "                            修改菜单                       " << endl;
		cout << "                                                         " << endl;
		cout << "|1.修改库存商品信息；|2.修改已售出商品信息；|3.返回主菜单|" << endl;
		cout << "                                                          " << endl;
		cout << "请选择你要的操作（请使用数字键，使用其他会出错）：";
		do {
			cin >> sh;
			if (sh == 3)
			{
				system("cls");
				return 0;
			}
			else if (sh != 1 && sh != 2)
			{
				cout << "输入有误！请重新输入：";
				continue;
			}
			else
			{
				Xiugai(sh);
				break;
			}
		} while (1);
	} while (1);
}
//=============================================================删除菜单
void Shanchu_d()
{
	bool back = false;
	do {
		cout << "                                     " << endl;
		cout << "                 |  删除菜单  |" << endl;
		cout << "                                      " << endl;
		cout << "                                                          " << endl;
		cout << "|1.删除库存商品信息；|2.删除已售出商品信息；|3.返回主菜单|" << endl;
		cout << "                                                          " << endl;
		cout << "请选择你要的操作：";
		do {
			cin >> num;
			if (num == '1')
			{
				Shanchu(1);
				system("cls"); break;
			}
			else if (num == '2')
			{
				Shanchu(2);
				system("cls"); break;
			}
			else if (num == '3')
			{
				back = true; break;
			}
			else
			{
				cout << "您的输入有误！请重新输入：";
			}
		} while (1);
		if (back)
		{
			Rewrite_in1();
			Rewrite_out1();
			system("cls"); break;
		}
	} while (1);
}
//=============================================================查看菜单
int Chakan_d()
{
	int Chaxun();
	do {
		cout << "                                      " << endl;
		cout << "              |     查看菜单   |" << endl;
		cout << "                                      " << endl;
		cout << "                                                  " << endl;
		cout << "|1.查看所有库存商品信息；|2.查看已出售商品信息；|" << endl;
		cout << "                                                 " << endl;
		cout << "|3.查找商品信息；        |4.返回主菜单          |" << endl;

		cout << "┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈" << endl;
		cout << "请选择您的查看方式：";
	C_input:
		cin >> num;
		switch (num)
		{
		case '1':system("cls"); Chakan(1); break;
		case '2':system("cls"); Chakan(2); break;
		case '3':system("cls"); Chaxun(); break;
		case '4':system("cls"); return 0;
		default:cout << "你的输入有误哦！请重新输入："; goto C_input;
		}
	} while (1);
}
int Read_in()
{
	product* head = nullptr, * ptr_b = nullptr;
	fstream f;
	f.open("C:\\Users\\28432\\Desktop\\综合课设\\2109060106-董妍-录像带商店进销存信息管理系统\\vid\\vid\\库存商品1.txt", ios::in );
	//ios::in 表示以输入方式打开文件，可以读取文件中的数据。
	if (!f)
		return 0;
	product temp; // 临时存储读取的数据
	while (f.read((char*)&temp, sizeof(product)))
	{
		if (temp.amount <= 0)
		{
			// 如果数量小于等于0，则跳过
		}
		else
		{
			product* ptr = new product; // 为当前数据分配新的内存
			*ptr = temp; // 将临时数据拷贝到新分配的内存空间
			ptr->next = nullptr;//尾插
			if (head == nullptr)
			{
				head = ptr;
				ptr_b = ptr;
			}
			else
			{
				ptr_b->next = ptr;
				ptr_b = ptr;
			}
		}
	}
	f.close();
	return 0;
}






//==========================================================从文件中读取售出商品信息的函数
int Read_sold()
{
	product* head2 = nullptr; // 新增链表头指针
	product* ptr_b = nullptr;
	product* ptr = nullptr;
	fstream f;
	f.open("C:\\Users\\28432\\Desktop\\综合课设\\2109060106-董妍-录像带商店进销存信息管理系统\\vid\\vid\\售出商品1.txt", ios::in );
	//ios::in 表示以输入方式打开文件，可以读取文件中的数据。
	if (!f)
		return 0;

	while (f.read((char*)&ptr, sizeof(product))) // 读取数据到临时变量ptr
	{
		if (ptr->amount <= 0) // 排除数量小于等于0的商品
		{
			delete ptr; // 释放内存
			ptr = nullptr; // 置空指针
		}
		else
		{
			ptr->next = nullptr;
			if (head2 == nullptr)
			{
				head2 = ptr;
				ptr_b = ptr;
			}
			else
			{
				ptr_b->next = ptr;
				ptr_b = ptr;
			}
		}
		ptr = nullptr; // 重置临时指针
	}
	f.close();
	return 0;
}


//=========================================================库存商品信息重新写入文本文件
void Rewrite_in1()
{
	fstream in("C:\\Users\\28432\\Desktop\\综合课设\\2109060106-董妍-录像带商店进销存信息管理系统\\vid\\vid\\库存商品1.txt", ios::out);
	//ios::out 模式，这意味着每次写入数据时会清空文件内容并重新写入新的数据。
	if (!in)
	{
		cout << "无法打开文件" << endl;
		return;
	}
	product* ptr;
	ptr = head;
	while (ptr)
	{
		in << setw(10) << left << ptr->code << " " // 指定字段宽度和对齐方式
			<< setw(20) << left << ptr->name << " "
			<< setw(10) << right << ptr->price << " "
			<< setw(10) << right << ptr->price1 << " "
			<< setw(10) << right << ptr->amount << " "
			<< setw(4) << right << ptr->date_year1 << "/" // 将年、月、日用斜杠分隔开
			<< setw(2) << setfill('0') << ptr->date_month1 << "/"
			<< setw(2) << setfill('0') << ptr->date_day1 << endl;

		ptr = ptr->next;
	}
	in.close();
}

//=========================================================售出商品信息重新写入文本文件
void Rewrite_out1()
{
	fstream in("C:\\Users\\28432\\Desktop\\综合课设\\2109060106-董妍-录像带商店进销存信息管理系统\\vid\\vid\\售出商品1.txt", ios::out);
	if (!in)
	{
		cout << "无法打开文件" << endl;
		return;
	}
	product* ptr;
	ptr = head2;
	while (ptr)
	{
		in << setw(10) << left << ptr->code << " "
			<< setw(20) << left << ptr->name << " "
			<< setw(10) << right << ptr->price << " "
			<< setw(10) << right << ptr->price1 << " "
			<< setw(10) << right << ptr->amount << " "
			<< setw(4) << right << ptr->date_year1 << "/"
			<< setw(2) << setfill('0') << ptr->date_month1 << "/"
			<< setw(2) << setfill('0') << ptr->date_day1 << endl;

		ptr = ptr->next;
	}
	in.close();
}


//===============================================================主函数===========================================================
int main()
{
	Read_in();
	Read_sold();
	cout << "                              *录像带进销存管理系统*                   " << endl;
	cout << "                                                                          " << endl;;
	do {
	
		cout << "                                【 主菜单 】                             " << endl;
		
	
		cout << "|0.商品进货    |1.商品补货    | 2.商品售出   |3.商品退货    |" << endl;
		cout << "|4.查看商品信息|5.修改商品信息|6.删除商品信息|7.退出 " << endl;
		cout << "  " << endl;
		cout << "请选择您需要的服务：";
		cin >> num;
		switch (num)
		{
		case'0':system("cls"); Jinhuo(); break;
		case'1':system("cls"); Buhuo(); break;
		case'2':system("cls"); Shouhuo(1); break;
		case'3':system("cls"); Shouhuo(2); break;
		case'4':system("cls"); Chakan_d(); break;
		case'5':system("cls"); Xiougai_d(); break;
		case'6':system("cls"); Shanchu_d(); break;		
		case'7':Rewrite_in1();
			Rewrite_out1();
			cout << "          ◆◆◆◆◆◆◆感谢您使用本系统◆◆◆◆◆◆◆" << endl;
			cout << "          ◆◆◆◆◆◆◆期待您的再次光临◆◆◆◆◆◆◆" << endl << endl;
			return 0;
		}
	} while (1);
	return 0;
}