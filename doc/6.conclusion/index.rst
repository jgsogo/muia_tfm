
.. raw:: latex

    \newpage


Conclusión y trabajo futuro
===========================

Trabajo futuro
--------------
En la :num:`sección #planteamiento-problema` listábamos el conjunto de tareas que
consideramos necesarias para llevar a cabo un trabajo riguroso sobre la distancia semántica
entre grafos en UNL. En esta tesis hemos dedicado un esfuerzo importante a investigar el estado
del arte relacionado con el problema y además hemos planteado un modelo de distancia y
comparado contra un conjunto de oraciones creadas *ad-hoc*.

Todas las tareas reseñadas en dicha sección deben ser consideradas como trabajo futuro, y 
también algunas otras más específicas que a lo largo del desarrollo de este trabajo hemos
dejado a un lado, pero que sin duda son importantes:

 * El algoritmo implementado explora todas las combinaciones posibles de MCS para buscar
   la que ofrece un valor menor de distancia, este problema combinatorio puede ser
   abordado mediante heurísticas que permitan obtener resultados aceptables mucho más
   rápidamente. Aunque aquí los tiempos de comparación obtenidos son bastante breves,
   en oraciones más largas, donde los grafos tengan un número mayor de nodos, la búsqueda
   por fuerza bruta puede resultar intratable.
   
 * Demostrar si el algoritmo de similaridad entre grafos que se ha propuesto devuelve un
   valor que cumple las propiedades de distancia.
