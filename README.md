**slmean** - calculates the mean of the columns *k* for a window of size *w* from a stream of data supplied by *stdin*

```bash
... | slmean [-k 1 -w 1000] 
```

```-k``` - column (1-based) indices to perform the operation on. Multiple columns can be indicated by using a comma (e.g. ```-k 2,3```), by specifying a range (e.g. ```-k 1-3```) or both (e.g. ```-k 1,2,4-7```).

```-w``` - size of the window within which to calculate the mean.

Notes:
- The mean will only be calculated and output produced once *w* lines of input have been produced (i.e once the window is "full").
- Missing values are indicated by "NA" and will be ignored (i.e. the mean will be calculated over all other values in the window).
- The output is according to the input column order (not according to input given by ```-k```.
