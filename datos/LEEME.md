# Referencia del campus real UPSA

Fuente: [Mapa Interactivo Campus - UPSA](https://maps.upsa.edu.bo/).
Consulta: 23 de noviembre de 2026.

`mapa_upsa_referencia.json` conserva los 205 registros del catalogo publicado
por esa aplicacion. Incluye los campos originales disponibles: identificador,
nombre, edificio, bloque, planta, categoria y posicion en el plano. Algunos
registros tienen campos vacios o ausentes; se mantienen tal como se publican.
El identificador del sitio no equivale al ID de zona del programa.

Ejemplos verificados:

| ID del mapa | Ubicacion | Bloque | Planta |
| --- | --- | --- | --- |
| 27 | Enfermeria | B | 1ra. |
| 49 | Coliseo Polideportivo | No especificado | No especificada |
| 131 | D-203 Laboratorio de Redes | D | 2da. |
| 173 | Biblioteca | A | 4ta. |

Este archivo es una referencia de ubicaciones, no una red de rutas peatonales.
En el catalogo extraido no se encontraron aristas, minutos de recorrido ni una
escala de distancia verificada. Los valores `map` se conservan sin convertirlos
a coordenadas GPS, metros o minutos. No se descargaron las imagenes del plano.

El programa sigue usando las ocho zonas y los costos obligatorios del PDF:
cambiar sus nombres o pesos por lugares del campus real alteraria las pruebas
de aceptacion. Para un modo adicional de campus real habria que definir nodos
y conexiones transitables, incluir escaleras/cambios de planta cuando corresponda
y medir o declarar como estimados los costos positivos de cada tramo.

El catalogo tambien se incluye compilado en `UbicacionesCampus.cpp`: el mapa
visual no necesita cargar este JSON ni conectarse a internet. Las posiciones
se convierten al espacio del dibujo con el mismo extent TILE_PIXELS que publica
la aplicacion oficial: [-20037508.342789244, -20037508.342789244,
20037508.342789244, 20037508.342789244]. No se interpretan como GPS o metros.
La vista actual usa la foto completa de Postgrado UPSA (ver FUENTE_PLANO.md).
Sus 36 referencias se ubican mediante anclajes en pixeles de esa imagen;
las coordenadas del catalogo interactivo no se proyectan directamente sobre
la foto porque son sistemas distintos. Las correspondencias nominales
verificadas usan las referencias impresas; las aulas restantes se representan
aproximadamente por bloque, con indicacion visible. Los lugares sin un anclaje
verificado no se dibujan sobre la foto. Vincular un lugar o referencia no
modifica estados, prioridades ni rutas del grafo.

## Verificacion del catalogo docente: 26/11/2026

Se volvio a descargar el catalogo del sitio oficial y coincide con los 205
registros conservados. `cat-classrooms` incluye 122 espacios: A32, B49, C5,
D18 y E18. Hay 72 entradas con la palabra Aula y 121 codigos de sala; CIAP
es una entrada de esa categoria sin codigo. El detalle esta en
`espacios-docentes.json`. No se afirma que este sea el inventario exhaustivo
de ambientes de la universidad. No se publican planos interiores en estos datos.
