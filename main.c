#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>
#include <time.h>

int main() {

  //================================ Create a fake mouse device

  // creer uns struct vide prete a etre associer a un peripherique:
  struct libevdev *dev = libevdev_new();
    // je remplie la struct pour init ma mouse:
  libevdev_set_name(dev, "USB Kottak Fake Mouse");
  
  
  //================================== Define what the mouse is capable of
    // definir de quoi le periph est capable:
  libevdev_enable_event_type(dev, EV_REL);
  libevdev_enable_event_code(dev, EV_REL, REL_X, NULL);
  libevdev_enable_event_code(dev, EV_REL, REL_Y, NULL);
        // toujours synchroniser : un flush ? 
        // SYN = message de fin de paquet envoyer par un periph
  libevdev_enable_event_type(dev, EV_SYN);
  libevdev_enable_event_code(dev, EV_SYN, SYN_REPORT, NULL);
 
      // ajouter un click pour que le kernel affiche la souris:
  libevdev_enable_event_type(dev, EV_KEY);
  libevdev_enable_event_code(dev, EV_KEY, BTN_LEFT, NULL); 

  struct libevdev_uinput *uidev = NULL; // receptacle du pointeur du futur objet virtuelle

  // creation de l'objet virtu claqué sur "dev", avec un flag-ordre, puis le pointeur:
  // libevdev_uinput_create_from_device(dev, flags, &uidev);
  int code = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &uidev);
  if (code != 0) {
    perror("error create");
    return -1;
  }
  printf("first func success!\n");



  //======================================= Fire fake mouse events
  srand(time(NULL)); // seed pour le random
  while (1)   {

    int amplitude = rand() % 41 -20; // random entre -20 et 20
    int direction = rand() % 2 == 0 ? REL_X : REL_Y;  // choix 50/50 entre chaque 

    // on utilise uidev : le pointeur receptacle du debut pour manipuler mon virtu periph:
    libevdev_uinput_write_event(uidev, EV_REL, direction, amplitude);
    libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);

    usleep(5000);


  }


}
