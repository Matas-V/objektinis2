# Objektinis programavimas

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

## Programos įdiegimas naudojant makefile
- `git clone https://github.com/Matas-V/objektinis.git`
- `cd objektinis2/vector`
- `make main`
- `./main`

## Releas'ai:
- [**v1.1**](https://github.com/Matas-V/objektinis2/releases/tag/v1.1)
