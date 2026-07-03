# Advanced Image Synthesis (AIS) — Universität Duisburg-Essen 🇩🇪

Este repositorio contiene las prácticas, proyectos y algoritmos desarrollados durante mi estancia **Erasmus** en la **Universität Duisburg-Essen (UDE)**, correspondientes a la asignatura de máster/nivel avanzado **Advanced Image Synthesis**. 

El curso abarca desde técnicas complejas de rasterización clásica hasta los paradigmas más modernos de **Neural Rendering**, optimización de funciones neuronales y reconstrucción de escenas 3D a partir de imágenes.

- Para ver los enunciados de los ejercicios, visitar [esta web](https://www.cgvis.de/teaching/wt2025/AIS/).
- Para ver la Teoría de la asignatura, visitar [LosDelDGIIM.github.io](https://LosDelDGIIM.github.io).

## 🚀 Tecnologías y Herramientas
*   **Lenguajes Principales:** C++ / OpenGl
*   **Gráficos y Shaders:** OpenGL
*   **Matemáticas y Geometría:** GLM

---

## 📚 Contenido del Curso y Características Implementadas

El repositorio se divide en las siguientes áreas de vanguardia en computación gráfica:

### 1. Advanced Rasterization & Classic Production Pipelines
*   **Rasterization Review & Advanced Effects:** Renderizado de reflejos complejos, transparencias dinámicas y mapeo de sombras avanzado.
*   **Terrain & Organic Rendering:** Algoritmos de renderizado de terrenos detallados y simulación de pelaje/pelo (*fur rendering*).
*   **REYES Architecture:** Estudio e implementación de la arquitectura clásica de renderizado por micropolígonos para fotorrealismo cinematográfico.

### 2. Neural Rendering & Differentiable Pipelines
*   **Neural Functions & Optimization:** Ajuste y optimización de funciones continuas mediante redes neuronales para representar geometría y apariencia.
*   **Differentiable Rendering:** Renderizado diferenciable para resolver problemas inversos permitiendo propagar gradientes desde los píxeles de la imagen hacia los parámetros 3D.
*   **Neural Radiance Fields (NeRF):** Representación de escenas volumétricas mediante perceptrones multicapa (MLP) y codificación posicional.

### 3. Real-Time Novel View Synthesis & Inverse Problems
*   **3D Gaussian Splatting:** Técnicas modernas de rasterización de elipsoides 3D (Gaussianas) para reconstrucción y renderizado de escenas en tiempo real a alta velocidad.
*   **Neural Appearance & Inverse Rendering:** Descomposición de imágenes reales en sus componentes físicos constituyentes (geometría, materiales/albedo e iluminación) mediante optimización.
*   **Acceleration Structures:** Métodos de aceleración de hardware y software específicos para pipelines neuronales y de síntesis de imágenes.