#include "parse_tree.h"
#include "utilities.h"
#include "pipes.h"
#include "execBatch.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char** argv){
    if(argc < 2){
        char message[] = "Usage: program notebook.nb";
        write(1,message, strlen(message));
        return 1;
    }
    //TODO maybe implement read from stdin '-'
    int fd = open(argv[1],O_RDONLY);
    char* buff;
    size_t len;
    Pipes mypipes = pipes_create(20); //TODO aloca isto 
    ParseTree pt = parse_tree_create(20);
    while(NULL != (buff = readln(fd, &len))){

        int batch = parse_tree_add_line(pt, buff, len);
        if(batch != -1){
            pipes_append(mypipes,batch);
            execBatch(parse_tree_get_batch(pt, batch),pipes_last(mypipes));
        }
    }
    

    close(fd);
    char** dump = parse_tree_dump(pt);
    fd = creat(argv[1],O_CREAT);
    int i = 0;
    while(dump[i])
        write(fd,dump,strlen(dump[i++]));

    return 0;
}
