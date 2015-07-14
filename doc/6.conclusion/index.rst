
.. raw:: latex

    \newpage


Conclusión y trabajo futuro
===========================
A lo largo de este trabajo hemos tenido la ocasión de aproximarnos a la problemática que
ofrecen los sistemas de traducción automáticos en cuanto a la fiabilidad de los textos 
que producen. El objetivo de estos sistemas es generar un texto en un idioma desconocido
por el cliente de un contenido que este le proporciona, por lo tanto la principal
característica que deben cumplir es que el mensaje sea el mismo en ambas lenguas.

El usuario que solicita la traducción lo hace precisamente porque desconoce el idioma de
destino, si no generaría la traducción él mismo, y por lo tanto está incapacitado para
valorarla. Surge así la necesidad de establecer una magnitud que permita evaluar la
corrección del texto producido con relación al texto original, es lo que llamamos
distancia semántica.

En el recorrido que hemos realizado por el estado del arte relacionado con esta temática,
hemos puesto de manifiesto que no existe una definición inequívoca de esta medida y que
los retos para su evaluación siguen siendo un desafío y un campo en el que todavía
hay mucha investigación pendiente.

Nosotros hemos propuesto un algoritmo que permite captar la distancia semántica entre dos
oraciones representadas por sus grafos conceptuales, con lo que en teoría podríamos 
automatizar el proceso de evaluación de un traductor y establecer un criterio para
determinar cuál es mejor y cuál peor en términos objetivos.

No obstante, hemos dejado también de manifiesto que para realizar esta tarea con el 
rigor científico necesario es imprescindible contar con recursos que ahora mismo no son
accesibles. En primer lugar es fundamental disponer de bases de datos con jerarquías de
conceptos (inexistentes en el caso del UNL) y corpus de textos etiquetados con esos 
conceptos que sean suficientemente representativos del lenguaje utilizado en las 
traducciones, tanto en lo referente al dominio tratado como en su contemporaneidad.

Además, para poder evaluar el modelo propuesto y compararlo con los pocos que están
disponibles en la bibliografía resulta también imprescindible contar con un conjunto de
datos de validación etiquetados manualmente que contengan una apreciación lo más objetiva
y profesional posible de la distancia entre varias oraciones. Solamente así es posible
evaluar el rendimiento del modelo y trabajar sobre él para mejorar sus resultados.


Trabajo futuro
--------------
En la :ref:`sección 3.3 <planteamiento-problema>` listábamos el conjunto de tareas que
consideramos necesarias para llevar a cabo un trabajo riguroso sobre la distancia semántica
entre grafos en UNL. En esta tesis hemos dedicado un esfuerzo importante a investigar el estado
del arte relacionado con el problema, hemos planteado un modelo de distancia semántica
entre oraciones y lo hemos sometido a experimentación contra un conjunto de oraciones
creadas *ad-hoc*.

Todas las tareas reseñadas en dicha sección deben ser consideradas como trabajo futuro, y 
también algunas otras más específicas que a lo largo del desarrollo de este trabajo hemos
dejado a un lado, pero que sin duda son importantes:

 * El algoritmo implementado explora todas las combinaciones posibles de MCS para buscar
   la que ofrece un valor menor de distancia, este problema combinatorio puede ser
   abordado mediante heurísticas que permitan obtener resultados aceptables mucho más
   rápidamente. Aunque aquí los tiempos de comparación obtenidos son bastante breves,
   en oraciones más largas, donde los grafos tengan un número mayor de nodos, la búsqueda
   por fuerza bruta puede resultar intratable.
   
   Hay que estudiar la utilización de heurísticas genéricas como algoritmos evolutivos
   para agilizar el cálculo cuando hay permutaciones, o bien algunas adaptadas al
   problema como la utilizada por *Zhong et al.* :cite:`Zhong2002` que mostramos
   en la bibliografía para ordenar el cálculo de similaridad.
   
 * Demostrar si el modelo de similaridad entre grafos que se ha propuesto devuelve un
   valor que puede ser transformado en distancia y cumple las propiedades de un espacio
   métrico.
   
 * También es imprescindible incorporar los atributos de las UWs en el cálculo de la
   distancia entre grafos, sin duda esta será una de las primeras incorporaciones
   que se realicen al modelo en una futura versión.

Por último, es necesario revisar los casos en los que el resultado del modelo ofrece
valores de similaridad que *a priori* consideramos incorrectos (figuras
:ref:`6.19 <sample07-measures-yandex-synset>` y :ref:`6.17 <sample09-relation-tol-0>`).
