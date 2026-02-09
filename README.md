
# Coding a mouse jigler in C

## following along a youtube tutorial 



# Le projet:

Coder une souris virtuelle qui bouge seule.



## dev :

```c
struct libevdev *dev = libevdev_new();
```
"dev" est la fiche technique/plan contient les infos:

- nom
- type d'envent ( EV_REL, EV_SYNC) 
- code specifiques (REL_X, BTN_LEFT)

## uidev :

Peripherique concret dans le kernel.
```c
    struct libevdev_uinput *iudev = NULL;
```

### ==> uidev = l’objet utilisable, dev = la recette / plan

---

### /dev/input/ :

- chaque peripherique a son file "event" 
- dans le kernel chaque event a une file d'attente
- un event est une action ( ex: bouton de souris)
Exemple:
```bash
    $ ls /dev/input/
by-path  event1   event11  event2  event4  event6  event8  mice    mouse1
event0   event10  event12  event3  event5  event7  event9  mouse0
```
---

 ==> ce n'est ni un pipe ni un file normal : CHARACTER DEVICE
    - ca lire ou ecrit direct au periph sans cache ni rien.

---

## EVTEST:

Permet de voir les peipherique de maniere precise:

```bash 
    sudo apt install evtest
```
Puis:
```bash 
    sudo evtest
```


---






 
