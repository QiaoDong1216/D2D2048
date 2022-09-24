#include "Board.h"

Board::Board()
	: m_cols(0), m_rows(0), m_board(nullptr), m_last_board(nullptr), game_Status(STATIC), m_score(0)
{
}

Board::Board(int x, int y)
	:m_cols(x), m_rows(y), m_board(nullptr), m_last_board(nullptr), game_Status(STATIC), m_score(0)
{
	this->initBoard(m_rows, m_cols);
}

Board::~Board()
{
}

void Board::initBoard(int rows, int cols)
{
	this->m_rows = rows; this->m_cols = cols;
	this->m_board = new int* [rows];

	for (int i = 0; i < rows; i++)
		this->m_board[i] = new int[cols];

	for (size_t y = 0; y < rows; y++)
		for (size_t x = 0; x < cols; x++)
			this->m_board[y][x] = 0;

	this->m_last_board = new int* [rows];
	for (int i = 0; i < rows; i++)
		this->m_last_board[i] = new int[cols];

	this->randCell(m_board, m_rows, m_cols);
}

void Board::Move(DIR dir)
{
	static int all_count = 0;
	static int win_count = 0;
	static int fail_count = 0;
	static bool last_fail_move = false;

	if (game_Status == GAMEOVER) return;
	if (game_Status == MOVE) return;
	if (game_Status == SIZEMOVE) return;

	/*for (int y = 0; y < m_rows; y++)
	{
		for (int x = 0; x < m_cols; x++)
		{
			if (m_board[y][x] >= 11)
			{
				Loger::WriteTime();
				Loger::Write("   2048 Win! \n");
				std::cout << "2048 WIN ";
				Reset();
				win_count++;
				all_count++;
				std::cout << "  All: " << all_count << "  W: " << win_count << "  F: " << fail_count << "  " << ((float)win_count / (float)all_count) * 100.0f << "%\n";
			}
		}
	}*/

	for (size_t y = 0; y < m_rows; y++)
		for (size_t x = 0; x < m_cols; x++)
			this->m_last_board[y][x] = this->m_board[y][x];

	m_score += move(dir, m_board, m_rows, m_cols);

	if (!isFailMove(this->m_board, this->m_last_board, m_rows, m_cols))
	{
		this->randCell(m_board, m_rows, m_cols);
		last_fail_move = false;
	}
	else
	{
		static int count = 0;
		/*if (last_fail_move)
		{
			if (count++ >= 500)
			{
				Reset();
				count = 0;
				Loger::WriteTime();
				Loger::Write("   2048 Reset! Time Out\n");
				std::cout << "2048 Reset Time Out";
				fail_count++;
				all_count++;
				std::cout << "  All: " << all_count << "  W: " << win_count << "  F: " << fail_count << "  " << ((float)win_count / (float)all_count) * 100.0f << "%\n";
			}
		}*/
		game_Status = STATIC;
		if (isGameOver(m_board, m_rows, m_cols))
		{
			game_Status = GAMEOVER;
			//Reset();
			Loger::WriteTime();
			Loger::Write("   2048 Reset! GameOver!\n");
			std::cout << "2048 Reset GameOver!";
			fail_count++;
			all_count++;
			std::cout << "  All: " << all_count << "  W: " << win_count << "  F: " << fail_count << "  " << ((float)win_count / (float)all_count) * 100.0f << "%\n";
		}
		last_fail_move = true;
	}
}

// �������һ������
void Board::randCell(int** arr, int rows, int cols)
{
	int new_cell = (rand() % 100 > 90) ? 2 : 1;
	int x, y;
	do
	{
		x = rand() % cols;
		y = rand() % rows;
	} while (arr[y][x] != 0);

	arr[y][x] = new_cell;

	if (m_animation_switch)
	{
		this->last_new_cell.first = { x, y };
		this->last_new_cell.second = new_cell;
	}
}

