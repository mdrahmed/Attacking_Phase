# False data injection attack 

## For the C program present in test_c folder
The `example.cpp` file was supposed to print this `Original foo() function`. But it was intercepted with the `intercept.so` library and executed the false function `foo()`,
```
void foo() {
    printf("Intercepted foo() function\n");
}
```

Now, how it's done, compile the `example.cpp` in general way `g++ -o example example.cpp`. The do the following,
* At first, create the library `intercept.so`,
	```gcc -shared -fPIC -o intercept.so intercept.c```
* Now, use the shared libray to run the `example` executable, 
	```LD_PRELOAD=./intercept.so ./example```


