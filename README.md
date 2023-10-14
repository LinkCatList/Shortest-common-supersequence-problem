# Shortest-common-supersequence-problem
https://en.wikipedia.org/wiki/Shortest_common_supersequence_problem

# За подробным описанием в Description.pdf

Я представлю один из самый простых жадных алгоритмов, который можно придумать для этой задачи, его можно улучшать локальными оптимизациями как и в плане асимптотики, так и в плане оптимальности ответа.
Ну хорошо, мы поняли, что нам хочется набрать все самый длинные $overlap$'ы, тогда давайте переберем все пары строк и для каждой насчитаем сначала максимальный суффикс первой строки, совпадающий с перфиксом второй, а потом максимальный префикс первой строки, совпадающий с суффиксом второй. Это можно сделать честно перебрав строки и суффикс, а потом взятием подстроки, этот фрагмент будет работать за $O(n^4)$. Однако это можно улучшить, воспользуемся хешами и тогда то же самое можно будет сделать за $O(n^3)$, подумав еще немного можно заменить цикл, перебирающий префикс на бинарный поиск, так как если существует префикс первой строки длины $k$ совпадающий с суффиксом длины $k$ второй строки, тогда префикс длины $k-1$ тоже будет совпадать с суффиксом длины $k-1$ второй строки, а значит функция монотонна. Тогда асимптотика этого фрагмента будет $O(n^2log(n))$.
Замечательно, теперь мы хотим узнать, какую строку необходимо поставить первой. Давайте для каждой строки насчитаем количество строк, с которыми текущая строка создает $overlap$ величины хотя бы $1$. Теперь пройдемся по всем строкам и из соображения жадности найдем ту, у которой насчитанная выше величина минимальна, обозначим ее $Start$. Далее запустим цикл на $n$ - количество строк и на каждой итерации цикла выберем оптимальную строку для строки $Start$, это будет просто строка, у которой $overlap$ со строкой $Start$ максимальный, назовем выбранную строку за $MaxString$, для того чтобы в дальнейшем случайно не взять эту строку снова, пометим ее
использованной и скажем, что $Start$ теперь равняется $MaxString$ и добавим $MaxString$ в ответ.
Итоговая асимптотика будет $O(Kn^2log(n))$, где $K$ - это то, о чем вы можете узнать в латексном файле.
:shipit:


