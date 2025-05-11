#include <iostream>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>  // �����ý���
#pragma comment(lib, "winmm.lib")  // ���Ӷ�ý���

// ��Ϸ��������
const int BLOCK_WIDTH = 100;
const int BLOCK_HEIGHT = 150;
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 700;
const int TITLE_AREA_HEIGHT = 100;
const int GAME_AREA_HEIGHT = 600;
const int GAME_TIME_LIMIT = 30;  // ��Ϸʱ������(��)

// ��Ϸ״̬ö��
enum GameState {
    RUNNING,
    PAUSED,
    GAME_OVER,
    GAME_COMPLETED
};

class Game {
private:
    int flag[4];        // �洢ÿһ�кڿ�λ��
    int score;          // �÷�
    GameState state;    // ��Ϸ״̬
    clock_t startTime;  // ��Ϸ��ʼʱ��
    int remainingTime;  // ʣ��ʱ��(��)
    bool timeUpdated;   // ʱ���Ƿ��Ѹ���

public:
    void playClickSound() {
        mciSendString(TEXT("play music.wav"), NULL, 0, NULL);
    }
    Game() : score(0), state(RUNNING), remainingTime(GAME_TIME_LIMIT), timeUpdated(false) {
        srand(time(NULL));
        init();
        startTime = clock();
    }

    // ��ʼ����Ϸ
    void init() {
        // ������ɺڿ�
        for (int i = 0; i < 4; i++) {
            flag[i] = rand() % 4;
        }
    }

    // ������Ϸ����
    void draw() {
        // ����
        setbkcolor(WHITE);
        cleardevice();

        // ���û�ͼ��ʽ
        setlinestyle(PS_SOLID, 2);
        setlinecolor(BLACK);

        // ��������
        for (int i = 0; i <= 4; i++) {
            // ���ƺ���
            line(0, i * BLOCK_HEIGHT + TITLE_AREA_HEIGHT, WINDOW_WIDTH, i * BLOCK_HEIGHT + TITLE_AREA_HEIGHT);
            // ��������
            line(i * BLOCK_WIDTH, TITLE_AREA_HEIGHT, i * BLOCK_WIDTH, WINDOW_HEIGHT);
        }

        // ���Ʊ���
        const char* title = "��Ȱ׿�";
        settextstyle(36, 0, "΢���ź�", 0, 0, 700, false, false, false);
        settextcolor(BLACK);
        int titleW = (WINDOW_WIDTH - textwidth(title)) / 2;
        int titleH = (TITLE_AREA_HEIGHT - textheight(title)) / 2;
        outtextxy(titleW, titleH, title);

        // ���ƺڿ�
        setfillcolor(BLACK);
        for (int i = 0; i < 4; i++) {
            int x = flag[i] * BLOCK_WIDTH;
            int y = i * BLOCK_HEIGHT + TITLE_AREA_HEIGHT;
            fillrectangle(x, y, x + BLOCK_WIDTH, y + BLOCK_HEIGHT);
        }

        // ���Ƶ÷�
        settextstyle(26, 0, "΢���ź�");
        char scoreText[30] = { 0 };
        sprintf_s(scoreText, "�÷�: %d", score);
        outtextxy(20, 40, scoreText);

        // ����ʣ��ʱ��
        char timeText[30] = { 0 };
        sprintf_s(timeText, "ʣ��ʱ��: %d��", remainingTime);
        outtextxy(WINDOW_WIDTH - textwidth(timeText) - 20, 40, timeText);

        // ������Ϸ״̬
        if (state == PAUSED) {
            const char* pauseText = "��Ϸ��ͣ";
            settextcolor(RED);
            int pauseW = (WINDOW_WIDTH - textwidth(pauseText)) / 2;
            int pauseH = (WINDOW_HEIGHT - textheight(pauseText)) / 2;
            outtextxy(pauseW, pauseH, pauseText);
        }
        else if (state == GAME_OVER) {
            const char* gameOverText = "��Ϸ����";
            const char* finalScoreText = "���յ÷�: ";
            sprintf_s(scoreText, "%s%d", finalScoreText, score);
            const char* restartText = "��R���¿�ʼ";

            settextcolor(RED);
            int overW = (WINDOW_WIDTH - textwidth(gameOverText)) / 2;
            int overH = (WINDOW_HEIGHT - textheight(gameOverText) * 3) / 2;

            outtextxy(overW, overH, gameOverText);
            outtextxy(overW, overH + 50, scoreText);
            outtextxy(overW, overH + 100, restartText);
        }
        else if (state == GAME_COMPLETED) {
            const char* completedText = "��ս�ɹ�!";
            const char* finalScoreText = "���յ÷�: ";
            sprintf_s(scoreText, "%s%d", finalScoreText, score);
            const char* restartText = "��R���¿�ʼ";

            settextcolor(GREEN);
            int overW = (WINDOW_WIDTH - textwidth(completedText)) / 2;
            int overH = (WINDOW_HEIGHT - textheight(completedText) * 3) / 2;

            outtextxy(overW, overH, completedText);
            outtextxy(overW, overH + 50, scoreText);
            outtextxy(overW, overH + 100, restartText);
        }
    }

