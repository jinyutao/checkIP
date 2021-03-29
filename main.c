#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <sys/ioctl.h>  
#include <sys/socket.h>  
#include <sys/types.h>  
#include <netdb.h>  
#include <net/if.h>  
#include <arpa/inet.h>  
#include <fcntl.h>
#include <unistd.h>

static int get_gw_ip(char *eth, struct sockaddr_in *ipaddr,struct sockaddr_in * sub)
{
    int sock_fd;
    struct ifreq ifr;

    /**//* Get socket file descriptor */
    if ((sock_fd = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        return 0;
    }

    /**//* Get IP Address */
    strncpy(ifr.ifr_name, eth, IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ-1]='\0';

    if (ioctl(sock_fd, SIOCGIFADDR, &ifr) < 0)
    {
        printf(":No Such Device %s/n",eth);
        return 0;
    }

    memcpy(ipaddr, &ifr.ifr_addr, sizeof(struct sockaddr_in));

    if (ioctl(sock_fd, SIOCGIFNETMASK, &ifr) < 0)
    {
        printf(":No Such Device %s/n",eth);
        return 0;
    }
    memcpy(sub, &ifr.ifr_netmask, sizeof(struct sockaddr));

    close(sock_fd);
    return 1;
}


int main(int agvc,char* agvr[])
{
    struct sockaddr_in ipaddr_if;
    struct sockaddr_in sub_if;
    if(get_gw_ip("enp3s0", &ipaddr_if ,&sub_if) == 0)
    {
        return 0;
    }    
        printf("ipaddr_if %08X , mask: %08X\n",
            ipaddr_if.sin_addr.s_addr , sub_if.sin_addr.s_addr);

    return 0;
}
