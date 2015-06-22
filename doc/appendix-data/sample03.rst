

Ejemplo #3
``````````

    *These concepts are essential for advancing towards a sustainable, more human world agenda, and they will undoubtedly continue to be relevant for many years to come.*
    

.. code-block:: unl
   :caption: Codificación UNL original.
   
   [S]
   obj(continue(icl>occur).@entry,:01)
   mod:01(concept(icl>logic).@entry.@pl,this)
   man(continue(icl>occur).@entry,undoubtedly(icl>man))
   gol(continue(icl>occur).@entry,:02)
   aoj:02(relevant(mod<thing).@entry,:01)
   dur:02(relevant(mod<thing).@entry,year(icl>time).@pl)
   mod:02(year(icl>time).@pl,many)
   mod:02(year(icl>time).@pl,forthcoming(mod<thing))
   and(continue(icl>occur).@entry,essential(mod<thing))
   aoj(essential(mod<thing),:01)
   pur(essential(mod<thing),advance(icl>progress(icl>do)))
   man(advance(icl>progress(icl>do)),towards)
   obj(towards,:03)
   mod:03(agenda(icl>programme).@entry,world(mod<thing))
   mod(:03,human(mod<thing))
   man(human(mod<thing),more)
   and(human(mod<thing),sustainable(mod<thing))
   [/S]

.. Comentario

.. code-block:: unl
   :caption: Codificación utilizada para el experimento (la codificación de los conceptos se corresponde con WordNet 3.1).
   
   {unl}
   obj(continue%2:42:01::, concept%1:09:00::)
   man(continue%2:42:01::, undoubtedly%4:02:00::)
   gol(continue%2:42:01::, be%2:42:03::)
   aoj(be%2:42:03::, concept%1:09:00::)
   obj(be%2:42:03::, relevant%3:00:00::)
   dur(relevant%3:00:00::, year%1:28:01::)
   mod(year%1:28:01::, many%3:00:00::)
   mod(year%1:28:01::, forthcoming%5:00:00:future:00)
   and(continue%2:42:01::, essential%3:00:00:necessary:00)
   aoj(essential%3:00:00:necessary:00, concept%1:09:00::)
   pur(essential%3:00:00:necessary:00, advance%2:38:00::)
   plc(advance%2:38:00::, agenda%1:10:00::)
   mod(agenda%1:10:00::, world%1:14:02::)
   mod(agenda%1:10:00::, human%3:01:00::)
   man(human%3:01:00::, more%4:02:00::)
   and(human%3:01:00::, sustainable%3:01:00::)
   {/unl}


.. figure:: ../data/samples/sample03_original.png
   :name: sample03-original
   :scale: 100 %
   :width: 100 %
   
   Grafo correspondiente al ejemplo #3 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).
   

   

