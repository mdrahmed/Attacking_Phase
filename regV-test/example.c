#include<stdio.h>

int main(){
	int a,b;
	printf("Enter value a: ");
	scanf("%d", &a);
	printf("Enter value b: ");
	scanf("%d", &b);
	int i =0;
	while(i <= 10){
		printf("Updated or not a: %d, b: %d\n",a, b);
		i++;
	}
	return 0;
}
