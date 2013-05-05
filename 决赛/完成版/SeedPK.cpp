#include "SeedPK.h"

using namespace std;

/* �궨�� */
#define MAX_NUM_OF_YELLOW_WALLS 20	/* ��ɫǽ������ */
#define MAX_NUM_OF_DOORS 20		/* �ŵ������� */
#define MAX_NUM_OF_pearlS 20		/* ��������� */
#define MAX_VISITED_TIMES 3		/* һ��·����ͬһ��λ�ñ���ྭ���Ĵ��� */
#define MAX_VEX_NUM	100		/* ·���ϵ�������� */

/* �ṹ���� */
typedef struct Position {	/* ��λ�ýṹ */
	int row;		/* �� */
	int col;		/* �� */
}Position;
typedef enum { UP, DOWN, LEFT, RIGHT } Direction;
typedef enum { NORMAL, YELLOW } State;	/* ���״̬ */

typedef struct {
	Position pos;		/* ���ʵĵ�λ�� */
	MoveDirection move;	/* ����õ���ƶ���ʽ */
}visited_t;
typedef struct PathNode {		/* ·���ϵĽ�� */
	Position pos;		/* �õ��λ�� */
	int pearls;		/* ����õ�ʱ�Ե���ˮ������ */
	Position pearls_pos[MAX_NUM_OF_pearlS];	/* ����õ�ʱ�Թ�����ε�λ�� */
	State state;		/* ��ε�״̬���Ƿ�Ϊ��ɫ��� */

	int yellowWalls;	/* �����Ļ�ɫǽ�ڵ����� */
	/* ����õ�ʱ����ɫ��δ�����Ļ�ɫǽ�ڵ�λ�� */
	Position yellowWalls_pos[MAX_NUM_OF_YELLOW_WALLS];
	int doors;		/* �������ŵ����� */
	/* ����õ�ʱ����δ������ŵ�λ�� */
	Position doors_pos[MAX_NUM_OF_DOORS];

	int visited_vex_num;	/* �����λ��ʱ���ʹ��ĵ�ĸ��� */
	visited_t visited_vex[MAX_VEX_NUM];	/* ���ʹ��ĵ�λ�� */
}PathNode;

typedef PathNode QElemType;

/* ���ж��� */
typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct {		/* ���������� */
	QueuePtr front;		/* ��ͷָ�� */
	QueuePtr rear;		/* ��βָ�� */
}LinkQueue; 
/***************************************/

/* �������� */
int InitQueue (LinkQueue &Q);
int EnQueue(LinkQueue &Q, QElemType e);
int DeQueue(LinkQueue &Q, QElemType &e);
Position getInitDropPosition(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount);
void InitDropState(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode &initDropNode);
bool throughedOpenDoor_bool(PathNode p, Position door_pos);
bool throughedYellowWall_bool(PathNode p, Position door_dos);
bool infinityLoop_bool(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p, Direction di);
bool goDirection_bool(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p, Direction di);
bool eatenPearl(PathNode p, Position pearl_pos);
PathNode getUp_upgrade(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p);
PathNode getDown_upgrade(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p);
PathNode getLeft_upgrade(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p);
PathNode getRight_upgrade(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p);
int getMyPearlCount(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount);
PathNode BFS(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode &p, LinkQueue &Q);
int upgradeVisitedVex(PathNode &p);
bool isOverVisited(PathNode p);

/**
 * ȫ�ֱ���
 */
int pearlsCount = 0;

/* ������ */
list<MoveDirection> solutionToMap(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
		int rowCount, int columnCount)
{
	list<MoveDirection> moveList;
	PathNode initDropNode, p, movePath;
	LinkQueue Q;
	moveList.clear();
	InitQueue(Q);
	InitDropState(quellReflectMap, rowCount, columnCount, initDropNode);
	pearlsCount = getMyPearlCount(quellReflectMap, rowCount, columnCount);

	p = initDropNode;
	movePath = BFS(quellReflectMap, rowCount, columnCount, p, Q);
   
	for (int i = 1; i < movePath.visited_vex_num; i++) {
		moveList.push_back(movePath.visited_vex[i].move);
	}

	return moveList;
}

