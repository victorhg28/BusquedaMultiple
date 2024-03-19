# BusquedaMultiple
Busque multiples palabras o lineas de texto en varios archivos | Search multiple words or text lines in multiple files

![Static Badge](https://img.shields.io/badge/estado-en_desarrollo-green)
![Static Badge](https://img.shields.io/badge/disponible_para-linux-black)
![Static Badge](https://img.shields.io/badge/disponible_para-windows-black)

## Sobre el programa
Cree un archivo de texto con todas las palabras (o lineas de texto) que desee buscar, separandolas por un salto de línea. Cargue todos los archivos donde desea buscar esas palabras o lienas de texto y listo! Obtenga una lista desplegable con todos los resultados obtenidos.

## Descarga
Disponible para Windows y Linux en la carpeta "Descargas"

## Uso
Siga los pasos que se puede ver en la siguiente imagen
![GUI_guia](https://github.com/victorhg28/BusquedaMultiple/assets/53150635/0736c477-eabe-4270-9629-4cec072e1168)

  1. Arrastre y suelte los archivos donde desea realizar la busqueda (tambien puede borrar los archivos subidos haciendo click en ellos y luego presionando la tecla SUPR)
     ![Cargar archivos](https://github.com/victorhg28/BusquedaMultiple/assets/53150635/eed68a74-8e91-4493-bd0b-15d17ca590e0)

  2. Cargue el archivo de texto que creó donde estan todas las palabras o lineas de texto a buscar
  3. Haga click en "Buscar" y listo, al lado derecho se mostrarán los resultados en un tree.
    ![uso](https://github.com/victorhg28/BusquedaMultiple/assets/53150635/9d2a7629-bbc1-4c03-9696-092b4180e39a)
  4. Puede cambiar el color de fondo usando los sliders situados en la parte inferior derecha de la ventana (el color escogido se guarda automaticamente, por lo que la siguiente vez que abra el programa este se mostrará en el color con el cual lo dejó la ultima vez)
     ![color](https://github.com/victorhg28/BusquedaMultiple/assets/53150635/b9e7f6f8-244a-4d14-baae-3578a486ed5d)

## Contexto
Desarrollado durante practicas pre profesionales en Claro Perú para distintos usos.

## Posibles errores
Si elimina el archivo "config"(que debería estar en la misma ruta que el ejecutable), el programa no abrirá pues este tratará de buscar este archivo, que contiene la configuracion de los colores de la interfaz gráfica.

## Herramientas utilizadas
- U++ (IDE y framework para desarrollo de software en el lenguaje C++): https://www.ultimatepp.org/
