# Alerta360

**Incidencias del campus UPSA, de principio a fin en consola.**

[![Compilación y pruebas](https://github.com/alejondr3/alerta360/actions/workflows/ci.yml/badge.svg)](https://github.com/alejondr3/alerta360/actions/workflows/ci.yml)
![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C)
![Pruebas](https://img.shields.io/badge/escenarios-31-165c46)

Registrá un problema con **bloque, aula, ID y gravedad**, consultá su ubicación en un mapa de texto y administrá su atención por prioridad. La aplicación funciona sin navegador, servidor ni conexión a Internet.

## Inicio rápido

```sh
git clone https://github.com/alejondr3/alerta360.git
cd alerta360
g++ -std=c++20 -Wall -Wextra -pedantic *.cpp -o alerta360
./alerta360
```

En Windows, compilá con `-o alerta360.exe` y ejecutá `./alerta360.exe`. El ZIP de entrega también incluye el ejecutable estático de Windows. Se necesita un compilador C++20 para compilar desde las fuentes; no hay paquetes externos.

Con CMake 3.20 o posterior:

```sh
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

El ejecutable queda en `build/alerta360` con generadores de una configuración; Visual Studio usa `build/Debug/alerta360.exe`. También se incluyen `make` y `make test`.

## Uso

```text
=== ALERTA360 ===
1 Registrar incidencia
2 Ver incidencias
3 Ver mapa en consola
4 Mas opciones
0 Salir
```

La opción **1** pide exactamente cuatro campos:

```text
Bloque: D
Aula: 203
ID de incidencia: 101
Gravedad (1-5): 5
```

**5 es la mayor urgencia.** El registro se clasifica automáticamente respetando la cola de recepción y queda pendiente. El ID es único durante la sesión. Se reconocen tanto `D` y `Bloque D` como `203` y `D-203`.

## Mapa en consola

La opción **3** dibuja un esquema de los bloques y muestra las incidencias activas. Cada bloque indica su cantidad y gravedad máxima; debajo aparecen **ID, aula, gravedad y estado**. Los conteos se calculan con los datos actuales, sin incidencias de ejemplo al iniciar.

```text
                         CANCHA / AREAS
  +--------------------+                          +--------------------+
  | BLOQUE B           |                          | BLOQUE E           |
  | Sin incidencias    |                          | Sin incidencias    |
  +--------------------+                          +--------------------+
  +--------------------+  +--------------------+  +--------------------+
  | BLOQUE A           |  | BLOQUE C           |  | BLOQUE D           |
  | ! 1 activa(s)      |  | Sin incidencias    |  | ! 1 activa(s)      |
  | Gravedad max: 3    |  |                    |  | Gravedad max: 5    |
  +--------------------+  +--------------------+  +--------------------+
  +--------------------+
  | BLOQUE CENTRAL     |
  | Sin incidencias    |
  +--------------------+
  ================= ACCESO / AVENIDA =================

  ! #101 | Bloque D | Aula 203 | Gravedad 5 | PENDIENTE
  ! #102 | Bloque A | Aula 108 | Gravedad 3 | PENDIENTE
```

Ejemplo ilustrativo con dos reportes. [Salida real de demostración](docs/mapa-consola.txt).

Dentro del mapa:

| Opción | Acción |
| :---: | :--- |
| **1** | Elegir A, B, C, D, E o CENTRAL y consultar sus incidencias y espacios docentes por planta. |
| **2** | Ingresar un ID para ver la ficha completa, incluso si está resuelto o cancelado. |
| **0** | Volver al menú principal. |

`!` identifica incidencias activas. Las canceladas y resueltas quedan en el historial. Los reportes sin un bloque representable permanecen visibles en el listado y se cuentan como **sin bloque en el esquema**. Una ubicación explícita posterior tiene prioridad sobre el bloque original para ubicar el reporte.

La disposición sigue aproximadamente la imagen de referencia del campus. **Es un esquema por bloques, sin planos interiores, escala ni distancias reales.** Las aulas se consultan por código y planta; no se inventa su posición dentro de los edificios. El mapa utiliza caracteres ASCII para funcionar también en terminales sin colores o símbolos especiales; los nombres del catálogo conservan UTF-8.

## Más opciones

| Opción del submenú | Acción |
| :---: | :--- |
| **1** | Buscar por ID. |
| **2** | Cambiar gravedad. |
| **3** | Deshacer el último cambio de gravedad. |
| **4** | Asignar la siguiente por prioridad. |
| **5** | Resolver una asignada. |
| **6** | Cancelar una recibida o pendiente. |
| **7** | Gestionar costos, cierres y restauraciones de rutas. |
| **8** | Vincular un lugar del catálogo; ingresar **206** para listar los lugares en consola. |
| **9** | Vincular una referencia numerada del plano de origen, disponible como listado de texto. |
| **0** | Volver. |

Las correcciones de gravedad se deshacen mientras la incidencia siga pendiente. Si una asignación no tiene ruta, la incidencia permanece pendiente. Los registros de bloque y aula esperan una configuración verificada de rutas por bloque; no se inventa una conexión con el grafo académico.

## Catálogo y fuentes

El catálogo incorporado procede de [maps.upsa.edu.bo](https://maps.upsa.edu.bo/) y conserva 205 lugares de referencia. La copia verificada el **26/11/2026** contiene 122 espacios en la categoría docente: A 32, B 49, C 5, D 18 y E 18. De ellos, 72 incluyen la palabra *Aula*. Es una copia de referencia, no una certificación del inventario actual de la universidad.

Por ejemplo, **D-203** figura como **Laboratorio de Redes · 2da. Planta**. Un aula ausente del catálogo conserva los datos ingresados sin asignarle otra sala. La falta de entradas de un bloque no demuestra que no tenga aulas.

[Catálogo docente](datos/espacios-docentes.json) · [Fuentes del plano](datos/FUENTE_PLANO.md) · [Alcance de los datos](datos/LEEME.md)

## Estructuras y arquitectura

| Estructura propia | Responsabilidad |
| :--- | :--- |
| Lista doblemente enlazada | Propiedad de los registros e historial. |
| Cola FIFO enlazada | Clasificación en orden de recepción. |
| BST por ID | Búsqueda sobre los registros originales. |
| Heap máximo | Gravedad descendente y antigüedad ante empates. |
| Pila LIFO | Historial de cambios de gravedad. |
| Grafo ponderado y Dijkstra | Rutas mínimas sobre los ocho nodos académicos. |

`main.cpp` gestiona las entradas. `SistemaAlerta360` coordina las operaciones; `MapaConsola` recorre los registros en modo de solo lectura. `UbicacionesCampus` contiene el catálogo. `DatosJSON` conserva la serialización de datos para verificaciones, sin generar una interfaz web.

El grafo académico parte de **0 · Central de soporte** y conserva las zonas y pesos de la consigna. Las rutas de control cuestan 8 minutos hacia la zona 3 y 13 hacia la zona 7. Sus pesos no representan mediciones reales sobre el campus.

[Arquitectura, invariantes y complejidades](docs/ARQUITECTURA.md).

## Modos de ejecución

| Argumento | Resultado |
| :--- | :--- |
| Sin argumentos | Menú principal en consola. |
| `--mapa` | Imprime el esquema vacío y termina. |
| `--visual` | Alias conservado: muestra el mapa y continúa en consola. |
| `--consigna` | Registro y menú académico originales; opción **11** imprime el mapa en consola. |
| `--pruebas` | Ejecuta los 31 escenarios automáticos y devuelve 0 si pasan. |

En `--consigna`, las opciones son: 1 registrar, 2 clasificar, 3 cambiar gravedad, 4 deshacer, 5 asignar, 6 resolver, 7 cancelar, 8 buscar, 9 informes, 10 rutas, 11 mapa, 12 catálogo, 13 referencia y 0 salir.

## Verificación

```sh
./alerta360 --pruebas
```

```text
=== Resumen: 31 aprobadas, 0 fallidas ===
```

La suite verifica prioridad, cancelaciones, estructuras, Dijkstra, validaciones, catálogo y mapa de consola. El caso **T25** comprueba conteos, filtros, aulas, reubicación y que consultar el mapa no cambie los datos. GitHub Actions compila y ejecuta las pruebas en Linux y Windows; Linux también utiliza AddressSanitizer y UndefinedBehaviorSanitizer.

Para reproducir una sesión completa en PowerShell:

```powershell
Get-Content pruebas/entrada_consola.txt | ./alerta360.exe
Get-Content pruebas/entrada_aceptacion.txt | ./alerta360.exe --consigna
```

[Casos](pruebas/CASOS.md) · [Resultados](pruebas/resultados.txt) · [Sesión de consola](pruebas/salida_consola.txt) · [Verificación](pruebas/VERIFICACION.txt)

## Alcance

Las incidencias permanecen en memoria hasta cerrar la aplicación. El programa libera las estructuras al salir o recibir fin de entrada. Las versiones HTML anteriores fueron retiradas del código ejecutable: el programa actual no abre el navegador ni genera archivos HTML. Los recursos gráficos de referencia conservados en `datos/` y `docs/assets/` no forman parte de la interfaz.

Proyecto académico de Estructuras de Datos, UPSA. No es un producto oficial de la universidad. La asistencia de IA se declara en [uso_IA.txt](uso_IA.txt).
