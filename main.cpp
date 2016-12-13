#include <iostream>

struct Edge;
struct State;

struct State {
    bool is_final = false;
    Edge *heads;
};

struct Edge {
    Edge *next;
    State *end;
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
            Edge cur = states[i].heads[j];

            char character;
            scanf(" %c",&character);

            int symbol; char ch;
            while(scanf("%c",&ch) > 0 && ch != 0x0a && scanf("%d",&symbol) > 0) {
                cur.end = &states[symbol];
                cur.next = new Edge;
                cur = *cur.next;
            }

        }

    }

    // todo read prefix here



    delete [] states;

    return 0;
}