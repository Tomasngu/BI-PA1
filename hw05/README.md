# Nejprodávanější zboží #

Úkolem je vytvořit program, který bude zpracovávat provedené nákupy a analyzovat prodejnost zboží.

Předpokládáme že zaznamenáváme jednotlivé prodeje zboží. Zajímá nás zejména to zboží, které se prodává nejvíce. Proto program bude umět vypočítat N druhů zboží, kterého se prodalo nejvíce kusů. Hodnota N (počet druhů zboží, které se prodává nejvíce) bude zadán na vstupu programu jako první údaj.

Zboží je identifikováno svým jménem - řetězcem. Jméno musí být nejvýše 99 znaků dlouhé a neobsahuje bílé znaky. Na vstupu se o prodeji zboží program dozví pomocí zadání + jméno-zboží. Na vstupu dále mohou být příkazy, kterými lze zobrazit analýzu prodeje. Konkrétně:

příkaz # zobrazí přehled N druhů zboží, kterého se dosud prodalo nejvíce. Výpis bude mít podobu podle ukázky níže, pro každý druh zboží bude uvedeno jméno a počet prodaných kusů. Dále bude zobrazen i celkový součet (součty prodaných kusů pro zobrazené nejvíce prodávané zboží).
příkaz ? zobrazí pouze celkový součet.
Fungování programu se trochu komplikuje pro vstupy, kde se pro dva a více různých druhů zboží prodal stejný počet kusů:

jednodušší situace je vidět v první ukázce. Ve výpisu jsou 4 kusy prodaných vajíček a mouky. Proto toto zboží má shodně 2. až 3. místo ve výpisu a odpovídá tomu i formát výpisu. Zároveň tím není určeno přesné pořadí ve výpisu. Testovací prostředí proto akceptuje obě (všechny) možnosti, tedy zde by konkrétně bylo správně jak:

```
   1. Milk, 5x
   2.-3. Eggs, 4x
   2.-3. Flour, 4x
   4. Beer, 3x
```
tak i:
```
   1. Milk, 5x
   2.-3. Flour, 4x
   2.-3. Eggs, 4x
   4. Beer, 3x
```  
Komplikovanější situace je vidět v druhé ukázce. Bylo zadáno, že se mají sledovat N=3 nejvíce prodávané druhy zboží, ale je vidět, že vypsaný seznam je někdy i delší, například u výstupu:
```
   1.-4. Black_tea, 1x
   1.-4. Caffeine, 1x
   1.-4. C/C++_for_dummies, 1x
   1.-4. Introduction_to_Algorithms, 1x
```  
nebo:
```
   1.-2. Black_tea, 2x
   1.-2. Caffeine, 2x
   3.-5. C/C++_for_dummies, 1x
   3.-5. Energy_drink, 1x
   3.-5. Introduction_to_Algorithms, 1x
```
Delší bude seznam v situaci, kdy by seznam N nejprodávanějších druhů zboží měl skončit a odříznout další druhy zboží, které mají stejnou prodejnost jako jiné zboží již zobrazené.
Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

- sledovaný počet druhů zboží N je neplatný (není celé číslo, je nulový nebo záporný),
- není zadaný žádný známý příkaz (+, ?, #),
- název zboží je neplatný (chybí, má 100 nebo více znaků).

**Ukázka práce programu:**
---
```
Pocet sledovanych:
4
Pozadavky:
+ Fruits
+ Milk
+ Milk
+ Sugar
+ Butter
+ Beer
+ Vegetables
+ Milk
+ Beer
+ Milk
+ Beer
+ Sugar
+ Eggs
+ Milk
+ Eggs
+ Eggs
+ Eggs
#
1. Milk, 5x
2. Eggs, 4x
3. Beer, 3x
4. Sugar, 2x
Nejprodavanejsi zbozi: prodano 14 kusu
+ Flour
+ Flour
+ Flour
+ Flour
#
1. Milk, 5x
2.-3. Eggs, 4x
2.-3. Flour, 4x
4. Beer, 3x
Nejprodavanejsi zbozi: prodano 16 kusu
+ Flour
?
Nejprodavanejsi zbozi: prodano 17 kusu
+ Flour
#
1. Flour, 6x
2. Milk, 5x
3. Eggs, 4x
4. Beer, 3x
Nejprodavanejsi zbozi: prodano 18 kusu
```