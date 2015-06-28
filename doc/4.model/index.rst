
.. raw:: latex

    \newpage


Propuesta de modelo
===================
Ante la carencia de un modelo que permita comparar grafos UNL y cuyo algoritmo estuviera
claramente expuesto, se ha decidido crear un modelo nuevo utilizando algunas ideas
vistas durante la revisión del estado del arte e incorporando la posibilidad de indicar un
umbral de flexibilidad en la comparación entre conceptos, algo que consideramos
imprescindible en este campo.

Ante la imposibilidad de encontrar un recurso tan imprescindible como la Ontología UNL,
el trabajo se ha desarrollado utilizando WordNet, por lo tanto no podemos hablar estrictamente
de distancia entre grafos UNL puesto que estamos sustituyendo las UWs por los *synsets*
correspondientes.
Esta sustitución, sin embargo, no supone ninguna pérdida de generalidad puesto que la
metodología utilizada puede ser aplicada de la misma forma en cualquier jerarquía de
conceptos con relaciones de hiponimia/hiperonimia.

El modelo propuesto satisface los siguientes objetivos:

 * Ofrecer una medida de similaridad entre grafos conceptuales cuyo valor esté contenido
   en el intervalo :math:`[0,1]`, donde :math:`0` indica mínima similaridad
   y el valor :math:`1` que se trata de grafos idénticos. No se plantea el estudio sobre
   si esta medida cumple las propiedades de una distancia y por lo tanto podría ser
   tratada como tal, así que en general hablaremos de similaridad.
   
 * Maximizar la similaridad calculada entre grafos: el algoritmo debe buscar la combinación que
   ofrezca la mínima distancia (máxima similaridad) entre los grafos a comparar, el cálculo
   propuesto realiza una búsqueda exhaustiva por lo que está garantizado que
   encuentra el máximo global [#]_.
    
 * Permitir la utilización de diferentes métricas de distancias entre conceptos, se
   utilizarán las que hemos expuesto en el estado del arte.
   
 * Permitir la utilización de diferentes métricas de distancias entre relaciones UNL.
 
 * Utilizar un par de parámetros configurables que permitan definir el umbral de
   tolerancia en la comparación de conceptos y relaciones de tal forma que dos *synsets*
   puedan ser considerados iguales y, por lo tanto, formen parte del máximo grafo
   común a pesar de existir cierta distancia entre ellos.
 
.. [#] Como se expondrá más adelante esta búsqueda exhaustiva resulta en muchos
   casos ineficiente en términos de tiempo de computación y se recomendará la utilización
   de heurísticas. En este trabajo se han optimizado algunos algoritmos para reducir
   los tiempos de computación, pero no se ha utilizado ninguna heurística, el espacio
   de búsqueda se explora en su totalidad.
   
Para poder alcanzar estos objetivos nos hemos apoyado en los recursos que se exponen en el
apartado siguiente. Una vez expuestos se describirá el modelo que se ha propuesto.


.. toctree::
   :maxdepth: 4

   i.recursos
   ii.modelo
