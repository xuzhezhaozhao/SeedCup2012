#define MAX_NUM_OF_YELLOW_WALLS 100
#define MAX_NUM_OF_DOORS 100
#define MAX_NUM_OF_TEARS 100

typedef struct Position {
	int row;	//行
	int col;	//列
}Position;

typedef enum { NOMAL, YELLOW } State;
typedef enum { OK, WRONG } DirectionState;

struct PathNode {
	Position p;		//该点的位置
	MoveDirection m;	//移动到该点的所用的操作
	int tears;		//到达该点时吃到的水珠数量
	Position tears_pos[MAX_NUM_OF_TEARS];	//到达该点时吃过的雨滴的位置
	State state;		//雨滴的状态，是否为黄色雨滴
	Position YellowWall[MAX_NUM_OF_YELLOW_WALLS];	//到达该点时被黄色雨滴穿过后的黄色墙壁的位置
	Position Door[MAX_NUM_OF_DOORS];		//到达该点时被雨滴穿过的门的位置
}
p = 0, p_up = 1, next = p_up
p = 1, p_right = 2, push (right), return p_right

PathNode BFS(PathNode p)
{
	PathNode next;
	if (向上走成功) {    
		p_up_state = OK;	//将向上的标志标记为可走
		p_up.p = getUpPos(); //得到向上走到的位置信息
		p_up.m = MoveUp;
		p_up.tears = p.tears + 向上走得到的雨滴;
		p_up.tears_pos 也要更新;
		p_up.state 雨滴状态更新;
		p_up.YellowWall 更新;
		p_up.Door 更新;
		
		if (tears == p_up.tears) {	// 雨滴全部吃完
			push(p_up.m);		//将相关操作压入栈中
			push(p.m);
			return p;		//返回该结点信息
		}
		
		EnQueue(p_up);			// 没有结束将该结点插入队列
	}
	
	if (向下走成功) {
	}
	
	if (向左走成功) {
	}
	
	if (向右走成功) {
	}
	
	
	DeQueue(q);
	next = BFS(q);
	if (	OK == p_up.state && Equal(p_up, next) 
	||	OK == p_down.state && Equal(p_down, next)
	||	OK == p_left.state && Equal(p_left, next)
	||	OK == p_right.state && Equal(p_right, next)) {
		push(p.m);	//说明p点也是最优路径上的点
		return p;
	} else {
		return next;
	}
}