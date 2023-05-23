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

void axisX_moveAbs(unsigned short x);
void axisY_moveAbs(unsigned short y);
void axisZ_moveAbs(unsigned short z);

void move_xyz(unsigned short x, unsigned short y, unsigned short z, TxtVgrPosOrder_t order)
{
    switch (order)
    {
        case VGRMOV_PTP:
            axisX_moveAbs(x);
            axisY_moveAbs(y);
            axisZ_moveAbs(z);
            break;
        default:
            break;
    }
}

void axisX_moveAbs(unsigned short x)
{
    // Implementation of axisX moveAbs
    printf("Moving axisX to position: %d\n", x);
}

void axisY_moveAbs(unsigned short y)
{
    // Implementation of axisY moveAbs
    printf("Moving axisY to position: %d\n", y);
}

void axisZ_moveAbs(unsigned short z)
{
    // Implementation of axisZ moveAbs
    printf("Moving axisZ to position: %d\n", z);
}

void move(const char *pos3name, TxtVgrPosOrder_t order)
{
    EncPos3 pos3;
    if (strcmp(pos3name, "DIN0") == 0)
    {
        pos3 = calibData.DIN0;
        // Perform the move operation using pos3 and order
        printf("Moving to DIN0 position\n");
        printf("x: %d, y: %d, z: %d\n", pos3.x, pos3.y, pos3.z);
    }
    else if (strcmp(pos3name, "DIN") == 0)
    {
        pos3 = calibData.DIN;
        // Perform the move operation using pos3 and order
        printf("Moving to DIN position\n");
        printf("x: %d, y: %d, z: %d\n", pos3.x, pos3.y, pos3.z);
    }
    else
    {
        printf("Position not found\n");
    }

    move_xyz(pos3.x, pos3.y, pos3.z, order);
}

void __attribute__((constructor)) init() {
	const char *pos3name = "DIN0";
    	TxtVgrPosOrder_t order = VGRMOV_PTP;
    	move(pos3name, order);
}


//int main()
//{
//    const char *pos3name = "DIN0";
//    TxtVgrPosOrder_t order = VGRMOV_PTP;
//    move(pos3name, order);
//    return 0;
//}

