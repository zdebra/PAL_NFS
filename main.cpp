#include <iostream>

struct Edge;
struct State;
void copy_array(bool *dest, bool* source, int len);
void clear_array(bool *dest, int len);
void init_array(bool *array, int len);
int fill_reachable(bool *dest, bool *active, State *states, int char_index, int len, int alphabet_size);
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
        scanf(" %d %c", &state, &is_final);
        states[i].is_final = is_final == 'F';
        states[i].heads = new Edge[alphabet_size];

        for(int j=0;j<alphabet_size;j++) {
            scanf(" %*c");

            Edge *cur = &states[i].heads[j];
            int iter = 0;
            int symbol; int ch;
            //char *seq = new char[3];
            while((ch=getc(stdin)) == ' ') {
            }
            if(ch!='\n') {

                ungetc(ch, stdin);

                while (scanf("%d", &symbol) > 0) {
                    if (iter == 0) {
                        states[i].heads[j].is_empty = false;
                    } else {
                        cur->next = new Edge();
                        cur = cur->next;
                    }
                    cur->end_index = symbol;
                    iter++;
                    while ((ch = getc(stdin)) == ' ') {
                    }
                    if (ch == '\n') {
                        break;
                    }
                    ungetc(ch, stdin);
                }
            }

        }

    }

    // reading a prefix
    char *prefix = new char[PREFIX_LEN];
    scanf("%s",prefix);
    int len = str_len(prefix);

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

    std::cout << prefix << ", " << len << std::endl;

    return 1; */
    bool active[states_count];
    bool reachable[states_count];

    // init
    clear_array(active, states_count);
    active[0] = true;

    // going through a prefix
    for(int i=0;i<len;i++) {

        // fills reachable states
        fill_reachable(reachable, active, states, prefix[i]-ASCI_DIFF, states_count, alphabet_size);

        // copy from reachable to active
        copy_array(active,reachable,states_count);

    }

    // going through rest of automata until there is at least one active state
    int active_state_count = fill_reachable(reachable, active, states, -1, states_count, alphabet_size);
    while(active_state_count > 0) {
        copy_array(active,reachable,states_count);
        active_state_count = fill_reachable(reachable, active, states, -1, states_count, alphabet_size);
    }

    // print output
    std::cout << MIN << " " << MAX << std::endl;

/*
    for(int i=0;i<states_count;i++) {
        std::cout << active[i] << std::endl;
    }


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

int fill_reachable(bool *dest, bool *active, State *states, int char_index, int len, int alphabet_size) {

    int count = 0;
    ITER++;

    // clear dest array
    clear_array(dest, len);

    /*
    std::cout << "ITER: " << ITER << ", ACTIVE" << std::endl;
    for(int i=0;i<len;i++) {
        std::cout << active[i] << std::endl;
    }
    std::cout << "**" << std::endl;
    */
    // going through all active states
    for(int i=0; i<len; i++) {

        if(active[i]) {
            count++;
            if(char_index < 0) {

                // for each character
                for(int j=0; j<alphabet_size; j++) {

                    Edge *cur = &states[i].heads[j];
                    if(!states[i].heads[j].is_empty) {
                        // going through all state's edges
                        while (cur != NULL) {
                            dest[cur->end_index] = true;

                            // check min/max here if the state is final
                            if(states[cur->end_index].is_final) {
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

            } else {

                Edge *cur = &states[i].heads[char_index];
                if(!states[i].heads[char_index].is_empty) {
                    // going through all state's edges
                    while (cur != NULL) {
                        dest[cur->end_index] = true;
                        cur = cur->next;
                    }
                }

            }


        }



    }

    /*
    std::cout << "ITER: " << ITER << ", REACHABLE:" << std::endl;
    for(int i=0;i<len;i++) {
        std::cout << dest[i] << std::endl;
    }
    std::cout << "----" << std::endl;
    std::cout << "----" << std::endl;
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