# Proyecto de Programación Avanzada 2026

Este repositorio ha sido creado con el objetivo de almacenar y organizar todos los archivos relacionados con el proyecto del curso de Programación Avanzada 2026.

# Organización del Proyecto
El proyecto se divide en tres carpetas principales creadas en :contentReference[oaicite:0]{index=0}:
## 📁 Proyecto-de-programacion-esp32-1
Se identificará como la carpeta **A**.

## 📁 Proyecto-de-programacion-ESP32-2
Se identificará como la carpeta **B**.

## 📁 Proyecto-de-programacion-ESP32-3
Se identificará como la carpeta **C**.

# Información General

Las carpetas han sido desarrolladas utilizando PlatformIO, una extensión ampliamente utilizada para la programación de microcontroladores y sistemas embebidos. En este proyecto se empleará principalmente programación para dispositivos ESP32 y Arduino.

## Ventajas de PlatformIO
- Mayor velocidad de compilación.
- Mejor organización de proyectos.
- Compatibilidad con múltiples microcontroladores.
- Integración directa con :contentReference[oaicite:1]{index=1}.
- Gestión más eficiente de librerías y dependencias.

---
# Funcionamiento del Sistema
## Carpeta A — ESP32 Emisor

En esta carpeta se encuentra el código correspondiente al ESP32 emisor.
Sus funciones principales son:
- Leer las señales provenientes de los sensores.
- Procesar los datos obtenidos.
- Enviar la información al ESP32 receptor.

## Carpeta B — ESP32 Receptor

En esta carpeta se encuentra el código del ESP32 receptor.
Sus funciones principales son:
- Recibir los datos enviados por el ESP32 emisor.
- Procesar la información recibida.
- Enviar los datos mediante comunicación serial hacia el sistema principal.

## Carpeta C — Comunicación con el Servidor
En esta carpeta se desarrolla la parte encargada de:
- Recibir datos seriales provenientes del ESP32 receptor.
- Procesar la información recibida.
- Conectarse con el servidor y gestionar el envío de datos.

# Estructura del Código
En cada proyecto, el código principal se encuentra dentro de:
```text
src/main.cpp
```
La carpeta `src` contiene el archivo principal de programación utilizado por PlatformIO.

# Colaboración
Los integrantes encargados de la parte desarrollada en Java pueden subir sus archivos y avances a este repositorio con el fin de mantener una mejor organización y facilitar el trabajo colaborativo.

# Observaciones

Se recomienda mantener una estructura ordenada en cada carpeta y documentar adecuadamente los cambios importantes realizados durante el desarrollo del proyecto.

# Eso es todo hihihi 