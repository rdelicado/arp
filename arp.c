#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
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

// https://www.youtube.com/watch?v=O1y7xBC_6Ns&ab_channel=CodersESCOM
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
    if (ioctl(fd, SIOCGIFINDEX, &nic) == -1) {
        system("clear");
        perror("Error en el indes\n");
        exit(1);
    } else {
        index = nic.ifr_ifindex;
    }
    return index;
}

void getData(int fd)
{
    struct ifreq nic;
    if (ioctl(fd, SIOCGIFHWADDR, &nic) == -1) {
        perror("Error al encontrar la MAC\n");
    } else {
        memcpy(MacOrigen, nic.ifr_hwaddr.sa_data, 6);
        printf("\nLa MAC del dispostivo es: ");
        printf("%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", 
            MacOrigen[0], MacOrigen[1], MacOrigen[2], 
            MacOrigen[3], MacOrigen[4], MacOrigen[5]);
    }
    
    if (ioctl(fd, SIOCGIFADDR, &nic) == -1) {
        perror("Error al encontrar la IP\n");
    } else {
        memcpy(ipOrigen, nic.ifr_hwaddr.sa_data + 2, 4);
        printf("\nIp de dispositivo: ");
        printf("%d.%d.%d.%d\n", ipOrigen[0], ipOrigen[1], ipOrigen[2], ipOrigen[3]);
    }

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
        printf("Socket abierto\n");
        index = getIndex(fd);
        printf("Index: %i\n", index);
        getData(fd);
    }
    close(fd);
    return 0;
}