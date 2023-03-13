#include "linuxHeader.h"
#include <workflow/WFFacilities.h>
static WFFacilities::WaitGroup waitGroup(1);
void sighandler(int signum) {
    printf("wait group done!\n");
    waitGroup.done();
}

int main() {
    signal(SIGINT,sighandler);
    waitGroup.wait();
    return 0;
}
