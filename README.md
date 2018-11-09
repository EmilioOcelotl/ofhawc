# ofhawc

## Introducción

Visualizador basado en OpenFrameworks de los datos de posición y curvas de luz recopilados por el Observatorio de Rayos Gamma HAWC (High-Altitude Water Cherenkov Gamma-Ray Observatory).

## Descripción

Cada objeto visible es una fuente y su localización en el espacio tridimensional está determinada por la traspolación de la posición en coordenadas galácticas a coordenadas esféricas. El posicionamiento de las fuentes en un espacio tridimensional permite realizar acercamientos de cámara de cada fuente. Los acercamientos arrojan información en forma de texto del objeto enfocado. 

La representación de las curvas de luz está relacionada con la intensidad lumínica de los objetos dibujados. Esta representación no tiene su correspondencia para cada fuente, solamente hay datos para tres fuentes observadas. 

Un complemento sonoro de este visualizador recibe los datos de la posición de la fuente enfocada por la cámara. Estos valores determinan la amplitud de una serie de 39 sintetizadores realizados en SuperCollider que representan a las fuentes dibujadas. 

El proyecto surge a partir del Hackatón astronómico organizado por GradoCero.  Este proyecto tiene una parte realizada en Processing. 

## Trabajo pendiente

Representaciones tridimensionales de las fuentes. 
Búsqueda del vecino más cercano para determinar las relaciones en el espacio de las fuentes. 
Integración con los otros equipos del hackatón astronómico. 

## Referencias

[The High-Altitude Water Cherenkov Gamma-Ray Observatory](https://www.hawc-observatory.org/)

