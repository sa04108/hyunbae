#include "MineSweeper.h"
#include "Keynmouse.h"
#include <iomanip>

enum M_INPUT {
    M_MOVE,
    M_LCLICK,
    M_RCLICK,
    M_ELSECLICK,
    M_DOUBLECLICK,
    M_WHEEL
};

MineSweeper::MineSweeper() {
    // 주 버퍼공간 리셋 및 출력. 지뢰 찾기 전 모든 칸이 닫혀있는 상태이다.
    width_plus1 = w_stored;
    height = h_stored;

    buffer = new wchar_t[width_plus1 * height];
    hide_buffer = new wchar_t[width_plus1 * height];
    gameOver = false;

    clear();
    boardText();

    block = L'◼';

    reset();
}

bool MineSweeper::compare(int arr[], int curr)
{ // arr의 각 인덱스에 있는 값과 가장 높은 인덱스에 있는 값을 비교하여 중복되는 값이 있을 경우 true 반환, 없으면 false 반환
    for (int i = 0; i < curr; i++)
    {
        if (arr[curr] == arr[i])
            return true;
    }
    return false;
}

bool MineSweeper::compare_dby(int* dropby)
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

void MineSweeper::reset()
{
    gameOver = false;
    moveTime = 0;
    dscvd_num = 0;

    GetPosition::gotoxy(0, 0);
    wmemset(buffer, block, width_plus1 * height);
    for (int i = 0; i < height; i++)
    {
        buffer[i * width_plus1 + width_plus1 - 1] = '\n';
    }
    buffer[width_plus1 * height - 1] = '\0';
    _setmode(_fileno(stdout), _O_U16TEXT);
    wcout << buffer;
    _setmode(_fileno(stdout), _O_TEXT);

    srand((unsigned int)time(NULL));
    mine_num = rand() % 11 + ((width_plus1 - 1) * height) / 10; // j는 10~20 사이의 값을 가진다.
    mine_index = new int[mine_num + 1];
    mine_index[mine_num] = '\0';

    wmemset(hide_buffer, 0, width_plus1 * height);
    for (int i = 0; i < mine_num; i++)
    {
        mine_index[i] = rand() % (width_plus1 * height);
        if (mine_index[i] % width_plus1 == width_plus1 - 1 || compare(mine_index, i)) // 지뢰가 \n 과 \0 영역에 설치될 경우, 새로운 랜덤위치가 전과 동일한 경우
            i--;
        else
            hide_buffer[mine_index[i]] = mine;
    }

    for (int i = 0; i < mine_num; i++)
    {
        if (mine_index[i] % width_plus1 != 0 && hide_buffer[mine_index[i] - 1] != mine) // 지뢰 ←에 1 추가
            hide_buffer[mine_index[i] - 1]++;
        if (mine_index[i] % width_plus1 != width_plus1 - 2 && hide_buffer[mine_index[i] + 1] != mine) // 지뢰 →에 1 추가
            hide_buffer[mine_index[i] + 1]++;
        if (mine_index[i] > width_plus1 - 1 && hide_buffer[mine_index[i] - width_plus1] != mine) // 지뢰 ↑에 1 추가
            hide_buffer[mine_index[i] - width_plus1]++;
        if (mine_index[i] < width_plus1 * (height - 1) && hide_buffer[mine_index[i] + width_plus1] != mine) // 지뢰 ↓에 1 추가
            hide_buffer[mine_index[i] + width_plus1]++;

        if (mine_index[i] % width_plus1 != 0 && mine_index[i] > width_plus1 - 1 && hide_buffer[mine_index[i] - width_plus1 - 1] != mine) // 지뢰 ↖에 1 추가
            hide_buffer[mine_index[i] - width_plus1 - 1]++;
        if (mine_index[i] % width_plus1 != 0 && mine_index[i] < width_plus1 * (height - 1) && hide_buffer[mine_index[i] + width_plus1 - 1] != mine) // 지뢰 ↙에 1 추가
            hide_buffer[mine_index[i] + width_plus1 - 1]++;
        if (mine_index[i] % width_plus1 != width_plus1 - 2 && mine_index[i] > width_plus1 - 1 && hide_buffer[mine_index[i] - width_plus1 + 1] != mine) // 지뢰 ↗에 1 추가
            hide_buffer[mine_index[i] - width_plus1 + 1]++;
        if (mine_index[i] % width_plus1 != width_plus1 - 2 && mine_index[i] < width_plus1 * (height - 1) && hide_buffer[mine_index[i] + width_plus1 + 1] != mine) // 지뢰 ↘에 1 추가
            hide_buffer[mine_index[i] + width_plus1 + 1]++;
    }
}

void MineSweeper::getEmpty(int index, int* dropby)
{ // 빈공간 클릭 시 해당 공간 주변 빈공간까지 다 밝혀짐
    bool isNum = false; // 숫자가 있는 공간 도착 시 모든 이동을 멈추고 함수 벗어남.
    dropby[dropby_num] = index;
    if (hide_buffer[index] == 0)
        buffer[index] = ' ';
    else
    {
        buffer[index] = hide_buffer[index];
        isNum = true;
    }

    if (!compare_dby(dropby) && !isNum)
    {
        if (hide_buffer[index - 1] != mine && index % width_plus1 != 0) // 기준점에서 ←으로 빈공간 확장
        {
            getEmpty(index - 1, dropby);
        }
        if (hide_buffer[index + 1] != mine && index % width_plus1 != width_plus1 - 2) // 기준점에서 →으로 빈공간 확장
        {
            getEmpty(index + 1, dropby);
        }
        if (hide_buffer[index - width_plus1] != mine && index > width_plus1 - 1) // 기준점에서 ↑으로 빈공간 확장
        {
            getEmpty(index - width_plus1, dropby);
        }
        if (hide_buffer[index + width_plus1] != mine && index < width_plus1 * (height - 1)) // 기준점에서 ↓으로 빈공간 확장
        {
            getEmpty(index + width_plus1, dropby);
        }
    }
}

