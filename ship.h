#ifndef SHIP_H
#define SHIP_H

typedef struct
{
    int x;
    int y;
} Ship;

void initShip(Ship *ship);
void updateShip(Ship *ship, char input);
void renderShip(Ship *ship);

#endif