#include "GridPanel.h"

enum M_INPUT {
    M_MOVE,
    M_LCLICK,
    M_RCLICK,
    M_ELSECLICK,
    M_DOUBLECLICK,
    M_WHEEL
};

GridPanel::GridPanel(Position lefttop, int width, int height) : width(10), height(10), width_temp(width), height_temp(height),
                            mine_index(nullptr), mine_num(0), mine('*'), block('&'), scene(Scene::getInstance()),
                            gameOver(false), panel(lefttop, Position(lefttop.getPosX() + width, lefttop.getPosY() + height))
    // 주 버퍼공간 리셋 및 출력. 지뢰 찾기 전 모든 칸이 닫혀있는 상태이다.
    {
    buffer = new char[(width + 1) * height];
    hide_buffer = new char[(width + 1) * height];
    reset();
}

void GridPanel::start() {
}

void GridPanel::update() {
    readyToInput();
}

bool GridPanel::compare(int arr[], int curr)
{ // arr의 각 인덱스에 있는 값과 가장 높은 인덱스에 있는 값을 비교하여 중복되는 값이 있을 경우 true 반환, 없으면 false 반환
    for (int i = 0; i < curr; i++)
    {
        if (arr[curr] == arr[i])
            return true;
    }
    return false;
}

bool GridPanel::compare_dby(int* dropby)
{ // dropby의 각 인덱스에 있는 값과 가장 높은 인덱스에 있는 값을 비교하여 중복되는 값이 있을 경우 true 반환, 없으면 false 반환
    for (int i = 0; i < dropby_num; i++)
    {
        if (dropby[dropby_num] == dropby[i])
        {
            return true;
        }
    }
    dropby_num++;
    return false;
}

void GridPanel::reset()
{
    scene.clearScene();
    boardText();

    gameOver = false;
    moveTime = 0;
    dscvd_num = 0;

    delete[] buffer;
    delete[] hide_buffer;

    width = width_temp;
    height = height_temp;
    panel.setRightBottom(Position(panel.getLeftTop().getPosX() + width, panel.getLeftTop().getPosY() + height));
    panel.draw();

    buffer = new char[(width + 1) * height];
    hide_buffer = new char[(width + 1) * height];

    memset(buffer, block, (width + 1) * height);
    for (int i = 0; i < height; i++)
    {
        buffer[i * (width + 1) + (width + 1) - 1] = '\n';
    }
    buffer[(width + 1) * height - 1] = '\0';
    scene.drawScene(buffer, panel.getLeftTop(), panel.getRightBottom());

    srand((unsigned int)time(NULL));
    mine_num = rand() % 11 + (((width + 1) - 1) * height) / 10; // j는 10~20 사이의 값을 가진다.
    mine_index = new int[mine_num + 1];
    mine_index[mine_num] = '\0';

    memset(hide_buffer, 0, (width + 1) * height);
    for (int i = 0; i < mine_num; i++)
    {
        mine_index[i] = rand() % ((width + 1) * height);
        if (mine_index[i] % (width + 1) == (width + 1) - 1 || compare(mine_index, i)) // 지뢰가 \n 과 \0 영역에 설치될 경우, 새로운 랜덤위치가 전과 동일한 경우
            i--;
        else
            hide_buffer[mine_index[i]] = mine;
    }

    for (int i = 0; i < mine_num; i++)
    {
        if (mine_index[i] % (width + 1) != 0 && hide_buffer[mine_index[i] - 1] != mine) // 지뢰 ←에 1 추가
            hide_buffer[mine_index[i] - 1]++;
        if (mine_index[i] % (width + 1) != (width + 1) - 2 && hide_buffer[mine_index[i] + 1] != mine) // 지뢰 →에 1 추가
            hide_buffer[mine_index[i] + 1]++;
        if (mine_index[i] > (width + 1) - 1 && hide_buffer[mine_index[i] - (width + 1)] != mine) // 지뢰 ↑에 1 추가
            hide_buffer[mine_index[i] - (width + 1)]++;
        if (mine_index[i] < (width + 1) * (height - 1) && hide_buffer[mine_index[i] + (width + 1)] != mine) // 지뢰 ↓에 1 추가
            hide_buffer[mine_index[i] + (width + 1)]++;

        if (mine_index[i] % (width + 1) != 0 && mine_index[i] > (width + 1) - 1 && hide_buffer[mine_index[i] - (width + 1) - 1] != mine) // 지뢰 ↖에 1 추가
            hide_buffer[mine_index[i] - (width + 1) - 1]++;
        if (mine_index[i] % (width + 1) != 0 && mine_index[i] < (width + 1) * (height - 1) && hide_buffer[mine_index[i] + (width + 1) - 1] != mine) // 지뢰 ↙에 1 추가
            hide_buffer[mine_index[i] + (width + 1) - 1]++;
        if (mine_index[i] % (width + 1) != (width + 1) - 2 && mine_index[i] > (width + 1) - 1 && hide_buffer[mine_index[i] - (width + 1) + 1] != mine) // 지뢰 ↗에 1 추가
            hide_buffer[mine_index[i] - (width + 1) + 1]++;
        if (mine_index[i] % (width + 1) != (width + 1) - 2 && mine_index[i] < (width + 1) * (height - 1) && hide_buffer[mine_index[i] + (width + 1) + 1] != mine) // 지뢰 ↘에 1 추가
            hide_buffer[mine_index[i] + (width + 1) + 1]++;
    }
}

