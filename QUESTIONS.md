#### 1. Компиляция, сборка, запуск:
- Таблица символов (утилита nm)
- Стек вызова функций
- Регистры общего назначения (rax/eax/ax, rbx, …), регистр FLAGS
- Ассемблерная инструкция mov (загрузить в регистр, [] - по адресу)
- Ассемблерные инструкции call/ret (записать/взять адрес со стека)
> Какой код на Си соответствует этому коду на ассемблере:
```asm 
    cmp rax, 10
    je .label
    add rax, 5
    .label:
  …
```
тот же код, но другой синтаксис, и расположение переменной другое
```asm
    cmp   8(%RBP), $10
    jeq    .label
    add   $5, 8(%RBP)
    .label: 
    …
```
```asm
    mov rax, 0
    .label1:
    cmp rax, 9
    jg .label2
    …
    add rax, 1
    jmp .label1
    .label2:
    …   
   ```
- ELF файл: секции, сегменты
- типы ELF файлов (DYN exec):
    - relocatable (REL Relocatable file) [.o]
  - shared object (DYN Shared object file) [.so]
  - PIE executable (DYN Position-Independent Executable file)
  - non-PIE executable (EXEC)
  - core (CORE Core file)
- Регистр IP/RIP (instruction pointer)
- Интерпретатор (ld-linux)
- position independent code (PIC/PIE / ASLR)
- LD_PRELOAD


#### 2. Системные вызовы:
- Прерывания (interrupts), системные вызовы
- Стандартные потоки ввода/вывода (stdin/STDIN_FILENO, stdout/STDOUT_FILENO, stderr/STDERR_FILENO)
- Переменная errno, сигналы (сигнал EINTR в том числе)
- vDSO


#### 3. Файлы и Файловые системы:
- Файлы, примеры файлов (например, регулярные, директории, символьные ссылки, FIFO трубы, сокеты, блочные, символьные)
- Файловый дескриптор
- inode
- Директория (почему это можно назвать таблицей)
- Жесткие и символьные ссылки
- Блокирующий ввод/вывод (неблокирующий будет нескоро - в задании на сеть с poll/select)
- file offset (смещение в файловом дескрипторе), lseek
- fsync
- sparse file
- page cache

#### 4. Адресное пространство процесса:

- Виртуальная память: адресное пространство процесса, стек
- Переменные среды исполнения/окружения
- Куча: как работает free
- fork, exec
- Куча: malloc (как работают brk и anonymous mmap)
- file mmap


#### 5. Создание, завершение процесса:
- Физическая память ОС, copy-on-write
- wait/waitpid, зомби (zombie), сироты (orphans), усыновление (adoption), уничтожение (reaping)
- clone (альтернатива fork)


#### 6. Межпроцессное взаимодействие:
- разделяемая память (MAP_SHARED / shm_open)
- unnamed pipes / named (FIFO)
- Unix domain sockets, их типы
