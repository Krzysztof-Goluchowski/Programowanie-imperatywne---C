
#include <stdio.h>

#define STACK_SIZE 10

enum state { OK = 0, UNDERFLOW = -1, OVERFLOW = -2 };

int stack[STACK_SIZE];
int top = 0;

int stack_push(int x) {
    if (top<10){
        stack[top] = x;
        top++;
        return OK;
    }
    if (top >= 10){
        return OVERFLOW;
    }

}

int stack_pop(void) {
    if (top == 0){
        return UNDERFLOW;
    } else{
        top--;
        int tmp = stack[top];
        stack[top] = 0;
        return tmp;
    }

}

int stack_state(void) {
    for (int i = 0; i < 10; i++){
        if(stack[i] == 0) {
            return i;
        }
    }
    return 10;
}

// FIFO queue with shifts

#define QUEUE_SIZE 10

int queue[QUEUE_SIZE];
int in = 0, curr_nr = 0;

int queue_push(int in_nr) { // in_nr clients try to enter the queue
    do{
        if (in == 10){
            curr_nr = curr_nr + in_nr;
            return OVERFLOW;
        }
        queue[in] = curr_nr + 1;
        curr_nr++;
        in++;
        in_nr--;
    } while (in_nr > 0);
    return OK;
}

int queue_pop(int out_nr) {
    if (out_nr > in){
        for (int i = 0; i < in; i++){
            queue[i] = 0;
        }
        return UNDERFLOW;
    }
    in = in - out_nr;
    int wynik = in - out_nr;
    for(int i = 0; i < out_nr; i++){
        for(int j = 0; j < 9; j++){
            queue[j] = queue[j+1];
        }
        queue[9] = 0;
    }
    return wynik;
}

int queue_state(void) {
    return in;
}

void queue_print(void) {
    int i = 0;
    do{
        printf("%d ", queue[i]);
        i++;
    } while (queue[i] != 0);
}

// Queue with cyclic buffer

#define CBUFF_SIZE 10

int cbuff[CBUFF_SIZE];
int out = 0, len = 0;


int cbuff_push(int cli_nr) {
    if (len == 10){
        return OVERFLOW;
    }
    int nr_ind = (out+len)%10;
    cbuff[nr_ind] = cli_nr;
    len++;
    return OK;
}

int cbuff_pop(void) {
    if (len == 0){
        return UNDERFLOW;
    }
    len--;
    int wynik = cbuff[out];
    out++;
    return wynik;
}

int cbuff_state(void) {
    return len;
}

void cbuff_print(void) {
    for (int i = 0; i < len; i++){
        printf("%d ", cbuff[(out+i)%10]);
    }
}

int main(void) {
	int to_do, n, client_no, answer;
	scanf("%d", &to_do);
	switch(to_do) {
		case 1: // stack
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = stack_push(n)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					printf("%d ", stack_pop());
				} else printf("\n%d\n", stack_state());
			} while(n != 0);
			break;
		case 2: // FIFO queue with shifts
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = queue_push(n)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					if ((answer = queue_pop(-n)) < 0) printf("%d ", answer);
				} else {
					printf("\n%d\n", queue_state());
					queue_print();
				}
			} while(n != 0);
			break;
		case 3: // queue with cyclic buffer
			client_no = 0;
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = cbuff_push(++client_no)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					printf("%d ", cbuff_pop());
				} else {
					printf("\n%d\n", cbuff_state());
					cbuff_print();
				}
			} while(n != 0);
			break;
		default: 
			printf("NOTHING TO DO!\n");
	}
	return 0;
}
