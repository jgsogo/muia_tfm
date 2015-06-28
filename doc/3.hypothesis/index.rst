
.. raw:: latex

    \newpage


Hipótesis de trabajo
====================

.. warning:: la verdad es que no tengo nada claro cómo enfocar este capítulo.

La cantidad de trabajo requerido para realizar todo el estudio con el rigor científico 
necesario excede el alcance de este trabajo por lo que, como el título de la tesis indica,
nos hemos centrado en la construcción de un modelo que sirva para medir la distancia
entre grafos UNL. Además, como hemos visto en el capítulo anterior, dada la carencia de
recursos existente tendremos que realizar un importante trabajo para generarlos sin
condicionar el funcionamiento del algoritmo.

Por todo lo anterior el alcance del presente trabajo se limitará a lo siguiente:

 * Implementación en lenguaje C++ de varios modelos de distancia semántica entre
   conceptos. La entrada serán dos UWs (que estarán mapeados a los *synsets*
   equivalentes de WordNet) y la salida será una medida de distancia entre ellos
   en el intervalo :math:`[0, 1]`.

 * Desarrollo de un modelo para el cálculo de distancia entre grafos UNL (las UWs
   estarán representadas por conceptos de WordNet). El modelo
   tomará como entrada dos grafos y su salida será un número real indicando la
   similaridad entre los mismos en el intervalo :math:`[0, 1]` (una similaridad
   :math:`1` indicará que los grafos son idénticos, valores menores indicarán
   grafos cada vez más distintos hasta el mínimo valor :math:`0`).
   Se cumplirá la igualdad 
   
   .. math::
   
      d(g_1, g_2) + s(g_1, g_2) = 1
   
   entre la distancia :math:`d` y la similaridad :math:`s` para cualquier par de grafos
   :math:`g_1`, :math:`g_2`.

 * El modelo de distancia entre grafos permitirá utilizar cualquiera de los modelos
   anteriores de distancia entre conceptos.

 * Implementación del modelo en el lenguaje de programación C++ para probarlo: se 
   programará una aplicación capaz de tomar como entrada dos archivos de texto, cada uno
   describiendo un grafo, y devolverá un número real indicando su similaridad. El
   tiempo que tarde este proceso no es relevante, pero debe permitir el desarrollo
   de las pruebas necesarias.
   
 * En este desarrollo no se considerarán los atributos de las UWs en la
   comparación de los grafos, se descarta así una cantidad importante de contenido
   semántico, pero se simplifica la interpretación de los resultados y la primera
   evaluación del modelo.
   
 * El modelo será probado con un conjunto de oraciones que permita obtener una
   valoración cualitativa de su funcionamiento. Estas oraciones serán traducidas
   utilizando sistemas de traducción automáticos (Google, Systrans y Yandex) sin que
   por ello el objetivo sea valorar la calidad de estos traductores.
   
 * El valor relativo de distancia entre las traducciones (cuál está más cerca del
   contenido original) se comparará con una clasificación realizada por una persona
   sin conocimientos ni formación específica, la intención es mostrar la metodología
   utilizada más que constrastar el algoritmo puesto que el número de muestras no
   se considera suficiente para esta valoración.

Durante el desarrollo del trabajo también tenemos que dar por válidas algunas limitaciones
dada la carencia de recursos disponibles:

 * Las metodologías propuestas para distancias entre conceptos en WordNet son directamente
   aplicables a las UWs en la Ontología UNL (si existiera). La conversión entre unos y otras
   será realizada de forma manual por el autor.

 * La información codificada en WordNet es válida para todos los contextos de trabajo y
   experimentación.

 * El *corpus* anotado SemCor supone una muestra adecuada del inglés para ser utilizado
   en las medidas de distancia entre conceptos que así lo requieren.


.. 4-6-8 páginas
.. Hipótesis de trabajo, restricciones y limitaciones (lista exhaustiva)

.. La definición de la hipótesis tiene que ser concisa y clara, y debe estar acompañada de una lista exhaustiva de asunciones y limitaciones que enmarquen el resto del trabajo: las primeras sirven para exponer aquellos enunciados en los que se apoya la investigación y que no se consideran susceptibles de ser cambiados, son lo que son porque el mundo es como es (aunque en algún momento posterior la ciencia podría demostrar la invalidez de alguna de ellas); por el contrario, las restricciones expresan el alcance del trabajo, en qué campos se ha realizado el estudio, dónde puede aplicarse la investigación y los resultados.

