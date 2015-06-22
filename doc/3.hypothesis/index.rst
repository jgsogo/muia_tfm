
.. raw:: latex

    \newpage


Hipótesis de trabajo
====================
La cantidad de trabajo requerido para realizar todo el estudio con el rigor que se requiere
excede el alcance de este trabajo por lo que, como el título de la tesis apunta, nos
hemos centrado en la construcción de un modelo que sirva para medir la distancia entre
grafos UNL, y lo probaremos utilizando unos conjuntos de frases creados para la ocasión.
Además, como hemos visto en el capítulo anterior, también hay una carencia de recursos
importante que condicionará su desarrollo.

Por todo lo anterior el alcance del presente trabajo se limitará a lo siguiente:

 * Implementación de varios modelos de distancia semántica entre conceptos. La entrada
   serán dos conceptos UWs (que estarán mapeados a los conceptos equivalentes de
   WordNet) y la salida será una medida de distancia entre ellos.

 * Desarrollo de un modelo para el cálculo de distancia entre grafos UNL (tal y como se indicó
   en el punto anterior, las UWs estaran representadas por conceptos de WordNet). El modelo
   tomará como entrada dos grafos y su salida será un número real indicando la
   distancia entre los mismos (una distancia ``0`` indicará que los grafos son
   idénticos, valores mayores indicarán grafos cada vez más distintos hasta el máximo valor de ``1``).
   Se cumplirá la igualdad :math:`d(g_1, g_2) + s(g_1, g_2) = 1` entre la distancia ``d`` y
   la similaridad ``s`` para cualquier par de grafos :math:`g_1`, :math:`g_2`.

 * Este modelo de distancia entre grafos permitirá utilizar cualquiera de los modelos
   anteriores de distancia entre conceptos.

 * Implementación del modelo en un lenguaje de programación para probarlo: se 
   programará una aplicación capaz de tomar como entrada dos archivos de texto, cada uno
   describiendo un grafo, y devolverá un número real indicando su distancia. El
   tiempo que tarde este proceso no es relevante, pero debe permitir el desarrollo
   de las pruebas necesarias.

Durante el desarrollo del trabajo daremos por válidas las siguientes asunciones:

 * Las metodologías propuestas para distancias entre conceptos en WordNet son directamente
   aplicables a los conceptos en la Ontología UNL. La conversión entre unos y otros se

 * La información codificada en WordNet es válida para todos los contextos de trabajo y
   experimentación.

 * El corpus anotado SemCor supone una muestra adecuada del inglés para ser utilizado
   en las medidas de distancia entre conceptos que así lo requieran.

 * El modelo lo probaremos con oraciones creadas a propósito y etiquetadas por el autor,
   simplemente con la intención de probar su validez cualitativa.

.. warning:: ..y las restricciones.

.. warning:: la verdad es que no tengo nada claro cómo enfocar este capítulo.




.. 4-6-8 páginas
.. Hipótesis de trabajo, restricciones y limitaciones (lista exhaustiva)

.. La definición de la hipótesis tiene que ser concisa y clara, y debe estar acompañada de una lista exhaustiva de asunciones y limitaciones que enmarquen el resto del trabajo: las primeras sirven para exponer aquellos enunciados en los que se apoya la investigación y que no se consideran susceptibles de ser cambiados, son lo que son porque el mundo es como es (aunque en algún momento posterior la ciencia podría demostrar la invalidez de alguna de ellas); por el contrario, las restricciones expresan el alcance del trabajo, en qué campos se ha realizado el estudio, dónde puede aplicarse la investigación y los resultados.