string teamNameToDisplay()
{
	/* ����ΪӢ�ģ���С��20���ַ� */
	return "xzz";
}

/**
 * ����һ���ն���Q
 */
int InitQueue (LinkQueue &Q)
{
	Q.front = (QNode *) malloc (sizeof(QNode));
	if (!Q.front) 
		return -1;
	Q.front->next = NULL;
	Q.rear = Q.front;
	return 0;
}

/**
 * ����Ԫ��eΪQ���µĶ�βԪ��
 */
int EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;
	p = (QNode *) malloc (sizeof(QNode));   //�����µĽ��
	if (!p)
		return -1;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 0;
}

/**
 * �����в��գ�ɾ������Q�Ķ�ͷԪ�أ���e������ֵ������OK�����򷵻�ERROR
 */
int DeQueue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;
	p = Q.front->next;
	if (Q.front == Q.rear)
		return -1;
	e = p->data;
	if (Q.front->next == Q.rear)	//������ֻ��һ��Ԫ��ʱ����Ҫ�޸�βָ��
		Q.rear = Q.front;
	Q.front->next = p->next;
	free(p);
	p = NULL;
	return 0;
}

/**
 * �õ���ʼʱ����ڵ�ͼ�е�λ��,����0��ʼ
 */
Position getInitDropPosition(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
		int rowCount, int columnCount)
{
	int row, col;
	Position p;
	for (row = 0 ; row < rowCount; row++) {
		for (col = 0; col < columnCount; col++) {
			if (CellRainDrop == quellReflectMap[row][col]) {
				p.col = col;
				p.row = row;
			}
		}
	}
	return p;
}

/**
 * ��ʼ�����״̬
 */
void InitDropState(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode &initDropNode)
{
	Position initPos;
	initPos = getInitDropPosition(quellReflectMap, 
		rowCount, columnCount);
	initDropNode.pos.col		= initPos.col;
	initDropNode.pos.row		= initPos.row;
	initDropNode.pearls		= 0;
	initDropNode.doors		= 0;
	initDropNode.yellowWalls	= 0;
	initDropNode.state		= NORMAL;
	initDropNode.visited_vex_num	= 1;
	initDropNode.visited_vex[0].pos.col	= initPos.col;
	initDropNode.visited_vex[0].pos.row	= initPos.row;
}

/**
 * �жϿ����Ƿ���δ�����������������true�����򷵻�false
 */
bool throughedOpenDoor_bool(PathNode p, Position door_pos)
{
	int i;
	for (i = 0; i < p.doors; i++) {
		if (	p.doors_pos[i].col == door_pos.col
		&&	p.doors_pos[i].row == door_pos.row) {
			return true;
		}
	}
	return false;
}

/**
 * �жϻ�ɫ��ǽ�Ƿ���δ�����������������true�����򷵻�false
 */
bool throughedYellowWall_bool(PathNode p, Position wall_pos)
{
	int i;
	for (i = 0; i < p.yellowWalls; i++) {
		if (	p.yellowWalls_pos[i].col == wall_pos.col
		&&	p.yellowWalls_pos[i].row == wall_pos.row) {
				return true;
		}
	}
	return false;
}

/**
 * �ж������ָ�������Ƿ������ѭ�����Ƿ���true�����򷵻�falae
 */
