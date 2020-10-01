# SpectrumForSyntacore
В папке Spectrum_by_weight/Spectrum_by_weight/ лежат все необходимые файлы.
### Заголовочные файлы:
  - LinearCapsule.h
  - WriteReadFiles.h
### Файлы с исходным кодом:
  - Linear_subspace_spectrum.cpp
  - LinearCapsule.cpp
  - WriteReadFiles.cpp
## Возможные улучшения реализации.
* Думаю, возможно ускорить получения векторов оболочки из изначального базиса, учитывая, что многие операции схожи.
Например, базис это: вектора a,b,c. И у нас есть вектора 1a+1b+1c и 0a+1b+1c. Возможно, можно вычислить 1b+1c, а затем уже рассмотреть два варианта.

