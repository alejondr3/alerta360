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

El ejecutable no carga este JSON ni depende de internet. La incorporacion de
esta referencia no modifica estados, prioridades, rutas o resultados del codigo.
