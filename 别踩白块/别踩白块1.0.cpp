//#include<iostream>
//#include<easyx.h>
//#include<time.h>
//#include<stdlib.h>
//using namespace std;
//int flag[4];
////ͳ�Ʒ���
//int score = 0;
//void init() 
//{
//	srand(time(NULL));
//	//������ɺڿ�
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
//		//������
//		line(0, i*150+100, 400, i*150+100);
//		//������
//		line(i * 100, 100, i * 100, 700);
//	}
//	
//	//�������
//	const char *text = "��Ȱ׿�";
//	settextstyle(30, 0, "΢���ź�");
//	settextcolor(BLACK);
//	int w = (getwidth() - textwidth(text)) / 2;
//	int h = (100 - textheight(text)) / 2;
//	outtextxy(w, h, text);
//	//���ƺڿ�
//	setfillcolor(BLACK);
//	for (int i = 0; i < 4; i++) {
//		int x=flag[i]*100;
//		int y=i*150+100;
//		fillrectangle(x, y, x + 100, y + 150);
//	}
//	//�������
//	settextstyle(26, 0, "΢���ź�");
//	char arr[30] = { 0 };
//	sprintf_s(arr, "����:%d", score);
//	outtextxy(20,40,arr);
//}
////���������
//bool mousepress(ExMessage* mes)
//{
//	//�жϵ����Χ
//	int x = flag[3] * 100;
//	int y = 3 * 150 + 100;
//	if (mes->x > x && mes->x<=x + 100 && mes->y>y && mes->y <= y + 150)
//	{
//		//������ƶ�
//		for (int i = 3; i > 0; i--) {
//				flag[i] = flag[i - 1];
//			}
//		flag[0] = rand() % 4;
//		//cout << "�������ȷ�ĺڿ�" << endl;
//		score++;//�����ۼ�
//		return true;
//	}
//	return false;
//}
//int main()
//{
//	//ͼ�δ���
//	initgraph(400, 700, EX_SHOWCONSOLE);
//	//���ñ�����ɫ
//	setbkcolor(WHITE);
//	cleardevice();
//	setbkmode(TRANSPARENT);
//	init();
//	draw();
//	//��Ϸѭ��
//	bool decide = false;
//	while (!decide)
//	{
//		//����ڿ�
//		ExMessage mes = { 0 };
//		if (peekmessage(&mes))
//		{
//			//ESC�˳���Ϸ
//			switch (mes.message)
//			{
//			case WM_KEYDOWN:
//				if (mes.vkcode == VK_ESCAPE)
//				{
//					cout << "��Ϸ����" << endl;
//					decide = true;
//					return 0;
//				}
//				break;
//			case WM_LBUTTONDOWN:
//				!mousepress(&mes);
//				break;
//			}
//		}
//		//�ڿ��ƶ�
//		BeginBatchDraw();
//		cleardevice();//����
//		draw();
//		EndBatchDraw();
//	}
//	getchar();
//	return 0;
//}