bool Board::isGameOver(int** arr, int rows, int cols)
{
	static pos dir_[4] =
	{
		{0, -1},{0, 1},{-1, 0},{1, 0}
	};

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			int val = arr[y][x];
			if (val == 0) return false;
			for (int i = 0; i < 4; i++)
			{
				pos other = { x + dir_[i].x, y + dir_[i].y };

				// ������
				if (other.x >= cols || other.x < 0) continue;
				if (other.y >= rows || other.y < 0) continue;

				if (val == arr[other.y][other.x]) return false;
			}
		}
	}
	return true;	// Game Over
}

void Board::Test()
{
	int i = 1;
	for (size_t y = 0; y < m_rows; y++)
		for (size_t x = 0; x < m_cols; x++)
			m_board[y][x] = i++;
}

void Board::Reset()
{
	this->m_score = 0;
	game_Status = STATIC;
	for (size_t y = 0; y < m_rows; y++)
		for (size_t x = 0; x < m_cols; x++)
			this->m_board[y][x] = 0;
	this->randCell(m_board, m_rows, m_cols);
}

// �������̴�С
void Board::ReSize(int width, int height)
{
	// ɾ��ԭ��������
	for (size_t i = 0; i < m_rows; i++)
	{
		delete[] this->m_board[i];
		delete[] this->m_last_board[i];
	}

	// �������̴�С
	this->m_cols = width;
	this->m_rows = height;

	// ����Ϊ���̷����ڴ�
	this->m_board = new int* [m_rows];
	for (int i = 0; i < m_rows; i++)
		this->m_board[i] = new int[m_cols];

	for (size_t y = 0; y < m_rows; y++)
		for (size_t x = 0; x < m_cols; x++)
			this->m_board[y][x] = 0;

	this->m_last_board = new int* [m_rows];
	for (int i = 0; i < m_rows; i++)
		this->m_last_board[i] = new int[m_cols];

	this->Reset();
}

DIR Board::GetAiMove()
{
	return aiGetMove(m_board, m_rows, m_cols);
}

int Board::getSocre()
{
	return this->m_score;
}

int Board::up(int** arr, int rows, int cols)
{
	int temp_score = 0;
	static int last_add = 0;
	pos dir = { 0, -1 };
	pos begin_pos = { 0, 0 };
	pos end_pos = { 0, 0 };
	for (int x = 0; x <= cols - 1; x++)
	{
		last_add = 0;
		for (int y = 1; y <= rows - 1; y++)
		{
			if (arr[y][x] == 0) continue;
			begin_pos = { x, y };
			end_pos = { x , y - 1 };
			for (int my = y - 1; my >= 0; my--)
			{
				if (arr[my][x] != arr[y][x] && arr[my][x] != 0)
					break;
				end_pos = { x, my };
			}

			last_add = applyMove(arr, rows, cols, begin_pos, end_pos, dir, last_add);
			temp_score += last_add;
		}
	}
	return temp_score;
}
int Board::down(int** arr, int rows, int cols)
{
	int temp_score = 0;
	static int last_add = 0;
	pos dir = { 0, 1 };
	pos begin_pos = { 0, 0 };
	pos end_pos = { 0, 0 };
	for (int x = 0; x <= cols - 1; x++)
	{
		last_add = 0;
		for (int y = rows - 2; y >= 0; y--)
		{
			if (arr[y][x] == 0) continue;
			begin_pos = { x, y };
			end_pos = { x , y + 1 };
			for (int my = y + 1; my <= rows - 1; my++)
			{
				if (arr[my][x] != arr[y][x] && arr[my][x] != 0)
					break;
				end_pos = { x, my };
			}

			last_add = applyMove(arr, rows, cols, begin_pos, end_pos, dir, last_add);
			temp_score += last_add;
		}
	}
	return temp_score;
}
int Board::left(int** arr, int rows, int cols)
{
	int temp_score = 0;
	static int last_add = 0;
	pos dir = { -1, 0 };
	pos begin_pos = { 0, 0 };
	pos end_pos = { 0, 0 };
	for (int y = 0; y < rows; y++)
	{
		last_add = 0;
		for (int x = 1; x < cols; x++)
		{
			if (arr[y][x] == 0) continue;
			begin_pos = { x, y };
			end_pos = { x - 1, y };
			for (int mx = x - 1; mx >= 0; mx--)
			{
				if (arr[y][mx] != arr[y][x] && arr[y][mx] != 0)
					break;
				end_pos = { mx, y };
			}

			last_add = applyMove(arr, rows, cols, begin_pos, end_pos, dir, last_add);
			temp_score += last_add;
		}
	}
	return temp_score;
}
int Board::right(int** arr, int rows, int cols)
{
	int temp_score = 0;
	static int last_add = 0;
	pos dir = { 1, 0 };
	pos begin_pos = { 0, 0 };
	pos end_pos = { 0, 0 };
	for (int y = 0; y < rows; y++)
	{
		last_add = 0;
		for (int x = cols - 2; x >= 0; x--)
		{
			if (arr[y][x] == 0) continue;
			begin_pos = { x, y };
			end_pos = { x + 1, y };
			for (int mx = x + 1; mx <= cols - 1; mx++)
			{
				if (arr[y][mx] != arr[y][x] && arr[y][mx] != 0)
					break;
				end_pos = { mx, y };
			}

			last_add = applyMove(arr, rows, cols, begin_pos, end_pos, dir, last_add);
			temp_score += last_add;
		}
	}
	return temp_score;
}

