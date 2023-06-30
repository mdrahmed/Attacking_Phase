### Python program
`table2.py` is the python program which is generating the table. To test the program give the valid input, which should be given after analyzing the `test-combined.txt` file. As this one contains the combination of both storing and removal of the `hbw` storage.

### General ideas
I need to test this program with the log by storing 1 value at a time and then removing 1 value at a time. In following,
```
F1 Unix: 1686260423
FFF Function: _ZN2ft26TxtHighBayWarehouseStorage5fetchENS_11TxtWPType_tE
Thu Jun  8 15:40:23 2023
TB Unix: 1686260423
loaded values: 0
Thu Jun  8 15:40:23 2023
TB Unix: 1686260423
loaded values: 0
Thu Jun  8 15:40:23 2023
TB Unix: 1686260423
loaded values: 0
Thu Jun  8 15:40:23 2023
TB Unix: 1686260423
loaded values: 0
Thu Jun  8 15:40:23 2023
TB Unix: 1686260423
loaded values: 2138033688
Thu Jun  8 15:40:23 2023
FB Unix: 1686260423
loaded values: 2
Thu Jun  8 15:40:23 2023
FB Unix: 1686260423
loaded values: 1
Thu Jun  8 15:40:23 2023
FB Unix: 1686260423
loaded values: 1
Thu Jun  8 15:40:23 2023
F1 Unix: 1686260423
```

The last `2,1,1` values of `loaded_values` can be the `nextFetchPos` and `found` 

For now, the logic is,
for storing the last `loaded values:0` should be 0
And for removing the last `loaded values: ` is used but need to consider the `nextFetchPos` and `found` variable.