bool infinityLoop_bool(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p, Direction di)
{
	int i;
	int row, col;
	Position yellowWall_pos, pearl_pos;
	PathNode pt;
	CellState cell;
	row = p.pos.row;
	col = p.pos.col;
	pt = p;
	switch(di) {
	case UP:
		for (i = 0; i < rowCount; i++) {
			if (	CellNormalWall	== quellReflectMap[i][pt.pos.col]
			||	CellOpenGate	== quellReflectMap[i][pt.pos.col] ) {
				return false;
			}
		}
		/* û����ͨǽ�Ϳ��ŵ��������Ӱ���ֻ�л�ɫǽ�ںͻ�ɫˮ�� */
		for (i = row - 1;; i--) {
			if (i < 0) {
				i = rowCount - 1;
			}
			cell = quellReflectMap[i][col];
			yellowWall_pos.row = pearl_pos.row = i;
			yellowWall_pos.col = pearl_pos.col = col;
			if (CellYellowPearl == cell && !eatenPearl(pt, pearl_pos)) {
				pt.state = YELLOW;
				pt.pearls_pos[pt.pearls].row = i;
				pt.pearls_pos[pt.pearls].col = col;
				pt.pearls++;
			}
			if (CellYellowWall == cell && !throughedYellowWall_bool(pt, yellowWall_pos)) {
				if (YELLOW == pt.state) {	/* ��ͨ�� */
					pt.state = NORMAL;
					pt.yellowWalls_pos[pt.yellowWalls].row = i;
					pt.yellowWalls_pos[pt.yellowWalls].col = col;
					pt.yellowWalls++;
				} else {		/* ����ͨ�� */
					return false;
				}
			}
			if (i == row) {			/* �ص�ԭ����λ����, ѭ�� */
				return true;
			}
		}
		break;
	case DOWN:
		for (i = 0; i < rowCount; i++) {
			if (	CellNormalWall	== quellReflectMap[i][pt.pos.col]
			||	CellOpenGate	== quellReflectMap[i][pt.pos.col] ) {
				return false;
			}
		}
		/* û����ͨǽ�Ϳ��ŵ��������Ӱ���ֻ�л�ɫǽ�ںͻ�ɫˮ�� */
		for (i = row + 1;; i++) {
			if (i == rowCount) {
				i = 0;
			}
			cell = quellReflectMap[i][col];
			yellowWall_pos.row = pearl_pos.row = i;
			yellowWall_pos.col = pearl_pos.col = col;
			if (CellYellowPearl == cell && !eatenPearl(pt, pearl_pos)) {
				pt.state = YELLOW;
				pt.pearls_pos[pt.pearls].row = i;
				pt.pearls_pos[pt.pearls].col = col;
				pt.pearls++;
			}
			if (CellYellowWall == cell && !throughedYellowWall_bool(pt, yellowWall_pos)) {
				if (YELLOW == pt.state) {	/* ��ͨ�� */
					pt.state = NORMAL;
					pt.yellowWalls_pos[pt.yellowWalls].row = i;
					pt.yellowWalls_pos[pt.yellowWalls].col = col;
					pt.yellowWalls++;
				} else {		/* ����ͨ�� */
					return false;
				}
			}
			if (i == row) {			/* �ص�ԭ����λ����, ѭ�� */
				return true;
			}
		}
		break;
	case LEFT:
		for (i = 0; i < columnCount; i++) {
			if (	CellNormalWall	== quellReflectMap[row][i]
			||	CellOpenGate	== quellReflectMap[row][i] ) {
				return false;
			}
		}
		/* û����ͨǽ�Ϳ��ŵ��������Ӱ���ֻ�л�ɫǽ�ںͻ�ɫˮ�� */
		for (i = col - 1;; i--) {
			if (i < 0) {
				i = columnCount - 1;
			}
			cell = quellReflectMap[row][i];
			yellowWall_pos.row = pearl_pos.row = row;
			yellowWall_pos.col = pearl_pos.col = i;
			if (CellYellowPearl == cell && !eatenPearl(pt, pearl_pos)) {
				pt.state = YELLOW;
				pt.pearls_pos[pt.pearls].row = row;
				pt.pearls_pos[pt.pearls].col = i;
				pt.pearls++;
			}
			if (CellYellowWall == cell && !throughedYellowWall_bool(pt, yellowWall_pos)) {
				if (YELLOW == pt.state) {	/* ��ͨ�� */
					pt.state = NORMAL;
					pt.yellowWalls_pos[pt.yellowWalls].row = row;
					pt.yellowWalls_pos[pt.yellowWalls].col = i;
					pt.yellowWalls++;
				} else {		/* ����ͨ�� */
					return false;
				}
			}
			if (i == col) {			/* �ص�ԭ����λ����, ѭ�� */
				return true;
			}
		}
		break;
	case RIGHT:
		for (i = 0; i < columnCount; i++) {
			if (	CellNormalWall	== quellReflectMap[row][i]
			||	CellOpenGate	== quellReflectMap[row][i] ) {
				return false;
			}
		}
		/* û����ͨǽ�Ϳ��ŵ��������Ӱ���ֻ�л�ɫǽ�ںͻ�ɫˮ�� */
		for (i = col + 1;; i++) {
			if (i == columnCount) {
				i = 0;
			}
			cell = quellReflectMap[row][i];
			yellowWall_pos.row = pearl_pos.row = row;
			yellowWall_pos.col = pearl_pos.col = i;
			if (CellYellowPearl == cell && !eatenPearl(pt, pearl_pos)) {
				pt.state = YELLOW;
				pt.pearls_pos[pt.pearls].row = row;
				pt.pearls_pos[pt.pearls].col = i;
				pt.pearls++;
			}
			if (CellYellowWall == cell && !throughedYellowWall_bool(pt, yellowWall_pos)) {
				if (YELLOW == pt.state) {	/* ��ͨ�� */
					pt.state = NORMAL;
					pt.yellowWalls_pos[pt.yellowWalls].row = row;
					pt.yellowWalls_pos[pt.yellowWalls].col = i;
					pt.yellowWalls++;
				} else {		/* ����ͨ�� */
					return false;
				}
			}
			if (i == col) {			/* �ص�ԭ����λ����, ѭ�� */
				return true;
			}
		}
		break;
	}
}

