#include <iostream>

struct Edge;
struct State;
void copy_array(bool *dest, bool* source, int len);
void clear_array(bool *dest, int len);
void init_array(bool *array, int len);
int fill_reachable(bool *dest, bool *active, State *states, int char_index, int len);
int str_len(char* str);

int PREFIX_LEN = 1000;
int ASCI_DIFF = 97;
int MAX = 0;
int MIN = 0;
int ITER = 0;

struct State {
    bool is_final = false;
    Edge *heads;
};

struct Edge {
    Edge *next;
    int end_index;
    bool is_empty = true;
};

bool* REF_ARRAY;

int main() {


    int states_count, alphabet_size;
    State *states;

    std::cin >> states_count;
    std::cin >> alphabet_size;

    states = new State[states_count];
    REF_ARRAY = new bool[states_count];
    init_array(REF_ARRAY, states_count);

    for(int i=0;i<states_count;i++) {

        int state; char is_final;
        scanf("%d %c", &state, &is_final);
        states[i].is_final = is_final == 'F';
        states[i].heads = new Edge[alphabet_size];

        for(int j=0;j<alphabet_size;j++) {
            char character;
            scanf(" %c",&character);

            Edge *cur = &states[i].heads[j];
            int iter = 0;
            int symbol; char ch;
            while(scanf("%c",&ch) > 0 && ch != '\n' && scanf("%d",&symbol) > 0) {
                if(iter==0) {
                    states[i].heads[j].is_empty = false;
                } else {
                    cur->next = new Edge();
                    cur = cur->next;
                }
                cur->end_index = symbol;
                iter++;
            }

        }

    }

    // reading a prefix
    char *prefix = new char[PREFIX_LEN];
    scanf("%s",prefix);
    int len = str_len(prefix);

    bool active[states_count];
    bool reachable[states_count];

    // init
    clear_array(active, states_count);
    active[0] = true;

    // going through a prefix
    for(int i=0;i<len;i++) {

        // fills reachable states
        fill_reachable(reachable, active, states, prefix[i]-ASCI_DIFF, states_count);

        // copy from reachable to active
        copy_array(active,reachable,states_count);

    }

    for(int i=0;i<states_count;i++) {
        std::cout << active[i] << std::endl;
    }

    /*
    for(int i=0;i<states_count;i++) {

        std::cout << "STATE: " << i << std::endl;

        for(int j=0;j<alphabet_size;j++) {

            std::cout << "char: " << j << "| ";
            Edge *cur = &states[i].heads[j];
            if(!cur->is_empty) {
                while (cur != NULL) {
                    std::cout << cur->end_index << ", ";
                    cur = cur->next;
                }
            }

            std::cout << std::endl;

        }

    }

    std::cout << prefix << std::endl;
    */



    delete [] states;

    return 0;
}

void clear_array(bool *dest, int len) {
    copy_array(dest,REF_ARRAY,len);
}

void copy_array(bool *dest, bool* source, int len) {
    memcpy(dest,source,len);
}

void init_array(bool* array, int len) {
    for(int i=0; i<len; i++) {
        array[i] = false;
    }
}

int fill_reachable(bool *dest, bool *active, State *states, int char_index, int len) {

    int count = 0;
    ITER++;

    // clear dest array
    clear_array(dest, len);

    // going through all active states
    for(int i=0; i<len; i++) {

        if(active[i]) {
            count++;
            Edge *cur = &states[i].heads[char_index];
            if(!states[i].heads->is_empty) {
                // going through all state's edges
                while (cur != NULL) {
                    dest[cur->end_index] = true;

                    // check min/max here if the state is final
                    if(char_index < 0 && states[cur->end_index].is_final) {
                        if(MIN==0||ITER<MIN) {
                            MIN = ITER;
                        }
                        if(ITER>MAX) {
                            MAX = ITER;
                        }
                    }

                    cur = cur->next;
                }
            }

        }

    }

    /*
    for(int i=0;i<len;i++) {
        std::cout << active[i] << std::endl;
    }

    std::cout << "aloha" << std::endl;

    */
    return count;


}

int str_len(char* str) {
    int i = 0;
    while(str[i] != '\0') {
        i++;
    }
    return i;

}