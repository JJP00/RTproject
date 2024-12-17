# Proyecto RT

Proyecto de 2024 para aprender conceptos básicos sobre la tecnología de renderización "Ray Tracing" (o "Path tracing" más adelante).

Se está siguiendo la serie de libros "Ray Tracing in one weekend", por lo tanto, ¡el crédito van a Peter Shirley, Trevor D Black, Steve Hollasch!

Hay que tener en cuenta que se programa sin ninguna otra librería... así que no usa la GPU... ya se hará otro proyecto para eso...

## Como compilar y ejecutar

Ya que es un programa paralelizado con OpenMP:

```console
g++ -fopenmp -o mainOpm.exe .\src\main.cpp
.\mainOpm.exe | Set-Content image.ppm -Encoding String
```

# RT Project

2024 project to learn basic concepts about “Ray Tracing” rendering technology (or “Path tracing” later on).

It is following the “Ray Tracing in one weekend” book series, so credit goes to Peter Shirley, Trevor D Black, Steve Hollasch!

Note that it is programmed without any other library... so it doesn't use the GPU... another project will be done for that...

## How to compile and run

Since it's a openMP parallelized program:

```console
g++ -fopenmp -o mainOpm.exe .\src\main.cpp
.\mainOpm.exe | Set-Content image.ppm -Encoding String
```

# Imagenes / Images

Tal vez, las imagenes se vean achatadas... no controlo markdown.

| <img src="resultados\2CirculosNormales.png" width=200 height=112> | <img src="resultados\2CirculosNormalesAA.png" width=200 height=112> | <img src="resultados\2EsferasDifusoV1.png" width=200 height=112> |
|:--:|:--:|:--:|
| 14/12/24 - Normales de dos esferas uno sobre el otro (poco a poco)|15/12/24 - Imagen anterior con Antialiasing. | 15/12/24 - Imagen con esferas mates, versión 1. |
| 14/12/24 - 2 sphere normals, one on top of eachother (little by little) | 15/12/24 - Previous image with Antialiasing. | 15/12/24 - Image with diffused spheres, version 1. |

| <img src="resultados\2EsferasDifusoV2.png" width=200 height=112> | <img src="resultados\4EsferasBorroso.png" width=200 height=112> | <img src="resultados\4EsferasRefractante.png" width=200 height=112> |
|:--:|:--:|:--:|
| 15/12/24 - bug precisión de hit(), Superficie de Lambert, corrección del gamma. |  15/12/24 - imagen anterior con borrosidad. | 16/12/24 Material con refracción, con 2 niveles diferentes de indice de refracción. |
| 15/12/24 - shadow acne fix, Lambertian, gamma correction. | 15/12/24 - Previous image with fuzziness. | 16/12/24 Material with refration, with 2 different refraction indexes. |

|<img src="resultados\final.png" width=800 height=448>|
|:---:|
| 17/12/24 - Imagen final, donde 1200x675, 500spp y 50 profundidad. |
| 17/12/24 - Final image, where 1200x675, 500spp y 50 depth. |

|<img src="resultados\MotionBlur.png" width=200 height=112>|
|:---:|
| 17/12/24 - Imagen final con desenfoque de movimiento, donde 400x225, 100spp y 50 profundidad. |
| 17/12/24 - Final image with motion blur, where 400x225, 100spp y 50 depth. |

# Referencias / references

- [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html)
