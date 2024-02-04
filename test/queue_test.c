#include "../src/queue.h"
#include "stdlib.h"
int main(int argc, char const *argv[])
{
    simple_queue* q = init_queue();

    char* msg = "This if message 1.";
    char* msg2 = "This is message 2.";
    char* msg3 = "This is message 3.";

    q_emplace_back(q, msg);
    q_emplace_back(q, msg2);
    q_emplace_back(q, msg3);

    free(q_pop(q));
    free(q_pop(q));
    free(q_pop(q));
    free_queue(q);
    return 0;
}
