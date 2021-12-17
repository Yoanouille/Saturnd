#include "saturnd.h"

task *test(task *t, int *len) {
    char *argv[] = {"echo", "test", "1235"};
    commandline c;
    alloc_commandline(&c, 3, argv);
    timing time = {1,1,1};
    return add_task(t, len, 1, c, time);
}

task *test2(task *t, int *len) {
    char *argv[] = {"une", "commande", "pour", "tester", "si", "le", "malloc", "est", "bon"};
    commandline c;
    alloc_commandline(&c, 9, argv);
    timing time = {1,1,1};
    return add_task(t, len, 568, c, time);
}

task *test3(task *t, int *len) {
    char *argv[] = {"je", "sais", "plus", "quoi", "mettre", "comme", "commande"};
    commandline c;
    alloc_commandline(&c, 7, argv);
    timing time = {1,1,1};
    return add_task(t, len, 4008, c, time);
}


void print_task(task *t) {
    printf("taskid = %lu\n", t->taskid);
    printf("commandline : ");
    for(int i = 0; i < t->cmd.argc; i++) {
        printf("%s ", t->cmd.argv[i].str);
    }
    printf("\n");
}

void print_task_array(task *t, int len) {
    for(int i = 0; i < len; i++) {
        if(t[i].alive) print_task(t + i);
    }
}

int main(){
    int len = 3;
    task *t = create_task_array(len);
    t = test(t, &len);
    t = test2(t, &len);
    t = test3(t, &len);
    remove_task(t, len, 1);
    t = test3(t, &len);
    t = test(t, &len);
    print_task_array(t, len);
    do_create(*t);

    //test ls
    /*int fd0 = open("run/pipes/saturnd-request-pipe", O_RDONLY);
    char read_buf[sizeof(uint16_t)];
    read(fd0, read_buf, sizeof(uint16_t));
    
    int fd = open("run/pipes/saturnd-reply-pipe", O_WRONLY);

    int n = 0;
    char buf[4096];
    n += write_opcode(buf, SERVER_REPLY_OK);
    n += list(buf+n, t, len);
    write(fd, buf, n);

    free_task_array(t, len);*/

    //test times_exitcodes

    int fd_times_exitcodes = open("task/4008/times_exitcodes", O_WRONLY | O_CREAT);
    uint32_t nbruns = 2;
    write(fd_times_exitcodes, &nbruns, sizeof(int32_t));
    int64_t time = 1639752739;
    write(fd_times_exitcodes, &time, sizeof(int64_t));
    uint16_t exitcode = 0;
    write(fd_times_exitcodes, &exitcode, sizeof(int16_t));
    time = 1639754749;
    write(fd_times_exitcodes, &time, sizeof(int64_t));
    exitcode = 1;
    write(fd_times_exitcodes, &exitcode, sizeof(int16_t));


    int fd0 = open("run/pipes/saturnd-request-pipe", O_RDONLY);
    char read_buf[sizeof(uint16_t)];
    read(fd0, read_buf, sizeof(uint16_t));
    
    

    int n = 0;
    char buf[4096];
    n += times_exitcodes(fd0, buf, t, len);
    int fd = open("run/pipes/saturnd-reply-pipe", O_WRONLY | O_CREAT);
    write(fd, buf, n);

    free_task_array(t, len);

    return 0;
}
