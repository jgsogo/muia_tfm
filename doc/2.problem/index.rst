
.. raw:: latex

    \newpage


Descripción del problema
========================

La distancia semántica
----------------------
En la revisión del estado del arte del capítulo anterior hemos mostrado los diferentes
elementos que se han de tener en cuenta para la comparación de dos oraciones en lenguaje
natural. Hemos comentado muy sucintamente los problemas relacionados con la conversión de
éste en una representación del conocimiento independiente de la lengua y que
no presente ambigüedades, que es la base de los sistemas de traducción basados en
interlingua. Hemos repasado los grafos conceptuales y la evolución de estos hasta el
*Universal Networking Language* (UNL).

Hemos mostrado las principales medidas de distancia entre conceptos que se
proponen en la bibliografía y los algoritmos de comparación de grafos que son la base
para la comparación de grafos conceptuales, presentados en la última sección del
estado del arte.

Sin embargo, ninguno de los artículos presentados es concluyente, debido, en primer lugar
a que **no existe una definición objetiva de distancia semántica** a nivel de conceptos y
por lo tanto, este problema se arrastra hasta la comparación de grafos conceptuales.

La problemática se presenta en dos niveles, el primero de ellos en los conceptos
individualizados y el segundo en el conjunto de la oración.


Distancia entre conceptos
`````````````````````````
Cada autor considera unas características diferentes a la hora de desarrollar su métrica
de distancia entre conceptos o bien la restringe a un contexto concreto o utiliza el
corpus que mejor se adecua al experimento que quiere realizar.

Existen esfuerzos como el de Budanitsky y Hirst :cite:`Budanitsky1998` :cite:`Budanitsky2006`
o el dirigido por Slimani :cite:`Slimani2013` que muestran la correlación entre diferentes
medidas de similaridad semántica o con datos obtenidos de estudios de campo.
Las comparación con datos de distancia percibidos por
personas se basan en pequeños experimentos (pocos sujetos y pocos pares de palabras) que
parten del realizado por Rubenstein y Goodenough :cite:`Rubenstein1965` en 1965 con 51 nativos
ingleses sobre 65 pares de palabras.

El estudio de Rubenstein y Goodenough ha sido comparado con otras muestras obtenidas
de otros sujetos varias veces obteniéndose unos niveles de correlación muy altos: Miller
y Charles en 1991 :cite:`Miller1991`, Resnik en 1995 :cite:`Resnik1995` y Pirró más
recientemente en 2009 :cite:`Pirro2009`. Los resultados muestran estabilidad en
la distancia semántica percibida por las personas a lo largo del tiempo para el conjunto de
palabras elegido, pero la lengua cambia, los usos de las palabras se modifican y no se
puede aceptar esta premisa como válida en términos generales (e.g. la palabra bizarro que
la RAE define como "valiente", pero que en su uso está más próxima al concepto
"raro, extravagante" importado del inglés *bizarre*).


Distancia entre oraciones
`````````````````````````
El otro gran problema asociado a la representación del conocimiento es la interpretación
del mensaje, que también tiene un componente subjetivo dificilmente medible. Una parte
muy importante del mensaje es implícito y su comprensión depende del sustrato cultural
común de los interlocutores, es un problema que mencionábamos al hablar de los 
fenómenos lingüísticos (:num:`sección #fenomenos-linguisticos`).

Este hecho provoca que el mismo mensaje pueda ser codificado de diferentes
formas (paráfrasis), en cuyo caso una buena medida de distancia debería obtener un valor
bajo que indicara que son muy similares, o bien, el mismo mensaje puede ser
interpretado de manera diferente por distintos sujetos y entonces sí que existirá
distancia real entre los grafos producidos.

A pesar de que existen numeros artículos en torno a la comparación de grafos, la literatura
no es tan prolífica a la hora de comparar grafos conceptuales y, mucho menos, en la
comparación flexible de grafos UNL. No se ha encontrado ningún artículo en el que
se ofrezca una comparativa entre los resultados obtenidos por diferentes algoritmos.


Recursos disponibles
--------------------





Algunas carencias en la bibliografía:

 * Nadie habla de la Ontología UNL (o no me he cruzado con ellos). Todas las métricas de distancia
   semántica entre conceptos se evalúan en WordNet
 * Nadie trabaja con grafos UNL - todo el trabajo llega, como mucho, a grafos conceptuales, y tampoco hay tanto.

Posibles líneas de actuación:

 * Adaptar algoritmos a la Ontología UNL y a los grafos UNL:
    * Documentar las diferencias (WordNet-Ontología UNL) y (CGs-Grafo UNL), adaptar algún algoritmo para
      que funcione en este nuevo escenario.
 * Valorar si realmente se puede aportar algún modelo nuevo.


