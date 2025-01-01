# 4 Darwin

> 1. Przed implementacją konieczna jest akceptacja struktury danych przez prowadzącego zajęcia.
> 2. Program powinien być podzielony na pliki z deklaracjami (*.h) i definicjami (*.cpp).
> 3. Wszystkie funkcje muszą być skomentowane w doxygenie.
> 4. Program musi obsługiwać różne permutacje parametrów linii poleceń.
> 5. Uruchomienie programu bez parametrów powoduje wyświetlenie krótkiej pomocy.
> 6. Program musi być odporny na pewne niedoskonałości formatu danych wejściowych.

<br>

Proszę napisać program symulujący ewolucję populacji osobników. Populacja może liczyć dowolną
liczbę osobników. Każdy osobnik zawiera chromosom, który jest ciągiem liczb naturalnych. Chromosomy
mogą być różnej długości. W każdym pokoleniu wylosowywanych jest `k` par osobników, które się następnie
krzyżują. Krzyżowanie polega na tym, że u każdego osobnika dochodzi do pęknięcia chromosomu
w dowolnym miejscu. Część początkowa chromosomu jednego osobnika łączy się z częścią końcową drugiego.
Inaczej mówiąc: osobniki wymieniają się fragmentami swoich chromosomów. Jeden osobnik może
być wylosowany do kilku krzyżowań. Po dokonaniu wszystkich krzyżowań w pokoleniu sprawdzane jest
przystosowanie osobników do warunków środowiska. W tym celu dla każdego osobnika wyznaczana jest
wartość `f ∈ [0, 1]` funkcji dopasowania. Osobniki, dla których wartość `f < w` (gdzie `w` jest progiem wymierania),
są usuwane z populacji. Osobniki, dla których `f > r` (gdzie `r` jest progiem rozmnażania) są
klonowane. A osobniki, dla których `w ⩽ f ⩽ r` pozostają w populacji, ale się nie rozmnażają.

Funkcja oceny osobnika jest ustawiana w funkcji main przez wskaźnik lub jako funkcja lambda.

<br>

Program uruchamiany jest z linii poleceń z wykorzystaniem następujących przełączników (kolejność przełączników jest dowolna):

- i plik wejściowy z populacją
- o plik wyjściowy z populacją
- w współczynnik wymierania w ∈ [0, 1]
- r współczynnik rozmnażania r ∈ [0, 1]
- p liczba pokoleń p
- k liczba k par osobników losowanych do krzyżowania



Uruchomienie programu bez parametrów powoduje wypisanie krótkiej informacji o tym, jak użyć programu.

---

Plik wejściowy ma następującą postać: Każda linia zawiera jednego osobnika. Osobnik charakteryzowany
jest chromosomem, który jest przedstawiony jako ciąg liczb naturalnych rozdzielonych białymi
znakami. Przykładowy plik wejściowy zawierający populację złożoną z czterech osobników:

```
2 9 84 9 5 6 25 12  
2 98 56 2 54  
5 2  
8 5 22 5 48 6 1 9 8 7 554 25 235 32  
```

Plik wyjściowy ma identyczny format.
