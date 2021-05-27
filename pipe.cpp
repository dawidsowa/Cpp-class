#include <stdio.h>
#include <unistd.h>

int main() {
    FILE *fp;
    int status;
    fp = popen("gnuplot -persist", "w");
    fprintf(fp, "plot '-' using 1:2 with lines\n1 2\n2 3\n4 5\ne\n");
    fflush(fp);
    sleep(5);
    fprintf(fp, "replot '-' using 1:2 with lines\n1 2\n2 3\n4 5\ne\n");

    pclose(fp);

    return 0;
}