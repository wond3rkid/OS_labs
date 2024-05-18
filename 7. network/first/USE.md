1. Компилируем оба файла:

```c 
gcc -o udp_client udp_client.c
gcc -o udp_server udp_server.c
```

2. Запускаем сервер с портом n

```c 
./udp_server n
```

3. В другом терминале запускаем клиент следующей командой. n используем такое же, как в прошлой команде.

```c
./udp_client localhost n "Hi i am first client"
```