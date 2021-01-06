#include <stdio.h>
#include <stdlib.h>
#include "managerMO.h"

int main(void)
{
    ManagerMO player;
    char cmd[512];

    initManagerMO(&player);

    addMO(&player,"WEI","data/fish.jpg",10,10,2014,PHOTO);
    addMO(&player,"WEI2","data/fishAndTree.jpg",11,10,2014,PHOTO);
    addMO(&player,"NewsAlert","data/dedicaceAKarol.mkv",10,10,2015,VIDEO);


    removeMO(&player,"WEI2");

    for(start(&player); !end(&player) ; next(&player))
        switch(getTypeCurrentMO(&player))
        {
            case PHOTO :
            {
                //build the command to view the picture
                sprintf(cmd," gpicview %s",getPathCurrentMO(&player));
                //display the command to view the picture
                printf("Visualisation de la photo %s : \n %s \n", getNameCurrentMO(&player),cmd);
                //launch the command to view the picture
                system(cmd);
                    break;
            }
            case VIDEO :
            {
                //build the command to view the video
                sprintf(cmd,"mplayer %s",getPathCurrentMO(&player));

                //display the command to view the video
                printf("Visualisation de la video %s : \n %s \n", getNameCurrentMO(&player),cmd);

                //launch the command to view the video
                system(cmd);
                    break;
            }
            default :
                    printf("Objet inconnu\n");
        }


    clearManagerMO(&player);

    return 0;
}

