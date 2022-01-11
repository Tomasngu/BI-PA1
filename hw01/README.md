# Rovinné obrazce #

Úkolem je vytvořit program, který bude porovnávat dvojice geometrických obrazců. Porovná jejich obsah a obvod.

Na vstupu programu je dvojice geometrických obrazců v rovině. Pro každý obrazec je zadaná jeho velikost. Obrazcem může být:

- trojúhelník - na vstup je identifikace obrazce (písmeno T) následovaná trojicí desetinných čísel (délky stran),
- obdélník - na vstup je identifikace obrazce (písmeno R) následovaná dvojicí desetinných čísel (délky stran) nebo
- čtverec - na vstup je identifikace obrazce (písmeno S) následovaná jedním desetinným číslem (délka strany).
Program určí, zda mají zadané obrazce stejný obsah/obvod a výsledek zobrazí dle formátu podle ukázky (viz níže).

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

- nebyl zadaný žádný povolený obrazec (trojúhelník/obdélník/čtverec),
- nebyl zadaný potřebný počet desetinných čísel - rozměrů obrazce,
- zadaný rozměr byl neplatný, neměl podobu platného čísla, byl záporný nebo nulový,
- zadané velikosti stran netvoří trojúhelník nebo
- obdélník má obě strany stejně dlouhé (měl být zadaný jako čtverec).

**Ukázka práce programu:**
--- 
**Obrazec #1**

S 4.5

**Obrazec #2**

R 2 10.125

**Obvod: ctverec #1 < obdelnik #2**

**Obsah: ctverec #1 = obdelnik #2**

---

**Obrazec #1**

R 4 5

**Obrazec #2**

T 4.5 6 7.5

**Obvod: obdelnik #1 = trojuhelnik #2**

**Obsah: obdelnik #1 > trojuhelnik #2**

---

**Obrazec #1**


   T
 1
 1
 1
**Obrazec #2**

 S
 2

**Obvod: trojuhelnik #1 < ctverec #2**

**Obsah: trojuhelnik #1 < ctverec #2**

---

**Obrazec #1** 

T 7.981 8.899 2.996 

**Obrazec #2** 

R 2.959 6.979

 **Obvod: trojuhelnik #1 = obdelnik #2** 
 
 **Obsah: trojuhelnik #1 < obdelnik #2**

* * *

**Obrazec #1**

R 6.474 0.559

**Obrazec #2**

T 0.507 14.276 14.285

**Obvod: obdelnik #1 < trojuhelnik #2**

**Obsah: obdelnik #1 = trojuhelnik #2**

* * *

**Obrazec #1**

T 20 30 50

**Nespravny vstup.**

* * *

**Obrazec #1**

S -4

**Nespravny vstup.**

* * *

**Obrazec #1**

R 20 30

**Obrazec #2**

T 0.444 0.521 0.965

**Nespravny vstup.**


* * *

**Obrazec #1**

R 12 12

**Nespravny vstup.**

* * *

**Obrazec #1**

R 1 abcd

**Nespravny vstup.**