int Board::applyMove(int** arr, int rows, int cols, const pos& from, const pos& to, const pos& dir, int last_add)
{
	int add = 0;
	if (from == to) return 0;

	if (m_animation_switch)
	{
		game_Status = MOVE;
		animation_clock.Reset();
	}

	if (arr[from.y][from.x] == arr[to.y][to.x])
	{
		if (last_add == arr[from.y][from.x])
		{
			int temp = arr[to.y - dir.y][to.x - dir.x];
			arr[to.y - dir.y][to.x - dir.x] = arr[from.y][from.x];
			arr[from.y][from.x] = temp;
			pos _to = { to.x - dir.x, to.y - dir.y };
			if(m_animation_switch)
				this->m_animation.push_back(std::make_pair(std::make_pair(from, _to), dir));
			return 0;
		}
		else
		{
			add = arr[to.y][to.x] += 1;
			arr[from.y][from.x] = 0;
		}
	}
	else
	{
		if (arr[to.y][to.x] == 0)
		{
			int temp = arr[to.y][to.x];
			arr[to.y][to.x] = arr[from.y][from.x];
			arr[from.y][from.x] = temp;
		}
		else
		{
			return 0;
		}
	}

	if (m_animation_switch)
		this->m_animation.push_back(std::make_pair(std::make_pair(from, to), dir));
	return add;
}

