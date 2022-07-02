//
//  main.cpp
//  ASD-T3-RBGraph
//
//  Cr1eated by Simone Cioffi on 31/05/22.

/*
    Per abilitare l'abilità di lettura del file all'interno della cartella del progetto si deve andare su:
        Product -> Scheme -> Edit Scheme.
    Dopodiche  poi selezionare : Run -> Options -> Use custom working directory e selezionare la cartella nella quale è situato il file di input.txt
 */


#include <iostream>
#include "Menu.hpp"

int main(int argc, const char * argv[]) {
    menu<int> Intmenu;
    //Recall Menu
    Intmenu.interactiveMenu();
    return 0;
    
    //Debbuging Errori
}
