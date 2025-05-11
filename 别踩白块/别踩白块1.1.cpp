//#include <iostream>
//#include <graphics.h>
//#include <time.h>
//#include <stdlib.h>
//using namespace std;
//
//// 游戏配置常量
//const int BLOCK_WIDTH = 100;
//const int BLOCK_HEIGHT = 150;
//const int WINDOW_WIDTH = 400;
//const int WINDOW_HEIGHT = 700;
//const int TITLE_AREA_HEIGHT = 100;
//const int GAME_AREA_HEIGHT = 600;
//const int GAME_TIME_LIMIT = 30;  // 游戏时间限制(秒)
//
//// 游戏状态枚举
//enum GameState {
//    RUNNING,
//    PAUSED,
//    GAME_OVER,
//    GAME_COMPLETED
//};
//
//class Game {
//private:
//    int flag[4];        // 存储每一行黑块的位置
//    int score;          // 分数
//    GameState state;    // 游戏状态
//    clock_t startTime;  // 游戏开始时间
//    int remainingTime;  // 剩余时间(秒)
//    bool timeUpdated;   // 时间是否已更新
//
//public:
//    Game() : score(0), state(RUNNING), remainingTime(GAME_TIME_LIMIT), timeUpdated(false) {
//        srand(time(NULL));
//        init();
//        startTime = clock();
//    }
//
//    // 初始化游戏
//    void init() {
//        // 随机生成黑块
//        for (int i = 0; i < 4; i++) {
//            flag[i] = rand() % 4;
//        }
//    }
//
//    // 绘制游戏界面
//    void draw() {
//        // 清屏
//        setbkcolor(WHITE);
//        cleardevice();
//
//        // 设置绘图样式
//        setlinestyle(PS_SOLID, 2);
//        setlinecolor(BLACK);
//
//        // 绘制网格
//        for (int i = 0; i <= 4; i++) {
//            // 画横线
//            line(0, i * BLOCK_HEIGHT + TITLE_AREA_HEIGHT, WINDOW_WIDTH, i * BLOCK_HEIGHT + TITLE_AREA_HEIGHT);
//            // 画竖线
//            line(i * BLOCK_WIDTH, TITLE_AREA_HEIGHT, i * BLOCK_WIDTH, WINDOW_HEIGHT);
//        }
//
//        // 标题输出
//        const char* title = "别踩白块";
//        settextstyle(36, 0, "微软雅黑", 0, 0, 700, false, false, false);
//        settextcolor(BLACK);
//        int titleW = (WINDOW_WIDTH - textwidth(title)) / 2;
//        int titleH = (TITLE_AREA_HEIGHT - textheight(title)) / 2;
//        outtextxy(titleW, titleH, title);
//
//        // 绘制黑块
//        setfillcolor(BLACK);
//        for (int i = 0; i < 4; i++) {
//            int x = flag[i] * BLOCK_WIDTH;
//            int y = i * BLOCK_HEIGHT + TITLE_AREA_HEIGHT;
//            fillrectangle(x, y, x + BLOCK_WIDTH, y + BLOCK_HEIGHT);
//        }
//
//        // 输出分数
//        settextstyle(26, 0, "微软雅黑");
//        char scoreText[30] = { 0 };
//        sprintf_s(scoreText, "分数: %d", score);
//        outtextxy(20, 40, scoreText);
//
//        // 输出剩余时间
//        char timeText[30] = { 0 };
//        sprintf_s(timeText, "剩余时间: %d秒", remainingTime);
//        outtextxy(WINDOW_WIDTH - textwidth(timeText) - 20, 40, timeText);
//
//        // 输出游戏状态
//        if (state == PAUSED) {
//            const char* pauseText = "游戏暂停";
//            settextcolor(RED);
//            int pauseW = (WINDOW_WIDTH - textwidth(pauseText)) / 2;
//            int pauseH = (WINDOW_HEIGHT - textheight(pauseText)) / 2;
//            outtextxy(pauseW, pauseH, pauseText);
//        }
//        else if (state == GAME_OVER) {
//            const char* gameOverText = "游戏结束";
//            const char* finalScoreText = "最终得分: ";
//            sprintf_s(scoreText, "%s%d", finalScoreText, score);
//            const char* restartText = "按R键重新开始";
//
//            settextcolor(RED);
//            int overW = (WINDOW_WIDTH - textwidth(gameOverText)) / 2;
//            int overH = (WINDOW_HEIGHT - textheight(gameOverText) * 3) / 2;
//
//            outtextxy(overW, overH, gameOverText);
//            outtextxy(overW, overH + 50, scoreText);
//            outtextxy(overW, overH + 100, restartText);
//        }
//        else if (state == GAME_COMPLETED) {
//            const char* completedText = "挑战成功!";
//            const char* finalScoreText = "最终得分: ";
//            sprintf_s(scoreText, "%s%d", finalScoreText, score);
//            const char* restartText = "按R键重新开始";
//
//            settextcolor(GREEN);
//            int overW = (WINDOW_WIDTH - textwidth(completedText)) / 2;
//            int overH = (WINDOW_HEIGHT - textheight(completedText) * 3) / 2;
//
//            outtextxy(overW, overH, completedText);
//            outtextxy(overW, overH + 50, scoreText);
//            outtextxy(overW, overH + 100, restartText);
//        }
//    }
//
//    // 处理鼠标点击
//    bool handleMouseClick(ExMessage* mes) {
//        if (state != RUNNING) return false;
//
//        // 判断点击范围
//        int x = flag[3] * BLOCK_WIDTH;
//        int y = 3 * BLOCK_HEIGHT + TITLE_AREA_HEIGHT;
//
//        if (mes->x > x && mes->x <= x + BLOCK_WIDTH && mes->y > y && mes->y <= y + BLOCK_HEIGHT) {
//            // 点击了正确的黑块
//            moveBlocks();
//            score++;
//            return true;
//        }
//        else {
//            // 点击了白块，游戏结束
//            state = GAME_OVER;
//            return false;
//        }
//    }
//
//    // 移动方块
//    void moveBlocks() {
//        // 方块下移
//        for (int i = 3; i > 0; i--) {
//            flag[i] = flag[i - 1];
//        }
//        flag[0] = rand() % 4;
//    }
//
//    // 处理键盘事件
//    void handleKeyPress(ExMessage* mes) {
//        switch (mes->vkcode) {
//        case VK_ESCAPE:
//            state = (state == RUNNING) ? PAUSED : RUNNING;
//            if (state == RUNNING) {
//                startTime = clock() - (GAME_TIME_LIMIT - remainingTime) * CLOCKS_PER_SEC;
//            }
//            break;
//        case 'R':
//        case 'r':
//            if (state == GAME_OVER || state == GAME_COMPLETED) {
//                resetGame();
//            }
//            break;
//        }
//    }
//
//    // 重置游戏
//    void resetGame() {
//        score = 0;
//        remainingTime = GAME_TIME_LIMIT;
//        timeUpdated = false;
//        init();
//        state = RUNNING;
//        startTime = clock();
//    }
//
//    // 更新游戏状态
//    void update() {
//        if (state != RUNNING) return;
//
//        // 更新剩余时间
//        clock_t currentTime = clock();
//        int elapsedSeconds = static_cast<int>((currentTime - startTime) / CLOCKS_PER_SEC);
//        int newRemainingTime = GAME_TIME_LIMIT - elapsedSeconds;
//
//        if (newRemainingTime != remainingTime) {
//            remainingTime = newRemainingTime;
//            timeUpdated = true;
//
//            if (remainingTime <= 0) {
//                remainingTime = 0;
//                state = GAME_COMPLETED;
//            }
//        }
//        else {
//            timeUpdated = false;
//        }
//    }
//
//    // 获取游戏状态
//    GameState getState() const {
//        return state;
//    }
//
//    // 检查时间是否更新
//    bool hasTimeUpdated() const {
//        return timeUpdated;
//    }
//};
//
//int main() {
//    // 创建图形窗口
//    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, EX_SHOWCONSOLE);
//
//    // 创建游戏对象
//    Game game;
//
//    // 启用批量绘图，减少闪烁
//    BeginBatchDraw();
//
//    // 游戏主循环
//    bool exitGame = false;
//    while (!exitGame) {
//        // 更新游戏状态
//        game.update();
//
//        // 绘制游戏界面
//        game.draw();
//        FlushBatchDraw();
//
//        // 处理消息
//        ExMessage mes = { 0 };
//        while (peekmessage(&mes)) {
//            switch (mes.message) {
//            case WM_KEYDOWN:
//                game.handleKeyPress(&mes);
//                if (mes.vkcode == VK_ESCAPE && game.getState() == PAUSED) {
//                    exitGame = true;
//                }
//                break;
//            case WM_LBUTTONDOWN:
//                game.handleMouseClick(&mes);
//                break;
//            case WM_CLOSE:
//                exitGame = true;
//                break;
//            }
//        }
//
//        // 延时，控制CPU使用率
//        Sleep(10);
//    }
//
//    EndBatchDraw();
//    closegraph();
//    return 0;
//}