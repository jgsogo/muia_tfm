:orphan:

.. raw:: latex

   \cleardoublepage
   \chapter*{Resumen}
   
.. only:: html

    Resumen
    =======

    
El trabajo que se presenta a continuación desarrolla un modelo para calcular la distancia
semántica entre dos oraciones representadas por grafos UNL. Este problema se plantea
en el contexto de la traducción automática donde diferentes traductores pueden generar
oraciones ligeramente diferentes partiendo del mismo original. La medida de distancia que
se propone tiene como objetivo proporcionar una evaluación objetiva sobre la calidad del
proceso de generación del texto.

El autor realiza una exploración del estado del arte sobre esta materia, reuniendo en un
único trabajo los modelos propuestos de distancia semántica entre conceptos, los modelos de
comparación de grafos y las pocas propuestas realizadas para calcular distancias entre
grafos conceptuales. También evalúa los pocos recursos disponibles para poder experimentar
el modelo y plantea una metodología para generar los conjuntos de datos que permitirían
aplicar la propuesta con el rigor científico necesario y desarrollar la experimentación.

Utilizando las piezas anteriores se propone un modelo novedoso de comparación entre grafos
conceptuales que permite utilizar diferentes algoritmos de distancia entre conceptos y
establecer umbrales de tolerancia para permitir una comparación flexible entre las oraciones.

Este modelo se programa utilizando C++, se alimenta con los recursos a los que se ha
hecho referencia anteriormente, y se experimenta con un conjunto de oraciones creado por el
autor ante la falta de otros recursos disponibles.

Los resultados del modelo muestran que la metodología y la implementación pueden conducir a
la obtención de una medida de distancia entre grafos UNL con aplicación en sistemas de
traducción automática, sin embargo, la carencia de recursos y de datos etiquetados con
los que validar el algoritmo requieren un esfuerzo previo importante antes de poder ofrecer
resultados concluyentes.

