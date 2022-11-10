#pragma once
#include <iostream>
#include <list>
#include "Direct2dApp/Direct2dApp.h"
#include "Clock.h"
#include "LogSys.h"
#define PI 3.14159265

#define MAX_CELL 512	// ���ĸ���������õ�����������ʵ��ֵӦ���� 2��MAX_CELL�η�

enum DIR { UP, DOWN, LEFT, RIGHT };
enum GAME_STATUS { STATIC/*��ֹ״̬*/, MOVE/*���Ŷ���״̬*/, SIZEMOVE,/*����������*/ GAMEOVER/*��Ϸ����*/ };
enum ANIMATION_MOVE {LINE, QUAD, MAX_QUAD, JELLY, FALL};

enum ANIMATION_SPEED_MODE { NORMAL, MEDIUM, SLOW };

typedef float (*MoveAnimationFun)(float);
typedef float (*SizeAnimationFun)(float);

float easeInOutQuad(float t);
float easeInOutQuart(float t);
float easeInOutBack(float t);
float easeInOutCirc(float t);
float easeOutElastic(float t);

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
	void setAnimationMode(ANIMATION_MOVE flag);
	void setAnimationSpeed(ANIMATION_SPEED_MODE flag);

	ANIMATION_MOVE m_animation_mode = MAX_QUAD;
	ANIMATION_SPEED_MODE m_animation_speed_mode = NORMAL;

private:
	std::list<std::pair<std::pair<pos, pos>, pos>> m_animation;
	std::list<pos> m_add_animation;
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

	float ANIMATION_SPEED      = 0.15f;	// �����ٶ�
	float ANIMATION_SIZE_SPEED = 0.15f;	// ���������Ӷ����ٶ�

	MoveAnimationFun m_move_animation_mode_fun;	// ��������ָ��
	SizeAnimationFun m_size_animation_mode_fun;	// ��������ָ��

private:
	// ���������������һ������
	void randCell(int** arr, int rows, int cols);

	int applyMove(int** arr, int rows, int cols, const pos& from, const pos& to, const pos& dir, int last_add);

	float getTime();

	// �Ƿ��Ѿ�GameOver
	bool isGameOver(int** arr, int rows, int cols);
	
	// �Ƿ�����Ч�ƶ�����Ч�ƶ�����true
	bool isFailMove(int** thisArr, int** lastArr, int rows, int cols);

	// ����������0�ĸ���
	int getArrZeroNum(int** arr, int rows, int cols);

	// ������ĵ����Խ������֣��ú����Ǵ����
	int aiDullScore(int** arr, int rows, int cols) = delete;

	// ���������ͬ�ĸ������������֣���ͬ�ĸ���Խ�࣬����Խ��
	int aiSameScore(int** arr, int rows, int cols);

	// ���ؿ�������
	DIR aiGetMove(int** arr, int rows, int cols, int deep);

	// ��ĳ�������ƶ��������ط���
	int move(DIR dir, int** arr, int rows, int cols);

	D2D1_COLOR_F getColor(int num);
	D2D1_COLOR_F getTextColor(int num);
	float		 getTextSize(int num);

	int down(int** arr, int rows, int cols);
	int up(int** arr, int rows, int cols);
	int left(int** arr, int rows, int cols);
	int right(int** arr, int rows, int cols);
};