/**
 * �ж������ָ���������Ƿ����ߣ����ܷ�ı䵱ǰλ�ã���������ѭ��Ҳ�ǲ����ߣ�
 * �ܷ���true�����ܷ���false
 */
bool goDirection_bool(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
		int rowCount, int columnCount, PathNode p, Direction di)
{
	int next_row;
	int next_col;
	int col;
	int row;
	CellState next_cell;
	Position door_pos, yellowWall_pos;
	col = p.pos.col;
	row = p.pos.row;
	switch (di) {
	case UP:
		if (0 == p.pos.row) {
			next_row = rowCount - 1;
		} else {
			next_row = p.pos.row - 1;
		}
		next_cell = quellReflectMap[next_row][col];
		door_pos.row =next_row;
		door_pos.col = col;
		break;
	case DOWN:
		if ((rowCount - 1) == p.pos.row) {
			next_row = 0;
		} else {
			next_row = p.pos.row + 1;
		}
		next_cell = quellReflectMap[next_row][col];
		door_pos.row =next_row;
		door_pos.col = col;
		break;
	case LEFT:
		if (0 == p.pos.col) {
			next_col = columnCount - 1;
		} else {
			next_col = p.pos.col - 1;
		}
		next_cell = quellReflectMap[row][next_col];
		door_pos.row =row;
		door_pos.col = next_col;
		break;
	case RIGHT:
		if ((columnCount - 1) == p.pos.col) {
			next_col = 0;
		} else {
			next_col = p.pos.col + 1;
		}
		next_cell = quellReflectMap[row][next_col];
		door_pos.row = row;
		door_pos.col = next_col;
		break;
	}
	yellowWall_pos.col = door_pos.col;
	yellowWall_pos.row = door_pos.row;
	if (infinityLoop_bool(quellReflectMap, rowCount, columnCount, p, di)) {
		return false;
	}
	if (	CellNormalWall == next_cell
	||	(CellYellowWall == next_cell && !throughedYellowWall_bool(p, yellowWall_pos) && NORMAL == p.state)
	||	(CellOpenGate == next_cell && throughedOpenDoor_bool(p, door_pos))) {
		return false;
	} else {
		return true;
	}
}

