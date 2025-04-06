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

int is_visited(struct game_state state, struct linked_list visited) {
    struct list_node *cursor = visited.head;
    size_t num_steps = state.num_steps;
    size_t check_val = serialize(state) - num_steps;
    size_t cursor_val;
    // struct game_state cursor_state;

    while (cursor != NULL) {
        cursor_val = (cursor -> value);
        // cursor_state = deserialize(cursor_val);
        // cursor_val -= cursor_state.num_steps;
        
        if (cursor_val == check_val) {
            return 1; // state is in the queue
        }
        cursor = cursor->next;
    }
    
    return 0;
}

int number_of_moves(struct game_state start) {
    struct linked_list visited;
    struct queue q;
    q.data.head = NULL;
    enqueue(&q, start);
    struct game_state current;

     // Generate possible moves
    //  struct game_state next_states[4];
    //  int num_next_states = 0;

    while (!is_empty(&q)) {

        // dequeue the next state
        current = dequeue(&q);

        if (is_visited(current, visited)) {
            // num_next_states = 0; // Reset for the next iteration
            continue; // Skip if already visited
        }

        if (is_solved(current)) {
            return current.num_steps; // Return the number of moves to solve
        }

        if (current.empty_row < 3) {
            // next_states[num_next_states++] = current;
            // move_up(&next_states[num_next_states - 1]);
            // enqueue(&q, next_states[num_next_states - 1]);
            // insert_at_head(&visited, serialize(next_states[num_next_states - 1]) - current.num_steps - 1);
            move_up(&current);
            enqueue(&q, current);
            move_down(&current);
            current.num_steps-=2;
            insert_at_head(&visited, serialize(current) - current.num_steps);
        }
        if (current.empty_row > 0) {
            // next_states[num_next_states++] = current;
            // move_down(&next_states[num_next_states - 1]);
            // enqueue(&q, next_states[num_next_states - 1]);
            // insert_at_head(&visited, serialize(next_states[num_next_states - 1]) - current.num_steps - 1);
            move_down(&current);
            enqueue(&q, current);
            move_up(&current);
            current.num_steps-=2;
            insert_at_head(&visited, serialize(current) - current.num_steps);
        }
        if (current.empty_col < 3) {
            // next_states[num_next_states++] = current;
            // move_left(&next_states[num_next_states - 1]);
            // enqueue(&q, next_states[num_next_states - 1]);
            // insert_at_head(&visited, serialize(next_states[num_next_states - 1]) - current.num_steps - 1);
            move_left(&current);
            enqueue(&q, current);
            move_right(&current);
            current.num_steps-=2;
            insert_at_head(&visited, serialize(current) - current.num_steps);
        }
        if (current.empty_col > 0) {
            // next_states[num_next_states++] = current;
            // move_right(&next_states[num_next_states - 1]);
            // enqueue(&q, next_states[num_next_states - 1]);
            // insert_at_head(&visited, serialize(next_states[num_next_states - 1]) - current.num_steps - 1);
            move_right(&current);
            enqueue(&q, current);
            move_left(&current);
            current.num_steps-=2;
            insert_at_head(&visited, serialize(current) - current.num_steps);
        }

        // // Enqueue new states if they haven't been visited
        // for (int i = 0; i < num_next_states; i++) {
        //     if (!is_visited(next_states[i], visited)) {
        //         enqueue(&q, next_states[i]);
        //     }
        // }

        // num_next_states = 0; // Reset for the next iteration
    }
  
    return current.num_steps; // Return -1 if no solution is found
}