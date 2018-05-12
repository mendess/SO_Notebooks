#ifndef PIPES_H
#define PIPES_H

typedef struct _pipes * Pipes;

Pipes pipes_create(int size);

void pipes_append(Pipes p);

int* pipes_index(Pipes p, int idx);

int* pipes_last(Pipes p);

void pipes_free(Pipes p);

#endif
