# Symulacja Paskowego Detektora Krzemowego w środowisku Geant4

## 📝 Opis projektu
Celem projektu jest stworzenie szczegółowej symulacji działania pojedynczego modułu paskowego detektora krzemowego. Detektory tego typu charakteryzują się wysoką precyzją przestrzenną, szybkością oraz odpornością na promieniowanie. Projekt bazuje na rozwiązaniach konstrukcyjnych wykorzystywanych w eksperymencie STAR (RHIC), służących do pomiaru pozycji protonów rozproszonych pod małymi kątami.

## 🔬 Specyfikacja techniczna

### Geometria układu
* **Okienko wejściowe**: Wykonane ze stali nierdzewnej o grubości 300 µm, umieszczone 2 cm przed detektorem.
* **Warstwa czynna**: Płytka krzemowa o grubości 400 µm.
* **Elektrody sygnałowe (paski)**:
    * Liczba: 756 elektrod typu p+.
    * Szerokość paska: 70 µm.
    * Długość paska: 48 mm.
    * Skok (pitch): 100 µm (odległość między środkami pasków).

### Warunki symulacji
* **Cząstka pierwotna**: Proton.
* **Energia**: 100 GeV.
* **Geometria wiązki**: Padanie prostopadłe, jednorodne na całej powierzchni aktywnej detektora.

## 🚀 Zrealizowane funkcjonalności

1. **Akwizycja Danych (Sensitive Detector)**: Pełna obsługa odczytu depozytu energii oraz pozycji hitu dla każdego paska z osobna.
2. **Integracja z ROOT**: Automatyczny zapis danych symulacyjnych do drzewa `TTree` (format `.root`), obejmujący informacje o depozytach energii i identyfikatorach pasków.
3. **Analiza Fizyczna**: Narzędzia do badania krotności trafień, rozkładów energii oraz analizy klastrów (sąsiadujących pasków powyżej progu detekcji).
  
## 🛠 Kompilacja i wykonanie projektu 

Projekt wykorzystuje system CMake. Aby zbudować aplikację, należy wykonać następujące kroki:

```
mkdir build
cd build
cmake ..
make
```

## 🏃 Uruchamianie
Po poprawnej kompilacji w folderze build powstanie plik wykonywalny o nazwie My.

1. Tryb interaktywny (GUI).
Uruchomienie programu bez parametrów otwiera interfejs graficzny pozwalający na wizualizację detektora i torów cząstek:
```
./My
```

2. Tryb wsadowy. 
Aby przeprowadzić symulację na podstawie gotowego makra, należy przekazać plik makra jako argument:
```
./My makro.mac
```

## 📚 Bibliografia
[1] R. Sikora, *Study of elastic proton-proton scattering with the STAR detector at RHIC*, [Dostęp online](https://misio.fis.agh.edu.pl/media/misiofiles/c087e76a6884246a0fc1b6c351991e08.pdf)