/**
 * �ж�ָ��λ�õ�����Ƿ��Ѿ������ˣ����˷���true�����򷵻�false 
 */
bool eatenPearl(PathNode p, Position pearl_pos)
{
	int i;
	for (i = 0; i < p.pearls; i++) {
		if (	p.pearls_pos[i].row == pearl_pos.row
		&&	p.pearls_pos[i].col == pearl_pos.col) {
			return true;
		}
	}
	return false;
}

/**
 * ���·��ʵĽ����Ϣ
 */
int upgradeVisitedVex(PathNode &p)
{
	p.visited_vex[p.visited_vex_num].pos.row = p.pos.row;
	p.visited_vex[p.visited_vex_num].pos.col = p.pos.col;
	p.visited_vex_num++;
	return 0;
}

/**
 * �жϸý����ʴ����Ƿ񳬹�MAX_VISITED_TIMES,
 * ��������true�����򷵻�false
 */
bool isOverVisited(PathNode p)
{
	int i;
	int count = 0;
	for (i = 0; i < p.visited_vex_num; i++) {
		if (p.visited_vex[i].pos.col == p.pos.col
		&& p.visited_vex[i].pos.row == p.pos.row) {
			count++;
		}
	}
	if (count >= MAX_VISITED_TIMES) {
		return true;
	} else {
		return false;
	}
}

/**
 * �ӵ�p�����ߣ������½�����Ϣ��ǰ���Ǹ÷�������
 */
PathNode getUp_upgrade(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p)
{
	int i, row, col;
	PathNode next_p;	/* ��һ���� */
	CellState cell;
	Position pearl_pos, wall_pos, door_pos;
	next_p = p;
	row = p.pos.row;
	col = p.pos.col;
	for (i = row - 1;; i--) {
		if (i < 0) {
			i = rowCount - 1;
		}
		cell = quellReflectMap[i][col];
		pearl_pos.row = wall_pos.row = door_pos.row = i;
		pearl_pos.col = wall_pos.col = door_pos.col = col;
		
		if (CellNormalPearl == cell && !eatenPearl(p, pearl_pos)) {	/* ��ͨˮ�� */
			next_p.pearls_pos[next_p.pearls].col = col;
			next_p.pearls_pos[next_p.pearls].row = i;
			next_p.pearls++;
		} else if (CellNormalWall == cell) {	/* ��ͨǽ�� */
			next_p.pos.col = col;
			if (i == rowCount - 1) {
				next_p.pos.row = 0;
			} else {
				next_p.pos.row = i + 1;
			}
			return next_p;
		} else if (CellYellowPearl == cell && !eatenPearl(p, pearl_pos)) {	/* ��ɫˮ�� */
			next_p.pearls_pos[next_p.pearls].col = col;
			next_p.pearls_pos[next_p.pearls].row = i;
			next_p.pearls++;
			next_p.state = YELLOW;		/* ��Ϊ��ɫ��� */
		} else if (CellYellowWall == cell && !throughedYellowWall_bool(p, wall_pos)) {	/* ��ɫǽ�� */
			if (NORMAL == next_p.state) {
				next_p.pos.col = col;
				if (i == rowCount - 1) {
					next_p.pos.row = 0;
				} else {
					next_p.pos.row = i + 1;
				}
				return next_p;
			} else {
				next_p.yellowWalls_pos[next_p.yellowWalls].row = i;
				next_p.yellowWalls_pos[next_p.yellowWalls].col = col;
				next_p.yellowWalls++;
				next_p.state = NORMAL;
			}
		} else if (CellOpenGate == cell) {	/* ���� */
			if (throughedOpenDoor_bool(p, door_pos)) {	/* ����ͨ�� */	
				next_p.pos.col = col;
				if (i == rowCount - 1) {
					next_p.pos.row = 0;
				} else {
					next_p.pos.row = i + 1;
				}
				return next_p;
			} else {	/* ��ͨ�� */
				next_p.doors_pos[next_p.doors].row = i;
				next_p.doors_pos[next_p.doors].col = col;
				next_p.doors++;
			}
		} else {
			;
		}
	}
}

