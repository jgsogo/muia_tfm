
.. raw:: latex

    \newpage


Descripción del problema
========================

En la revisión del estado del arte del capítulo anterior hemos mostrado los diferentes
elementos que se han de tener en cuenta para la comparación de dos oraciones en lenguaje
natural. Hemos comentado muy sucintamente los problemas relacionados con la conversión del
lenguaje natural a una representación del conocimiento independiente de la lengua y que
no presente ambigüedades, que es la base de los sistemas de traducción basados en
interlingua. Hemos repasado los grafos conceptuales y la evolución de estos hasta el
*Universal Networking Language* (UNL).

Asimismo hemos repasado las principales medidas de distancia entre conceptos que se
proponen en la bibliografía y los algoritmos de comparación de grafos que son la base
para la comparación de grafos conceptuales, presentados en la última sección del
estado del arte.




Algunas carencias en la bibliografía:

 * Nadie habla de la Ontología UNL (o no me he cruzado con ellos). Todas las métricas de distancia
   semántica entre conceptos se evalúan en WordNet
 * Nadie trabaja con grafos UNL - todo el trabajo llega, como mucho, a grafos conceptuales, y tampoco hay tanto.

Posibles líneas de actuación:

 * Adaptar algoritmos a la Ontología UNL y a los grafos UNL:
    * Documentar las diferencias (WordNet-Ontología UNL) y (CGs-Grafo UNL), adaptar algún algoritmo para
      que funcione en este nuevo escenario.
 * Valorar si realmente se puede aportar algún modelo nuevo.