void GridPanel::getEmpty(int index, int* dropby)
{ // 빈공간 클릭 시 해당 공간 주변 빈공간까지 다 밝혀짐
    bool isNum = false; // 숫자가 있는 공간 도착 시 모든 이동을 멈추고 함수 벗어남.
    dropby[dropby_num] = index;
    if (hide_buffer[index] == 0)
        buffer[index] = ' ';
    else
    {
        buffer[index] = hide_buffer[index] + 48; // int 형을 char 형으로 바꿔주기
        isNum = true;
    }

    if (!compare_dby(dropby) && !isNum)
    {
        if (hide_buffer[index - 1] != mine && index % (width + 1) != 0) // 기준점에서 ←으로 빈공간 확장
        {
            getEmpty(index - 1, dropby);
        }
        if (hide_buffer[index + 1] != mine && index % (width + 1) != (width + 1) - 2) // 기준점에서 →으로 빈공간 확장
        {
            getEmpty(index + 1, dropby);
        }
        if (hide_buffer[index - (width + 1)] != mine && index > (width + 1) - 1) // 기준점에서 ↑으로 빈공간 확장
        {
            getEmpty(index - (width + 1), dropby);
        }
        if (hide_buffer[index + (width + 1)] != mine && index < (width + 1) * (height - 1)) // 기준점에서 ↓으로 빈공간 확장
        {
            getEmpty(index + (width + 1), dropby);
        }
    }
}

void GridPanel::readyToInput()
{
#ifndef index
#define index (InputManager::x - panel.getLeftTop().getPosX() + (InputManager::y - panel.getLeftTop().getPosY()) * (width + 1))
#endif
    if (!gameOver) {
        if (InputManager::x >= panel.getLeftTop().getPosX() && InputManager::x < panel.getRightBottom().getPosX()
            && InputManager::y >= panel.getLeftTop().getPosY() && InputManager::y < panel.getRightBottom().getPosY()
            && index % (width + 1) != height)
        { //마우스 포인터의 x, y 값이 버퍼 내 공간에 들어올 경우 && 배열의 인덱스에 있는 값이 \n 또는 \0 이 아닌 경우
            if (InputManager::mouseinput == M_LCLICK && buffer[index] == block)
            { // 좌클릭 시 && 마우스 위치에 /(깃발) 그리고 ?(보류) 표시가 아닌 경우
                moveTime++;
                if (hide_buffer[index] == 0) // 0 은 곧 빈공간을 의미한다.
                {
                    int* dropby = new int[(width + 1) * height];
                    memset(dropby, '\0', (width + 1) * height);
                    dropby_num = 0;

                    getEmpty(index, dropby);

                    dscvd_num += dropby_num;

                    delete[] dropby;
                }
                else if (hide_buffer[index] == mine)
                {
                    hitMine();
                    return;
                }
                else // 숫자가 있는 공간을 밟았을 경우
                {
                    dscvd_num++;
                    buffer[index] = hide_buffer[index] + 48;
                }

                draw();

                dscvd_num /= 2;
                boardRefresh();

                if (mine_num + dscvd_num >= ((width + 1) - 1) * height) // 게임 클리어 조건: 찾아낸 공간 수와 숨겨진 지뢰 수의 합 = 전체 공간 수
                    complete();
            }
            else if (InputManager::mouseinput == M_RCLICK)
            { // 우클릭 시
                if (buffer[index] == block || buffer[index] == '/' || buffer[index] == '?')
                {
                    if (buffer[index] == block)
                        buffer[index] = '/';
                    else if (buffer[index] == '/')
                    {
                        buffer[index] = '?';
                    }
                    else if (buffer[index] == '?')
                    {
                        buffer[index] = block;
                    }
                    scene.drawScene(buffer, panel.getLeftTop(), panel.getRightBottom());
                }
            }
        }
    }
}

void GridPanel::draw()
{
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        scene.drawScene(buffer, panel.getLeftTop(), panel.getRightBottom());

        if (buffer[i] != block && buffer[i] != '/' && buffer[i] != '?' && buffer[i] != mine && buffer[i] != '\n')
            dscvd_num++;
    }
}

void GridPanel::hitMine()
{ // 지뢰를 건드릴 경우
    gameOver = true;
    
    for (int i = 0; mine_index[i] != '\0'; i++)
    {
        buffer[mine_index[i]] = mine;
    }
    draw();

    Position::gotoxy((panel.getRightBottom().getPosX() + 1) + 1, height / 2);
    cout << "Game Over";
}

void GridPanel::complete()
{ // 게임 완료
    gameOver = true;
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == block)
            buffer[i] = mine;
        else if (buffer[i] == '/')
            buffer[i] = 'X';
    }
    draw();

    Position::gotoxy((width + 1) + 1, height / 2);
    cout << "COMPLETED!!!";
}

void GridPanel::boardText()
{
    int x = panel.getRightBottom().getPosX() + 1;
    Position::gotoxy(x + 10, height / 5);
    cout << "MINE SWEEPER GAME";
    Position::gotoxy(x + 10, height / 5 + 2);
    cout << "MOVED: ";
    Position::gotoxy(x + 10, height / 2 + 4);
    cout << "Screen Size: ";
}

void GridPanel::boardRefresh()
{
    int x = panel.getRightBottom().getPosX() + 1;
    Position::gotoxy(x + 10, height / 2 + 2);
    cout << "Discovered Space: " << dscvd_num;
    Position::gotoxy(x + 10, height / 2 + 3);
    cout << "Number of Mines: " << mine_num;
    Position::gotoxy(x + 17, height / 5 + 2);
    cout << moveTime << "    ";
}

/*
_setmode(_fileno(stdout), _O_U16TEXT);
_setmode(_fileno(stdout), _O_TEXT);
*/