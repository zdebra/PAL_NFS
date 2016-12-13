#include <iostream>

struct Edge;
struct State;

struct State {
    bool is_final = false;
    Edge *heads;
};

struct Edge {
    Edge *next;
    int end_index;
};


int main() {


    int states_count, alphabet_size;
    State *states;

    std::cin >> states_count;
    std::cin >> alphabet_size;

    states = new State[states_count];

    for(int i=0;i<states_count;i++) {

        int state; char is_final;
        scanf("%d %c", &state, &is_final);
        states[i].is_final = is_final == 'F';
        states[i].heads = new Edge[alphabet_size];

        for(int j=0;j<alphabet_size;j++) {
            Edge *cur = &states[i].heads[j];

            char character;
            scanf(" %c",&character);

            int symbol; char ch;
            // try to read first



            while(scanf("%c",&ch) > 0 && ch != '\n' && scanf("%d",&symbol) > 0) {
                cur->next = new Edge();
                cur = cur->next;
                cur->end_index = symbol;
            }

        }

    }


    // todo read prefix here



    for(int i=0;i<states_count;i++) {

        std::cout << "STATE: " << i << std::endl;

        for(int j=0;j<alphabet_size;j++) {

            std::cout << "char: " << j << "| ";
            Edge *cur = &states[i].heads[j];
            while(cur!=NULL) {
                std::cout << cur->end_index << ", ";
                cur = cur->next;
            }
            std::cout << std::endl;

        }

    }




        delete [] states;

    return 0;
}