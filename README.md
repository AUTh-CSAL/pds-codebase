# pds-codebase
Repo for course 050 - Parallel and Distributed Systems, Aristotle University of Thessaloniki, Dpt. of Electrical & Computer Engineering. 

## Instructions
### non-local-means denoising filter
If you are using Matlab you can use the files as they are under the folder `matlab`. If you are using GNU Octave, just apply the 
[patch](./octave_diff.patch) present in the root of the git repository 
```shell
$ git apply octave_diff.patch
```
and run this in Octave either using the GUI or the CLI 
```shell
$ cd matlab/
$ octave pipeline_non_local_means.m
``` 