void Board::Render(app::Direct2dApp& App, RECT& _rc)
{
	RECT rc = _rc;
	float m_spacing = min(rc.right - rc.left, rc.bottom - rc.top) * 0.03f / max(m_rows, m_cols) * 2.0f;
	int MinWidth = min(rc.right - rc.left, rc.bottom - rc.top);
	float BlockWidth = (MinWidth - (m_spacing * (max(m_rows, m_cols) + 1))) / max(m_rows, m_cols);

	float boardX = (rc.right - rc.left - (max(m_rows, m_cols) * BlockWidth + (max(m_rows, m_cols) + 1) * m_spacing)) / 2.0f;
	float boardY = (rc.bottom - rc.top - (max(m_rows, m_cols) * BlockWidth + (max(m_rows, m_cols) + 1) * m_spacing)) / 2.0f;

	if (animation_clock.getTime() >= ANIMATION_SPEED && game_Status == MOVE)
	{
		m_animation.clear();
		game_Status = SIZEMOVE;
		size_animation_clock.Reset();
	}

	if (size_animation_clock.getTime() >= ANIMATION_SIZE_SPEED && game_Status == SIZEMOVE)
	{
		game_Status = STATIC;
	}

	switch (game_Status)
	{
	case STATIC:
	{
		for (size_t y = 0; y < m_rows; y++)
		{ //y = 0 ~ (ROWS - 1)
			for (size_t x = 0; x < m_cols; x++)
			{
				App.getDC()->SetTransform(D2D1::Matrix3x2F::Translation(
					boardX + m_spacing + x * (BlockWidth + m_spacing), boardY + m_spacing + y * (BlockWidth + m_spacing)
				));

				App.fillRoundedRect(0.0f, 0.0f, BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f, getColor(0));
				if (this->m_board[y][x] != 0)
					App.fillRoundedRect(0.0f, 0.0f, BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f, this->getColor(this->m_board[y][x]));
				static wchar_t buf[32] = { 0 };
				wsprintfW(buf, L"%d", (int)pow(2, this->m_board[y][x]));
				if (this->m_board[y][x] != 0)
					App.drawCenterText(buf, { 0.0f, 0.0f }, BlockWidth, BlockWidth, getTextColor(this->m_board[y][x]), BlockWidth * getTextSize(this->m_board[y][x]));
			}
		}
	}
	break;
	case MOVE:
	{
		for (size_t y = 0; y < m_rows; y++)
		{ //y = 0 ~ (ROWS - 1)
			for (size_t x = 0; x < m_cols; x++)
			{
				App.getDC()->SetTransform(D2D1::Matrix3x2F::Translation(
					boardX + m_spacing + x * (BlockWidth + m_spacing), boardY + m_spacing + y * (BlockWidth + m_spacing)
				));

				App.fillRoundedRect(0.0f, 0.0f, BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f, this->getColor(0));
				if (this->m_last_board[y][x] != 0)
					App.fillRoundedRect(0.0f, 0.0f, BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f, this->getColor(this->m_last_board[y][x]));
				static wchar_t buf[32] = { 0 };
				wsprintfW(buf, L"%d", (int)pow(2, this->m_last_board[y][x]));
				if (this->m_last_board[y][x] != 0)
					App.drawCenterText(buf, { 0.0f, 0.0f }, BlockWidth, BlockWidth, getTextColor(this->m_last_board[y][x]), BlockWidth * getTextSize(this->m_last_board[y][x]));
			}
		}

		for (auto it = m_animation.begin(); it != m_animation.end(); it++)
		{
			pos from = it->first.first;
			pos to = it->first.second;
			pos dir = it->second;
			static wchar_t buf[32] = { 0 };

			// FROM
			App.getDC()->SetTransform(D2D1::Matrix3x2F::Translation(
				boardX + m_spacing + from.x * (BlockWidth + m_spacing), boardY + m_spacing + from.y * (BlockWidth + m_spacing)
			));

			float movePercent = animation_clock.getTime() / ANIMATION_SPEED;

			fpos rect_pos = {
				(max(from.x, to.x) - min(from.x, to.x)) * (BlockWidth + m_spacing) * movePercent * dir.x,
				(max(from.y, to.y) - min(from.y, to.y)) * (BlockWidth + m_spacing) * movePercent * dir.y
			};

			App.fillRoundedRect(0.0f, 0.0f,
				BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f,
				D2D1::ColorF(187 / 255., 173 / 255., 160 / 255.));

			App.fillRoundedRect(0.0f, 0.0f,
				BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f,
				getColor(0));

			App.fillRoundedRect(rect_pos.x, rect_pos.y,
				BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f,
				this->getColor(this->m_last_board[from.y][from.x]));

			wsprintfW(buf, L"%d", (int)pow(2, this->m_last_board[from.y][from.x]));
			App.drawCenterText(buf, { (float)rect_pos.x, (float)rect_pos.y }, BlockWidth, BlockWidth, getTextColor(this->m_last_board[from.y][from.x]), BlockWidth * getTextSize(this->m_last_board[from.y][from.x]));
		}
	}
	break;
	case SIZEMOVE:
	{
		for (size_t y = 0; y < m_rows; y++)
		{ //y = 0 ~ (ROWS - 1)
			for (size_t x = 0; x < m_cols; x++)
			{
				App.getDC()->SetTransform(D2D1::Matrix3x2F::Translation(
					boardX + m_spacing + x * (BlockWidth + m_spacing), boardY + m_spacing + y * (BlockWidth + m_spacing)
				));

				App.fillRoundedRect(0.0f, 0.0f, BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f, getColor(0));
				if (this->m_board[y][x] != 0)
					App.fillRoundedRect(0.0f, 0.0f, BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f, this->getColor(this->m_board[y][x]));
				static wchar_t buf[32] = { 0 };
				wsprintfW(buf, L"%d", (int)pow(2, this->m_board[y][x]));
				if (this->m_board[y][x] != 0)
					App.drawCenterText(buf, { 0.0f, 0.0f }, BlockWidth, BlockWidth, getTextColor(this->m_board[y][x]), BlockWidth * getTextSize(this->m_board[y][x]));
			}
		}

		float movePercent = size_animation_clock.getTime() / ANIMATION_SIZE_SPEED;

		App.getDC()->SetTransform(D2D1::Matrix3x2F::Translation(
			boardX + m_spacing + last_new_cell.first.x * (BlockWidth + m_spacing), boardY + m_spacing + last_new_cell.first.y * (BlockWidth + m_spacing)
		));

		App.fillRoundedRect(0.0f, 0.0f,
			BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f,
			D2D1::ColorF(187 / 255., 173 / 255., 160 / 255.));

		App.fillRoundedRect(0.0f, 0.0f,
			BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f,
			getColor(0));

		App.fillRoundedRect((BlockWidth - BlockWidth * movePercent) * 0.5f, (BlockWidth - BlockWidth * movePercent) * 0.5f, BlockWidth * movePercent, BlockWidth * movePercent, BlockWidth * 0.1f, BlockWidth * 0.1f, this->getColor(last_new_cell.second));

		static wchar_t buf[32] = { 0 };
		wsprintfW(buf, L"%d", (int)pow(2, last_new_cell.second));
		App.drawCenterText(buf, { 0.0f, 0.0f }, BlockWidth, BlockWidth, getTextColor(last_new_cell.second), BlockWidth * getTextSize(last_new_cell.second) * movePercent);
	}
	break;
	case GAMEOVER:
	{
		for (size_t y = 0; y < m_rows; y++)
		{ //y = 0 ~ (ROWS - 1)
			for (size_t x = 0; x < m_cols; x++)
			{
				App.getDC()->SetTransform(D2D1::Matrix3x2F::Translation(
					boardX + m_spacing + x * (BlockWidth + m_spacing), boardY + m_spacing + y * (BlockWidth + m_spacing)
				));

				App.fillRoundedRect(0.0f, 0.0f, BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f, getColor(0));
				if (this->m_board[y][x] != 0)
					App.fillRoundedRect(0.0f, 0.0f, BlockWidth, BlockWidth, BlockWidth * 0.1f, BlockWidth * 0.1f, this->getColor(this->m_board[y][x]));
				static wchar_t buf[32] = { 0 };
				wsprintfW(buf, L"%d", (int)pow(2, this->m_board[y][x]));
				if (this->m_board[y][x] != 0)
					App.drawCenterText(buf, { 0.0f, 0.0f }, BlockWidth, BlockWidth, getTextColor(this->m_board[y][x]), BlockWidth * getTextSize(this->m_board[y][x]));
			}
		}

		App.getDC()->SetTransform(D2D1::Matrix3x2F::Translation(
			0.0f, 0.0f
		));

		App.fillRect(0.0f, 0.0f, rc.right - rc.left, rc.bottom - rc.top, D2D1::ColorF(D2D1::ColorF::Orange, 0.5f));

		App.drawCenterText(L"GameOver!!", { 0.0f, 0.0f }, rc.right - rc.left, rc.bottom - rc.top, D2D1::ColorF(D2D1::ColorF::White), min(rc.right - rc.left, rc.bottom - rc.top) * 0.1f);
	}
	break;
	default:
		break;
	}
}