/**
 * �ӵ�p�����ߣ������½�����Ϣ��ǰ���Ǹ÷�������
 */
PathNode getDown_upgrade(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p)
{
	int i, row, col;
	PathNode next_p;	/* ��һ���� */
	CellState cell;
	Position pearl_pos, wall_pos, door_pos;
	next_p = p;
	row = p.pos.row;
	col = p.pos.col;
	for (i = row + 1;; i++) {
		if (i  == rowCount) {
			i = 0;
		}
		cell = quellReflectMap[i][col];
		pearl_pos.row = wall_pos.row = door_pos.row = i;
		pearl_pos.col = wall_pos.col = door_pos.col = col;
		
		if (CellNormalPearl == cell && !eatenPearl(p, pearl_pos)) {	/* ��ͨˮ�� */
			next_p.pearls_pos[next_p.pearls].col = col;
			next_p.pearls_pos[next_p.pearls].row = i;
			next_p.pearls++;
		} else if (CellNormalWall == cell) {	/* ��ͨǽ�� */
			next_p.pos.col = col;
			if (i == 0) {
				next_p.pos.row = rowCount - 1;
			} else {
				next_p.pos.row = i - 1;
			}
			return next_p;
		} else if (CellYellowPearl == cell && !eatenPearl(p, pearl_pos)) {	/* ��ɫˮ�� */
			next_p.pearls_pos[next_p.pearls].col = col;
			next_p.pearls_pos[next_p.pearls].row = i;
			next_p.pearls++;
			next_p.state = YELLOW;		/* ��Ϊ��ɫ��� */
		} else if (CellYellowWall == cell && !throughedYellowWall_bool(p, wall_pos)) {	/* ��ɫǽ�� */
			if (NORMAL == next_p.state) {		/* ���ܴ��� */
				next_p.pos.col = col;
				if (i == 0) {
					next_p.pos.row = rowCount - 1;
				} else {
					next_p.pos.row = i - 1;
				}
				return next_p;
			} else {			/* �ܴ��� */
				next_p.yellowWalls_pos[next_p.yellowWalls].row = i;
				next_p.yellowWalls_pos[next_p.yellowWalls].col = col;
				next_p.yellowWalls++;
				next_p.state = NORMAL;
			}
		} else if (CellOpenGate == cell) {	/* ���� */
			if (throughedOpenDoor_bool(p, door_pos)) {	/* ����ͨ�� */	
				next_p.pos.col = col;
				if (i == 0) {
					next_p.pos.row = rowCount - 1;
				} else {
					next_p.pos.row = i - 1;
				}
				return next_p;
			} else {	/* ��ͨ�� */
				next_p.doors_pos[next_p.doors].row = i;
				next_p.doors_pos[next_p.doors].col = col;
				next_p.doors++;
			}
		} else {
			;
		}
	}
}

/**
 * �ӵ�p�����ߣ������½�����Ϣ��ǰ���Ǹ÷�������
 */
