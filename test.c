// #include<stdio.h>
#include "mymalloc.h"

int main()
{
    int *ptr1 = (int *)MyMalloc(sizeof(int));                       // 4
    printf("ptr1 : %d\tAllocated size : %lu\n", ptr1, sizeof(int)); // 24+4=28

    double *ptr2 = (double *)MyMalloc(sizeof(double));                 // 8
    printf("ptr2 : %d\tAllocated size : %lu\n", ptr2, sizeof(double)); // 24+28+8=60

    char *ptr3 = (char *)MyMalloc(100 * sizeof(char));     // 100
    printf("ptr3 : %d\tAllocated size : %d\n", ptr3, 100); // 60+24+100=184

    float *ptr5 = (float *)MyMalloc(10 * sizeof(float));  // 40
    printf("ptr5 : %d\tAllocated size : %d\n", ptr5, 40); // 184+40+24=248

    MyFree(ptr1); // free 4
    MyFree(ptr2); // free 100+4=104
    MyFree(ptr3); // free 8+104=112

    int *ptr6 = (int *)MyMalloc(24000);                      // 24000
    printf("ptr6 : %d\tAllocated size : %d\n", ptr6, 24000); // 24024+248-112=24160

    int *ptr7 = (int *)MyMalloc(500);                      // 500
    printf("ptr7 : %d\tAllocated size : %d\n", ptr7, 500); // 24160+524=24684

    int *ptr8 = (int *)MyMalloc(200);                        // 200
    printf("ptr8 : %d\t\tAllocated size : %d\n", ptr8, 200); // 24684+224=24908 

    int *ptr9 = (int *)MyMalloc(40);                        // 40
    printf("ptr9 : %d\tAllocated size : %d\n", ptr9, 40);   // 24908+40+24=24972

    int *ptr10 = (int *)MyMalloc(50);
    printf("ptr10 : %d\tAllocated size : %d\n", ptr10, 50); // Palaweni set eken 50 -> 56+66=122    -------22 ---6

    int *ptr11 = (int *)MyMalloc(220);
    printf("ptr11 : %d\t\tAllocated size : %d\n", ptr11, 220); // overflow

    int *ptr12 = (int *)MyMalloc(100);
    printf("ptr12 : %d\t\tAllocated size : %d\n", ptr12, 100); // overflow

    int *ptr13 = (int *)MyMalloc(30);                       // 30
    printf("ptr13 : %d\tAllocated size : %d\n", ptr13, 30); // Anthim set eken 24924+46=24970     ---------30  ---14

    int *ptr14 = (int *)MyMalloc(6);
    printf("ptr14 : %d\tAllocated size : %d\n", ptr14, 6); // overflow

    int *ptr15 = (int *)MyMalloc(10);
    printf("ptr15 : %d\tAllocated size : %d\n", ptr15, 10); // ytama eka full denn wenw

    int *ptr16 = (int *)MyMalloc(4);
    printf("ptr16 : %d\tAllocated size : %d\n", ptr16, 4); // uda eken full denn wenw

    MyFree(ptr10); // free 50
    MyFree(ptr9);  // free 40
    MyFree(ptr6);  // free 160

    int *ptr17 = (int *)MyMalloc(160);
    printf("ptr17 : %d\t\tAllocated size : %d\n", ptr17, 160); // ptr4 enn one

    int *ptr18 = (int *)MyMalloc(20);
    printf("ptr18 : %d\tAllocated size : %d\n", ptr18, 10); // ptr9 enn one

    int *ptr19 = (int *)MyMalloc(200);
    printf("ptr19 : %d\t\tAllocated size : %d\n", ptr19, 200); // overflow

    return 0;
}
