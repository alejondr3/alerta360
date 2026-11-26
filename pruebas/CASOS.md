# Matriz de pruebas

Entradas y verificaciones automaticas: `Pruebas.cpp`. Cada prueba imprime su
expectativa, resultado real OK/FALLO y estado APROBADA/FALLIDA. Las salidas
obtenidas y el registro de operaciones estan en `resultados.txt`.

| ID | Entrada/situacion | Resultado esperado |
| --- | --- | --- |
| T01 | Registrar 101 zona 3, 102 zona 7, 103 zona 2 | RECIBIDAS, secuencias 1,2,3; lista/BST/cola consistentes. |
| T02 | Clasificar con 5,5,3 | Orden 101,102,103. |
| T03 | Gravedad 103 de 3 a 5 | Una correccion; 101 y 102 conservan precedencia. |
| T04 | Deshacer | 103 vuelve a 3; pila vacia, heap correcto. |
| T05 | Asignar siguiente | 101, ruta 0-2-1-3, costo 8. |
| T06 | Resolver 101 dos veces | Primera aceptada, segunda rechazada. |
| T07 | Cerrar 5-7 y 6-7; asignar | Rechazo, 102 pendiente y sin ruta registrada. |
| T08 | Restaurar 6-7; asignar | 102, ruta 0-2-1-3-4-6-7, costo 13. |
| T09 | Registrar/cancelar 104 y clasificar | 104 se descarta de cola, no entra al heap. |
| T10 | Buscar 999, cancelar 101 resuelta, asignar hasta vaciar | Rechazos claros e invariantes intactas. |
| T11 | Datos invalidos, duplicados y transiciones prohibidas | Rechazos sin modificar registros validos. |
| T12 | Cancelar medio/cima/hoja; cambios repetidos y deshacer | Heap sin duplicados; restauracion LIFO. |
| T13 | Deshacer con pila vacia, asignada y cancelada | No revierte; descarta la entrada correspondiente. |
| T14 | 40 pendientes y consultas repetidas | Crecimiento seguro; top 5 = 4,9,14,19,24; consultas no cambian estado. |
| T15 | BST con 1..7 y con 4,2,6,1,3,5,7 | Alturas 7 y 3; ambas busquedas correctas. |
| T16 | Origen 0 a 0, aislar base, entradas invalidas | Costo 0, inaccesible detectado, restauracion simetrica. |
| T17 | Cambiar mapa despues de asignar | Ruta/costo historicos permanecen iguales. |
| T18 | 100 ciclos con memoria dinamica, doble cierre y reutilizacion | Sin fallo; estructuras vacias y secuencia reiniciada. |
| T19 | Empate artificial de gravedad y secuencia | Tercer desempate defensivo por ID; sin corrupcion. |
| T20 | Todas las vias con costo INT_MAX | Ruta 0 a 7 cuesta 8589934588, sin overflow. |
| T21 | Varias canceladas y deshacer invalido sobre otro valido | FIFO preservada; cada intento consume una sola correccion. |
| T22 | Descripcion UTF-8 de 120/121 caracteres y misma gravedad | Acepta 120, rechaza 121; mismo valor no apila. |
| T23 | Vincular/quitar lugar UPSA e IDs invalidos | Ubicacion independiente de zona; rechazos sin modificar registro. |
| T24 | Exportar descripcion con etiquetas script y catalogo | JSON seguro, datos completos y consultas sin mutacion. |
| T25 | Crear/reemplazar mapa con JPEG incorporado; carpeta inexistente y directorio como destino | Archivo completo, errores controlados, directorio preservado. |
| T26 | Referencias 1-36 de la foto, cambios de identificador y valores invalidos | Biblioteca 26 y Polideportivo 31 correctos; zona, estado y heap conservados. |

| T27 | Registro de bloque, aula, ID y gravedad | Campos guardados, clasificación automática y heap por prioridad; ruta pendiente sin inventar zona. |
| T28 | Campos vacíos, longitudes, controles, ID y gravedad inválidos | Rechazos sin datos parciales; ID único; corrección, deshacer y cancelación funcionan. |
| T29 | Registro nuevo detrás de una recibida antigua | FIFO preservada; gravedades guardadas y clasificación posterior sin duplicados. |
| T30 | Catalogo docente, codigos de aula, bloques y plantas | 122 espacios, 72 Aula; A32 B49 C5 D18 E18; D-203 en segunda planta. |
| T31 | Registrar bloque/aula con reconocimiento automatico | Vinculo a lugar #131 sin pedir mas datos; aula no catalogada conservada sin coincidencia inventada. |


T19 prueba la estructura aislada: en el sistema real la secuencia de ingreso es
unica, por lo que no se repite para dos incidencias.

## Menu por entrada estandar

- `entrada_aceptacion.txt`: reproduce T01-T10 desde el menu; evidencia en
  `salida_aceptacion.txt`.
- `entrada_invalidas.txt`: letras, opciones fuera de rango, ID duplicado,
  descripcion corta, zona/gravedad invalidas, operaciones rechazadas y cierre;
  evidencia en `salida_invalidas.txt`.
- EOF: cierre seguro incluso a mitad de registro, sin registrar datos parciales.

La ejecucion automatica cubre tambien la limpieza, pero no demuestra por si
sola ausencia absoluta de fugas. Consultar `VERIFICACION.txt` para el entorno
y las herramientas disponibles.


Entrada de menu adicional: entrada_foto.txt (opcion 13 -> referencia 26);
evidencia real: salida_foto.txt.

Las entradas anteriores se reproducen con `--consigna`. El registro de cuatro
campos se reproduce con `entrada_registro.txt`, sin argumentos; evidencia en
`salida_registro.txt`.
