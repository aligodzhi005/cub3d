# cub3d
Для запуска необходимо:
1) перейти в папку с проектом
2) ввести команду make, чтобы собрать проект
3) ввести команду ./cub3D map.cub - второй аргумент это файл с картой, описание которой ниже

Описание файла с картой:
1-я строка задаёт разрешение
строки со 2-ой по 5-ой пути к текстурам стен
6-я строка путь к текстурке спрайта
7-я и 8-я строки цвет потолка и пола
остальные строки описывают саму карту
1 - стена
2 - спрайт
0 - пустое пространство
буква N,S,W или E - это место, где появляется герой и в какую сторону света он смотрит