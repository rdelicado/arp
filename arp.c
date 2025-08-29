#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ehthernet.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>

unsigned char MacOrigen[6], ipOrigen[4], MaskO[4];

https://www.youtube.com/watch?v=O1y7xBC_6Ns&ab_channel=CodersESCOM
int openSocket()
{
    int packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    return packet_socket;
}

int getIndex(int fd)
{
    int index, i;
    struct ifreq nic;

    printf("Inserta el nombre de la interfaz: ");
    scanf("%s", nic.ifr_name);
    if (ioctl(ds, SIOCGIFINDEX, &nic) == -1) {
        system("clear");
        perror("Error en el indes\n");
        exit(1);
    } else {
        index = nic.ifr_ifindex;
    }
    return index;
}

void getData(int ds)
{
    struct
}

int main()
{
    int fd, index;
    fd = openSocket();
    
    if (fd == -1) {
        perror("Error al abrir el socket\n");
        exit(1);
    } else {
        system("clear");
        printf("Socket abierto\n")
        index = getIndex(fd);
        printf("Index: %i\n", index);
        getData(fd);
    }
    close(fd);
    return 0;
}