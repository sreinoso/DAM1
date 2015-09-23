1.2 - Definiciones
------------------

- SGBD: conjunto de datos relaciones entre si y programas que nos permiten permiten acceder a esto

- Antes de la aparicion de las bases de datos la información se almacenaba en archivos

- Problemas de los sistemas basados en archivos
   
	- Redundancia e inconsistencia de los datos y con informacion diferente

- Depencencia programa <-> datos: si queremos cambiar los datos tenemos que rehacer el programa

- Dificultad de acceso: si queremos consultar la informacion de una forma nueva se tendra que rehacer el programa

- Acceso concurrente: es dificil que 2 o mas usuarios accedan a la vez a un mismo archivo

1.3-El modelo entidad-relacion
------------------------------

Modelo Entidad-Relacion -> Modelo relacional -> SGBD(UF2)

El modelo entidad-interelacion fue propuesto por Peter Chen en el año 1976
En 1988 se convirtio en el standard para el analisis y diseño de bases de datos

- Entidad: Representacion de los objetos del mundo real. Lo denotaremos con un rectangulo

  .. image:: img/ejemploEntidad.png
        :scale: 200%

- Atributo o campo: para guardar estas representaciones, guardaremos un conjunto de informaciones.Se representan ligadas a la entidad y con un circulo. Ej.: Entidad cliente de un banco
   
  .. image:: img/ejemploAtributo.png
        :scale: 200%

- Identificador o superclave: conjunto de atributos de una entidad que nos permite identificar de forma inequivoca cada elemento de la entidad

- Clave candidata: conjunto de superclave formada por el minimo numero de campos posibles.

- Clave primaria: Clave candidata escogida por nosotros para identificar la entidad
