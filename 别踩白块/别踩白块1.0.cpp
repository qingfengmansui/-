//#include<iostream>
//#include<easyx.h>
//#include<time.h>
//#include<stdlib.h>
//using namespace std;
//int flag[4];
////统计分数
//int score = 0;
//void init() 
//{
//	srand(time(NULL));
//	//随机生成黑块
//	for (int i = 0; i < 4; i++) {
//		flag[i] = rand() % 4;
//	}
//}
//
//void draw()
//{
//	setlinestyle(PS_SOLID, 1);
//	setlinecolor(BLACK);
//	for (int i = 0; i < 5; i++) 
//	{
//		//画横线
//		line(0, i*150+100, 400, i*150+100);
//		//画竖线
//		line(i * 100, 100, i * 100, 700);
//	}
//	
//	//标题输出
//	const char *text = "别踩白块";
//	settextstyle(30, 0, "微软雅黑");
//	settextcolor(BLACK);
//	int w = (getwidth() - textwidth(text)) / 2;
//	int h = (100 - textheight(text)) / 2;
//	outtextxy(w, h, text);
//	//绘制黑块
//	setfillcolor(BLACK);
//	for (int i = 0; i < 4; i++) {
//		int x=flag[i]*100;
//		int y=i*150+100;
//		fillrectangle(x, y, x + 100, y + 150);
//	}
//	//输出分数
//	settextstyle(26, 0, "微软雅黑");
//	char arr[30] = { 0 };
//	sprintf_s(arr, "分数:%d", score);
//	outtextxy(20,40,arr);
//}
////处理鼠标点击
//bool mousepress(ExMessage* mes)
//{
//	//判断点击范围
//	int x = flag[3] * 100;
//	int y = 3 * 150 + 100;
//	if (mes->x > x && mes->x<=x + 100 && mes->y>y && mes->y <= y + 150)
//	{
//		//点击后移动
//		for (int i = 3; i > 0; i--) {
//				flag[i] = flag[i - 1];
//			}
//		flag[0] = rand() % 4;
//		//cout << "点击了正确的黑块" << endl;
//		score++;//分数累计
//		return true;
//	}
//	return false;
//}
//int main()
//{
//	//图形窗口
//	initgraph(400, 700, EX_SHOWCONSOLE);
//	//设置背景颜色
//	setbkcolor(WHITE);
//	cleardevice();
//	setbkmode(TRANSPARENT);
//	init();
//	draw();
//	//游戏循环
//	bool decide = false;
//	while (!decide)
//	{
//		//点击黑块
//		ExMessage mes = { 0 };
//		if (peekmessage(&mes))
//		{
//			//ESC退出游戏
//			switch (mes.message)
//			{
//			case WM_KEYDOWN:
//				if (mes.vkcode == VK_ESCAPE)
//				{
//					cout << "游戏结束" << endl;
//					decide = true;
//					return 0;
//				}
//				break;
//			case WM_LBUTTONDOWN:
//				!mousepress(&mes);
//				break;
//			}
//		}
//		//黑块移动
//		BeginBatchDraw();
//		cleardevice();//清屏
//		draw();
//		EndBatchDraw();
//	}
//	getchar();
//	return 0;
//}