bool Board::isFailMove(int** thisArr, int** lastArr, int rows, int cols)
{
	for (size_t y = 0; y < rows; y++)
	{
		for (size_t x = 0; x < cols; x++)
		{
			if (lastArr[y][x] != thisArr[y][x])
			{
				return false;
			}
		}
	}
	return true;
}

DIR Board::aiGetMove(int** arr, int rows, int cols)
{
	bool flag = this->m_animation_switch;
	this->m_animation_switch = false;
	// Copy Map
	int** temp_board = new int* [rows];
	for (int i = 0; i < rows; i++)
		temp_board[i] = new int[cols];
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < cols; x++)
			temp_board[y][x] = arr[y][x];

	int** temp_last_board = new int* [rows];
	for (int i = 0; i < rows; i++)
		temp_last_board[i] = new int[cols];
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < cols; x++)
			temp_last_board[y][x] = arr[y][x];

	const int deep = 400;	// �������
	int scores[4][deep] = { 0 };

	for (int i = 0; i < deep; i++)
	{
		// UP
		int score = 0;
		for (int y = 0; y < rows; y++)
			for (int x = 0; x < cols; x++)
				temp_board[y][x] = arr[y][x];

		score += up(temp_board, rows, cols);
		while (!isGameOver(temp_board, rows, cols))
		{
			for (int y = 0; y < rows; y++)
				for (int x = 0; x < cols; x++)
					temp_last_board[y][x] = temp_board[y][x];

			score += move((DIR)(rand() % 4), temp_board, rows, cols);
			if(!isFailMove(temp_board, temp_last_board, rows, cols))
				randCell(temp_board, rows, cols);
		}
		scores[0][i] = score;

		// DOWN
		score = 0;
		for (int y = 0; y < rows; y++)
			for (int x = 0; x < cols; x++)
				temp_board[y][x] = arr[y][x];

		score += down(temp_board, rows, cols);
		while (!isGameOver(temp_board, rows, cols))
		{
			for (int y = 0; y < rows; y++)
				for (int x = 0; x < cols; x++)
					temp_last_board[y][x] = temp_board[y][x];

			score += move((DIR)(rand() % 4), temp_board, rows, cols);
			if (!isFailMove(temp_board, temp_last_board, rows, cols))
				randCell(temp_board, rows, cols);
		}
		scores[1][i] = score;

		// LEFT
		score = 0;
		for (int y = 0; y < rows; y++)
			for (int x = 0; x < cols; x++)
				temp_board[y][x] = arr[y][x];

		score += left(temp_board, rows, cols);
		while (!isGameOver(temp_board, rows, cols))
		{
			for (int y = 0; y < rows; y++)
				for (int x = 0; x < cols; x++)
					temp_last_board[y][x] = temp_board[y][x];

			score += move((DIR)(rand() % 4), temp_board, rows, cols);
			if (!isFailMove(temp_board, temp_last_board, rows, cols))
				randCell(temp_board, rows, cols);
		}
		scores[2][i] = score;

		// RIGHT
		score = 0;
		for (int y = 0; y < rows; y++)
			for (int x = 0; x < cols; x++)
				temp_board[y][x] = arr[y][x];

		score += right(temp_board, rows, cols);
		while (!isGameOver(temp_board, rows, cols))
		{
			for (int y = 0; y < rows; y++)
				for (int x = 0; x < cols; x++)
					temp_last_board[y][x] = temp_board[y][x];

			score += move((DIR)(rand() % 4), temp_board, rows, cols);
			if (!isFailMove(temp_board, temp_last_board, rows, cols))
				randCell(temp_board, rows, cols);
		}
		scores[3][i] = score;
	}

	int add[4] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j <= deep - 2; j++)
		{
			scores[i][0] += scores[i][j + 1];
		}
		add[i] = scores[i][0];
	}

	DIR dir = UP;

	int max = 0;
	max = add[0];
	for (int i = 0; i <= 4 - 1; i++)
	{
		//std::cout << add[i] << ' ';
		if (add[i] > max)
		{
			max = add[i];
			dir = (DIR)i;
		}
	}

	//std::cout << "MAX: " << dir << '\n';

	// Delete Temp Map
	for (int i = 0; i < rows; i++)
		delete[] temp_board[i];
	for (int i = 0; i < rows; i++)
		delete[] temp_last_board[i];
	this->m_animation_switch = flag;
	return dir;
}

