#include <stdio.h>
#include <string.h>

typedef enum
{
    VGRMOV_PTP, // 3 threads
    VGRMOV_XYZ, // seq3 ...
    VGRMOV_XZY,
    VGRMOV_YXZ,
    VGRMOV_YZX,
    VGRMOV_ZXY,
    VGRMOV_ZYX,
    VGRMOV_X_PTP, // seq2 ...
    VGRMOV_Y_PTP,
    VGRMOV_Z_PTP
} TxtVgrPosOrder_t;

typedef struct
{
    int x;
    int y;
    int z;
} EncPos3;

typedef struct
{
    EncPos3 DIN0;
    EncPos3 DIN;
    // Add more positions as needed
} CalibData;

CalibData calibData = {
    .DIN0 = {17, 600, 16},
    .DIN = {17, 758, 16},
    // Add more positions as needed
};

void move(const char *pos3name, TxtVgrPosOrder_t order)
{
    if (strcmp(pos3name, "DIN0") == 0)
    {
        EncPos3 pos3 = calibData.DIN0;
        // Perform the move operation using pos3 and order
        printf("Moving to DIN0 position\n");
        printf("x: %d, y: %d, z: %d\n", pos3.x, pos3.y, pos3.z);
    }
    else if (strcmp(pos3name, "DIN") == 0)
    {
        EncPos3 pos3 = calibData.DIN;
        // Perform the move operation using pos3 and order
        printf("Moving to DIN position\n");
        printf("x: %d, y: %d, z: %d\n", pos3.x, pos3.y, pos3.z);
    }
    else
    {
        printf("Position not found\n");
    }
}

int main()
{
    const char *pos3name = "DIN0";
    TxtVgrPosOrder_t order = VGRMOV_PTP;
    move(pos3name, order);
    return 0;
}

