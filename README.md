# ofhawc

## Introducción

Visualizador basado en OpenFrameworks de los datos de posición y curvas de luz de fuentes observadas. Estos datos fueron recopilados por el Observatorio de Rayos Gamma HAWC (High-Altitude Water Cherenkov Gamma-Ray Observatory). El proyecto surge a propósito del Hackatón astronómico organizado en el Instituto de Atronomía. Este repositorio es parte de un proyecto colaborativo que se complementa con [2HAWC](https://github.com/ciretorres/2HAWC) y [sc_hawc](https://github.com/marianneteixido/sc_hawc).

## Colaboradorxs

Marianne Teixido, Eric Torres, Rodrigo Treviño. 

## Descripción

Cada objeto visible es una fuente y su localización en el espacio tridimensional está determinada por la traspolación de la posición en coordenadas galácticas a coordenadas esféricas. El posicionamiento de las fuentes en un espacio tridimensional permite realizar acercamientos de cámara de cada fuente. Los acercamientos arrojan información en forma de texto del objeto enfocado. Es posible enfocar el objeto a partir de un comando que puede ser escrito en la mini-consola del visualizador. Ej: fuente 1. 

El visualizador está pensado para ejecutarse a la par de un complemento sonoro realizado en SuperCollider. El motor de audio extrae y secuencia los valores de las curvas de luz. Posteriormente estos son enviados a OF para ser representados en forma de intensidad lumínica. Esta representación no tiene su correspondencia para cada fuente ya que solamente hay datos para tres fuentes observadas. La parte de audio utiliza una serie de 39 sintetizadores asignados cada uno a una fuente en específico y los valores de amplitud están relacionados a la fuente enfocada (el resto queda "sonando" como ruido de fondo con una amplitud menor).

Este proyecto se inspira parcialmente en Orbit, una plataforma para realizar Live Coding e integrarlo con audio y video. Debido a esto, es posible escribir texto en pantalla para controlar distintos parámetros del sistema. Por otro lado, el complemento de audio utiliza la librería JITLib, lo cual permite la manipulación dinámica de los flujos de información que representan las curvas de luz. 

## Conclusiones

El modelo bidireccional de intercambio de información nos permite aprovechar las posibilidades de OpenFrameworks y SuperCollider. Por un lado, encontramos cómodo trabajar las estructuras fijas de datos en OpenFrameworks, mientras que los datos secuenciados en un continuo de tiempo son más fáciles de manipular en SuperCollider. 

El trabajo con múltiples plataformas (OF, SC, P) nos permitió conducir de manera colectiva la comprensión y la realización del objetivo final. 

El uso de técnica de Live Coding permite manipular los datos en vivo. Gracias a esto es posible tener una experiencia performática de aproximación a los datos del HAWC. 

## Trabajo pendiente

Shaders sincronizados

Representaciones tridimensionales de las fuentes. 

Búsqueda del vecino más cercano para determinar las relaciones en el espacio de las fuentes. 

Integración con los otros equipos del hackatón astronómico. 

## Referencias

[The High-Altitude Water Cherenkov Gamma-Ray Observatory](https://www.hawc-observatory.org/)

[ (The (Temporary|Transnational|Terrestrial|Transdimensional) Organisation for the (Promotion|Proliferation|Permanence|Purity) of Live (Algorithm|Audio|Art|Artistic) Programming)](https://toplap.org/about/)

[Just In Time programming library](http://doc.sccode.org/Overviews/JITLib.html)

[Live Coding en México. Hernani Villaseñor](http://www.hernanivillasenor.com/archivos/html/livecoding.html)

[Hackatón Astronómico ACT. Live Coding y sonorización de datos astronómicos ](http://artecienciaytecnologias.mx/es/programacion/divulgacion/5121748WQHs766EB9yOj0146)

[Orbit](https://github.com/EmilioOcelotl/Orbit)

[PiranhaLab](https://github.com/EmilioOcelotl/PiranhaLib)
