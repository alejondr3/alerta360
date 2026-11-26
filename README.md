<p align="center">
  <img src="docs/assets/alerta360-banner.svg" alt="Alerta360 — incidencias, prioridades y rutas del campus" width="100%">
</p>

<div align="center">

# Alerta360

**Del reporte a la resolución, con prioridad y ubicación.**

Central de incidencias técnicas de campus desarrollada en C++20, con estructuras de datos propias y un mapa visual de la UPSA.

[![Compilación y pruebas](https://github.com/alejondr3/alerta360/actions/workflows/ci.yml/badge.svg)](https://github.com/alejondr3/alerta360/actions/workflows/ci.yml)
![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus&logoColor=white)
![Pruebas](https://img.shields.io/badge/escenarios_de_prueba-31-165c46)
![Plataformas](https://img.shields.io/badge/CI-Linux_%7C_Windows-374151)

[Inicio rápido](#inicio-rápido) · [Mapa del campus](#mapa-del-campus) · [Arquitectura](#arquitectura) · [Pruebas](#pruebas) · [Documentación](#documentación)

</div>

---

> **Registro simplificado:** ahora se solicitan solo **bloque, aula, ID y gravedad**. La incidencia se clasifica al registrarse. El mapa integra una vista limpia basada en el plano real y el catálogo docente por bloque y planta. Las conexiones de rutas de cada bloque todavía requieren una configuración verificada.

## Qué hace

Alerta360 recibe fallas de energía, red, equipos, climatización e infraestructura. Las clasifica, ordena su atención por urgencia, calcula una ruta de asignación y conserva el historial de cada reporte durante la sesión.

| Capacidad | Comportamiento |
| :--- | :--- |
| **Recepción ordenada** | Los reportes reciben un ID único; la cola FIFO conserva el orden durante la clasificación automática. |
| **Atención por prioridad** | Mayor gravedad primero; ante un empate, se atiende el reporte más antiguo. |
| **Correcciones reversibles** | Los cambios de gravedad se guardan en una pila y pueden deshacerse mientras la incidencia siga pendiente. |
| **Asignación con ruta** | Dijkstra calcula el camino mínimo desde la base. Si no hay ruta, el reporte permanece pendiente. |
| **Ubicación visual** | Las incidencias se marcan sobre la imagen completa del campus, con referencias numeradas y zoom. |
| **Historial e indicadores** | Búsqueda por ID, recorridos, conteos por estado y próximas cinco incidencias sin modificar las estructuras. |

## Mapa del campus

![Mapa con aulas por bloque y planta](docs/assets/mapa-aulas.jpg)

La vista ofrece una **ilustración limpia derivada con IA del plano de Postgrado UPSA** y el botón **Plano original** para comparar con la infraestructura publicada. Ambas imágenes están incorporadas en el ejecutable y funcionan sin conexión. La ilustración no sustituye un plano técnico ni contiene distribuciones interiores verificadas.

**Acercá hasta 400%, desplazá el plano y seleccioná una incidencia para consultar su estado y ubicación.** El botón **Ver completo** recupera el encuadre original.

<details>
<summary><strong>Ver captura de la aplicación con incidencias de demostración</strong></summary>

<p align="center">
  <img src="docs/assets/mapa-incidencias.jpg" alt="Alerta360 mostrando el plano completo y tres incidencias de demostración" width="680">
</p>

Los marcadores rojos corresponden a datos de ejemplo identificados como **DEMO**. Esta captura documenta el plano anterior, pendiente de reemplazo.

</details>

### Aulas por bloque y planta

El catálogo oficial, verificado el **26/11/2026**, contiene **122 espacios en su categoría docente**: **72** tienen la palabra *Aula* en el nombre; los demás incluyen laboratorios, talleres y salas. Esto no certifica el inventario total de la universidad.

| Bloque | Espacios docentes catalogados |
| :---: | ---: |
| A | 32 |
| B | 49 |
| C | 5 |
| D | 18 |
| E | 18 |

Elegí bloque y planta, buscá un código y seleccioná una tarjeta. Por ejemplo, **D-203** figura como **Laboratorio de Redes · 2da. Planta**. El marcador señala su bloque y el detalle conserva el aula y la planta; no se dibuja una distribución interior inventada.

El registro sigue pidiendo solo **bloque, aula, ID y gravedad**. Si el aula figura en el catálogo, se vincula automáticamente. Se aceptan `D` o `Bloque D`, y `203` o `D-203`. Un aula no catalogada conserva lo ingresado y se indica que no fue verificada.

El archivo [espacios-docentes.json](datos/espacios-docentes.json) conserva el inventario publicado y sus conteos. La falta de entradas para un bloque no demuestra que ese bloque no tenga aulas.

### Marcar dónde está el problema

1. Registrá la incidencia desde la opción **01**.
2. Abrí el mapa con **11**.
3. Elegí **13 → ID de incidencia → número impreso en la foto**.

| Referencia de la foto | Ubicación |
| :---: | :--- |
| **26** | Biblioteca |
| **31** | Polideportivo |
| **36** | Laboratorios de Ingeniería |

La opción **12** permite usar el catálogo avanzado de **205 lugares**, con nombres, bloques y plantas.

> **Tres numeraciones, tres propósitos.** La foto usa referencias **1–36**; el catálogo, ID **1–205**; y el grafo de atención, nodos **0–7**. Una ubicación visual no cambia la zona de atención ni el cálculo de rutas. Las aulas sin referencia propia se muestran aproximadamente por bloque, con una indicación visible.

## Inicio rápido

### Requisitos

- Compilador compatible con **C++20**: GCC, Clang o MSVC.
- **CMake 3.20+**, si elegís ese método de compilación.
- Navegador para la vista del campus.

El núcleo utiliza la biblioteca estándar y las APIs del sistema para abrir el navegador. No requiere instalar paquetes externos.

```sh
git clone https://github.com/alejondr3/alerta360.git
cd alerta360
```

### Windows · GCC / MinGW

```powershell
g++ -std=c++20 -Wall -Wextra -pedantic *.cpp -o alerta360.exe
./alerta360.exe --visual
```

### Linux / macOS · GCC o Clang

```sh
g++ -std=c++20 -Wall -Wextra -pedantic *.cpp -o alerta360
./alerta360 --visual
```

Con Clang, reemplazá `g++` por `clang++`. En una consola Windows antigua, `chcp 65001` permite usar texto UTF-8.

<details>
<summary><strong>Compilar con CMake, Visual Studio o Make</strong></summary>

```sh
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

| Generador / entorno | Ejecutar el mapa con la consola |
| :--- | :--- |
| Linux / macOS, generador de una configuración | `./build/alerta360 --visual` |
| Windows con MinGW | `./build/alerta360.exe --visual` |
| Windows con Visual Studio | `./build/Debug/alerta360.exe --visual` |

Para seleccionar MinGW explícitamente, usá una carpeta de compilación nueva:

```powershell
cmake -S . -B build-mingw -G "MinGW Makefiles"
cmake --build build-mingw
```

Con Make: `make`, `make test` y `make clean`. En MinGW, usá `mingw32-make`.

</details>

### Modos de ejecución

| Argumento | Resultado |
| :--- | :--- |
| Sin argumentos | Inicia la consola con registro de bloque, aula, ID y gravedad. |
| `--visual` | Inicia la consola y abre el mapa de la sesión. |
| `--mapa` | Genera y abre un mapa vacío, y termina. |
| `--pruebas` | Ejecuta la suite automática y devuelve su resultado. |
| `--consigna` | Conserva el registro y la clasificación manual originales para reproducir las pruebas de la consigna. |

## Un primer registro

La opción **01** solicita exactamente:

```text
Bloque: D
Aula: 203
ID de incidencia: 501
Gravedad (1-5): 5
```

El programa conserva bloque y aula y carga la incidencia como **PENDIENTE**, con prioridad 5. No pide tipo, descripción ni zona. La descripción se genera con la ubicación ingresada.

Los registros reconocidos se vinculan al catálogo y señalan su bloque en el mapa. Las rutas por bloque todavía no están configuradas con pesos verificados; no reciben una zona de destino inventada. Si se intenta asignarlos, permanecen pendientes y se informa que falta configurar la ruta del bloque. La clasificación, corrección de gravedad, deshacer, consultas y cancelación siguen disponibles.

La gravedad va de **1 a 5**; **5 es la mayor urgencia**. El modo `--consigna` conserva el flujo original y las rutas de control del grafo de prueba para la evaluación académica.

<details>
<summary><strong>Referencia completa del menú</strong></summary>

| Opción | Acción |
| :---: | :--- |
| **01** | Registrar bloque, aula, ID y gravedad; clasificar automáticamente en orden FIFO. |
| **02** | Clasificar la siguiente recibida que aún esté esperando (compatibilidad con el modo original). |
| **03** | Cambiar la gravedad de una pendiente. |
| **04** | Deshacer la última corrección de gravedad. |
| **05** | Asignar la siguiente por prioridad y registrar su ruta. |
| **06** | Resolver una incidencia asignada. |
| **07** | Cancelar una recibida o pendiente. |
| **08** | Buscar por ID mediante el BST. |
| **09** | Consultar historial, indicadores y próximas cinco pendientes. |
| **10** | Gestionar costos, cierres y restauraciones de vías. |
| **11** | Abrir el mapa visual. |
| **12** | Vincular un lugar del catálogo UPSA, con ID de 1 a 205. |
| **13** | Vincular una referencia de la foto, de 1 a 36. |
| **00** | Liberar las estructuras y cerrar. |

</details>

## Arquitectura

La consola y el mapa comparten los datos de una misma sesión. `SistemaAlerta360` coordina las reglas de negocio y mantiene consistentes las estructuras implementadas por el proyecto.

| Estructura propia | Responsabilidad |
| :--- | :--- |
| **Lista doblemente enlazada** | Repositorio único e historial de incidencias. |
| **Cola FIFO enlazada** | Orden de recepción para la clasificación. |
| **BST por ID** | Índice hacia los registros originales de la lista. |
| **Heap binario máximo** | Prioridad por gravedad y antigüedad. |
| **Pila LIFO enlazada** | Historial de correcciones de gravedad. |
| **Grafo ponderado + Dijkstra** | Conexiones del campus de prueba y caminos mínimos. |

La lista posee los registros. Los índices guardan referencias o IDs y no duplican incidencias completas. El heap mantiene una posición inversa para reajustar o retirar elementos conocidos en `O(log p)`.

Los detalles de memoria, invariantes y complejidad están en [Arquitectura y decisiones de diseño](docs/ARQUITECTURA.md).

### Organización del repositorio

```text
alerta360/
├── main.cpp                    # Menú y entrada validada
├── Incidencia.h                # Modelo de dominio
├── Estructuras.h/.cpp          # Lista, cola, BST, heap y pila
├── GrafoCampus.h/.cpp          # Matriz de adyacencia y Dijkstra
├── SistemaAlerta360.h/.cpp     # Reglas e integración
├── MapaVisual.h/.cpp           # Exportación y apertura del mapa
├── MapaPlantilla.inc           # Interfaz visual
├── MapaCampusImagen.inc        # JPEG original incorporado
├── MapaCampusLimpio.inc        # Ilustración IA incorporada
├── UbicacionesCampus.h/.cpp    # Catálogo y referencias del plano
├── Pruebas.cpp                 # 31 escenarios automáticos
├── pruebas/                    # Entradas, salidas y evidencias
├── datos/                      # Foto original, catálogo y fuentes
├── docs/                       # Arquitectura y recursos del README
├── .github/workflows/ci.yml    # Linux, Windows y sanitizadores
├── CMakeLists.txt
├── Makefile
└── uso_IA.txt
```

## Grafo de atención

El sistema utiliza el grafo **no dirigido de ocho nodos** definido para el proyecto. El origen fijo es **0 · Central de soporte**.

| Nodo | Zona | Nodo | Zona |
| :---: | :--- | :---: | :--- |
| 0 | Central de soporte | 4 | Residencias |
| 1 | Biblioteca | 5 | Cafetería |
| 2 | Laboratorios | 6 | Centro de salud universitario |
| 3 | Coliseo | 7 | Estadio |

<details>
<summary><strong>Conexiones, costos y rutas de control</strong></summary>

| Vía | Minutos | Vía | Minutos |
| :---: | ---: | :---: | ---: |
| 0–1 | 4 | 0–2 | 2 |
| 1–2 | 1 | 1–3 | 5 |
| 2–3 | 8 | 2–4 | 10 |
| 3–4 | 2 | 3–5 | 6 |
| 4–5 | 3 | 4–6 | 1 |
| 5–7 | 4 | 6–7 | 2 |

| Destino | Ruta mínima desde la base | Costo |
| :--- | :--- | ---: |
| Zona 3 | `0 → 2 → 1 → 3` | **8 min** |
| Zona 7 | `0 → 2 → 1 → 3 → 4 → 6 → 7` | **13 min** |

Las conexiones tienen costos positivos; la diagonal es `0` y una vía ausente o cerrada vale `-1`. Los costos acumulados se almacenan en `long long`.

</details>

Si el destino queda desconectado, la asignación se rechaza y la incidencia conserva su posición lógica como pendiente. Las rutas registradas se mantienen como historial aunque el mapa cambie después.

## Pruebas

La suite incluye **31 escenarios reproducibles**: los diez casos de aceptación del proyecto y casos adicionales de prioridad, cancelación, memoria, entradas inválidas, UTF-8, exportación segura y referencias de la foto.

```powershell
./alerta360.exe --pruebas
```

```text
=== Resumen: 31 aprobadas, 0 fallidas ===
```

El proceso devuelve `0` si todas las pruebas pasan y `1` si alguna falla. CTest agrupa los 31 escenarios en una suite.

| Verificación automática | Entorno |
| :--- | :--- |
| Compilación C++20 y suite funcional | GitHub Actions · Linux y Windows |
| AddressSanitizer y UndefinedBehaviorSanitizer | GitHub Actions · Linux |
| Entradas y salidas reproducibles del menú | Archivos de evidencia en `pruebas/` |

[Ver las ejecuciones de CI](https://github.com/alejondr3/alerta360/actions) · [Matriz de pruebas](pruebas/CASOS.md) · [Resultados](pruebas/resultados.txt) · [Registro de verificación](pruebas/VERIFICACION.txt)

<details>
<summary><strong>Reproducir sesiones y ejecutar sanitizadores localmente</strong></summary>

```powershell
Get-Content pruebas/entrada_aceptacion.txt | ./alerta360.exe --consigna
Get-Content pruebas/entrada_invalidas.txt | ./alerta360.exe --consigna
Get-Content pruebas/entrada_foto.txt | ./alerta360.exe --consigna
Get-Content pruebas/entrada_registro.txt | ./alerta360.exe
```

En Linux/macOS, usá `./alerta360 --consigna < pruebas/entrada_aceptacion.txt`.

Con GCC/Clang y sanitizadores disponibles en Linux/macOS:

```sh
cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
cmake --build build-asan
ctest --test-dir build-asan --output-on-failure
```

</details>

## Alcance de la sesión

- Las incidencias permanecen **en memoria** hasta cerrar el programa.
- `mapa_alerta360.html` conserva una instantánea visual; no recupera la sesión.
- Con el mapa activo, la consola regenera el HTML después de las operaciones. El navegador se actualiza cuando no se está interactuando.
- Cada sesión visual debe usar su propia carpeta para evitar compartir el mismo archivo generado.
- El grafo de prueba conserva los pesos de la consigna. Sus tiempos no representan mediciones peatonales reales sobre la fotografía.

## Documentación

| Recurso | Contenido |
| :--- | :--- |
| [Arquitectura](docs/ARQUITECTURA.md) | Componentes, propiedad de memoria, invariantes y complejidades. |
| [Pruebas y evidencias](pruebas/CASOS.md) | Escenarios, entradas y resultados esperados. |
| [Fuente del plano](datos/FUENTE_PLANO.md) | Procedencia, dimensiones y hash de la imagen original. |
| [Catálogo del campus](datos/LEEME.md) | Alcance de las ubicaciones y correspondencias con la foto. |
| [Asistencia de IA](uso_IA.txt) | Declaración del alcance de la asistencia utilizada. |

---

**Contexto académico:** proyecto integrador de Estructuras de Datos, UPSA. La implementación y la documentación del repositorio acompañan el informe y la defensa requeridos por la asignatura.

La imagen del campus pertenece a su fuente original y mantiene sus marcas y atribuciones. Su incorporación no implica que Alerta360 sea un producto oficial de la universidad.
