 # New Green Deal #

 Úkolem je realizovat funkci (ne celý program, pouze funkci), která bude počítat spotřebu el. energie v digitálních hodinách.

Evropská unie správně chápe, že energií je potřeba šetřit, ať to stojí, co to stojí. Zatím se to týká žárovek, výbojek, vysavačů, ale dá se očekávat, že tento progresivní trend zasáhne i další energeticky náročná zařízení. Abychom náročné práci euroúředníků pomohli, poskytneme jim v této úloze analytický nástroj, kterým půjde v dlouhodobém horizontu zkoumat energetickou náročnost digitálních hodin s mechanickým sedmisegmentovým displejem.

Hodiny zobrazují čas na sedmisegmentovém displeji. Čas je zobrazován ve 24 hodinovém formátu, tedy 00 00 00 až 23 59 59. Displej je mechanický, číslice je tvořena ze 7 segmentů, každý segment je buď světlý nebo tmavý obdélník. Pokud je nedochází ke změně daného segmentu, není potřeba dodávat žádnou energii. Naopak, změna tmavého segmentu na světlý nebo opačná stojí energii, pro jednoduchost předpokládáme 1J na změnu jednoho segmentu. Cifry na sedmisegmentovém displeji mají standardní tvar, tedy:

```
 -         -    -         -    -    -    -    -                                                                     
| |    |    |    |  | |  |    |      |  | |  | |                                                                       
           -    -    -    -    -         -    -                                                                     
| |    |  |      |    |    |  | |    |  | |    |                                                                       
 -         -    -         -    -         -    -  
```

Naše funkce dostane parametrem dva časové údaje - počátek a konec časového intervalu. Počátek i konec je dán rokem, měsícem, dnem, hodinou a minutou. Funkce spočítá, kolik energie hodiny za tuto dobu spotřebují.

Požadovaná funkce má rozhraní:

**int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
                        int y2, int m2, int d2, int h2, int i2, 
                        long long int * consumption )**
                        
y1, m1, d1, h1, i1
jsou vstupní parametry, které představují rok, měsíc, den, hodinu a minutu počátku intervalu,
y2, m2, d2, h2, i2
jsou vstupní parametry, které představují rok, měsíc, den, hodinu a minutu konce intervalu,
consumption
je výstupní parametr, do kterého funkce uloží vypočtenou spotřebu v zadaném období. Spotřebu vracejte v joulech (J). Parametr bude funkce nastavovat pouze pokud jsou zadané správné vstupní parametry. Pokud jsou zadané nesprávné vstupy, nelze hodnotu určit. V takovém případě funkce signalizuje neúspěch a ponechá tento výstupní parametr beze změn. Vypočtená hodnota zahrnuje spotřebu na všechny změny obsahu displeje provedené mezi prvním a posledním zobrazeným časovým údajem. Tedy např. pro ukázkové zadání:

```c
     assert ( energyConsumption ( 2400,  2, 29, 12,  0, 2400,  2, 29, 12,  1, &consumption ) == 1 && consumption == 204LL );
``` 

Během této doby proběhlo 60 změn zobrazovaných sekund (200J) a změna minut z 00 na 01 (4J)..
návratová hodnota funkce
bude nastavena na hodnotu 1 pro úspěch (správné vstupní parametry) nebo 0 pro neúspěch (nesprávné vstupní parametry).
Pokud jsou zadané nesprávné vstupní parametry, je potřeba vrátit hodnotu 0 (neúspěch). Správné hodnoty vstupních parametrů musí splňovat:

- rok je větší roven 1600,
- měsíc je platný (1 až 12),
- den je platný (1 až počet dní v měsíci),
- hodina je platná (0 až 23),
- minuta je platná (0 až 59),
- zadaný okamžik počátku intervalu nenastane až po zadaném okamžiku konce intervalu.


Odevzdávejte zdrojový soubor, který obsahuje implementaci požadované funkce energyConsumption. Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou z energyConsumption volané. Funkce bude volaná z testovacího prostředí, je proto důležité přesně dodržet zadané rozhraní funkce. Za základ pro implementaci použijte kód z ukázky níže. V kódu chybí vyplnit funkci energyConsumption (a případné další podpůrné funkce). Ukázka obsahuje testovací funkci main, uvedené hodnoty jsou použité při základním testu. Všimněte si, že vkládání hlavičkových souborů a funkce main jsou zabalené v bloku podmíněného překladu (#ifdef/#endif). Prosím, ponechte bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně spouštět a testovat. Při kompilaci na Progtestu funkce main a vkládání hlavičkových souborů "zmizí", tedy nebude kolidovat s hlavičkovými soubory a funkcí main testovacího prostředí.

Při výpočtu času uvažujeme Gregoriánský kalendář. Tedy měsíce mají vždy 30 nebo vždy 31 dní, výjimkou je únor, který má 28 dní (nepřestupný rok) nebo 29 dní (přestupný rok). Podle Gregoriánského kalendáře platí:

- roky nejsou přestupné,
- s výjimkou let dělitelných 4, které jsou přestupné,
- s výjimkou let dělitelných 100, které nejsou přestupné,
- s výjimkou let dělitelných 400, které jsou přestupné,
- s výjimkou let dělitelných 4000, které nejsou přestupné.
Tedy roky 1901, 1902, 1903, 1905, ... jsou nepřestupné (pravidlo 1), roky 1904, 1908, ..., 1996, 2004, ... jsou přestupné (pravidlo 2), roky 1700, 1800, 1900, 2100, ... nejsou přestupné (pravidlo 3), roky 1600, 2000, 2400, ..., 3600, 4400, ... jsou přestupné (pravidlo 4) a roky 4000, 8000, ... nejsou přestupné (pravidlo 5).

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Časové limity jsou nastavené tak, aby rozumná implementace naivního algoritmu prošla všemi povinnými testy. Řešení fungující v povinných testech může získat nominálních 100% bodů. Bonusový test vyžaduje časově efektivní výpočet i pro velké intervaly (vysoké roky hodně převyšující 4000).