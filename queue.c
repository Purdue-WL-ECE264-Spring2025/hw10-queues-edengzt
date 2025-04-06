#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
   insert_at_tail(&(q->data), serialize(state));
}

struct game_state dequeue(struct queue *q) { 

    size_t moves = remove_from_head(&(q->data));
    struct game_state state = deserialize(moves);
    
    return state; 
}

int is_empty(struct queue *q) {
    return q->data.head == NULL;
}

int is_solved(struct game_state state) {    
    int solved[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

    for (int i = 0; i < 16; i++) {
        if (state.tiles[i / 4][i % 4] != solved[i]) {
            return 0;
        }
    }
    
    return 1;
}

int is_visited(struct queue q, struct game_state state) {
    struct list_node *cursor = (q.data).head;
    size_t num_steps = state.num_steps;
    size_t visited = serialize(state) - num_steps;

    while (cursor != NULL) {
        size_t cursor_val = (cursor -> value) - num_steps;
        if (cursor_val == visited) {
            return 1; // state is in the queue
        }
        cursor = cursor->next;
    }
    
    return 0;
}

int number_of_moves(struct game_state start) {
    struct queue q;
    q.data.head = NULL;
    enqueue(&q, start);

    while (!is_empty(&q)) {
        struct game_state current = dequeue(&q);

        if (is_solved(current)) {
            return current.num_steps; // Return the number of moves to solve
        }

        // Generate possible moves
        struct game_state next_states[4];
        int num_next_states = 0;

        if (current.empty_row > 0) {
            next_states[num_next_states++] = current;
            move_up(&next_states[num_next_states - 1]);
        }
        if (current.empty_row < 3) {
            next_states[num_next_states++] = current;
            move_down(&next_states[num_next_states - 1]);
        }
        if (current.empty_col > 0) {
            next_states[num_next_states++] = current;
            move_left(&next_states[num_next_states - 1]);
        }
        if (current.empty_col < 3) {
            next_states[num_next_states++] = current;
            move_right(&next_states[num_next_states - 1]);
        }

        // Enqueue new states if they haven't been visited
        for (int i = 0; i < num_next_states; i++) {
            if (!is_visited(q, next_states[i])) {
                enqueue(&q, next_states[i]);
            }
        }
    }
  
    return 0; // Return -1 if no solution is found
}