

Ejemplo #1
``````````

    *The Universal Forum of Cultures will be held from April 23 to September 24, 2004,
    and will include exhibitions, debates and festivals to celebrate cultural diversity
    throughout the world.*
    

.. code-block:: unl
   :caption: Codificación UNL original.
   
   [S:3]
   aoj(include(icl>be).@entry.@future,:01) 
   mod:01(forum.@def.@entry,universal) 
   mod:01(forum.@def.@entry,culture(icl>abstract thing).@def.@pl) 
   obj(include(icl>be).@entry.@future,festival(icl>event).@pl) 
   and(festival(icl>event).@pl,debate(icl>event).@pl) 
   and(debate(icl>event).@pl,exhibition(icl>event).@pl) 
   pur(include(icl>be).@entry.@future,celebrate(icl>do)) 
   obj(celebrate(icl>do),diversity(icl>variety).@def) 
   mod(diversity(icl>variety).@def,cultural) 
   scn(diversity(icl>variety).@def,throughout) 
   obj(throughout,world(icl>region).@def) 
   [/S]

.. Comentario

.. code-block:: unl
   :caption: Codificación utilizada para el experimento (la codificación de los conceptos se corresponde con WordNet 3.1).
   
   {unl}
   aoj(include%2:42:00::, forum%1:14:00::)
   mod(forum%1:14:00::, universal%5:00:00:comprehensive:00)
   mod(forum%1:14:00::, culture%1:14:00::)
   obj(include%2:42:00::, festival%1:04:00::)
   and(festival%1:04:00::, debate%1:10:01::)
   and(debate%1:10:01::, exhibition%1:04:00::)
   pur(include%2:42:00::, celebrate%2:41:00::)
   obj(celebrate%2:41:00::, diversity%1:07:02::)
   mod(diversity%1:07:02::, cultural%5:00:00:social:00)
   plc(diversity%1:07:02::, throughout%4:02:00::)
   obj(throughout%4:02:00::, world%1:17:00::)
   {/unl}


.. figure:: ../data/samples/sample01_original.png
   :name: sample01-original
   
   Grafo correspondiente al ejemplo #1 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).
   

   

