#define N 5
#define semaphor int
semaphor hashi[N] = {2, 0, 1, 2, 0};
semaphor mutex = 1;
void philosofer(int i) {
    while (true) {
        think();
        down(hashi[i]);
        down(hashi[i]);
        eat();
        up(hashi[(i==0?N-1,i-1)]);
        up(hashi[(i + 1) % n]);
    }
}