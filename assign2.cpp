//Assignnment 2 code (Hamming Code)
#include<stdio.h>
#define MAX 7
int main()
{
    int arr[MAX];
    int i;
    int count_p1=0;
    int count_p2=0;
    int count_p3=0;
    int count_s1=0;
    int count_s2=0;
    int count_s3=0;
    int s1, s2, s3;
    int receiver[MAX];
    for(i=0; i<=6; i++)
    {
        arr[i]=0;
    }
    int sender_code;
    printf("\nEnter sender code (4-bit): ");
    scanf("%d", &sender_code);
    printf("\nThe sender code is: %d", sender_code);
    
    int rem;
    for(i=6; i>=0; i--)
    {
        if(i!=3 && i!=5 && i!=6)
        {
            rem = sender_code%10;
            sender_code=sender_code/10;
            arr[i]=rem;
        }
    }
    printf("\nThe array is: ");
    for(i=0; i<=6; i++)
    {
        printf("%d", arr[i]);
    }
    //p1= 3, 6, 7
    for(i=0; i<MAX; i++)
    {
        if((i==0 || i==2 || i==4) && arr[i]==1)
        {
            count_p1++;
        }
    }
    if(count_p1%2==0)
    {
        arr[6]=0;
    }
    else
    {
        arr[6]=1;
    }
    printf("\nThe array after calculating p1 is: ");
    for(i=0; i<=6; i++)
    {
        printf("%d", arr[i]);
    }
    for(i=0; i<MAX; i++)
    {
        if((i==0 || i==1 || i==4) && arr[i]==1)
        {
            count_p2++;
        }
    }
    if(count_p2%2==0)
    {
        arr[5]=0;
    }
    else
    {
        arr[5]=1;
    }
    printf("\nThe array after calculating p2 is: ");
    for(i=0; i<=6; i++)
    {
        printf("%d", arr[i]);
    }
    for(i=0; i<MAX; i++)
    {
        if((i==0 || i==1 || i==2) && arr[i]==1)
        {
            count_p3++;
        }
    }
    if(count_p3%2==0)
    {
        arr[3]=0;
    }
    else
    {
        arr[3]=1;
    }
    printf("\nThe array after calculating p3 is: ");
    for(i=0; i<=6; i++)
    {
        printf("%d", arr[i]);
    }
    
    
    
    //Receiver's code 
    
    printf("\nEnter receiver's code (7-bit): ");
    for(i=0; i<MAX; i++)
    {
        scanf("%d", &receiver[i]);
    }
    for(i=0; i<MAX; i++)
    {
        if((i==0 || i==2 || i==4 || i==6) && receiver[i]==1)
        {
            count_s1++;
        }
    }
    if(count_s1%2==0)
    {
        s1=0;
    }
    else
    {
        s1=1;
    }
    for(i=0; i<MAX; i++)
    {
        if((i==0 || i==1 || i==4 || i==5) && receiver[i]==1)
        {
            count_s2++;
        }
    }
    if(count_s2%2==0)
    {
        s2=0;
    }
    else
    {
        s2=1;
    }
    for(i=0; i<MAX; i++)
    {
        if((i==0 || i==1 || i==2 || i==3) && receiver[i]==1)
        {
            count_s3++;
        }
    }
    if(count_s3%2==0)
    {
        s3=0;
    }
    else
    {
        s3=1;
    }
    
    if(s1==1 || s2==1 || s3==1)
    {
        printf("\nError detected. Bit position is: %d", s3*4+s2*2+s1);
        if(receiver[7-(s3*4+s2*2+s1)]==0)
        {
            receiver[7-(s3*4+s2*2+s1)]=1;
        }
        else
        {
            receiver[7-(s3*4+s2*2+s1)]=0;
        }
        printf("\n Corrected receiver's code (7-bit): ");
        for(i=0; i<MAX; i++)
        {
            printf("%d", receiver[i]);
        }
    }
    else
    {
        printf("\nNo error detected");
    }
    
}
