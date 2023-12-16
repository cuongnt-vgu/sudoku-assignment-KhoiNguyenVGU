#include "hidden_triples.h"
#include "utils.h"
#include <stdlib.h>

int find_hidden_triples(Cell **p_cells, HiddenTriple *hidden_triples) {
    int num_triples = 0;

    for (int val1 = 1; val1 <= BOARD_SIZE; val1++) {
        for (int val2 = val1 + 1; val2 <= BOARD_SIZE; val2++) {
            for (int val3 = val2 + 1; val3 <= BOARD_SIZE; val3++) {
                Cell *cells_with_triple[3];
                int count = 0;

                for (int i = 0; i < BOARD_SIZE; i++) {
                    if (is_candidate(p_cells[i], val1) && is_candidate(p_cells[i], val2) && is_candidate(p_cells[i], val3)) {
                        if (count < 3) {
                            cells_with_triple[count] = p_cells[i];
                        }
                        count++;
                    }
                }

                if (count == 3 && (cells_with_triple[0]->num_candidates > 3 || cells_with_triple[1]->num_candidates > 3 || cells_with_triple[2]->num_candidates > 3)) {
                    hidden_triples[num_triples++] = (HiddenTriple){{cells_with_triple[0], cells_with_triple[1], cells_with_triple[2]}, {val1, val2, val3}};
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
        unset_other_candidates(hidden_triples[i].p_cells[0], hidden_triples[i].values, 3);
        unset_other_candidates(hidden_triples[i].p_cells[1], hidden_triples[i].values, 3);
        unset_other_candidates(hidden_triples[i].p_cells[2], hidden_triples[i].values, 3);
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