int Board::move(DIR dir, int** arr, int rows, int cols)
{
	int s = 0;
	switch (dir)
	{
	case UP:
		s += this->up(arr, rows, cols);
		break;
	case DOWN:
		s += this->down(arr, rows, cols);
		break;
	case LEFT:
		s += this->left(arr, rows, cols);
		break;
	case RIGHT:
		s += this->right(arr, rows, cols);
		break;
	default: break;
	}
	return s;
}

void Board::setAnimation(bool flag)
{
	this->m_animation_switch = flag;
}

D2D1_COLOR_F Board::getColor(int num)
{
	static D2D1_COLOR_F color[13] =
	{
		D2D1::ColorF(238. / 255., 228. / 255., 218 / 255., 0.35f),// 0
		D2D1::ColorF(238. / 255., 228. / 255., 218. / 255.),	// 2
		D2D1::ColorF(237. / 255., 224. / 255., 200. / 255.),	// 4
		D2D1::ColorF(242. / 255., 177. / 255., 121. / 255.),	// 8
		D2D1::ColorF(245. / 255., 149. / 255., 99. / 255.),		// 16
		D2D1::ColorF(246. / 255., 124. / 255., 95. / 255.),		// 32
		D2D1::ColorF(246. / 255., 94. / 255., 59. / 255.),		// 64
		D2D1::ColorF(237. / 255., 207. / 255., 114. / 255.),	// 128
		D2D1::ColorF(237. / 255., 240. / 255., 97. / 255.),		// 256
		D2D1::ColorF(237. / 255., 200. / 255., 80. / 255.),		// 512
		D2D1::ColorF(237. / 255., 197. / 255., 63. / 255.),		// 1024
		D2D1::ColorF(237. / 255., 194. / 255., 46. / 255.),		// 2048
		D2D1::ColorF(60. / 255., 58. / 255., 50. / 255.),		// > 2048
	};

	if (num >= 12) return color[12];

	return color[num];
}

D2D1_COLOR_F Board::getTextColor(int num)
{
	if (num >= 3 && num <= 6) return D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);
	if (num >= 0 && num <= 2) return D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f);
	if (num >= 7 && num <= 11) return D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f);
	if (num >= 12) return D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);
}

float Board::getTextSize(int num)
{
	num = pow(2, num);
	if (num >= 0 && num <= 99)
	{
		return 0.5f;
	}
	else if (num >= 100 && num <= 999)
	{
		return 0.45f;
	}
	else if (num >= 1000 && num <= 9999)
	{
		return 0.35f;
	}
	else if (num >= 10000 && num <= 99999)
	{
		return 0.25f;
	}
	else if (num >= 100000 && num <= 999999)
	{
		return 0.1f;
	}
	else if (num >= 1000000 && num <= 9999999)
	{
		return 0.1f;
	}
	return 0.1f;
}

float Board::getTime()
{
	static DWORD last_time = 0;
	static DWORD now_time = 0;
	static DWORD time;

	now_time = timeGetTime();
	time = now_time - last_time;
	last_time = now_time;
	return (float)time / 1000.0f;
}
