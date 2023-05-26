# False data injection attack 

## For the C program present in test_c folder
The `example.c` file was supposed to print this `Original foo() function`. But it was intercepted with the `intercept.so` library and executed the false function `foo()`,
```
void foo() {
    printf("Intercepted foo() function\n");
}
```

Now, how it's done, compile the `example.c` in general way `gcc -o example example.c`. The do the following,
* At first, create the library `intercept.so`,
	```gcc -shared -fPIC -o intercept.so intercept.c```
* Now, use the shared libray to run the `example` executable, 
	```LD_PRELOAD=./intercept.so ./example```

**[Simply modifying the structs is not gonna work as there is a initialization process. To make that move, I will need to write the whole code like them and then call it.]**
