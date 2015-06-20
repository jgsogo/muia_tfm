

Ejemplo #6
``````````

    *The Forum strives to foster the kind of understanding and respect capable of increasing both our appreciation of our human environment and our ability to work together to make the world a better place.*
    

.. code-block:: unl
   :caption: Codificación UNL original.
   
   [S:3]
   agt(strive(icl>do).@entry,forum.@def)
   obj(strive(icl>do).@entry,foster(icl>do))
   agt(foster(icl>do),forum.@def)
   obj(foster(icl>do),kind(icl>variety).@def)
   mod(kind(icl>variety).@def,respect(icl>abstract thing))
   and(respect(icl>abstract thing),understanding)
   mod(kind(icl>variety).@def,capable(mod<thing))
   obj(capable(mod<thing),increase(icl>do))
   obj(increase(icl>do),:01)
   pos:01(ability.@entry,we:01)
   obj:01(ability.@entry,work(icl>do))
   man:01(work(icl>do),together(icl>how))
   pur:01(work(icl>do),turn(icl>transform(icl>do)))
   obj:01(turn(icl>transform(icl>do)),world(icl>region))
   gol:01(turn(icl>transform(icl>do)),place(icl>thing))
   mod:01(place(icl>thing),good(mod<thing))
   man:01(good(mod<thing),more)
   and(:01,:02)
   obj:02(appreciation.@entry,environment)
   pos:02(environment,we:03)
   mod:02(environment,human(mod<thing))
   [/S]

.. Comentario

.. code-block:: unl
   :caption: Codificación utilizada para el experimento (la codificación de los conceptos se corresponde con WordNet 3.1).
   
   {unl}
   agt(strive%2:41:00::, forum%1:14:00::)
   obj(strive%2:41:00::, foster%2:41:00::)
   agt(foster%2:41:00::, forum%1:14:00::)
   obj(foster%2:41:00::, kind%1:09:00::)
   mod(kind%1:09:00::, respect%1:12:00::)
   and(respect%1:12:00::, understanding%1:09:01::)
   mod(kind%1:09:00::, capable%3:00:00:susceptible:00)
   obj(capable%3:00:00:susceptible:00, increase%1:22:00::)
   obj(increase%1:22:00::, ability%1:09:00::)
   obj(ability%1:09:00::, work%1:04:00::)
   man(work%1:04:00::, together%4:02:01::)
   pur(work%1:04:00::, turn%2:30:04::)
   obj(turn%2:30:04::, world%1:17:00::)
   gol(turn%2:30:04::, place%1:15:04::)
   mod(place%1:15:04::, good%3:00:01::)
   man(good%3:00:01::, more%4:02:00::)
   and(ability%1:09:00::, appreciation%1:09:00::)
   obj(appreciation%1:09:00::, environment%1:15:00::)
   mod(environment%1:15:00::, human%3:01:00::)
   {/unl}


.. figure:: ../data/samples/sample06_original.png
   :name: sample06-original
   :scale: 50 %
   
   Grafo correspondiente al ejemplo #6 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).
   

   

