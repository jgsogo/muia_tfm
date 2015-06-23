

Ejemplo #5
``````````

    *This knowledge implies reflection about the common ground between all individuals as well as the qualities that differentiate them.*
    

.. code-block:: unl
   :caption: Codificación UNL original.
   
   [S]
   aoj(imply(icl>be).@entry,knowledge(icl>notion))
   mod(knowledge(icl>notion),this)
   obj(imply(icl>be).@entry,reflection(icl>activity))
   man(reflection(icl>activity),about(icl>concerning))
   obj(about(icl>concerning),:02)
   agt:02(differentiate(icl>do),quality(icl>attribute).@def.@entry.@pl)
   obj:02(differentiate(icl>do),individual(icl>person).@def.@pl)
   mod:02(individual(icl>person).@def.@pl,all)
   and(:02,:01)
   mod:01(ground(icl>abstract thing).@def.@entry,common(icl>shared))
   obj:01(common(icl>shared),individual(icl>person).@def.@pl)
   mod:01(individual(icl>person).@def.@pl,all)
   [/S]

.. Comentario

.. code-block:: unl
   :caption: Codificación utilizada para el experimento (la codificación de los conceptos se corresponde con WordNet 3.1).
   
   {unl}
   aoj(imply%2:42:00::, knowledge%1:03:00::)
   obj(imply%2:42:00::, reflection%1:09:00::)
   man(reflection%1:09:00::, about%4:02:06::)
   obj(about%4:02:06::, differentiate%2:31:01::)
   agt(differentiate%2:31:01::, quality%1:07:00::)
   obj(differentiate%2:31:01::, individual%1:03:00::)
   mod(individual%1:03:00::, all%3:00:00::)
   and(differentiate%2:31:01::, ground%1:09:01::)
   mod(ground%1:09:01::, common%3:00:02::)
   obj(common%3:00:02::, individual%1:03:00::)
   {/unl}


.. figure:: ../data/samples/sample05_original.png
   :name: sample05-original
   :scale: 60 %
   
   Grafo correspondiente al ejemplo #5 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).
   

   

