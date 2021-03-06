

Ejemplo #4
``````````

    *Knowledge of other cultures is essential for establishing a constructive dialogue between different communities.*
    

.. code-block:: unl
   :caption: Codificación UNL original.
   
   [S]
   aoj(essential(mod<thing).@entry,knowledge(icl>notion).@def)
   mod(knowledge(icl>notion).@def,culture(icl>abstract thing).@pl)
   mod(culture(icl>abstract thing).@pl,other(mod<thing))
   pur(essential(mod<thing).@entry,establish(icl>do))
   obj(establish(icl>do),dialogue(icl>event))
   mod(dialogue(icl>event),constructive(mod<thing))
   scn(establish(icl>do),between(icl>how))
   obj(between(icl>how),community(icl>group).@pl)
   mod(community(icl>group).@pl,various)
   [/S]

.. Comentario

.. code-block:: unl
   :caption: Codificación utilizada para el experimento (la codificación de los conceptos se corresponde con WordNet 3.1).
   
   {unl}
   aoj(essential%3:00:00::, knowledge%1:03:00::)
   mod(knowledge%1:03:00::, culture%1:14:00::)
   mod(culture%1:14:00::, other%3:00:00::)
   pur(essential%3:00:00::, establish%2:36:00::)
   obj(establish%2:36:00::, dialogue%1:10:03::)
   mod(dialogue%1:10:03::, constructive%3:00:00::)
   plc(establish%2:36:00::, between%4:02:00::)
   obj(between%4:02:00::, community%1:14:03::)
   mod(community%1:14:03::, different%3:00:00::)
   {/unl}


.. figure:: ../data/samples/sample04_original.png
   :name: sample04-original
   :scale: 80 %
   
   Grafo correspondiente al ejemplo #4 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).
   

   