PathNode getLeft_upgrade(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p)
{
	int i, row, col;
	PathNode next_p;	/* ��һ���� */
	CellState cell;
	Position pearl_pos, wall_pos, door_pos;
	next_p = p;
	row = p.pos.row;
	col = p.pos.col;
	for (i = col - 1;; i--) {
		if (i  < 0) {
			i = columnCount - 1;
		}
		cell = quellReflectMap[row][i];
		pearl_pos.row = wall_pos.row = door_pos.row = row;
		pearl_pos.col = wall_pos.col = door_pos.col = i;
		
		if (CellNormalPearl == cell && !eatenPearl(p, pearl_pos)) {	/* ��ͨˮ�� */
			next_p.pearls_pos[next_p.pearls].col = i;
			next_p.pearls_pos[next_p.pearls].row = row;
			next_p.pearls++;
		} else if (CellNormalWall == cell) {	/* ��ͨǽ�� */
			next_p.pos.row = row;
			if (i == columnCount - 1) {
				next_p.pos.col = 0;
			} else {
				next_p.pos.col = i + 1;
			}
			return next_p;
		} else if (CellYellowPearl == cell && !eatenPearl(p, pearl_pos)) {	/* ��ɫˮ�� */
			next_p.pearls_pos[next_p.pearls].col = i;
			next_p.pearls_pos[next_p.pearls].row = row;
			next_p.pearls++;
			next_p.state = YELLOW;		/* ��Ϊ��ɫ��� */
		} else if (CellYellowWall == cell && !throughedYellowWall_bool(p, wall_pos)) {	/* ��ɫǽ�� */
			if (NORMAL == next_p.state) {		/* ���ܴ��� */
				next_p.pos.row = row;
				if (i == columnCount - 1) {
					next_p.pos.col = 0;
				} else {
					next_p.pos.col = i + 1;
				}
				return next_p;
			} else {			/* �ܴ��� */
				next_p.yellowWalls_pos[next_p.yellowWalls].row = row;
				next_p.yellowWalls_pos[next_p.yellowWalls].col = i;
				next_p.yellowWalls++;
				next_p.state = NORMAL;
			}
		} else if (CellOpenGate == cell) {	/* ���� */
			if (throughedOpenDoor_bool(p, door_pos)) {	/* ����ͨ�� */	
				next_p.pos.row = row;
				if (i == columnCount - 1) {
					next_p.pos.col = 0;
				} else {
					next_p.pos.col = i + 1;
				}
				return next_p;
			} else {	/* ��ͨ�� */
				next_p.doors_pos[next_p.doors].row = row;
				next_p.doors_pos[next_p.doors].col = i;
				next_p.doors++;
			}
		} else {
			;
		}
	}
}

/**
 * �ӵ�p�����ߣ������½�����Ϣ��ǰ���Ǹ÷�������
 */
PathNode getRight_upgrade(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode p)
{
	int i, row, col;
	PathNode next_p;	/* ��һ���� */
	CellState cell;
	Position pearl_pos, wall_pos, door_pos;
	next_p = p;
	row = p.pos.row;
	col = p.pos.col;
	for (i = col + 1;; i++) {
		if (i  == columnCount) {
			i = 0;
		}
		cell = quellReflectMap[row][i];
		pearl_pos.row = wall_pos.row = door_pos.row = row;
		pearl_pos.col = wall_pos.col = door_pos.col = i;
		
		if (CellNormalPearl == cell && !eatenPearl(p, pearl_pos)) {	/* ��ͨˮ�� */
			next_p.pearls_pos[next_p.pearls].col = i;
			next_p.pearls_pos[next_p.pearls].row = row;
			next_p.pearls++;
		} else if (CellNormalWall == cell) {	/* ��ͨǽ�� */
			next_p.pos.row = row;
			if (i == 0) {
				next_p.pos.col = columnCount - 1;
			} else {
				next_p.pos.col = i - 1;
			}
			return next_p;
		} else if (CellYellowPearl == cell && !eatenPearl(p, pearl_pos)) {	/* ��ɫˮ�� */
			next_p.pearls_pos[next_p.pearls].col = i;
			next_p.pearls_pos[next_p.pearls].row = row;
			next_p.pearls++;
			next_p.state = YELLOW;		/* ��Ϊ��ɫ��� */
		} else if (CellYellowWall == cell && !throughedYellowWall_bool(p, wall_pos)) {	/* ��ɫǽ�� */
			if (NORMAL == next_p.state) {		/* ���ܴ��� */
				next_p.pos.row = row;
				if (i == 0) {
					next_p.pos.col = columnCount - 1;
				} else {
					next_p.pos.col = i - 1;
				}
				return next_p;
			} else {			/* �ܴ��� */
				next_p.yellowWalls_pos[next_p.yellowWalls].row = row;
				next_p.yellowWalls_pos[next_p.yellowWalls].col = i;
				next_p.yellowWalls++;
				next_p.state = NORMAL;
			}
		} else if (CellOpenGate == cell) {	/* ���� */
			if (throughedOpenDoor_bool(p, door_pos)) {	/* ����ͨ�� */	
				next_p.pos.row = row;
				if (i == 0) {
					next_p.pos.col = columnCount - 1;
				} else {
					next_p.pos.col = i - 1;
				}
				return next_p;
			} else {	/* ��ͨ�� */
				next_p.doors_pos[next_p.doors].row = row;
				next_p.doors_pos[next_p.doors].col = i;
				next_p.doors++;
			}
		} else {
			;
		}
	}
}

