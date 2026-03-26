# Descripción de la actividad:

En esta actividad desarrolle 3 estructuras de datos en C++: Stacks, Queue y Hashmap, además de probarlos contra diferentes casos de prueba tanto manuales como automáticos para validar su precisión, aparte de también usarlas para resolver diferentes problemas de codeforces, asi no solo probando que funcionen de manera correcto sino que también rapida.

- Stack (Stack.h): Implementación con punteros y lista enlazada simple. Tiene las operaciones básicas de push, pop, top, isEmpty y size.

- Queue  (Queue.h): Implementación con nodos y punteros en el frente y final. Tiene operaciones como: push, pop, front, isEmpty y size.

- Hashmap/Dictionary (Hashtable.h): Implementación usando separate chaining (arreglo de buckets + lista enlazada por bucket), básicamente generando un hash por cada llave y guardando la pareja (key, value) en la linkedlist de la bucket con índice hash. Implementa funciones como: insert, remove, get, contains, operator[], at, clear, size y empty.

## ¿Cómo se implementó?

Las estructuras fueron programadas manualmente en c++, trate de evitar usar estructuras de datos existentes, pero en hashmap por ejemplo, utilice la implementación de vector en c++, fuera de eso todo se implementó desde 0 usando punteros en c++.

Las implementaciones de de stack y queue fueron las más fáciles ya que era implementar las operaciones más básicas de una linkedlist y ajustarlas para las necesidades de la estructura de datos. Fue fácil implementarlas ya que ya las había implementado en algún momento en mis clases de algoritmos en el Tec, aunque a veces sí tuve que buscar sintaxis e información de cómo funcionan los punteros en c++.

La implementación de la hashtable fue un poco más retadora porque aunque la idea teóricamente es muy fácil, la implementación es más difícil porque la linkedlist que necesitamos para implementar el separate chaining es un poco más compleja por lo que también tuve que investigar cómo implementar ciertas cosas y como usar punteros en ciertas ocasiones.

## Test Cases realizados:

Para probar que las estructuras anteriormente mencionadas funcionan, se realizaron 3 tipos diferentes de prueba, el primero son las pruebas manuales donde hago operaciones con la estructura de datos y pruebo su comportamiento basado en lo que yo sé es el resultado. Las segundas son las pruebas automáticas donde generó miles de operaciones al azar para aplicar a nuestra estructura de datos y comparó su comportamiento con la estructura que ya existe en stl. Y la tercera fue probar las estructuras de datos en problemas de programación competitiva, probando que su comportamiento funciona en cientos de casos de prueba.

### Pruebas de Stack (test_stack.cpp):

- Pila vacía al inicio.
- push de uno y varios elementos.
- Consulta de top después de insertar.
- pop en secuencia LIFO.
- Actualización correcta del tamaño.
- Excepción/validación al consultar top en pila vacía

### Pruebas de Queue (test_queue.cpp):

- Cola vacía al inicio.
- enqueue de múltiples elementos.
- Consulta de front.
- dequeue en orden FIFO.
- Actualización correcta del tamaño.
- Validación de acceso a front cuando está vacía.

### Pruebas de hash table (test_hash.cpp):

- Inserción de claves nuevas.
- Sobrescritura/actualización de valor para clave existente.
- Búsqueda con get y verificación de contains.
- Eliminación de claves (remove) existentes y no existentes.
- Acceso con operator[] para crear/actualizar entradas.
- Validación de at en clave presente y manejo de excepción en clave ausente.
- clear, size, empty y conteo de elementos.

### Casos aplicados tipo problema:

Aparte de las pruebas anteriores, también se utilizaron las implementaciones de estas estructuras de datos en problemas de programación competitiva, para asi no solo probar que funcionan sino que también son eficientes.

- stack_and_hashmap_codeforces_problem_test.cpp: uso combinado de stack y hash table para conteo/validación sobre secuencias de paréntesis: https://codeforces.com/contest/5/submission/368201569
- queue_palindrome_flipping_codeforces_test.cpp: caso de uso de cola en un problema que utiliza bfs:  https://codeforces.com/contest/2158/submission/368202115

## Github:

https://github.com/RodrigoGarciaT/Tarea-1-Desarrollo-de-Aplicaciones-avanzadas-
