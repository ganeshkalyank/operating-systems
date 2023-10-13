#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *isPrime(void *prarg) {
    printf("Enter a number: \n");
    int n;
    scanf("%d", &n);
    int flag = 1;
    for (int i=2;i<n;i++) {
        if (n%i == 0) flag = 0;
    }
    long int *tid = (long int *) prarg;
    if (flag == 1) printf("%d is a prime (%ld)\n",n,*tid);
    else printf("%d is not a prime (%ld)\n",n,*tid);
    return 0;
}

void *isArmstrong(void *ararg) {
    printf("Enter a number: \n");
    int n;
    scanf("%d", &n);
    int tmp = n,sum = 0;
    while (tmp!=0) {
        sum += (tmp%10)*(tmp%10)*(tmp%10);
        tmp/=10;
    }
    long int *tid = (long int *) ararg;
    if (n==sum) printf("%d is armstrong (%ld)\n",n,*tid);
    else printf("%d is not armstrong (%ld)\n",n,*tid);
    return 0;
}

int main() {
    pthread_t prime,armstrong;
    pthread_create(&prime, NULL, isPrime, (void *)&prime);
    pthread_create(&armstrong, NULL, isArmstrong, (void *)&armstrong);
    pthread_join(prime,NULL);
    pthread_join(armstrong,NULL);
    return 0;
}
