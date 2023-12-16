#include "hidden_triples.h"
#include "utils.h"
#include <stdlib.h>

int find_hidden_triples(Cell **p_cells, HiddenTriple *hidden_triples) {
    int num_triples = 0;

    for (int i = 0; i < BOARD_SIZE - 2; i++) {
        for (int j = i + 1; j < BOARD_SIZE - 1; j++) {
            for (int k = j + 1; k < BOARD_SIZE; k++) {
                // Check if the cells have the same set of three candidates
                if (p_cells[i]->num_candidates == 3 &&
                    p_cells[j]->num_candidates == 3 &&
                    p_cells[k]->num_candidates == 3 &&
                    same_candidates(p_cells[i], p_cells[j]) &&
                    same_candidates(p_cells[i], p_cells[k])) {

                    // Check if the set of three values is not in any other cells
                    if (!is_in_list_hidden_triples(hidden_triples, num_triples, &(p_cells[i]), get_candidates(p_cells[i]))) {
                        hidden_triples[num_triples++] = (HiddenTriple){{p_cells[i], p_cells[j], p_cells[k]},
                                                                      {p_cells[i]->candidates[0],
                                                                       p_cells[i]->candidates[1],
                                                                       p_cells[i]->candidates[2]}};
                    }
                }
            }
        }
    }

    return num_triples;
}

bool is_in_list_hidden_triples(HiddenTriple *p_array, int size, Cell **p_cells, int *values) {
    for (int i = 0; i < size; i++) {
        if ((p_cells[0] == p_array[i].p_cells[0] && p_cells[1] == p_array[i].p_cells[1] && p_cells[2] == p_array[i].p_cells[2]) ||
            (p_cells[0] == p_array[i].p_cells[0] && p_cells[1] == p_array[i].p_cells[2] && p_cells[2] == p_array[i].p_cells[1]) ||
            (p_cells[0] == p_array[i].p_cells[1] && p_cells[1] == p_array[i].p_cells[0] && p_cells[2] == p_array[i].p_cells[2]) ||
            (p_cells[0] == p_array[i].p_cells[1] && p_cells[1] == p_array[i].p_cells[2] && p_cells[2] == p_array[i].p_cells[0]) ||
            (p_cells[0] == p_array[i].p_cells[2] && p_cells[1] == p_array[i].p_cells[0] && p_cells[2] == p_array[i].p_cells[1]) ||
            (p_cells[0] == p_array[i].p_cells[2] && p_cells[1] == p_array[i].p_cells[1] && p_cells[2] == p_array[i].p_cells[0]) ||
            (values[0] == p_array[i].values[0] && values[1] == p_array[i].values[1] && values[2] == p_array[i].values[2]) ||
            (values[0] == p_array[i].values[0] && values[1] == p_array[i].values[2] && values[2] == p_array[i].values[1]) ||
            (values[0] == p_array[i].values[1] && values[1] == p_array[i].values[0] && values[2] == p_array[i].values[2]) ||
            (values[0] == p_array[i].values[1] && values[1] == p_array[i].values[2] && values[2] == p_array[i].values[0]) ||
            (values[0] == p_array[i].values[2] && values[1] == p_array[i].values[0] && values[2] == p_array[i].values[1]) ||
            (values[0] == p_array[i].values[2] && values[1] == p_array[i].values[1] && values[2] == p_array[i].values[0])) {
            return true;
        }
    }
    return false;
}

void find_hidden_triples_in_group(Cell **p_group, HiddenTriple *hidden_triples, int *p_counter) {
    int triples_in_group = find_hidden_triples(p_group, hidden_triples);
    for (int i = 0; i < triples_in_group; i++) {
        set_candidates(hidden_triples[i].p_cells[0], hidden_triples[i].values, 3);
        set_candidates(hidden_triples[i].p_cells[1], hidden_triples[i].values, 3);
        set_candidates(hidden_triples[i].p_cells[2], hidden_triples[i].values, 3);
        (*p_counter)++;
    }
}

int hidden_triples(SudokuBoard *p_board) {
    int hidden_triples_counter = 0;
    HiddenTriple hidden_triples[BOARD_SIZE * BOARD_SIZE];

    // Check rows for hidden triples
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_triples_in_group(p_board->p_rows[i], hidden_triples, &hidden_triples_counter);
    }

    // Check columns for hidden triples
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_triples_in_group(p_board->p_cols[i], hidden_triples, &hidden_triples_counter);
    }

    // Check boxes for hidden triples
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_hidden_triples_in_group(p_board->p_boxes[i], hidden_triples, &hidden_triples_counter);
    }

    return hidden_triples_counter;
}