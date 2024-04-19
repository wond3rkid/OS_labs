Программа выводит список команд:
```text
a - mkdir
b - ls
c - rmdir
d - touch
e - cat
f - rm file
g - create symlink
h - get symlink
i - cat symlink file
j - rm symlink
k - create hardlink
l - delete hardlink
m - get info about file
n - change rights
You have to input your command and argument!
```
Для команд **a - f** и **m - n** нужно передать **путь к файлу/директории** в зависимости от команды

Для команд g - l нужно передавать **soft/hard link**
Команда для создания **soft link**

```bash
ln -s <путь_к_оригинальному_файлу> <путь_к_символической_ссылке>
```