/**
 * �õ���ͼ��ˮ��ĸ���
 */
int getMyPearlCount(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
		int rowCount, int columnCount)
{
	int row, col, count;
	count = 0;
	for (row = 0; row < rowCount; row++) {
		for (col = 0; col < columnCount; col++) {
			if (	CellNormalPearl == quellReflectMap[row][col] 
			||	CellYellowPearl == quellReflectMap[row][col]) {
				count++;
			}
		}
	}
	return count;
}

/**
 * �ӵ�p���������������·������������·�������һ����㣬����ڷ��ʽ���򱣴�·�������н��
 * ��������
 * ��Ҫ�õݹ飬��Ϊ�ݹ����̫�����ջ�ռ䲻�㡣
 */
PathNode BFS(CellState quellReflectMap[MaxMapRow][MaxMapColumn], 
	int rowCount, int columnCount, PathNode &p, LinkQueue &Q)
{
	bool finish = false;
	PathNode p_up, p_down, p_left, p_right;
	
	while (!finish) {
		if (goDirection_bool(quellReflectMap, rowCount, columnCount, p, UP)) {
			p_up = getUp_upgrade(quellReflectMap, rowCount, columnCount, p);
			if (!isOverVisited(p_up)) {	/* p_up�����ʴ���û�г������� */
				upgradeVisitedVex(p_up);
				p_up.visited_vex[p_up.visited_vex_num-1].move = MoveUp;
				if (pearlsCount == p_up.pearls) {	/* ���� */
					finish = true;
					return p_up;	
				}
				EnQueue(Q, p_up);
			}
		}

		if (goDirection_bool(quellReflectMap, rowCount, columnCount, p, DOWN)) {
			p_down = getDown_upgrade(quellReflectMap, rowCount, columnCount, p);
			if (!isOverVisited(p_down)) {
				upgradeVisitedVex(p_down);
				p_down.visited_vex[p_down.visited_vex_num-1].move = MoveDown;
				if (pearlsCount == p_down.pearls) {	/* ���� */
					finish = true;
					return p_down;
				}
				EnQueue(Q, p_down);
			}
		}

		if (goDirection_bool(quellReflectMap, rowCount, columnCount, p, LEFT)) {
			p_left = getLeft_upgrade(quellReflectMap, rowCount, columnCount, p);
			if (!isOverVisited(p_left)) {
				upgradeVisitedVex(p_left);
				p_left.visited_vex[p_left.visited_vex_num-1].move = MoveLeft;
				if (pearlsCount == p_left.pearls) {	/* ���� */
					finish = true;
					return p_left;
				}
				EnQueue(Q, p_left);
			}
		}

		if (goDirection_bool(quellReflectMap, rowCount, columnCount, p, RIGHT)) {
			p_right = getRight_upgrade(quellReflectMap, rowCount, columnCount, p);
			if (!isOverVisited(p_right)) {
					upgradeVisitedVex(p_right);
					p_right.visited_vex[p_right.visited_vex_num-1].move = MoveRight;
					if (pearlsCount == p_right.pearls) {	/* ���� */
					finish = true;
					return p_right;
				}
				EnQueue(Q, p_right);		
			}	
		}

		DeQueue(Q, p);
	}
}