    // ����������¼�
    bool handleMouseClick(ExMessage* mes) {
        if (state != RUNNING) return false;

        // �жϵ����Χ
        int x = flag[3] * BLOCK_WIDTH;
        int y = 3 * BLOCK_HEIGHT + TITLE_AREA_HEIGHT;

        if (mes->x > x && mes->x <= x + BLOCK_WIDTH && mes->y > y && mes->y <= y + BLOCK_HEIGHT) {
            // �������ȷ�ĺڿ�
            moveBlocks();
            score++;
            // ���ŵ����Ƶ
            playClickSound();
            return true;
        }
        else {
            // ������׿飬��Ϸ����
            state = GAME_OVER;
            return false;
        }
    }

    // �ƶ��ڿ�
    void moveBlocks() {
        // �����ƶ��ڿ�
        for (int i = 3; i > 0; i--) {
            flag[i] = flag[i - 1];
        }
        flag[0] = rand() % 4;
    }

    // �������¼�
    void handleKeyPress(ExMessage* mes) {
        switch (mes->vkcode) {
        case VK_ESCAPE:
            state = (state == RUNNING) ? PAUSED : RUNNING;
            if (state == RUNNING) {
                startTime = clock() - (GAME_TIME_LIMIT - remainingTime) * CLOCKS_PER_SEC;
            }
            break;
        case 'R':
        case 'r':
            if (state == GAME_OVER || state == GAME_COMPLETED) {
                resetGame();
            }
            break;
        }
    }

    // ������Ϸ
    void resetGame() {
        score = 0;
        remainingTime = GAME_TIME_LIMIT;
        timeUpdated = false;
        init();
        state = RUNNING;
        startTime = clock();
    }

    // ������Ϸ״̬
    void update() {
        if (state != RUNNING) return;

        // ����ʣ��ʱ��
        clock_t currentTime = clock();
        int elapsedSeconds = static_cast<int>((currentTime - startTime) / CLOCKS_PER_SEC);
        int newRemainingTime = GAME_TIME_LIMIT - elapsedSeconds;

        if (newRemainingTime != remainingTime) {
            remainingTime = newRemainingTime;
            timeUpdated = true;

            if (remainingTime <= 0) {
                remainingTime = 0;
                state = GAME_COMPLETED;
            }
        }
        else {
            timeUpdated = false;
        }
    }

    // ��ȡ��Ϸ״̬
    GameState getState() const {
        return state;
    }

    // �ж�ʱ���Ƿ��Ѹ���
    bool hasTimeUpdated() const {
        return timeUpdated;
    }
};

int main() {
    // ��ʼ��ͼ�δ���
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, EX_SHOWCONSOLE);

    // ������Ϸ����
    Game game;

    // ����������ͼ����ֹ��˸
    BeginBatchDraw();

    // ��Ϸ��ѭ��
    bool exitGame = false;
    while (!exitGame) {
        // ������Ϸ״̬
        game.update();

        // ������Ϸ����
        game.draw();
        FlushBatchDraw();

        // ������Ϣ
        ExMessage mes = { 0 };
        while (peekmessage(&mes)) {
            switch (mes.message) {
            case WM_KEYDOWN:
                game.handleKeyPress(&mes);
                if (mes.vkcode == VK_ESCAPE && game.getState() == PAUSED) {
                    exitGame = true;
                }
                break;
            case WM_LBUTTONDOWN:
                game.handleMouseClick(&mes);
                break;
            case WM_CLOSE:
                exitGame = true;
                break;
            }
        }

        // �ʵ���ʱ������ CPU ʹ����
        Sleep(10);
    }

    EndBatchDraw();
    closegraph();
    return 0;
}