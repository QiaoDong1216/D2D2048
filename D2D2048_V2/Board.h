#pragma once
#include <iostream>
#include <list>
#include "Direct2dApp/Direct2dApp.h"
#include "Clock.h"
#include "LogSys.h"

#define ANIMATION_SPEED 0.15f	// �����ٶ�
#define ANIMATION_SIZE_SPEED 0.15f	// ���������Ӷ����ٶ�

enum DIR { UP, DOWN, LEFT, RIGHT };
enum GAME_STATUS { STATIC/*��ֹ״̬*/, MOVE/*���Ŷ���״̬*/, SIZEMOVE,/*����������*/ GAMEOVER/*��Ϸ����*/ };

class pos
{
public:
	int x;
	int y;

	friend std::ostream& operator << (std::ostream& out, pos& p)
	{
		std::cout << "x: " << p.x << " y: " << p.y;
		return out;
	}
	friend bool operator == (const pos& a, const pos& b)
	{
		return (a.x == b.x && a.y == b.y);
	}
};

class fpos
{
public:
	float x;
	float y;
};

class Board
{
public:
	Board();
	Board(int x, int y);
	~Board();

	void initBoard(int rows, int cols);
	void Move(DIR dir);
	void Render(app::Direct2dApp& App, RECT& _rc);
	int getSocre();
	void Test();
	void Reset();
	void ReSize(int width, int height);
	void setAnimation(bool flag);
	DIR GetAiMove();

private:
	std::list<std::pair<std::pair<pos, pos>, pos>> m_animation;
	GAME_STATUS game_Status;
	Clock animation_clock;
	Clock size_animation_clock;
	std::pair<pos, int> last_new_cell;
	int** m_board;
	int** m_last_board;
	int m_rows;	// ��
	int m_cols;	// ��
	int m_score;
	bool m_animation_switch = true;

private:
	/// <summary>
	/// ���������������һ������
	/// </summary>
	void randCell(int** arr, int rows, int cols);
	int applyMove(int** arr, int rows, int cols, const pos& from, const pos& to, const pos& dir, int last_add);
	float getTime();
	/// <summary>
	/// �Ƿ��Ѿ�GameOver
	/// </summary>
	/// <returns></returns>
	bool isGameOver(int** arr, int rows, int cols);
	
	/// <summary>
	/// �Ƿ�����Ч�ƶ�����Ч�ƶ�����true
	/// </summary>
	/// <param name="thisArr"></param>
	/// <param name="lastArr"></param>
	/// <param name="rows"></param>
	/// <param name="cols"></param>
	/// <returns></returns>
	bool isFailMove(int** thisArr, int** lastArr, int rows, int cols);

	/// <summary>
	/// ����������0�ĸ���
	/// </summary>
	/// <param name="arr"></param>
	/// <param name="rows"></param>
	/// <param name="cols"></param>
	/// <returns></returns>
	int getArrZeroNum(int** arr, int rows, int cols);

	/// <summary>
	/// ������ĵ����Խ�������
	/// </summary>
	/// <returns></returns>
	int aiDullScore(int** arr, int rows, int cols);

	/// <summary>
	/// ���ؿ�������
	/// </summary>
	/// <param name="arr"></param>
	/// <param name="rows"></param>
	/// <param name="cols"></param>
	/// <returns></returns>
	DIR aiGetMove(int** arr, int rows, int cols, int deep);

	/// <summary>
	/// ��ĳ�������ƶ��������ط���
	/// </summary>
	/// <param name="arr"></param>
	/// <param name="rows"></param>
	/// <param name="cols"></param>
	/// <returns></returns>
	int move(DIR dir, int** arr, int rows, int cols);

	D2D1_COLOR_F getColor(int num);
	D2D1_COLOR_F getTextColor(int num);
	float		 getTextSize(int num);

	int down(int** arr, int rows, int cols);
	int up(int** arr, int rows, int cols);
	int left(int** arr, int rows, int cols);
	int right(int** arr, int rows, int cols);
};

