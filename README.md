# Objektinis programavimas

## Versija v0.1
- *Galima įvesti studentų duomenis rankiniu arba automatinio generavimo būdu.*
- *Galima pasirinkti galutinio įvertinimo skaičiavimą naudojant vidurkį arba medianą namų darbų.*

## Versija v0.1.1
- *Patobulinta pirmoji versija, įdiegtas dinamiškumas masyvuose.*

## Versija v0.2
- *Padarytas duomenų skaitymas iš failo.*

## Versija v0.3
- *Sukurtas heading failas, programa išskaidyta į kelis cpp failus.*
- *Atlikti keli try catch atvejai.*

## Versija v0.4
- *Sukurta galimybė automatiškai generuoti studentų duomenų failus.*
- *Vykdomas programos testavimas su esamais duomenų failais.*

![dasdasda](https://user-images.githubusercontent.com/80633152/159670868-564f85ee-65b2-49cc-9709-89c2d0a52497.png)

## Versija v0.5
- *Šioje versijoje buvo sukurtos trys atskiros programos, kurios kiekviena turėjo po skirtingą konteinerį: vector, list ir deque.*
- *Buvo tiriama, kaip pasikeistų programos veikimas ir jos laikas dirbant su skirtingais konteineriais.*

## Versija v1.0
- *Pritaikytos 2 strategijos darbui su konteineriu, t.y. vargšiukų ir kietiakų dalijimui.*
- *Gauti rezultatai skirtingų strategijų bei konteinerių yra palyginami laiko ir užimamos atminties atžvilgiu.*

## Versija v1.1
- *Pakeistos struktūros duomenys į klasių duomenis.*
- *Atlikta optimizacijos flag'ų analizė.*

Pasikeitus klasei duomenų tipo iš structūros programos laikas nepakito ryškiai, maždaug išliko toks pat.

*Structūros tipo*

![tipo vector](https://user-images.githubusercontent.com/80633152/166110279-b8fffb5c-93f8-42ce-a517-0cfc0a28c7b6.png)

*Klasės tipo*

![o3](https://user-images.githubusercontent.com/80633152/166110289-250bf503-1b3f-49d9-b97a-4ba690f5f6c0.png)

### Programa sukompiliuota naudojant -O1 flag'ą:
![o1](https://user-images.githubusercontent.com/80633152/166109967-a0f660c7-36b1-4150-b4af-5b8c2d8c08d0.png)
### Programa sukompiliuota naudojant -O2 flag'ą:
![o2](https://user-images.githubusercontent.com/80633152/166109960-74dbdf03-8615-412b-879d-394d9b3dd48a.png)
### Programa sukompiliuota naudojant -O3 flag'ą:
![o3](https://user-images.githubusercontent.com/80633152/166109958-0c638ae4-092d-4ab8-a4f8-86170d63e026.png)

## Versija v1.2
- *Įgyvendinta rule of three taisyklė.*

## Versija v1.5
- *Programoje sukurta abstrakčioji klasė "zmogus", kuri saugo studento vardą ir pavardę.*

## Versija v2.0
Programos diegimo instrukcija:
    <br />1) Atsisiunčiame ir paleidžiame "Setup.exe" failą savo kompiuteryje.
    <br />2) Tuomet sekame instrukcijas.
 <br /><br />
![1](https://user-images.githubusercontent.com/80633152/169152841-3327439e-6f34-465b-864d-8c7657c1d049.png)
![2](https://user-images.githubusercontent.com/80633152/169152848-59c41d0d-39f6-4343-a597-4023b3d26818.png)
![3](https://user-images.githubusercontent.com/80633152/169152868-fd74d0d4-5544-43db-a2a7-6a20de4c76e1.png)
![4](https://user-images.githubusercontent.com/80633152/169153093-845b76db-a789-4191-a4f1-4f292e281719.png)


## Programos įdiegimas naudojant makefile
- `git clone https://github.com/Matas-V/objektinis.git`
- `cd objektinis`
- `make main`
- `./main`
