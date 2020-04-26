used three different implementations : 
* dynamically allocated array
* map
* set

 x| ```MatriceDynamique``` | ```MatriceMap``` |```MatriceSet```
 --- | --- | --- | ---
 i<100 ```int``` | 9.1293e-05 s | 0.00718578 s | 8.2796e-05 s
 i<100000 ```int``` | 0.0652805 s | 7.23497 s | 3.22224 s
 i<100000 ```double``` | 0.0739427 s | 7.66935 s | 3.20412 s
i<1000000 ```double``` | **0.749437** s | **72.4547** s | **32.4821** s

