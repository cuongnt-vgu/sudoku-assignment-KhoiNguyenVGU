#include "naked_pairs.h"
#include "utils.h"

#include <stdlib.h>

int find_naked_pairs(Cell **p_cells, NakedPair *naked_pairs) {
    int num_pairs = 0;

    for (int i = 0; i < BOARD_SIZE - 1; i++) {
        for (int j = i + 1; j < BOARD_SIZE; j++) {
            // Check if the cells have the same set of two candidates
            if (p_cells[i]->num_candidates == 2 &&
                p_cells[j]->num_candidates == 2 &&
                same_candidates(p_cells[i], p_cells[j])) {

                // Check if the set of two values is not in any other cells
                if (!is_in_list_naked_pairs(naked_pairs, num_pairs, &(p_cells[i]), get_candidates(p_cells[i]))) {
                    naked_pairs[num_pairs++] = (NakedPair){{p_cells[i], p_cells[j]},
                                                            {p_cells[i]->candidates[0],
                                                             p_cells[i]->candidates[1]}};
                }
            }
        }
    }

    return num_pairs;
}

bool is_in_list_naked_pairs(NakedPair *p_array, int size, Cell **p_cells, int *values) {
    for (int i = 0; i < size; i++) {
        if ((p_cells[0] == p_array[i].p_cells[0] && p_cells[1] == p_array[i].p_cells[1]) ||
            (p_cells[0] == p_array[i].p_cells[1] && p_cells[1] == p_array[i].p_cells[0]) ||
            (values[0] == p_array[i].values[0] && values[1] == p_array[i].values[1]) ||
            (values[0] == p_array[i].values[1] && values[1] == p_array[i].values[0])) {
            return true;
        }
    }
    return false;
}

void find_naked_pairs_in_group(Cell **p_group, NakedPair *naked_pairs, int *p_counter) {
    int pairs_in_group = find_naked_pairs(p_group, naked_pairs);
    for (int i = 0; i < pairs_in_group; i++) {
        unset_other_candidates(naked_pairs[i].p_cells[0], naked_pairs[i].values, 2);
        unset_other_candidates(naked_pairs[i].p_cells[1], naked_pairs[i].values, 2);
        (*p_counter)++;
    }
}

int naked_pairs(SudokuBoard *p_board) {
    int naked_pairs_counter = 0;
    NakedPair naked_pairs[BOARD_SIZE * BOARD_SIZE];

    // Check rows for naked pairs
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_naked_pairs_in_group(p_board->p_rows[i], naked_pairs, &naked_pairs_counter);
    }

    // Check columns for naked pairs
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_naked_pairs_in_group(p_board->p_cols[i], naked_pairs, &naked_pairs_counter);
    }

    // Check boxes for naked pairs
    for (int i = 0; i < BOARD_SIZE; i++) {
        find_naked_pairs_in_group(p_board->p_boxes[i], naked_pairs, &naked_pairs_counter);
    }

    return naked_pairs_counter;
}