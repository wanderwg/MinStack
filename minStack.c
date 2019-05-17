typedef int SDataType;
typedef struct Stack
{
	SDataType* _array;
	int _top;
	int _capacity;
}Stack;
void StackInit(Stack* ps) {
	assert(ps);
	ps->_array = (SDataType*)malloc(sizeof(SDataType) * 3);
	if (ps->_array == NULL) {
		assert(0);
		return;
	}
	ps->_capacity = 3;
	ps->_top = 0;
}

void StackDestory(Stack* ps) {
	assert(ps);
	if (ps->_array) {
		free(ps->_array);
		ps->_capacity = 0;
		ps->_top = 0;
	}
}

void CheckCapacity(Stack* ps) {
	assert(ps);
	if (ps->_capacity == ps->_top) {
		int newCapacity = ps->_capacity * 2;
		SDataType* pTemp = (SDataType*)malloc(sizeof(SDataType)*newCapacity);
		if (pTemp == NULL) {
			assert(0);
			return;
		}
		for (int i = 0; i < ps->_top; ++i) {
			pTemp[i] = ps->_array[i];
		}
		free(ps->_array);
		ps->_array = pTemp;
		ps->_capacity = newCapacity;
	}
}

void StackPush(Stack* ps, SDataType data) {
	CheckCapacity(ps);
	ps->_array[ps->_top++] = data;
}
void StackPop(Stack* ps) {
	assert(ps);
	if (StackEmpty(ps))
		return;
	ps->_top--;
}
SDataType StackTop(Stack* ps) {
	assert(ps);
	return ps->_array[ps->_top - 1];
}
int StackEmpty(Stack* ps) {
	assert(ps);
	return ps->_top == 0;
}
int StackSize(Stack* ps) {
	assert(ps);
	return ps->_top;
}
typedef struct {
	Stack ds;//存储数据
	Stack ms;//存储最小值
} MinStack;

/** initialize your data structure here. */

MinStack* minStackCreate() {
	MinStack* pms = (MinStack*)malloc(sizeof(MinStack));
	if (pms == NULL) {
		assert(0);
		return NULL;
	}
	StackInit(&pms->ds);
	StackInit(&pms->ms);
	return pms;
}

void minStackPush(MinStack* obj, int x) {
	assert(obj);
	StackPush(&obj->ds,x);
	if (StackEmpty(&obj->ms)||x<=StackTop(&obj->ms)) {
		StackPush(&obj->ms,x);
	}
}

void minStackPop(MinStack* obj) {
	assert(obj);
	if (StackTop(&obj->ds) == StackTop(&obj->ms))
		StackPop(&obj->ms);
	StackPop(&obj->ds);
}

int minStackTop(MinStack* obj) {
	assert(obj);
	return StackTop(&obj->ds);
}

int minStackGetMin(MinStack* obj) {
	assert(obj);
	return StackTop(&obj->ms);
}

void minStackFree(MinStack* obj) {
	StackDestory(&obj->ds);
	StackDestory(&obj->ms);
	free(obj);
}