void MineSweeper::check()
{
#ifndef index
#define index (Keynmouse::x + Keynmouse::y * width_plus1)
#endif
    if (Keynmouse::x < width_plus1 - 1 && Keynmouse::y < height && index % width_plus1 != height)
    { //마우스 포인터의 x, y 값이 버퍼 내 공간에 들어올 경우 && 배열의 인덱스에 있는 값이 \n 또는 \0 이 아닌 경우
        if (Keynmouse::mouseinput == M_LCLICK && buffer[index] == block)
        { // 좌클릭 시 && 마우스 위치에 /(깃발) 그리고 ?(보류) 표시가 아닌 경우
            moveTime++;
            if (hide_buffer[index] == 0) // 0 은 곧 빈공간을 의미한다.
            {
                int* dropby = new int[width_plus1 * height];
                memset(dropby, '\0', width_plus1 * height);
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
            else
            {
                dscvd_num++;
                buffer[index] = hide_buffer[index];
            }

            draw();

            dscvd_num /= 2;
            boardRefresh();

            if (mine_num + dscvd_num >= (width_plus1 - 1) * height) // 게임 클리어 조건: 찾아낸 공간 수와 숨겨진 지뢰 수의 합 = 전체 공간 수
                complete();
        }
        else if (Keynmouse::mouseinput == M_RCLICK)
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
                GetPosition::gotoxy(Keynmouse::x, Keynmouse::y);
                _setmode(_fileno(stdout), _O_U16TEXT);
                wcout << buffer[index];
                _setmode(_fileno(stdout), _O_TEXT);
            }
        }
    }
}

void MineSweeper::draw()
{
    GetPosition::gotoxy(0, 0);
    _setmode(_fileno(stdout), _O_U16TEXT);
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == block || buffer[i] == '/' || buffer[i] == '?' || buffer[i] == 'X' || buffer[i] == mine || buffer[i] == ' ' || buffer[i] == '\n')
            wcout << buffer[i];
        else
            wcout << (int)buffer[i];

        if (buffer[i] != block && buffer[i] != '/' && buffer[i] != '?' && buffer[i] != mine && buffer[i] != '\n')
            dscvd_num++;
    }
    _setmode(_fileno(stdout), _O_TEXT);
}

void MineSweeper::hitMine()
{ // 지뢰를 건드릴 경우
    gameOver = true;
    
    for (int i = 0; mine_index[i] != '\0'; i++)
    {
        buffer[mine_index[i]] = mine;
    }
    draw();

    GetPosition::gotoxy(width_plus1 + 1, height / 2);
    cout << "Game Over";
}

void MineSweeper::complete()
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

    GetPosition::gotoxy(width_plus1 + 1, height / 2);
    cout << "COMPLETED!!!";
}

void MineSweeper::setScreen()
{
    if (Keynmouse::keyinput == 37 && w_stored > 5)
        w_stored--;
    else if (Keynmouse::keyinput == 39)
        w_stored++;
    else if (Keynmouse::keyinput == 38 && h_stored > 5)
        h_stored--;
    else if (Keynmouse::keyinput == 40)
        h_stored++;
    boardRefresh();
}

void MineSweeper::clear()
{
    char* clear_buffer = new char[(width_plus1 + 100) * (height + 50)];
    memset(clear_buffer, ' ', (width_plus1 + 100) * (height + 50));

    for (int i = 0; i < height + 50; i++)
    {
        clear_buffer[i * (width_plus1 + 100) + width_plus1 + 99] = '\n';
    }
    clear_buffer[(width_plus1 + 100) * (height + 50) - 1] = '\0';

    GetPosition::gotoxy(0, 0);

    cout << clear_buffer;

    delete[] clear_buffer;
}

void MineSweeper::boardText()
{
    GetPosition::gotoxy(width_plus1 + 10, height / 5);
    cout << "MINE SWEEPER GAME";
    GetPosition::gotoxy(width_plus1 + 10, height / 5 + 2);
    cout << "MOVED: ";
    GetPosition::gotoxy(width_plus1 + 10, height / 2 + 4);
    cout << "Screen Size: ";

    GetPosition::gotoxy(0, height + 5);
    cout << "Press 'R' Button to reset the game.";
    GetPosition::gotoxy(0, height + 6);
    cout << "Press ↑, ↓, ←, →, to adjust the game screen.";
}

void MineSweeper::boardRefresh()
{
    GetPosition::gotoxy(width_plus1 + 10, height / 2 + 2);
    cout << "Discovered Space: " << dscvd_num;
    GetPosition::gotoxy(width_plus1 + 10, height / 2 + 3);
    cout << "Number of Mines: " << mine_num;
    GetPosition::gotoxy(width_plus1 + 17, height / 5 + 2);
    cout << moveTime << "    ";
    GetPosition::gotoxy(width_plus1 + 23, height / 2 + 4);
    cout << setw(3) << w_stored - 1 << " * " << setw(3) << h_stored << " (change will begin next game.)    ";
}