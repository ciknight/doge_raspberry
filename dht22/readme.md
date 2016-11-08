## Raspberry Pi dht22

DHT22 为温度传感器模块，比 DHT11 精度更高

### dht22.c

使用 wiringPi 包开发

> gcc -lwiringPi dht22.c -o dht22.o
> sudo ./dht22.o

### pydht22.c

为 python 封装的 c 扩展模块，可在 python 中直接导入

> gcc -fpic -c -I/usr/include/python2.7 -I /usr/lib/python2.7/config dht22.c pydht22.c -lwiringPi
> gcc -shared -o pydht22.so dht22.o pydht22.o
